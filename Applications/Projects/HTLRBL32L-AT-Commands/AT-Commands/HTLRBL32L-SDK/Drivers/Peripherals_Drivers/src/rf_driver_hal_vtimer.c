/**
******************************************************************************
* @file    rf_driver_hal_vtimer.c 
* @author  RF Application Team
* @brief   Virtual timer and Radio timer high level APIs
* @details This file implements the software layer that provides the virtualization of the
* resources of a single hardware timer in order to allocate many user virtual timers.
* The only constraint to the number of virtual timers is the memory.
* Each instance of a virtual timer is placed in an queue ordered by the expiration time
* and it can be linked to a callback.
* The timer tick is in charge to execute the callback linked to each virtual timer
* and to update the hardware timeout to gurantee the expiration of the next virtual
* timer in the queue.
* A special virtual timer called calibration/anti-wrapping timer is automatically armed
* by the software. This timer can address two tasks:
* - it is in charge to maintain the never wrapping virtual time base.
* - if the slow clock calibration is enabled, it starts the calibration procedure at each
* calibration interval specified during the initialization.
*
* A timer is intended as an event programmed in the future at a certain absolute expiration time
* on a time base. In this implementation the time base grows on 64 bits. Then, it never wraps.
* However, due to hardware timer finite length and in order to maintain the timing coherency, the time base
* must be maintained at least one time before the hardware timer wraps.  
* Then even if the slow clock calibration is disabled, the calibration/anti-wrapping timer
* is always active with the only role to maintain the time base and it will expire
* at a rate that depends on the hardware timer capability.
* The time base unit is a STU that is the unit exposed to the user and it is equal to 625/256 us. 
* The calibration/anti-wrapping mechanism is not managed by the user.
*
* This software layer also exposes the possibility to program a radio timer.
* A radio timer allows the user to trigger an already configured radio transaction.
* The duties of this library does not include the configuration of a radio transaction.
* This layer tries to exploit the last calibration values to program the radio activity
* in order to improve the accuracy. In this case, the radio event is not immediately programmed 
* when it is requested, but only when the next calibration values are available.
* Since the calibration values are available inside the timer tick when the calibration is over,
* the application must ensure that the timer tick is called after the calibration timer 
* expiration within a certain margin in order to avoid that the radio event is shifted in the
* past and cannot be anymore programmed.
*
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
* <h2><center>&copy; COPYRIGHT 2020 STMicroelectronics</center></h2>
******************************************************************************
*/ 
/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdio.h>
#include "rf_driver_hal_vtimer.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @defgroup VTIMER VTIMER
  * @brief VTIMER module driver
  * @{
  */

/** @defgroup VTIMER_Private_Macros VTIMER Private Macros
  * @{
  */

#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
                                __disable_irq(); \
/* Must be called in the same scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

#define MAX(a,b) ((a) < (b) )? (b) : (a)
#define MIN(a,b) ((a) < (b) )? (a) : (b)
#define DIFF8(a,b) ((a)>=(b) ? ((a)-(b)) : (256+((a)-(b))))
#define INCREMENT_EXPIRE_COUNT_ISR (HAL_VTIMER_Context.expired_count = ((HAL_VTIMER_Context.expired_count + 1) == HAL_VTIMER_Context.served_count) ? HAL_VTIMER_Context.expired_count : (HAL_VTIMER_Context.expired_count + 1))
#define INCREMENT_EXPIRE_COUNT ATOMIC_SECTION_BEGIN(); INCREMENT_EXPIRE_COUNT_ISR ; ATOMIC_SECTION_END();

/**
  * @}
  */

/** @defgroup VTIMER_Private_Constants VTIMER Private Constants
  * @{
  */

/*Minimum threshold to safely program the radio timer (expressed in STU) */
#define TIMER1_MARGIN (10)
                                  
/*  Delay to program a radio timer in the worst case (in STU).
  This is the sum of: 1st init dalay, 2 init delay and tx delay (118 + 65 + 2)  */
#define TIMER1_INIT_DELAY (76)

/* Minimum threshold in STU to safely clear radio timers.
The wakeup timer in the worst case triggers about 30us in advance.
This must be considered when the radio timer is cleared.
Then a window of about 30 us is considered as critical, that is 
it is not sure the timer can be cleared properly */
#define CLEAR_MIN_THR (15)

/* Threshold to take into account the calibration duration. */
#define CALIB_SAFE_THR (370)

/* Extra margin to consider before going in low power mode */
#define LOW_POWER_THR (30)

#if HOST_WAKEUP_FIX_ENABLE
/* HOST_MARGIN is the margin in STU needed to program a pending radio operation after the host timer is triggered */                               
#define HOST_MARGIN (200)
#endif

/**
  * @}
  */

/** @defgroup VTIMER_Private_Types VTIMER Private Types
  * @{
  */

typedef struct HAL_VTIMER_ContextS {
  uint32_t PeriodicCalibrationInterval;  /*!< Periodic calibration interval in ms, to disable set to 0 */
  BOOL calibration_in_progress;  /*!< Flag to indicate that a periodic calibration has been started */
  VTIMER_HandleType *rootNode; /*!< First timer of the host timer queue */
  BOOL enableTimeBase;      /*!< Internal flag. User can ignore it*/
  uint32_t hs_startup_time; /*!< HS startup time */
  uint8_t expired_count; /*!< Progressive number to indicate expired timers */
  uint8_t served_count; /*!< Progressive number to indicate served expired timers */
} HAL_VTIMER_ContextType;

typedef struct VTIMER_RadioHandleTypeS {
    uint64_t expiryTime;
    BOOL cal_req;
    BOOL active;
    BOOL pending;
    BOOL event_type;
} VTIMER_RadioHandleType;

/**
  * @}
  */

/** @defgroup VTIMER_Private_Variables VTIMER Private Variables
  * @{
  */

static HAL_VTIMER_ContextType HAL_VTIMER_Context;
static VTIMER_HandleType calibrationTimer;
static VTIMER_RadioHandleType radioTimer;

#if HOST_WAKEUP_FIX_ENABLE
/* If hostIsRadioPending is true, the virtual timer callback will be triggered when the wakeup timer triggers */ 
static uint8_t hostIsRadioPending;
/* It depends on the hs startup time. See HOST_MARGIN */
static uint32_t hostMargin;
/* Wait the next calibration to get the latest values */
static uint8_t waitCal;
#endif

static TIMER_CalibrationType calibrationData;

/**
  * @}
  */


/** @defgroup VTIMER_Private_Function VTIMER Private Function 
  * @{
  */

/*Check if it is time to program the pending radio timer (large timeouts).
1) The radio event is before the next calibration event. Then the timer must be programmed.
2) The calibration timer expired but the calibration didn't start and the values not updated as expected.
   Then the next calibration event is missleading. The radio timer must be programmed.
3) The radio event is after the next calibration event. Then the timer will be programmed with the latest values.
The check on the next calibration event is made even though the calibration is disabled (max cal. interval)
in order to avoid counter wrapping with timeouts far in the future.
*/
static void _check_radio_activity(VTIMER_RadioHandleType * timerHandle, uint8_t *expired)
{
  uint64_t nextCalibrationEvent, currentTime; 
                                 
  *expired = 0;
  
  if (timerHandle->pending){
    nextCalibrationEvent = calibrationData.last_calibration_time + \
                           HAL_VTIMER_Context.PeriodicCalibrationInterval;
    ATOMIC_SECTION_BEGIN();
    currentTime = TIMER_GetCurrentSysTime();
    
    if((timerHandle->expiryTime < (nextCalibrationEvent + RADIO_ACTIVITY_MARGIN)) \
                                    || \
      (currentTime > (nextCalibrationEvent + CALIB_SAFE_THR)))
     {
       if (timerHandle->expiryTime - TIMER1_INIT_DELAY > (currentTime + TIMER1_MARGIN)){
        *expired = TIMER_SetRadioTimerValue(timerHandle->expiryTime, timerHandle->event_type,timerHandle->cal_req);
        timerHandle->pending = FALSE; /* timer has been served. No more pending */
        timerHandle->active = TRUE; /* timer has been programmed and it becomes ACTIVE */
        ATOMIC_SECTION_END();
      }
      else{
        radioTimer.pending = FALSE;
        ATOMIC_SECTION_END();
        *expired = 1;
      }
    }
    else{
#if HOST_WAKEUP_FIX_ENABLE
      waitCal = 1;
#endif
      ATOMIC_SECTION_END();
    }
  }
}

static void calibration_callback (void *handle)
{
  TIMER_StartCalibration();
  HAL_VTIMER_Context.calibration_in_progress = TRUE;
}

static VTIMER_HandleType * _remove_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle)
{
  VTIMER_HandleType *current = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;
  
  while ((current!=NULL) && (current != handle)) {
    prev = current;
    current=current->next;
  }
  
  if (current == NULL) {
    /* Not found */
  }
  else if (current == rootNode) {
    /* New root node */
    returnValue = current->next;
  }
  else {
    prev->next = current->next;
  }
  
  return returnValue;
}

