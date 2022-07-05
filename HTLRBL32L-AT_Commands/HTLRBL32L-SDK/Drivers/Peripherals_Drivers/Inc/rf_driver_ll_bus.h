/**
  ******************************************************************************
  * @file    rf_driver_ll_bus.h
  * @author  RF Application Team
  * @brief   Header file of BUS LL module.

  @verbatim
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
        (++) AHB & APB peripherals, 1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB & APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

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
#ifndef RF_DRIVER_LL_BUS_H
#define RF_DRIVER_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup BUS_LL BUS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Constants BUS Exported Constants
  * @{
  */

/** @defgroup BUS_LL_AHB_PERIPH  AHB PERIPH
  * @{
  */
#define LL_AHB_PERIPH_ALL            (RCC_AHBENR_DMAEN|RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOBEN|RCC_AHBENR_CRCEN|RCC_AHBENR_PKAEN|RCC_AHBENR_RNGEN)
#define LL_AHB_PERIPH_DMA            RCC_AHBENR_DMAEN
#define LL_AHB_PERIPH_GPIOA          RCC_AHBENR_GPIOAEN
#define LL_AHB_PERIPH_GPIOB          RCC_AHBENR_GPIOBEN
#define LL_AHB_PERIPH_CRC            RCC_AHBENR_CRCEN
#if defined(PKA)
#define LL_AHB_PERIPH_PKA            RCC_AHBENR_PKAEN
#endif
#define LL_AHB_PERIPH_RNG            RCC_AHBENR_RNGEN
#if defined(AES1)
#define LL_AHB_PERIPH_AES1           RCC_AHBENR_AESEN
#endif
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup BUS_LL_APB0_PERIPH  APB0 PERIPH
  * @{
  */
#define LL_APB0_PERIPH_ALL            (RCC_APB0ENR_TIM1EN|RCC_APB0ENR_SYSCFGEN|RCC_APB0ENR_RTCEN|RCC_APB0ENR_WDGEN)
#if defined(TIM1)
#define LL_APB0_PERIPH_TIM1           RCC_APB0ENR_TIM1EN
#endif
#if defined(TIM2)
#define LL_APB0_PERIPH_TIM2           RCC_APB0ENR_TIM2EN
#endif
#if defined(TIM16)
#define LL_APB0_PERIPH_TIM16          RCC_APB0ENR_TIM16EN
#endif
#if defined(TIM17)
#define LL_APB0_PERIPH_TIM17          RCC_APB0ENR_TIM17EN
#endif
#define LL_APB0_PERIPH_SYSCFG         RCC_APB0ENR_SYSCFGEN
#if defined(LCD)
#define LL_APB0_PERIPH_LCDC           RCC_APB0ENR_LCDCEN
#endif
#if defined(COMP1)
#define LL_APB0_PERIPH_COMP           RCC_APB0ENR_COMPEN
#endif
#if defined(DAC)
#define LL_APB0_PERIPH_DAC            RCC_APB0ENR_DACEN
#endif
#define LL_APB0_PERIPH_RTC            RCC_APB0ENR_RTCEN
#if defined(SCI)
#define LL_APB0_PERIPH_SCI            RCC_APB0ENR_SCIEN
#endif
#define LL_APB0_PERIPH_WDG            RCC_APB0ENR_WDGEN
#if defined(DBGMCU)
#define LL_APB0_PERIPH_DBGMCU         RCC_APB0ENR_DBGMCUEN
#endif
/**
  * @}
  */


/** @defgroup BUS_LL_APB1_PERIPH  APB1 PERIPH
  * @{
  */
#define LL_APB1_PERIPH_ALL            (RCC_APB1ENR_SPI1EN|RCC_APB1ENR_ADCDIGEN|RCC_APB1ENR_ADCANAEN|RCC_APB1ENR_LPUARTEN|RCC_APB1ENR_USARTEN|RCC_APB1ENR_SPI2EN|RCC_APB1ENR_SPI3EN|RCC_APB1ENR_I2C1EN|RCC_APB1ENR_I2C2EN)
#if defined(SPI1) 
#define LL_APB1_PERIPH_SPI1           RCC_APB1ENR_SPI1EN
#endif
#define LL_APB1_PERIPH_ADCDIG         RCC_APB1ENR_ADCDIGEN
#define LL_APB1_PERIPH_ADCANA         RCC_APB1ENR_ADCANAEN
#define LL_APB1_PERIPH_LPUART         RCC_APB1ENR_LPUARTEN
#define LL_APB1_PERIPH_USART          RCC_APB1ENR_USARTEN
#if defined(SPI2) 
#define LL_APB1_PERIPH_SPI2           RCC_APB1ENR_SPI2EN
#endif  
#define LL_APB1_PERIPH_SPI3           RCC_APB1ENR_SPI3EN
#define LL_APB1_PERIPH_I2C1           RCC_APB1ENR_I2C1EN
#if defined(I2C2) 
#define LL_APB1_PERIPH_I2C2           RCC_APB1ENR_I2C2EN
#endif
/**
  * @}
  */

/** @defgroup BUS_LL_APB2_PERIPH  APB2 PERIPH
  * @{
  */
#if defined(BLUE)
#define LL_APB2_PERIPH_ALL            (RCC_APB2ENR_MRBLEEN)
#define LL_APB2_PERIPH_MRBLE          RCC_APB2ENR_MRBLEEN
#endif
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/** @defgroup BUS_LL_Exported_Functions BUS Exported Functions
  * @{
  */

/** @defgroup BUS_LL_EF_AHB AHB
  * @{
  */

/**
  * @brief  Enable AHB peripherals clock.
  * @rmtoll AHBENR      DMAEN        LL_AHB_EnableClock
  *         AHBENR      GPIOAEN      LL_AHB_EnableClock
  *         AHBENR      GPIOBEN      LL_AHB_EnableClock
  *         AHBENR      CRCEN        LL_AHB_EnableClock
  *         AHBENR      PKAEN        LL_AHB_EnableClock
  *         AHBENR      RNGEN        LL_AHB_EnableClock
  *         AHBENR      AESEN        LL_AHB_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB_PERIPH_DMA
  *         @arg @ref LL_AHB_PERIPH_GPIOA
  *         @arg @ref LL_AHB_PERIPH_GPIOB
  *         @arg @ref LL_AHB_PERIPH_CRC
  *         @arg @ref LL_AHB_PERIPH_PKA
  *         @arg @ref LL_AHB_PERIPH_RNG
  *         @arg @ref LL_AHB_PERIPH_AES
  * @retval None
  * @note   LL_AHB_PERIPH_PKA is valid only for BlueNRG-LP 
*/
__STATIC_INLINE void LL_AHB_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHBENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHBENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB peripheral clock is enabled or not
  * @rmtoll AHBENR      DMAEN          LL_AHB_IsEnabledClock
  *         AHBENR      GPIOAEN        LL_AHB_IsEnabledClock
  *         AHBENR      GPIOBEN        LL_AHB_IsEnabledClock
  *         AHBENR      CRCEN          LL_AHB_IsEnabledClock
  *         AHBENR      PAKAEN         LL_AHB_IsEnabledClock
  *         AHBENR      RNGEN          LL_AHB_IsEnabledClock
  *         AHBENR      AESEN          LL_AHB_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB_PERIPH_DMA
  *         @arg @ref LL_AHB_PERIPH_GPIOA
  *         @arg @ref LL_AHB_PERIPH_GPIOB
  *         @arg @ref LL_AHB_PERIPH_CRC
  *         @arg @ref LL_AHB_PERIPH_PKA
  *         @arg @ref LL_AHB_PERIPH_RNG
  *         @arg @ref LL_AHB_PERIPH_AES
  * @retval uint32_t
  * @note   LL_AHB_PERIPH_PKA is valid only for BlueNRG-LP 
*/
__STATIC_INLINE uint32_t LL_AHB_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHBENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB peripherals clock.
  * @rmtoll AHBENR      DMAENN        LL_AHB_DisableClock
  *         AHBENR      GPIOAEN       LL_AHB_DisableClock
  *         AHBENR      GPIOBEN       LL_AHB_DisableClock
  *         AHBENR      CRCEN         LL_AHB_DisableClock
  *         AHBENR      PKAEN         LL_AHB_DisableClock
  *         AHBENR      RNGEN         LL_AHB_DisableClock
  *         AHBENR      AESEN         LL_AHB_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB_PERIPH_DMA
  *         @arg @ref LL_AHB_PERIPH_GPIOA
  *         @arg @ref LL_AHB_PERIPH_GPIOB
  *         @arg @ref LL_AHB_PERIPH_CRC
  *         @arg @ref LL_AHB_PERIPH_PKA
  *         @arg @ref LL_AHB_PERIPH_RNG
  *         @arg @ref LL_AHB_PERIPH_AES
  * @retval None
  * @note   LL_AHB_PERIPH_PKA is valid only for BlueNRG-LP 
*/
__STATIC_INLINE void LL_AHB_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHBENR, Periphs);
}

