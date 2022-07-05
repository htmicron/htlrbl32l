/**
  ******************************************************************************
  * @file    rf_driver_hal_rcc_ex.h
  * @author  RF Application Team
  * @brief   Header file of RCC HAL Extended module.
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
#ifndef RF_DRIVER_HAL_RCC_EX_H
#define RF_DRIVER_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"
#include "rf_driver_ll_exti.h"
#include "rf_driver_ll_pwr.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Macros
  * @{
  */

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_NOCLOCK)        || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSI)            || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))
  
#define IS_RCC_LSCO(__LSCOX__) ( ((__LSCOX__) == RCC_LSCO1) || ((__LSCOX__) == RCC_LSCO2) || ((__LSCOX__) == RCC_LSCO3) )
  
#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_RF)   == RCC_PERIPHCLK_RF)       || \
                (((__SELECTION__) & RCC_PERIPHCLK_SPI2_I2S) == RCC_PERIPHCLK_SPI2_I2S)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_SPI3_I2S) == RCC_PERIPHCLK_SPI3_I2S))

#define IS_RCC_RF_BLE_CLOCK_SOURCE(__SOURCE__) \
                ((((__SOURCE__) & RCC_RF_RC64MPLL_DIV2) == RCC_RF_RC64MPLL_DIV2) || \
                 (((__SOURCE__) & RCC_RF_RC64MPLL_DIV4) == RCC_RF_RC64MPLL_DIV4))
  
#define IS_RCC_SMPS_CLOCK_SOURCE(__SOURCE__) \
                ((((__SOURCE__) & RCC_SMPSCLKSOURCE_RC64MPLL) == RCC_SMPSCLKSOURCE_RC64MPLL))

#define IS_RCC_SMPS_CLOCK_PRESC(__PRESC__) \
                ((((__PRESC__) & RCC_SMPSCLK_DIV2) == RCC_SMPSCLK_DIV2) || \
                 (((__PRESC__) & RCC_SMPSCLK_DIV4) == RCC_SMPSCLK_DIV4))

#if defined(SPI2) 
#define IS_RCC_SPI2I2S_CLOCK_SOURCE(__SOURCE__) \
                ((((__SOURCE__) & RCC_SPI2I2S_CLKSOURCE_16M) == RCC_SPI2I2S_CLKSOURCE_16M) || \
                 (((__SOURCE__) & RCC_SPI2I2S_CLKSOURCE_32M) == RCC_SPI2I2S_CLKSOURCE_32M))
#endif 

#if defined(SPI3) 
#define IS_RCC_SPI3I2S_CLOCK_SOURCE(__SOURCE__) \
                ((((__SOURCE__) & RCC_SPI3I2S_CLKSOURCE_16M) == RCC_SPI3I2S_CLKSOURCE_16M) || \
                 (((__SOURCE__) & RCC_SPI3I2S_CLKSOURCE_32M) == RCC_SPI3I2S_CLKSOURCE_32M))

#endif
#define IS_RCC_TRIMOSC(__OSC_TYPE__)  ((((__OSC_TYPE__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */

/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t PeriphClockSelection;    /*!< The Extended Clock to be configured.
                                         This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

#if defined(SPI2) 
  uint32_t SPI2I2SClockSelection;   /*!< Specifies SPI2_I2S clock source.
                                         This parameter can be a value of @ref RCCEx_SPI2_I2S_Clock_Source */
#endif
#if defined(SPI3) 
  uint32_t SPI3I2SClockSelection;   /*!< Specifies SPI3_I2S clock source.
                                         This parameter can be a value of @ref RCCEx_SPI3_I2S_Clock_Source */
