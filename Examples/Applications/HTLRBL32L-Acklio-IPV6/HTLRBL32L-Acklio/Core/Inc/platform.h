/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    platform.h
  * @author  MCD Application Team
  * @brief   Header for General HW instances configuration
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported constants --------------------------------------------------------*/

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
//#include "stm32l4xx.h"
#include "sys_app.h"
#include "main.h"
#include "nucleo_l476rg_bus.h"
#include "timer.h"

//#define CRITICAL_SECTION_BEGIN() UTILS_ENTER_CRITICAL_SECTION()
//#define CRITICAL_SECTION_END() UTILS_EXIT_CRITICAL_SECTION()

#define PRINT_HEX_BUF(buf, size) platform_print_hex_buffer(buf, size);
#define PRINT_AT(...) APP_PRINTF(__VA_ARGS__)

/**
 * Let various existing layers use the generic error handler.
 */
#define Error_Handler platform_error_handler

  typedef TimerEvent_t timer_obj_t;

  void platform_reset(void);
  void platform_print_hex_buffer(const uint8_t *buffer, uint16_t size);
  void platform_error_handler(void);
  void platform_delay_ms(uint32_t ms);
  uint32_t platform_get_clock_ms(void);
  void platform_configure_sleep_mode(void);
  void platform_enter_low_power(void);
  void platform_enter_low_power_ll(void);
  void platform_set_uart_rx_callback(void (*callback)(uint8_t *ch));

  /**
   * @brief Initializes timer module
   */
  void platform_timer_init(void);

  /**
   * @brief Adds a timer
   *
   * @param tmr Timer object
   * @param id Timer ID
   * @param cb Callback to be executed when the timer goes off
   * @param cb_arg Argument to the callback
   */
  void platform_timer_add(timer_obj_t *tmr, uint16_t id, void (*cb)(void *),
                          void *cb_arg);

  /**
   * @brief Starts a timer
   *
   * @param tmr Timer object
   */
  void platform_timer_start(timer_obj_t *tmr);

  /**
   * @brief Sets the duration of a timer and starts it
   *
   * @param tmr Timer object
   * @param duration Duration of the timer in milliseconds
   */
  void platform_timer_set_duration_start(timer_obj_t *tmr, uint32_t duration);

  /**
   * @brief Stops a timer
   *
   * @param tmr Timer object
   */
  void platform_timer_stop(timer_obj_t *tmr);

  /**
   * @brief Sets the MCU in sleep mode for the given number of milliseconds
   *
   * @param ms Time in milliseconds
   */
  void platform_set_sleep_for_ms(uint32_t ms);

  /**
   * @brief Reloads watchdog timer to avoid system reset
   */
  void platform_reload_watchdog(void);

  /**
   * @brief Configures system clock
   */
  void platform_system_clock_config(void);

  /* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
