/**
  ******************************************************************************
  * @file    rf_driver_hal_rcc.c
  * @author  RF Application Team
  * @brief   RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Reset and Clock Control (RCC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                      ##### RCC specific features #####
  ==============================================================================
    [..]
      After reset the device is running from High Speed Internal oscillator
      (64 MHz RC oscillator) with Flash 0 wait state. All peripherals clock are off except internal
      SRAM, Flash and GPIO for SWD communication.

      (+) There is no prescaler
      (+) The clock for all peripherals is switched off, except the SRAM and FLASH and GPIO.
      (+) All GPIOs are in input mode, except the SWD pins which
          are assigned to be used for debug purpose.

    [..]
      Once the device started from reset, the user application has to:
      (+) Configure the clock source to be used to drive the System clock
          (if the application needs higher frequency/performance)
      (+) Configure the System clock frequency and Flash settings
      (+) Enable the clock for the peripheral(s) to be used
      (+) Configure the clock source(s) for peripherals which clocks are not
          always 16MHz or 32 MHz (SMPS, SMPS_ANA_ADC, SPI2I2S, SPI3I2S)

  @endverbatim
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
#include "system_BlueNRG_LP.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @brief RCC HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants
 * @{
 */
#define HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE          (2U)    /* 2 ms (minimum Tick + 1)   */
#define LSI_TIMEOUT_VALUE          (2U)    /* 2 ms (minimum Tick + 1)   */
#define PLL_TIMEOUT_VALUE          (2U)    /* 2 ms (minimum Tick + 1)   */
#define PRESCALER_TIMEOUT_VALUE    (2U)    /* 2 ms (minimum Tick + 1)   */
#define LATENCY_TIMEOUT_VALUE      (2U)    /* 2 ms (minimum Tick + 1)   */
#define CLOCKSWITCH_TIMEOUT_VALUE  (5000U) /* 5 s                       */

#define PLLSOURCE_NONE             (0U)
#define MEGA_HZ                     1000000U /* Division factor to convert Hz in Mhz */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#define __MCO1_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO1_GPIO_PORT        GPIOA
#define MCO1_PIN              GPIO_PIN_5

#define __MCO2_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO2_GPIO_PORT        GPIOA
#define MCO2_PIN              GPIO_PIN_11

#define __MCO3_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define MCO3_GPIO_PORT        GPIOB
#define MCO3_PIN              GPIO_PIN_15

