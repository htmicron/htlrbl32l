/**
  ******************************************************************************
  * @file    system_BlueNRG_LP.h
  * @author  RF Application Team
  * @brief   CMSIS Cortex Device System Source File for BlueNRG_LP devices.  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup bluenrg_lp_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_BLUENRG_LP_H
#define __SYSTEM_BLUENRG_LP_H

#ifdef __cplusplus
 extern "C" {
#endif 
 
#include <stdint.h>
#include "compiler.h"
     
/** @addtogroup Library configuration section
  * @{
  */

/**
  * @brief BlueNRG-LP Family
  */
   

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
  /*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number
  */
#define __BLUENRG_LP_CMSIS_VERSION_MAIN   (0x00U) /*!< [31:24] main version */
#define __BLUENRG_LP_CMSIS_VERSION_SUB1   (0x00U) /*!< [23:16] sub1 version */
#define __BLUENRG_LP_CMSIS_VERSION_SUB2   (0x0AU) /*!< [15:8]  sub2 version */
#define __BLUENRG_LP_CMSIS_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __BLUENRG_LP_CMSIS_DEVICE_VERSION       ((__BLUENRG_LP_CMSIS_VERSION_MAIN << 24)\
                                                |(__BLUENRG_LP_CMSIS_VERSION_SUB1 << 16)\
                                                |(__BLUENRG_LP_CMSIS_VERSION_SUB2 << 8 )\
                                                |(__BLUENRG_LP_CMSIS_VERSION_RC))

/**
  * @}
  */
 
/** @addtogroup System Address
  * @{
  */

/**
 * @brief RAM base address
 */   
#define _MEMORY_RAM_BEGIN_       0x20000000
#ifdef CONFIG_DEVICE_BLUENRG_345
#define _MEMORY_RAM_SIZE_        0x8000            /* 32KB  */
#define _MEMORY_RAM_END_         0x20007FFF
#else
#define _MEMORY_RAM_SIZE_        0x10000           /* 64KB  */
#define _MEMORY_RAM_END_         0x2000FFFF
#endif
   
/**
 * @brief User FLASH base address
 */
#define _MEMORY_FLASH_BEGIN_     0x10040000
#define _MEMORY_FLASH_SIZE_      0x40000          /* 256KB */
#define _MEMORY_FLASH_END_       0x1007FFFF
#define _MEMORY_BYTES_PER_PAGE_  (2048)


/**
 * @brief ROM base address
 */   
#define _MEMORY_ROM_BEGIN_       0x10000000
#define _MEMORY_ROM_SIZE_        0x1800             /* 6KB */
#define _MEMORY_ROM_END_         0x1000017FF

/**
  * @}
  */

/** @addtogroup System Information
  * @{
  */

#define CORE_CM0PLUS

/**
  * @}
  */

/** @defgroup HWConfigOptions Hardware configuration options
  * @{
  */

/*
 * Tip: To avoid modifying this file each time you need to switch between configurations,
 * you can define the configuration in your toolchain compiler preprocessor.
 */

/** @defgroup HWDevice Device Selection
 *  Choose one of the supported devices.
 *  @li CONFIG_DEVICE_BLUENRG_LP for BlueNRG-LP.
 *
 *  Uncomment one of the lines or define the configuration in your toolchain compiler preprocessor.
 *  @note It is mandatory to define one (and only one) of the options.
 *  @{
 */

/* #define CONFIG_DEVICE_BLUENRG_LP */              /*!< BlueNRG-LP */

/**
 * @}
 */

/** @defgroup HW_LS Low Speed Oscillator Configuration
 *  @li CONFIG_HW_LS_RO  to use the internal Ring Oscillator, if a 32 KHz crystal is not present.
 *  @li CONFIG_HW_LS_XTAL  to use the crystal oscillator if a 32 kHz crystal is present.
 *
 *  Uncomment one of the lines or define the configuration in your toolchain compiler preprocessor.
 *  @note It is mandatory to define one (and only one) of the options.
 *  @{
 */

/* #define CONFIG_HW_LS_RO   */ 	/*!< Internal RO */
/* #define CONFIG_HW_LS_XTAL */ 	/*!< External 32KHz crystal */

/**
 * @}
 */

