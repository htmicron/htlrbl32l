/**
  ******************************************************************************
  * @file    rf_driver_hal_power_manager.h
  * @author  AMG - RF-Application Team
  * @version V1.0.0
  * @date    21-December-2020
  * @brief   Header file for the power save manager
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2019 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#ifndef __HAL_POWER_MANAGER_H__
#define __HAL_POWER_MANAGER_H__

#include <stdint.h>
#include "rf_driver_ll_pwr.h"

/** @brief Enumerations for the possible microcontroller power save levels.
 * - POWER_SAVE_LEVEL_RUNNING
 *     Everything is active and running.
 * - POWER_SAVE_LEVEL_CPU_HALT
 *     Only the CPU is halted.  The rest of the chip continues running
 *     normally.  The chip will wake from any interrupt.
 * - POWER_SAVE_LEVEL_STOP_WITH_TIMER
 *     The device is in deep sleep and the timer clock sources (LSI or LSE) remain running. 
 *     Wakeup is possible from all IOs enabled for this scope, RTC, IWDG, 
 *     radio IP and the Hal Virtual Timers.
 * - POWER_SAVE_LEVEL_STOP_NOTIMER
 *     The device is in deep sleep. All the peripherals and clock sources are turned off.
 *     Wakeup is possible only from IOs enabled for this scope.
 */
typedef enum {
  POWER_SAVE_LEVEL_RUNNING          = 0,
  POWER_SAVE_LEVEL_CPU_HALT         = 1,
  POWER_SAVE_LEVEL_STOP_WITH_TIMER  = 2,
  POWER_SAVE_LEVEL_STOP_NOTIMER     = 3
} PowerSaveLevels; 

/** @brief Wakeup source RTC Mask */
#define WAKEUP_RTC LL_PWR_EWS_INT

/** @brief Wakeup source LPUART Mask (not valid for BlueNRG-LP) */
#if defined(LL_PWR_EWS_INT2)
#define WAKEUP_LPU LL_PWR_EWS_INT2
#endif

/** @brief Wakeup source BLE Host Timer Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_BLE_HOST_TIMER LL_PWR_EWS_BLEHOST

/** @brief Wakeup source BLE Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_BLE LL_PWR_EWS_BLE

/** @brief Wakeup source PA15 Mask (only valid for BlueNRG-LP) */
#if defined(PWR_CR6_EWU27)
#define WAKEUP_PA15 LL_PWE_EWS_EW27
#endif

/** @brief Wakeup source PA14 Mask (only valid for BlueNRG-LP) */
#if defined(PWR_CR6_EWU26)
#define WAKEUP_PA14 LL_PWE_EWS_EW26
#endif

/** @brief Wakeup source PA13 Mask (only valid for BlueNRG-LP) */
#if defined(PWR_CR6_EWU25)
#define WAKEUP_PA13 LL_PWE_EWS_EW25
#endif

/** @brief Wakeup source PA12 Mask (only valid for BlueNRG-LP) */
#if defined(PWR_CR6_EWU24)
#define WAKEUP_PA12 LL_PWE_EWS_EW24
#endif

/** @brief Wakeup source PA11 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PA11 LL_PWE_EWS_EW11

/** @brief Wakeup source PA10 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PA10 LL_PWE_EWS_EW10

/** @brief Wakeup source PA9 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PA9  LL_PWE_EWS_EW9

/** @brief Wakeup source PA8 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PA8  LL_PWE_EWS_EW8

/** @brief Wakeup source PA7 Mask (only valid for BlueNRG-LP) */
#define WAKEUP_PA7 LL_PWE_EWS_EW19

/** @brief Wakeup source PA6 Mask (only valid for BlueNRG-LP) */
#define WAKEUP_PA6 LL_PWE_EWS_EW18

/** @brief Wakeup source PA5 Mask (only valid for BlueNRG-LP) */
#define WAKEUP_PA5 LL_PWE_EWS_EW17

/** @brief Wakeup source PA4 Mask (only valid for BlueNRG-LP) */
#define WAKEUP_PA4 LL_PWE_EWS_EW16