static VTIMER_HandleType * _insert_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle)
{
  VTIMER_HandleType *current = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;
  
  while ((current!=NULL) && (current->expiryTime < handle->expiryTime)) {
    prev = current;
    current=current->next;
  }
  
  handle->next = current;
  
  if (prev == NULL) {
    /* We are the new root */
    returnValue = handle;
  }
  else {
    prev->next = handle;
  }
  
  return returnValue;
}

/* Set timeout and skip non active timers */
static VTIMER_HandleType *_update_user_timeout(VTIMER_HandleType *rootNode, uint8_t *expired)
{
  VTIMER_HandleType *curr = rootNode;
  VTIMER_HandleType *rootOrig = rootNode;
  int64_t delay;
  *expired =0;
  while (curr != NULL) {
    if (curr->active) {
      ATOMIC_SECTION_BEGIN();
#if HOST_WAKEUP_FIX_ENABLE
      uint8_t dummy;
      BOOL share = FALSE;
      _check_radio_activity(&radioTimer,&dummy);
#endif
      delay = curr->expiryTime-TIMER_GetCurrentSysTime();
      if (delay > 0) {
        /* Protection against interrupt must be used to avoid that the called function will be interrupted
          and so the timer programming will happen after the target time is already passed
          leading to a timer expiring after timer wraps, instead of the expected delay */
#if HOST_WAKEUP_FIX_ENABLE
        /* Is the active radio operation before or too close the host timeout? */
        if(((radioTimer.expiryTime) < (curr->expiryTime + hostMargin)) && radioTimer.active)
        {
          if((radioTimer.expiryTime >= curr->expiryTime) && radioTimer.active)
          {
            hostIsRadioPending = 1;
          }
        }
        else
        {
          /* It's fine to program the wakeup timer for an host wakeup */
          share = TRUE;
        }
        TIMER_SetRadioHostWakeupTime(delay, &share);
        if(share == TRUE)
        {
          radioTimer.pending |= radioTimer.active;
          radioTimer.active = FALSE; 
        }
#else
        TIMER_SetWakeupTime(delay, TRUE);
#endif
        ATOMIC_SECTION_END();
        break;
      }
      else {
        *expired = 1;
        ATOMIC_SECTION_END();
        break;
      }
    }
    curr=curr->next;
  }
  if (*expired)
    return rootOrig;
  return curr;
}

