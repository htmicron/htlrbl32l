/**
******************************************************************************
* @file    pka_manager_bluenrg_lp.c
* @author  AMS - RF Application Team
* @brief   This file provides functions implementation for BlueNRG-LP PKA Manager
*
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "pka_manager.h"
#include "pka_manager_bluenrg_lp.h"

/** @defgroup PKA_Manager_BlueNRG_LP  PKA Manager
* @{
*/


/** @defgroup PKA_Manager_BlueNRG_LP_Private_Variables Private Variables
* @{
*/
static uint32_t ret[24] = {0};
/**
* @}
*/


/** @defgroup PKA_Manager_BlueNRG_LP_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
PKAMGR_ResultStatus PKAMGR_PrivateInit(void);
PKAMGR_ResultStatus PKAMGR_PrivateDeinit(void);
void (*PKAMGR_funcCB_LP)(PKAMGR_ResultStatus errorCode, void *args);
/**
* @}
*/

/** @defgroup PKA_Manager_BlueNRG_LP_Private_Functions Private Functions
* @{
*/
PKAMGR_ResultStatus PKAMGR_PrivateInit(void)
{
  /* Peripheral clock enable */
  LL_AHB_EnableClock(LL_AHB_PERIPH_PKA);
  
  /* Configure NVIC for PKA interrupts */
  /*   Set priority for PKA_IRQn */
  /*   Enable PKA_IRQn */
  NVIC_SetPriority(PKA_IRQn, IRQ_HIGH_PRIORITY);
  NVIC_EnableIRQ(PKA_IRQn);
  
  /* Elliptic Curve Diffie-Hellman (ECDH)  signature generation in interrupt mode */
  LL_PKA_EnableIT_ADDRERR(PKA);
  LL_PKA_EnableIT_RAMERR(PKA);
  LL_PKA_EnableIT_PROCEND(PKA);
  
  return PKAMGR_SUCCESS;
}


PKAMGR_ResultStatus PKAMGR_PrivateDeinit(void)
{
  /* Force PKA reset */
  LL_AHB_ForceReset(LL_AHB_PERIPH_PKA);

  /* Release PKA reset */
  LL_AHB_ReleaseReset(LL_AHB_PERIPH_PKA);
    
  return PKAMGR_SUCCESS;
}

uint8_t PKAMGR_PowerSaveLevelCheck(uint8_t x){
  if(PKAMGR_SleepCheck()==PKAMGR_SUCCESS)
  {
    return POWER_SAVE_LEVEL_STOP_NOTIMER;
  }
  else // PKA on going
  {
    return POWER_SAVE_LEVEL_CPU_HALT;
  }
}

PKAMGR_ResultStatus PKAMGR_StartP256DHkeyGeneration(uint32_t* secretKey, uint32_t* publicKey, PKAMGR_funcCB funcCB)
{
  /* Set the PKA internal state to busy */
  if(PKAMGR_Lock()!=PKAMGR_SUCCESS)
    return PKAMGR_ERR_BUSY;
 
  PKAMGR_funcCB_LP = funcCB;
  
  /* ***** PROCEDURE FOR NewPoint ***** */
  
  /* Insert the random K for NewPoint */
  if(LL_PKA_SetData(LL_PKA_DATA_SK, (uint32_t*) secretKey) == ERROR)
  {
    PKAMGR_Unlock();
    return PKAMGR_ERR_PARAM; 
  } 
  
  /* Insert the initial starting point coordinates */
  if(LL_PKA_SetData(LL_PKA_DATA_PCX, (uint32_t *)&publicKey[0]) == ERROR)
  {
    PKAMGR_Unlock();
    return PKAMGR_ERR_PARAM; 
  } 
  
  if( LL_PKA_SetData(LL_PKA_DATA_PCY, (uint32_t *)&publicKey[8]) == ERROR)
  {
    PKAMGR_Unlock();
    return PKAMGR_ERR_PARAM; 
  } 
  
  /* Launch the computation in interrupt mode */
  LL_PKA_Start(PKA);
  
  return PKAMGR_SUCCESS;
}

/**
  * Brief   This function handles PKA Instance interrupt request.
  * Param   None
  * Retval  None
  */
void PKAMGR_IRQHandler(void)
{
  /* Manage the PKA RAM error flag */
  if(LL_PKA_IsActiveFlag_RAMERR(PKA) == 1)
  {
    LL_PKA_ClearFlag_RAMERR(PKA);
    PKAMGR_Unlock();
    ret[0] = 0x01;
    PKAMGR_funcCB_LP(PKAMGR_ERR_PROCESS, ret); 
  }
  
  /* Manage the Address error flag */
  if(LL_PKA_IsActiveFlag_ADDRERR(PKA) == 1)
  {
    LL_PKA_ClearFlag_ADDRERR(PKA);
    PKAMGR_Unlock();
    ret[0] = 0x02;
    PKAMGR_funcCB_LP(PKAMGR_ERR_PROCESS, ret); 
  }
   
  /* Manage the PKA End of Operation flag */
  if(LL_PKA_IsActiveFlag_PROCEND(PKA) == 1)
  {
    LL_PKA_ClearFlag_PROCEND(PKA);

    /* Compare to expected results */
    if (LL_PKA_VerifyProcess() == ERROR)
    {
      PKAMGR_Unlock();
      ret[0] = 0x03;
      PKAMGR_funcCB_LP(PKAMGR_ERR_PROCESS, ret); 
    }
    else
    {
      for(int i=0; i<24; i++)
        ret[i] = 0;
      /*  | Secret Key  | Public Key X-coord | Public Key Y-coord | */
      /*  | (32 octets) | (32 octets)        | (32 octets)        | */
      /* Get the new calculated point NewPoint of the ellipse       */
      LL_PKA_GetData(LL_PKA_DATA_SK, (uint8_t *)&ret[0]);
      LL_PKA_GetData(LL_PKA_DATA_PCX, (uint8_t *)&ret[8]);
      LL_PKA_GetData(LL_PKA_DATA_PCY, (uint8_t *)&ret[16]);
      
      PKAMGR_Unlock();
      PKAMGR_funcCB_LP(PKAMGR_SUCCESS, ret);
    }
  }   
}
/**
* @}
*/


/**
* @}
*/
