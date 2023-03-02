/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sys_app.c
  * @author  MCD Application Team
  * @brief   Initializes HW and SW system entities (not related to the radio)
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "platform.h"
#include "rf_driver_hal.h"
#include "sys_app.h"
#include "adc_if.h"
#include "radio_board_if.h"
#include "stm32_seq.h"
#include "stm32_systime.h"
#include "stm32_lpm.h"
#include "utilities_def.h"
#include "sys_debug.h"
#include "rtc_if.h"
#include "sys_sensors.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

// RX callback provided by AT command processing.
void (*cmd_rx_callback)(uint8_t *rxChar) = NULL;

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
#define MAX_TS_SIZE (int) 16

/**
  * Defines the maximum battery level
  */
#define LORAWAN_MAX_BAT   254
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  Set all pins such to minimized consumption (necessary for some STM32 families)
  * @param none
  * @retval None
  */
static void Gpio_PreInit(void);
/**
  * @brief Returns sec and msec based on the systime in use
  * @param buff to update with timestamp
  * @param size of updated buffer
  */
static void TimestampNow(uint8_t *buff, uint16_t *size);

/**
  * @brief  it calls UTIL_ADV_TRACE_VSNPRINTF
  */
static void tiny_snprintf_like(char *buf, uint32_t maxsize, const char *strFormat, ...);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

static void user_rx_callback(uint8_t *PData, uint16_t Size, uint8_t Error)
{
  (void)Size;
  (void)Error;
  if (cmd_rx_callback != NULL) cmd_rx_callback(PData);
}

/* Exported functions ---------------------------------------------------------*/
void SystemApp_Init(void)
{
  /* USER CODE BEGIN SystemApp_Init_1 */

  /* USER CODE END SystemApp_Init_1 */

  /* Ensure that MSI is wake-up system clock */
  //__HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI); TODO

  /*Initialize timer and RTC*/
  UTIL_TIMER_Init();

  Gpio_PreInit();

  /* Debug config : disable serial wires and DbgMcu pins settings */
 // DBG_Disable();

  /* Initializes the SW probes pins and the monitor RF pins via Alternate Function */
 // DBG_ProbesInit();

  /*Initialize the terminal */
  UTIL_ADV_TRACE_Init();
  UTIL_ADV_TRACE_RegisterTimeStampFunction(TimestampNow);

  /*Set verbose LEVEL*/
  UTIL_ADV_TRACE_SetVerboseLevel(VERBOSE_LEVEL);

  UTIL_ADV_TRACE_StartRxProcess(user_rx_callback);

  /*Initialize the temperature and Battery measurement services */
  SYS_InitMeasurement();

  Sx_Board_Bus_Init();

  Sx_Board_IoInit();

//  /*Initialize the Sensors */
//  EnvSensors_Init();
//
//  /*Init low power manager*/
//  UTIL_LPM_Init();
//  /* Disable Stand-by mode */
//  UTIL_LPM_SetOffMode((1 << CFG_LPM_APPLI_Id), UTIL_LPM_DISABLE);
//
//#if defined (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 1)
//  /* Disable Stop Mode */
//  UTIL_LPM_SetStopMode((1 << CFG_LPM_APPLI_Id), UTIL_LPM_DISABLE);
//#elif !defined (LOW_POWER_DISABLE)
//#error LOW_POWER_DISABLE not defined
//#endif /* LOW_POWER_DISABLE */

  /* USER CODE BEGIN SystemApp_Init_2 */

  /* USER CODE END SystemApp_Init_2 */
}

/**
  * @brief redefines __weak function in stm32_seq.c such to enter low power
  */
void UTIL_SEQ_Idle(void)
{
  /* USER CODE BEGIN UTIL_SEQ_Idle_1 */

  /* USER CODE END UTIL_SEQ_Idle_1 */
  UTIL_LPM_EnterLowPower();
  /* USER CODE BEGIN UTIL_SEQ_Idle_2 */

  /* USER CODE END UTIL_SEQ_Idle_2 */
}

