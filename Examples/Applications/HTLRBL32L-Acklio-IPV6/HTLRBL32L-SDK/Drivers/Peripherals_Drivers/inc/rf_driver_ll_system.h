/**
  ******************************************************************************
  * @file    rf_driver_ll_system.h
  * @author  RF Application Team
  * @brief   Header file of SYSTEM LL module.
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL SYSTEM driver contains a set of generic APIs that can be
    used by user:
      (+) Some of the FLASH features need to be handled in the SYSTEM file.
      (+) Access to SYSCFG registers

  @endverbatim
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
#ifndef RF_DRIVER_LL_SYSTEM_H
#define RF_DRIVER_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_REMAP SYSCFG REMAP
* @{
*/
#define LL_SYSCFG_REMAP_FLASH                   FLASH_CONFIG_PREMAP                 /*!< Main Flash memory mapped at 0x00000000   */
#define LL_SYSCFG_REMAP_SRAM                    FLASH_CONFIG_REMAP                  /*!< SRAM mapped at 0x00000000               */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_I2C_FASTMODEPLUS SYSCFG I2C FASTMODEPLUS
  * @{
  */
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PA0_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA0          SYSCFG_I2C_FMP_CTRL_I2C1_PA0_FMP /*!< Enable Fast Mode Plus on PA0       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PA1_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA1          SYSCFG_I2C_FMP_CTRL_I2C1_PA1_FMP /*!< Enable Fast Mode Plus on PA1       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PB6_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB6          SYSCFG_I2C_FMP_CTRL_I2C1_PB6_FMP  /*!< Enable Fast Mode Plus on PB6       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PB7_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB7          SYSCFG_I2C_FMP_CTRL_I2C1_PB7_FMP  /*!< Enable Fast Mode Plus on PB7       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PB10_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB10         SYSCFG_I2C_FMP_CTRL_I2C1_PB10_FMP /*!< Enable Fast Mode Plus on PB10      */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PB11_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB11         SYSCFG_I2C_FMP_CTRL_I2C1_PB11_FMP /*!< Enable Fast Mode Plus on PB11      */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PA6_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA6          SYSCFG_I2C_FMP_CTRL_I2C2_PA6_FMP  /*!< Enable Fast Mode Plus on PA6       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PA7_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA7          SYSCFG_I2C_FMP_CTRL_I2C2_PA7_FMP  /*!< Enable Fast Mode Plus on PA7       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PA13_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA13         SYSCFG_I2C_FMP_CTRL_I2C2_PA13_FMP /*!< Enable Fast Mode Plus on PA13      */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PA14_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA14         SYSCFG_I2C_FMP_CTRL_I2C2_PA14_FMP /*!< Enable Fast Mode Plus on PA14      */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP) 
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB6          SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP /*!< Enable Fast Mode Plus on PB6       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PB7_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB7          SYSCFG_I2C_FMP_CTRL_I2C2_PB7_FMP /*!< Enable Fast Mode Plus on PB7       */
#endif
/**
  * @}
  */


/** @defgroup SYSTEM_LL_PWRC_IM SYSCFG Power Controller Inerrupt MASK
  * @{
  */