/**
  * @brief  Force AHB peripherals reset.
  * @rmtoll AHBRSTR     DMARST        LL_AHB_ForceReset
  *         AHBRSTR     GPIOARST      LL_AHB_ForceReset
  *         AHBRSTR     GPIOBRST      LL_AHB_ForceReset
  *         AHBRSTR     CRCRST        LL_AHB_ForceReset
  *         AHBRSTR     PKARST        LL_AHB_ForceReset
  *         AHBRSTR     RNGRST        LL_AHB_ForceReset
  *         AHBRSTR     AESRST        LL_AHB_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB_PERIPH_DMA
  *         @arg @ref LL_AHB_PERIPH_GPIOA
  *         @arg @ref LL_AHB_PERIPH_GPIOB
  *         @arg @ref LL_AHB_PERIPH_CRC
  *         @arg @ref LL_AHB_PERIPH_PKA
  *         @arg @ref LL_AHB_PERIPH_RNG
  *         @arg @ref LL_AHB_PERIPH_AES
  * @retval None
  * @note   LL_AHB_PERIPH_PKA is valid only for BlueNRG-LP 
*/
__STATIC_INLINE void LL_AHB_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHBRSTR, Periphs);
}

/**
  * @brief  Release AHB peripherals reset.
  * @rmtoll AHBRSTR     DMARST       LL_AHB_ReleaseReset
  *         AHBRSTR     GPIOARST     LL_AHB_ReleaseReset
  *         AHBRSTR     GPIOBRST     LL_AHB_ReleaseReset
  *         AHBRSTR     CRCRST       LL_AHB_ReleaseReset
  *         AHBRSTR     PKARST       LL_AHB_ReleaseReset
  *         AHBRSTR     RNGRST       LL_AHB_ReleaseReset
  *         AHBRSTR     AESRST       LL_AHB_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB_PERIPH_DMA
  *         @arg @ref LL_AHB_PERIPH_GPIOA
  *         @arg @ref LL_AHB_PERIPH_GPIOB
  *         @arg @ref LL_AHB_PERIPH_CRC
  *         @arg @ref LL_AHB_PERIPH_PKA
  *         @arg @ref LL_AHB_PERIPH_RNG
  *         @arg @ref LL_AHB_PERIPH_AES
  * @retval None
  * @note   LL_AHB_PERIPH_PKA is valid only for BlueNRG-LP 
*/
__STATIC_INLINE void LL_AHB_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHBRSTR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB0 APB0
  * @{
  */

/**
  * @brief  Enable APB0 peripherals clock.
  * @rmtoll APB0ENR     TIM1EN     LL_APB0_EnableClock
  *         APB0ENR     TIM2EN     LL_APB0_EnableClock
  *         APB0ENR     TIM16EN    LL_APB0_EnableClock
  *         APB0ENR     TIM17EN    LL_APB0_EnableClock
  *         APB0ENR     SYSCFGEN   LL_APB0_EnableClock
  *         APB0ENR     LCDCEN     LL_APB0_EnableClock
  *         APB0ENR     COMPEN     LL_APB0_EnableClock
  *         APB0ENR     DACEN      LL_APB0_EnableClock
  *         APB0ENR     RTCEN      LL_APB0_EnableClock
  *         APB0ENR     SCIEN      LL_APB0_EnableClock
  *         APB0ENR     WDGEN      LL_APB0_EnableClock
  *         APB0ENR     DBGMCUEN   LL_APB0_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB0_PERIPH_TIM1
  *         @arg @ref LL_APB0_PERIPH_TIM2
  *         @arg @ref LL_APB0_PERIPH_TIM16
  *         @arg @ref LL_APB0_PERIPH_TIM17
  *         @arg @ref LL_APB0_PERIPH_SYSCFG
  *         @arg @ref LL_APB0_PERIPH_LCDC
  *         @arg @ref LL_APB0_PERIPH_COMP
  *         @arg @ref LL_APB0_PERIPH_DAC
  *         @arg @ref LL_APB0_PERIPH_RTC
  *         @arg @ref LL_APB0_PERIPH_SCI
  *         @arg @ref LL_APB0_PERIPH_WDG
  *         @arg @ref LL_APB0_PERIPH_DBGMCU
  * @retval None
  * @note   LL_APB0_PERIPH_TIM1 is valid only for BlueNRG-LP
  * @note   LL_APB0_PERIPH_TIM2, LL_APB0_PERIPH_TIM16, LL_APB0_PERIPH_LCDC, LL_APB0_PERIPH_COMP, LL_APB0_PERIPH_DAC
*/
__STATIC_INLINE void LL_APB0_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB0ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB0ENR, Periphs);
  (void)tmpreg;
  }