/* Check the number of expired timer from rootNode (ordered list of timers) and return the list of expired timers */
static VTIMER_HandleType *_check_callbacks(VTIMER_HandleType *rootNode,VTIMER_HandleType **expiredList)
{
  
  VTIMER_HandleType *curr = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;
  *expiredList = rootNode;
  
  int64_t delay;
  uint32_t expiredCount = 0;
  
  while (curr != NULL) {
    
    if (curr->active) {
      delay = curr->expiryTime-TIMER_GetCurrentSysTime();
      
      if (delay > 5) { /*TBR*/
        /* End of expired timers list*/
        break;
      }
    } 
    
    prev = curr;
    curr=curr->next;
    expiredCount++;
  }
  
  if (expiredCount) {
    /* Some timers expired */
    prev->next=NULL;
    returnValue = curr;
  }
  else {
    /* No timer expired */
    *expiredList = NULL;
  }
  
  return returnValue;
}

#if HOST_WAKEUP_FIX_ENABLE
static void _check_host_activity(void)
{
  uint8_t expired;
  HAL_VTIMER_Context.rootNode = _update_user_timeout(HAL_VTIMER_Context.rootNode, &expired);
  if (expired == 1) {
    /* A new root timer is already expired, mimic timer expire */
    INCREMENT_EXPIRE_COUNT_ISR;
  }
}
#endif