#define LL_SYSCFG_PWRC_PVD                     SYSCFG_PWRC_IER_PVD_IE  /*!< PVD interrupt mask  */
#define LL_SYSCFG_PWRC_WKUP                    SYSCFG_PWRC_IER_WKUP_IE /*!< WKUP interrupt mask */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 0x00000000U                  /*!< FLASH Zero wait state  */
#define LL_FLASH_LATENCY_1                 FLASH_CONFIG_WAIT_STATES_0   /*!< FLASH One wait state when system clock frequency is 64 MHz */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_DEVICE_INFORMATION Device Version Information
  * @{
  */
#define LL_BLUENRG_LP_CUT_10               0x10
#define LL_BLUENRG_LP_CUT_20               0x20
/**
  * @}
  */


/** @defgroup SYSTEM_LL_IO_ANALOG_SWITCH IO GPIOB14 analog configuration
  * @{
  */
#define LL_SYSCFG_PB14_PVD      0x00000000U                      /*!< PVD external voltage feature is selected */
#define LL_SYSCFG_PB14_ATB1     SYSCFG_GPIO_SWA_CTRL_ATB1_nPVD   /*!< ATB1 feature is selected                 */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_RXTX_DET_TYPE Tx/Rx sequence information detection type
  * @{
  */
#define LL_SYSCFG_BLERXTX_DET_TYPE_EDGE           ((uint8_t)0x00U) /*!<  Tx/Rx detection type EDGE  */
#define LL_SYSCFG_BLERXTX_DET_TYPE_LEVEL          ((uint8_t)0x01U) /*!<  Tx/Rx detection type LEVEL */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_RXTX_EDGE_TRIGGER Tx/Rx detection trigger
  * @{
  */
#define LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE     ((uint8_t)0x00U) /*!< Trigger on Rising Edge  */
#define LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE    ((uint8_t)0x01U) /*!< Trigger on Falling Edge */
#define LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE       ((uint8_t)0x02U) /*!< Trigger on Both Edge    */
#define LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL       ((uint8_t)0x03U) /*!< Trigger on Low Level    */
#define LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL      ((uint8_t)0x04U) /*!< Trigger on High Level   */

/**
  * @}
  */

/** @defgroup SYSCFG_LL_TX_RX_EVENT_ENABLE Tx/Rx event 
  * @{
  */
#define LL_SYSCFG_BLE_TX_EVENT    SYSCFG_BLERXTX_IER_TX_IE /*!< Tx Event Enable */
#define LL_SYSCFG_BLE_RX_EVENT    SYSCFG_BLERXTX_IER_RX_IE /*!< Rx Event Enable */
#if defined(SYSCFG_BLERXTX_ISCR_RX_ISEDGE)
#define LL_SYSCFG_BLE_RX_FALLING_EDGE_EVENT    (0x00000000U)                     /*!< Falling edge on RX sequence detected */
#define LL_SYSCFG_BLE_RX_RISING_EDGE_EVENT     (SYSCFG_BLERXTX_ISCR_RX_ISEDGE)   /*!< Rising edge on RX sequence detected  */
#endif
#if defined(SYSCFG_BLERXTX_ISCR_TX_ISEDGE)
#define LL_SYSCFG_BLE_TX_FALLING_EDGE_EVENT    (0x00000000U)                     /*!< Falling edge on TX sequence detected */
#define LL_SYSCFG_BLE_TX_RISING_EDGE_EVENT     (SYSCFG_BLERXTX_ISCR_TX_ISEDGE)   /*!< Rising edge on TX sequence detected  */
#endif
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Get the device version and cut information.
  * @rmtoll DIE_ID PRODUCT/VERSION/REVISION   LL_SYSCFG_GetDeviceID
  * @retval Device ID
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDeviceID(void)
{
  return (uint32_t)READ_REG(SYSCFG->DIE_ID);
}


/**
  * @brief  Get the device cut revision (metal fix) information.
  * @rmtoll DIE_ID REVISION   LL_SYSCFG_GetDeviceRevision
  * @retval Device ID
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDeviceRevision(void)
{
  return (uint32_t)((READ_REG(SYSCFG->DIE_ID) & SYSCFG_DIE_ID_REVISION) >> SYSCFG_DIE_ID_REVISION_Pos);
}

/**
  * @brief  Get the device cut version information.
  * @rmtoll DIE_ID VERSION   LL_SYSCFG_GetDeviceVersion
  * @retval Device ID
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDeviceVersion(void)
{
  return (uint32_t)((READ_REG(SYSCFG->DIE_ID) & SYSCFG_DIE_ID_VERSION) >> SYSCFG_DIE_ID_VERSION_Pos);
}

/**
  * @brief  Get the JTAG_ID device information.
  * @rmtoll JTAG_ID    LL_SYSCFG_GetDeviceJTAG_ID
  * @retval Device ID
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDeviceJTAG_ID(void)
{
  return (uint32_t)READ_REG(SYSCFG->JTAG_ID);
}

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll CONFIG PREMAP/REMAP      LL_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRemapMemory(uint32_t Memory)
{
  MODIFY_REG(FLASH->CONFIG, (FLASH_CONFIG_PREMAP|FLASH_CONFIG_REMAP), Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll CONFIG PREMAP/REMAP      LL_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRemapMemory(void)
{
  uint32_t remap, premap;
  uint32_t memory_map;
  
  remap = READ_BIT(FLASH->CONFIG, FLASH_CONFIG_REMAP) >> FLASH_CONFIG_REMAP_Pos;
  premap = READ_BIT(FLASH->CONFIG, FLASH_CONFIG_PREMAP) >> FLASH_CONFIG_PREMAP_Pos;

  if (remap == 1)
    memory_map = LL_SYSCFG_REMAP_SRAM;

  if ((premap == 1) && (remap == 0))
    memory_map = LL_SYSCFG_REMAP_FLASH;
  
  return memory_map;
}

/**
  * @brief  Enable the I2C fast mode plus driving capability.
  * @rmtoll I2C_FMP_CTRL  I2C1_PAx_FMP/I2C2_PBx_FMP   LL_SYSCFG_EnableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA0
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB10
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB11
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA13
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA14
  * @retval None
  * @note   LL_SYSCFG_I2C_FASTMODEPLUS_PB10, LL_SYSCFG_I2C_FASTMODEPLUS_PB11, LL_SYSCFG_I2C_FASTMODEPLUS_PA6,
  *         LL_SYSCFG_I2C_FASTMODEPLUS_PA7, LL_SYSCFG_I2C_FASTMODEPLUS_PA13 and LL_SYSCFG_I2C_FASTMODEPLUS_PA14
  */
__STATIC_INLINE void LL_SYSCFG_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  SET_BIT(SYSCFG->I2C_FMP_CTRL, ConfigFastModePlus);
}

/**
  * @brief  Disable the I2C fast mode plus driving capability.
  * @rmtoll I2C_FMP_CTRL  I2C1_PAx_FMP/I2C2_PBx_FMP   LL_SYSCFG_DisableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA0
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB10
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB11
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA13
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA14
  * @retval None
  * @note   LL_SYSCFG_I2C_FASTMODEPLUS_PB10, LL_SYSCFG_I2C_FASTMODEPLUS_PB11, LL_SYSCFG_I2C_FASTMODEPLUS_PA6,
  *         LL_SYSCFG_I2C_FASTMODEPLUS_PA7, LL_SYSCFG_I2C_FASTMODEPLUS_PA13 and LL_SYSCFG_I2C_FASTMODEPLUS_PA14
  */
__STATIC_INLINE void LL_SYSCFG_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  CLEAR_BIT(SYSCFG->I2C_FMP_CTRL, ConfigFastModePlus);
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_PWRC SYSCFG
  * @{
  */
  
/**
  * @brief  Enable PWRC Interrupt Mask
  * @rmtoll PWRC_IER        LL_SYSCFG_PWRC_EnableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_PWRC_PVD
  *         @arg @ref LL_SYSCFG_PWRC_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_PWRC_EnableIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->PWRC_IER, Interrupt);
}

/**
  * @brief  Disable PWRC Interrupt Mask
  * @rmtoll PWRC_IER        LL_SYSCFG_PWRC_DisableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_PWRC_PVD
  *         @arg @ref LL_SYSCFG_PWRC_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_PWRC_DisableIT(uint32_t Interrupt)
{
  CLEAR_BIT(SYSCFG->PWRC_IER, Interrupt);
}

/**
  * @brief  Indicate if PWRC Interrupt Mask is enabled
  * @rmtoll PWRC_IER        LL_SYSCFG_PWRC_IsEnabledIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_PWRC_PVD
  *         @arg @ref LL_SYSCFG_PWRC_WKUP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_PWRC_IsEnabledIT(uint32_t Interrupt)
{
  return ((READ_BIT(SYSCFG->PWRC_IER, Interrupt) == (Interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Get PWRC Interrupt Status
  * @rmtoll PWRC_ISCR        LL_SYSCFG_PWRC_GetStatusIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_PWRC_PVD
  *         @arg @ref LL_SYSCFG_PWRC_WKUP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_PWRC_GetStatusIT(uint32_t Interrupt)
{
  return ((READ_BIT(SYSCFG->PWRC_ISCR, Interrupt) == (Interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Clear PWRC Interrupt Status
  * @rmtoll PWRC_ISCR        LL_SYSCFG_PWRC_ClearIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_PWRC_PVD
  *         @arg @ref LL_SYSCFG_PWRC_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_PWRC_ClearIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->PWRC_ISCR, Interrupt);
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_CONFIG    WAIT_STATE      LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->CONFIG, FLASH_CONFIG_WAIT_STATES, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_CONFIG    WAIT_STATE     LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->CONFIG, FLASH_CONFIG_WAIT_STATES));
}
/**
  * @}
  */

/** @defgroup SYSTEM_LL_ANALOG_SWITCH Analog source selection to connect on analog pads
  * @{
  */

#if defined(SYSCFG_GPIO_SWA_CTRL_PGACAP_nVIN0)
/**
  * @brief  Enable analog feature on PB2/PB3 between connection external capacitor
  *         on PGA (for analog audio mode) and VNM/P0 for ADC measurements when the
  *         PB2 and PB3 are programmed in analog mode
  * @rmtoll GPIO_SWA_CTRL    PGACAP_nVIN0     LL_IO_AnalogSwitchControl_VINM_PO_Enable
  * @retval None
  */
__STATIC_INLINE void LL_IO_AnalogSwitchControl_VINM_PO_Enable(void)
{
  SET_BIT(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_PGACAP_nVIN0);
}

/**
  * @brief  Disable analog feature on PB2/PB3 between connection external capacitor
  *         on PGA (for analog audio mode) and VNM/P0 for ADC measurements when the
  *         PB2 and PB3 are programmed in analog mode
  * @rmtoll GPIO_SWA_CTRL    PGACAP_nVIN0     LL_IO_AnalogSwitchControl_VINM_PO_Disable
  * @retval None
  */
__STATIC_INLINE void LL_IO_AnalogSwitchControl_VINM_PO_Disable(void)
{
  CLEAR_BIT(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_PGACAP_nVIN0);
}
  
/**
  * @brief  Return if the analog feature on PB2/PB3 between connection external capacitor
  *         on PGA (for analog audio mode) and VNM/P0 for ADC measurements when the
  *         PB2 and PB3 are programmed in analog mode is enabled
  * @rmtoll GPIO_SWA_CTRL    PGACAP_nVIN0     LL_IO_AnalogSwitchControl_VINM_PO_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_IO_AnalogSwitchControl_VINM_PO_IsEnabled(void)
{
  return ((READ_BIT(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_PGACAP_nVIN0) == (SYSCFG_GPIO_SWA_CTRL_PGACAP_nVIN0)) ? 1UL : 0UL);
}
#endif

#if defined(SYSCFG_GPIO_SWA_CTRL_VINP2_ATB0)
/**
  * @brief  Enable analog feature on PA3 between VINP2 and ATB0 when the PA3 I/O
  *         is programmed in analog mode (in the associated GPIO_MODER register)
  * @rmtoll GPIO_SWA_CTRL    VINP2_ATB0     LL_IO_AnalogSwitchControl_VINP2_ATB0_Enable
  * @retval None
  */
__STATIC_INLINE void LL_IO_AnalogSwitchControl_VINP2_ATB0_Enable(void)
{
  SET_BIT(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_VINP2_ATB0);
}

/**
  * @brief  Disable analog feature on PA3 between VINP2 and ATB0 when the PA3 I/O
  *         is programmed in analog mode (in the associated GPIO_MODER register)
  * @rmtoll GPIO_SWA_CTRL    VINP2_ATB0     LL_IO_AnalogSwitchControl_VINP2_ATB0_Disable
  * @retval None
  */
__STATIC_INLINE void LL_IO_AnalogSwitchControl_VINP2_ATB0_Disable(void)
{
  CLEAR_BIT(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_VINP2_ATB0);
}
  
/**
  * @brief  Return if the analog feature on PA3 between VINP2 and ATB0 when the PA3 I/O
  *         is programmed in analog mode (in the associated GPIO_MODER register)
  * @rmtoll GPIO_SWA_CTRL    VINP2_ATB0     LL_IO_AnalogSwitchControl_VINP2_ATB0_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_IO_AnalogSwitchControl_VINP2_ATB0_IsEnabled(void)
{
  return ((READ_BIT(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_VINP2_ATB0) == (SYSCFG_GPIO_SWA_CTRL_VINP2_ATB0)) ? 1UL : 0UL);
}
#endif

/**
  * @brief  Setup analog feature on PB14 between ATB1 and PVD when the PB14 I/O
  *         is programmed in analog mode
  * @rmtoll GPIO_SWA_CTRL    ATB1_nPVD   LL_IO_AnalogSwitchControl_PB14
  * @param  feature this parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_PB14_PVD
  *         @arg @ref LL_SYSCFG_PB14_ATB1
  * @retval None
  */
__STATIC_INLINE void LL_IO_SetAnalogSwitchControl_PB14(uint32_t feature)
{
  MODIFY_REG(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_ATB1_nPVD, feature);
}

/**
  * @brief  Setup analog feature on PB14 between ATB1 and PVD when the PB14 I/O
  *         is programmed in analog mode
  * @rmtoll GPIO_SWA_CTRL    ATB1_nPVD   LL_IO_AnalogSwitchControl_PB14
  * @retval The return value can be one of the following values:
  *         @arg @ref LL_SYSCFG_PB14_PVD
  *         @arg @ref LL_SYSCFG_PB14_ATB1
  */
__STATIC_INLINE uint32_t LL_IO_GetAnalogSwitchControl_PB14(uint32_t feature)
{
  return (uint32_t)(READ_BIT(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_ATB1_nPVD));
}

/**
  * @}
  */

/** @defgroup SYSCFG_LL_RADIO_RXTX_IT_Management RX TX IT_Management
  * @{
  */
/**
  * @brief  Enable Tx Rx Interrupt
  * @rmtoll BLERXTX_IER        LL_SYSCFG_BLERXTX_EnableIT
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_EnableIT(uint32_t Signal)
{
  SET_BIT(SYSCFG->BLERXTX_IER, Signal);
}

/**
  * @brief  Disable Tx Rx Interrupt
  * @rmtoll BLERXTX_IER        LL_SYSCFG_BLERXTX_DisableIT
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_DisableIT(uint32_t Signal)
{
  CLEAR_BIT(SYSCFG->BLERXTX_IER, Signal);
}

/**
  * @brief  Indicate if Tx Rx Interrupt is enabled
  * @rmtoll BLERXTX_IER        LL_SYSCFG_BLERXTX_IsEnabledIT
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLERXTX_IsEnabledIT(uint32_t Signal)
{
  return ((READ_BIT(SYSCFG->BLERXTX_IER, Signal) == (Signal)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SYSCFG_LL_RADIO_EVENT_TYPE_Management Level/Edge Management
  * @{
  */
/**
  * @brief  Set Tx/Rx Interrupt Detection Type
  * @rmtoll BLERXTX_DTR        LL_SYSCFG_BLERXTX_SetType
  * @param  Type This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_BLERXTX_DET_TYPE_EDGE
  *         @arg @ref LL_SYSCFG_BLERXTX_DET_TYPE_LEVEL
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_SetType(uint8_t Type, uint32_t Signal)
{
  if (Type == LL_SYSCFG_BLERXTX_DET_TYPE_EDGE) {
    CLEAR_BIT(SYSCFG->BLERXTX_DTR, Signal);
  } else {
    SET_BIT(SYSCFG->BLERXTX_DTR, Signal);
  }
}

/**
  * @brief  Get Tx/Rx Interrupt Detection Type
  * @rmtoll BLERXTX_DTR        LL_SYSCFG_BLERXTX_GetType
  * @param  Signal This parameter one of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval One of the following values:
  *         @arg @ref LL_SYSCFG_BLERXTX_DET_TYPE_EDGE
  *         @arg @ref LL_SYSCFG_BLERXTX_DET_TYPE_LEVEL
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLERXTX_GetType(uint32_t Signal)
{
  if (READ_BIT(SYSCFG->BLERXTX_DTR, Signal))
    return LL_SYSCFG_BLERXTX_DET_TYPE_LEVEL;

  return LL_SYSCFG_BLERXTX_DET_TYPE_EDGE;
}

/**
  * @} 
  */

/** @defgroup LL_SYSCFG_BLERXTX_SetTrigger Trigger_Management
  * @{
  */
/**
  * @brief  Set Tx Rx Interrupt Trigger 
  * @rmtoll BLERXTX_IBER/BLERXTX__IEVR/BLERXTX__DTR        LL_SYSCFG_BLERXTX_SetTrigger
  * @param  Trigger This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_SetTrigger(uint8_t Trigger, uint32_t Signal)
{  
  if (Trigger == LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE) {
    SET_BIT(SYSCFG->BLERXTX_IBER, Signal);
    CLEAR_BIT(SYSCFG->BLERXTX_IEVR, Signal);
    return;
  }
  if (Trigger == LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE) {
    CLEAR_BIT(SYSCFG->BLERXTX_IBER, Signal);
    SET_BIT(SYSCFG->BLERXTX_IEVR, Signal);
    return;
  }
  if (Trigger == LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE) {
    CLEAR_BIT(SYSCFG->BLERXTX_IBER, Signal);
    CLEAR_BIT(SYSCFG->BLERXTX_IEVR, Signal);
    return;
  }
  if (Trigger == LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL) {
    CLEAR_BIT(SYSCFG->BLERXTX_IBER, Signal);
    CLEAR_BIT(SYSCFG->BLERXTX_IEVR, Signal);
    return;
  }
  if (Trigger == LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL) {
    CLEAR_BIT(SYSCFG->BLERXTX_IBER, Signal);
    SET_BIT(SYSCFG->BLERXTX_IEVR, Signal);
  }  
}

/**
  * @brief  Get Tx Rx Interrupt Trigger
  * @rmtoll BLERXTX_IBER/BLERXTX_IEVR/BLERXTX_DTR        LL_SYSCFG_BLERXTX_GetTrigger
  * @param  Signal This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval The return value can be one of the following values:
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL
  *         @arg @ref LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL
  */
__STATIC_INLINE uint8_t LL_SYSCFG_BLERXTX_GetTrigger(uint32_t Signal)
{
  uint32_t level_setup, level_edge, both_edge;

  level_setup = READ_BIT(SYSCFG->BLERXTX_DTR, Signal);
  level_edge = READ_BIT(SYSCFG->BLERXTX_IEVR, Signal);
  both_edge = READ_BIT(SYSCFG->BLERXTX_IBER, Signal);
    
  if (level_setup) {
    if (level_edge) {
      return LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL;
    } else {
      return LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL;
    }
  } else {
    if (both_edge) {
      return LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE;
    }
    if (level_edge) {
      return LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE;
    }
  }
  return LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE;
}

/**
  * @}
  */

/** @defgroup SYSCFG_LL_EVENT_Flag_Management Flag_Management
  * @{
  */
/**
  * @brief Check if the Tx Rx Interrupt is set or not
  * @note  This bit is cleared by writing a 1 to the bit.
  * @rmtoll BLERXTX_ISCR                   LL_SYSCFG_BLERXTX_IsInterruptPending
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLERXTX_IsInterruptPending(uint32_t Signal)
{
  return ((READ_BIT(SYSCFG->BLERXTX_ISCR, Signal) == (Signal)) ? 1UL : 0UL);
}


/**
  * @brief Clear the Tx Rx Interrupt 
  * @rmtoll BLERXTX_ISCR                   LL_SYSCFG_BLERXTX_ClearInterrupt
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_ClearInterrupt(uint32_t Signal)
{
  WRITE_REG(SYSCFG->BLERXTX_ISCR, Signal);
}


#if defined(SYSCFG_BLERXTX_ISCR_TX_ISEDGE)
/**
  * @brief Returns the TX interrupt edge status on a TX sequence event
  * @rmtoll BLERXTX_ISCR                   LL_SYSCFG_BLETX_EdgeSequence
  * @retval  The return value can be one of the following values:
  *         @arg @ref LL_SYSCFG_BLE_TX_FALLING_EDGE_EVENT
  *         @arg @ref LL_SYSCFG_BLE_TX_RISING_EDGE_EVENT
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLETX_EdgeSequence(void)
{
  return READ_BIT(SYSCFG->BLERXTX_ISCR, SYSCFG_BLERXTX_ISCR_TX_ISEDGE);
}
#endif


#if defined(SYSCFG_BLERXTX_ISCR_RX_ISEDGE)
/**
  * @brief Returns the RX interrupt edge status on a RX sequence event
  * @rmtoll BLERXTX_ISCR                   LL_SYSCFG_BLERX_EdgeSequence
  * @retval  The return value can be one of the following values:
  *         @arg @ref LL_SYSCFG_BLE_RX_FALLING_EDGE_EVENT
  *         @arg @ref LL_SYSCFG_BLE_RX_RISING_EDGE_EVENT
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLERX_EdgeSequence(void)
{
  return READ_BIT(SYSCFG->BLERXTX_ISCR, SYSCFG_BLERXTX_ISCR_RX_ISEDGE);
}
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

#endif /* defined (FLASH) || defined (SYSCFG) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_LL_SYSTEM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
