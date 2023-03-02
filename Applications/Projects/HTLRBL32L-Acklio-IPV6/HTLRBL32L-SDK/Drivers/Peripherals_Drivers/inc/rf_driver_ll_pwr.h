/**
  ******************************************************************************
  * @file    rf_driver_ll_pwr.h
  * @author  RF Application Team
  * @brief   Header file of PWR LL module.
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
#ifndef RF_DRIVER_LL_PWR_H
#define RF_DRIVER_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_MODE_PWR MODE PWR
  * @{
  */
#define LL_PWR_MODE_DEEPSTOP               (0x000000000U)
#define LL_PWR_MODE_SHUTDOWN               (PWR_CR1_LPMS)
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RAMRET RAM Retention enable
  * @{
  */
#define LL_PWR_RAMRET_1    PWR_CR2_RAMRET1
#if defined(PWR_CR2_RAMRET2)
#define LL_PWR_RAMRET_2    PWR_CR2_RAMRET2
#endif
#if defined(PWR_CR2_RAMRET3)
#define LL_PWR_RAMRET_3    PWR_CR2_RAMRET3
#endif
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL PVDLEVEL
  * @{
  */
#define LL_PWR_PVDLEVEL_0                  (0x00000000U)                                     /* VPVD0 around 2.0 V */
#define LL_PWR_PVDLEVEL_1                  (PWR_CR2_PVDLS_0)                                 /* VPVD1 around 2.2 V */
#define LL_PWR_PVDLEVEL_2                  (PWR_CR2_PVDLS_1)                                 /* VPVD2 around 2.4 V */
#define LL_PWR_PVDLEVEL_3                  (PWR_CR2_PVDLS_1 | PWR_CR2_PVDLS_0)               /* VPVD3 around 2.5 V */
#define LL_PWR_PVDLEVEL_4                  (PWR_CR2_PLVDS_2)                                 /* VPVD4 around 2.6 V */
#define LL_PWR_PVDLEVEL_5                  (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_0)               /* VPVD5 around 2.8 V */
#define LL_PWR_PVDLEVEL_6                  (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_1)               /* VPVD6 around 2.9 V */
#define LL_PWR_PVDLEVEL_7                  (PWR_CR2_PVDLS)                                   /* External input analog voltage   (Compare internally to VBGP) */
/**
  * @}
  */

/** @defgroup PWR_LL_EW_SOURCE_PORT IO Port for wakeup source 
  * @{
*/
#define LL_PWR_EWS_PORTA   (0x00000000U)                                     /* IO port A to get out from DEEPSTOP mode */
#define LL_PWR_EWS_PORTB   (0x00000001U)                                     /* IO port B to get out from DEEPSTOP mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EW_SOURCE Enable Wakeup Source
  * @{
  */
#define LL_PWE_EWS_ALL            0xFFFFFFFF                /* Enable all the wakeup source                   */
#define LL_PWR_EWS_INT            PWR_CR3_EIWL              /* Enable wakeup on Internal event (RTC)          */
#if defined(PWR_CR3_EIWL2)
#define LL_PWR_EWS_INT2           PWR_CR3_EIWL2             /* Enable wakeup on Internal event 2 (LPUART)     */
#endif
#define LL_PWR_EWS_BLEHOST        PWR_CR3_EWBLEHCPU         /* Enable wakeup on BLE Host CPU event            */
#define LL_PWR_EWS_BLE            PWR_CR3_EWBLE             /* Enable wakeup on BLE event                     */
#define LL_PWE_EWS_EW11           PWR_CR3_EWU11             /* Enable wakeup on PA11 I/O event                */
#define LL_PWE_EWS_EW10           PWR_CR3_EWU10             /* Enable wakeup on PA10 I/O event                */
#define LL_PWE_EWS_EW9            PWR_CR3_EWU9              /* Enable wakeup on PA9 I/O event                 */
#define LL_PWE_EWS_EW8            PWR_CR3_EWU8              /* Enable wakeup on PA8 I/O event                 */
#define LL_PWE_EWS_EW7            PWR_CR3_EWU7              /* Enable wakeup on PB7 I/O event                 */
#define LL_PWE_EWS_EW6            PWR_CR3_EWU6              /* Enable wakeup on PB6 I/O event                 */
#define LL_PWE_EWS_EW5            PWR_CR3_EWU5              /* Enable wakeup on PB5 I/O event                 */
#define LL_PWE_EWS_EW4            PWR_CR3_EWU4              /* Enable wakeup on PB4 I/O event                 */
#define LL_PWE_EWS_EW3            PWR_CR3_EWU3              /* Enable wakeup on PB3 I/O event                 */
#define LL_PWE_EWS_EW2            PWR_CR3_EWU2              /* Enable wakeup on PB2 I/O event                 */
#define LL_PWE_EWS_EW1            PWR_CR3_EWU1              /* Enable wakeup on PB1 I/O event                 */
#define LL_PWE_EWS_EW0            PWR_CR3_EWU0              /* Enable wakeup on PB0 I/O event                 */
#if defined(PWR_CR6_EWU27)
#define LL_PWE_EWS_EW27           (PWR_CR6_EWU27 << 16)     /* Enable wakeup on PA15 I/O event                */
#endif
#if defined(PWR_CR6_EWU26)
#define LL_PWE_EWS_EW26           (PWR_CR6_EWU26 << 16)     /* Enable wakeup on PA14 I/O event                */
#endif
#if defined(PWR_CR6_EWU25) 
#define LL_PWE_EWS_EW25           (PWR_CR6_EWU25 << 16)     /* Enable wakeup on PA13 I/O event                */
#endif
#if defined(PWR_CR6_EWU24)
#define LL_PWE_EWS_EW24           (PWR_CR6_EWU24 << 16)     /* Enable wakeup on PA12 I/O event                */
#endif
#if defined(PWR_CR6_EWU23)
#define LL_PWE_EWS_EW23           (PWR_CR6_EWU23 << 16)     /* Enable wakeup on PB11 I/O event                */
#endif
#if defined(PWR_CR6_EWU22)
#define LL_PWE_EWS_EW22           (PWR_CR6_EWU22 << 16)     /* Enable wakeup on PB10 I/O event                */
#endif
#if defined(PWR_CR6_EWU21)
#define LL_PWE_EWS_EW21           (PWR_CR6_EWU21 << 16)     /* Enable wakeup on PB9 I/O event                 */
#endif
#if defined(PWR_CR6_EWU20)
#define LL_PWE_EWS_EW20           (PWR_CR6_EWU20 << 16)     /* Enable wakeup on PB8 I/O event                 */
#endif
#define LL_PWE_EWS_EW19           (PWR_CR6_EWU19 << 16)     /* Enable wakeup on LP-PA7 or LPS-PB15 I/O event  */
#define LL_PWE_EWS_EW18           (PWR_CR6_EWU18 << 16)     /* Enable wakeup on LP-PA6 or LPS-PB14 I/O event  */
#define LL_PWE_EWS_EW17           (PWR_CR6_EWU17 << 16)     /* Enable wakeup on LP-PA5 or LPS-PB13 I/O event  */
#define LL_PWE_EWS_EW16           (PWR_CR6_EWU16 << 16)     /* Enable wakeup on LP-PA4 or LPS-PB12 I/O event  */
#define LL_PWE_EWS_EW15           (PWR_CR6_EWU15 << 16)     /* Enable wakeup on PA3 I/O event                 */
#define LL_PWE_EWS_EW14           (PWR_CR6_EWU14 << 16)     /* Enable wakeup on PA2 I/O event                 */
#define LL_PWE_EWS_EW13           (PWR_CR6_EWU13 << 16)     /* Enable wakeup on PA1 I/O event                 */
#define LL_PWE_EWS_EW12           (PWR_CR6_EWU12 << 16)     /* Enable wakeup on PA0 I/O event                 */

/**
  * @}
  */
  
/** @defgroup PWR_LL_EC_IO_CFG IOs PU/PD configuration
  * @{
  */
#define LL_PWR_PUPD_IO0          (uint32_t)(1U << 0U)     /*!< IO0  */
#define LL_PWR_PUPD_IO1          (uint32_t)(1U << 1U)     /*!< IO1  */
#define LL_PWR_PUPD_IO2          (uint32_t)(1U << 2U)     /*!< IO2  */
#define LL_PWR_PUPD_IO3          (uint32_t)(1U << 3U)     /*!< IO3  */
#define LL_PWR_PUPD_IO4          (uint32_t)(1U << 4U)     /*!< IO4  */
#define LL_PWR_PUPD_IO5          (uint32_t)(1U << 5U)     /*!< IO5  */
#define LL_PWR_PUPD_IO6          (uint32_t)(1U << 6U)     /*!< IO6  */
#define LL_PWR_PUPD_IO7          (uint32_t)(1U << 7U)     /*!< IO7  */
#define LL_PWR_PUPD_IO8          (uint32_t)(1U << 8U)     /*!< IO8  */
#define LL_PWR_PUPD_IO9          (uint32_t)(1U << 9U)     /*!< IO9  */
#define LL_PWR_PUPD_IO10         (uint32_t)(1U << 10U)    /*!< IO10  */
#define LL_PWR_PUPD_IO11         (uint32_t)(1U << 11U)    /*!< IO11  */
#define LL_PWR_PUPD_IO12         (uint32_t)(1U << 12U)    /*!< IO12  */
#define LL_PWR_PUPD_IO13         (uint32_t)(1U << 13U)    /*!< IO13  */
#define LL_PWR_PUPD_IO14         (uint32_t)(1U << 14U)    /*!< IO14  */
#define LL_PWR_PUPD_IO15         (uint32_t)(1U << 15U)    /*!< IO15  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_IO_CFG IOs PU/PD configuration
  * @{
  */
#define LL_PWR_WUP_RISIEDG (0x000000000U)   /* Detection of wakeup event on rising edge. */
#define LL_PWR_WUP_FALLEDG (0x000000001U)   /* Detection of wakeup event on falling edge. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_IO_OUT_CFG PA4-PA11 output configuration during DEEPSTOP
  * @{
  */
#define LL_PWR_IOCFG_BYP        (0x000000000U)   /* BYPASS mode. The I/O mode is controlled by the GPIO block 
                                                    registers in active mode and switch to input mode 
                                                    during DEESPTOP state.                                        */
#define LL_PWR_IOCFG_RTC        (0x000000001U)   /* RTC_OUT signal for PA11 and PA8 */
#define LL_PWR_IOCFG_LCO        (0x000000001U)   /* LCO output signal for PA10 and PA9 */
#define LL_PWR_IOCFG_LOW        (0x000000002U)   /* I/O drives a low level in both active and DEEPSTOP modes      */
#define LL_PWR_IOCFG_HIGH       (0x000000003U)   /* I/O drives a high level in both active and DEEPSTOP modes     */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_IO_LATCH_BOOT PA8-PA11 I/Os value latched at POR.
  * @{
  */
#define LL_PWR_PA8_LATCH_POR    PWR_SR2_IOBOOTVAL_0 /* PA8  input value latched at POR. */
#define LL_PWR_PA9_LATCH_POR    PWR_SR2_IOBOOTVAL_1 /* PA9  input value latched at POR. */
#define LL_PWR_PA10_LATCH_POR   PWR_SR2_IOBOOTVAL_2 /* PA10 input value latched at POR. */
#define LL_PWR_PA11_LATCH_POR   PWR_SR2_IOBOOTVAL_3 /* PA11 input value latched at POR. */
/**
  * @}
  */
    
/** @defgroup PWR_LL_EC_IO_LATCH_BOOT PB12-PB15 I/Os value latched at POR.
  * @{
  */
#if defined(PWR_SR2_IOBOOTVAL2_0)
#define LL_PWR_PB12_LATCH_POR   PWR_SR2_IOBOOTVAL2_0 /* PB12  input value latched at POR. */
#endif
#if defined(PWR_SR2_IOBOOTVAL2_1)
#define LL_PWR_PB13_LATCH_POR   PWR_SR2_IOBOOTVAL2_1 /* PB13  input value latched at POR. */
#endif
#if defined(PWR_SR2_IOBOOTVAL2_2)
#define LL_PWR_PB14_LATCH_POR   PWR_SR2_IOBOOTVAL2_2 /* PB14  input value latched at POR. */
#endif
#if defined(PWR_SR2_IOBOOTVAL2_3)
#define LL_PWR_PB15_LATCH_POR   PWR_SR2_IOBOOTVAL2_3 /* PB15  input value latched at POR. */
#endif
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_MODE SMPS Mode
  * @{
  */
#define LL_PWR_SMPS       (0x000000000U)   /* SMPS is enabled     */
#define LL_PWR_NO_SMPS    PWR_CR5_NOSMPS   /* SMPS is disabled    */
/**
  * @}
  */
  
/** @defgroup PWR_LL_EC_SMPS_PRECHARGE_MODE SMPS PRECHARGE Mode
  * @{
  */
#define LL_PWR_NO_SMPS_PRECHARGE    (0x000000000U)     /* SMPS not in pecharge mode     */
#define LL_PWR_SMPS_PRECHARGE       PWR_CR5_SMPSFBYP   /* SMPS is disabled and bypassed in precharge mode    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_OPEN_MODE SMPS OPEN Mode during DEEPSTOP
  * @{
  */
#define LL_PWR_NO_SMPS_LPOPEN    (0x000000000U)      /* In DEEPSTOP, the SMPS is in PRECHARGE mode with output connected to VDDIO */
#define LL_PWR_SMPS_LPOPEN       PWR_CR5_SMPSLPOPEN  /* In DEEPSTOP, the SMPS is disabled with floating output                    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_BOM SMPS BOM
  * @{
  */
#define LL_PWR_SMPS_BOM1       (0x000000000U)        
#define LL_PWR_SMPS_BOM2       PWR_CR5_SMPSBOMSEL_0  
#define LL_PWR_SMPS_BOM3       PWR_CR5_SMPSBOMSEL_1  
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_OUTLVL SMPS Output Level
  * @{
  */
#define LL_PWR_SMPS_OUTLVL_1V2               (0x000000000U)
#define LL_PWR_SMPS_OUTLVL_1V25              (PWR_CR5_SMPSLVL_0)
#define LL_PWR_SMPS_OUTLVL_1V3               (PWR_CR5_SMPSLVL_1)
#define LL_PWR_SMPS_OUTLVL_1V35              (PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)
#define LL_PWR_SMPS_OUTLVL_1V4               (PWR_CR5_SMPSLVL_2)
#define LL_PWR_SMPS_OUTLVL_1V45              (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)
#define LL_PWR_SMPS_OUTLVL_1V5               (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1)
#define LL_PWR_SMPS_OUTLVL_1V55              (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)
#define LL_PWR_SMPS_OUTLVL_1V6               (PWR_CR5_SMPSLVL_3)
#define LL_PWR_SMPS_OUTLVL_1V65              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_0)
#define LL_PWR_SMPS_OUTLVL_1V7               (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1)
#define LL_PWR_SMPS_OUTLVL_1V75              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)
#define LL_PWR_SMPS_OUTLVL_1V8               (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2)
#define LL_PWR_SMPS_OUTLVL_1V85              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)
#define LL_PWR_SMPS_OUTLVL_1V9               (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1)
#define LL_PWR_SMPS_OUTLVL_1V95              (PWR_CR5_SMPSLVL)
/**
  * @}
  */

#if defined(PWR_CR5_SMPS_PRECH_CUR_SEL)
/** @defgroup PWR_LL_EC_SMPS_PRECHARGE_LIMIT_CURRENT Select SMPS PRECHARGE limit current
  * @{
  */
#define LL_PWR_SMPS_PRECH_LIMIT_CUR_2_5     (0x000000000U)
#define LL_PWR_SMPS_PRECH_LIMIT_CUR_5       (PWR_CR5_SMPS_PRECH_CUR_SEL_0)
#define LL_PWR_SMPS_PRECH_LIMIT_CUR_10      (PWR_CR5_SMPS_PRECH_CUR_SEL_1)
#define LL_PWR_SMPS_PRECH_LIMIT_CUR_20      (PWR_CR5_SMPS_PRECH_CUR_SEL_0|PWR_CR5_SMPS_PRECH_CUR_SEL_1)
/**
  * @}
  */
#endif

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable the BOR reset supervising during SHUTDOWN mode.
  * @rmtoll CR1          ENSDNBOR           LL_PWR_EnableBORinSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBORinSDN(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_ENSDNBOR);
}

/**
  * @brief  Disable the BOR reset supervising during SHUTDOWN mode.
  * @rmtoll CR1          ENSDNBOR           LL_PWR_DisableBORinSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBORinSDN(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_ENSDNBOR);
}

/**
  * @brief  Checks if BOR is enabled or disabled during SHUTDOWN mode.
  * @rmtoll CR1         ENSDNBOR      LL_PWR_IsEnabledBORinSDN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBORinSDN(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_ENSDNBOR) == (PWR_CR1_ENSDNBOR)) ? 1UL : 0UL);
}

/**
  * @brief  Select the low-power mode.
  * @rmtoll CR1          LPMS           LL_PWR_LowPowerMode
  * @param  selection Low Power Mode Selection. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_DEEPSTOP
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_LowPowerMode(uint32_t selection)
{
  SET_BIT(PWR->CR1, selection);
}

#if defined(PWR_CR2_LSILPMUFEN)
/**
  * @brief  LSI always enabled. Instead to be enabled/disabled by hardware depending
  *         on the analog LPMU block needs.
  * @rmtoll CR2          LSILPMUFEN           LL_PWR_EnableLSILPMU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableLSILPMU(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_LSILPMUFEN);
}

/**
  * @brief  Disable the LSI always enabled. With this setting the LSI LPMU is automatically enabled/disabled
  *         by hardware depending on the analog LPMU block needs.
  * @rmtoll CR2          LSILPMUFEN           LL_PWR_DisableLSILPMU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableLSILPMU(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_LSILPMUFEN);
}

/**
  * @brief  Checks if LSI LPMU is enabled or disabled.
  * @rmtoll CR2         LSILPMUFEN     LL_PWR_IsEnabledLSILPMU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledLSILPMU(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_LSILPMUFEN) == (PWR_CR2_LSILPMUFEN)) ? 1UL : 0UL);
}
#endif

#if defined(PWR_CR2_ENTS)
/**
  * @brief  Enabled the temperature sensor.
  * @rmtoll CR2          ENTS           LL_PWR_EnableTempSens
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableTempSens(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_ENTS);
}

/**
  * @brief  Disable the temperature sensor.
  * @rmtoll CR2          ENTS           LL_PWR_DisableTempSens
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableTempSens(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_ENTS);
}

/**
  * @brief  Checks if temperature sensor is enabled or disabled.
  * @rmtoll CR2         ENTS     LL_PWR_IsEnabledTempSens
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledTempSens(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_ENTS) == (PWR_CR2_ENTS)) ? 1UL : 0UL);
}
#endif

/**
  * @brief  Enable the RAM bank retention.
  * @rmtoll CR2         RAMRET1/RAMRET2/RAMRET3      LL_PWR_EnableRAMBankRet
  * @param  banks RAM bank selection. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_RAMRET_1
  *         @arg @ref LL_PWR_RAMRET_2
  *         @arg @ref LL_PWR_RAMRET_3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableRAMBankRet(uint32_t banks)
{
  SET_BIT(PWR->CR2, banks);
}

/**
  * @brief  Get the RAM banks retention selected.
  * @rmtoll CR2         RAMRET1/RAMRET2/RAMRET3      LL_PWR_GetRAMBankRet
  * @retval RAM bank selection. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_RAMRET_1
  *         @arg @ref LL_PWR_RAMRET_2
  *         @arg @ref LL_PWR_RAMRET_3
  */
__STATIC_INLINE uint32_t LL_PWR_GetRAMBankRet(void)
{
  uint32_t ram_ret;
  
  ram_ret = READ_BIT(PWR->CR2, (PWR_CR2_RAMRET1));
#if defined(PWR_CR2_RAMRET2)
  ram_ret |= READ_BIT(PWR->CR2, (PWR_CR2_RAMRET2));
#endif
#if defined(PWR_CR2_RAMRET3)
  ram_ret |= READ_BIT(PWR->CR2, (PWR_CR2_RAMRET3));
#endif  
  return ram_ret;
}

/**
  * @brief  Disable the RAM bank retention.
  * @rmtoll CR2         RAMRET1/RAMRET2/RAMRET3      LL_PWR_DisableRAMBankRet
  * @param  banks RAM bank selection. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_RAMRET_1
  *         @arg @ref LL_PWR_RAMRET_2
  *         @arg @ref LL_PWR_RAMRET_3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableRAMBankRet(uint32_t banks)
{
  CLEAR_BIT(PWR->CR2, banks);
}

/**
  * @brief  Enable the PVD (Programmable Voltage Detector).
  * @rmtoll CR2          PVDE           LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Disable the PVD (Programmable Voltage Detector).
  * @rmtoll CR2          PVDE           LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Checks if PVD is enabled or disabled.
  * @rmtoll CR2         PVDE      LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_PVDE) == (PWR_CR2_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Set PVD voltage level.
  * @rmtoll CR2         PVDLS      LL_PWR_SetPVDLevel
  * @param  level PVD voltage level selection. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t level)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_PVDLS, level);
}

/**
  * @brief  Get PVD voltage level.
  * @rmtoll CR2         PVDLS      LL_PWR_GetPVDLevel
  * @retval PVD voltage level selection. The parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR2, PWR_CR2_PVDLS));
}

/**
  * @brief  Enable Wakeup Source to get out of DEEPSTOP mode.
  * @rmtoll CR3/CR6               LL_PWR_EnableWakeupSource
  * @param  wakeup_sources Enable the wakeup sources. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_EWS_INT
  *         @arg @ref LL_PWR_EWS_INT2
  *         @arg @ref LL_PWR_EWS_BLEHOST 
  *         @arg @ref LL_PWR_EWS_BLE     
  *         @arg @ref LL_PWE_EWS_EW27
  *         @arg @ref LL_PWE_EWS_EW26
  *         @arg @ref LL_PWE_EWS_EW25
  *         @arg @ref LL_PWE_EWS_EW24
  *         @arg @ref LL_PWE_EWS_EW23
  *         @arg @ref LL_PWE_EWS_EW22
  *         @arg @ref LL_PWE_EWS_EW21
  *         @arg @ref LL_PWE_EWS_EW20
  *         @arg @ref LL_PWE_EWS_EW19
  *         @arg @ref LL_PWE_EWS_EW18
  *         @arg @ref LL_PWE_EWS_EW17
  *         @arg @ref LL_PWE_EWS_EW16
  *         @arg @ref LL_PWE_EWS_EW15
  *         @arg @ref LL_PWE_EWS_EW14
  *         @arg @ref LL_PWE_EWS_EW13
  *         @arg @ref LL_PWE_EWS_EW12
  *         @arg @ref LL_PWE_EWS_EW11    
  *         @arg @ref LL_PWE_EWS_EW10    
  *         @arg @ref LL_PWE_EWS_EW9     
  *         @arg @ref LL_PWE_EWS_EW8     
  *         @arg @ref LL_PWE_EWS_EW7     
  *         @arg @ref LL_PWE_EWS_EW6     
  *         @arg @ref LL_PWE_EWS_EW5     
  *         @arg @ref LL_PWE_EWS_EW4     
  *         @arg @ref LL_PWE_EWS_EW3     
  *         @arg @ref LL_PWE_EWS_EW2     
  *         @arg @ref LL_PWE_EWS_EW1     
  *         @arg @ref LL_PWE_EWS_EW0
  * @retval None
  *         LL_PWE_EWS_EW21, LL_PWE_EWS_EW22, LL_PWE_EWS_EW23, LL_PWE_EWS_EW24, 
  *         LL_PWE_EWS_EW25, LL_PWE_EWS_EW26 and LL_PWE_EWS_EW27
  *         For BlueNRG-LP device is not valid LL_PWR_EWS_INT2
  */
__STATIC_INLINE void LL_PWR_EnableWakeupSource(uint32_t wakeup_sources)
{
  SET_BIT(PWR->CR3, (wakeup_sources & 0x0000FFFF));
  SET_BIT(PWR->CR6, (wakeup_sources >> 16));
}

/**
  * @brief  Disable Wakeup Source to get out of DEEPSTOP mode.
  * @rmtoll CR3/CR6               LL_PWR_DisableWakeupSource
  * @param  wakeup_sources Disable the wakeup sources. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_EWS_INT
  *         @arg @ref LL_PWR_EWS_BLEHOST 
  *         @arg @ref LL_PWR_EWS_BLE     
  *         @arg @ref LL_PWE_EWS_EW27
  *         @arg @ref LL_PWE_EWS_EW26
  *         @arg @ref LL_PWE_EWS_EW25
  *         @arg @ref LL_PWE_EWS_EW24
  *         @arg @ref LL_PWE_EWS_EW23
  *         @arg @ref LL_PWE_EWS_EW22
  *         @arg @ref LL_PWE_EWS_EW21
  *         @arg @ref LL_PWE_EWS_EW20
  *         @arg @ref LL_PWE_EWS_EW19
  *         @arg @ref LL_PWE_EWS_EW18
  *         @arg @ref LL_PWE_EWS_EW17
  *         @arg @ref LL_PWE_EWS_EW16
  *         @arg @ref LL_PWE_EWS_EW15
  *         @arg @ref LL_PWE_EWS_EW14
  *         @arg @ref LL_PWE_EWS_EW13
  *         @arg @ref LL_PWE_EWS_EW12
  *         @arg @ref LL_PWE_EWS_EW11    
  *         @arg @ref LL_PWE_EWS_EW10    
  *         @arg @ref LL_PWE_EWS_EW9     
  *         @arg @ref LL_PWE_EWS_EW8     
  *         @arg @ref LL_PWE_EWS_EW7     
  *         @arg @ref LL_PWE_EWS_EW6     
  *         @arg @ref LL_PWE_EWS_EW5     
  *         @arg @ref LL_PWE_EWS_EW4     
  *         @arg @ref LL_PWE_EWS_EW3     
  *         @arg @ref LL_PWE_EWS_EW2     
  *         @arg @ref LL_PWE_EWS_EW1     
  *         @arg @ref LL_PWE_EWS_EW0
  * @retval None
  *         LL_PWE_EWS_EW21, LL_PWE_EWS_EW22, LL_PWE_EWS_EW23, LL_PWE_EWS_EW24, 
  *         LL_PWE_EWS_EW25, LL_PWE_EWS_EW26 and LL_PWE_EWS_EW27
  *         For BlueNRG-LP device is not valid LL_PWR_EWS_INT2
  */
__STATIC_INLINE void LL_PWR_DisableWakeupSource(uint32_t wakeup_sources)
{
  CLEAR_BIT(PWR->CR3, (wakeup_sources & 0x0000FFFF));
  CLEAR_BIT(PWR->CR6, (wakeup_sources >> 16));
}

/**
  * @brief  Is Wakeup Source enabled.
  * @rmtoll CR3/CR6               LL_PWR_IsEnabledWakeupSource
  * @param  wakeup_sources Disable the wakeup sources. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_EWS_INT
  *         @arg @ref LL_PWR_EWS_INT2
  *         @arg @ref LL_PWR_EWS_BLEHOST 
  *         @arg @ref LL_PWR_EWS_BLE     
  *         @arg @ref LL_PWE_EWS_EW27
  *         @arg @ref LL_PWE_EWS_EW26
  *         @arg @ref LL_PWE_EWS_EW25
  *         @arg @ref LL_PWE_EWS_EW24
  *         @arg @ref LL_PWE_EWS_EW23
  *         @arg @ref LL_PWE_EWS_EW22
  *         @arg @ref LL_PWE_EWS_EW21
  *         @arg @ref LL_PWE_EWS_EW20
  *         @arg @ref LL_PWE_EWS_EW19
  *         @arg @ref LL_PWE_EWS_EW18
  *         @arg @ref LL_PWE_EWS_EW17
  *         @arg @ref LL_PWE_EWS_EW16
  *         @arg @ref LL_PWE_EWS_EW15
  *         @arg @ref LL_PWE_EWS_EW14
  *         @arg @ref LL_PWE_EWS_EW13
  *         @arg @ref LL_PWE_EWS_EW12
  *         @arg @ref LL_PWE_EWS_EW11    
  *         @arg @ref LL_PWE_EWS_EW10    
  *         @arg @ref LL_PWE_EWS_EW9     
  *         @arg @ref LL_PWE_EWS_EW8     
  *         @arg @ref LL_PWE_EWS_EW7     
  *         @arg @ref LL_PWE_EWS_EW6     
  *         @arg @ref LL_PWE_EWS_EW5     
  *         @arg @ref LL_PWE_EWS_EW4     
  *         @arg @ref LL_PWE_EWS_EW3     
  *         @arg @ref LL_PWE_EWS_EW2     
  *         @arg @ref LL_PWE_EWS_EW1     
  *         @arg @ref LL_PWE_EWS_EW0
  * @retval State of bit (1 or 0).
  *         LL_PWE_EWS_EW21, LL_PWE_EWS_EW22, LL_PWE_EWS_EW23, LL_PWE_EWS_EW24, 
  *         LL_PWE_EWS_EW25, LL_PWE_EWS_EW26 and LL_PWE_EWS_EW27
  *         For BlueNRG-LP device is not valid LL_PWR_EWS_INT2
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeupSource(uint32_t wakeup_sources)
{
  return ((READ_BIT(PWR->CR3, (wakeup_sources & 0x0000FFFF)) == (wakeup_sources & 0x0000FFFF)) &&
          (READ_BIT(PWR->CR6, (wakeup_sources >> 16)) == (wakeup_sources >> 16)) ? 1UL : 0UL);
}

/**
  * @brief  Set the polarity for the I/Os wakeup sources.
  * @rmtoll CR4/CR7               LL_PWR_SetWakeupIOPolarity
  * @param  IO IO to configure. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWE_EWS_EW27
  *         @arg @ref LL_PWE_EWS_EW26
  *         @arg @ref LL_PWE_EWS_EW25
  *         @arg @ref LL_PWE_EWS_EW24
  *         @arg @ref LL_PWE_EWS_EW23
  *         @arg @ref LL_PWE_EWS_EW22
  *         @arg @ref LL_PWE_EWS_EW21
  *         @arg @ref LL_PWE_EWS_EW20
  *         @arg @ref LL_PWE_EWS_EW19
  *         @arg @ref LL_PWE_EWS_EW18
  *         @arg @ref LL_PWE_EWS_EW17
  *         @arg @ref LL_PWE_EWS_EW16
  *         @arg @ref LL_PWE_EWS_EW15
  *         @arg @ref LL_PWE_EWS_EW14
  *         @arg @ref LL_PWE_EWS_EW13
  *         @arg @ref LL_PWE_EWS_EW12
  *         @arg @ref LL_PWE_EWS_EW11
  *         @arg @ref LL_PWE_EWS_EW10
  *         @arg @ref LL_PWE_EWS_EW9
  *         @arg @ref LL_PWE_EWS_EW8
  *         @arg @ref LL_PWE_EWS_EW7
  *         @arg @ref LL_PWE_EWS_EW6
  *         @arg @ref LL_PWE_EWS_EW5
  *         @arg @ref LL_PWE_EWS_EW4
  *         @arg @ref LL_PWE_EWS_EW3
  *         @arg @ref LL_PWE_EWS_EW2
  *         @arg @ref LL_PWE_EWS_EW1
  *         @arg @ref LL_PWE_EWS_EW0
  * @param  polarity IO polarity to configure. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WUP_RISIEDG 
  *         @arg @ref LL_PWR_WUP_FALLEDG 
  * @retval None
  *         LL_PWE_EWS_EW21, LL_PWE_EWS_EW22, LL_PWE_EWS_EW23, LL_PWE_EWS_EW24, 
  *         LL_PWE_EWS_EW25, LL_PWE_EWS_EW26 and LL_PWE_EWS_EW27
  */
__STATIC_INLINE void LL_PWR_SetWakeupIOPolarity(uint32_t IO, uint32_t polarity)
{
  if (polarity == LL_PWR_WUP_FALLEDG)
  {
    SET_BIT(PWR->CR4, (IO & 0x0000FFFF));
    SET_BIT(PWR->CR7, (IO >> 16));
  } else {
    CLEAR_BIT(PWR->CR4, (IO & 0x0000FFFF));
    CLEAR_BIT(PWR->CR7, (IO >> 16));;
  }
}

/**
  * @brief  Get the polarity for the I/Os wakeup sources.
  * @rmtoll CR4/CR7               LL_PWR_GetWakeupIOPolarity
  * @param  IO IO configured. This parameter can be one of the following values:
  *         @arg @ref LL_PWE_EWS_EW27
  *         @arg @ref LL_PWE_EWS_EW26
  *         @arg @ref LL_PWE_EWS_EW25
  *         @arg @ref LL_PWE_EWS_EW24
  *         @arg @ref LL_PWE_EWS_EW23
  *         @arg @ref LL_PWE_EWS_EW22
  *         @arg @ref LL_PWE_EWS_EW21
  *         @arg @ref LL_PWE_EWS_EW20
  *         @arg @ref LL_PWE_EWS_EW19
  *         @arg @ref LL_PWE_EWS_EW18
  *         @arg @ref LL_PWE_EWS_EW17
  *         @arg @ref LL_PWE_EWS_EW16
  *         @arg @ref LL_PWE_EWS_EW15
  *         @arg @ref LL_PWE_EWS_EW14
  *         @arg @ref LL_PWE_EWS_EW13
  *         @arg @ref LL_PWE_EWS_EW12
  *         @arg @ref LL_PWE_EWS_EW11
  *         @arg @ref LL_PWE_EWS_EW10
  *         @arg @ref LL_PWE_EWS_EW9
  *         @arg @ref LL_PWE_EWS_EW8
  *         @arg @ref LL_PWE_EWS_EW7
  *         @arg @ref LL_PWE_EWS_EW6
  *         @arg @ref LL_PWE_EWS_EW5
  *         @arg @ref LL_PWE_EWS_EW4
  *         @arg @ref LL_PWE_EWS_EW3
  *         @arg @ref LL_PWE_EWS_EW2
  *         @arg @ref LL_PWE_EWS_EW1
  *         @arg @ref LL_PWE_EWS_EW0
  * @retval The IO polarity. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WUP_RISIEDG 
  *         @arg @ref LL_PWR_WUP_FALLEDG 
  *         LL_PWE_EWS_EW21, LL_PWE_EWS_EW22, LL_PWE_EWS_EW23, LL_PWE_EWS_EW24, 
  *         LL_PWE_EWS_EW25, LL_PWE_EWS_EW26 and LL_PWE_EWS_EW27
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeupIOPolarity(uint32_t IO)
{
  if (IO & 0x0000FFFF) {
    return (uint32_t)((READ_BIT(PWR->CR4, (IO & 0x0000FFFF))) ? 1UL : 0UL);
  } else {
    return (uint32_t)((READ_BIT(PWR->CR7, (IO >> 16))) ? 1UL : 0UL);
}

}

/**
  * @brief  Get which source woken up the device after a DEEPSTOP.
  * @rmtoll SR1/SR3               LL_PWR_GetWakeupSource
  * @retval Wakeup Source from DEEPSTOP. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_EWS_INT
  *         @arg @ref LL_PWR_EWS_INT2
  *         @arg @ref LL_PWR_EWS_BLEHOST 
  *         @arg @ref LL_PWR_EWS_BLE     
  *         @arg @ref LL_PWE_EWS_EW27
  *         @arg @ref LL_PWE_EWS_EW26
  *         @arg @ref LL_PWE_EWS_EW25
  *         @arg @ref LL_PWE_EWS_EW24
  *         @arg @ref LL_PWE_EWS_EW23
  *         @arg @ref LL_PWE_EWS_EW22
  *         @arg @ref LL_PWE_EWS_EW21
  *         @arg @ref LL_PWE_EWS_EW20
  *         @arg @ref LL_PWE_EWS_EW19
  *         @arg @ref LL_PWE_EWS_EW18
  *         @arg @ref LL_PWE_EWS_EW17
  *         @arg @ref LL_PWE_EWS_EW16
  *         @arg @ref LL_PWE_EWS_EW15
  *         @arg @ref LL_PWE_EWS_EW14
  *         @arg @ref LL_PWE_EWS_EW13
  *         @arg @ref LL_PWE_EWS_EW12
  *         @arg @ref LL_PWE_EWS_EW11    
  *         @arg @ref LL_PWE_EWS_EW10    
  *         @arg @ref LL_PWE_EWS_EW9     
  *         @arg @ref LL_PWE_EWS_EW8     
  *         @arg @ref LL_PWE_EWS_EW7     
  *         @arg @ref LL_PWE_EWS_EW6     
  *         @arg @ref LL_PWE_EWS_EW5     
  *         @arg @ref LL_PWE_EWS_EW4     
  *         @arg @ref LL_PWE_EWS_EW3     
  *         @arg @ref LL_PWE_EWS_EW2     
  *         @arg @ref LL_PWE_EWS_EW1     
  *         @arg @ref LL_PWE_EWS_EW0
  *         LL_PWE_EWS_EW21, LL_PWE_EWS_EW22, LL_PWE_EWS_EW23, LL_PWE_EWS_EW24, 
  *         LL_PWE_EWS_EW25, LL_PWE_EWS_EW26 and LL_PWE_EWS_EW27
  *         For BlueNRG-LP device is not valid LL_PWR_EWS_INT2
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeupSource(void)
{
  uint32_t wakeup_source;
  
  wakeup_source = READ_REG(PWR->SR1) & 0x0000FFFF;
  return (uint32_t)(wakeup_source | (READ_REG(PWR->SR3) << 16));
}

/**
  * @brief  Clear the source that woken up the device after a DEEPSTOP.
  * @rmtoll SR1 /SR3              LL_PWR_ClearWakeupSource
  * @param  source Wakeup Source from DEEPSTOP. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWE_EWS_ALL
  *         @arg @ref LL_PWR_EWS_INT
  *         @arg @ref LL_PWR_EWS_INT2
  *         @arg @ref LL_PWR_EWS_BLEHOST 
  *         @arg @ref LL_PWR_EWS_BLE     
  *         @arg @ref LL_PWE_EWS_EW27
  *         @arg @ref LL_PWE_EWS_EW26
  *         @arg @ref LL_PWE_EWS_EW25
  *         @arg @ref LL_PWE_EWS_EW24
  *         @arg @ref LL_PWE_EWS_EW23
  *         @arg @ref LL_PWE_EWS_EW22
  *         @arg @ref LL_PWE_EWS_EW21
  *         @arg @ref LL_PWE_EWS_EW20
  *         @arg @ref LL_PWE_EWS_EW19
  *         @arg @ref LL_PWE_EWS_EW18
  *         @arg @ref LL_PWE_EWS_EW17
  *         @arg @ref LL_PWE_EWS_EW16
  *         @arg @ref LL_PWE_EWS_EW15
  *         @arg @ref LL_PWE_EWS_EW14
  *         @arg @ref LL_PWE_EWS_EW13
  *         @arg @ref LL_PWE_EWS_EW12     
  *         @arg @ref LL_PWE_EWS_EW11    
  *         @arg @ref LL_PWE_EWS_EW10    
  *         @arg @ref LL_PWE_EWS_EW9     
  *         @arg @ref LL_PWE_EWS_EW8     
  *         @arg @ref LL_PWE_EWS_EW7     
  *         @arg @ref LL_PWE_EWS_EW6     
  *         @arg @ref LL_PWE_EWS_EW5     
  *         @arg @ref LL_PWE_EWS_EW4     
  *         @arg @ref LL_PWE_EWS_EW3     
  *         @arg @ref LL_PWE_EWS_EW2     
  *         @arg @ref LL_PWE_EWS_EW1     
  *         @arg @ref LL_PWE_EWS_EW0
  *         @arg @ref LL_PWE_EWS_ALL
  * @retval None
  *         LL_PWE_EWS_EW21, LL_PWE_EWS_EW22, LL_PWE_EWS_EW23, LL_PWE_EWS_EW24, 
  *         LL_PWE_EWS_EW25, LL_PWE_EWS_EW26 and LL_PWE_EWS_EW27
  *         For BlueNRG-LP device is not valid LL_PWR_EWS_INT2
  */
__STATIC_INLINE void LL_PWR_ClearWakeupSource(uint32_t source)
{
  WRITE_REG(PWR->SR1, (source & 0x0000FFFF));
  WRITE_REG(PWR->SR3, (source >> 16));
}

  
/**
  * @brief  Get IO BOOT value.
  * @rmtoll SR2               LL_PWR_GetIOBootVal
  * @param  IO. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PA8_LATCH_POR
  *         @arg @ref LL_PWR_PA9_LATCH_POR
  *         @arg @ref LL_PWR_PA10_LATCH_POR
  *         @arg @ref LL_PWR_PA11_LATCH_POR
  *         @arg @ref LL_PWR_PB12_LATCH_POR
  *         @arg @ref LL_PWR_PB13_LATCH_POR
  *         @arg @ref LL_PWR_PB14_LATCH_POR
  *         @arg @ref LL_PWR_PB15_LATCH_POR
  * @retval State of pin (1 or 0).
  * @note   For BlueNRG-LP device are not valid LL_PWR_PB12_LATCH_POR,
  *         LL_PWR_PB13_LATCH_POR, LL_PWR_PB14_LATCH_POR, LL_PWR_PB15_LATCH_POR 
  */
__STATIC_INLINE uint32_t LL_PWR_GetIOBootVal(uint32_t IO)
{
  return ((READ_BIT(PWR->SR2, IO) == (IO)) ? 1UL : 0UL);
}

/**
  * @brief  Get the Power voltage Detector Output.
  *         When the Power voltage Detector is enabled (PWRC_CR2.PVDE=1), this bit indicates when
  *         the VDDIO is lower than the selected threshold (through PWRC_CR2.PVDLS bit field).
  * @rmtoll SR2       PWR_SR2_PVDO         LL_PWR_GetPVDO
  * @retval State of bit (1 or 0). 1=The VDDIO is lower than the selected threshold
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDO(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_PVDO) == (PWR_SR2_PVDO)) ? 1UL : 0UL);
}

#if defined(PWR_SR2_REGMS)
/**
  * @brief  Get the Main Regulator ready status.
  * @rmtoll SR2      PWR_SR2_REGMS         LL_PWR_IsMainRegulatorReady
  * @retval State of Main Regulator (1=ready or 0=not ready).
  */
__STATIC_INLINE uint32_t LL_PWR_IsMainRegulatorReady(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGMS) == (PWR_SR2_REGMS)) ? 1UL : 0UL);
}
#endif

/**
  * @brief  Get the Low Power Regulator ready status.
  * @rmtoll SR2      PWR_SR2_REGLPS         LL_PWR_IsLowPowerRegulatorReady
  * @retval State of Low Power Regulator (1=ready or 0=not ready).
  */
__STATIC_INLINE uint32_t LL_PWR_IsLowPowerRegulatorReady(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGLPS) == (PWR_SR2_REGLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS ready status.
  * @rmtoll SR2    PWR_SR2_SMPSRDY      LL_PWR_IsSMPSReady
  * @retval State of SMPS (1=ready or 0=not ready).
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSReady(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY) == (PWR_SR2_SMPSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS RUN mode status.
  * @rmtoll SR2       PWR_SR2_SMPSENR         LL_PWR_IsSMPSinRUNMode
  * @retval SMPS RUN mode status (1=SMPS in RUN mode or 0=in PRECHARGE or NOSMPS mode).
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSinRUNMode(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSENR) == (PWR_SR2_SMPSENR)) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS PRECHARGE mode status.
  * @rmtoll SR2    PWR_SR2_SMPSBYPR     LL_PWR_IsSMPSinPRECHARGEMode
  * @retval SMPS PRECHARGE mode status (1=SMPS regulator is in PRECHARGE mode or 0=NOT in PRECHARGE).
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSinPRECHARGEMode(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSBYPR) == (PWR_SR2_SMPSBYPR)) ? 1UL : 0UL);
}

/**
  * @brief  Set SMPS Mode.
  * @rmtoll CR5          PWR_CR5_NOSMPS           LL_PWR_SetSMPSMode
  * @param mode SMPS Mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS
  *         @arg @ref LL_PWR_NO_SMPS
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_NOSMPS, mode);
}

/**
  * @brief  Get SMPS Mode.
  * @rmtoll CR5          PWR_CR5_NOSMPS           LL_PWR_GetSMPSMode
  * @retval SMPS Mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS
  *         @arg @ref LL_PWR_NO_SMPS
  */
  __STATIC_INLINE uint32_t LL_PWR_GetSMPSMode(void)
{
  return (uint32_t) (READ_BIT(PWR->CR5, PWR_CR5_NOSMPS));
}

/**
  * @brief  Set SMPS in PRECHARGE Mode.
  * @rmtoll CR5          PWR_CR5_SMPSFBYP           LL_PWR_SetSMPSPrechargeMode
  * @param mode SMPS in Precharge Mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_NO_SMPS_PRECHARGE
  *         @arg @ref LL_PWR_SMPS_PRECHARGE
  * @retval None
  */
__STATIC_INLINE void  LL_PWR_SetSMPSPrechargeMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSFBYP, mode);
}

/**
  * @brief  Set SMPS OPEN Mode during DEEPSTOP.
  * @rmtoll CR5          PWR_CR5_NOSMPS           LL_PWR_SetSMPSOpenMode
  * @param  mode SMPS Mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_NO_SMPS_LPOPEN
  *         @arg @ref LL_PWR_SMPS_LPOPEN
  */
__STATIC_INLINE void LL_PWR_SetSMPSOpenMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLPOPEN, mode);
}