#endif
  
  uint32_t RFClockSelection;        /*!< RADIO IP does not use directly the system clock for its APB / AHB 
                                         interfaces but the system clock with a potential divider (2 or 4).
                                         This parameter can be a value of @ref RCC_RF_RC64MPLL_Clock_Divider
                                         The supported configurations are:
                                         - CLK_SYS = 1 MHz / 2 MHz / 4 MHz / 8 MHz --> Not possible to use RADIO IP
                                         - CLK_SYS = 64 MHz / 32 MHz / 16 MHz --> Allow the use of the RADIO IP.
					 The only constraint is that the CLK_SYS shall be bigger or equal than RADIO IP clk */

  uint32_t SmpsDivSelection;        /*!< Specifies SMPS clock prescaling factor.
                                         This parameter can be a value of @ref RCCEx_SMPS_Clock_Divider */

} RCC_PeriphCLKInitTypeDef;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCC_LSCO_Index LSCO Index
  * @{
  */
#define RCC_LSCO1                       0x00000000U          /*!< LSCO1 index */
#define RCC_LSCO2                       0x00000001U          /*!< LSCO2 index */
#define RCC_LSCO3                       0x00000002U          /*!< LSCO3 index */

/**
  * @}
  */

/** @defgroup RCC_LSCO_Clock_Source LSCO Clock Source
  * @{
  */
#define RCC_LSCOSOURCE_NOCLOCK         LL_RCC_LSCOSOURCE_NOCLOCK          /*!< LSCO output disabled, no clock on LSCO */
#define RCC_LSCOSOURCE_LSI             LL_RCC_LSCOSOURCE_LSI              /*!< LSI selection as LSCO source */
#define RCC_LSCOSOURCE_LSE             LL_RCC_LSCOSOURCE_LSE              /*!< LSE selection as LSCO source */
/**
  * @}
  */


/** @defgroup RCCEx_Periph_Clock_Selection Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_RF                0x00000001U                    /*!< RADIO IP  Peripheral Clock Selection */
#define RCC_PERIPHCLK_SMPS              0x00000002U                    /*!< SMPS Peripheral Clock Selection      */
#if defined(SPI2)  
#define RCC_PERIPHCLK_SPI2_I2S          0x00000004U                    /*!< SPI2 I2S Peripheral Clock Selection  */
#endif 
#if defined(SPI3) 
#define RCC_PERIPHCLK_SPI3_I2S          0x00000008U                    /*!< SPI3 I2S Peripheral Clock Selection  */
#endif
/**
  * @}
  */

#if defined(SPI2)  
/** @defgroup RCCEx_SPI2_I2S_Clock_Source SPI2_I2S Clock Source
  * @{
  */
#define RCC_SPI2I2S_CLKSOURCE_16M    LL_RCC_SPI2_I2S_CLK16M  /*!< SPI2 I2S 16 MHz clock source selection */
#define RCC_SPI2I2S_CLKSOURCE_32M    LL_RCC_SPI2_I2S_CLK32M  /*!< SPI2 I2S 32 MHz clock source selection */
/**
  * @}
  */
#endif 

#if defined(SPI3) 
/** @defgroup RCCEx_SPI3_I2S_Clock_Source SPI3_I2S Clock Source
  * @{
  */
#define RCC_SPI3I2S_CLKSOURCE_16M    LL_RCC_SPI3_I2S_CLK16M  /*!< SPI3 I2S 16 MHz clock source selection */
#define RCC_SPI3I2S_CLKSOURCE_32M    LL_RCC_SPI3_I2S_CLK32M  /*!< SPI3 I2S 32 MHz clock source selection */
/**
  * @}
  */
#endif


/** @defgroup RCCEx_SMPS_Clock_Divider SMPS clock prescaling factor
  * @{
  */
#define RCC_SMPSCLK_DIV2   LL_RCC_SMPS_DIV_2   /*!< SMPS clock division 2 (SMPS clock is 8 MHz if ANADIV = 1)*/
#define RCC_SMPSCLK_DIV4   LL_RCC_SMPS_DIV_4   /*!< SMPS clock division 4 (SMPS clock is 4 MHz if ANADIV = 1)*/
/**
  * @}
  */
  
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
 * @{
 */

/** 
  * @brief  Macro to configure the LSCO clock.
  * @param  __LSCOCLKSOURCE__ specifies the LSCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSCOSOURCE_NOCLOCK          LSCO output disabled
  *            @arg @ref RCC_LSCOSOURCE_LSI_LPMU         Internal LPMU slow clock source as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSI              LSI clock selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSE              LSE clock selected as LSCO sourcee
  */
#define __HAL_RCC_LSCO_CONFIG(__LSCOCLKSOURCE__)  LL_RCC_ConfigLSCO((__LSCOCLKSOURCE__))

/** @brief  Macro to configure the SMPS clock prescaling factor.
  *
  * @param  __SMPSCLKDIV__ specifies the division factor for SMPS clock.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_SMPSCLK_DIV2           SMPS clock division 2 (SMPS clock is 8 MHz if ANADIV = 1)
  *            @arg @ref RCC_SMPSCLK_DIV4           SMPS clock division 4 (SMPS clock is 4 MHz if ANADIV = 1)
  *
  * @retval None
  */
#define __HAL_RCC_SMPS_DIV_CONFIG(__SMPSCLKDIV__) LL_RCC_SetSMPSPrescaler(__SMPSCLKDIV__)

/** @brief  Macro to get the SMPS clock prescaling factor.
  *
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_SMPSCLK_DIV2           SMPS clock division 2 (SMPS clock is 8 MHz if ANADIV = 1)
  *            @arg @ref RCC_SMPSCLK_DIV4           SMPS clock division 4 (SMPS clock is 4 MHz if ANADIV = 1)
  *
  */
#define __HAL_RCC_GET_SMPS_DIV() LL_RCC_GetSMPSPrescaler()

/** @brief  Macro to configure the SMPS ADC ANA clock DIV prescaler.
  * @param  __SMPS_ADC_ANA_DIV__ specifies the SMPS ADC ANA div prescaler.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_SMPS_ADC_ANADIV1     SMPS and ADC clock division 1 (ADC/SMPS source clock is 32 MHz)
  *            @arg @ref RCC_SMPS_ADC_ANADIV2     SMPS and ADC clock division 2 (ADC/SMPS source clock is 16 MHz)
  *            @arg @ref RCC_SMPS_ADC_ANADIV4     SMPS and ADC clock division 4 (ADC/SMPS source clock is  8 MHz)
  *
  * @retval None
  */

#define __HAL_RCC_SMPS_ADC_ANA_DIV_CONFIG(__SMPS_ADC_ANA_DIV__) LL_RCC_SetSMPS_ANADIVPrescaler(__SMPS_ADC_ANA_DIV__)

/** @brief  Macro to get the SMPS ADC ANA clock DIV prescaler.
  * @retval SMPS ADC ANA div prescaler.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_SMPS_ADC_ANADIV1     SMPS and ADC clock division 1 (ADC/SMPS source clock is 32 MHz)
  *            @arg @ref RCC_SMPS_ADC_ANADIV2     SMPS and ADC clock division 2 (ADC/SMPS source clock is 16 MHz)
  *            @arg @ref RCC_SMPS_ADC_ANADIV4     SMPS and ADC clock division 4 (ADC/SMPS source clock is  8 MHz)
  */
#define __HAL_RCC_GET_SMPS_ADC_ANA_DIV_CONFIG() LL_RCC_GetSMPS_ANADIV_Prescaler()

#if defined(SPI2)  
/** @brief  Macro to configure the SPI2_I2S clock.
  *
  * @param  __SPI2I2S_CLKSOURCE__ specifies the SPI2I2S clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_SPI2I2S_CLKSOURCE_16M
  *            @arg @ref RCC_SPI2I2S_CLKSOURCE_32M
  * @retval None
  */
#define __HAL_RCC_SPI2I2S_CONFIG(__SPI2I2S_CLKSOURCE__) LL_RCC_SetSPI2I2SClockSource(__SPI2I2S_CLKSOURCE__)

/** @brief  Macro to get the SPI2_I2S clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_SPI2I2S_CLKSOURCE_16M
  *            @arg @ref RCC_SPI2I2S_CLKSOURCE_32M
  */
#define __HAL_RCC_GET_SPI2I2S_SOURCE() LL_RCC_GetSPI2I2SClockSource()
#endif

#if defined(SPI3) 
/** @brief  Macro to configure the SPI3_I2S clock.
  *
  * @param  __SPI3I2S_CLKSOURCE__ specifies the SPI3I2S clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_SPI3I2S_CLKSOURCE_16M
  *            @arg @ref RCC_SPI3I2S_CLKSOURCE_32M
  * @retval None
  */
#define __HAL_RCC_SPI3I2S_CONFIG(__SPI3I2S_CLKSOURCE__) LL_RCC_SetSPI3I2SClockSource(__SPI3I2S_CLKSOURCE__)

/** @brief  Macro to get the SPI3_I2S clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_SPI3I2S_CLKSOURCE_16M
  *            @arg @ref RCC_SPI3I2S_CLKSOURCE_32M
  */
#define __HAL_RCC_GET_SPI3I2S_SOURCE() LL_RCC_GetSPI3I2SClockSource()

/**
  * @}
  */
#endif

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

void              HAL_RCCEx_LSCOConfig(uint32_t RCC_LSCOx, uint32_t RCC_LSCOSource);
void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);

HAL_StatusTypeDef   HAL_RCCEx_TrimOsc(uint32_t OscillatorType);

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

#endif /* RF_DRIVER_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
