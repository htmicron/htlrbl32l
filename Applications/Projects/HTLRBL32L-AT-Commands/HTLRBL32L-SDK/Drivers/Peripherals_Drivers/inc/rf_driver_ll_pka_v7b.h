/**
  ******************************************************************************
  * @file    rf_driver_ll_pka_v7b.h
  * @author  RF Application Team
  * @brief   Header file of PKA LL module.
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
#ifndef RF_DRIVER_LL_PKA_H
#define RF_DRIVER_LL_PKA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined(PKA)

/** @defgroup PKA_LL PKA
  * @{
  */

/* Private variables ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PKA_LL_ES_INIT PKA Exported Init structure
  * @{
  */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Constants PKA Exported Constants
  * @{
  */

/** @defgroup PKA_SELECT_DATA_VALUE Select Data for PKA operation
  * @{
  */
#define LL_PKA_DATA_SK       0x01  /* PKA select data for K value */
#define LL_PKA_DATA_PCX      0x02  /* PKA select data for Point X coordinate value */
#define LL_PKA_DATA_PCY      0x03  /* PKA select data for Point Y coordinate value */
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
  
/** @defgroup PKA_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PKA_ReadReg function
  * @{
  */
#define LL_PKA_PROCEND                 PKA_ISR_PROC_END
#define LL_PKA_RAMERR                  PKA_ISR_RAM_ERR
#define LL_PKA_ADDRERR                 PKA_ISR_ADD_ERR
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Macros PKA Exported Macros
  * @{
  */

/** @defgroup PKA_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PKA register
  * @param  __INSTANCE__ PKA Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PKA_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PKA register
  * @param  __INSTANCE__ PKA Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PKA_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Functions PKA Exported Functions
  * @{
  */

/** @defgroup PKA_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Starts the encryption engine for the PKA peripheral.
  * @rmtoll CSR           GO            LL_PKA_Start
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_Start(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CSR, PKA_CSR_GO);
  /* The Bit GO must be reset before the end of calculation */
  CLEAR_BIT(PKAx->CSR, PKA_CSR_GO);  
}

/**
  * @brief  PKA peripheral software reset.
  * @rmtoll CSR           SFT_RST            LL_PKA_SWReset
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_SWReset(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CSR, PKA_CSR_SFT_RST);
}

/**
  * @brief  PKA peripheral software reset release.
  * @rmtoll CSR           SFT_RST            LL_PKA_SWResetRelease
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_SWResetRelease(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->CSR, PKA_CSR_SFT_RST);
}

/**
  * @brief  PKA peripheral ready to start a new calculation.
  * @rmtoll CSR           READY            LL_PKA_Ready
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_Ready(PKA_TypeDef *PKAx)
{
  return (uint32_t) ((READ_BIT(PKAx->CSR, PKA_CSR_READY) == (PKA_CSR_READY)) ? 1U : 0U);
}
  
/**
  * @}
  */

/** @defgroup PKA_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable address error interrupt.
  * @rmtoll IEN           ADDERR_EN     LL_PKA_EnableIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_ADDRERR(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->IEN, PKA_IEN_ADDERR_EN);
}

/**
  * @brief  Enable RAM error interrupt.
  * @rmtoll IEN           RAMERR_EN      LL_PKA_EnableIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_RAMERR(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->IEN, PKA_IEN_RAMERR_EN);
}

/**
  * @brief  Enable end of operation interrupt.
  * @rmtoll IEN           READY_EN     LL_PKA_EnableIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_PROCEND(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->IEN, PKA_IEN_READY_EN);
}

/**
  * @brief  Disable address error interrupt.
  * @rmtoll IEN           ADDERR_EN     LL_PKA_DisableIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_ADDRERR(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->IEN, PKA_IEN_ADDERR_EN);
}

/**
  * @brief  Disable RAM error interrupt.
  * @rmtoll IEN           RAMERR_EN      LL_PKA_DisableIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_RAMERR(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->IEN, PKA_IEN_RAMERR_EN);
}

/**
  * @brief  Disable End of operation interrupt.
  * @rmtoll IEN           READY_EN     LL_PKA_DisableIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_PROCEND(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->IEN, PKA_IEN_READY_EN);
}

/**
  * @brief  Check if address error interrupt is enabled.
  * @rmtoll IEN           ADDERR_EN     LL_PKA_IsEnabledIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_ADDRERR(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->IEN, PKA_IEN_ADDERR_EN) == (PKA_IEN_ADDERR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RAM error interrupt is enabled.
  * @rmtoll IEN           RAMERR_EN      LL_PKA_IsEnabledIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_RAMERR(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->IEN, PKA_IEN_RAMERR_EN) == (PKA_IEN_RAMERR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Check if end of operation interrupt is enabled.
  * @rmtoll IEN           READY_EN     LL_PKA_IsEnabledIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_PROCEND(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->IEN, PKA_IEN_READY_EN) == (PKA_IEN_READY_EN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup PKA_LL_EF_FLAG_Management PKA flag management
  * @{
  */

/**
  * @brief  Get PKA address error flag.
  * @rmtoll ISR           ADD_ERR      LL_PKA_IsActiveFlag_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_ADDRERR(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->ISR, PKA_ISR_ADD_ERR) == (PKA_ISR_ADD_ERR)) ? 1UL : 0UL);
}

/**
  * @brief  Get PKA RAM error flag.
  * @rmtoll ISR           RAM_ERR       LL_PKA_IsActiveFlag_RAMERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_RAMERR(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->ISR, PKA_ISR_RAM_ERR) == (PKA_ISR_RAM_ERR)) ? 1UL : 0UL);
}

/**
  * @brief  Get PKA end of operation flag.
  * @rmtoll ISR           PROC_END      LL_PKA_IsActiveFlag_PROCEND
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_PROCEND(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->ISR, PKA_ISR_PROC_END) == (PKA_ISR_PROC_END)) ? 1UL : 0UL);
}

/**
  * @brief  Clear PKA address error flag.
  * @rmtoll ISR        ADD_ERR     LL_PKA_ClearFlag_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_ADDRERR(PKA_TypeDef *PKAx)
{
  /* To clear the pending interrupt, 
   * the user must write this bit to 1
   * and clear it just after by writing 0.
   */
  SET_BIT(PKAx->ISR, PKA_ISR_ADD_ERR);
  CLEAR_BIT(PKAx->ISR, PKA_ISR_ADD_ERR);
}