/** @brief Wakeup source PA3 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PA3 LL_PWE_EWS_EW15

/** @brief Wakeup source PA2 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PA2 LL_PWE_EWS_EW14

/** @brief Wakeup source PA1 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PA1 LL_PWE_EWS_EW13

/** @brief Wakeup source PA0 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PA0 LL_PWE_EWS_EW12

#define WAKEUP_PB15 LL_PWE_EWS_EW19

#define WAKEUP_PB14 LL_PWE_EWS_EW18

#define WAKEUP_PB13 LL_PWE_EWS_EW17

#define WAKEUP_PB12 LL_PWE_EWS_EW16

/** @brief Wakeup source PB11 Mask (only valid for BlueNRG-LP) */
#if defined(PWR_CR6_EWU23)
#define WAKEUP_PB11 LL_PWE_EWS_EW23
#endif

/** @brief Wakeup source PB10 Mask (only valid for BlueNRG-LP) */
#if defined(PWR_CR6_EWU22)
#define WAKEUP_PB10 LL_PWE_EWS_EW22
#endif

/** @brief Wakeup source PB9 Mask (only valid for BlueNRG-LP) */
#if defined(PWR_CR6_EWU21)
#define WAKEUP_PB9 LL_PWE_EWS_EW21
#endif

/** @brief Wakeup source PB8 Mask (only valid for BlueNRG-LP) */
#if defined(PWR_CR6_EWU20)
#define WAKEUP_PB8 LL_PWE_EWS_EW20
#endif

/** @brief Wakeup source PB7 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PB7  LL_PWE_EWS_EW7

/** @brief Wakeup source PB6 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PB6  LL_PWE_EWS_EW6

/** @brief Wakeup source PB5 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PB5  LL_PWE_EWS_EW5

/** @brief Wakeup source PB4 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PB4  LL_PWE_EWS_EW4

/** @brief Wakeup source PB3 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PB3  LL_PWE_EWS_EW3

/** @brief Wakeup source PB2 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PB2  LL_PWE_EWS_EW2

/** @brief Wakeup source PB1 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PB1  LL_PWE_EWS_EW1

/** @brief Wakeup source PB0 Mask (valid for both BlueNRG-LP ) */
#define WAKEUP_PB0  LL_PWE_EWS_EW0


/** @brief No Wakeup source Mask */
#define NO_WAKEUP_SOURCE  0x00000000

/** @brief All Wakeup source Mask */
#define ALL_WAKEUP_SOURCE  0xFFFFFFFF

/**
  * @brief Wakeup Sosurce Configuration Structure definition
  */
typedef struct {
  uint8_t  RTC_enable;            /*!< Specifies if the RTC wakeup source is enabled or not */
  uint8_t  LPU_enable;            /*!< Specifies if the LPUART wakeup source is enabled or not */
  uint32_t IO_Mask_Low_polarity;  /*!< This bitmask specifies which IO are configured to wakeup and getout from STOP level 
                                       with low polarity, that is detection of wakeup event on falling edge. 
                                       NOTE: If not used SHALL be init to zero */
  uint32_t IO_Mask_High_polarity; /*!< This bitmask Specifies which IO are configured to wakeup and getout from STOP level
                                       with high polarity, that is detection of wakeup event on rising edge. 
                                       NOTE: If not used SHALL be init to zero */
} WakeupSourceConfig_TypeDef;

/** 
 * @brief This function allows to put the device in low power state.
 *
 * This function allows to enter a desired power save level that is negotiated between Radio stack needs, CPU Host Timer needs and application needs.
 * The application can provide the desired power save level using the parameter mode. In addition to this, the application can
 * optionally use the @ref App_PowerSaveLevel_Check to provide its desired power save level.
 * The function will compute the power save level by combining the different requests and choosing the lowest possible power save level mode.
 *
 * The device can be configured with different wake sources
 * according to the mode parameter. The lowest power save level is obtained configuring the device in 
 * POWER_SAVE_MODE_SHUTDOWN, but in this case the only wakeup source is a low pulse on the RSTN pad, so, no smart power management 
 * is in place, because there is no memory retention in this power save level configuration.
 * For all power save levels, HAL_PWR_MNGR_Request() will return when the wakeup occours.
 * 
 * @param level Power save level (see PowerSaveLevels enum)
 * 
 * @param wsConfig this is the wakeup sources configuration (@ref WakeupSourceConfig_TypeDef structure)
 * 
 * @param[out] negotiatedLevel This parameter returns the negotiated power save level really applied.
 *
 * @retval SUCCESS or error code 
 */