/**
  * @brief  Set SMPS BOM
  * @rmtoll CR5   PWR_CR5_SMPSBOMSEL_0/PWR_CR5_SMPSBOMSEL_1    LL_PWR_SetSMPSBOM
  * @param  BOM BOM. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_BOM1
  *         @arg @ref LL_PWR_SMPS_BOM2
  *         @arg @ref LL_PWR_SMPS_BOM3
  */
__STATIC_INLINE void LL_PWR_SetSMPSBOM(uint32_t BOM)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSBOMSEL, BOM);
}

/**
  * @brief  Get SMPS BOM
  * @rmtoll CR5   PWR_CR5_SMPSBOMSEL_0/PWR_CR5_SMPSBOMSEL_1    LL_PWR_GetSMPSBOM
  * @retval BOM. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_BOM1
  *         @arg @ref LL_PWR_SMPS_BOM2
  *         @arg @ref LL_PWR_SMPS_BOM3
  */
__STATIC_INLINE uint32_t LL_PWR_GetSMPSBOM(void)
{
  return (uint32_t) (READ_BIT(PWR->CR5, PWR_CR5_SMPSBOMSEL));
}

/**
  * @brief  Set SMPS Output Level
  * @rmtoll CR5   PWR_CR5_SMPSLVL    LL_PWR_SetSMPSOutputLevel
  * @param  output_level Output Level. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V2
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V25             
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V3              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V35             
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V4              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V45              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V5               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V55              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V6               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V65              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V7               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V75              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V8               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V85              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V9               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V95
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSOutputLevel(uint32_t output_level)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLVL, output_level);
}

/**
  * @brief  Get SMPS Output Level
  * @rmtoll CR5   PWR_CR5_SMPSLVL    LL_PWR_GetSMPSOutputLevel
  * @retval Output Level. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V2
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V25             
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V3              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V35             
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V4              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V45              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V5               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V55              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V6               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V65              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V7               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V75              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V8               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V85              
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V9               
  *         @arg @ref LL_PWR_SMPS_OUTLVL_1V95
  */
