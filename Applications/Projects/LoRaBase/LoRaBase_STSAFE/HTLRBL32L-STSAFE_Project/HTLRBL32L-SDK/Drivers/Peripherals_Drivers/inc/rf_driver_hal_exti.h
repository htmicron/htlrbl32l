/**
  ******************************************************************************
  * @file    rf_driver_hal_exti.h
  * @author  RF Application Team
  * @brief   Header file of EXTI HAL module.
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
#ifndef RF_DRIVER_HAL_EXTI_H
#define RF_DRIVER_HAL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @brief EXTI HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup EXTI_Exported_Types EXTI Exported Types
  * @{
  */
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U,
} EXTI_CallbackIDTypeDef;


/**
  * @brief  EXTI Handle structure definition
  */
typedef struct
{
  uint32_t Line;                             /*!<  Exti line number */
  void (* PendingCallback)(uint32_t Line);   /*!<  Exti pending callback */
} EXTI_HandleTypeDef;

/**
  * @brief  EXTI Configuration structure definition
  */
typedef struct
{
  uint32_t Line;      /*!< The Exti line to be configured. This parameter
                           can be a value of @ref EXTI_Line */
  uint32_t Type;      /*!< The Exti Type to be configured.
                           This parameter can be a combination of @ref EXTI_Type */
  uint32_t Trigger;   /*!< The Exti Trigger to be configured. This parameter
                           can be a value of @ref EXTI_Trigger */
} EXTI_ConfigTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI Exported Constants
  * @{
  */

/** @defgroup EXTI_Line  EXTI Line
  * @{
  */
#define EXTI_LINE_PA0                         LL_EXTI_LINE_PA0
#define EXTI_LINE_PA1                         LL_EXTI_LINE_PA1
#define EXTI_LINE_PA2                         LL_EXTI_LINE_PA2
#define EXTI_LINE_PA3                         LL_EXTI_LINE_PA3
#define EXTI_LINE_PA4                         LL_EXTI_LINE_PA4
#define EXTI_LINE_PA5                         LL_EXTI_LINE_PA5
#define EXTI_LINE_PA6                         LL_EXTI_LINE_PA6
#define EXTI_LINE_PA7                         LL_EXTI_LINE_PA7
#define EXTI_LINE_PA8                         LL_EXTI_LINE_PA8
#define EXTI_LINE_PA9                         LL_EXTI_LINE_PA9
#define EXTI_LINE_PA10                        LL_EXTI_LINE_PA10
#define EXTI_LINE_PA11                        LL_EXTI_LINE_PA11
#define EXTI_LINE_PA12                        LL_EXTI_LINE_PA12
#define EXTI_LINE_PA13                        LL_EXTI_LINE_PA13
#define EXTI_LINE_PA14                        LL_EXTI_LINE_PA14
#define EXTI_LINE_PA15                        LL_EXTI_LINE_PA15
#define EXTI_LINE_PB0                         LL_EXTI_LINE_PB0
#define EXTI_LINE_PB1                         LL_EXTI_LINE_PB1
#define EXTI_LINE_PB2                         LL_EXTI_LINE_PB2
#define EXTI_LINE_PB3                         LL_EXTI_LINE_PB3
#define EXTI_LINE_PB4                         LL_EXTI_LINE_PB4
#define EXTI_LINE_PB5                         LL_EXTI_LINE_PB5
#define EXTI_LINE_PB6                         LL_EXTI_LINE_PB6
#define EXTI_LINE_PB7                         LL_EXTI_LINE_PB7
#define EXTI_LINE_PB8                         LL_EXTI_LINE_PB8
#define EXTI_LINE_PB9                         LL_EXTI_LINE_PB9
#define EXTI_LINE_PB10                        LL_EXTI_LINE_PB10
#define EXTI_LINE_PB11                        LL_EXTI_LINE_PB11
#define EXTI_LINE_PB12                        LL_EXTI_LINE_PB12
#define EXTI_LINE_PB13                        LL_EXTI_LINE_PB13
#define EXTI_LINE_PB14                        LL_EXTI_LINE_PB14
#define EXTI_LINE_PB15                        LL_EXTI_LINE_PB15
/**
  * @}
  */

/** @defgroup EXTI_Type  EXTI Type
  * @{
  */
#define EXTI_TYPE_EDGE                      LL_EXTI_TYPE_EDGE
#define EXTI_TYPE_LEVEL                     LL_EXTI_TYPE_LEVEL
/**
  * @}
  */

/** @defgroup EXTI_Trigger  EXTI Trigger
  * @{
  */
#define EXTI_TRIGGER_NONE                   0x00000000u
#define EXTI_TRIGGER_RISING_EDGE            LL_EXTI_TRIGGER_RISING_EDGE
#define EXTI_TRIGGER_FALLING_EDGE           LL_EXTI_TRIGGER_FALLING_EDGE
#define EXTI_TRIGGER_BOTH_EDGE              LL_EXTI_TRIGGER_BOTH_EDGE
#define EXTI_TRIGGER_LOW_LEVEL              LL_EXTI_TRIGGER_LOW_LEVEL
#define EXTI_TRIGGER_HIGH_LEVEL             LL_EXTI_TRIGGER_HIGH_LEVEL
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Macros EXTI Exported Macros
  * @{
  */

/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup EXTI_Private_Macros EXTI Private Macros
  * @{
  */
#define IS_EXTI_LINE(__LINE__)         (((__LINE__) == EXTI_LINE_PA0) || \
                                        ((__LINE__) == EXTI_LINE_PA1) || \
                                        ((__LINE__) == EXTI_LINE_PA2) || \
                                        ((__LINE__) == EXTI_LINE_PA3) || \
                                        ((__LINE__) == EXTI_LINE_PA4) || \
                                        ((__LINE__) == EXTI_LINE_PA5) || \
                                        ((__LINE__) == EXTI_LINE_PA6) || \
                                        ((__LINE__) == EXTI_LINE_PA8) || \
                                        ((__LINE__) == EXTI_LINE_PA9) || \
                                        ((__LINE__) == EXTI_LINE_PA10) || \
                                        ((__LINE__) == EXTI_LINE_PA11) || \
                                        ((__LINE__) == EXTI_LINE_PA12) || \
                                        ((__LINE__) == EXTI_LINE_PA13) || \
                                        ((__LINE__) == EXTI_LINE_PA14) || \
                                        ((__LINE__) == EXTI_LINE_PA15) || \
                                        ((__LINE__) == EXTI_LINE_PB0) || \
                                        ((__LINE__) == EXTI_LINE_PB1) || \
                                        ((__LINE__) == EXTI_LINE_PB2) || \
                                        ((__LINE__) == EXTI_LINE_PB3) || \
                                        ((__LINE__) == EXTI_LINE_PB4) || \
                                        ((__LINE__) == EXTI_LINE_PB5) || \
                                        ((__LINE__) == EXTI_LINE_PB6) || \
                                        ((__LINE__) == EXTI_LINE_PB7) || \
                                        ((__LINE__) == EXTI_LINE_PB8) || \
                                        ((__LINE__) == EXTI_LINE_PB9) || \
                                        ((__LINE__) == EXTI_LINE_PB10) || \
                                        ((__LINE__) == EXTI_LINE_PB11) || \
                                        ((__LINE__) == EXTI_LINE_PB12) || \
                                        ((__LINE__) == EXTI_LINE_PB14) || \
                                        ((__LINE__) == EXTI_LINE_PB15))
  
#define IS_EXTI_TYPE(__TYPE__)          (((__TYPE__) == EXTI_TYPE_EDGE) || \
                                         ((__TYPE__) == EXTI_TYPE_LEVEL))

#define IS_EXTI_TRIGGER(__TRIGGER__)    (((__TRIGGER__) == EXTI_TRIGGER_NONE) || \
                                         ((__TRIGGER__) == EXTI_TRIGGER_RISING_EDGE) || \
                                         ((__TRIGGER__) == EXTI_TRIGGER_FALLING_EDGE) || \
                                         ((__TRIGGER__) == EXTI_TRIGGER_BOTH_EDGE) || \
                                         ((__TRIGGER__) == EXTI_TRIGGER_LOW_LEVEL) || \
                                         ((__TRIGGER__) == EXTI_TRIGGER_HIGH_LEVEL))
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions EXTI Exported Functions
  * @brief    EXTI Exported Functions
  * @{
  */

/** @defgroup EXTI_Exported_Functions_Group1 Configuration functions
  * @brief    Configuration functions
  * @{
  */
/* Configuration functions ****************************************************/
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(uint32_t Line));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);
HAL_StatusTypeDef HAL_EXTI_Cmd(EXTI_HandleTypeDef *hexti, uint8_t NewState);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group2 IO operation functions
  * @brief    IO operation functions
  * @{
  */
/* IO operation functions *****************************************************/
void              HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti);
uint32_t          HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti);
void              HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti);

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

#endif /* RF_DRIVER_HAL_EXTI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