/** @defgroup HW_SMPS SMPS Configuration
 *  Options to select the SMPS switching frequency.
 *  @li CONFIG_HW_SMPS_10uH  to use a 10 uH inductor (4 MHz switching frequency)
 *  @li CONFIG_HW_SMPS_2_2uH  to use a 2.2 uH inductor (8 MHz switching frequency)
 *  @li CONFIG_HW_SMPS_1_5uH  to use a 1.5 uH inductor (8 MHz switching frequency)
 *  @li CONFIG_HW_SMPS_NONE to switch off SMPS, if device is used without inductor.
 *
 *  Uncomment one of the lines or define the configuration in your toolchain compiler preprocessor.
 *  @note It is mandatory to define one (and only one) of the options.
 *  @{
 */

/* #define CONFIG_HW_SMPS_10uH  */  /*!< SMPS inductor: 10 uH */
/* #define CONFIG_HW_SMPS_2_2uH */  /*!< SMPS inductor: 2.2 uH */
/* #define CONFIG_HW_SMPS_1_5uH */  /*!< SMPS inductor: 1.5 uH */
/* #define CONFIG_HW_SMPS_NONE  */  /*!< No inductor */

/**
 * @}
 */

/** @defgroup HW_HSE HSE capacitor configuration
 *  Option to specify the value to tune the capacitors for HSE. Set a value
 *  between 0 and 63.
 *
 *  Uncomment and change the value on the line below or define the configuration
 *  in your toolchain compiler preprocessor.
 *  @note It is mandatory to define this macro.
 *  @{
 */

/* #define CONFIG_HW_HSE_TUNE 32  */

/**
 * @}
 */

/**
 * @}
 */

/** @defgroup ClockConfigOptions System clock and RF clock configuration options
  * @{
  */

/** @addtogroup SYSTEM Clock Configuration 
 *  @{
 */

#define SYSCLK_DIRECT_HSE 0x00   /*!< system clock frequency is 32 MHz DIRECT HSE with HSI OFF */
#define SYSCLK_64M        0x01   /*!< system clock frequency is 64 MHz from PLL */
#define SYSCLK_32M        0x02   /*!< system clock frequency is 32 MHz from PLL */
#define SYSCLK_16M        0x03   /*!< system clock frequency is 16 MHz from PLL */
#define SYSCLK_8M         0x04   /*!< system clock frequency is 8  MHz from PLL */
#define SYSCLK_4M         0x05   /*!< system clock frequency is 4  MHz from PLL */
#define SYSCLK_2M         0x06   /*!< system clock frequency is 2  MHz from PLL */
#define SYSCLK_1M         0x07   /*!< system clock frequency is 1  MHz from PLL */
   
   
/**
 * @}
 */

/** @addtogroup BLE SYSTEM Clock Configuration 
 *  @{
 */

#define BLE_SYSCLK_NONE  0xFF   /*!< BLE system clock disabled */
#define BLE_SYSCLK_32M   0x00   /*!< BLE system clock frequency is 32 MHz */
#define BLE_SYSCLK_16M   0x01   /*!< BLE system clock frequency is 16 MHz */
   
#define RADIO_SYSCLK_NONE BLE_SYSCLK_NONE /*!< Added for compatibility with all the devices */
   
/**
 * @}
 */

/**
 * @}
 */


/** @addtogroup Exported types
  * @{
  */
typedef void( *intfunc )( void );

typedef union { intfunc __fun; void * __ptr; } intvec_elem;

typedef struct RAM_VR_s  
{ 
  uint32_t OTAActivation;
  uint32_t SavedMSP;
  uint32_t WakeupFromSleepFlag;
  uint32_t ResetReason;
  uint32_t AppBase;
  uint32_t Reserved[5];
  uint32_t BlueFlag;
}RAM_VR_TypeDef;

/**
  * @}
  */

/** @addtogroup Exported variables
  * @{
  */
extern const intvec_elem __vector_table[];
extern uint32_t SystemCoreClock;            /*!< System Clock Frequency */
extern RAM_VR_TypeDef RAM_VR;               /*!< Virtual Register map in RAM  */

/**
  * @}
  */

 /** @addtogroup Device Included
  * @{
  */

#include "bluenrg_lpx.h"

/**
  * @}
  */

/** @addtogroup BlueNRG_LP NVIC IRQ Priority
  * @{
  */

#define IRQ_CRITICAL_PRIORITY   0
   
#define IRQ_HIGH_PRIORITY       1
   
#define IRQ_MED_PRIORITY        2
   
#define IRQ_LOW_PRIORITY        3

