/**
  ******************************************************************************
  * @file    rf_driver_ll_flash.h
  * @author  RF Application Team
  * @brief   Header file of FLASH LL module.
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
#ifndef RF_DRIVER_LL_FLASH_H
#define RF_DRIVER_LL_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined (FLASH)
/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_Constants FLASH Constants
  * @{
  */
#define LL_FLASH_SIZE                      (((*(uint32_t *)FLASHSIZE_BASE & 0xFFFF) + 1) << 2U)
#define LL_FLASH_START_ADDR                NVM_BASE
#define LL_FLASH_END_ADDR                  (LL_FLASH_START_ADDR + LL_FLASH_SIZE - 1U)

#define LL_FLASH_PAGE_SIZE                 0x00000800U  /*!< FLASH Page Size, 2KBytes */
#define LL_FLASH_PAGE_NUMBER               (LL_FLASH_SIZE/LL_FLASH_PAGE_SIZE )

#define LL_FLASH_WRERP_GRANULARITY         0x00004000U  /*!< FLASH Write/Erase Protection Granularity, 16KBytes */
#define LL_FLASH_PCROP_GRANULARITY         LL_FLASH_SIZE   /*!< FLASH Code Readout Protection Granularity, all the MAIN FLASH */

/**
  * @}
  */

   
/** @defgroup FLASH_WAIT_STATES FLASH Wait States
  * @{
  */
#define LL_FLASH_WAIT_STATES_0                 0x00000000UL                /*!< FLASH Zero wait state   */
#define LL_FLASH_WAIT_STATES_1                 FLASH_CONFIG_WAIT_STATES_0  /*!< FLASH One wait state    */
/**
  * @}
  */

/** @defgroup FLASH_CONFIG_IRQ_VECT_TABLE FLASH Configuration Interrupt Vector Table 
  * @{
  */
#define LL_FLASH_CONFIG_IRQ_VECT_TABLE_FLASH    FLASH_CONFIG_PREMAP  /*!< Vector Table located in FLASH */
#define LL_FLASH_CONFIG_IRQ_VECT_TABLE_RAM      FLASH_CONFIG_REMAP   /*!< Vector Table located in RAM   */
/**
  * @}
  */

/** @defgroup FLASH_FLAGS FLASH Flags Definition
  * @{
  */
#define LL_FLASH_FLAG_CMDDONE             FLASH_IRQRAW_CMDDONE_RIS     /*!< FLASH command done flag    */
#define LL_FLASH_FLAG_CMDSTART            FLASH_IRQRAW_CMDSTART_RIS    /*!< FLASH command started flag */
#define LL_FLASH_FLAG_CMDERR              FLASH_IRQRAW_CMDERR_RIS      /*!< FLASH command error flag   */
#define LL_FLASH_FLAG_ILLCMD              FLASH_IRQRAW_ILLCMD_RIS      /*!< FLASH illegal command flag */

#define LL_FLASH_FLAG_ALL_ERRORS          (FLASH_IRQSTAT_CMDERR_RIS | FLASH_IRQSTAT_ILLCMD_RIS)

/** @defgroup FLASH_INTERRUPT_DEFINITION FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#define LL_FLASH_IT_CMDDONE               FLASH_IRQMASK_CMDDONEM     /*!< FLASH command done Interrupt source */
#define LL_FLASH_IT_CMDSTART              FLASH_IRQMASK_CMDSTARTM    /*!< FLASH command started Interrupt source */
#define LL_FLASH_IT_CMDERR                FLASH_IRQMASK_CMDERRM      /*!< FLASH command error Interrupt source */
#define LL_FLASH_IT_ILLCMD                FLASH_IRQMASK_ILLCMDM      /*!< FLASH illegal command Interrupt source */
/**
  * @}
  */

/** @defgroup FLASH_ERROR FLASH Error
  * @{
  */
#define LL_HAL_FLASH_ERROR_NONE            0x00000000U
#define LL_HAL_FLASH_ERROR_OP              FLASH_FLAG_CMDERR
#define LL_HAL_FLASH_ERROR_ILLCMD          FLASH_FLAG_ILLCMD
/**
  * @}
  */

/** @defgroup FLASH_COMMAND FLASH Command
  * @{
  */
#define LL_FLASH_CMD_ERASE_PAGES           0x11  /*!< flash pages erase command */
#define LL_FLASH_CMD_MASSERASE             0x22  /*!< Flash mass erase command  */
#define LL_FLASH_CMD_WRITE                 0x33  /*!< Flash write command       */
#define LL_FLASH_CMD_BURSTWRITE            0xCC  /*!< Flash burst write command */
#define LL_FLASH_CMD_OTPWRITE              0xEE  /*!< Flash OTP write command   */
/**
  * @}
  */

/** @defgroup FLASH_TYPE_ERASE FLASH Erase Type
  * @{
  */