__STATIC_INLINE uint32_t LL_PWR_GetSMPSOutputLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR5, PWR_CR5_SMPSLVL));
}

/**
  * @brief  Enable pull-up and pull-down configuration
  * @rmtoll CR1          APC           LL_PWR_EnablePUPDCfg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePUPDCfg(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief  Disable pull-up and pull-down configuration
  * @rmtoll CR1          APC           LL_PWR_DisablePUPDCfg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePUPDCfg(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief  Check if pull-up and pull-down configuration is enabled
  * @rmtoll CR1          APC           LL_PWR_IsEnabledPUPDCfg
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUPDCfg(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_APC) == (PWR_CR1_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the IO pull-up configuration for port A.
  * @rmtoll PUCRA               LL_PWR_EnablePUA
  * @param  IO Pins Pull-up enable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO6, LL_PWR_PUPD_IO7, LL_PWR_PUPD_IO12, LL_PWR_PUPD_IO13,
  *         LL_PWR_PUPD_IO14, LL_PWR_PUPD_IO15
  */
__STATIC_INLINE void LL_PWR_EnablePUA(uint32_t IO)
{
  CLEAR_BIT(PWR->PDCRA, IO); 
  SET_BIT(PWR->PUCRA, IO);
}

/**
  * @brief  Disable the IO pull-up configuration for port A.
  * @rmtoll PUCRA               LL_PWR_DisablePUA
  * @param  IO Pins Pull-up disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO6, LL_PWR_PUPD_IO7, LL_PWR_PUPD_IO12, LL_PWR_PUPD_IO13,
  *         LL_PWR_PUPD_IO14, LL_PWR_PUPD_IO15
  */
