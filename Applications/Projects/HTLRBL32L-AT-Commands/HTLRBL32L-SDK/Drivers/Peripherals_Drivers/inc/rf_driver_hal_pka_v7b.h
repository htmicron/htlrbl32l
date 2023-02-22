/**
  ******************************************************************************
  * @file    rf_driver_hal_pka_v7b.h
  * @author  RF Application Team
  * @brief   Header file of PKA HAL module.
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
#ifndef RF_DRIVER_HAL_PKA_H
#define RF_DRIVER_HAL_PKA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"

/** @addtogroup RF_DRIVER_HAL_Driver
 * @{
 */

#if defined(PKA) && defined(HAL_PKA_MODULE_ENABLED)

/** @addtogroup PKA
 * @{
 */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PKA_Exported_Types PKA Exported Types
 * @{
 */

/** @defgroup HAL_state_structure_definition HAL state structure definition
  * @brief  HAL State structures definition
  * @{
  */
typedef enum
{
  HAL_PKA_STATE_RESET   = 0x00U,  /*!< PKA not yet initialized or disabled  */
  HAL_PKA_STATE_READY   = 0x01U,  /*!< PKA initialized and ready for use    */
  HAL_PKA_STATE_BUSY    = 0x02U,  /*!< PKA internal processing is ongoing   */
  HAL_PKA_STATE_ERROR   = 0x03U,  /*!< PKA error state                      */
}
HAL_PKA_StateTypeDef;

/**
  * @}
  */

#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
/** @defgroup HAL_callback_id HAL callback ID enumeration
  * @{
  */
typedef enum
{
  HAL_PKA_OPERATION_COMPLETE_CB_ID      = 0x00U,    /*!< PKA End of operation callback ID  */
  HAL_PKA_ERROR_CB_ID                   = 0x01U,    /*!< PKA Error callback ID             */
  HAL_PKA_MSPINIT_CB_ID                 = 0x02U,    /*!< PKA Msp Init callback ID          */
  HAL_PKA_MSPDEINIT_CB_ID               = 0x03U     /*!< PKA Msp DeInit callback ID        */
} HAL_PKA_CallbackIDTypeDef;
  
/**
  * @}
  */

#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */

/** @defgroup PKA_Error_Code_definition PKA Error Code definition
  * @brief  PKA Error Code definition
  * @{
  */
#define HAL_PKA_ERROR_NONE      (0x00000000U)
#define HAL_PKA_ERROR_ADDRERR   (0x00000001U)
#define HAL_PKA_ERROR_RAMERR    (0x00000002U)
#define HAL_PKA_ERROR_TIMEOUT   (0x00000004U)
#define HAL_PKA_ERROR_OPERATION (0x00000008U)
#define HAL_PKA_ERROR_DATA_PCX  (0x00000010U)
#define HAL_PKA_ERROR_DATA_PCY  (0x00000020U)
#define HAL_PKA_ERROR_DATA_SK   (0x00000040U)
#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
#define HAL_PKA_ERROR_INVALID_CALLBACK  (0x00000080U)    /*!< Invalid Callback error */
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup PKA_handle_Structure_definition PKA handle Structure definition
  * @brief  PKA handle Structure definition
  * @{
  */
typedef struct __PKA_HandleTypeDef
{
  PKA_TypeDef                   *Instance;              /*!< Register base address */
  __IO HAL_PKA_StateTypeDef     State;                  /*!< PKA state */
  __IO uint32_t                 ErrorCode;              /*!< PKA Error code */
#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
  void (* OperationCpltCallback)(struct __PKA_HandleTypeDef *hpka); /*!< PKA End of operation callback */
  void (* ErrorCallback)(struct __PKA_HandleTypeDef *hpka);         /*!< PKA Error callback            */
  void (* MspInitCallback)(struct __PKA_HandleTypeDef *hpka);       /*!< PKA Msp Init callback         */
  void (* MspDeInitCallback)(struct __PKA_HandleTypeDef *hpka);     /*!< PKA Msp DeInit callback       */
#endif  /* USE_HAL_PKA_REGISTER_CALLBACKS */
} PKA_HandleTypeDef;
/**
  * @}
  */

#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
/** @defgroup PKA_Callback_definition PKA Callback pointer definition
  * @brief  PKA Callback pointer definition
  * @{
  */
typedef  void (*pPKA_CallbackTypeDef)(PKA_HandleTypeDef *hpka); /*!< Pointer to a PKA callback function */
/**
  * @}
  */
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PKA_Exported_Constants PKA Exported Constants
  * @{
  */

/** @defgroup PKA_SELECT_DATA_VALUE Select Data for PKA operation
  * @{
  */
#define PKA_DATA_SK       0x01  /* PKA select data for K value */
#define PKA_DATA_PCX      0x02  /* PKA select data for Point X coordinate value */
#define PKA_DATA_PCY      0x03  /* PKA select data for Point Y coordinate value */
/**
  * @}
  */
   
/** @defgroup PKA_RAM_ADDR RAM Address Definitions
  * @{
  */
#define PKA_RAM_ECC_ADDR_KP_ERROR   (PKA_RAM_BASE)
#define PKA_RAM_ECC_ADDR_K          (PKA_RAM_BASE + 0x6C)
#define PKA_RAM_ECC_ADDR_PX         (PKA_RAM_BASE + 0x90)
#define PKA_RAM_ECC_ADDR_PY         (PKA_RAM_BASE + 0xB4)

/* The initial Point X coordinate of the curve in hex format:
 * 6b17d1f2 e12c4247 f8bce6e5 63a440f2 77037d81 2deb33a0 f4a13945 d898c296
 */
#define INITIAL_START_POINT_X_W1        0xd898c296
#define INITIAL_START_POINT_X_W2        0xf4a13945
#define INITIAL_START_POINT_X_W3        0x2deb33a0
#define INITIAL_START_POINT_X_W4        0x77037d81
#define INITIAL_START_POINT_X_W5        0x63a440f2
#define INITIAL_START_POINT_X_W6        0xf8bce6e5
#define INITIAL_START_POINT_X_W7        0xe12c4247
#define INITIAL_START_POINT_X_W8        0x6b17d1f2

/* The initial Point Y coordinate of the curve in hex format:
 * 4fe342e2 fe1a7f9b 8ee7eb4a 7c0f9e16 2bce3357 6b315ece cbb64068 37bf51f5
 */
#define INITIAL_START_POINT_Y_W1        0x37bf51f5
#define INITIAL_START_POINT_Y_W2        0xcbb64068
#define INITIAL_START_POINT_Y_W3        0x6b315ece
#define INITIAL_START_POINT_Y_W4        0x2bce3357
#define INITIAL_START_POINT_Y_W5        0x7c0f9e16
#define INITIAL_START_POINT_Y_W6        0x8ee7eb4a
#define INITIAL_START_POINT_Y_W7        0xfe1a7f9b
#define INITIAL_START_POINT_Y_W8        0x4fe342e2
/**
  * @}
  */
  
/** @defgroup PKA_Interrupt_configuration_definition PKA Interrupt configuration definition
  * @brief PKA Interrupt definition
  * @{
  */
#define PKA_IT_PROCEND                            PKA_IEN_READY_EN
#define PKA_IT_ADDRERR                            PKA_IEN_ADDERR_EN
#define PKA_IT_RAMERR                             PKA_IEN_RAMERR_EN
/**
  * @}
  */

/** @defgroup PKA_Flag_definition PKA Flag definition
  * @{
  */
#define PKA_FLAG_PROCEND                          PKA_ISR_PROC_END
#define PKA_FLAG_ADDRERR                          PKA_ISR_RAM_ERR
#define PKA_FLAG_RAMERR                           PKA_ISR_ADD_ERR
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup PKA_Exported_Macros PKA Exported Macros
  * @{
  */

/** @brief  Reset PKA handle state.
  * @param  __HANDLE__ specifies the PKA Handle
  * @retval None
  */
#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
#define __HAL_PKA_RESET_HANDLE_STATE(__HANDLE__)                do{                                                   \
                                                                    (__HANDLE__)->State = HAL_PKA_STATE_RESET;       \
                                                                    (__HANDLE__)->MspInitCallback = NULL;            \
                                                                    (__HANDLE__)->MspDeInitCallback = NULL;          \
                                                                  } while(0)
#else
#define __HAL_PKA_RESET_HANDLE_STATE(__HANDLE__)                ((__HANDLE__)->State = HAL_PKA_STATE_RESET)
#endif

/** @brief  Enable the specified PKA interrupt.
  * @param  __HANDLE__ specifies the PKA Handle
  * @param  __INTERRUPT__ specifies the interrupt source to enable.
  *        This parameter can be one of the following values:
  *            @arg @ref PKA_IT_PROCEND End Of Operation interrupt enable
  *            @arg @ref PKA_IT_ADDRERR Address error interrupt enable
  *            @arg @ref PKA_IT_RAMERR RAM error interrupt enable
  * @retval None
  */
#define __HAL_PKA_ENABLE_IT(__HANDLE__, __INTERRUPT__)          ((__HANDLE__)->Instance->IEN |= (__INTERRUPT__))

/** @brief  Disable the specified PKA interrupt.
  * @param  __HANDLE__ specifies the PKA Handle
  * @param  __INTERRUPT__ specifies the interrupt source to disable.
  *        This parameter can be one of the following values:
  *            @arg @ref PKA_IT_PROCEND End Of Operation interrupt enable
  *            @arg @ref PKA_IT_ADDRERR Address error interrupt enable
  *            @arg @ref PKA_IT_RAMERR RAM error interrupt enable
  * @retval None
  */
#define __HAL_PKA_DISABLE_IT(__HANDLE__, __INTERRUPT__)         ((__HANDLE__)->Instance->IEN &= (~(__INTERRUPT__)))

/** @brief  Check whether the specified PKA interrupt source is enabled or not.
  * @param  __HANDLE__ specifies the PKA Handle
  * @param  __INTERRUPT__ specifies the PKA interrupt source to check.
  *        This parameter can be one of the following values:
  *            @arg @ref PKA_IT_PROCEND End Of Operation interrupt enable
  *            @arg @ref PKA_IT_ADDRERR Address error interrupt enable
  *            @arg @ref PKA_IT_RAMERR RAM error interrupt enable
  * @retval The new state of __INTERRUPT__ (SET or RESET)
  */
#define __HAL_PKA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)      ((((__HANDLE__)->Instance->IEN & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Check whether the specified PKA flag is set or not.
  * @param  __HANDLE__ specifies the PKA Handle
  * @param  __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg @ref PKA_FLAG_PROCEND End Of Operation
  *            @arg @ref PKA_FLAG_ADDRERR Address error
  *            @arg @ref PKA_FLAG_RAMERR RAM error
  * @retval The new state of __FLAG__ (SET or RESET)
  */
#define __HAL_PKA_GET_FLAG(__HANDLE__, __FLAG__)                (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/** @brief  Clear the PKA pending flags which are cleared by writing 1 in a specific bit.
  * @param  __HANDLE__ specifies the PKA Handle
  * @param  __FLAG__ specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg @ref PKA_FLAG_PROCEND End Of Operation
  *            @arg @ref PKA_FLAG_ADDRERR Address error
  *            @arg @ref PKA_FLAG_RAMERR RAM error
  * @retval None
  */
#define __HAL_PKA_CLEAR_FLAG(__HANDLE__, __FLAG__)    do {                                                    \
                                                           SET_BIT((__HANDLE__)->Instance->ISR,(__FLAG__));   \
                                                           CLEAR_BIT((__HANDLE__)->Instance->ISR,(__FLAG__)); \
                                                         } while(0)

/** @brief  Start a PKA operation.
  * @param  __HANDLE__ specifies the PKA Handle
  * @retval None
  */
#define __HAL_PKA_START(__HANDLE__)                             (SET_BIT((__HANDLE__)->Instance->CSR,  PKA_CSR_GO))
/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup PKA_Exported_Functions
  * @{
  */

/** @addtogroup PKA_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_PKA_Init(PKA_HandleTypeDef *hpka);
HAL_StatusTypeDef HAL_PKA_DeInit(PKA_HandleTypeDef *hpka);
void              HAL_PKA_MspInit(PKA_HandleTypeDef *hpka);
void              HAL_PKA_MspDeInit(PKA_HandleTypeDef *hpka);

#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_PKA_RegisterCallback(PKA_HandleTypeDef *hpka, HAL_PKA_CallbackIDTypeDef CallbackID, pPKA_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_PKA_UnRegisterCallback(PKA_HandleTypeDef *hpka, HAL_PKA_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup PKA_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
/* High Level Functions *******************************************************/
HAL_StatusTypeDef HAL_PKA_StartProc(PKA_HandleTypeDef *hpka, uint32_t *randomK, uint32_t Timeout, uint32_t *PKAStartPoint);
HAL_StatusTypeDef HAL_PKA_StartProc_IT(PKA_HandleTypeDef *hpka, uint32_t *randomK, uint32_t Timeout, uint32_t *PKAStartPoint);
void HAL_PKA_GetResult(PKA_HandleTypeDef *hpka, uint8_t dataType, uint8_t *pRes);
HAL_StatusTypeDef HAL_PKA_Abort(PKA_HandleTypeDef *hpka);
void HAL_PKA_RAMReset(PKA_HandleTypeDef *hpka);
void HAL_PKA_OperationCpltCallback(PKA_HandleTypeDef *hpka);
void HAL_PKA_ErrorCallback(PKA_HandleTypeDef *hpka);
void HAL_PKA_IRQHandler(PKA_HandleTypeDef *hpka);
/**
  * @}
  */

/** @addtogroup PKA_Exported_Functions_Group3
  * @{
  */
/* Peripheral State and Error functions ***************************************/
HAL_PKA_StateTypeDef HAL_PKA_GetState(PKA_HandleTypeDef *hpka);
uint32_t             HAL_PKA_GetError(PKA_HandleTypeDef *hpka);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(PKA) && defined(HAL_PKA_MODULE_ENABLED) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_HAL_PKA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
