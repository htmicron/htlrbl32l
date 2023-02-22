/**
  ******************************************************************************
  * @file    rf_driver_hal_rcc_ex.c
  * @author  RF Application Team
  * @brief   Extended RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities RCC extended peripheral:
  *           + Extended Peripheral Control functions
  *           + Extended Clock management functions
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @defgroup RCCEx RCCEx
  * @brief RCC Extended HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup RCCEx_Private_Constants RCCEx Private Constants
 * @{
 */

#define CLOCKSMPS_TIMEOUT_VALUE  (5000U) /* 5 s    */

#define __LSCO1_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define LSCO1_GPIO_PORT        GPIOA
#define LSCO1_PIN              GPIO_PIN_4

#define __LSCO2_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define LSCO2_GPIO_PORT        GPIOA
#define LSCO2_PIN              GPIO_PIN_10

#define __LSCO3_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define LSCO3_GPIO_PORT        GPIOB
#define LSCO3_PIN              GPIO_PIN_12
#define LSCO3_GPIO_AF          GPIO_AF1_LCO



#define LSI2_TIMEOUT_VALUE         (3U)    /* to be adjusted with DS    */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Functions RCCEx Exported Functions
  * @{
  */

/** @defgroup RCCEx_Exported_Functions_Group1 Extended Peripheral Control functions
 *  @brief  Extended Peripheral Control functions
 *
@verbatim
 ===============================================================================
                ##### Extended Peripheral Control functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks
    frequencies.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the RCC extended peripherals clocks according to the specified
  *         parameters in the @ref RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit  pointer to a @ref RCC_PeriphCLKInitTypeDef structure that
  *         contains a field PeriphClockSelection which can be a combination of the following values:
  *
  *            @arg @ref RCC_PERIPHCLK_RF        RF peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SMPS      SMPS peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI2_I2S  SPI2 I2S peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3_I2S  SPI3 I2S peripheral clock
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

#if defined(BLUE)
  /*-------------------------- RF_BLE clock source configuration ---------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RF) == RCC_PERIPHCLK_RF))
  {
    assert_param(IS_RCC_RF_BLE_CLOCK_DIVIDER(RFClockDivSelection));
    __HAL_RCC_RF_RC64MPLL_SET_CONFIG(PeriphClkInit->RFClockSelection);
  }
#endif
  
  /*-------------------------- SMPS clock configuration -------------------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SMPS) == RCC_PERIPHCLK_SMPS))
  {
    assert_param(IS_RCC_SMPS_CLOCK_PRESC(PeriphClkInit->SmpsDivSelection));
    assert_param(IS_RCC_SMPS_ADC_ANA_CLOCK_PRESC(PeriphClkInit->SmpsADCANADivSelection));
    __HAL_RCC_SMPS_DIV_CONFIG(PeriphClkInit->SmpsDivSelection);
  }

#if defined(SPI2) 
  /*-------------------------- SPI2_I2S clock source configuration ---------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI2_I2S) == RCC_PERIPHCLK_SPI2_I2S))
  {
    assert_param(IS_RCC_SPI2I2S_CLOCK_SOURCE(PeriphClkInit->SPI2I2SClockSelection));
    __HAL_RCC_SPI2I2S_CONFIG(PeriphClkInit->SPI2I2SClockSelection);
  }
#endif

#if defined(SPI3)   
  /*-------------------------- SPI3_I2S clock source configuration ---------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI3_I2S) == RCC_PERIPHCLK_SPI3_I2S))
  {
    assert_param(IS_RCC_SPI3I2S_CLOCK_SOURCE(PeriphClkInit->SPI3I2SClockSelection));
    __HAL_RCC_SPI3I2S_CONFIG(PeriphClkInit->SPI3I2SClockSelection);
  }
#endif

  return HAL_OK;
}


/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals
  *         clocks(RF, SMPS, SPI2I2S, SPI3I2S).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/
  PeriphClkInit->PeriphClockSelection = 0;
#if defined(BLUE)
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_RF;
#endif
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_SMPS;
#if defined(SPI2)  
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_SPI2_I2S;
#endif
#if defined(SPI3)  
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_SPI3_I2S;
#endif 

#if defined(SPI2) 
  /* Get the SPI2 I2S clock source ---------------------------------------------*/
  PeriphClkInit->SPI2I2SClockSelection = __HAL_RCC_GET_SPI2I2S_SOURCE();
#endif

  /* Get the SPI3 I2S clock source ---------------------------------------------*/
  PeriphClkInit->SPI3I2SClockSelection = __HAL_RCC_GET_SPI3I2S_SOURCE();

  /* Get the RF BLE clock source -----------------------------------------------*/
#if defined(BLUE)
  PeriphClkInit->RFClockSelection = __HAL_RCC_RF_RC64MPLL_GET_CONFIG();
#endif

  /* Get the SMPS clock divider ------------------------------------------------*/
  PeriphClkInit->SmpsDivSelection = __HAL_RCC_GET_SMPS_DIV();
}