static int _start_timer(VTIMER_HandleType *timerHandle, uint64_t time)
{
  uint8_t expired = 0;

  /* The timer is already started*/
  if(timerHandle->active)
  {
    return 1;
  }
  timerHandle->expiryTime = time;
  timerHandle->active = TRUE;
  if (_insert_timer_in_queue(HAL_VTIMER_Context.rootNode, timerHandle) == timerHandle) {
    HAL_VTIMER_Context.rootNode = _update_user_timeout(timerHandle, &expired);
    if (expired) {
      /* A new root timer is already expired, mimic timer expire that is normally signaled
       through the interrupt handler that increase the number of expired timers*/
      INCREMENT_EXPIRE_COUNT;
    }
  }
  return expired;
}

static void _virtualTimeBaseEnable(FunctionalState state)
{
  if(state != DISABLE)
  {
    if (HAL_VTIMER_Context.enableTimeBase == FALSE)
    {
      calibration_callback(&calibrationTimer);
      HAL_VTIMER_Context.enableTimeBase = TRUE;
    }
  }
  else
  {
    HAL_VTIMER_StopTimer(&calibrationTimer);
    HAL_VTIMER_Context.enableTimeBase = FALSE;
  }
}

#if HOST_WAKEUP_FIX_ENABLE
static void _set_controller_as_host(void)
{
  blueglob->BYTE4 &= ~(1<<7);
  blueglob->BYTE22 = 0x0;
  blueglob->BYTE23 = 0x0;
}
#endif

/**
  * @}
  */

/** @defgroup VTIMER_Exported_Functions VTIMER Exported Functions
  * @{
  */

/**
 * @brief  Return the status of the radio timer.
 *         The timeout of the last radio timer activity taken into account by the Timer Module
 *         is saved in the variable passed as parameter.
 * @param  time: Pointer of the variable where the time of the last radio activity scheduled is stored
 *               The time is expressed in STU.
 * @retval 0 if no radio timer is pending.
 * @retval 1 if a radio timer is pending.
 */
TimerStatus HAL_VTIMER_GetRadioTimerValue(uint64_t *time)
{
  *time = radioTimer.expiryTime;
  if((radioTimer.pending) || (TIMER_GET_BLUE_WAKEUP_EN) || (TIMER_GET_TIMER1_STATUS))
    return RADIO_TIMER_PENDING;
  else
    return RADIO_TIMER_OFF;
}

/**
 * @brief  Clear the last radio activity scheduled disabling the radio timers too.
 *         Furthermore, it returns if the timeout is too close with respect the current time and
 *         the radio activity might not be cleared in time.
 * @retval 0 if the radio activity has been cleared successfully.
 * @retval 1 if it is too late to clear the last radio activity.
 * @retval 2 if it might not be possible to clear the last radio activity.
 */
uint8_t HAL_VTIMER_ClearRadioTimerValue(void)
{
  int64_t time_diff;
  uint8_t retVal;
  
  TIMER_ClearRadioTimerValue();
  radioTimer.active = FALSE;
  radioTimer.pending = FALSE;

  /*The rfSetup is different if Timer1 or Wakeup timer is programmed*/
  ATOMIC_SECTION_BEGIN();
  time_diff = radioTimer.expiryTime \
              - TIMER_GetCurrentSysTime() \
              - __TIMER_GetSysRfSetupTime();
  ATOMIC_SECTION_END();
  
  if(time_diff <= 0)
    retVal = HAL_VTIMER_LATE;
  else if (time_diff < CLEAR_MIN_THR)
    retVal = HAL_VTIMER_CRITICAL;
  else{
    retVal = HAL_VTIMER_SUCCESS;
  }
  return retVal;
}

/**
 * @brief  Disable Timer2. 
 * @retval None
 */
void HAL_VTIMER_StopRadioTimer2(void)
{
  TIMER_ClearRadioTimer2();
}

/**
 * @brief   If the wakeup timer triggers for a host wakeup, a pending radio activity is programmed.
 *          If the wakeup timer triggers for a radio activity, a pending virtual timer callback is executed.
 * @warning To be considered only if HOST_WAKEUP_FIX_ENABLE is 1.
 * @retval  None
 */
