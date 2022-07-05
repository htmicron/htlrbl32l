/**
  ******************************************************************************
  * @file    rf_driver_hal.h
  * @author  RF Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef RF_DRIVER_HAL_H
#define RF_DRIVER_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_ll_system.h"
#include "system_BlueNRG_LP.h"
#include "bluenrg_lp_hal_conf.h"
   
/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @defgroup HAL HAL
  * @{
  */
  
/* Exported constants --------------------------------------------------------*/
/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */
  
/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
#define  HAL_TICK_FREQ_10HZ         100U
#define  HAL_TICK_FREQ_100HZ        10U
#define  HAL_TICK_FREQ_1KHZ         1U
#define  HAL_TICK_FREQ_DEFAULT      HAL_TICK_FREQ_1KHZ

/**
  * @}
  */
  
/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_BootMode BOOT Mode
  * @{
  */
#define SYSCFG_BOOT_MAINFLASH           LL_SYSCFG_REMAP_FLASH           /*!< Main Flash memory mapped at 0x00000000   */
#define SYSCFG_BOOT_SRAM                LL_SYSCFG_REMAP_SRAM            /*!< SRAM1 mapped at 0x00000000               */

/**
  * @}
  */
    
/** @defgroup SYSCFG_FastModePlus_GPIO Fast-mode Plus on GPIO
  * @{
  */

/** @brief  Fast-mode Plus driving capability on a specific GPIO
  */  
#if defined(I2C1) 
#define SYSCFG_FASTMODEPLUS_PA0         SYSCFG_I2C_FMP_CTRL_I2C1_PA0_FMP  /*!< Enable Fast-mode Plus on PA0       */
#define SYSCFG_FASTMODEPLUS_PA1         SYSCFG_I2C_FMP_CTRL_I2C1_PA1_FMP  /*!< Enable Fast Mode Plus on PA1       */ 
#endif
#if defined(I2C2) 
#define SYSCFG_FASTMODEPLUS_PB6         SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP  /*!< Enable Fast Mode Plus on PB6       */ 
#define SYSCFG_FASTMODEPLUS_PB7         SYSCFG_I2C_FMP_CTRL_I2C2_PB7_FMP  /*!< Enable Fast Mode Plus on PB7       */ 
#endif
   
/**
 * @}
 */
    
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */

/** @brief  Main Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FLASH()        LL_SYSCFG_SetRemapMemory(LL_SYSCFG_REMAP_FLASH)

/** @brief  Embedded SRAM mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SRAM()         LL_SYSCFG_SetRemapMemory(LL_SYSCFG_REMAP_SRAM)


/**
  * @brief  Return the boot mode as configured by user.
  * @retval The boot mode as configured by user. The returned value can be one
  *         of the following values:
  *           @arg @ref SYSCFG_BOOT_MAINFLASH
  *           @arg @ref SYSCFG_BOOT_SRAM
  */
#define __HAL_SYSCFG_GET_BOOT_MODE()            LL_SYSCFG_GetRemapMemory()


/** @brief  Fast mode Plus driving capability enable/disable macros
  * @param __FASTMODEPLUS__ This parameter can be a value of @ref SYSCFG_FastModePlus_GPIO
  */
#define __HAL_SYSCFG_FASTMODEPLUS_ENABLE(__FASTMODEPLUS__)  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__))); \
                                                                LL_SYSCFG_EnableFastModePlus(__FASTMODEPLUS__);           \
                                                               }while(0)

#define __HAL_SYSCFG_FASTMODEPLUS_DISABLE(__FASTMODEPLUS__) do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__))); \
                                                                LL_SYSCFG_DisableFastModePlus(__FASTMODEPLUS__);          \
                                                               }while(0)

/**
  * @}
  */

/**
  * @}
  */
  
/* Private macros ------------------------------------------------------------*/
/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */

/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */

#define IS_SYSCFG_FASTMODEPLUS(__PIN__)                 ((((__PIN__) & SYSCFG_FASTMODEPLUS_PA0)  == SYSCFG_FASTMODEPLUS_PA0)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PA1)  == SYSCFG_FASTMODEPLUS_PA1)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB6)  == SYSCFG_FASTMODEPLUS_PB6)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7)  == SYSCFG_FASTMODEPLUS_PB7))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */

/** @defgroup HAL_Exported_Functions_Group1 HAL Initialization and Configuration functions
  * @{
  */

/* Initialization and Configuration functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);

HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority);

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group2 HAL Control functions
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(uint32_t Freq);
uint32_t HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);

/**
  * @}
  */

/* Exported variables ---------------------------------------------------------*/
/** @addtogroup HAL_Exported_Variables
  * @{
  */
extern __IO uint32_t uwTick;
extern uint32_t uwTickPrio;
extern uint32_t uwTickFreq;
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

#endif /* RF_DRIVER_HAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