/**
  * @}
  */

/** @addtogroup BlueNRG_LP Vector Table Location
  * @{
  */

/**@brief Vector Table located in FLASH */
#define CONFIG_IRQ_VECT_FLASH_SECTOR (FLASH_CONFIG_PREMAP)

/**@brief  Vector Table located in RAM */
#define CONFIG_IRQ_VECT_RAM_SECTOR   (FLASH_CONFIG_REMAP)

/**@brief Vector Table Offset Address */
#ifndef VECT_TAB_OFFSET
#define VECT_TAB_OFFSET              0x0U
#endif
   
/**
  * @}
  */
    
/** @addtogroup BlueNRG_LP System Configuration Error
  * @{
  */
#define SYSTEM_CONFIG_SMPS_READY_ERROR 0x01
#define SYSTEM_CONFIG_LSE_READY_ERROR  0x02
#define SYSTEM_CONFIG_LSI_READY_ERROR  0x03
#define SYSTEM_CONFIG_HSE_READY_ERROR  0x04
#define SYSTEM_CONFIG_PLL_READY_ERROR  0x05
#define SYSTEM_CONFIG_DIRECT_HSE_NOT_SUPPORTED 0x06
/**
  * @}
  */
    
/** @addtogroup Tags Tags in interrupt vector table
  * @{
  */
#define BLUE_FLAG_TAG   (0x424C5545)
/**
  * @}
  */
    
#if defined (USE_HAL_DRIVER)
#include "rf_driver_hal.h"
#endif /* USE_HAL_DRIVER */

/* Important note: The __low_level_init() function is critical for waking up from 
   deep sleep and it should not use more that 20 stack positions
   otherwise a stack corruption will occur when waking up from deep sleep.
   For this reason we are saving and restoring the first 20 words of the stack that 
   will be corrupted during the wake-up procedure from deep sleep.
   If the __low_level_init() will be modified, this define shall be modifed according
   the new function implementation
*/
#define CSTACK_PREAMBLE_NUMBER 20


/** @addtogroup BlueNRG_LP_System_Exported_Functions
  * @{
  */

void NMI_IRQHandler(void);
void HardFault_IRQHandler(void);
void SVC_IRQHandler(void);
void PendSV_IRQHandler(void);                         
void SysTick_IRQHandler(void);
void FLASH_IRQHandler(void); 
void RCC_IRQHandler(void);
void PVD_IRQHandler(void);
void I2C1_IRQHandler(void);
#if defined(I2C2)
void I2C2_IRQHandler(void);
#endif
#if defined(SPI1)
void SPI1_IRQHandler(void);
#endif
#if defined(SPI2)
void SPI2_IRQHandler(void);
#endif
void SPI3_IRQHandler(void);
void USART1_IRQHandler(void);
void LPUART1_IRQHandler(void);
#if defined(TIM1)
void TIM1_IRQHandler(void);
#endif
#if defined(TIM2)
void TIM2_IRQHandler(void);
#endif
void RTC_IRQHandler(void);
void ADC_IRQHandler(void);
void PKA_IRQHandler(void);
void UPCONV_IRQHandler(void);
void GPIOA_IRQHandler(void);
void GPIOB_IRQHandler(void);
void DMA_IRQHandler(void);
void BLE_TX_RX_IRQHandler(void);
void BLE_AES_IRQHandler(void);
void BLE_ERROR_IRQHandler(void);
void RADIO_CTRL_IRQHandler(void);
void MR_BLE_IRQHandler(void);
void CPU_WKUP_IRQHandler(void);
void BLE_WKUP_IRQHandler(void);
void BLE_RXTX_SEQ_IRQHandler(void);
#if defined(TIM16)
void TIM16_IRQHandler(void);
#endif
#if defined(TIM17)
void TIM17_IRQHandler(void);
#endif


uint8_t SystemInit(uint8_t SysClk, uint8_t BleSysClk);
uint8_t SystemClockConfig(uint8_t SysClk);
uint8_t RadioClockConfig(uint8_t BleSysClk, uint8_t SysClk);
void MrBleBiasTrimConfig(uint8_t coldStart);
void SystemTimer_TimeoutConfig(uint32_t system_clock_freq, uint32_t timeout, uint8_t enable);
uint8_t SystemTimer_TimeoutExpired(void);
void setInterruptPriority(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_BLUENRG_LP_H */

/**
  * @}
  */
  
/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
