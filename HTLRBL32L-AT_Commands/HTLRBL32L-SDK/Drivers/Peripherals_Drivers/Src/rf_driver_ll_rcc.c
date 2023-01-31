/**
  ******************************************************************************
  * @file    rf_driver_ll_rcc.c
  * @author  RF Application Team
  * @brief   RCC LL module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "rf_driver_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif
/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined(RCC)

/** @addtogroup RCC_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_LL_Private_Macros
  * @{
  */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_LL_Private_Functions RCC Private functions
  * @{
  */
uint32_t RCC_GetSystemClockFreq(void);

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_LL_Exported_Functions
  * @{
  */

/** @addtogroup RCC_LL_EF_Init
  * @{
  */

/**
  * @brief  Reset the RCC clock  to the default reset state. To Be Reviewed ???[FC]
  * @note   The default reset state of the clock configuration is given below:
  *         - HSI ON and used as system clock source
  *         - HSE and PLL Source OFF
  *         - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RCC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RCC_DeInit(void)
{
  uint32_t vl_mask;

  /* Disable all the HS clock source */
  LL_RCC_HSE_Disable();
  LL_RCC_RC64MPLL_Disable();

  /* Set the System Clock prescaler to reset state */
  LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_4);
 
  /* Wait for PLL READY bit to be reset */
  while(LL_RCC_RC64MPLL_IsReady() != 0U)
  {}

  /* Insure HSIRDY bit is set */
  while (LL_RCC_HSI_IsReady() == 0U)
  {}

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  /* Clear all interrupt flags */
  vl_mask = RCC_CIFR_LSIRDYF | RCC_CIFR_LSERDYF | RCC_CIFR_HSIRDYF | RCC_CIFR_HSERDYF | RCC_CIFR_HSIPLLRDYF;
  LL_RCC_WriteReg(CIFR, vl_mask);

  /* Clear reset flags */
  LL_RCC_ClearResetFlags();

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequency of the system clock device.
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   (**) HSI_VALUE is a constant defined in this file (default value
  *              64 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  * @note   (***) HSE_VALUE is a constant defined in this file (default value
  *               32 MHz). The HSE_VALUE value is divided from a 64 MHz PLL to return
  *               frequency of the crystal used.
  * @{
  */

/**
  * @brief  Return the frequency of the system clock.
  * @param  RCC_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which will hold the clocks frequencies
  * @retval None
  */
void LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks)
{
  /* Get SYSCLK frequency */
  RCC_Clocks->SYSCLK_Frequency = RCC_GetSystemClockFreq();
}

/**
  * @brief  Return SMPS clock frequency
  * @note   This function is only applicable when CPU runs.
  * @retval SMPS clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that the peripheral has a wrong ANADIV prescaler setup
  */
uint32_t LL_RCC_GetSMPSClockFreq(void)
{
  uint32_t smps_frequency;
  uint32_t smps_prescaler;

  smps_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  
  smps_prescaler = LL_RCC_GetSMPSPrescaler();
    if (smps_prescaler == LL_RCC_SMPS_DIV_2) {
    smps_frequency = 32000000/4;
    } else {
    smps_frequency = 32000000/8;
    }
  
  return smps_frequency;
}
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup RCC_LL_Private_Functions
  * @{
  */

/**
  * @brief  Return SYSTEM clock (SYSCLK) frequency
  * @retval SYSTEM clock frequency (in Hz)
  */
uint32_t RCC_GetSystemClockFreq(void)
{
  uint32_t frequency;
  uint32_t smps_prescaler;

  if (LL_RCC_DIRECT_HSE_IsEnabled()) {
    return HSE_VALUE;
  } else {
    frequency = RC64MPLL_VALUE;
  }
  
  switch (LL_RCC_GetRC64MPLLPrescaler()){
  case LL_RCC_RC64MPLL_DIV_1:
    smps_prescaler = 1;
    break;
  case LL_RCC_RC64MPLL_DIV_2:
    smps_prescaler = 2;
    break;
  case LL_RCC_RC64MPLL_DIV_4:
    smps_prescaler = 4;
    break;
  case LL_RCC_RC64MPLL_DIV_8:
    smps_prescaler = 8;
    break;
  case LL_RCC_RC64MPLL_DIV_16:
    smps_prescaler = 16;
    break;
  case LL_RCC_RC64MPLL_DIV_32:
    smps_prescaler = 32;
    break;
  case LL_RCC_RC64MPLL_DIV_64:
    smps_prescaler = 64;
    break;
  }

  return (uint32_t)(frequency/smps_prescaler);
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