#define __COUNTOF(_A_)   (sizeof(_A_) / sizeof(*(_A_)))
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup RCC_Private_Variables RCC Private Variables
  * @{
  */


/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
  @verbatim
 ===============================================================================
           ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to configure the internal and external oscillators
      (HSE, HSI, LSE, LSI, PLL and MCO) and the System busses clocks (SYSCLK).

    [..] Internal/external clock and PLL configuration
         (+) HSI (high-speed internal): 64 MHz factory-trimmed RC used through
             the PLL as System clock source.

         (+) LSI (low-speed internal): 32 KHz low consumption RC used as IWDG and/or RTC.
             clock source.

         (+) HSE (high-speed external): 32 MHz crystal oscillator. Can be used also optionally as RTC clock source.

         (+) LSE (low-speed external): 32.768 KHz oscillator used as IWDG, RTC,
             RF system Auto-wakeup from DeepStop modes.

         (+) PLL (clocked by HSI, HSE) providing system clock.

         (+) MCO (microcontroller clock output): used to output HSI, HSE, SYSCLK, 
             HSI64M_DIV2048, RC64MPLL clock (through a configurable prescaler) on PA5, PA11 & PB15 pins.

         -@- All the peripheral clocks have an always 16 MHz or 32 MHz to maintain fixed baud rate 
             while system clock is switching from a frequency to another from the System clock (SYSCLK).
             An always 32 MHz requested by few peripherals like the MR_BLE radio IP for instance.
             An always 16 MHz requested by few peripherals like serial interfaces or like flash controller and 
             MR_BLE radio IP (to have a fixed reference clock to manage delays).

           (+@) A programmable prescaled clock for ADC block. The ADC uses a 64 MHz prescaled clock (called
                CLKANA_ADC) that can be 8 MHz / 16 MHz / 32 MHz.
                You have to use @ref __HAL_RCC_SMPS_ADC_ANA_DIV_CONFIG() and @ref HAL_RCCEx_PeriphCLKConfig() 
                function to configure this clock.
           (+@) A programmable prescaled clock for I2S block, that can be 16 MHz / 32 MHz.
                You have to use @ref __HAL_RCC_SPI2I2S_CONFIG(), @ref __HAL_RCC_SPI3I2S_CONFIG and 
                @ref HAL_RCCEx_PeriphCLKConfig() function to configure this clock.

         (+) The maximum frequency of the SYSCLK is 64 MHz.
             The maximum frequency of the CLK_SYS_BLE is 32 MHz.

  @endverbatim

           Table 1. Flash Latency vs Clock frequency.
           +-------------------------------------------------------+
           | Wait State      |    System  clock frequency (MHz)    |
           |-----------------|-------------------------------------|
           |0WS(1 CPU cycles)|         SYSCLK < 32 MHz             |
           |-----------------|-------------------------------------|
           |1WS(2 CPU cycles)|         SYSCLK >= 32 MHz            |
           +-----------------+-------------------------------------+

  * @{
  */

/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - HSE, PLL OFF
  *            - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *            - Peripheral clocks
  *            - LSI and LSE clocks
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_DeInit(void)
{
  uint32_t tickstart;
  uint32_t vl_mask;
  
  /* Disable the HSE clock source */
  LL_RCC_HSE_Disable();
  
  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Disable the RC64MPLL clock source */
  LL_RCC_RC64MPLL_Disable();

  /* Set the System Clock prescaler to reset state */
  LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_4);
 
  /* Wait for PLL READY bit to be reset */
  while(LL_RCC_RC64MPLL_IsReady() != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Insure HSIRDY bit is set */
  while (LL_RCC_HSI_IsReady() == 0U)
  {
    if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }
  
  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  /* Clear all interrupt flags */
  vl_mask = RCC_CIFR_LSIRDYF | RCC_CIFR_LSERDYF | RCC_CIFR_HSIRDYF | RCC_CIFR_HSERDYF | RCC_CIFR_HSIPLLRDYF;
  LL_RCC_WriteReg(CIFR, vl_mask);

  /* Clear reset flags */
  LL_RCC_ClearResetFlags();

  return HAL_OK;
}

/**
  * @brief  Initialize the RCC Oscillators according to the specified parameters in the
  *         @ref RCC_OscInitTypeDef.
  * @param  RCC_OscInitStruct  pointer to a @ref RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  uint32_t tickstart;

  /* Check Null pointer */
  if(RCC_OscInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));

  /*------------------------------- HSE Configuration ------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));

    /* When the HSE is used as system clock it is not allowed to be disabled */
    const uint32_t temp_sysclksrc = __HAL_RCC_GET_SYSCLK_SOURCE();
    if (temp_sysclksrc == RCC_SYSCLKSOURCE_HSE)
    {
      if ((LL_RCC_HSE_IsReady() != 0U) && (RCC_OscInitStruct->HSEState == RCC_HSE_OFF))
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Set the new HSE configuration ---------------------------------------*/
      __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);

      /* Check the HSE State */
      if (RCC_OscInitStruct->HSEState != RCC_HSE_OFF)
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSE is ready */
        while (LL_RCC_HSE_IsReady() == 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSE is disabled */
        while (LL_RCC_HSE_IsReady() != 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }
  /*----------------------------- HSI Configuration --------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI(RCC_OscInitStruct->HSIState));
    assert_param(IS_RCC_HSI_CALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

    /* Check if HSI is used as system clock */
    const uint32_t temp_sysclksrc = __HAL_RCC_GET_SYSCLK_SOURCE();
    if (temp_sysclksrc == RCC_SYSCLKSOURCE_HSI)
    {
      /* When HSI is used as system clock it will not be disabled */
      if ((LL_RCC_HSI_IsReady() != 0U) && (RCC_OscInitStruct->HSIState == RCC_HSI_OFF))
      {
        return HAL_ERROR;
      }
      else
      {
        /* Check the HSI State */
        if (RCC_OscInitStruct->HSIState != RCC_HSI_OFF)
        {
          /* Disable the HSE clock source */
          __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF);

          /* Get Start Tick*/
          tickstart = HAL_GetTick();

          /* Wait till HSI is ready */
          while (LL_RCC_HSI_IsReady() == 0U)
          {
            if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
            {
              return HAL_TIMEOUT;
            }
          }
          /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
          __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
        }
        else
        {

          /* Get Start Tick*/
          tickstart = HAL_GetTick();

          /* Wait till HSI is disabled */
          while (LL_RCC_HSI_IsReady() != 0U)
          {
            if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
            {
              return HAL_TIMEOUT;
            }
          }
        }
      }
    }
  }
  /*--------------------------------- LSI Configuration -----------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSI(RCC_OscInitStruct->LSIState));

    /* Check the LSI State */
    if (RCC_OscInitStruct->LSIState != RCC_LSI_OFF)
    {
      assert_param(IS_RCC_LSI_CALIBRATION_VALUE(RCC_OscInitStruct->LSICalibrationValue));
      
      /*  Enable the Internal Low Speed oscillator (LSI) and set trimming value */
      __HAL_RCC_LSI_ENABLE();
      
      /* Get Start Tick*/
      tickstart = HAL_GetTick();
      
      /* Wait till LSI is ready */
      while (LL_RCC_LSI_IsReady() == 0U)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
      /* Adjusts the Internal Low Speed oscillator (LSI) calibration value */
      __HAL_RCC_LSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->LSICalibrationValue);
    }
    else
    {

      /* Disable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_DISABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is disabled */
      while (LL_RCC_LSI_IsReady() != 0U)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }  
  /*------------------------------ LSE Configuration -------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {

    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));

    /* Set the new LSE configuration -----------------------------------------*/
    __HAL_RCC_LSE_CONFIG(RCC_OscInitStruct->LSEState);

    /* Check the LSE State */
    if (RCC_OscInitStruct->LSEState != RCC_LSE_OFF)
    {
      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is ready */
      while (LL_RCC_LSE_IsReady() == 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is disabled */
      while (LL_RCC_LSE_IsReady() != 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  return HAL_OK;
}


/**
  * @brief  Initialize the system clock according to the specified
  *         parameters in the RCC_ClkInitStruct.
  * @param  RCC_ClkInitStruct  pointer to a @ref RCC_ClkInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @param  FLatency  FLASH Latency
  *          This parameter can be one of the following values:
  *            @arg FLASH_WAIT_STATE_0   FLASH 0 wait state cycle
  *            @arg FLASH_WAIT_STATE_1   FLASH 1 wait state cycle
  *
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency
  *         and updated within this function
  *
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source is ready.
  *
  * @note   You can use @ref HAL_RCC_GetClockConfig() function to know which clock is
  *         currently used as system clock source.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t FLatency)
{
  uint32_t tickstart;

  /* Check Null pointer */
  if(RCC_ClkInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_FLASH_WAIT_STATES(FLatency));

  /* To correctly read data from FLASH memory, the number of wait states (LATENCY)
     must be correctly programmed according to the frequency of the FLASH clock */

  /* Setup flash wait states because according the system clock frequency */
  if (FLatency != __HAL_FLASH_GET_WAIT_STATES())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_CONFIG register */
    __HAL_FLASH_SET_WAIT_STATES(FLatency);

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* Check that the new number of wait states is taken into account to access the Flash
       memory by reading the FLASH_CONFIG register */
    while (__HAL_FLASH_GET_WAIT_STATES() != FLatency)
    {
      if ((HAL_GetTick() - tickstart) > LATENCY_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /*------------------------- SYSCLK Configuration ---------------------------*/
  assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));
  assert_param(IS_RCC_SYSCLK_DIVIDER(RCC_ClkInitStruct->SYSCLKDivider));
    

  /* HSE is selected as System Clock Source */
  if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
  {
    /* Check the HSE ready flag */
    if (LL_RCC_HSE_IsReady() == 0U)
    {
      return HAL_ERROR;
    }
  }
  /* HSI is selected as System Clock Source */
  else
  {
    /* Check the HSI ready flag */
    if (LL_RCC_HSI_IsReady() == 0U)
    {
      return HAL_ERROR;
    }
  }

  /* Enable the RC64MPLL*/
  __HAL_RCC_RC64MPLL_ENABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till RC64MPLL is ready */
  while (LL_RCC_RC64MPLL_IsReady() == 0)
  {
    if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Configure the RC64MPLL multiplication factor */
  __HAL_RCC_RC64MPLL_PRESC_CONFIG(RCC_ClkInitStruct->SYSCLKDivider);

  /*---------------------------------------------------------------------------*/

  /* Update the SystemCoreClock global variable */
  switch (LL_RCC_GetRC64MPLLPrescaler())
  {
    case LL_RCC_RC64MPLL_DIV_1:
      SystemCoreClock = RC64MPLL_VALUE;
      break;
    case LL_RCC_RC64MPLL_DIV_2:
      SystemCoreClock = RC64MPLL_VALUE/2;
      break;
    case LL_RCC_RC64MPLL_DIV_4:
      SystemCoreClock = RC64MPLL_VALUE/4;
      break;
    case LL_RCC_RC64MPLL_DIV_8:
      SystemCoreClock = RC64MPLL_VALUE/8;
      break;
    case LL_RCC_RC64MPLL_DIV_16:
      SystemCoreClock = RC64MPLL_VALUE/16;
      break;
    case LL_RCC_RC64MPLL_DIV_32:
      SystemCoreClock = RC64MPLL_VALUE/32;
      break;
    case LL_RCC_RC64MPLL_DIV_64:
      SystemCoreClock = RC64MPLL_VALUE/64;
      break;
  }

  /* Configure the source of time base considering new system clocks settings*/
  return HAL_InitTick (HAL_GetTickPrio());
}

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Control functions
 *  @brief   RCC clocks control functions
 *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to:

    (+) Ouput clock to MCO pin.
    (+) Retrieve current clock frequencies.

@endverbatim
  * @{
  */

/**
  * @brief  Select the clock source to output on MCO1 pin(PA5) or MC02 pin (PA11) or MCO3 pin (PB15).
  * @note   PA5, PA11 or PB15 should be configured in alternate function mode.
  * @param  RCC_MCOx  specifies the output direction for the clock source.
  *            @arg @ref RCC_MCO1  Clock source to output on MCO1 pin(PA5)
  *            @arg @ref RCC_MCO2  Clock source to output on MCO2 pin(PA11)
  *            @arg @ref RCC_MCO3  Clock source to output on MCO3 pin(PB15)
  * @param  RCC_MCOSource  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCOSOURCE_NOCLOCK         MCO output disabled, no clock on MCO
  *            @arg @ref RCC_MCOSOURCE_SYSCLK          System  clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSI             HSI clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSE             HSE clock selected as MCO sourcee
  *            @arg @ref RCC_MCOSOURCE_RC64MPLL        RC64MPLL clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSI64M_DIV2048  HSI64M_DIV2048 clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_SMPS            SMPS clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_ADC             ADC clock before stabilization selected as MCO source
  * @param  RCC_MCODiv  specifies the MCO prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1  no division applied to MCO clock
  *            @arg @ref RCC_MCODIV_2  division by 2 applied to MCO clock
  *            @arg @ref RCC_MCODIV_4  division by 4 applied to MCO clock
  *            @arg @ref RCC_MCODIV_8  division by 8 applied to MCO clock
  *            @arg @ref RCC_MCODIV_16  division by 16 applied to MCO clock
  * @retval None
  */
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Check the parameters */
  assert_param(IS_RCC_MCO(RCC_MCOx));
  assert_param(IS_RCC_MCODIV(RCC_MCODiv));
  assert_param(IS_RCC_MCOSOURCE(RCC_MCOSource));

  /* Common GPIO init parameters */
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;

  /* RCC_MCO1 */
  if(RCC_MCOx == RCC_MCO1)
  {
    /* MCO1 Clock Enable */
    __MCO1_CLK_ENABLE();
    /* Configue the MCO1 pin in alternate function mode */
    GPIO_InitStruct.Pin       = MCO1_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    HAL_GPIO_Init(MCO1_GPIO_PORT, &GPIO_InitStruct);

  }
  else if (RCC_MCOx == RCC_MCO2)
  {
    /* MCO2 Clock Enable */
    __MCO2_CLK_ENABLE();
    /* Configue the MCO2 pin in alternate function mode */
    GPIO_InitStruct.Pin       = MCO2_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    HAL_GPIO_Init(MCO2_GPIO_PORT, &GPIO_InitStruct);

  }
  else
  {
    /* MCO3 Clock Enable */
    __MCO3_CLK_ENABLE();
    /* Configue the MCO3 pin in alternate function mode */
    GPIO_InitStruct.Pin       = MCO3_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF2_MCO;
    HAL_GPIO_Init(MCO3_GPIO_PORT, &GPIO_InitStruct);
  }

    /* Mask MCOSEL[] and CCOPRE[] bits then set MCO clock source and prescaler */
    LL_RCC_ConfigMCO(RCC_MCOSource, RCC_MCODiv);
}

/**
  * @brief  Return the SYSCLK frequency.
  *
  * @note   The system  computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source. The return value is the 
  *         content of the SystemCoreClock CMSIS variable
  *
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  return SystemCoreClock;
}

/**
  * @brief  Configure the RCC_OscInitStruct according to the internal
  *         RCC configuration registers.
  * @param  RCC_OscInitStruct  pointer to an RCC_OscInitTypeDef structure that
  *         will be configured.
  * @retval None
  */
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  /* Check the parameters */
  assert_param(RCC_OscInitStruct != (void *)NULL);

  /* Set all possible values for the Oscillator type parameter ---------------*/
  RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | \
                                      RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI;


  /* Get the HSE configuration -----------------------------------------------*/
  if ((RCC->CR & RCC_CR_HSEON) == RCC_CR_HSEON)
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_ON;
  }
  else
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_OFF;
  }

  /* Get the HSI configuration -----------------------------------------------*/
  if ((RCC->CR & RCC_CR_HSIRDY) == RCC_CR_HSIRDY)
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_ON;
  }
  else
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_OFF;
  }

  RCC_OscInitStruct->HSICalibrationValue = LL_RCC_HSI_GetCalibTrimming();

  /* Get the LSE configuration -----------------------------------------------*/
  if ((RCC->CR & RCC_CR_LSEBYP) == RCC_CR_LSEBYP)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_BYPASS;
  }
  else if ((RCC->CR & RCC_CR_LSEON) == RCC_CR_LSEON)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_ON;
  }
  else
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_OFF;
  }

  /* Get the LSI configuration -----------------------------------------------*/
  if ((RCC->CR & RCC_CR_LSION) == RCC_CR_LSION)
  {
    RCC_OscInitStruct->LSIState = RCC_LSI_ON;
  }
  else
  {
    RCC_OscInitStruct->LSIState = RCC_LSI_OFF;
  }

  RCC_OscInitStruct->LSICalibrationValue = LL_RCC_LSI_GetTrimming();
}

/**
  * @brief  Configure the RCC_ClkInitStruct according to the internal
  *         RCC configuration registers.
  * @param  RCC_ClkInitStruct Pointer to a @ref RCC_ClkInitTypeDef structure that
  *                           will be configured.
  * @param  pFLatency         Pointer on the Flash Latency.
  * @retval None
  */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency)
{
  /* Check the parameters */
  assert_param(RCC_ClkInitStruct != (void *)NULL);
  assert_param(pFLatency != (void *)NULL);

  /* Set all possible values for the Clock type parameter --------------------*/

  /* Get the SYSCLK configuration --------------------------------------------*/
  RCC_ClkInitStruct->SYSCLKSource = LL_RCC_GetSysClkSource();

  /* Get the SYSCLK Divider --------------------------------------------------*/
  RCC_ClkInitStruct->SYSCLKDivider = LL_RCC_GetRC64MPLLPrescaler();
  
  /* Get the Flash Wait State (Latency) configuration ------------------------*/
  *pFLatency = __HAL_FLASH_GET_WAIT_STATES();
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
