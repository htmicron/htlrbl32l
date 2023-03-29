/**
******************************************************************************
* @file    rng_manager_bluenrg_lp.c
* @author  AMS - RF Application Team
* @brief   This file provides functions implementation for BlueNRG-LP RNG Manager.
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
#include "rng_manager.h"
#include "rng_manager_bluenrg_lp.h"

/** @defgroup RNG_Manager_BlueNRG_LP  RNG Manager
* @{
*/

/** @defgroup RNG_Manager_BlueNRG_LP_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_Private_Defines Private Defines
* @{
*/
#define RNG_BUFFER_DIM                  30

#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
__disable_irq(); \
  /* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_Private_Variables Private Variables
* @{
*/
//static uint16_t internalBuffer[RNG_BUFFER_DIM] = {0};
//static uint16_t internalBufferIndex = 0;

/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
void RNGMGR_PRIVATE_GenerateNewRandomNumberForBuffer(void);
/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_Private_Functions Private Functions
* @{
*/
void RNGMGR_PRIVATE_GenerateNewRandomNumberForBuffer(void)
{

}

/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_Public_Functions Public Functions
* @{
*/

RNGMGR_ResultStatus RNGMGR_Init(void)
{
  /* Peripheral clock enable */
  LL_AHB_EnableClock(LL_AHB_PERIPH_RNG);
  
  /* Initialize random numbers generation */
  LL_RNG_Enable(RNG);
  
  /* Generate Random 16bit Numbers */
  
#if (USE_TIMEOUT == 1)
  Timeout = RNG_GENERATION_TIMEOUT;
#endif /* USE_TIMEOUT */
  
  /* Wait for DRDY flag to be raised */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG))
  {
#if (USE_TIMEOUT == 1)
    /* Check Systick counter flag to decrement the time-out value */
    if (LL_SYSTICK_IsActiveCounterFlag()) 
    { 
      if(Timeout-- == 0)
      {
        return RNGMGR_ERROR_TIMEOUT;
      }
    } 
#endif /* USE_TIMEOUT */
  }
  
  /* Check if error occurs */
  if (  LL_RNG_IsActiveFlag_FAULT(RNG)  )
  {
    /* Clock or Seed Error detected. Set LED to blinking mode (Error type)*/
    return RNGMGR_ERROR;
  }
  
  /* Values of Generated Random numbers are now available in buffer array. */
  return RNGMGR_SUCCESS;
}


RNGMGR_ResultStatus RNGMGR_Deinit(void)
{
  /* Stop random numbers generation */
  LL_RNG_Disable(RNG);
  return RNGMGR_SUCCESS;
}


RNGMGR_ResultStatus RNGMGR_NewSecretKey(uint32_t* buffer)
{
  uint32_t temp[2];
  /* The requeste size of the input buffer is 8 */
  /* Get a random number to be used as Secret Key */
  for(int i=0; i<8; i++)
  {
    /* Wait for RNGRDY signal */
    while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));
    temp[0] = (uint32_t)LL_RNG_ReadRandData16(RNG);
    
    /* Wait for RNGRDY signal */
    while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));
    temp[1] = (uint32_t)LL_RNG_ReadRandData16(RNG);
    
    buffer[i] = ( temp[0] + (temp[1] << 16) );
  }
  return RNGMGR_SUCCESS;
}

/**
 * @brief Provide a 16-bit true random number 
 * @param buffer: pointer to the random value returned
 * @param isr: 1 = The function is being called from  the radio isr context
 *              0 = The function is being called from the user context
 *
 * @return error status: 0 = No error, 1 = Timeout
 */
RNGMGR_ResultStatus RNGMGR_GetRandom16(uint32_t* buffer, uint8_t isr)
{
  /* Wait for RNGRDY signal */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));
  
  buffer[0] = (uint32_t)LL_RNG_ReadRandData16(RNG);
  
  return RNGMGR_SUCCESS;
}
/**
* @}
*/

/**
* @}
*/