/**
  * @brief  Check if APB0 peripheral clock is enabled or not
  * @rmtoll APB0ENR     TIM1EN       LL_APB0_IsEnabledClock
  *         APB0ENR     TIM2EN       LL_APB0_IsEnabledClock
  *         APB0ENR     TIM16EN      LL_APB0_IsEnabledClock
  *         APB0ENR     TIM17EN      LL_APB0_IsEnabledClock
  *         APB0ENR     SYSCFGEN     LL_APB0_IsEnabledClock
  *         APB0ENR     LCDCEN       LL_APB0_IsEnabledClock
  *         APB0ENR     COMPEN       LL_APB0_IsEnabledClock
  *         APB0ENR     DACEN        LL_APB0_IsEnabledClock
  *         APB0ENR     RTCEN        LL_APB0_IsEnabledClock
  *         APB0ENR     SCIEN        LL_APB0_IsEnabledClock
  *         APB0ENR     WDGEN        LL_APB0_IsEnabledClock
  *         APB0ENR     DBGMCUEN     LL_APB0_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB0_PERIPH_TIM1
  *         @arg @ref LL_APB0_PERIPH_TIM2
  *         @arg @ref LL_APB0_PERIPH_TIM16
  *         @arg @ref LL_APB0_PERIPH_TIM17
  *         @arg @ref LL_APB0_PERIPH_SYSCFG
  *         @arg @ref LL_APB0_PERIPH_LCDC
  *         @arg @ref LL_APB0_PERIPH_COMP
  *         @arg @ref LL_APB0_PERIPH_DAC
  *         @arg @ref LL_APB0_PERIPH_RTC
  *         @arg @ref LL_APB0_PERIPH_SCI
  *         @arg @ref LL_APB0_PERIPH_WDG
  *         @arg @ref LL_APB0_PERIPH_DBGMCU
  * @retval uint32_t
  * @note   LL_APB0_PERIPH_TIM1 is valid only for BlueNRG-LP
  * @note   LL_APB0_PERIPH_TIM2, LL_APB0_PERIPH_TIM16, LL_APB0_PERIPH_LCDC, LL_APB0_PERIPH_COMP, LL_APB0_PERIPH_DAC,
*/
__STATIC_INLINE uint32_t LL_APB0_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB0ENR , Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB0 peripherals clock.
  * @rmtoll APB0ENR     TIM1EN       LL_APB0_DisableClock
  *         APB0ENR     TIM2EN       LL_APB0_DisableClock
  *         APB0ENR     TIM16EN      LL_APB0_DisableClock
  *         APB0ENR     TIM17EN      LL_APB0_DisableClock
  *         APB0ENR     SYSCFGEN     LL_APB0_DisableClock
  *         APB0ENR     LCDCEN       LL_APB0_DisableClock
  *         APB0ENR     COMPEN       LL_APB0_DisableClock
  *         APB0ENR     DACEN        LL_APB0_DisableClock
  *         APB0ENR     RTCEN        LL_APB0_DisableClock
  *         APB0ENR     SCIEN        LL_APB0_DisableClock
  *         APB0ENR     WDGEN        LL_APB0_DisableClock
  *         APB0ENR     DBGMCUEN     LL_APB0_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB0_PERIPH_TIM1
  *         @arg @ref LL_APB0_PERIPH_TIM2
  *         @arg @ref LL_APB0_PERIPH_TIM16
  *         @arg @ref LL_APB0_PERIPH_TIM17
  *         @arg @ref LL_APB0_PERIPH_SYSCFG
  *         @arg @ref LL_APB0_PERIPH_LCDC
  *         @arg @ref LL_APB0_PERIPH_COMP
  *         @arg @ref LL_APB0_PERIPH_DAC
  *         @arg @ref LL_APB0_PERIPH_RTC
  *         @arg @ref LL_APB0_PERIPH_SCI
  *         @arg @ref LL_APB0_PERIPH_WDG
  *         @arg @ref LL_APB0_PERIPH_DBGMCU
  * @retval None
  * @note   LL_APB0_PERIPH_TIM1 is valid only for BlueNRG-LP
  * @note   LL_APB0_PERIPH_TIM2, LL_APB0_PERIPH_TIM16, LL_APB0_PERIPH_LCDC, LL_APB0_PERIPH_COMP, LL_APB0_PERIPH_DAC,
