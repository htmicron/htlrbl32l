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
#include "HT_push_button.h"

extern EXTI_HandleTypeDef HEXTI_InitStructure;
extern EXTI_HandleTypeDef Button_EXTI_InitStructure;

volatile uint32_t debounce_count = 0;
volatile uint32_t debounce_last = 0;

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

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_IRQHandler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_IRQHandler(void)
{

}

/**
//  * @brief This function handles System tick timer.
//  */
void SysTick_IRQHandler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  debounce_count++;
}

void SPI1_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&hspi1);

}

void GPIOA_IRQHandler(void){ 
  static uint32_t debounce_last = 0;
   
  if(HAL_EXTI_GetPending(&Button_EXTI_InitStructure)){
    if((debounce_count - debounce_last) >= 35) { 
      /* Add the SW no bounce */
      debounce_last = debounce_count;
      
      /* Handle user button press in dedicated function */
      HAL_EXTI_IRQHandler(&Button_EXTI_InitStructure);
    }
  }
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

void HAL_PWR_MNGR_WakeupIOCallback(uint32_t source) {

#if DEEP_SLEEP_MODE == 1
  printf("Waking up..\n");
  HT_PB_SetState(SM_PUSH_BUTTON_HANDLER);
#endif

}

void RTC_IRQHandler(void)
{
	//printf("RTC_IRQHandler\n");
	TimerIrqHandler( );

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