void HAL_VTIMER_WakeUpCallback(void)
{
#if HOST_WAKEUP_FIX_ENABLE
   volatile uint32_t status;
   uint8_t expired;
   
  _check_radio_activity(&radioTimer,&expired);
  if(hostIsRadioPending)
  {
    hostIsRadioPending = 0;
    HAL_VTIMER_TimeoutCallback();
  }

  WAKEUP->WAKEUP_BLE_IRQ_STATUS |= 1;
  status = WAKEUP->WAKEUP_BLE_IRQ_STATUS;
#endif
}

/**
 * @brief  Virtual timer Timeout Callback. It signals that a host timeout occured.
 * @retval None
 */
void HAL_VTIMER_TimeoutCallback(void)
{
  volatile uint32_t status;
#if HOST_WAKEUP_FIX_ENABLE
  hostIsRadioPending = 0;
#endif
  /* Disable host timer */
  TIMER_DISABLE_CM0_TIMER;
  INCREMENT_EXPIRE_COUNT_ISR;
  /* Clear the interrupt */
  WAKEUP->WAKEUP_CM0_IRQ_STATUS |= 1;
  status = WAKEUP->WAKEUP_CM0_IRQ_STATUS;
}

/**
 * @brief  Radio activity finished.
 * @retval None
 */
void HAL_VTIMER_RadioTimerIsr(void)
{
#if HOST_WAKEUP_FIX_ENABLE
  if (!(TIMER_GET_TIMER1_STATUS || TIMER_GET_TIMER2_STATUS))
  {
    _check_host_activity();
  }
#endif
}

/**
 * @brief  Starts a one-shot virtual timer for the given absolute timeout value
 *         expressed in internal time units.
 * @param  timerHandle: The virtual timer
 * @param  time: Absolute time expressed in STU.
 * @retval 0 if the timerHandle is valid.
 * @retval 1 if the timerHandle is not valid. It is already started.
 */
int HAL_VTIMER_StartTimerSysTime(VTIMER_HandleType *timerHandle, uint64_t time)
{
  uint8_t retVal;
  retVal = _start_timer(timerHandle, time);
  _virtualTimeBaseEnable(ENABLE);
  return retVal;
}

/**
 * @brief  Starts a one-shot virtual timer for the given relative timeout value expressed in ms
 * @param  timerHandle: The virtual timer
 * @param  msRelTimeout: The relative time, from current time, expressed in ms
 * @retval 0 if the timerHandle is valid.
 * @retval 1 if the timerHandle is not valid. It is already started.
 */
int HAL_VTIMER_StartTimerMs(VTIMER_HandleType *timerHandle, uint32_t msRelTimeout)
{
  uint64_t temp = msRelTimeout;
  uint8_t retVal;
  retVal = _start_timer(timerHandle, TIMER_GetCurrentSysTime() + (temp*TIMER_SYSTICK_PER_10MS)/10);
  _virtualTimeBaseEnable(ENABLE);
  return retVal;
}

/**
 * @brief  Schedules a radio activity for the given absolute timeout value expressed in STU.
 *         If the calibration of the low speed oscillator is needed, if it is possible,
 *         the radio timer will be programmed with the latest calibration data.
 * @param  time: Absolute time expressed in STU.
 * @param  event_type: Specify if it is a TX (1) or RX (0) event.
 * @param  cal_req: Specify if PLL calibration is requested (1) or not (0).
 * @retval 0 if radio activity has been scheduled succesfully.
 * @retval 1 if radio activity has been rejected (it is too close or in the past).
 */
uint8_t HAL_VTIMER_SetRadioTimerValue(uint32_t time, uint8_t event_type, uint8_t cal_req)
{
  uint8_t retVal = 0;
#if HOST_WAKEUP_FIX_ENABLE
  uint64_t current_time;
#endif
  radioTimer.event_type = event_type;
  radioTimer.cal_req = cal_req;
  radioTimer.expiryTime = calibrationData.last_calibration_time + (uint32_t)(time - (uint32_t)calibrationData.last_calibration_time);
  radioTimer.active = FALSE;
  radioTimer.pending = TRUE;

#if HOST_WAKEUP_FIX_ENABLE
  
  current_time = TIMER_GetCurrentSysTime();
  
  if(HAL_VTIMER_Context.rootNode->expiryTime < current_time ||
     ((radioTimer.expiryTime < (HAL_VTIMER_Context.rootNode->expiryTime + hostMargin)) && HAL_VTIMER_Context.rootNode->active) || !HAL_VTIMER_Context.rootNode->active)
  {
    /* Program the radio timer */
    _check_radio_activity(&radioTimer, &retVal);
    if((radioTimer.expiryTime >= HAL_VTIMER_Context.rootNode->expiryTime) && HAL_VTIMER_Context.rootNode->active)
    {
      /*The radio operation is before or too close the host timeout*/
      hostIsRadioPending = 1;
    }
  }
  else
  {
    /* If radio timer is not programmed, an emulated host timer is already programmed.
       Make sure radio errors are disabled.
      This call is not needed if radio errors are not enabled by the BLE stack. */
    _set_controller_as_host();
  }
#else
  _check_radio_activity(&radioTimer, &retVal);
#endif
  
  _virtualTimeBaseEnable(ENABLE);
  return retVal;
}