uint8_t GetBatteryLevel(void)
{
  uint8_t batteryLevel = 0;
  uint16_t batteryLevelmV;

  /* USER CODE BEGIN GetBatteryLevel_0 */

  /* USER CODE END GetBatteryLevel_0 */

  batteryLevelmV = (uint16_t) SYS_GetBatteryLevel();

  /* Convert battery level from mV to linear scale: 1 (very low) to 254 (fully charged) */
  if (batteryLevelmV > VDD_BAT)
  {
    batteryLevel = LORAWAN_MAX_BAT;
  }
  else if (batteryLevelmV < VDD_MIN)
  {
    batteryLevel = 0;
  }
  else
  {
    batteryLevel = (((uint32_t)(batteryLevelmV - VDD_MIN) * LORAWAN_MAX_BAT) / (VDD_BAT - VDD_MIN));
  }

  APP_LOG(TS_ON, VLEVEL_M, "VDDA= %d\r\n", batteryLevel);

  /* USER CODE BEGIN GetBatteryLevel_2 */

  /* USER CODE END GetBatteryLevel_2 */

  return batteryLevel;  /* 1 (very low) to 254 (fully charged) */
}

uint16_t GetTemperatureLevel(void)
{
  uint16_t temperatureLevel = 0;

  temperatureLevel = (uint16_t)(SYS_GetTemperatureLevel() / 256);
  /* USER CODE BEGIN GetTemperatureLevel */

  /* USER CODE END GetTemperatureLevel */
  return temperatureLevel;
}

void GetUniqueId(uint8_t *id)
{
  /* USER CODE BEGIN GetUniqueId_1 */

  /* USER CODE END GetUniqueId_1 */
  uint32_t ID_1_3_val = HAL_GetUIDw0() + HAL_GetUIDw2();
  uint32_t ID_2_val = HAL_GetUIDw1();

  id[7] = (ID_1_3_val) >> 24;
  id[6] = (ID_1_3_val) >> 16;
  id[5] = (ID_1_3_val) >> 8;
  id[4] = (ID_1_3_val);
  id[3] = (ID_2_val) >> 24;
  id[2] = (ID_2_val) >> 16;
  id[1] = (ID_2_val) >> 8;
  id[0] = (ID_2_val);

  /* USER CODE BEGIN GetUniqueId_2 */

  /* USER CODE END GetUniqueId_2 */
}

uint32_t GetDevAddr(void)
{
  return ((HAL_GetUIDw0()) ^ (HAL_GetUIDw1()) ^ (HAL_GetUIDw2()));
}

/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Private functions ---------------------------------------------------------*/

static void TimestampNow(uint8_t *buff, uint16_t *size)
{
  /* USER CODE BEGIN TimestampNow_1 */

  /* USER CODE END TimestampNow_1 */
  SysTime_t curtime = SysTimeGet();
  tiny_snprintf_like((char *)buff, MAX_TS_SIZE, "%ds%03d:", curtime.Seconds, curtime.SubSeconds);
  *size = strlen((char *)buff);
  /* USER CODE BEGIN TimestampNow_2 */

  /* USER CODE END TimestampNow_2 */
}

__weak void user_button_callback(void *context)
{
  /* to be implemented by the application */
}

static void Gpio_PreInit(void)
{
  /* USER CODE BEGIN Gpio_PreInit_1 */

  /* USER CODE END Gpio_PreInit_1 */
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Configure all IOs in analog input              */
  /* Except PA13 and PA14 (SWCLK and SWD) for debug*/
  /* PA13 and PA14 are configured in debug_init     */
  /* Configure all GPIO as analog to reduce current consumption on non used IOs */
  /* Enable GPIOs clock */
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
////  __HAL_RCC_GPIOC_CLK_ENABLE();
////  __HAL_RCC_GPIOH_CLK_ENABLE();
//
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  /* All GPIOs except debug pins (SWCLK and SWD) */
//  GPIO_InitStruct.Pin = GPIO_PIN_All & (~(GPIO_PIN_13 | GPIO_PIN_14));
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  /* All GPIOs except debug pins (SWO) */
//  GPIO_InitStruct.Pin = GPIO_PIN_All & (~GPIO_PIN_3);
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//  /* All GPIOs */
//  GPIO_InitStruct.Pin = GPIO_PIN_All;
////  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
////  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
//
//  /* Configure Button pin as input with External interrupt */
//  GPIO_InitStruct.Pin = GPIO_PIN_13;
//  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
// // HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//
//  /* Enable and set Button EXTI Interrupt to the lowest priority */
////  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0F, 0);
////  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
//
//  /* Disable GPIOs clock */
//  __HAL_RCC_GPIOA_CLK_DISABLE();
//  __HAL_RCC_GPIOB_CLK_DISABLE();
////  __HAL_RCC_GPIOC_CLK_DISABLE();
////  __HAL_RCC_GPIOH_CLK_DISABLE();
//  /* USER CODE BEGIN Gpio_PreInit_2 */
//
//  /* USER CODE END Gpio_PreInit_2 */
}