uint8_t HAL_PWR_MNGR_Request(PowerSaveLevels level, WakeupSourceConfig_TypeDef wsConfig, PowerSaveLevels *negotiatedLevel);


/** 
 * @brief This function allows to put the device in shutdown.
 *
 * This function allows to put the device in shutdown mode, this is the least power consuming mode.
 * The only wakeup source is a low pulse on the RSTN pad.
 *  The conditions to enter the Shutdown mode are:
 *  - the radio is sleeping,
 *  - the CPU is sleeping (WFI with SLEEPDEEP information active)
 * A Shutdown exit is similar to a POR startup of the board. The associated reset reason is the PORRSTF flag 
 * The BOR feature may be enabled or disabled during SHUTDOWN mode.
 *
 * @param BOR_enabled if TRUE the BOR is enabled during Shutdown mode, otherwise it is disabled.
 * 
 * @retval ERROR if for some reason the device not allow the Shutdown mode.
 *
 * Note: The application never read SUCCESS like return value because a POR happens at wakeup
 */
uint8_t HAL_PWR_MNGR_ShutdownRequest(uint8_t BOR_enabled);

/**
 * @brief Return the wakeup source from power save.
 * @retval The return value can be a combination of the following values:
 *         - WAKEUP_RTC
 *         - WAKEUP_LPU
 *         - WAKEUP_BLE_HOST_TIMER
 *         - WAKEUP_BLE
 *         - WAKEUP_PA15
 *         - WAKEUP_PA14
 *         - WAKEUP_PA13
 *         - WAKEUP_PA12
 *         - WAKEUP_PA11
 *         - WAKEUP_PA10
 *         - WAKEUP_PA9
 *         - WAKEUP_PA8
 *         - WAKEUP_PA7
 *         - WAKEUP_PA6
 *         - WAKEUP_PA5
 *         - WAKEUP_PA4
 *         - WAKEUP_PA3
 *         - WAKEUP_PA2
 *         - WAKEUP_PA1
 *         - WAKEUP_PA0
 *         - WAKEUP_PB15
 *         - WAKEUP_PB14
 *         - WAKEUP_PB13
 *         - WAKEUP_PB12
 *         - WAKEUP_PB11
 *         - WAKEUP_PB10
 *         - WAKEUP_PB9
 *         - WAKEUP_PB8
 *         - WAKEUP_PB7
 *         - WAKEUP_PB6
 *         - WAKEUP_PB5
 *         - WAKEUP_PB4
 *         - WAKEUP_PB3
 *         - WAKEUP_PB2
 *         - WAKEUP_PB1
 *         - WAKEUP_PB0
 *         - NO_WAKEUP_SOURCE (for any reason the device has not activated the DEEPSTOP level)
 * @note   Refer the wakeup source declaration to see if are supported from the device
 */ 
uint32_t HAL_PWR_MNGR_WakeupSource(void);