__STATIC_INLINE void LL_PWR_DisablePUA(uint32_t IO)
{
  CLEAR_BIT(PWR->PUCRA, IO); 
}

/**
  * @brief  Checks if IO pull-up is enabled or disabled for port A.
  * @rmtoll PUCRA               LL_PWR_IsEnabledPUA
  * @param  IO Pins Pull-up disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval State of bit (1 or 0).
  *         LL_PWR_PUPD_IO6, LL_PWR_PUPD_IO7, LL_PWR_PUPD_IO12, LL_PWR_PUPD_IO13,
  *         LL_PWR_PUPD_IO14, LL_PWR_PUPD_IO15
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUA(uint32_t IO)
{
  return ((READ_BIT(PWR->PUCRA, IO) == (IO)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the IO pull-down configuration for port A.
  * @rmtoll PDCRA               LL_PWR_EnablePDA
  * @param  IO Pins Pull-down enable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO6, LL_PWR_PUPD_IO7, LL_PWR_PUPD_IO12, LL_PWR_PUPD_IO13,
  *         LL_PWR_PUPD_IO14, LL_PWR_PUPD_IO15
  */
__STATIC_INLINE void LL_PWR_EnablePDA(uint32_t IO)
{
  CLEAR_BIT(PWR->PUCRA, IO); 
  SET_BIT(PWR->PDCRA, IO);
}

