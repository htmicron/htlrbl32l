/**
******************************************************************************
* @file    aes_manager_bluenrg_lp.c
* @author  AMS - RF Application Team
* @brief   This file provides functions implementation for BlueNRG-LP AES Manager
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
#include "aes_manager.h"
#include "aes_manager_bluenrg_lp.h"

/** @defgroup AES_Manager_BlueNRG_LP  AES Manager
* @{
*/

/** @defgroup AES_Manager_BlueNRG_LP_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup AES_Manager_BlueNRG_LP_Private_Defines Private Defines
* @{
*/
#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
__disable_irq(); \
  /* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

/**
* @}
*/

__STATIC_INLINE uint8_t AESMGR_Start(void);
__STATIC_INLINE void LL_AES_StartManualEncription(BLUE_TypeDef *BLUEx);
__STATIC_INLINE uint32_t LL_AES_IsBusy(BLUE_TypeDef *BLUEx);
  
/** @defgroup AES_Manager_BlueNRG_LP_Private_Variables Private Variables
* @{
*/
/**
* @}
*/

/** @defgroup AES_Manager_BlueNRG_LP_External_Variables External Variables
* @{
*/
/**
* @}
*/


/** @defgroup AES_Manager_BlueNRG_LP_Public_Functions Public Functions
* @{
*/

AESMGR_ResultStatus AESMGR_Init(void)
{
  if(!LL_APB2_IsEnabledClock(LL_APB2_PERIPH_MRBLE))
  {
    /* Peripheral reset */
    LL_APB2_ForceReset(LL_APB2_PERIPH_MRBLE);
    LL_APB2_ReleaseReset(LL_APB2_PERIPH_MRBLE);

    /* Enable MR_BLE's clock */
    LL_APB2_EnableClock(LL_APB2_PERIPH_MRBLE); 
  }
  return AESMGR_SUCCESS;
}

AESMGR_ResultStatus AESMGR_Deinit(void)
{
  // The init function must enable the BLE if I want use it without the BLE.
  return AESMGR_SUCCESS;
}

AESMGR_ResultStatus AESMGR_Encrypt(const uint32_t *plainTextData, const uint32_t *key, uint32_t *encryptedData, uint8_t isr)
{
  static volatile uint8_t inIsr;

  do
  {
    inIsr = isr;

    /* Write the Key in the BLE register */  
    BLUE->MANAESKEY0REG = key[0];
    BLUE->MANAESKEY1REG = key[1];
    BLUE->MANAESKEY2REG = key[2];
    BLUE->MANAESKEY3REG = key[3];

    /* Write the plain text data in the BLE register */
    BLUE->MANAESCLEARTEXT0REG = plainTextData[0];
    BLUE->MANAESCLEARTEXT1REG = plainTextData[1];
    BLUE->MANAESCLEARTEXT2REG = plainTextData[2];
    BLUE->MANAESCLEARTEXT3REG = plainTextData[3];

    AESMGR_Start();

    /* Read the plain text data in the BLE register */
    encryptedData[0] = BLUE->MANAESCIPHERTEXT0REG;
    encryptedData[1] = BLUE->MANAESCIPHERTEXT1REG;
    encryptedData[2] = BLUE->MANAESCIPHERTEXT2REG;
    encryptedData[3] = BLUE->MANAESCIPHERTEXT3REG;

  } while (inIsr != isr);

  return AESMGR_SUCCESS;
}


/**
 * @brief Function to start the AES 128 encryption in blocking mode.
 * @param  None
 *
 * @retval i     
 */
__STATIC_INLINE uint8_t AESMGR_Start(void)
{
    volatile uint8_t i = 100U;

    /* Start AES encryption */
    LL_AES_StartManualEncription(BLUE);
    do
    {
        i--;
        if( !LL_AES_IsBusy(BLUE) )
        {
            break;
        }
    } while (i != 0U);

    return i;
}

/**
* @}
*/


/** @defgroup AES_Manager_BlueNRG_LP_Private_Functions Private Functions
* @{
*/

/**
  * @brief  AES manual encryption Start function.
  * @rmtoll MANAESCMDREG          START         LL_AES_StartManualEncription
  * @param  BLUEx BLUE Instance
  * @retval None
  */
__STATIC_INLINE void LL_AES_StartManualEncription(BLUE_TypeDef *BLUEx)
{
  SET_BIT(BLUEx->MANAESCMDREG, BLUE_MANAESCMDREG_START);
}

/**
  * @brief  Indicate if AES is busy
  * @rmtoll MANAESSTATREG          BUSY         LL_AES_IsBusy
  * @param  BLUEx BLUE Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AES_IsBusy(BLUE_TypeDef *BLUEx)
{
  return ((READ_BIT(BLUEx->MANAESSTATREG, BLUE_MANAESSTATREG_BUSY) == (BLUE_MANAESSTATREG_BUSY)) ? 1U : 0U);
}


/**
* @}
*/

/**
* @}
*/