#define LL_FLASH_TYPE_ERASE_PAGES           0x00  /*!< Pages erase      */
#define LL_FLASH_TYPE_ERASE_MASSERASE       0xFF  /*!< Flash mass erase */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  *  @{
  */

/** @defgroup USART_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in FLASH register
  * @param  __INSTANCE__ FLASH Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_FLASH_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in FLASH register
  * @param  __INSTANCE__ FLASH Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_FLASH_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup FLASH_LL_Exported_Functions FLASH Exported Functions
  * @{
  */

/** @defgroup FLASH_LL_EF_Configuration Configuration functions
  * @{
  */

/**
  * @brief  Set the FLASH Wait States.
  * @param  FLASHx FLASH Instance
  * @param wait_states FLASH WAIT States
  *         This parameter can be one of the following values :
  *     @arg @ref LL_FLASH_WAIT_STATES_0 FLASH Zero wait state
  *     @arg @ref LL_FLASH_WAIT_STATES_1 FLASH One wait state
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetWaitStates(FLASH_TypeDef *FLASHx, uint32_t wait_states)
{
  MODIFY_REG(FLASHx->CONFIG, FLASH_CONFIG_WAIT_STATES, wait_states);
}

/**
  * @brief  Get the FLASH Wait States.
  * @param  FLASHx FLASH Instance
  * @retval FLASH Wait States
  *         Returned value can be one of the following values :
  *     @arg @ref LL_FLASH_WAIT_STATES_0 FLASH Zero wait state
  *     @arg @ref LL_FLASH_WAIT_STATES_1 FLASH One wait state
  */ 
__STATIC_INLINE uint32_t LL_FLASH_GetWaitStates(FLASH_TypeDef *FLASHx)
{
   return (uint32_t)(READ_BIT(FLASHx->CONFIG, FLASH_CONFIG_WAIT_STATES));
}

/**
  * @brief  Enable the FLASH burst write operations.
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableBurstWrite(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CONFIG, FLASH_CONFIG_DIS_GROUP_WRITE);
}   

/**
  * @brief  Disable the FLASH burst write operations.
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableBurstWrite(FLASH_TypeDef *FLASHx)
{
   SET_BIT(FLASHx->CONFIG, FLASH_CONFIG_DIS_GROUP_WRITE);
}

/**
  * @brief  Set the FLASH Interrupt Vector Table location.
  * @param  FLASHx FLASH Instance
  * @param vect_table Vector Table Configuration
  *         This parameter can be one of the following values :
  *     @arg @ref LL_FLASH_CONFIG_IRQ_VECT_TABLE_FLASH Vector Table located in FLASH
  *     @arg @ref LL_FLASH_CONFIG_IRQ_VECT_TABLE_RAM   Vector Table located in RAM
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetVectTable(FLASH_TypeDef *FLASHx, uint32_t vect_table)
{
   MODIFY_REG(FLASHx->CONFIG, FLASH_CONFIG_PREMAP|FLASH_CONFIG_REMAP, vect_table);
}

/**
  * @brief  Get the FLASH Interrupt Vector Table location.
  * @param  FLASHx FLASH Instance
  * @retval Vector Table Configuration
  *         Returned value can be one of the following values :
  *     @arg @ref LL_FLASH_CONFIG_IRQ_VECT_TABLE_FLASH Vector Table located in FLASH
  *     @arg @ref LL_FLASH_CONFIG_IRQ_VECT_TABLE_RAM   Vector Table located in RAM
  */ 
__STATIC_INLINE uint32_t LL_FLASH_GetVectTable(FLASH_TypeDef *FLASHx)
{
   return (uint32_t)(READ_BIT(FLASHx->CONFIG, FLASH_CONFIG_PREMAP|FLASH_CONFIG_REMAP));
}
   
/**
  * @}
  */

/**
  * @}
  */


/** @defgroup FLASH_Interrupt FLASH Interrupts Macros
 *  @brief macros to handle FLASH interrupts
 * @{
 */

/**
  * @brief  Enable the specified FLASH interrupt.
  * @param  FLASHx FLASH Instance
  * @param  interrupt FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref LL_FLASH_IT_CMDDONE  Command Done Interrupt
  *     @arg @ref LL_FLASH_IT_CMDSTART Command Started Interrupt
  *     @arg @ref LL_FLASH_IT_CMDERR   Command Error Interrupt
  *     @arg @ref LL_FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval none
  */
__STATIC_INLINE void LL_FLASH_EnableIT(FLASH_TypeDef *FLASHx, uint32_t interrupt)
{
   CLEAR_BIT(FLASHx->IRQMASK, interrupt);
}

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  FLASHx FLASH Instance
  * @param  interrupt FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref LL_FLASH_IT_CMDDONE  Command Done Interrupt
  *     @arg @ref LL_FLASH_IT_CMDSTART Command Started Interrupt
  *     @arg @ref LL_FLASH_IT_CMDERR   Command Error Interrupt
  *     @arg @ref LL-FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval none
  */
