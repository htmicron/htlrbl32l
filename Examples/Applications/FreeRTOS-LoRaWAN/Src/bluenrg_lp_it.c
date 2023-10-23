/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/bluenrg_lp_it.c
  * @author  RF Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
#include "bluenrg_lp_it.h"
#include "clock.h"
#include "hal_miscutil.h"
#include "crash_handler.h"
#include "spi.h"
#include "hal_wrappers.h"
#include "timeServer.h"
#include "sx126x.h"
#include "radio.h"

extern EXTI_HandleTypeDef HEXTI_InitStructure;

/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
 
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/


/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */ 
/******************************************************************************/


NOSTACK_FUNCTION(NORETURN_FUNCTION(void HardFault_IRQHandler(void)))
{
	printf("\nHard fault\n");
	while (1);
}


/**
//  * @brief This function handles System tick timer.
//  */

void SPI1_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&hspi1);

}
	
void GPIOB_IRQHandler(void){  
  if(HAL_EXTI_GetPending( &HEXTI_InitStructure )){
    HAL_EXTI_IRQHandler( &HEXTI_InitStructure );
  }
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  RadioIrqProcess();
}

IRQn_Type MSP_GetIRQn( uint16_t GPIO_Pin)
{

return GPIOB_IRQn;
}
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
 // TimerIrqHandler( );
}

void RTC_IRQHandler(void)
{
	TimerIrqHandler( );

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