/**
  * @brief  Disable the IO pull-down configuration for port A.
  * @rmtoll PDCRA               LL_PWR_DisablePDA
  * @param  IO Pins Pull-down disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO6, LL_PWR_PUPD_IO7, LL_PWR_PUPD_IO12, LL_PWR_PUPD_IO13,
  *         LL_PWR_PUPD_IO14, LL_PWR_PUPD_IO15
  */
__STATIC_INLINE void LL_PWR_DisablePDA(uint32_t IO)
{
  CLEAR_BIT(PWR->PDCRA, IO); 
}

/**
  * @brief  Checks if IO pull-down is enabled or disabled for port A.
  * @rmtoll PDCRA               LL_PWR_IsEnabledPDA
  * @param  IO Pins Pull-down disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval State of bit (1 or 0).
  *         LL_PWR_PUPD_IO6, LL_PWR_PUPD_IO7, LL_PWR_PUPD_IO12, LL_PWR_PUPD_IO13,
  *         LL_PWR_PUPD_IO14, LL_PWR_PUPD_IO15
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPDA(uint32_t IO)
{
  return ((READ_BIT(PWR->PDCRA, IO) == (IO)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the IO in NO PULL configuration for port A.
  * @rmtoll PDCRA/PUCRA               LL_PWR_SetNoPullA
  * @param  GPIOx GPIO Port
  * @param  IO Pins No Pull cofiguration. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO6, LL_PWR_PUPD_IO7, LL_PWR_PUPD_IO12, LL_PWR_PUPD_IO13,
  *         LL_PWR_PUPD_IO14, LL_PWR_PUPD_IO15
  */