/* Link the interrupt with the callback */
void HAL_GPIO_EXTI_Callback(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
    case GPIO_PIN_13:
      user_button_callback(NULL);
      break;
    default:
      break;
  }
}

/* Disable StopMode when traces need to be printed */
void UTIL_ADV_TRACE_PreSendHook(void)
{
  /* USER CODE BEGIN UTIL_ADV_TRACE_PreSendHook_1 */

  /* USER CODE END UTIL_ADV_TRACE_PreSendHook_1 */
  UTIL_LPM_SetStopMode((1 << CFG_LPM_UART_TX_Id), UTIL_LPM_DISABLE);
  /* USER CODE BEGIN UTIL_ADV_TRACE_PreSendHook_2 */

  /* USER CODE END UTIL_ADV_TRACE_PreSendHook_2 */
}
/* Re-enable StopMode when traces have been printed */
void UTIL_ADV_TRACE_PostSendHook(void)
{
  /* USER CODE BEGIN UTIL_LPM_SetStopMode_1 */

  /* USER CODE END UTIL_LPM_SetStopMode_1 */
  UTIL_LPM_SetStopMode((1 << CFG_LPM_UART_TX_Id), UTIL_LPM_ENABLE);
  /* USER CODE BEGIN UTIL_LPM_SetStopMode_2 */

  /* USER CODE END UTIL_LPM_SetStopMode_2 */
}

static void tiny_snprintf_like(char *buf, uint32_t maxsize, const char *strFormat, ...)
{
  /* USER CODE BEGIN tiny_snprintf_like_1 */

  /* USER CODE END tiny_snprintf_like_1 */
  va_list vaArgs;
  va_start(vaArgs, strFormat);
  UTIL_ADV_TRACE_VSNPRINTF(buf, maxsize, strFormat, vaArgs);
  va_end(vaArgs);
  /* USER CODE BEGIN tiny_snprintf_like_2 */

  /* USER CODE END tiny_snprintf_like_2 */
}

/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */

/* HAL overload functions ---------------------------------------------------------*/

/**
  * @note This function overwrites the __weak one from HAL
  */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  /*Don't enable SysTick if TIMER_IF is based on other counters (e.g. RTC) */
  /* USER CODE BEGIN HAL_InitTick_1 */

  /* USER CODE END HAL_InitTick_1 */
  return HAL_OK;
  /* USER CODE BEGIN HAL_InitTick_2 */

  /* USER CODE END HAL_InitTick_2 */
}

/**
  * @note This function overwrites the __weak one from HAL
  */
uint32_t HAL_GetTick(void)
{
  /* USER CODE BEGIN HAL_GetTick_1 */

  /* USER CODE END HAL_GetTick_1 */
  return RTC_IF_GetTimerValue();
  /* USER CODE BEGIN HAL_GetTick_2 */

  /* USER CODE END HAL_GetTick_2 */
}

/**
  * @note This function overwrites the __weak one from HAL
  */
void HAL_Delay(__IO uint32_t Delay)
{
  /* USER CODE BEGIN HAL_Delay_1 */

  /* USER CODE END HAL_Delay_1 */
  RTC_IF_DelayMs(Delay);   /* based on RTC */
  /* USER CODE BEGIN HAL_Delay_2 */

  /* USER CODE END HAL_Delay_2 */
}

/* USER CODE BEGIN Overload_HAL_weaks */

/* USER CODE END Overload_HAL_weaks */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