/**
 * @brief Clear the wakeup source information.
 * @param source Wakeup source to clear, the parameter can be a combination of the following values:
 *        - WAKEUP_RTC
 *        - WAKEUP_LPU
 *        - WAKEUP_BLE_HOST_TIMER
 *        - WAKEUP_BLE
 *        - WAKEUP_PA15
 *        - WAKEUP_PA14
 *        - WAKEUP_PA13
 *        - WAKEUP_PA12
 *        - WAKEUP_PA11
 *        - WAKEUP_PA10
 *        - WAKEUP_PA9
 *        - WAKEUP_PA8
 *        - WAKEUP_PA7
 *        - WAKEUP_PA6
 *        - WAKEUP_PA5
 *        - WAKEUP_PA4
 *        - WAKEUP_PA3
 *        - WAKEUP_PA2
 *        - WAKEUP_PA1
 *        - WAKEUP_PA0
 *        - WAKEUP_PB15
 *        - WAKEUP_PB14
 *        - WAKEUP_PB13
 *        - WAKEUP_PB12
 *        - WAKEUP_PB11
 *        - WAKEUP_PB10
 *        - WAKEUP_PB9
 *        - WAKEUP_PB8
 *        - WAKEUP_PB7
 *        - WAKEUP_PB6
 *        - WAKEUP_PB5
 *        - WAKEUP_PB4
 *        - WAKEUP_PB3
 *        - WAKEUP_PB2
 *        - WAKEUP_PB1
 *        - WAKEUP_PB0
 *        - ALL_WAKEUP_SOURCE
 * @retval None
 * @note   Refer the wakeup source declaration to see if are supported from the device
 */ 
void HAL_PWR_MNGR_ClearWakeupSource(uint32_t source);

/**
 * @brief Sets an user callback that will be executed at the end of the wakeup context restore. 
 *        This callback will be executed if an IO is a wakeup source.
 * @param source Wakeup source in the last power save cycle. The parameter can be a combination of the following values:
 *        - WAKEUP_PA15
 *        - WAKEUP_PA14
 *        - WAKEUP_PA13
 *        - WAKEUP_PA12
 *        - WAKEUP_PA11
 *        - WAKEUP_PA10
 *        - WAKEUP_PA9
 *        - WAKEUP_PA8
 *        - WAKEUP_PA7
 *        - WAKEUP_PA6
 *        - WAKEUP_PA5
 *        - WAKEUP_PA4
 *        - WAKEUP_PA3
 *        - WAKEUP_PA2
 *        - WAKEUP_PA1
 *        - WAKEUP_PA0
 *        - WAKEUP_PB15
 *        - WAKEUP_PB14
 *        - WAKEUP_PB13
 *        - WAKEUP_PB12
 *        - WAKEUP_PB11
 *        - WAKEUP_PB10
 *        - WAKEUP_PB9
 *        - WAKEUP_PB8
 *        - WAKEUP_PB7
 *        - WAKEUP_PB6
 *        - WAKEUP_PB5
 *        - WAKEUP_PB4
 *        - WAKEUP_PB3
 *        - WAKEUP_PB2
 *        - WAKEUP_PB1
 *        - WAKEUP_PB0
 *        - ALL_WAKEUP_SOURCE
 * @retval None
 * @note This function should be used if an interrupt is associated to the IO wakeup source. 
 *       The device during the DEEPSTOP period has the GPIO peripherals disabled.
 *       So, if a signal variation happens in a IO pin, the device will be woke up but the associated interrupt to the line 
 *       is lost because the peripheral is not clocked and configured before the context restore. 
 *       To serve this interrupt the application shall add the GPIO IRQ code inside this user callback. 
 *       Refer the wakeup source declaration to see if are supported from the device
 */ 
void HAL_PWR_MNGR_WakeupIOCallback(uint32_t source);

/** 
 * @brief This function allows the application to define its desired power save level.
 * 
 * The App_PowerSaveLevel_Check allows the application to set its desired power save level based on the application power management policy.
 * When user calls @ref HAL_PWR_MNGR_Request, a negotiation occurs to define the power save level and this function is called to get
 * inputs from application.
 * It is important to notice that this function is executed with interrupts disabled
 *
 * @param level Power save level (see PowerSaveLevels enum)
 *
 * @retval Return the Power save level possible and safe from the application point of view
 *
 * @note A weak implementation always returning POWER_SAVE_LEVEL_STOP_NOTIMER is provided as default
 * when no application specifc behaviour is required.
 */
PowerSaveLevels App_PowerSaveLevel_Check(PowerSaveLevels level);

#endif /* __HAL_POWER_MANAGER_H__ */