__STATIC_INLINE void LL_PWR_SetNoPullA(uint32_t IO)
{
  CLEAR_BIT(PWR->PUCRA, IO);
  CLEAR_BIT(PWR->PDCRA, IO);
}

/**
  * @brief  Enable the IO pull-up configuration for port B.
  * @rmtoll PUCRB               LL_PWR_EnablePUB
  * @param  IO Pins Pull-up enable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO9, LL_PWR_PUPD_IO10, LL_PWR_PUPD_IO11
  */
__STATIC_INLINE void LL_PWR_EnablePUB(uint32_t IO)
{
  CLEAR_BIT(PWR->PDCRB, IO); 
  SET_BIT(PWR->PUCRB, IO);
}

/**
  * @brief  Disable the IO pull-up configuration for port B.
  * @rmtoll PUCRB               LL_PWR_DisablePUB
  * @param  IO Pins Pull-up disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO9, LL_PWR_PUPD_IO10, LL_PWR_PUPD_IO11
  */
__STATIC_INLINE void LL_PWR_DisablePUB(uint32_t IO)
{
  CLEAR_BIT(PWR->PUCRB, IO); 
}

/**
  * @brief  Checks if IO pull-up is enabled or disabled for port B.
  * @rmtoll PUCRB               LL_PWR_IsEnabledPUB
  * @param  IO Pins Pull-up disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval State of bit (1 or 0).
  *         LL_PWR_PUPD_IO9, LL_PWR_PUPD_IO10, LL_PWR_PUPD_IO11
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUB(uint32_t IO)
{
  return ((READ_BIT(PWR->PUCRB, IO) == (IO)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the IO pull-down configuration for port B.
  * @rmtoll PDCRB               LL_PWR_EnablePDB
  * @param  IO Pins Pull-down enable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO9, LL_PWR_PUPD_IO10, LL_PWR_PUPD_IO11
  */