/**
  * @brief  Return the peripheral clock frequency for peripherals with clock source
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_RF        RF   peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SMPS      SMPS peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI2_I2S  SPI2 I2S peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3_I2S  SPI3 I2S peripheral clock
  * @retval Frequency in Hz
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t frequency;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));
  
  /* No if clausule is covered */
  frequency = 0;
  
  if(PeriphClk == RCC_PERIPHCLK_RF)
  {
    switch(__HAL_RCC_RF_RC64MPLL_GET_CONFIG())
    {
      case RCC_RF_RC64MPLL_DIV2:
        frequency = 32000000;
        break;
      case RCC_RF_RC64MPLL_DIV4:
        frequency = 16000000;
        break;
    }
  }
  else if (PeriphClk == RCC_PERIPHCLK_SMPS)
  {
    switch( __HAL_RCC_GET_SMPS_DIV())
    {
      case RCC_SMPSCLK_DIV2:
         frequency = 16000000/2;
         break;
      case RCC_SMPSCLK_DIV4:
         frequency = 16000000/4;
         break;      
    }
  }
  
#if defined(SPI2)
  if (PeriphClk == RCC_PERIPHCLK_SPI2_I2S)
  {
    if (__HAL_RCC_GET_SPI2I2S_SOURCE() == RCC_SPI2I2S_CLKSOURCE_16M)
    {
      frequency = 16000000;
    }
    else
    {
      frequency = 32000000;
    }
  }
#endif
  
  if (PeriphClk == RCC_PERIPHCLK_SPI3_I2S)
  {
    if (__HAL_RCC_GET_SPI3I2S_SOURCE() == RCC_SPI3I2S_CLKSOURCE_16M)
    {
      frequency = 16000000;
    }
    else
    {
      frequency = 32000000;
    }
  }
  
  return (frequency);
}

/**
  * @}
  */

/** @defgroup RCCEx_Exported_Functions_Group2 Extended Clock management functions
 *  @brief  Extended Clock management functions
 *
@verbatim
 ===============================================================================
                ##### Extended clock management functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the
    activation or deactivation of MSI PLL-mode, PLLSAI1, PLLSAI12, LSE CSS,
    Low speed clock output and clock after wake-up from STOP mode.
@endverbatim
  * @{
  */

/**
  * @brief  Select the clock source to output on LSCO1 pin(PA4) or LSC02 pin (PA10) or LSCO3 pin (PB12).
  * @note   PA4, PA10 or PB12 should be configured in alternate function mode.
  * @param  RCC_LSCOx  specifies the output direction for the clock source.
  *            @arg @ref RCC_LSCO1  Clock source to output on LSCO1 pin(PA4)
  *            @arg @ref RCC_LSCO2  Clock source to output on LSCO2 pin(PA10)
  *            @arg @ref RCC_LSCO3  Clock source to output on LSCO3 pin(PB12)
  * @param  RCC_LSCOSource  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSCOSOURCE_LSI       LSI clock selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSE       LSE clock selected as LSCO source
  * @retval None
  * @note   LSCO should be disable with @ref HAL_RCCEx_DisableLSCO
  */
