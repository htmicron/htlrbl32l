/**
 * Copyright (C) 2018-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Flavien Moullec - flavien@ackl.io
 */

#include <stdint.h>

#include "platform.h"

// Defined in sys_app.c.
extern void (*cmd_rx_callback)(uint8_t *rxChar);

void platform_print_hex_buffer(const uint8_t *buffer, uint16_t size)
{
  uint8_t newline = 0;

  for (uint16_t i = 0; i < size; i++)
  {
    if (newline != 0)
    {
      APP_PRINTF("\n");
      newline = 0;
    }

    APP_PRINTF("%02X ", buffer[i]);

    if (((i + 1) % 16) == 0)
    {
      newline = 1;
    }
  }
  APP_PRINTF("\n");
}

void platform_delay_ms(uint32_t ms)
{
  HAL_Delay(ms);
}

void platform_timer_init(void)
{
  UTIL_TIMER_Init();
}

void platform_timer_add(timer_obj_t *tmr, uint16_t id, void (*cb)(void *),
                        void *cb_arg)
{
  (void)id;
  UTIL_TIMER_Create(tmr, 0, UTIL_TIMER_ONESHOT, cb, cb_arg);
}

void platform_timer_set_duration_start(timer_obj_t *tmr, uint32_t duration)
{
  UTIL_TIMER_StartWithPeriod((UTIL_TIMER_Object_t *)tmr, duration);
}

void platform_timer_start(timer_obj_t *tmr)
{
  UTIL_TIMER_Start((UTIL_TIMER_Object_t *)tmr);
}

void platform_timer_stop(timer_obj_t *tmr)
{
  UTIL_TIMER_Stop((UTIL_TIMER_Object_t *)tmr);
}


void platform_reset(void)
{
  HAL_NVIC_SystemReset();
}

// Initialize system to enter sleep mode instead of standby mode
void platform_configure_sleep_mode(void)
{
//  LPM_SetOffMode(LPM_APPLI_Id, LPM_Disable);
//  LPM_SetStopMode(LPM_APPLI_Id, LPM_Disable);
}

void platform_enter_low_power_ll(void)
{
//  LPM_EnterLowPower();
}

void platform_error_handler(void)
{
  APP_PRINTF("***** entered error state\n\r");
  while (true)
    ;
}

void platform_set_uart_rx_callback(void (*callback)(uint8_t *ch))
{
  cmd_rx_callback = callback;
}

void platform_system_clock_config(void)
{
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

//  /* MSI is enabled after System reset, activate PLL with MSI as source */
//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
//  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
//  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
//  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
//  RCC_OscInitStruct.PLL.PLLM = 1;
//  RCC_OscInitStruct.PLL.PLLN = 40;
//  RCC_OscInitStruct.PLL.PLLR = 2;
//  RCC_OscInitStruct.PLL.PLLP = 7;
//  RCC_OscInitStruct.PLL.PLLQ = 4;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }

//  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
//  clocks dividers */
//  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
//  {
//    Error_Handler();
//  }
}