*/
__STATIC_INLINE void LL_APB0_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB0ENR, Periphs);
}

/**
  * @brief  Force APB0 peripherals reset.
  * @rmtoll APB0RSTR    TIM1RST      LL_APB0_ForceReset
  *         APB0RSTR    TIM2RST      LL_APB0_ForceReset
  *         APB0RSTR    TIM16RST     LL_APB0_ForceReset
  *         APB0RSTR    TIM17RST     LL_APB0_ForceReset
  *         APB0RSTR    SYSCFGRST    LL_APB0_ForceReset
  *         APB0RSTR    LCDCRST      LL_APB0_ForceReset
  *         APB0RSTR    COMPRST      LL_APB0_ForceReset
  *         APB0RSTR    DACRST       LL_APB0_ForceReset
  *         APB0RSTR    RTCRST       LL_APB0_ForceReset
  *         APB0RSTR    SCIRST       LL_APB0_ForceReset
  *         APB0RSTR    WDGRST       LL_APB0_ForceReset
  *         APB0RSTR    DBGMCURST    LL_APB0_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB0_PERIPH_TIM1
  *         @arg @ref LL_APB0_PERIPH_TIM2
  *         @arg @ref LL_APB0_PERIPH_TIM16
  *         @arg @ref LL_APB0_PERIPH_TIM17
  *         @arg @ref LL_APB0_PERIPH_SYSCFG
  *         @arg @ref LL_APB0_PERIPH_LCDC
  *         @arg @ref LL_APB0_PERIPH_COMP
  *         @arg @ref LL_APB0_PERIPH_DAC
  *         @arg @ref LL_APB0_PERIPH_RTC
  *         @arg @ref LL_APB0_PERIPH_SCI
  *         @arg @ref LL_APB0_PERIPH_WDG
  *         @arg @ref LL_APB0_PERIPH_DBGMCU
  * @retval None
  * @note   LL_APB0_PERIPH_TIM1 is valid only for BlueNRG-LP
  * @note   LL_APB0_PERIPH_TIM2, LL_APB0_PERIPH_TIM16, LL_APB0_PERIPH_LCDC, LL_APB0_PERIPH_COMP, LL_APB0_PERIPH_DAC,
*/
__STATIC_INLINE void LL_APB0_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB0RSTR, Periphs);
}

