/**
  ******************************************************************************
  * @file    rf_driver_hal_rcc.h
  * @author  RF Application Team
  * @brief   Header file of RCC HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RF_DRIVER_HAL_RCC_H
#define RF_DRIVER_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"
#include "rf_driver_ll_rcc.h"
#include "rf_driver_ll_bus.h"


/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */

#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__)                            == RCC_OSCILLATORTYPE_NONE)     || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)      || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)      || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)      || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE))


#define IS_RCC_HSE(__HSE__)  (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON))

#define IS_RCC_LSE(__LSE__)  (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON) || \
                              ((__LSE__) == RCC_LSE_BYPASS))

#define IS_RCC_HSI(__HSI__)  (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))

#define IS_RCC_LSI(__LSI__)  (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))

#define IS_RCC_RC64MPLL(__PLL__) (((__PLL__) == RCC_RC64MPLL_OFF) || \
                                  ((__PLL__) == RCC_RC64MPLL_ON))

#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE))

#define IS_RCC_SYSCLK_DIVIDER(__HCLK__) (((__HCLK__) == RCC_RC64MPLL_DIV1) || ((__HCLK__) == RCC_RC64MPLL_DIV2)  || \
                                         ((__HCLK__) == RCC_RC64MPLL_DIV4) || ((__HCLK__) == RCC_RC64MPLL_DIV8)  || \
					 ((__HCLK__) == RCC_RC64MPLL_DIV16)|| ((__HCLK__) == RCC_RC64MPLL_DIV32) || \
					 ((__HCLK__) == RCC_RC64MPLL_DIV64))

#define IS_RCC_MCO(__MCOX__) ( ((__MCOX__) == RCC_MCO1) || ((__MCOX__) == RCC_MCO2) || ((__MCOX__) == RCC_MCO3) )
  
#define IS_RCC_MCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)        || \
                                      ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)         || \
                                      ((__SOURCE__) == RCC_MCOSOURCE_HSI)            || \
                                      ((__SOURCE__) == RCC_MCOSOURCE_HSE)            || \
                                      ((__SOURCE__) == RCC_MCOSOURCE_RC64MPLL)       || \
                                      ((__SOURCE__) == RCC_MCOSOURCE_HSI64M_DIV2048) || \
                                      ((__SOURCE__) == RCC_MCOSOURCE_SMPS)           || \
                                      ((__SOURCE__) == RCC_MCOSOURCE_ADC))

#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                ((__DIV__) == RCC_MCODIV_16)|| ((__DIV__) == RCC_MCODIV_32))

#define IS_RCC_LSE_DRIVE(__DRIVE__) (((__DRIVE__) == RCC_LSEDRIVE_LOW)        || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_HIGH))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value (default is @ref RCC_HSICALIBRATION_DEFAULT).*/

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  uint32_t LSICalibrationValue;  /*!< The LSI calibration trimming value .
                                    This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xF     */
} RCC_OscInitTypeDef;

/**
  * @brief  RCC System clock configuration structure definition
  */
