/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/bluenrg_lp_hal_msp.c
  * @author  RF Application Team
  * @brief   HAL MSP module.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "peripheral_init.h"
#include "radio.h"
#include "rf_driver_ll_pwr.h"
#include "rf_driver_hal_rng.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
 
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/

EXTI_HandleTypeDef HEXTI_InitStructure;

/**

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

void MX_RNG_Init(RNG_HandleTypeDef *hrng)
{
  hrng->Instance = RNG;
  if (HAL_RNG_Init(hrng) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_RNG_MspInit(RNG_HandleTypeDef* hrng)
{
  if(hrng->Instance==RNG)
  {
    /* Peripheral clock enable */
    __HAL_RCC_RNG_CLK_ENABLE();
  }
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