/**
 * @brief  Get the last anchorPoint in system time unit.
 * @return TimerCapture register in system time unit.
 */
uint64_t HAL_VTIMER_GetAnchorPoint(void)
{
  return TIMER_GetAnchorPoint();
}

/**
 * @brief  Stops the one-shot virtual timer specified if found
 * @param  timerHandle: The virtual timer
 * @retval None
 */
void HAL_VTIMER_StopTimer(VTIMER_HandleType *timerHandle)
{
  VTIMER_HandleType *rootNode = _remove_timer_in_queue(HAL_VTIMER_Context.rootNode, timerHandle);
  uint8_t expired = 0;
  timerHandle->active=FALSE;
  if (HAL_VTIMER_Context.rootNode != rootNode) {
    HAL_VTIMER_Context.rootNode = _update_user_timeout(rootNode, &expired);
    if (expired) {
      /* A new root timer is already expired, mimic timer expire */
      INCREMENT_EXPIRE_COUNT;
    }
  }
  else
     HAL_VTIMER_Context.rootNode = rootNode;
}	

/**
 * @brief  This function returns the current reference time expressed in system time units.
 *         The returned value can be used as absolute time parameter where needed in the other
 *         HAL_VTIMER* APIs
 * @return absolute current time expressed in system time units.
 */
uint64_t HAL_VTIMER_GetCurrentSysTime(void)
{
  return TIMER_GetCurrentSysTime();
}

/**
 * @brief  This function returns the sum of an absolute time and a signed relative time.
 * @param  sysTime: Absolute time expressed in internal time units.
 * @param  msTime: Signed relative time expressed in ms.
 * @return 64bit resulting absolute time expressed in internal time units.
 */
uint64_t HAL_VTIMER_AddSysTimeMs(uint64_t sysTime, int32_t msTime)
{
  int32_t sysTick = (msTime * TIMER_SYSTICK_PER_10MS)/10;
  return (sysTime+sysTick);
}

/**
 * @brief  Returns the difference between two absolute times: sysTime1-sysTime2.
 *         The resulting value is expressed in ms.
 * @param  sysTime2: Absolute time expressed in internal time units.
 * @param  sysTime1: Absolute time expressed in internal time units.
 * @return resulting signed relative time expressed in ms.
 */
int64_t HAL_VTIMER_DiffSysTimeMs(uint64_t sysTime1, uint64_t sysTime2)
{
  return ((sysTime1-sysTime2)*10)>>12;
}

/**
 * @brief Returns the absolute expiry time of a running timer expressed in internal time units.
 * @param timerHandle: The virtual timer
 * @param sysTime: Absolute time expressed in internal time units.
 */
int HAL_VTIMER_ExpiryTime(VTIMER_HandleType *timerHandle, uint64_t *sysTime)
{
  *sysTime = timerHandle->expiryTime;
  return 0;
}

/**
 * @brief  Returns the number of timers in the queue.
 * @return number of timers in the queue.
 */
uint32_t HAL_VTIMER_GetPendingTimers(void)
{
  VTIMER_HandleType *curr = HAL_VTIMER_Context.rootNode;
  uint32_t counter = 0;
  while (curr != NULL) {
    counter++;
    curr = curr->next;
  }
  return counter;
}

/**
 * @brief  Initialize the timer module. It must be placed in the initialization
 *         section of the application.
 * @retval None
 */