typedef struct
{
  uint32_t SYSCLKSource;          /*!< The clock source used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t SYSCLKDivider;         /*!< The RC64MPLL clock divider used as system clock (SYSCLK). 
                                       This parameter can be a value of @ref RCC_RC64MPLL_Clock_Divider */
  
} RCC_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Timeout_Value Timeout Values
  * @{
  */
#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT  /* LSE timeout in ms        */
/**
  * @}
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE        0x00000000U   /*!< Oscillator configuration unchanged  */
#define RCC_OSCILLATORTYPE_HSE         0x00000001U   /*!< HSE to configure                    */
#define RCC_OSCILLATORTYPE_HSI         0x00000002U   /*!< HSI to configure                    */
#define RCC_OSCILLATORTYPE_LSE         0x00000004U   /*!< LSE to configure                    */
#define RCC_OSCILLATORTYPE_LSI         0x00000008U   /*!< LSI to configure                    */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                    0x00000000U                                /*!< HSE clock deactivation               */
#define RCC_HSE_ON                     RCC_CR_HSEON                               /*!< HSE clock activation                 */
/**
  * @}
  */

/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                    0x00000000U                                 /*!< LSE clock deactivation */
#define RCC_LSE_ON                     RCC_CR_LSEON                                /*!< LSE clock activation */
#define RCC_LSE_BYPASS                 RCC_CR_LSEBYP                               /*!< External clock source for LSE clock */
/**
  * @}
  */

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                    0x00000000U  /*!< HSI clock deactivation */
#define RCC_HSI_ON                     0x00000001U  /*!< HSI clock activation   */

#define RCC_HSICALIBRATION_DEFAULT     64U          /*!< Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U                        /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CR_LSION                       /*!< LSI clock activation   */
/**
  * @}
  */

/** @defgroup RCC_PLL_Config PLL Config
  * @{
  */
#define RCC_RC64MPLL_OFF                    0x00000000U      /*!< RC64MPLL deactivation */
#define RCC_RC64MPLL_ON                     RCC_CR_HSIPLLON  /*!< RC64MPLL activation   */
/**
  * @}
  */

/** @defgroup RCC_RF_RC64MPLL_Clock_Divider  RF RC64MPLL Clock Divider
  * @{
  */
#define RCC_RF_RC64MPLL_DIV2       LL_RCC_RF_RC64MPLL_DIV2   /*!< RC64MPLL divided by 2 used as RF system clock */
#define RCC_RF_RC64MPLL_DIV4       LL_RCC_RF_RC64MPLL_DIV4   /*!< RC64MPLL divided by 4 used as RF system clock */
/**
  * @}
  */

/** @defgroup RCC_RC64MPLL_Clock_Divider RC64MPLL Clock Divider
  * @{
  */
#define RCC_RC64MPLL_DIV1              LL_RCC_RC64MPLL_DIV_1    /*!< RC64MPLL division factor = 1   */
#define RCC_RC64MPLL_DIV2              LL_RCC_RC64MPLL_DIV_2    /*!< RC64MPLL division factor = 2   */
#define RCC_RC64MPLL_DIV4              LL_RCC_RC64MPLL_DIV_4    /*!< RC64MPLL division factor = 4   */
#define RCC_RC64MPLL_DIV8              LL_RCC_RC64MPLL_DIV_8    /*!< RC64MPLL division factor = 8   */
#define RCC_RC64MPLL_DIV16             LL_RCC_RC64MPLL_DIV_16   /*!< RC64MPLL division factor = 16  */
#define RCC_RC64MPLL_DIV32             LL_RCC_RC64MPLL_DIV_32   /*!< RC64MPLL division factor = 32  */
#define RCC_RC64MPLL_DIV64             LL_RCC_RC64MPLL_DIV_64   /*!< RC64MPLL division factor = 64  */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI           LL_RCC_SYS_HSI         /*!< HSI selection as system clock      */
#define RCC_SYSCLKSOURCE_HSE           LL_RCC_SYS_HSE         /*!< HSE selection as system clock      */
/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define RCC_MCO1                       0x00000000U          /*!< MCO1 index */
#define RCC_MCO2                       0x00000001U          /*!< MCO2 index */
#define RCC_MCO3                       0x00000002U          /*!< MCO3 index */

/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Source MCO Clock Source
  * @{
  */
#define RCC_MCOSOURCE_NOCLOCK         LL_RCC_MCOSOURCE_NOCLOCK            /*!< MCO output disabled, no clock on MCO */
#define RCC_MCOSOURCE_SYSCLK          LL_RCC_MCOSOURCE_SYSCLK             /*!< SYSCLK selection as MCO source */
#define RCC_MCOSOURCE_HSI             LL_RCC_MCOSOURCE_HSI                /*!< HSI selection as MCO source */
#define RCC_MCOSOURCE_HSE             LL_RCC_MCOSOURCE_HSE                /*!< HSE after stabilization selection as MCO source */
#define RCC_MCOSOURCE_RC64MPLL        LL_RCC_MCOSOURCE_RC64MPLL           /*!< RC64MPLL selection as MCO source */
#define RCC_MCOSOURCE_HSI64M_DIV2048  LL_RCC_MCOSOURCE_HSI64M_DIV2048     /*!< HSI64M_DIV2048 selection as MCO source */
#define RCC_MCOSOURCE_SMPS            LL_RCC_MCOSOURCE_SMPS               /*!< SMPS selection as MCO source */
#define RCC_MCOSOURCE_ADC             LL_RCC_MCOSOURCE_ADC                /*!< ADC selection as MCO source */
/**
  * @}
  */

  
/** @defgroup RCC_MCOx_Clock_Prescaler MCO Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                   LL_RCC_MCO_DIV_1                  /*!< MCO not divided */
#define RCC_MCODIV_2                   LL_RCC_MCO_DIV_2                  /*!< MCO divided by 2 */
#define RCC_MCODIV_4                   LL_RCC_MCO_DIV_4                  /*!< MCO divided by 4 */
#define RCC_MCODIV_8                   LL_RCC_MCO_DIV_8                  /*!< MCO divided by 8 */
#define RCC_MCODIV_16                  LL_RCC_MCO_DIV_16                 /*!< MCO divided by 16 */
#define RCC_MCODIV_32                  LL_RCC_MCO_DIV_32                 /*!< MCO divided by 32 */
/**
  * @}
  */

/** @defgroup RCC_HSEAMPTHRESHOLD HSE bias current factor
  * @{
  */
#if defined(RCC_RFSWHSECR_SATRG)
#define RCC_HSEAMPTHRESHOLD_1_2       LL_RCC_HSEAMPTHRESHOLD_1_2           /*!< HSE bias current factor 1/2 */
#define RCC_HSEAMPTHRESHOLD_3_4       LL_RCC_HSEAMPTHRESHOLD_3_4           /*!< HSE bias current factor 3/4 */
#endif

/**
  * @}
  */

/** @defgroup RCC_HSE_CURRENTMAX HSE current max limit
  * @{
  */
#define RCC_HSE_CURRENTMAX_0           LL_RCC_HSE_CURRENTMAX_0             /*!< HSE current max limit 0.18 mA/V */
#define RCC_HSE_CURRENTMAX_1           LL_RCC_HSE_CURRENTMAX_1             /*!< HSE current max limit 0.57 mA/V */
#define RCC_HSE_CURRENTMAX_2           LL_RCC_HSE_CURRENTMAX_2             /*!< HSE current max limit 0.78 mA/V */
#define RCC_HSE_CURRENTMAX_3           LL_RCC_HSE_CURRENTMAX_3             /*!< HSE current max limit 1.13 mA/V */
#define RCC_HSE_CURRENTMAX_4           LL_RCC_HSE_CURRENTMAX_4             /*!< HSE current max limit 0.61 mA/V */
#define RCC_HSE_CURRENTMAX_5           LL_RCC_HSE_CURRENTMAX_5             /*!< HSE current max limit 1.65 mA/V */
#define RCC_HSE_CURRENTMAX_6           LL_RCC_HSE_CURRENTMAX_6             /*!< HSE current max limit 2.12 mA/V */
#define RCC_HSE_CURRENTMAX_7           LL_RCC_HSE_CURRENTMAX_7             /*!< HSE current max limit 2.84 mA/V */

/**
  * @}
  */

/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_LSIRDY                  LL_RCC_CIFR_LSIRDYF      /*!< LSI Ready Interrupt flag */
#define RCC_IT_LSERDY                  LL_RCC_CIFR_LSERDYF      /*!< LSE Ready Interrupt flag */
#define RCC_IT_HSIRDY                  LL_RCC_CIFR_HSIRDYF      /*!< HSI Ready Interrupt flag */
#define RCC_IT_HSERDY                  LL_RCC_CIFR_HSERDYF      /*!< HSE Ready Interrupt flag */
#define RCC_IT_PLLRDY                  LL_RCC_CIFR_PLLRDYF      /*!< PLL Ready Interrupt flag */
#define RCC_IT_RTCRSTRELRDY            LL_RCC_CIFR_RTCRSTRELF   /*!< RTC Reset Release Interrupt Flag */
#define RCC_IT_WDGRSTRELRDY            LL_RCC_CIFR_WDGRSTRELF   /*!< WDG Reset Release Interrupt Flag */
#if defined(RCC_CIFR_LPURSTF)
#define RCC_IT_LPURSTRELRDY            LL_RCC_CIFR_LPURSTRELF   /*!< LPU Reset Release Interrupt Flag */
#endif
#if defined(RCC_CIFR_LCDRSTF)
#define RCC_IT_LCDRSTRELRDY            LL_RCC_CIFR_LCDRSTRELF   /*!< LCD Reset Release Interrupt Flag */
#endif
#if defined(RCC_CIFR_SCIRSTF)
#define RCC_IT_SCIRSTRELRDY            LL_RCC_CIFR_SCIRSTRELF   /*!< SCI Reset Release Interrupt Flag */
#endif

/**
  * @}
  */


/** @defgroup RCC_Flag Flags
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                RCC_CR_HSIRDY        /*!< HSI Ready flag */
#define RCC_FLAG_HSERDY                RCC_CR_HSERDY        /*!< HSE Ready flag */
#define RCC_FLAG_PLLRDY                RCC_CR_HSIPLLRDY     /*!< PLL Ready flag */
#define RCC_FLAG_LSIRDY                RCC_CR_LSIRDY        /*!< LSI Ready flag */
#define RCC_FLAG_LSERDY                RCC_CR_LSERDY        /*!< LSE Ready flag */
  
/* Flags in the CSR register */
#define RCC_FLAG_LOCKUPRST             RCC_CSR_LOCKUPRSTF   /*!< CPU lockup reset flag      */
#define RCC_FLAG_WDGRST                RCC_CSR_WDGRSTF      /*!< Watchdog reset flag        */
#define RCC_FLAG_SFTRST                RCC_CSR_SFTRSTF      /*!< Software reset flag        */
#define RCC_FLAG_PORRST                RCC_CSR_PORRSTF      /*!< Power-On or BOR reset flag */
#define RCC_FLAG_PADRSTF               RCC_CSR_PADRSTF      /*!< NRSTn pad reset flag       */
/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Configuration
  * @{
  */
#define RCC_LSEDRIVE_LOW                 LL_RCC_LSEDRIVE_LOW            /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW           LL_RCC_LSEDRIVE_MEDIUMLOW      /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH          LL_RCC_LSEDRIVE_MEDIUMHIGH     /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH                LL_RCC_LSEDRIVE_HIGH           /*!< LSE high drive capability */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup RCC_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_AHB_Peripheral_Clock_Enable_Disable AHB Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_DMA_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_DMA)
#define __HAL_RCC_GPIOA_CLK_ENABLE()           LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_ENABLE()           LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define __HAL_RCC_CRC_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_RNG)
#if defined(AES1)
#define __HAL_RCC_AES1_CLK_ENABLE()            LL_AHB_EnableClock(LL_AHB_PERIPH_AES1)
#endif

#define __HAL_RCC_DMA_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_DMA)
#define __HAL_RCC_GPIOA_CLK_DISABLE()          LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_DISABLE()          LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)
#define __HAL_RCC_CRC_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_RNG)
#if defined(AES1)
#define __HAL_RCC_AES1_CLK_DISABLE()           LL_AHB_DisableClock(LL_AHB_PERIPH_AES1)
#endif

/**
  * @}
  */

/** @defgroup RCC_APB0_Clock_Enable_Disable APB0 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB0 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#if defined(TIM1) 
#define __HAL_RCC_TIM1_CLK_ENABLE()            LL_APB0_EnableClock(LL_APB0_PERIPH_TIM1)
#endif
#if defined(TIM2) 
#define __HAL_RCC_TIM2_CLK_ENABLE()            LL_APB0_EnableClock(LL_APB0_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_CLK_ENABLE()          LL_APB0_EnableClock(LL_APB0_PERIPH_SYSCFG)
#if defined(LCD)
#define __HAL_RCC_LCDC_CLK_ENABLE()            LL_APB0_EnableClock(LL_APB0_PERIPH_LCDC)
#endif
#if defined(COMP1)
#define __HAL_RCC_COMP_CLK_ENABLE()            LL_APB0_EnableClock(LL_APB0_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_CLK_ENABLE()            LL_APB0_EnableClock(LL_APB0_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_CLK_ENABLE()             LL_APB0_EnableClock(LL_APB0_PERIPH_RTC)
#if defined(SCI)
#define __HAL_RCC_SCI_CLK_ENABLE()            LL_APB0_EnableClock(LL_APB0_PERIPH_SCI)
#endif
#define __HAL_RCC_WDG_CLK_ENABLE()             LL_APB0_EnableClock(LL_APB0_PERIPH_WDG)
#if defined(TIM16) 
#define __HAL_RCC_TIM16_CLK_ENABLE()           LL_APB0_EnableClock(LL_APB0_PERIPH_TIM16)
#endif
#if defined(TIM17) 
#define __HAL_RCC_TIM17_CLK_ENABLE()           LL_APB0_EnableClock(LL_APB0_PERIPH_TIM17)
#endif

#if defined(TIM1) 
#define __HAL_RCC_TIM1_CLK_DISABLE()           LL_APB0_DisableClock(LL_APB0_PERIPH_TIM1)
#endif
#if defined(TIM2) 
#define __HAL_RCC_TIM2_CLK_DISABLE()           LL_APB0_DisableClock(LL_APB0_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_CLK_DISABLE()         LL_APB0_DisableClock(LL_APB0_PERIPH_SYSCFG)
#if defined(LCD)
#define __HAL_RCC_LCDC_CLK_DISABLE()           LL_APB0_DisableClock(LL_APB0_PERIPH_LCDC)
#endif
#if defined(COMP1)
#define __HAL_RCC_COMP_CLK_DISABLE()           LL_APB0_DisableClock(LL_APB0_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_CLK_DISABLE()            LL_APB0_DisableClock(LL_APB0_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_CLK_DISABLE()            LL_APB0_DisableClock(LL_APB0_PERIPH_RTC)
#if defined(SCI)
#define __HAL_RCC_SCI_CLK_DISABLE()            LL_APB0_DisableClock(LL_APB0_PERIPH_SCI)
#endif
#define __HAL_RCC_WDG_CLK_DISABLE()            LL_APB0_DisableClock(LL_APB0_PERIPH_WDG)
#if defined(TIM16) 
#define __HAL_RCC_TIM16_CLK_DISABLE()          LL_APB0_DisableClock(LL_APB0_PERIPH_TIM16)
#endif
#if defined(TIM17) 
#define __HAL_RCC_TIM17_CLK_DISABLE()          LL_APB0_DisableClock(LL_APB0_PERIPH_TIM17)
#endif
/**
  * @}
  */
  
/** @defgroup RCC_APB1_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#if defined(SPI1) 
#define __HAL_RCC_SPI1_CLK_ENABLE()            LL_APB1_EnableClock(LL_APB1_PERIPH_SPI1)
#endif 
#define __HAL_RCC_ADCDIG_CLK_ENABLE()          LL_APB1_EnableClock(LL_APB1_PERIPH_ADCDIG)
#define __HAL_RCC_ADCANA_CLK_ENABLE()          LL_APB1_EnableClock(LL_APB1_PERIPH_ADCANA)
#define __HAL_RCC_LPUART_CLK_ENABLE()          LL_APB1_EnableClock(LL_APB1_PERIPH_LPUART)
#define __HAL_RCC_USART_CLK_ENABLE()           LL_APB1_EnableClock(LL_APB1_PERIPH_USART)
#if defined(SPI2) 
#define __HAL_RCC_SPI2_CLK_ENABLE()            LL_APB1_EnableClock(LL_APB1_PERIPH_SPI2)
#endif 
#if defined(SPI3) 
#define __HAL_RCC_SPI3_CLK_ENABLE()            LL_APB1_EnableClock(LL_APB1_PERIPH_SPI3)
#endif
#if defined(I2C1) 
#define __HAL_RCC_I2C1_CLK_ENABLE()            LL_APB1_EnableClock(LL_APB1_PERIPH_I2C1)
#endif
#if defined(I2C2)
#define __HAL_RCC_I2C2_CLK_ENABLE()            LL_APB1_EnableClock(LL_APB1_PERIPH_I2C2)
#endif 

#if defined(SPI1) 
#define __HAL_RCC_SPI1_CLK_DISABLE()           LL_APB1_DisableClock(LL_APB1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADCDIG_CLK_DISABLE()         LL_APB1_DisableClock(LL_APB1_PERIPH_ADCDIG)
#define __HAL_RCC_ADCANA_CLK_DISABLE()         LL_APB1_DisableClock(LL_APB1_PERIPH_ADCANA)
#define __HAL_RCC_LPUART_CLK_DISABLE()         LL_APB1_DisableClock(LL_APB1_PERIPH_LPUART)
#define __HAL_RCC_USART_CLK_DISABLE()          LL_APB1_DisableClock(LL_APB1_PERIPH_USART)
#if defined(SPI2) 
#define __HAL_RCC_SPI2_CLK_DISABLE()           LL_APB1_DisableClock(LL_APB1_PERIPH_SPI2)
#endif
#if defined(SPI3) 
#define __HAL_RCC_SPI3_CLK_DISABLE()           LL_APB1_DisableClock(LL_APB1_PERIPH_SPI3)
#endif
#if defined(I2C1) 
#define __HAL_RCC_I2C1_CLK_DISABLE()           LL_APB1_DisableClock(LL_APB1_PERIPH_I2C1)
#endif
#if defined(I2C2) 
#define __HAL_RCC_I2C2_CLK_DISABLE()           LL_APB1_DisableClock(LL_APB1_PERIPH_I2C2)
#endif
/**
  * @}
  */
  
/** @defgroup RCC_APB2_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(BLUE)
#define __HAL_RCC_MRBLE_CLK_ENABLE()            LL_APB2_EnableClock(LL_APB2_PERIPH_MRBLE)

#define __HAL_RCC_MRBLE_CLK_DISABLE()           LL_APB2_DisableClock(LL_APB2_PERIPH_MRBLE)
#endif
/**
  * @}
  */

/** @defgroup RCC_AHB_Peripheral_Clock_Enable_Disable_Status AHB Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_DMA_IS_CLK_ENABLED()             LL_AHB_IsEnabledClock(LL_AHB_PERIPH_DMA)
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()           LL_AHB_IsEnabledClock(LL_AHB_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()           LL_AHB_IsEnabledClock(LL_AHB_PERIPH_GPIOB)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()             LL_AHB_IsEnabledClock(LL_AHB_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_IS_CLK_ENABLED()             LL_AHB_IsEnabledClock(LL_AHB_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_IS_CLK_ENABLED()             LL_AHB_IsEnabledClock(LL_AHB_PERIPH_RNG)
#if defined(AES1)
#define __HAL_RCC_AES1_IS_CLK_ENABLED()            LL_AHB_IsEnabledClock(LL_AHB_PERIPH_AES1)
#endif

#define __HAL_RCC_DMA_IS_CLK_DISABLED()            !(LL_AHB_IsEnabledClock(LL_AHB_PERIPH_DMA))
#define __HAL_RCC_GPIOA_IS_CLK_DISABLED()          !(LL_AHB_IsEnabledClock(LL_AHB_PERIPH_GPIOA))
#define __HAL_RCC_GPIOB_IS_CLK_DISABLED()          !(LL_AHB_IsEnabledClock(LL_AHB_PERIPH_GPIOB))
#define __HAL_RCC_CRC_IS_CLK_DISABLED()            !(LL_AHB_IsEnabledClock(LL_AHB_PERIPH_CRC))
#if defined(PKA)
#define __HAL_RCC_PKA_IS_CLK_DISABLED()            !(LL_AHB_IsEnabledClock(LL_AHB_PERIPH_PKA))
#endif
#define __HAL_RCC_RNG_IS_CLK_DISABLED()            !(LL_AHB_IsEnabledClock(LL_AHB_PERIPH_RNG))
#if defined(AES1)
#define __HAL_RCC_AES1_IS_CLK_DISABLED()           !(LL_AHB_IsEnabledClock(LL_AHB_PERIPH_AES1))
#endif
/**
  * @}
  */

/** @defgroup RCC_APB0_Clock_Enable_Disable_Status APB0 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB0 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#if defined(TIM1) 
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()            LL_APB0_IsEnabledClock(LL_APB0_PERIPH_TIM1)
#endif
#if defined(TIM2) 
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()            LL_APB0_IsEnabledClock(LL_APB0_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()          LL_APB0_IsEnabledClock(LL_APB0_PERIPH_SYSCFG)
#if defined(LCD)
#define __HAL_RCC_LCDC_IS_CLK_ENABLED()            LL_APB0_IsEnabledClock(LL_APB0_PERIPH_LCDC)
#endif
#if defined(COMP1)
#define __HAL_RCC_COMP_IS_CLK_ENABLED()            LL_APB0_IsEnabledClock(LL_APB0_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()             LL_APB0_IsEnabledClock(LL_APB0_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_IS_CLK_ENABLED()             LL_APB0_IsEnabledClock(LL_APB0_PERIPH_RTC)
#if defined(SCI)
#define __HAL_RCC_SCI_IS_CLK_ENABLED()             LL_APB0_IsEnabledClock(LL_APB0_PERIPH_SCI)
#endif
#define __HAL_RCC_WDG_IS_CLK_ENABLED()             LL_APB0_IsEnabledClock(LL_APB0_PERIPH_WDG)
#if defined(TIM16) 
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()           LL_APB0_IsEnabledClock(LL_APB0_PERIPH_TIM16)
#endif
#if defined(TIM17) 
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()           LL_APB0_IsEnabledClock(LL_APB0_PERIPH_TIM17)
#endif

#if defined(TIM1) 
#define __HAL_RCC_TIM1_IS_CLK_DISABLED()           !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_TIM1))
#endif
#if defined(TIM2) 
#define __HAL_RCC_TIM2_IS_CLK_DISABLED()           !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_TIM2))
#endif
#define __HAL_RCC_SYSCFG_IS_CLK_DISABLED()         !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_SYSCFG))
#if defined(LCD)
#define __HAL_RCC_LCDC_IS_CLK_DISABLED()           !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_LCDC))
#endif
#if defined(COMP1)
#define __HAL_RCC_COMP_IS_CLK_DISABLED()           !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_COMP))
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_IS_CLK_DISABLED()            !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_DAC))
#endif
#define __HAL_RCC_RTC_IS_CLK_DISABLED()            !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_RTC))
#if defined(SCI)
#define __HAL_RCC_SCI_IS_CLK_DISABLED()            !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_SCI))
#endif
#define __HAL_RCC_WDG_IS_CLK_DISABLED()            !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_WDG))
#if defined(TIM16) 
#define __HAL_RCC_TIM16_IS_CLK_DISABLED()          !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_TIM16))
#endif
#if defined(TIM17) 
#define __HAL_RCC_TIM17_IS_CLK_DISABLED()          !(LL_APB0_IsEnabledClock(LL_APB0_PERIPH_TIM17))
#endif
/**
  * @}
  */


/** @defgroup RCC_APB1_Clock_Enable_Disable_Status APB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(SPI1) 
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()            LL_APB1_IsEnabledClock(LL_APB1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADCDIG_IS_CLK_ENABLED()          LL_APB1_IsEnabledClock(LL_APB1_PERIPH_ADCDIG)
#define __HAL_RCC_ADCANA_IS_CLK_ENABLED()          LL_APB1_IsEnabledClock(LL_APB1_PERIPH_ADCANA)
#define __HAL_RCC_LPUART_IS_CLK_ENABLED()          LL_APB1_IsEnabledClock(LL_APB1_PERIPH_LPUART)
#define __HAL_RCC_USART_IS_CLK_ENABLED()           LL_APB1_IsEnabledClock(LL_APB1_PERIPH_USART)
#if defined(SPI2) 
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()            LL_APB1_IsEnabledClock(LL_APB1_PERIPH_SPI2)
#endif
#if defined(SPI3) 
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()            LL_APB1_IsEnabledClock(LL_APB1_PERIPH_SPI3)
#endif
#if defined(I2C1) 
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()            LL_APB1_IsEnabledClock(LL_APB1_PERIPH_I2C1)
#endif
#if defined(I2C2) 
#define __HAL_RCC_I2C2_IS_CLK_ENABLED()            LL_APB1_IsEnabledClock(LL_APB1_PERIPH_I2C2)
#endif

#if defined(SPI1) 
#define __HAL_RCC_SPI1_IS_CLK_DISABLED()           !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_SPI1))
#endif
#define __HAL_RCC_ADCDIG_IS_CLK_DISABLED()         !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_ADCDIG))
#define __HAL_RCC_ADCANA_IS_CLK_DISABLED()         !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_ADCANA))
#define __HAL_RCC_LPUART_IS_CLK_DISABLED()         !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_LPUART))
#define __HAL_RCC_USART_IS_CLK_DISABLED()          !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_USART))
#if defined(SPI2)
#define __HAL_RCC_SPI2_IS_CLK_DISABLED()           !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_SPI2))
#endif
#if defined(SPI3)
#define __HAL_RCC_SPI3_IS_CLK_DISABLED()           !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_SPI3))
#endif
#if defined(I2C1)
#define __HAL_RCC_I2C1_IS_CLK_DISABLED()           !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_I2C1))
#endif
#if defined(I2C2)
#define __HAL_RCC_I2C2_IS_CLK_DISABLED()           !(LL_APB1_IsEnabledClock(LL_APB1_PERIPH_I2C2))
#endif

/**
  * @}
  */


/** @defgroup RCC_APB2_Clock_Enable_Disable_Status APB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(BLUE)
#define __HAL_RCC_MRBLE_IS_CLK_ENABLED()            LL_APB2_IsEnabledClock(LL_APB2_PERIPH_MRBLE)

#define __HAL_RCC_MRBLE_IS_CLK_DISABLED()           !(LL_APB2_IsEnabledClock(LL_APB2_PERIPH_MRBLE))
#endif

/**
  * @}
  */



/** @defgroup RCC_AHB_Force_Release_Reset AHB Peripheral Force Release Reset
  * @brief  Force or release AHB peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB_FORCE_RESET()             LL_AHB_ForceReset(LL_AHB_PERIPH_ALL)
#define __HAL_RCC_DMA_FORCE_RESET()             LL_AHB_ForceReset(LL_AHB_PERIPH_DMA)
#define __HAL_RCC_GPIOA_FORCE_RESET()           LL_AHB_ForceReset(LL_AHB_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_FORCE_RESET()           LL_AHB_ForceReset(LL_AHB_PERIPH_GPIOB)
#define __HAL_RCC_CRC_FORCE_RESET()             LL_AHB_ForceReset(LL_AHB_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_FORCE_RESET()             LL_AHB_ForceReset(LL_AHB_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_FORCE_RESET()             LL_AHB_ForceReset(LL_AHB_PERIPH_RNG)
#if defined(AES1)
#define __HAL_RCC_AES1_FORCE_RESET()            LL_AHB_ForceReset(LL_AHB_PERIPH_AES1)
#endif
  
#define __HAL_RCC_AHB_RELEASE_RESET()           LL_AHB_ReleaseReset(LL_AHB_PERIPH_ALL)
#define __HAL_RCC_DMA_RELEASE_RESET()           LL_AHB_ReleaseReset(LL_AHB_PERIPH_DMA)
#define __HAL_RCC_GPIOA_RELEASE_RESET()         LL_AHB_ReleaseReset(LL_AHB_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_RELEASE_RESET()         LL_AHB_ReleaseReset(LL_AHB_PERIPH_GPIOB)
#define __HAL_RCC_CRC_RELEASE_RESET()           LL_AHB_ReleaseReset(LL_AHB_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_RELEASE_RESET()           LL_AHB_ReleaseReset(LL_AHB_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_RELEASE_RESET()           LL_AHB_ReleaseReset(LL_AHB_PERIPH_RNG)
#if defined(AES1)
#define __HAL_RCC_AES1_RELEASE_RESET()          LL_AHB_ReleaseReset(LL_AHB_PERIPH_AES1)
#endif

/**
  * @}
  */

/** @defgroup RCC_APB0_Force_Release_Reset APB0 Peripheral Force Release Reset
  * @brief  Force or release APB0 peripheral reset.
  * @{
  */

#define __HAL_RCC_APB0_FORCE_RESET()            LL_APB0_ForceReset(LL_APB0_PERIPH_ALL)
#if defined(TIM1) 
#define __HAL_RCC_TIM1_FORCE_RESET()            LL_APB0_ForceReset(LL_APB0_PERIPH_TIM1)
#endif
#if defined(TIM2) 
#define __HAL_RCC_TIM2_FORCE_RESET()            LL_APB0_ForceReset(LL_APB0_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_FORCE_RESET()          LL_APB0_ForceReset(LL_APB0_PERIPH_SYSCFG)
#if defined(LCD)
#define __HAL_RCC_LCDC_FORCE_RESET()            LL_APB0_ForceReset(LL_APB0_PERIPH_LCDC)
#endif
#if defined(COMP1)
#define __HAL_RCC_COMP_FORCE_RESET()            LL_APB0_ForceReset(LL_APB0_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_FORCE_RESET()             LL_APB0_ForceReset(LL_APB0_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_FORCE_RESET()             LL_APB0_ForceReset(LL_APB0_PERIPH_RTC)
#if defined(SCI)
#define __HAL_RCC_SCI_FORCE_RESET()             LL_APB0_ForceReset(LL_APB0_PERIPH_SCI)
#endif
#define __HAL_RCC_WDG_FORCE_RESET()             LL_APB0_ForceReset(LL_APB0_PERIPH_WDG)
#if defined(TIM16) 
#define __HAL_RCC_TIM16_FORCE_RESET()           LL_APB0_ForceReset(LL_APB0_PERIPH_TIM16)
#endif
#if defined(TIM17) 
#define __HAL_RCC_TIM17_FORCE_RESET()           LL_APB0_ForceReset(LL_APB0_PERIPH_TIM17)
#endif

#define __HAL_RCC_APB0_RELEASE_RESET()          LL_APB0_ReleaseReset(LL_APB0_PERIPH_ALL)
#if defined(TIM1) 
#define __HAL_RCC_TIM1_RELEASE_RESET()          LL_APB0_ReleaseReset(LL_APB0_PERIPH_TIM1)
#endif
#if defined(TIM2) 
#define __HAL_RCC_TIM2_RELEASE_RESET()          LL_APB0_ReleaseReset(LL_APB0_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_RELEASE_RESET()        LL_APB0_ReleaseReset(LL_APB0_PERIPH_SYSCFG)
#if defined(LCD)
#define __HAL_RCC_LCDC_RELEASE_RESET()          LL_APB0_ReleaseReset(LL_APB0_PERIPH_LCDC)
#endif
#if defined(COMP1)
#define __HAL_RCC_COMP_RELEASE_RESET()          LL_APB0_ReleaseReset(LL_APB0_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_RELEASE_RESET()           LL_APB0_ReleaseReset(LL_APB0_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_RELEASE_RESET()           LL_APB0_ReleaseReset(LL_APB0_PERIPH_RTC)
#if defined(SCI)
#define __HAL_RCC_SCI_RELEASE_RESET()           LL_APB0_ReleaseReset(LL_APB0_PERIPH_SCI)
#endif
#define __HAL_RCC_WDG_RELEASE_RESET()           LL_APB0_ReleaseReset(LL_APB0_PERIPH_WDG)
#if defined(TIM16) 
#define __HAL_RCC_TIM16_RELEASE_RESET()         LL_APB0_ReleaseReset(LL_APB0_PERIPH_TIM16)
#endif
#if defined(TIM17) 
#define __HAL_RCC_TIM17_RELEASE_RESET()         LL_APB0_ReleaseReset(LL_APB0_PERIPH_TIM17)
#endif
/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset APB1 Peripheral Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{
  */

#define __HAL_RCC_APB1_FORCE_RESET()            LL_APB1_ForceReset(LL_APB1_PERIPH_ALL)
#if defined(SPI1) 
#define __HAL_RCC_SPI1_FORCE_RESET()            LL_APB1_ForceReset(LL_APB1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADCDIG_FORCE_RESET()          LL_APB1_ForceReset(LL_APB1_PERIPH_ADCDIG)
#define __HAL_RCC_ADCANA_FORCE_RESET()          LL_APB1_ForceReset(LL_APB1_PERIPH_ADCANA)
#define __HAL_RCC_LPUART_FORCE_RESET()          LL_APB1_ForceReset(LL_APB1_PERIPH_LPUART)
#define __HAL_RCC_USART_FORCE_RESET()           LL_APB1_ForceReset(LL_APB1_PERIPH_USART)
#if defined(SPI2) 
#define __HAL_RCC_SPI2_FORCE_RESET()            LL_APB1_ForceReset(LL_APB1_PERIPH_SPI2)
#endif
#if defined(SPI3) 
#define __HAL_RCC_SPI3_FORCE_RESET()            LL_APB1_ForceReset(LL_APB1_PERIPH_SPI3)
#endif
#if defined(I2C1) 
#define __HAL_RCC_I2C1_FORCE_RESET()            LL_APB1_ForceReset(LL_APB1_PERIPH_I2C1)
#endif
#if defined(I2C2) 
#define __HAL_RCC_I2C2_FORCE_RESET()            LL_APB1_ForceReset(LL_APB1_PERIPH_I2C2)
#endif

#define __HAL_RCC_APB1_RELEASE_RESET()          LL_APB1_ReleaseReset(LL_APB1_PERIPH_ALL)
#if defined(SPI1) 
#define __HAL_RCC_SPI1_RELEASE_RESET()          LL_APB1_ReleaseReset(LL_APB1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADCDIG_RELEASE_RESET()        LL_APB1_ReleaseReset(LL_APB1_PERIPH_ADCDIG)
#define __HAL_RCC_ADCANA_RELEASE_RESET()        LL_APB1_ReleaseReset(LL_APB1_PERIPH_ADCANA)
#define __HAL_RCC_LPUART_RELEASE_RESET()        LL_APB1_ReleaseReset(LL_APB1_PERIPH_LPUART)
#define __HAL_RCC_USART_RELEASE_RESET()         LL_APB1_ReleaseReset(LL_APB1_PERIPH_USART)
#if defined(SPI2) 
#define __HAL_RCC_SPI2_RELEASE_RESET()          LL_APB1_ReleaseReset(LL_APB1_PERIPH_SPI2)
#endif
#if defined(SPI3) 
#define __HAL_RCC_SPI3_RELEASE_RESET()          LL_APB1_ReleaseReset(LL_APB1_PERIPH_SPI3)
#endif
#if defined(I2C1) 
#define __HAL_RCC_I2C1_RELEASE_RESET()          LL_APB1_ReleaseReset(LL_APB1_PERIPH_I2C1)
#endif
#if defined(I2C2) 
#define __HAL_RCC_I2C2_RELEASE_RESET()          LL_APB1_ReleaseReset(LL_APB1_PERIPH_I2C2)
#endif

/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset APB2 Peripheral Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB2_FORCE_RESET()             LL_APB2_ForceReset(LL_APB2_PERIPH_ALL)
#if defined(BLUE)
#define __HAL_RCC_MRBLE_FORCE_RESET()            LL_APB2_ForceReset(LL_APB2_PERIPH_MRBLE)
#endif

#define __HAL_RCC_APB2_RELEASE_RESET()           LL_APB2_ReleaseReset(LL_APB2_PERIPH_ALL)
#if defined(BLUE)
#define __HAL_RCC_MRBLE_RELEASE_RESET()          LL_APB2_ReleaseReset(LL_APB2_PERIPH_MRBLE)
#endif
/**
  * @}
  */


/** @brief  Macro to adjust the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between Min_data=0 and Max_Data=127.
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__)  LL_RCC_HSI_SetCalibTrimming(__HSICALIBRATIONVALUE__)


/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI1 oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI_ENABLE()         LL_RCC_LSI_Enable()
#define __HAL_RCC_LSI_DISABLE()        LL_RCC_LSI_Disable()

/** @brief  Macro to adjust the Internal Low Speed oscillator (LSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __LSITRIMMINGVALUE__ specifies the calibration trimming value
  *         This parameter must be a number between Min_data=0 and Max_Data=15.
  * @retval None
  */
#define __HAL_RCC_LSI_CALIBRATIONVALUE_ADJUST(__LSITRIMMINGVALUE__)  LL_RCC_LSI_SetTrimming(__LSITRIMMINGVALUE__)

/** 
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this macro. User should request a transition to HSE Off
  *         first and then HSE On or HSE Bypass.
  * @note   After enabling the HSE (RCC_HSE_ON), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the RC64MPLL.
  * @note   HSE state can not be changed if it is used directly or through the
  *         RC64MPLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering DEEPSTOP and SHUTDOWN modes.
  * @param  __STATE__  specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_OFF  Turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON  Turn ON the HSE oscillator.
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)                      \
                    do {                                     \
                      if((__STATE__) == RCC_HSE_ON)          \
                      {                                      \
                       LL_RCC_HSE_Enable();                  \
                      }                                      \
                      else                                   \
                      {                                      \
                        LL_RCC_HSE_Disable();                \
                      }                                      \
                    } while(0U)

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this macro. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_BYPASS), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  __STATE__  specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF  Turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON  Turn ON the LSE oscillator.
  *            @arg @ref RCC_LSE_BYPASS  LSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__)                        \
                    do {                                       \
                      if((__STATE__) == RCC_LSE_ON)            \
                      {                                        \
                        LL_RCC_LSE_Enable();                   \
                      }                                        \
                      else if((__STATE__) == RCC_LSE_BYPASS)   \
                      {                                        \
                        LL_RCC_LSE_EnableBypass();             \
                        LL_RCC_LSE_Enable();                   \
                      }                                        \
                      else                                     \
                      {                                        \
                        LL_RCC_LSE_Disable();                  \
                        LL_RCC_LSE_DisableBypass();            \
                      }                                        \
                    } while(0U)

#if defined(RCC_RFSWHSECR_SATRG)
/** @brief  Macros to configure HSE sense amplifier threshold.
  * @note   to configure HSE sense amplifier, first disable HSE
  *         using @ref __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF) macro.
  *
  * @param  __HSE_AMPTHRES__  specifies the HSE sense amplifier threshold.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSEAMPTHRESHOLD_1_2  HSE bias current factor 1/2.
  *            @arg @ref RCC_HSEAMPTHRESHOLD_3_4  HSE bias current factor 3/4.
  * @retval None
  */
#define __HAL_RCC_HSE_AMPCONFIG(__HSE_AMPTHRES__)  LL_RCC_HSE_SetSenseAmplifier(__HSE_AMPTHRES__)
#endif
  
/** @brief  Macros to configure HSE current control.
  * @note   to configure HSE current control, first disable HSE
  *         using @ref __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF) macro.
  *
  * @param  __HSE_CURRENTMAX__  specifies the HSE current max limit.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_CURRENTMAX_0  HSE current max limit 0.18 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_1  HSE current max limit 0.57 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_2  HSE current max limit 0.78 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_3  HSE current max limit 1.13 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_4  HSE current max limit 0.61 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_5  HSE current max limit 1.65 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_6  HSE current max limit 2.12 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_7  HSE current max limit 2.84 mA/V.
  * @retval None
  */
#define __HAL_RCC_HSE_CURRENTCONFIG(__HSE_CURRENTMAX__)  LL_RCC_HSE_SetCurrentControl(__HSE_CURRENTMAX__)

/** @brief  Macros to configure HSE capacitor tuning.
  * @note   to configure HSE current control, first disable HSE
  *         using __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF) macro.
  *
  * @param  __HSE_LOAD_CAPACITANCE__  specifies the HSE capacitor value.
  *         This Value Between Min_Data = 0 and Max_Data = 63
  * @retval None
  */
#define __HAL_RCC_HSE_CAPACITORTUNING(__HSE_LOAD_CAPACITANCE__)  LL_RCC_HSE_SetCapacitorTuning(__HSE_LOAD_CAPACITANCE__)


/** @brief  Macros to enable or disable the main RC64MPLL.
  * @note   After enabling the main RC64MPLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main RC64MPLL can not be disabled if it is used as system clock source
  * @note   The main RC64MPLL is disabled by hardware when entering DEEPSTOP and SHUTDOWN modes.
  * @retval None
  */
#define __HAL_RCC_RC64MPLL_ENABLE()         LL_RCC_RC64MPLL_Enable()
#define __HAL_RCC_RC64MPLL_DISABLE()        LL_RCC_RC64MPLL_Disable()

/** @brief  Macro to configure the RC64MPLL multiplication factor.
  * @note   This function must be used only when the main RC64MPLL is disabled.
  * @param  __PLLM__  specifies the division factor 
  *         This parameter must be a value of RCC_RC64MPLL_Clock_Divider.
  * @retval None
  *
  */
#define __HAL_RCC_RC64MPLL_PRESC_CONFIG(__PLLM__) LL_RCC_SetRC64MPLLPrescaler(__PLLM__)

/** @brief  Macro to configure the RF clock source.
  * @param  __SOURCE__  specifies the RF BLE clock source  
  *         This parameter must be a value of RCC_RF_RC64MPLL_Clock_Divider.
  * @retval None
  *
  */
#define __HAL_RCC_RF_RC64MPLL_SET_CONFIG(__SOURCE__) LL_RCC_SetRFClockSource(__SOURCE__)
  
/** @brief  Macro to get the RF BLE clock source.
  * @retval The RF BLE clock source. The returned value can be one of the
  *         following values:
  *              @arg @ref RCC_RF_RC64MPLL_DIV2
  *              @arg @ref RCC_RF_RC64MPLL_DIV4
  *
  */
#define __HAL_RCC_RF_RC64MPLL_GET_CONFIG() LL_RCC_GetRFClockSource()
  
/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__  specifies the system clock source.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_SYSCLKSOURCE_HSI HSI oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_HSE HSE oscillator is used as system clock source.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__)  LL_RCC_SetSysClkSource(__SYSCLKSOURCE__)

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              @arg @ref RCC_SYSCLKSOURCE_HSI HSI used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_HSE HSE used as system clock.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE()  LL_RCC_GetSysClkSource()

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @param  __LSEDRIVE__  specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW  LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW  LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH  LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH  LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__)  LL_RCC_LSE_SetDriveCapability(__LSEDRIVE__)

/** 
  * @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCOSOURCE_NOCLOCK          MCO output disabled
  *            @arg @ref RCC_MCOSOURCE_SYSCLK           System  clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSI              HSI clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSE              HSE clock selected as MCO sourcee
  *            @arg @ref RCC_MCOSOURCE_RC64MPLL         Main PLL clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSI64M_DIV2048   HSI div 2048 clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_SMPS             SMPS clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_ADC              ADC clock selected as MCO source

  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1   MCO clock source is divided by 1
  *            @arg @ref RCC_MCODIV_2   MCO clock source is divided by 2
  *            @arg @ref RCC_MCODIV_4   MCO clock source is divided by 4
  *            @arg @ref RCC_MCODIV_8   MCO clock source is divided by 8
  *            @arg @ref RCC_MCODIV_16  MCO clock source is divided by 16
  *            @arg @ref RCC_MCODIV_32  MCO clock source is divided by 32

  */
#define __HAL_RCC_MCO_CONFIG(__MCOCLKSOURCE__, __MCODIV__)  LL_RCC_ConfigMCO((__MCOCLKSOURCE__), (__MCODIV__))

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/** @brief  Enable RCC interrupt.
  * @param  __INTERRUPT__  specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY      LSI ready interrupt enable
  *            @arg @ref RCC_IT_LSERDY      LSE ready interrupt enable
  *            @arg @ref RCC_IT_HSIRDY      HSI ready interrupt enable
  *            @arg @ref RCC_IT_HSERDY      HSE ready interrupt enable
  *            @arg @ref RCC_IT_PLLRDY      Main PLL ready interrupt enable
  *            @arg @ref RCC_IT_RTCRSTRELRDY RTC Reset Release ready interrupt enable
  *            @arg @ref RCC_IT_WDGRSTRELRDY WDG Reset Release ready interrupt enable
  *            @arg @ref RCC_IT_LPURSTRELRDY LPU Reset Release ready interrupt enable
  *            @arg @ref RCC_IT_LCDRSTRELRDY LCD Reset Release ready interrupt enable
  *            @arg @ref RCC_IT_SCIRSTRELRDY SCI Reset Release ready interrupt enable
  * @retval None
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt.
  * @param  __INTERRUPT__  specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY      LSI ready interrupt disable
  *            @arg @ref RCC_IT_LSERDY      LSE ready interrupt disable
  *            @arg @ref RCC_IT_HSIRDY      HSI ready interrupt disable
  *            @arg @ref RCC_IT_HSERDY      HSE ready interrupt disable
  *            @arg @ref RCC_IT_PLLRDY      Main PLL ready interrupt disable
  *            @arg @ref RCC_IT_RTCRSTRELRDY RTC Reset Release ready interrupt disable
  *            @arg @ref RCC_IT_WDGRSTRELRDY WDG Reset Release ready interrupt disable
  *            @arg @ref RCC_IT_LPURSTRELRDY LPU Reset Release ready interrupt disable
  *            @arg @ref RCC_IT_LCDRSTRELRDY LCD Reset Release ready interrupt disable
  *            @arg @ref RCC_IT_SCIRSTRELRDY SCI Reset Release ready interrupt disable
  * @retval None
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear RCC interrupt pending bits (Perform Byte access to RCC_CICR[17:0]
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__  specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt clear
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt clear
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt clear
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt clear
  *            @arg @ref RCC_IT_PLLRDY   Main PLL ready interrupt clear
  *            @arg @ref RCC_IT_RTCRSTRELRDY RTC Reset Release ready interrupt clear
  *            @arg @ref RCC_IT_WDGRSTRELRDY WDG Reset Release ready interrupt clear
  *            @arg @ref RCC_IT_LPURSTRELRDY LPU Reset Release ready interrupt clear
  *            @arg @ref RCC_IT_LCDRSTRELRDY LCD Reset Release ready interrupt clear
  *            @arg @ref RCC_IT_SCIRSTRELRDY SCI Reset Release ready interrupt clear
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->CIFR = (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__  specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt flag
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt flag
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt flag
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt flag
  *            @arg @ref RCC_IT_PLLRDY   Main PLL ready interrupt flag
  *            @arg @ref RCC_IT_RTCRSTRELRDY RTC Reset Release ready interrupt flag
  *            @arg @ref RCC_IT_WDGRSTRELRDY WDG Reset Release ready interrupt flag
  *            @arg @ref RCC_IT_LPURSTRELRDY LPU Reset Release ready interrupt flag
  *            @arg @ref RCC_IT_LCDRSTRELRDY LCD Reset Release ready interrupt flag
  *            @arg @ref RCC_IT_SCIRSTRELRDY SCI Reset Release ready interrupt flag
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: RCC_FLAG_LOCKUPRST, RCC_FLAG_WDGRST, RCC_FLAG_SFTRST, 
  *                             RCC_FLAG_PORRST and RCC_FLAG_PADRSTF.
  * @retval None
 */
#define __HAL_RCC_CLEAR_RESET_FLAGS() LL_RCC_ClearResetFlags()

/** @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__  specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_HSIRDY      HSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSERDY      HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_PLLRDY      Main PLL clock ready
  *            @arg @ref RCC_FLAG_LSIRDY      LSI oscillator clock ready
  *            @arg @ref RCC_FLAG_LSERDY      LSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LOCKUPRST   CPU lockup reset flag
  *            @arg @ref RCC_FLAG_WDGRST      Watchdog reset flag
  *            @arg @ref RCC_FLAG_SFTRST      Software reset flag
  *            @arg @ref RCC_FLAG_PORRST      Power-On or BOR reset flag
  *            @arg @ref RCC_FLAG_PADRSTF      NRSTn pad reset flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) (((__FLAG__) & 0x1F) ? ((RCC->CR & (__FLAG__)) == (__FLAG__)) : ((RCC->CSR & (__FLAG__)) == (__FLAG__)))
                                     

/**
  * @}
  */

/**
  * @}
  */

/* Include RCC HAL Extended module */
#include "rf_driver_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions
  * @{
  */


/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
uint32_t          HAL_RCC_GetSysClockFreq(void);

void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_HAL_RCC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