__STATIC_INLINE void LL_PWR_EnablePDB(uint32_t IO)
{
  CLEAR_BIT(PWR->PUCRB, IO); 
  SET_BIT(PWR->PDCRB, IO);
}

/**
  * @brief  Disable the IO pull-down configuration for port B.
  * @rmtoll PDCRB               LL_PWR_DisablePDB
  * @param  IO Pins Pull-down disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO9, LL_PWR_PUPD_IO10, LL_PWR_PUPD_IO11
  */
__STATIC_INLINE void LL_PWR_DisablePDB(uint32_t IO)
{
  CLEAR_BIT(PWR->PDCRB, IO); 
}

/**
  * @brief  Checks if IO pull-down is enabled or disabled for port B.
  * @rmtoll PDCRB               LL_PWR_IsEnabledPDB
  * @param  IO Pins Pull-down disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval State of bit (1 or 0).
  *         LL_PWR_PUPD_IO9, LL_PWR_PUPD_IO10, LL_PWR_PUPD_IO11
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPDB(uint32_t IO)
{
  return ((READ_BIT(PWR->PDCRB, IO) == (IO)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the IO in NO PULL configuration for port B.
  * @rmtoll PDCRB/PUCRB               LL_PWR_SetNoPullB
  * @param  GPIOx GPIO Port
  * @param  IO Pins Pull-down disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_PUPD_IO0
  *         @arg @ref LL_PWR_PUPD_IO1
  *         @arg @ref LL_PWR_PUPD_IO2
  *         @arg @ref LL_PWR_PUPD_IO3
  *         @arg @ref LL_PWR_PUPD_IO4
  *         @arg @ref LL_PWR_PUPD_IO5
  *         @arg @ref LL_PWR_PUPD_IO6
  *         @arg @ref LL_PWR_PUPD_IO7
  *         @arg @ref LL_PWR_PUPD_IO8
  *         @arg @ref LL_PWR_PUPD_IO9
  *         @arg @ref LL_PWR_PUPD_IO10
  *         @arg @ref LL_PWR_PUPD_IO11
  *         @arg @ref LL_PWR_PUPD_IO12
  *         @arg @ref LL_PWR_PUPD_IO13
  *         @arg @ref LL_PWR_PUPD_IO14
  *         @arg @ref LL_PWR_PUPD_IO15
  * @retval None
  *         LL_PWR_PUPD_IO9, LL_PWR_PUPD_IO10, LL_PWR_PUPD_IO11
  */
__STATIC_INLINE void LL_PWR_SetNoPullB(uint32_t IO)
{
  CLEAR_BIT(PWR->PUCRB, IO);
  CLEAR_BIT(PWR->PDCRB, IO);
}

#if defined(PWR_IOxCFG_IOCFG4)
/**
  * @brief  Set PA4 during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_SetPA4OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA4OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG4, mode);
}

/**
  * @brief  Get PA4 output during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_GetPA4OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA4OutputinDEEPSTOP(void)
{
  return (uint32_t) (READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG4) >> PWR_IOxCFG_IOCFG4_Pos);
}
#endif

#if defined(PWR_IOxCFG_IOCFG5)
  /**
  * @brief  Set PA5 during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_SetPA5OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA5OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG5, mode);
}

/**
  * @brief  Get PA5 output during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_GetPA5OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA5OutputinDEEPSTOP(void)
{
  return (uint32_t) (READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG5) >> PWR_IOxCFG_IOCFG5_Pos);
}
#endif

#if defined(PWR_IOxCFG_IOCFG6)
/**
  * @brief  Set PA6 during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_SetPA6OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA6OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG6, mode);
}

/**
  * @brief  Get PA6 output during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_GetPA6OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA6OutputinDEEPSTOP(void)
{
  return (uint32_t) (READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG6) >> PWR_IOxCFG_IOCFG6_Pos);
}
#endif

#if defined(PWR_IOxCFG_IOCFG7)
/**
  * @brief  Set PA7 during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_SetPA7OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA7OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG7, mode);
}

/**
  * @brief  Get PA7 output during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_GetPA7OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA7OutputinDEEPSTOP(void)
{
  return (uint32_t) (READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG7) >> PWR_IOxCFG_IOCFG7_Pos);
}
#endif

#if defined(PWR_IOxCFG_IOCFG0)
/**
  * @brief  Set PA8 during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_SetPA8OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA8OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG0, mode);
}

/**
  * @brief  Get PA8 output during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_GetPA8OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA8OutputinDEEPSTOP(void)
{
  return (uint32_t) (READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG0) >> PWR_IOxCFG_IOCFG0_Pos);
}
#endif

#if defined(PWR_IOxCFG_IOCFG1)
/**
  * @brief  Set PA9 during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_SetPA9OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA9OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG1, mode);
}

/**
  * @brief  Get PA9 output during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_GetPA9OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA9OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG1) >> PWR_IOxCFG_IOCFG1_Pos);
}
#endif

#if defined(PWR_IOxCFG_IOCFG2)
/**
  * @brief  Set PA10 during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_SetPA10OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA10OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG2, mode);
}

/**
  * @brief  Get PA10 output during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_GetPA10OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA10OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG2) >> PWR_IOxCFG_IOCFG2_Pos);
}
#endif

#if defined(PWR_IOxCFG_IOCFG3)
/**
  * @brief  Set PA11 during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_SetPA11OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA11OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG3, mode);
}

/**
  * @brief  Get PA11 output during DEEPSTOP mode.
  * @rmtoll IOxCFG               LL_PWR_GetPA11OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA11OutputinDEEPSTOP(void)
{
  return (uint32_t) (READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG3) >> PWR_IOxCFG_IOCFG3_Pos);
}
#endif

/**
  * @brief  Set SMPS trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetSMPSTrim
  * @param  trim SMPS output voltage trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSTrim(uint32_t trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_SMPS_TRIM, ((trim << PWR_ENGTRIM_SMPS_TRIM_Pos) & PWR_ENGTRIM_SMPS_TRIM));
  SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_SMPSTRIMEN);
}

/**
  * @brief  Get SMPS trimming value.
  * @rmtoll TRIMR/ENGTRIM               LL_PWR_GetSMPSTrim
  * @retval SMPS output voltage trimming value
  */