void HAL_RCCEx_LSCOConfig(uint32_t RCC_LSCOx, uint32_t RCC_LSCOSource)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Check the parameters */
  assert_param(IS_RCC_LSCO(RCC_LSCOx));
  assert_param(IS_RCC_LSCOSOURCE(RCC_LSCOSource));

  /* Common GPIO init parameters */
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;

  /* RCC_LSCO1 */
  if(RCC_LSCOx == RCC_LSCO1)
  {
    /* LSCO1 Clock Enable */
    __LSCO1_CLK_ENABLE();
    /* Configue the LSCO1 pin in alternate function mode */
    GPIO_InitStruct.Pin       = LSCO1_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF0_LCO;
    HAL_GPIO_Init(LSCO1_GPIO_PORT, &GPIO_InitStruct);
  }
  else if (RCC_LSCOx == RCC_LSCO2)
  {
    /* LSCO2 Clock Enable */
    __LSCO2_CLK_ENABLE();
    /* Configue the LSCO2 pin in alternate function mode */
    GPIO_InitStruct.Pin       = LSCO2_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF0_LCO;
    HAL_GPIO_Init(LSCO2_GPIO_PORT, &GPIO_InitStruct);
  }
  else
  {
    /* LSCO3 Clock Enable */
    __LSCO3_CLK_ENABLE();
    /* Configue the LSCO3 pin in alternate function mode */
    GPIO_InitStruct.Pin       = LSCO3_PIN;
    GPIO_InitStruct.Alternate = LSCO3_GPIO_AF;
    HAL_GPIO_Init(LSCO3_GPIO_PORT, &GPIO_InitStruct);
  }
  
  /* Configure the clock source to output */
  LL_RCC_ConfigLSCO(RCC_LSCOSource);
}



/**
  * @brief  Select the Low Speed clock source to output on LSCO pin (PA4).
  * @param  LSCOSource  specifies the Low Speed clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSCOSOURCE_LSI_LPMU  Internal LPMU slow clock source selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSI       LSI clock selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSE       LSE clock selected as LSCO source
  * @retval None
  */
void HAL_RCCEx_EnableLSCO(uint32_t LSCOSource)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Check the parameters */
  assert_param(IS_RCC_LSCOSOURCE(LSCOSource));

  /* LSCO Pin Clock Enable */
  __LSCO1_CLK_ENABLE();

  /* Configure the LSCO pin in analog mode */
  GPIO_InitStruct.Pin   = LSCO1_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = GPIO_AF0_LCO;
  HAL_GPIO_Init(LSCO1_GPIO_PORT, &GPIO_InitStruct);

  LL_RCC_ConfigLSCO(LSCOSource);
}

/**
  * @brief  Disable the Low Speed clock output.
  * @retval None
  */
void HAL_RCCEx_DisableLSCO(void)
{
  LL_RCC_ConfigLSCO(LL_RCC_LSCOSOURCE_NOCLOCK);
}


/**
  * @brief  Perform the oscillator(s) auto-trimming procedure
  * @param OscillatorType  Specifies the oscillator to be trimmed
  *   This parameter can be one of the following values:
  *     @arg @ref RCC_OSCILLATORTYPE_LSI LSI oscilloator selected.
  * @note The LSI trimming information is retained in DeepStop mode.
  *       Trimming is only needed once after a NRST reset.
  * @note The LSI oscillator must be enable before calling this trimming function through @ref HAL_RCC_OscConfig
  * @retval HAL status
  */
HAL_StatusTypeDef   HAL_RCCEx_TrimOsc(uint32_t OscillatorType)
{
  HAL_StatusTypeDef status;
  uint32_t trimming = 15U;

  assert_param(IS_RCC_TRIMOSC(OscillatorType));

  if(OscillatorType == RCC_OSCILLATORTYPE_LSI)
  {
    if (LL_RCC_LSI_IsReady() == 0U)
    {
      status = HAL_ERROR;
    }
    else
    {
      /* LSI Trimming procedure */
      /* 1/2 LSI is already enable and ready as initial condition */

      /*  3. Write LSITRIM to its max value b1111 */
      LL_RCC_LSI_SetTrimming(trimming);

      /* 4. Enable LSI trimming */
      LL_RCC_LSI_EnableTrimming();

      /* 5. Check if the LSI trimming value is OK by reading LSITRIMOK bit
            till trimming value reach 0 */
      const uint32_t temp_lsi1trimmed = LL_RCC_LSI_IsTrimmed();
      const uint32_t temp_lsi2trimmed = LL_RCC_LSI_GetTrimming();
      while((temp_lsi1trimmed != 1U) && (temp_lsi2trimmed != 0U))
      {
        /* 6/7 Decrease LSITRIM value by 1 */
        trimming = trimming - 1U;
        LL_RCC_LSI_SetTrimming(trimming);
      }

      /* Check if trimming is successful */
      if (LL_RCC_LSI_IsTrimmed() == 1U)
      {
        status = HAL_OK;
      }
      /* Otherwise, it means we reach minimal trimming value (0) wtihout trimming ok */
      else
      {
        status = HAL_ERROR;
      }
      /* 8. Disable LSI trimming */
      LL_RCC_LSI_DisableTrimming();
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  return status;
}

/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_RCC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

