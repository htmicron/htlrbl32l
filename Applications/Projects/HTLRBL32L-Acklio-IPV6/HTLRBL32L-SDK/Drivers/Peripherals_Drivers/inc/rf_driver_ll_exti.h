/**
  ******************************************************************************
  * @file    rf_driver_ll_exti.h
  * @author  RF Application Team
  * @brief   Header file of EXTI LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RF_DRIVER_LL_EXTI_H
#define RF_DRIVER_LL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

/** @defgroup EXTI_LL EXTI
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup EXTI_LL_Private_Macros EXTI Private Macros
  * @{
  */
/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/
/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup EXTI_LL_ES_INIT EXTI Exported Init structure
  * @{
  */
typedef struct
{

  uint32_t Line;                 /*!< Specifies the EXTI lines to be enabled or disabled for Lines in range PA0 to PB15
                                      This paramete rcan be any combination of @ref EXTI_LL_EC_LINE */

  FunctionalState LineCommand;  /*!< Specifies the new state of the selected EXTI lines.
                                     This parameter can be set either to ENABLE or DISABLE */

  uint8_t Type;                 /*!< Specifies the type for the EXTI lines EDGE or LEVEL.
                                     This parameter can be a value of @ref EXTI_LL_EC_TYPE. */

  uint8_t Trigger;              /*!< Specifies the trigger signal active edge/level for the EXTI lines.
                                     This parameter can be a value of @ref EXTI_LL_EC_TRIGGER. */
} LL_EXTI_InitTypeDef;

/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Constants EXTI Exported Constants
  * @{
  */

/** @defgroup EXTI_LL_EC_LINE LINE
  * @{
  */
#define LL_EXTI_LINE_PA0        (uint32_t)(1U << 0U)    /*!< PA0  */
#define LL_EXTI_LINE_PA1        (uint32_t)(1U << 1U)    /*!< PA1  */
#define LL_EXTI_LINE_PA2        (uint32_t)(1U << 2U)    /*!< PA2  */
#define LL_EXTI_LINE_PA3        (uint32_t)(1U << 3U)    /*!< PA3  */
#define LL_EXTI_LINE_PA4        (uint32_t)(1U << 4U)    /*!< PA4  */
#define LL_EXTI_LINE_PA5        (uint32_t)(1U << 5U)    /*!< PA5  */
#define LL_EXTI_LINE_PA6        (uint32_t)(1U << 6U)    /*!< PA6  */
#define LL_EXTI_LINE_PA7        (uint32_t)(1U << 7U)    /*!< PA7  */
#define LL_EXTI_LINE_PA8        (uint32_t)(1U << 8U)    /*!< PA8  */
#define LL_EXTI_LINE_PA9        (uint32_t)(1U << 9U)    /*!< PA9  */
#define LL_EXTI_LINE_PA10       (uint32_t)(1U << 10U)   /*!< PA10 */
#define LL_EXTI_LINE_PA11       (uint32_t)(1U << 11U)   /*!< PA11 */
#define LL_EXTI_LINE_PA12       (uint32_t)(1U << 12U)   /*!< PA12 */
#define LL_EXTI_LINE_PA13       (uint32_t)(1U << 13U)   /*!< PA13 */
#define LL_EXTI_LINE_PA14       (uint32_t)(1U << 14U)   /*!< PA14 */
#define LL_EXTI_LINE_PA15       (uint32_t)(1U << 15U)   /*!< PA15 */
#define LL_EXTI_LINE_PB0        (uint32_t)(1U << 16U)   /*!< PB0  */
#define LL_EXTI_LINE_PB1        (uint32_t)(1U << 17U)   /*!< PB1  */
#define LL_EXTI_LINE_PB2        (uint32_t)(1U << 18U)   /*!< PB2  */
#define LL_EXTI_LINE_PB3        (uint32_t)(1U << 19U)   /*!< PB3  */
#define LL_EXTI_LINE_PB4        (uint32_t)(1U << 20U)   /*!< PB4  */
#define LL_EXTI_LINE_PB5        (uint32_t)(1U << 21U)   /*!< PB5  */
#define LL_EXTI_LINE_PB6        (uint32_t)(1U << 22U)   /*!< PB6  */
#define LL_EXTI_LINE_PB7        (uint32_t)(1U << 23U)   /*!< PB7  */
#define LL_EXTI_LINE_PB8        (uint32_t)(1U << 24U)   /*!< PB8  */
#define LL_EXTI_LINE_PB9        (uint32_t)(1U << 25U)   /*!< PB9  */
#define LL_EXTI_LINE_PB10       (uint32_t)(1U << 26U)   /*!< PB10 */
#define LL_EXTI_LINE_PB11       (uint32_t)(1U << 27U)   /*!< PB11 */
#define LL_EXTI_LINE_PB12       (uint32_t)(1U << 28U)   /*!< PB12 */
#define LL_EXTI_LINE_PB13       (uint32_t)(1U << 29U)   /*!< PB13 */
#define LL_EXTI_LINE_PB14       (uint32_t)(1U << 30U)   /*!< PB14 */
#define LL_EXTI_LINE_PB15       (uint32_t)(1U << 31U)   /*!< PB15 */
#define LL_EXTI_LINE_ALL        (uint32_t)(0xFFFFFFFFU) /*!< All the EXTI lines PA0...PB15 */

#if defined(USE_FULL_LL_DRIVER)
#define LL_EXTI_LINE_NONE              (0x00000000U)    /*!< None Extended line */
#endif /*USE_FULL_LL_DRIVER*/

/**
  * @}
  */

/** @defgroup EXTI_LL_EC_TYPE Type
  * @{
  */
#define LL_EXTI_TYPE_EDGE               ((uint8_t)0x00U) /*!<  Interrupt Type EDGE detection */
#define LL_EXTI_TYPE_LEVEL              ((uint8_t)0x01U) /*!<  Interrupt Type LEVEL detection */
/**
  * @}
  */

/** @defgroup EXTI_LL_EC_TRIGGER Edge Trigger
  * @{
  */
#define LL_EXTI_TRIGGER_NONE                 ((uint8_t)0x00U) /*!< Trigger None */
#define LL_EXTI_TRIGGER_RISING_EDGE          ((uint8_t)0x01U) /*!< Trigger Rising Edge */
#define LL_EXTI_TRIGGER_FALLING_EDGE         ((uint8_t)0x02U) /*!< Trigger Falling Edge */
#define LL_EXTI_TRIGGER_BOTH_EDGE            ((uint8_t)0x03U) /*!< Trigger Both Edge */
#define LL_EXTI_TRIGGER_LOW_LEVEL            ((uint8_t)0x04U) /*!< Trigger Low Level */
#define LL_EXTI_TRIGGER_HIGH_LEVEL           ((uint8_t)0x05U) /*!< Trigger High Level */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Macros EXTI Exported Macros
  * @{
  */

/** @defgroup EXTI_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SYSCFG register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_EXTI_WriteReg(__REG__, __VALUE__) WRITE_REG(SYSCFG->__REG__, (__VALUE__))

/**
  * @brief  Read a value in SYSCFG register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_EXTI_ReadReg(__REG__) READ_REG(SYSCFG->__REG__)
/**
  * @}
  */


/**
  * @}
  */



/* Exported functions --------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Functions EXTI Exported Functions
 * @{
 */
/** @defgroup EXTI_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable IO Interrupt for Lines in range PA0... PB15
  * @rmtoll IO_IER        LL_EXTI_EnableIT
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE void LL_EXTI_EnableIT(uint32_t ExtiLine)
{
  SET_BIT(SYSCFG->IO_IER, ExtiLine);
}

/**
  * @brief  Disable IO Interrupt for Lines in range PA0... PB15
  * @rmtoll IO_IER        LL_EXTI_DisableIT
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE void LL_EXTI_DisableIT(uint32_t ExtiLine)
{
  CLEAR_BIT(SYSCFG->IO_IER, ExtiLine);
}

/**
  * @brief  Indicate if IO Interrupt Mask is enabled
  * @rmtoll IO_IER        LL_EXTI_IsEnabledIT
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval State of bit (1 or 0).
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledIT(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_IER, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_TYPE_Management Level/Edge Management
  * @{
  */

/**
  * @brief  Set IO Interrupt Type for Lines in range PA0... PB15
  * @rmtoll IO_DTR        LL_EXTI_SetType
  * @param  Type This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_TYPE_EDGE
  *         @arg @ref LL_EXTI_TYPE_LEVEL
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE void LL_EXTI_SetType(uint8_t Type, uint32_t ExtiLine)
{
  if (Type == LL_EXTI_TYPE_EDGE) {
    CLEAR_BIT(SYSCFG->IO_DTR, ExtiLine);
  } else {
    SET_BIT(SYSCFG->IO_DTR, ExtiLine);
  }
}

/**
  * @brief  Get IO Interrupt Type for Lines in range PA0... PB15
  * @rmtoll IO_DTR        LL_EXTI_GetType
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval One of the following values:
  *         @arg @ref LL_EXTI_TYPE_EDGE
  *         @arg @ref LL_EXTI_TYPE_LEVEL
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE uint8_t LL_EXTI_GetType(uint32_t ExtiLine)
{
  if (READ_BIT(SYSCFG->IO_DTR, ExtiLine))
    return LL_EXTI_TYPE_LEVEL;

  return LL_EXTI_TYPE_EDGE;  
}

/**
  * @}
  */
  
/** @defgroup EXTI_LL_EF_Trigger_Management Trigger_Management
  * @{
  */

/**
  * @brief  Set IO Interrupt Trigger for Lines in range PA0... PB15
  * @rmtoll IO_IBER/IO_IEVR/IO_DTR        LL_EXTI_SetTrigger
  * @param  Trigger This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_TRIGGER_RISING_EDGE
  *         @arg @ref LL_EXTI_TRIGGER_FALLING_EDGE
  *         @arg @ref LL_EXTI_TRIGGER_BOTH_EDGE
  *         @arg @ref LL_EXTI_TRIGGER_LOW_LEVEL
  *         @arg @ref LL_EXTI_TRIGGER_HIGH_LEVEL
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE void LL_EXTI_SetTrigger(uint8_t Trigger, uint32_t ExtiLine)
{  
  if (Trigger == LL_EXTI_TRIGGER_BOTH_EDGE) {
    SET_BIT(SYSCFG->IO_IBER, ExtiLine);
    CLEAR_BIT(SYSCFG->IO_IEVR, ExtiLine);
    return;
  }
  if (Trigger == LL_EXTI_TRIGGER_RISING_EDGE) {
    CLEAR_BIT(SYSCFG->IO_IBER, ExtiLine);
    SET_BIT(SYSCFG->IO_IEVR, ExtiLine);
    return;
  }
  if (Trigger == LL_EXTI_TRIGGER_FALLING_EDGE) {
    CLEAR_BIT(SYSCFG->IO_IBER, ExtiLine);
    CLEAR_BIT(SYSCFG->IO_IEVR, ExtiLine);
    return;
  }
  if (Trigger == LL_EXTI_TRIGGER_LOW_LEVEL) {
    CLEAR_BIT(SYSCFG->IO_IBER, ExtiLine);
    CLEAR_BIT(SYSCFG->IO_IEVR, ExtiLine);
    return;
  }
  if (Trigger == LL_EXTI_TRIGGER_HIGH_LEVEL) {
    CLEAR_BIT(SYSCFG->IO_IBER, ExtiLine);
    SET_BIT(SYSCFG->IO_IEVR, ExtiLine);
  }  
}

/**
  * @brief  Get IO Interrupt Trigger for Lines in range PA0... PB15
  * @rmtoll IO_IBER/IO_IEVR/IO_DTR        LL_EXTI_GetTrigger
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval The return value can be one of the following values:
  *         @arg @ref LL_EXTI_TRIGGER_RISING_EDGE
  *         @arg @ref LL_EXTI_TRIGGER_FALLING_EDGE
  *         @arg @ref LL_EXTI_TRIGGER_BOTH_EDGE
  *         @arg @ref LL_EXTI_TRIGGER_LOW_LEVEL
  *         @arg @ref LL_EXTI_TRIGGER_HIGH_LEVEL
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE uint8_t LL_EXTI_GetTrigger(uint32_t ExtiLine)
{
  uint32_t level_setup, level_edge, both_edge;

  level_setup = READ_BIT(SYSCFG->IO_DTR, ExtiLine);
  level_edge = READ_BIT(SYSCFG->IO_IEVR, ExtiLine);
  both_edge = READ_BIT(SYSCFG->IO_IBER, ExtiLine);
    
  if (level_setup) {
    if (level_edge) {
      return LL_EXTI_TRIGGER_HIGH_LEVEL;
    } else {
      return LL_EXTI_TRIGGER_LOW_LEVEL;
    }
  } else {
    if (both_edge) {
      return LL_EXTI_TRIGGER_BOTH_EDGE;
    }
    if (level_edge) {
      return LL_EXTI_TRIGGER_RISING_EDGE;
    }
  }
  return LL_EXTI_TRIGGER_FALLING_EDGE;
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Flag_Management Flag_Management
  * @{
  */

/**
  * @brief Check if the ExtLine Interrupt is set or not for Lines in range PA0...PB15
  * @note  This bit is cleared by writing a 1 to the bit.
  * @rmtoll IO_ISCR                   LL_EXTI_IsInterruptPending
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval State of bit (1 or 0).
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE uint32_t LL_EXTI_IsInterruptPending(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_ISCR, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}


/**
  * @brief Clear the ExtLine Interrupt for Lines in range PA0...PB15
  * @rmtoll IO_ISCR                   LL_EXTI_ClearInterrupt
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0 
  *         @arg @ref LL_EXTI_LINE_PB1 
  *         @arg @ref LL_EXTI_LINE_PB2 
  *         @arg @ref LL_EXTI_LINE_PB3 
  *         @arg @ref LL_EXTI_LINE_PB4 
  *         @arg @ref LL_EXTI_LINE_PB5 
  *         @arg @ref LL_EXTI_LINE_PB6 
  *         @arg @ref LL_EXTI_LINE_PB7 
  *         @arg @ref LL_EXTI_LINE_PB8 
  *         @arg @ref LL_EXTI_LINE_PB9 
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for BLueNRG-LP 
  */
__STATIC_INLINE void LL_EXTI_ClearInterrupt(uint32_t ExtiLine)
{
  WRITE_REG(SYSCFG->IO_ISCR, ExtiLine);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup EXTI_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_EXTI_Init(LL_EXTI_InitTypeDef *EXTI_InitStruct);
ErrorStatus LL_EXTI_DeInit(void);
void LL_EXTI_StructInit(LL_EXTI_InitTypeDef *EXTI_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

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

#endif /* RF_DRIVER_LL_EXTI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
