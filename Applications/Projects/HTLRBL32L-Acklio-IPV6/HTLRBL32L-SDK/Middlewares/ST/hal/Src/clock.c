/**
******************************************************************************
* @file    clock.c 
* @author  AMS -  RF Application Team
* @version V1.0.0
* @date    29-March-2019
* @brief   clock APIs based on SySTick
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
/* Includes ------------------------------------------------------------------*/
#include "BlueNRG_LPx.h"
#include "clock.h"
#include "system_BlueNRG_LP.h"
#include "rf_driver_ll_utils.h"
#include "rf_driver_ll_rcc.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile tClockTime sys_tick_count;
const tClockTime CLOCK_SECOND = 1000;

/*---------------------------------------------------------------------------*/
void SysCount_Handler(void) 
{
  sys_tick_count++;
  //printf("%d\r\n", sys_tick_count); //TBR
}

/*---------------------------------------------------------------------------*/

void Clock_Init(void)
{
  /** Configure SysTick to generate Interrupt with 1ms period */
  
  LL_RCC_ClocksTypeDef RCC_Clocks;
  
  LL_RCC_GetSystemClocksFreq(&RCC_Clocks);
  
  SysTick_Config(((RCC_Clocks.SYSCLK_Frequency)/1000) -1UL); 
}

/*---------------------------------------------------------------------------*/

tClockTime Clock_Time(void)
{
  return sys_tick_count;
}

/*---------------------------------------------------------------------------*/
/**
 * Wait for a multiple of 1 ms.
 *
 */
void Clock_Wait(uint32_t i)
{
  tClockTime start;

  start = Clock_Time();
  while(Clock_Time() - start < (tClockTime)i);
}
/*---------------------------------------------------------------------------*/