__STATIC_INLINE void LL_FLASH_DisableIT(FLASH_TypeDef *FLASHx, uint32_t interrupt)
{
   SET_BIT(FLASHx->IRQMASK, interrupt);
}

/**
  * @brief  Check whether the specified FLASH interrupt has occurred or not.
  * @param  FLASHx FLASH Instance
  * @param  interrupt FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_CMDDONE  Command Done Interrupt
  *     @arg @ref FLASH_IT_CMDSTART Command Started Interrupt
  *     @arg @ref FLASH_IT_CMDERR   Command Error Interrupt
  *     @arg @ref FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval The new state of interrupt flag (SET or RESET).
  */
__STATIC_INLINE uint32_t LL_FLASH_GetIT(FLASH_TypeDef *FLASHx, uint32_t interrupt)
{
  return (uint32_t)((READ_BIT(FLASHx->IRQSTAT, interrupt) != RESET) ? SET : RESET);
}

/**
  * @brief  Clear the specified FLASH interrupt flag.
  * @param  FLASHx FLASH Instance
  * @param  interrupt FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_CMDDONE  Command Done Interrupt
  *     @arg @ref FLASH_IT_CMDSTART Command Started Interrupt
  *     @arg @ref FLASH_IT_CMDERR   Command Error Interrupt
  *     @arg @ref FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearIT(FLASH_TypeDef *FLASHx, uint32_t interrupt)
{
   WRITE_REG(FLASHx->IRQSTAT, interrupt);
}

/**
  * @brief  Check whether the specified FLASH flag is set or not.
  * @param  FLASHx FLASH Instance
  * @param  flag specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg @ref LL_FLASH_FLAG_CMDDONE     FLASH command done flag
  *     @arg @ref LL_FLASH_FLAG_CMDSTART    FLASH command started flag
  *     @arg @ref LL_FLASH_FLAG_CMDERR      FLASH command error flag
  *     @arg @ref LL_FLASH_FLAG_ILLCMD      FLASH illegal command flag
  * @retval The new state of FLASH flag (SET or RESET).
  */
__STATIC_INLINE uint32_t LL_FLASH_GetFlag(FLASH_TypeDef *FLASHx, uint32_t flag)
{
   return (uint32_t)((READ_BIT(FLASHx->IRQRAW, flag) == flag) ? 1UL : 0UL);
}

/**
  * @brief  Clear the FLASH's pending flags.
  * @param  FLASHx FLASH Instance
  * @param  flag specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg @ref LL_FLASH_FLAG_CMDDONE     FLASH command done flag
  *     @arg @ref LL_FLASH_FLAG_CMDSTART    FLASH command started flag
  *     @arg @ref LL_FLASH_FLAG_CMDERR      FLASH command error flag
  *     @arg @ref LL_FLASH_FLAG_ILLCMD      FLASH illegal command flag
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag(FLASH_TypeDef *FLASHx, uint32_t flag)
{
  WRITE_REG(FLASHx->IRQRAW, flag);
}

/**
  * @}
  */


/** @defgroup FLASH_Security FLASH Security Macros
 *  @brief macros to read FLASH security applied
 * @{
 */

/**
  * @brief  Check if FLASH & RAM SWD access is disabled
  * @rmtoll SIZE           SWD_DISABLE  LL_FLASH_SWD_Access_IsDisabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_SWD_Access_IsDisabled(void)
{
  return ((READ_BIT(FLASH->SIZE, FLASH_FLASH_SIZE_SWD_DISABLE) == (FLASH_FLASH_SIZE_SWD_DISABLE)) ? 1UL : 0UL);
}
 
/**
  * @brief  Check if FLASH Readout Protection is enabled
  * @rmtoll SIZE           FLASH_SECURE  LL_FLASH_ReadoutProtection_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadoutProtection_IsEnabled(void)
{
  return ((READ_BIT(FLASH->SIZE, FLASH_FLASH_SIZE_FLASH_SECURE) == (FLASH_FLASH_SIZE_FLASH_SECURE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @addtogroup FLASH_Exported_Functions
  * @{
  */
void LL_FLASH_Program(FLASH_TypeDef *FLASHx, uint32_t Address, uint32_t Data);
void LL_FLASH_ProgramBurst(FLASH_TypeDef *FLASHx, uint32_t Address, uint32_t *Data);
void LL_FLASH_Erase(FLASH_TypeDef *FLASHx, uint32_t TypeErase, uint32_t Page, uint32_t NbPages);
void LL_FLASH_OTPWrite(FLASH_TypeDef *FLASHx, uint32_t Address, uint32_t Data);
void LL_FLASH_PageProtection(FLASH_TypeDef *FLASHx, uint32_t pageProt_0, uint32_t pageProt_1, FunctionalState state);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */
   
/* Private constants --------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
 *  @{
 */


/**
  * @}
  */

/**
  * @}
  */
   
#endif /* defined(FLASH) */
   
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_LL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