__STATIC_INLINE uint32_t LL_PWR_GetSMPSTrim(void)
{
  if (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_SMPSTRIMEN)) {
    return (uint32_t) (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_SMPS_TRIM) >> PWR_ENGTRIM_SMPS_TRIM_Pos);
  } else {
    return (uint32_t) (READ_BIT(PWR->TRIMR, PWR_TRIMR_SMPS_TRIM) >> PWR_TRIMR_SMPS_TRIM_Pos);
  }
}

/**
  * @brief  Set Main regulator voltage trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetMRTrim
  * @param  trim Main Regulator voltage trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetMRTrim(uint32_t trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_MR, ((trim << PWR_ENGTRIM_TRIM_MR_Pos) & PWR_ENGTRIM_TRIM_MR));
  SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMMREN);
}

/**
  * @brief  Get Main regulator voltage trimming value.
  * @rmtoll TRIMR/ENGTRIM               LL_PWR_GetMRTrim
  * @retval Main regulator voltage trimming value
  */
__STATIC_INLINE uint32_t LL_PWR_GetMRTrim(void)
{
  if (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMMREN)) {
    return (uint32_t) (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_MR) >> PWR_ENGTRIM_TRIM_MR_Pos);
  } else {
    return (uint32_t) (READ_BIT(PWR->TRIMR, PWR_TRIMR_TRIM_MR) >> PWR_TRIMR_TRIM_MR_Pos);
  }
}

#if defined(PWR_ENGTRIM_TRIM_LSI_LPMU) 
/**
  * @brief  Set Low Speed Internal oscillator LPMU trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetLPMULSITrim
  * @param  trim Low Speed Internal oscillator trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetLSILPMUTrim(uint32_t trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_LSI_LPMU, ((trim << PWR_ENGTRIM_TRIM_LSI_LPMU_Pos) & PWR_ENGTRIM_TRIM_LSI_LPMU));
  SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMLSILPMUEN);
}

/**
  * @brief  Get Low Speed Internal oscillator LPMU trimming value.
  * @rmtoll TRIMR/ENGTRIM               LL_PWR_GetLSITrim
  * @retval Low Speed Internal oscillator trimming value
  */
__STATIC_INLINE uint32_t LL_PWR_GetLSILPMUTrim(void)
{
  if (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMLSILPMUEN)) {
    return (uint32_t) (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_LSI_LPMU) >> PWR_ENGTRIM_TRIM_LSI_LPMU_Pos);
  } else {
    return (uint32_t) (READ_BIT(PWR->TRIMR, PWR_TRIMR_TRIM_LSI_LPMU) >> PWR_TRIMR_TRIM_LSI_LPMU_Pos);
  }
}
#endif

#if defined(PWR_ENGTRIM_TRIM_RFDREG) 
/**
  * @brief  Set RF LDO trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetRFDREGTrim
  * @param  trim RF LDO trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRFDREGTrim(uint32_t trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_RFDREG, ((trim << PWR_ENGTRIM_TRIM_RFDREG_Pos) & PWR_ENGTRIM_TRIM_RFDREG));
  SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMRFDREGEN);
}

/**
  * @brief  Get RF LDO trimming value.
  * @rmtoll TRIMR/ENGTRIM               LL_PWR_GetRFDREGTrim
  * @retval RF LDO trimming value
  */
__STATIC_INLINE uint32_t LL_PWR_GetRFDREGTrim(void)
{
  if (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMRFDREGEN)) {
    return (uint32_t) (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_RFDREG) >> PWR_ENGTRIM_TRIM_RFDREG_Pos);
  } else {
    return (uint32_t) (READ_BIT(PWR->TRIMR, PWR_TRIMR_RFD_REG_TRIM) >> PWR_TRIMR_RFD_REG_TRIM_Pos);
  }
}
#endif

/**
  * @}
  */

/** @defgroup PWR_LL_DBG_DEEPSTOP Function to setup the DEEPSTOP2 will be applied instead
  *                               of DEEPSTOP and the debugger features not lost
  * @{
  */
  
/**
  * @brief  Enable the DEEPSTOP2 feature, debugger feature not lost during DEEPSTOP.
  * @rmtoll DBGR               LL_PWR_EnableDEEPSTOP2
  * @param  None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableDEEPSTOP2(void)
{
  SET_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2);
}

/**
  * @brief  Disable the DEEPSTOP2 feature, debugger feature lost during DEEPSTOP.
  * @rmtoll DBGR               LL_PWR_DisableDEEPSTOP2
  * @param  None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableDEEPSTOP2(void)
{
  CLEAR_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2); 
}

/**
  * @brief  Checks if the DEEPSTOP2 feature is enabled or disabled
  * @rmtoll DBGR               LL_PWR_IsEnabledDEEPSTOP2
  * @param  None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDEEPSTOP2(void)
{
  return ((READ_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2) == (PWR_DBGR_DEEPSTOP2)) ? 1UL : 0UL);
}
/**
  * @}
  */

#if defined (PWR_CR2_GPIORET)
/** @defgroup PWR_LL_DEEPSTOP_GPIORET Functions to setup the GPIORET bit. 
  *                                   GPIO retention
  * @{
  */
  
/**
  * @brief  Enable the GPIORET feature, GPIO retain their status during DEEPSTOP 
  *         and exiting from DEEPSTOP.
  * @rmtoll CR2         GPIORET      LL_PWR_EnableGPIORET
  * @param  None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableGPIORET(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_GPIORET);
}

/**
  * @brief  Disable the GPIORET feature, don’t retain their status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         GPIORET      LL_PWR_DisableGPIORET
  * @param  None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableGPIORET(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_GPIORET); 
}

/**
  * @brief  Checks if the GPIO retention in DEEPSTOP feature is enabled or disabled
  * @rmtoll CR2         GPIORET      LL_PWR_IsEnabledGPIORET
  * @param  None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIORET(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_GPIORET) == (PWR_CR2_GPIORET)) ? 1UL : 0UL);
}
/**
  * @}
  */
#endif

#if defined (PWR_CR2_DBGRET)
/** @defgroup PWR_LL_DEEPSTOP_DBGRET Functions to setup the DBGRET bit. 
  *           GPIOA_Pin_2 and GPIOA_Pin_3 retention exiting from DEEPSTOP
  * @{
  */
  
/**
  * @brief  Enable the DBGRET feature, GPIOA_Pin_2 and GPIOA_Pin_3 retain their 
  *         status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         DBGRET      LL_PWR_EnableDBGRET
  * @param  None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableDBGRET(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_DBGRET);
}

/**
  * @brief  Disable the DBGRET feature, GPIOA_Pin_2 and GPIOA_Pin_3 don’t retain 
  *         status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         DBGRET      LL_PWR_DisableDBGRET
  * @param  None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableDBGRET(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_DBGRET); 
}

/**
  * @brief  Checks if the GPIOA_Pin_2 and GPIOA_Pin_3 retention in DEEPSTOP 
  *         feature is enabled or disabled
  * @rmtoll CR2         DBGRET      LL_PWR_IsEnabledDBGRET
  * @param  None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDBGRET(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_DBGRET) == (PWR_CR2_DBGRET)) ? 1UL : 0UL);
}
/**
  * @}
  */
#endif

#if defined(PWR_CR5_SMPS_PRECH_CUR_SEL)
/**
  * @brief  Select SMPS PRECHARGE limit current.
  * @rmtoll CR5               LL_PWR_SetSMPSPrechargeLimitCurrent
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_2_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_10
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_20
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSPrechargeLimitCurrent(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->CR5, PWR_CR5_SMPS_PRECH_CUR_SEL, mode);
}

/**
  * @brief  Get SMPS PRECHARGE limit current selected.
  * @rmtoll CR5               LL_PWR_GetSMPSPrechargeLimitCurrent
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_2_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_10
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_20
  */
__STATIC_INLINE uint32_t LL_PWR_GetSMPSPrechargeLimitCurrent(void)
{
  return (uint32_t) (READ_BIT(PWR->CR5, PWR_CR5_SMPS_PRECH_CUR_SEL) >> PWR_CR5_SMPS_PRECH_CUR_SEL_Pos);
}
#endif

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
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

#endif /* defined(PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_LL_PWR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
