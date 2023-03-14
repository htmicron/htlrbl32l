/**
******************************************************************************
* @file    pka_manager.c
* @author  AMS - RF Application Team
* @brief   This file provides weak functions for PKA Manager.
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
#include "rng_manager.h"
#include "rf_driver_ll_bus.h"


/** @defgroup PKA_Manager  PKA Manager
* @{
*/



/** @defgroup PKA_Manager_BlueNRG_LP_Private_Variables Private Variables
* @{
*/

/**
* @}
*/

/** @defgroup PKA_Manager_TypesDefinitions Private Type Definitions
* @{
*/

/* Internal state of the PKA */
typedef enum
{
  PKAMGR_STATE_READY     =  0,
  PKAMGR_STATE_IDLE,
  PKAMGR_STATE_RESET,
  PKAMGR_STATE_BUSY
} PKAMGR_State;

/**
* @}
*/

/** @defgroup PKA_Manager_Private_Defines Private Defines
* @{
*/
#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
__disable_irq(); \
  /* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)
/**
* @}
*/


/** @defgroup PKA_Manager_Private_Variables Private Variables
* @{
*/
static volatile uint32_t internalState = PKAMGR_STATE_RESET;
/**
* @}
*/


/** @defgroup PKA_Manager_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
PKAMGR_ResultStatus PKAMGR_PrivateInit(void);

PKAMGR_ResultStatus PKAMGR_PrivateDeinit(void);

//PKAMGR_ResultStatus PKAMGR_Isr(void);

//PKAMGR_ResultStatus PKAMGR_Tick(void);

PKAMGR_ResultStatus PKAMGR_Status(void);
/**
* @}
*/

/** @defgroup PKA_Manager_Private_Functions Private Functions
* @{
*/
WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_PrivateInit(void))
{
  return PKAMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_PrivateDeinit(void))
{
  return PKAMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

//WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_Tick(void))
//{
//  return PKAMGR_SUCCESS;
//  
//  /* NOTE : This function should not be modified, the callback is implemented 
//  in the dedicated board file */
//}


WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_Status(void))
{
  return PKAMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}
/**
* @}
*/

/** @defgroup PKA_Manager_Public_Functions Public Functions
* @{
*/
PKAMGR_ResultStatus PKAMGR_Init(void)
{
  if(internalState != PKAMGR_STATE_RESET)
  {
    return PKAMGR_ERROR;
  }
  
  if(PKAMGR_PrivateInit() == PKAMGR_SUCCESS)
  {
    ATOMIC_SECTION_BEGIN();
    internalState = PKAMGR_STATE_IDLE;
    ATOMIC_SECTION_END();
    return PKAMGR_SUCCESS;
  }
  return PKAMGR_ERROR;
}

PKAMGR_ResultStatus PKAMGR_Deinit(void)
{
  ATOMIC_SECTION_BEGIN();
  if(internalState == PKAMGR_STATE_BUSY)
  {
    ATOMIC_SECTION_END();
    return PKAMGR_ERR_BUSY;
  }
  else
  {
    /* Lock mechanism to access concurrently at the PKA resource */
    internalState = PKAMGR_STATE_BUSY;
    ATOMIC_SECTION_END();
  }
  
  if( PKAMGR_PrivateDeinit() == PKAMGR_SUCCESS)
  {
    ATOMIC_SECTION_BEGIN();
    internalState = PKAMGR_STATE_RESET;
    ATOMIC_SECTION_END();
    return PKAMGR_SUCCESS;
  }
  
  return PKAMGR_ERROR;
}

PKAMGR_ResultStatus PKAMGR_SleepCheck(void)
{
  if(internalState == PKAMGR_STATE_IDLE)
    return PKAMGR_SUCCESS;
  else
    return PKAMGR_ERR_BUSY;
}

WEAK_FUNCTION(uint8_t PKAMGR_PowerSaveLevelCheck(uint8_t x))
{
  (void) x;                                 /* To avoid gcc/g++ warnings */
  return 0;	

  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

PKAMGR_ResultStatus PKAMGR_Lock()
{
  /* Only one consumer (Application layer or Stack) can use the PKA at the time */
  ATOMIC_SECTION_BEGIN();
  if(internalState != PKAMGR_STATE_IDLE)
  {
    ATOMIC_SECTION_END();
    return PKAMGR_ERR_BUSY;
  }
  else
  {
    /* Lock mechanism to access concurrently at the PKA resource */
    internalState = PKAMGR_STATE_BUSY;
    ATOMIC_SECTION_END();
  }
  return PKAMGR_SUCCESS;
}

PKAMGR_ResultStatus PKAMGR_Unlock()
{
  /* Only one consumer (Application layer or Stack) can use the PKA at the time */
  ATOMIC_SECTION_BEGIN();
  if(internalState != PKAMGR_STATE_BUSY)
  {
    ATOMIC_SECTION_END();
    return PKAMGR_ERR_BUSY;
  }
  else
  {
    /* Unlock mechanism to access concurrently at the PKA resource */
    internalState = PKAMGR_STATE_IDLE;
    ATOMIC_SECTION_END();
  }
  return PKAMGR_SUCCESS;
}


PKAMGR_ResultStatus PKAMGR_StartP256PublicKeyGeneration(PKAMGR_funcCB funcCB)
{
  uint32_t secretKey[8] = {0};

#if 1
  RNGMGR_NewSecretKey(secretKey);
#else
  /* ****************TEST*********************** */
  /* 0 only to generate the point test           */
  /* 0xEE80AADE 0xF458AD60 0x635B77EA 0xA8CC1FEB */
  /* 0x700DEE70 0xD31F447C 0xF6A1319A 0x4915ED08 */
  /* 0xF0111A82 0xAD38071A 0xDCB9F308 0x77F0BAB8 */
  /* 0xA0FAFD61 0xF36CA7DA 0xD2F8209C 0x552E3E71 */
  #warning "TEST OF KNOWN POINT : RNG not used for secret key. This is a test to use a known start point to obtain the expected output point.\n\r"
  secretKey[0] = 0x00005e5f;
  for(int i=1; i<8; i++)
    secretKey[i] = 0;
#endif
  
  return PKAMGR_StartP256DHkeyGeneration(secretKey, (uint32_t *)&PKAStartPoint[0], funcCB);
}  


WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_StartP256DHkeyGeneration(uint32_t *secretKey, uint32_t *publicKey, PKAMGR_funcCB funcCB))
{
  (void) secretKey;                                 /* To avoid gcc/g++ warnings */
  (void) publicKey;                                 /* To avoid gcc/g++ warnings */
  (void) funcCB;                                    /* To avoid gcc/g++ warnings */
  return PKAMGR_SUCCESS;	

  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

/**
* @}
*/

/**
* @}
*/