/**
  * @brief  Release APB0 peripherals reset.
  * @rmtoll APB0RSTR    TIM1RST      LL_APB0_ReleaseReset
  *         APB0RSTR    TIM2RST      LL_APB0_ReleaseReset
  *         APB0RSTR    TIM16RST     LL_APB0_ReleaseReset
  *         APB0RSTR    TIM17RST     LL_APB0_ReleaseReset
  *         APB0RSTR    SYSCFGRST    LL_APB0_ReleaseReset
  *         APB0RSTR    LCDCRST      LL_APB0_ReleaseReset
  *         APB0RSTR    COMPRST      LL_APB0_ReleaseReset
  *         APB0RSTR    DACRST       LL_APB0_ReleaseReset
  *         APB0RSTR    RTCRST       LL_APB0_ReleaseReset
  *         APB0RSTR    SCIRST       LL_APB0_ReleaseReset
  *         APB0RSTR    WDGRST       LL_APB0_ReleaseReset
  *         APB0RSTR    DBGMCURST    LL_APB0_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB0_PERIPH_TIM1
  *         @arg @ref LL_APB0_PERIPH_TIM2
  *         @arg @ref LL_APB0_PERIPH_TIM6
  *         @arg @ref LL_APB0_PERIPH_TIM7
  *         @arg @ref LL_APB0_PERIPH_SYSCFG
  *         @arg @ref LL_APB0_PERIPH_LCDC
  *         @arg @ref LL_APB0_PERIPH_COMP
  *         @arg @ref LL_APB0_PERIPH_DAC
  *         @arg @ref LL_APB0_PERIPH_RTC
  *         @arg @ref LL_APB0_PERIPH_SCI
  *         @arg @ref LL_APB0_PERIPH_WDG
  *         @arg @ref LL_APB0_PERIPH_DBGMCU
  * @retval None
  * @note   LL_APB0_PERIPH_TIM1 is valid only for BlueNRG-LP
  * @note   LL_APB0_PERIPH_TIM2, LL_APB0_PERIPH_TIM16, LL_APB0_PERIPH_LCDC, LL_APB0_PERIPH_COMP, LL_APB0_PERIPH_DAC,
*/
__STATIC_INLINE void LL_APB0_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB0RSTR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1 APB1
  * @{
  */

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_EnableClock
  *         APB1ENR      ADCDIGEN      LL_APB1_EnableClock
  *         APB1ENR      ADCANAEN      LL_APB1_EnableClock
  *         APB1ENR      LPUARTEN      LL_APB1_EnableClock
  *         APB1ENR      USARTEN       LL_APB1_EnableClock
  *         APB1ENR      SPI2EN        LL_APB1_EnableClock
  *         APB1ENR      SPI3EN        LL_APB1_EnableClock
  *         APB1ENR      I2C1EN        LL_APB1_EnableClock
  *         APB1ENR      I2C2EN        LL_APB1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_PERIPH_SPI1
  *         @arg @ref LL_APB1_PERIPH_ADCDIG
  *         @arg @ref LL_APB1_PERIPH_ADCANA
  *         @arg @ref LL_APB1_PERIPH_LPUART
  *         @arg @ref LL_APB1_PERIPH_USART
  *         @arg @ref LL_APB1_PERIPH_SPI2
  *         @arg @ref LL_APB1_PERIPH_SPI3
  *         @arg @ref LL_APB1_PERIPH_I2C1
  *         @arg @ref LL_APB1_PERIPH_I2C2
  * @retval None
  * @note   LL_APB1_PERIPH_SPI1, LL_APB1_PERIPH_SPI2 and LL_APB1_PERIPH_I2C2 are valid for BlueNRG-LP
*/
__STATIC_INLINE void LL_APB1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_IsEnabledClock
  *         APB1ENR      ADCDIGEN      LL_APB1_IsEnabledClock
  *         APB1ENR      ADCANAEN      LL_APB1_IsEnabledClock
  *         APB1ENR      LPUARTEN      LL_APB1_IsEnabledClock
  *         APB1ENR      USARTEN       LL_APB1_IsEnabledClock
  *         APB1ENR      SPI2EN        LL_APB1_IsEnabledClock
  *         APB1ENR      SPI3EN        LL_APB1_IsEnabledClock
  *         APB1ENR      I2C1EN        LL_APB1_IsEnabledClock
  *         APB1ENR      I2C2EN        LL_APB1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_PERIPH_SPI1
  *         @arg @ref LL_APB1_PERIPH_ADCDIG
  *         @arg @ref LL_APB1_PERIPH_ADCANA
  *         @arg @ref LL_APB1_PERIPH_LPUART
  *         @arg @ref LL_APB1_PERIPH_USART
  *         @arg @ref LL_APB1_PERIPH_SPI2
  *         @arg @ref LL_APB1_PERIPH_SPI3
  *         @arg @ref LL_APB1_PERIPH_I2C1
  *         @arg @ref LL_APB1_PERIPH_I2C2
  * @retval uint32_t
  * @note   LL_APB1_PERIPH_SPI1, LL_APB1_PERIPH_SPI2 and LL_APB1_PERIPH_I2C2 are valid for BlueNRG-LP
*/
__STATIC_INLINE uint32_t LL_APB1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_IsEnabledClock
  *         APB1ENR      ADCDIGEN      LL_APB1_DisableClock
  *         APB1ENR      ADCANAEN      LL_APB1_DisableClock
  *         APB1ENR      LPUARTEN      LL_APB1_DisableClock
  *         APB1ENR      USARTEN       LL_APB1_DisableClock
  *         APB1ENR      SPI2EN        LL_APB1_DisableClock
  *         APB1ENR      SPI3EN        LL_APB1_DisableClock
  *         APB1ENR      I2C1EN        LL_APB1_DisableClock
  *         APB1ENR      I2C2EN        LL_APB1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_PERIPH_SPI1
  *         @arg @ref LL_APB1_PERIPH_ADCDIG
  *         @arg @ref LL_APB1_PERIPH_ADCANA
  *         @arg @ref LL_APB1_PERIPH_LPUART
  *         @arg @ref LL_APB1_PERIPH_USART
  *         @arg @ref LL_APB1_PERIPH_SPI2
  *         @arg @ref LL_APB1_PERIPH_SPI3
  *         @arg @ref LL_APB1_PERIPH_I2C1
  *         @arg @ref LL_APB1_PERIPH_I2C2
  * @retval None
  * @note   LL_APB1_PERIPH_SPI1, LL_APB1_PERIPH_SPI2 and LL_APB1_PERIPH_I2C2 are valid for BlueNRG-LP
*/
__STATIC_INLINE void LL_APB1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR     SPI1RST       LL_APB1_ForceReset
  *         APB1RSTR     ADCRST        LL_APB1_ForceReset
  *         APB1RSTR     LPUARTRST     LL_APB1_ForceReset
  *         APB1RSTR     USARTRST      LL_APB1_ForceReset
  *         APB1RSTR     SPI2RST       LL_APB1_ForceReset
  *         APB1RSTR     SPI3RST       LL_APB1_ForceReset
  *         APB1RSTR     I2C1RST       LL_APB1_ForceReset
  *         APB1RSTR     I2C2RST       LL_APB1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_PERIPH_ALL
  *         @arg @ref LL_APB1_PERIPH_SPI1
  *         @arg @ref LL_APB1_PERIPH_ADCDIG
  *         @arg @ref LL_APB1_PERIPH_LPUART
  *         @arg @ref LL_APB1_PERIPH_USART
  *         @arg @ref LL_APB1_PERIPH_SPI2
  *         @arg @ref LL_APB1_PERIPH_SPI3
  *         @arg @ref LL_APB1_PERIPH_I2C1
  *         @arg @ref LL_APB1_PERIPH_I2C2
  * @retval None
  * @note   LL_APB1_PERIPH_SPI1, LL_APB1_PERIPH_SPI2 and LL_APB1_PERIPH_I2C2 are valid for BlueNRG-LP
*/
__STATIC_INLINE void LL_APB1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR     SPI1RST       LL_APB1_ReleaseReset
  *         APB1RSTR     ADCRST        LL_APB1_ReleaseReset
  *         APB1RSTR     LPUARTRST     LL_APB1_ReleaseReset
  *         APB1RSTR     USARTRST      LL_APB1_ReleaseReset
  *         APB1RSTR     SPI2RST       LL_APB1_ReleaseReset
  *         APB1RSTR     SPI3RST       LL_APB1_ReleaseReset
  *         APB1RSTR     I2C1RST       LL_APB1_ReleaseReset
  *         APB1RSTR     I2C2RST       LL_APB1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_PERIPH_ALL
  *         @arg @ref LL_APB1_PERIPH_SPI1
  *         @arg @ref LL_APB1_PERIPH_ADCDIG
  *         @arg @ref LL_APB1_PERIPH_LPUART
  *         @arg @ref LL_APB1_PERIPH_USART
  *         @arg @ref LL_APB1_PERIPH_SPI2
  *         @arg @ref LL_APB1_PERIPH_SPI3
  *         @arg @ref LL_APB1_PERIPH_I2C1
  *         @arg @ref LL_APB1_PERIPH_I2C2
  * @retval None
  * @note   LL_APB1_PERIPH_SPI1, LL_APB1_PERIPH_SPI2 and LL_APB1_PERIPH_I2C2 are valid for BlueNRG-LP
*/
__STATIC_INLINE void LL_APB1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB2 APB2
  * @{
  */

/**
  * @brief  Enable APB2 peripherals clock.
  * @rmtoll APB2ENR      MRBLEEN        LL_APB2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_PERIPH_MRBLE
  * @retval None
  * @note   LL_APB2_PERIPH_MRBLE is valid only for BlueNRG-LP 
*/
__STATIC_INLINE void LL_APB2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 peripheral clock is enabled or not
  * @rmtoll APB2ENR      MRBLEEN        LL_APB2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_PERIPH_MRBLE
  * @retval uint32_t
  * @note   LL_APB2_PERIPH_MRBLE is valid only for BlueNRG-LP 
*/
__STATIC_INLINE uint32_t LL_APB2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB2ENR      MRBLEEN        LL_APB2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_PERIPH_MRBLE
  * @retval None
  * @note   LL_APB2_PERIPH_MRBLE is valid only for BlueNRG-LP 
*/
__STATIC_INLINE void LL_APB2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll APB2RSTR     MRBLERST        LL_APB2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_PERIPH_MRBLE
  * @retval None
  * @note   LL_APB2_PERIPH_MRBLE is valid only for BlueNRG-LP 
*/
__STATIC_INLINE void LL_APB2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll APB2RSTR     MRBLERST        LL_APB2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_PERIPH_MRBLE
  * @retval None
  * @note   LL_APB2_PERIPH_MRBLE is valid only for BlueNRG-LP 
*/
__STATIC_INLINE void LL_APB2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_LL_BUS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
