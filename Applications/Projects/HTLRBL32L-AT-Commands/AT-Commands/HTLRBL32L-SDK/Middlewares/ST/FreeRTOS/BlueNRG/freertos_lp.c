/**
  ******************************************************************************
  * @file    freertos_lp.c 
  * @author  AMS RF Application Team
  * @brief   Support ot tickless idle functionality of FreeRTOS for BlueNRG
  *          application processors.
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
  * <h2><center>&copy; COPYRIGHT 2018 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the ARM CM3 port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "bluenrg_lp_stack.h"   
#include "rf_driver_hal_power_manager.h"
#include "rf_driver_hal_vtimer.h"


static VTIMER_HandleType TimerHandle;

static WakeupSourceConfig_TypeDef wakeupConfig = {0,0,0};

/*-----------------------------------------------------------*/
void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
{
  eSleepModeStatus eSleepStatus;
  uint32_t timeBeforeSleep, timeAfterSleep;
  PowerSaveLevels stopLevel;
  
  timeBeforeSleep = HAL_VTIMER_GetCurrentSysTime();
  
  eSleepStatus = eTaskConfirmSleepModeStatus();  
  
  /* Start a timer to wake up the system after the given interval if there
    are tasks waiting for a timeout. Since this may take some time, it is not
    called inside the critical section.  */
  if(eSleepStatus == eStandardSleep)
  {
    HAL_VTIMER_StopTimer(&TimerHandle);
    HAL_VTIMER_StartTimerMs(&TimerHandle, (xExpectedIdleTime*1000)/configTICK_RATE_HZ);
  }
  
  /* Enter a critical section. */
  __disable_irq();
  
  /* Ensure it is still ok to enter the sleep mode. */
  eSleepStatus = eTaskConfirmSleepModeStatus();
  
  if( eSleepStatus == eAbortSleep )
    {
        /* A task has been moved out of the Blocked state since this macro was
        executed, or a context siwth is being held pending.  Do not enter a
        sleep state.  Exit the critical section. */
        __enable_irq();
        HAL_VTIMER_StopTimer(&TimerHandle);
    }
    else
    {
        if( eSleepStatus == eNoTasksWaitingTimeout )
        {
            /* It is not necessary to configure an interrupt to bring the
            microcontroller out of its low power state at a fixed time in the
            future. */
           /* No need to stop the timer since it was started only if eSleepStatus was
            eStandardSleep. It may happen that eSleepStatus becomes eAbortSleep
            after the second call to eTaskConfirmSleepModeStatus(), but it cannot
            happen that eSleepStatus becomes eNoTasksWaitingTimeout if it
            was eStandardSleep. */                    
          HAL_PWR_MNGR_Request(POWER_SAVE_LEVEL_STOP_NOTIMER, wakeupConfig, &stopLevel); 
        }
        else
        {
            /* Enter the low power state. */ 
           HAL_PWR_MNGR_Request(POWER_SAVE_LEVEL_STOP_WITH_TIMER, wakeupConfig, &stopLevel);
            
           if(stopLevel > POWER_SAVE_LEVEL_CPU_HALT)
            {              
              /* Determine how long the microcontroller was actually in a low power
              state for, which will be less than xExpectedIdleTime if the
              microcontroller was brought out of low power mode by an interrupt
              other than that configured by the vSetWakeTimeInterrupt() call.
              Note that the scheduler is suspended before
              portSUPPRESS_TICKS_AND_SLEEP() is called, and resumed when
              portSUPPRESS_TICKS_AND_SLEEP() returns.  Therefore no other tasks will
              execute until this function completes. */
              timeAfterSleep = HAL_VTIMER_GetCurrentSysTime();
              
              /* Correct the kernels tick count to account for the time the
              microcontroller spent in its low power state. */
              
              /* TODO: Account for the rounding to millisecond time units.
                Set the systick LOAD register to the appropriate value.  */
              
              vTaskStepTick( HAL_VTIMER_DiffSysTimeMs(timeAfterSleep,timeBeforeSleep)/portTICK_PERIOD_MS );
            }
        }

        /* Exit the critical section - it might be possible to do this immediately
        after the prvSleep() calls. */
        __enable_irq();
    }
}
/*-----------------------------------------------------------*/
/* Set wakeup configuration (GPIOs and RTC) to be used when FreeRTOS Idle Task will call BlueNRG sleep function.
  See documentation for WakeupSourceConfig_TypeDef. */
void BlueNRG_SetWakeupMask(WakeupSourceConfig_TypeDef wsConfig)
{
   wakeupConfig = wsConfig;   
}
