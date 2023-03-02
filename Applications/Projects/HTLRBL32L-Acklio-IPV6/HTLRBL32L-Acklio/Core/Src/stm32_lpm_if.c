/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32_lpm_if.c
  * @author  MCD Application Team
  * @brief   Low layer function to enter/exit low power modes (stop, sleep)
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
#include "sys_debug.h"
#include "stm32_lpm_if.h"
#include "usart_if.h"
#include "radio_board_if.h"
#include "adc.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief Power driver callbacks handler
  */
const struct UTIL_LPM_Driver_s UTIL_PowerDriver =
{
  PWR_EnterSleepMode,
  PWR_ExitSleepMode,

  PWR_EnterStopMode,
  PWR_ExitStopMode,

  PWR_EnterOffMode,
  PWR_ExitOffMode,
};

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/

void PWR_EnterOffMode(void)
{
  /* USER CODE BEGIN EnterOffMode_1 */

  /* USER CODE END EnterOffMode_1 */
}

void PWR_ExitOffMode(void)
{
  /* USER CODE BEGIN ExitOffMode_1 */

  /* USER CODE END ExitOffMode_1 */
}

void PWR_EnterStopMode(void)
{
  /* USER CODE BEGIN EnterStopMode_1 */

//  /* USER CODE END EnterStopMode_1 */
//  UTILS_ENTER_CRITICAL_SECTION();

//  Sx_Board_IoDeInit();

//  HAL_ADC_MspDeInit(&hadc);

//  UTILS_EXIT_CRITICAL_SECTION();
//  /* USER CODE BEGIN EnterStopMode_2 */

//  /* USER CODE END EnterStopMode_2 */
//  /* Enter Stop Mode */
//  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  /* USER CODE BEGIN EnterStopMode_3 */

  /* USER CODE END EnterStopMode_3 */
}

void PWR_ExitStopMode(void)
{
  /* USER CODE BEGIN ExitStopMode_1 */

  /* USER CODE END ExitStopMode_1 */
  /* Disable IRQ while the MCU is not running on PLL */

//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  uint32_t pFLatency = 0;

//  UTILS_ENTER_CRITICAL_SECTION();

//  /* In case nvic had a pending IT, the arm doesn't enter stop mode
//   * Hence the pll is not switched off and will cause HAL_RCC_OscConfig return
//    an error*/
//  if (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_PLL)
//  {
//    /* Enable Power Control clock */
//    __HAL_RCC_PWR_CLK_ENABLE();

//    /* Get the Oscillators configuration according to the internal RCC registers */
//    HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

//    /* Enable PLL */
//    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
//    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//    {
//      while (1);
//    }

//    /* Get the Clocks configuration according to the internal RCC registers */
//    HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &pFLatency);

//    /* Select PLL as system clock source and keep HCLK, PCLK1 and PCLK2 clocks dividers as before */
//    RCC_ClkInitStruct.ClockType     = RCC_CLOCKTYPE_SYSCLK;
//    RCC_ClkInitStruct.SYSCLKSource  = RCC_SYSCLKSOURCE_PLLCLK;
//    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, pFLatency) != HAL_OK)
//    {
//      while (1);
//    }
//  }
//  else
//  {
//    /*mcu did not enter stop mode because NVIC had a pending IT*/
//  }

//  /* initializes the peripherals */
//  Sx_Board_IoInit();

//  UTILS_EXIT_CRITICAL_SECTION();
//  /* USER CODE BEGIN ExitStopMode_2 */

//  /* USER CODE END ExitStopMode_2 */
}

void PWR_EnterSleepMode(void)
{
  /* USER CODE BEGIN EnterSleepMode_1 */

  /* USER CODE END EnterSleepMode_1 */
  /* USER CODE BEGIN EnterSleepMode_2 */

  /* USER CODE END EnterSleepMode_2 */
//  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
  /* USER CODE BEGIN EnterSleepMode_3 */

  /* USER CODE END EnterSleepMode_3 */
}

void PWR_ExitSleepMode(void)
{
  /* USER CODE BEGIN ExitSleepMode_1 */

  /* USER CODE END ExitSleepMode_1 */

  /* USER CODE BEGIN ExitSleepMode_2 */

  /* USER CODE END ExitSleepMode_2 */
}

/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Private Functions Definition -----------------------------------------------*/
/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