void HAL_VTIMER_Init(HAL_VTIMER_InitType *HAL_TIMER_InitStruct)
{
  TIMER_InitType TIMER_InitStruct;
  TIMER_Enable_CPU_WKUP();
#if HOST_WAKEUP_FIX_ENABLE
  WAKEUP->WAKEUP_BLE_IRQ_STATUS |= 1;
  WAKEUP->WAKEUP_BLE_IRQ_ENABLE |= 1;
  NVIC_EnableIRQ(BLE_WKUP_IRQn);
  hostMargin = MAX(HOST_MARGIN,HAL_TIMER_InitStruct->XTAL_StartupTime);
#endif
  NVIC_EnableIRQ(BLE_ERROR_IRQn);
  TIMER_InitStruct.TIMER_InitialCalibration = HAL_TIMER_InitStruct->EnableInitialCalibration;
  TIMER_InitStruct.TIMER_PeriodicCalibration = HAL_TIMER_InitStruct->PeriodicCalibrationInterval;
  TIMER_InitStruct.XTAL_StartupTime = HAL_TIMER_InitStruct->XTAL_StartupTime;
  TIMER_Init(&TIMER_InitStruct);
  TIMER_GetCurrentCalibrationData(&calibrationData); 
  HAL_VTIMER_Context.rootNode = NULL;
  HAL_VTIMER_Context.enableTimeBase = TRUE;
  radioTimer.active = FALSE;
  radioTimer.pending = FALSE;
  radioTimer.expiryTime = 0;
  HAL_VTIMER_Context.hs_startup_time = HAL_TIMER_InitStruct->XTAL_StartupTime;
  HAL_VTIMER_Context.expired_count=0;
  HAL_VTIMER_Context.served_count=0;
  HAL_VTIMER_Context.PeriodicCalibrationInterval = (TIMER_SYSTICK_PER_10MS * HAL_TIMER_InitStruct->PeriodicCalibrationInterval)/10;
  HAL_VTIMER_Context.calibration_in_progress = FALSE;
  if (HAL_VTIMER_Context.PeriodicCalibrationInterval == 0)
    HAL_VTIMER_Context.PeriodicCalibrationInterval = TIMER_MachineTimeToSysTime(TIMER_MAX_VALUE-TIMER_WRAPPING_MARGIN);
  else
    HAL_VTIMER_Context.PeriodicCalibrationInterval = MIN(HAL_VTIMER_Context.PeriodicCalibrationInterval,
                                                       TIMER_MachineTimeToSysTime(TIMER_MAX_VALUE-TIMER_WRAPPING_MARGIN));
  calibrationTimer.callback = calibration_callback;
  calibrationTimer.userData = NULL;
  _start_timer(&calibrationTimer, TIMER_GetCurrentSysTime() + HAL_VTIMER_Context.PeriodicCalibrationInterval);
}

/**
 * @brief  Timer module state machine. Check and schedule the calibration.
 *         Check expired timers and execute user callback.
 *         It must be placed inside the infinite loop.
 * @retval None
 */