/**
  * @brief  Clear PKA RAM error flag.
  * @rmtoll ISR        RAM_ERR      LL_PKA_ClearFlag_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_RAMERR(PKA_TypeDef *PKAx)
{
  /* To clear the pending interrupt, 
   * the user must write this bit to 1
   * and clear it just after by writing 0.
   */
  SET_BIT(PKAx->ISR, PKA_ISR_RAM_ERR);
  CLEAR_BIT(PKAx->ISR, PKA_ISR_RAM_ERR);
}

/**
  * @brief  Clear PKA end of operation flag.
  * @rmtoll ISR        PROC_END     LL_PKA_ClearFlag_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_PROCEND(PKA_TypeDef *PKAx)
{
  /* To clear the pending interrupt, 
   * the user must write this bit to 1
   * and clear it just after by writing 0.
   */
  SET_BIT(PKAx->ISR, PKA_ISR_PROC_END);
  CLEAR_BIT(PKAx->ISR, PKA_ISR_PROC_END);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)

/** @defgroup PKA_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_PKA_DeInit(PKA_TypeDef *PKAx);
ErrorStatus LL_PKA_Init(PKA_TypeDef *PKAx);
void LL_PKA_WaitEndProcess(PKA_TypeDef *PKAx);
ErrorStatus LL_PKA_VerifyProcess(void);
ErrorStatus LL_PKA_SetData(uint8_t dataType, uint32_t* srcData);
ErrorStatus LL_PKA_GetData(uint8_t dataType, uint8_t* dataTarget);
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

#endif /* defined(PKA) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_LL_PKA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
