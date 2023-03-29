/**
  ******************************************************************************
  * @file    rf_driver_hal_rng.h
  * @author  RF Application Team
  * @brief   Header file of RNG HAL module.
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
#ifndef RF_DRIVER_HAL_RNG_H
#define RF_DRIVER_HAL_RNG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

#if defined (RNG)

/** @defgroup RNG RNG
  * @brief RNG HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RNG_Exported_Types RNG Exported Types
  * @{
  */

/** @defgroup RNG_Exported_Types_Group1 RNG Init Structure definition
  * @{
  */
typedef struct
{
  uint32_t                    ClockErrorDetection; /*!< CED Clock error detection */
} RNG_InitTypeDef;

/**
  * @}
  */

/** @defgroup RNG_Exported_Types_Group2 RNG State Structure definition
  * @{
  */
typedef enum
{
  HAL_RNG_STATE_RESET     = 0x00U,  /*!< RNG not yet initialized or disabled */
  HAL_RNG_STATE_READY     = 0x01U,  /*!< RNG initialized and ready for use   */
  HAL_RNG_STATE_BUSY      = 0x02U,  /*!< RNG internal process is ongoing     */
  HAL_RNG_STATE_TIMEOUT   = 0x03U,  /*!< RNG timeout state                   */
  HAL_RNG_STATE_ERROR     = 0x04U   /*!< RNG error state                     */

} HAL_RNG_StateTypeDef;

/**
  * @}
  */

/** @defgroup RNG_Exported_Types_Group3 RNG Handle Structure definition
  * @{
  */
typedef struct
{
  RNG_TypeDef                 *Instance;    /*!< Register base address   */

  RNG_InitTypeDef             Init;         /*!< RNG configuration parameters */

  HAL_LockTypeDef             Lock;         /*!< RNG locking object      */

  __IO HAL_RNG_StateTypeDef   State;        /*!< RNG communication state */

  __IO  uint32_t              ErrorCode;    /*!< RNG Error code               */

  uint32_t                    RandomNumber; /*!< Last Generated RNG Data */
} RNG_HandleTypeDef;

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RNG_Exported_Constants RNG Exported Constants
  * @{
  */

/** @defgroup RNG_Exported_Constants_Group1 RNG Flag definition
  * @{
  */
#define RNG_FLAG_DRDY   RNG_SR_RNGRDY  /*!< New Random Data Ready */
#define RNG_FLAG_REVCLK RNG_SR_REVCLK  /*!< Clock Detection flag  */
#define RNG_FLAG_FAULT  RNG_SR_FAULT   /*!< Fault flag            */
/**
  * @}
  */

/** @defgroup RNG_Exported_Constants_Group2 RNG Clock Error Detection
  * @{
  */
#define RNG_CED_DISABLE          0x00000000U     /*!< Clock error detection Enabled  */
#define RNG_CED_ENABLE           RNG_CR_TST_CLK  /*!< Clock error detection Disabled */
/**
  * @}
  */

/** @defgroup RNG_Error_Definition   RNG Error Definition
  * @{
  */
#define  HAL_RNG_ERROR_NONE             0x00000000U    /*!< No error */
#define  HAL_RNG_ERROR_SEQUENCE         0x00000001U    /*!< This bit is set by hardware when a faulty sequence of bits occurs */
#define  HAL_RNG_ERROR_TIMEOUT          0x00000002U    /*!< Timeout Error */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RNG_Exported_Macros RNG Exported Macros
  * @{
  */

/** @brief Reset RNG handle state
  * @param  __HANDLE__ RNG Handle
  * @retval None
  */
#define __HAL_RNG_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_RNG_STATE_RESET)

/**
  * @brief  Enables the RNG peripheral.
  * @param  __HANDLE__ RNG Handle
  * @retval None
  */
#define __HAL_RNG_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR &= ~RNG_CR_RNG_DIS)

/**
  * @brief  Disables the RNG peripheral.
  * @param  __HANDLE__ RNG Handle
  * @retval None
  */
#define __HAL_RNG_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR |= RNG_CR_RNG_DIS)

/**
  * @brief  Check the selected RNG flag status.
  * @param  __HANDLE__ RNG Handle
  * @param  __FLAG__ RNG flag
  *          This parameter can be one of the following values:
  *            @arg RNG_FLAG_DRDY:    New Random Data Ready
  *            @arg RNG_FLAG_REVCLK:  Clock Detection flag
  *            @arg RNG_FLAG_FAULT:   Fault flag
  * @retval The new state of __FLAG__ (SET or RESET).
  */
#define __HAL_RNG_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR & (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clears the selected RNG flag status.
  * @param  __HANDLE__ RNG handle
  * @param  __FLAG__ RNG flag to clear
  * @note   WARNING: This macro clear only RNG_FLAG_FAULT flag because
  *         flags RNG_FLAG_DRDY and RNG_FLAG_REVCLK are read-only.
  * @retval None
  */
#define __HAL_RNG_CLEAR_FLAG(__HANDLE__, __FLAG__)  (if((__FLAG__) ==  RNG_FLAG_FAULT) (__HANDLE__)->Instance->SR = RNG_FLAG_FAULT)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RNG_Exported_Functions RNG Exported Functions
  * @{
  */

/** @defgroup RNG_Exported_Functions_Group1 Initialization and configuration functions
  * @{
  */
HAL_StatusTypeDef HAL_RNG_Init(RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef HAL_RNG_DeInit(RNG_HandleTypeDef *hrng);
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng);
void HAL_RNG_MspDeInit(RNG_HandleTypeDef *hrng);
/**
  * @}
  */

/** @defgroup RNG_Exported_Functions_Group2 Peripheral Control functions
  * @{
  */
HAL_StatusTypeDef HAL_RNG_GenerateRandomNumber(RNG_HandleTypeDef *hrng, uint32_t *random32bit);
uint32_t HAL_RNG_ReadLastRandomNumber(RNG_HandleTypeDef *hrng);
/**
  * @}
  */

/** @defgroup RNG_Exported_Functions_Group3 Peripheral State functions
  * @{
  */
HAL_RNG_StateTypeDef HAL_RNG_GetState(RNG_HandleTypeDef *hrng);
uint32_t             HAL_RNG_GetError(RNG_HandleTypeDef *hrng);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RNG_Private_Macros RNG Private Macros
  * @{
  */
#define IS_RNG_FLAG(FLAG) (((FLAG) == RNG_FLAG_DRDY)   || \
                           ((FLAG) == RNG_FLAG_REVCLK) ||  \
                           ((FLAG) == RNG_FLAG_FAULT))

/**
  * @brief Verify the RNG Clock Error Detection mode.
  * @param __MODE__ RNG Clock Error Detection mode
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_RNG_CED(__MODE__)   (((__MODE__) == RNG_CED_ENABLE) || \
                                ((__MODE__) == RNG_CED_DISABLE))
/**
  * @}
  */

/**
  * @}
  */

#endif /* RNG */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* RF_DRIVER_HAL_RNG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