void HAL_VTIMER_Tick(void)
{
  uint8_t expired = 0;

  ATOMIC_SECTION_BEGIN();
  if(radioTimer.active){
    if(radioTimer.expiryTime < TIMER_GetCurrentSysTime()){
      radioTimer.active = FALSE;
    }
  }
  ATOMIC_SECTION_END();

  /* Check for expired timers */  
  while (DIFF8(HAL_VTIMER_Context.expired_count,HAL_VTIMER_Context.served_count)) {
    VTIMER_HandleType *expiredList, *curr;
    uint8_t to_be_served = DIFF8(HAL_VTIMER_Context.expired_count,HAL_VTIMER_Context.served_count);
    
    HAL_VTIMER_Context.rootNode = _check_callbacks(HAL_VTIMER_Context.rootNode, &expiredList);
    
    /* Call all the user callbacks */
    curr=expiredList;
    while (curr != NULL) {

      /* Save next pointer, in case callback start the timer again */
      VTIMER_HandleType *next = curr->next;
      curr->active = FALSE;
      if (curr->callback)
        curr->callback(curr); /* we are sure a callback is set?*/
      curr = next;
    }
    
    HAL_VTIMER_Context.rootNode = _update_user_timeout(HAL_VTIMER_Context.rootNode, &expired);
    if (expired == 1) {
      /* A new root timer is already expired, mimic timer expire */
      INCREMENT_EXPIRE_COUNT;
    }
    HAL_VTIMER_Context.served_count += to_be_served;
  }
  
  /* Check for periodic calibration */
  if (HAL_VTIMER_Context.calibration_in_progress) {
     if (TIMER_IsCalibrationRunning() == FALSE) {
      /* Calibration is completed */
      HAL_VTIMER_Context.calibration_in_progress = FALSE;
      /* Collect calibration data */
      TIMER_UpdateCalibrationData();
      TIMER_GetCurrentCalibrationData(&calibrationData);
#if HOST_WAKEUP_FIX_ENABLE
      if(waitCal){
        waitCal = 0;
        radioTimer.pending = TRUE;
        _check_radio_activity(&radioTimer,&expired);
        HAL_VTIMER_Context.rootNode = _update_user_timeout(HAL_VTIMER_Context.rootNode, &expired);
      }
#else
      _check_radio_activity(&radioTimer,&expired);
#endif
      HAL_VTIMER_StopTimer(&calibrationTimer);
      /* Schedule next calibration event */
      _start_timer(&calibrationTimer, TIMER_GetCurrentSysTime() + HAL_VTIMER_Context.PeriodicCalibrationInterval);
    }		
  }
  /* if there is a periodic calibration, start it in advance during the active phase */
  else{
    if(calibrationData.periodic_calibration){
      if( TIMER_GetCurrentSysTime() > (calibrationData.last_calibration_time + TIMER_SYSTICK_PER_FIVE_SECONDS))
      {
        calibration_callback(&calibrationTimer);
      }
    }
  }
}

/**
 * @brief  Returns the admitted sleep mode according to the next timer activity.
 * @return Sleep mode 
 */
PowerSaveLevels HAL_VTIMER_PowerSaveLevelCheck(PowerSaveLevels level)
{
  uint32_t nextRadioActivity;
  uint8_t timerState;

  if (HAL_VTIMER_SleepCheck() == FALSE)
  {
    return POWER_SAVE_LEVEL_RUNNING;
  }

  timerState = TIMER_GetRadioTimerValue(&nextRadioActivity);
  /*Timer1 and wakeup timer are programmed only through 
  the timer module*/
  if(((radioTimer.active || radioTimer.pending)  && !(timerState == TIMER1_BUSY)))
  {
    if(radioTimer.expiryTime < (TIMER_GetCurrentSysTime() + \
                                __TIMER_GetSysRfSetupTime() + \
                                HAL_VTIMER_Context.hs_startup_time + \
                                LOW_POWER_THR))
    {
      return POWER_SAVE_LEVEL_CPU_HALT;
    }
    
    level = POWER_SAVE_LEVEL_STOP_WITH_TIMER;
  }
  else
  {
    if ((timerState == TIMER2_BUSY) || (timerState == TIMER1_BUSY))
    {
      return POWER_SAVE_LEVEL_CPU_HALT;
    }
  }

  if(HAL_VTIMER_Context.rootNode != NULL && HAL_VTIMER_Context.rootNode->active)
  {
    if(HAL_VTIMER_Context.rootNode->expiryTime < (TIMER_GetCurrentSysTime() + LOW_POWER_THR + HAL_VTIMER_Context.hs_startup_time))
    {
      return POWER_SAVE_LEVEL_CPU_HALT;
    }
    
    if(level == POWER_SAVE_LEVEL_STOP_NOTIMER)
    {
      if((HAL_VTIMER_Context.rootNode->next == NULL) && (HAL_VTIMER_Context.rootNode == &calibrationTimer))
      {
        _virtualTimeBaseEnable(DISABLE);
        TIMER_DISABLE_CM0_TIMER;
        return POWER_SAVE_LEVEL_STOP_NOTIMER;
      }
    }
    level = POWER_SAVE_LEVEL_STOP_WITH_TIMER;
  }
  return level;
}

/**
 * @brief  Return the consensus of the Virtual timer management to go in sleep.
 * @retval TRUE if all vtimers have been served and the calibration procedure has already finished. 
 * @retval FALSE if the vtimer Tick is still busy.
 */
BOOL HAL_VTIMER_SleepCheck(void)
{
  return ((HAL_VTIMER_Context.expired_count == HAL_VTIMER_Context.served_count) && (HAL_VTIMER_Context.calibration_in_progress == FALSE));
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


  /******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
