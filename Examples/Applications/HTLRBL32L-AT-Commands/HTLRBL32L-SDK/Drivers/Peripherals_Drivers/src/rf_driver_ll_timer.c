/**
******************************************************************************
* @file    rf_driver_ll_timer.c
* @author  RF Application Team
* @brief   This file provides a set of functions to manage the radio and sleep timers.
* @details The basic support is provided by a low speed oscillator with a nominal speed of 32.768 kHz.
* The low speed oscillator provides a counter that increments at a nominal rate of 30.52 us.
* The counter is 32 bits wide and the low speed oscillator only increments bits 31:4 (most significant 28 bits)
* The remaining 4 bits are interpolated using the high speed 16 MHz clock. The counter unit are called conventionally
* machine time unit (MTU).
* At the end, the counter resolution will be about 1.91 us and it will wrap about every 2.30 hours.
* It is important to notice that the interpolated bits will only be functional when the system is out of sleep.
* While in sleep only the 28 most significant bits will tick.
* The user can setup a timer that will wakeup the system (if asleep) and it will trigger an interrupt when the timer expires.
* The user timer will not take into account the high speed XTAL wakeup time.
* The possible options for the low speed oscillator are:
* - external 32.768 kHz XTAL
* - internal ring oscillator (RO)
*
* The external 32 kHz XTAL meets the assumption made above regarding the nominal speed. The internal RO 
* is sensitive to temperature. Due to this reason, the concept of calibration or compensation is
* introduced. The calibration process involves measuring the nominal 32 kHz period using the high speed 16 MHz clock, once
* this operation is performed, the software will compensate all the timing using the most recent calibration value.
* The calibration is started by hardware at power-on and software in all the other cases.
* In order to cope with this variation a concept of system time unit (STU) is introduced.
* The STU is defined as scaled clock compared to MTU in order to:
* - handle variation of internal RO
* - express easily timing dictated by Bluetooth Low Energy protocol.
*
* The STU are absolute units of time and each unit represent 625/256 us, that is about 2.44 us.
* The MTU, on the other hand, have a nominal value of 1.91 us, and this value can be assumed constant when using
* external 32 kHz clock, but it will vary (mainly with temperature variation) when using internal RO.
* As a design choice, use of MTU is reserved as much as possible to the driver, while STU is exposed to user.
* This software layer provides also the possibility to program a radio timer linked to an already
* configured radio event. The radio timer is clocked by the low speed oscillator too.
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
#include "rf_driver_ll_timer.h"

/** @addtogroup RF_DRIVER_LL_Driver
* @{
*/

/** @defgroup TIMER TIMER
  * @brief TIMER module driver
  * @{
  */

/** @defgroup TIMER_Private_Types TIMER Private Types 
* @{
*/
typedef struct timer_context_s {
  uint64_t cumulative_time; /** Absolute system time since power up */
  uint64_t last_calibration_time; /** Absolute system time when last calibration was performed */
  uint32_t hs_startup_time; /** XTAL startup time in STU */
  uint16_t wakeup_time_offset;
  uint32_t period; /** Number of 16 MHz clock cycles in (2*(SLOW_COUNT+1)) low speed oscillator periods */
  uint32_t freq; /** 2^39/period */
  int32_t freq1;                    /** Round(((freq/64)*0x753)/256) */
  int32_t period1;                  /** Round (( ((period /256) * 0x8BCF6) + (((period % 256)* 0x8BCF6)/256)) / 32) */
  int32_t last_period1;             /** Period global in last calibration */
  uint32_t last_machine_time; /** Last machine time used to update cumulative time */
  uint32_t last_calibration_machine_time; /** Last machine time when calibration was performed */
  uint8_t  periodic_calibration; /** Tells whether periodic hardware calibration is needed or not, i.e. lsosc speed varies with temperature, etc. */
  uint8_t tx_cal_delay; /**time in MTU to be compensated if transmission and pll calibration are requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t tx_no_cal_delay; /**time in MTU to be compensated if transmission is requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t rx_cal_delay; /**time in MTU to be compensated if reception and pll calibration are requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t rx_no_cal_delay; /**time in MTU to be compensated if reception is requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t tx_cal_delay_st; /**time in STU to be compensated if transmission and pll calibration are requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t tx_no_cal_delay_st; /**time in STU to be compensated if transmission is requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t rx_cal_delay_st; /**time in STU to be compensated if reception and pll calibration are requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t rx_no_cal_delay_st; /**time in STU to be compensated if reception is requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t tim12_delay_mt;
  uint8_t last_setup_time; /**setup time of last timer programmed*/
} TIMER_ContextType; 

/**
* @}
*/

/** @defgroup TIMER_Private_Macros TIMER Private Macros
* @{
*/

#define TIME_DIFF(a, b)       (((int32_t)((a - b) << (32-TIMER_BITS))) >> (32-TIMER_BITS))
/* This define assumes that a is always greater than b */
#define TIME_ABSDIFF(a, b)       ((a - b) & TIMER_MAX_VALUE)
/* #define IRQ_SAFE */
#define MIN(a,b) ((a) < (b) )? (a) : (b)
#define MAX(a,b) ((a) < (b) )? (b) : (a)

#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
                                __disable_irq(); \
/* Must be called in the same scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

/**
* @}
*/

/** @defgroup TIMER_Private_Constants TIMER Private Constants
* @{
*/                        
#define MULT64_THR_FREQ (806)
#define MULT64_THR_PERIOD (1589)

/*Radio event types*/
#define RX (0)
#define TX (1)

#define MARGIN_EXT (200)
                                  
#define WAKEUP_INIT_DELAY (27) /* about 65us in STU */

/**
* @}
*/

/** @defgroup TIMER_Private_Variables TIMER Private Variables
* @{
*/
static TIMER_ContextType TIMER_Context;

/**
* @}
*/

/** @defgroup TIMER_Private_Functions TIMER Private Functions
* @{
*/
static void _timer_start_calibration(void)
{
  /* Clear any pending interrupt */
  RADIO_CTRL->RADIO_CONTROL_IRQ_STATUS |= 1;
  RADIO_CTRL->CLK32PERIOD_REG = 0;
}

static void _get_calibration_data(TIMER_ContextType *context)
{
  int32_t period,freq;
  period = TIMER_GET_SLOW_PERIOD; 
  
  while(period != TIMER_GET_SLOW_PERIOD || period == 0)
  {
    period = TIMER_GET_SLOW_PERIOD; 
  }

  int32_t mul1 = 0x8BCF6 ;
  int32_t b1 = period >> 8 ;
  int32_t b2 = period & 0xff ;
  context->period1 = ((mul1 * b1) + ((b2 * mul1)>>8) + 16 )>>5 ;     
  context->period = period;
  
  int32_t mult = 0x753 ;
  freq = TIMER_GET_SLOW_FREQEUNCY;
  
  while(freq != TIMER_GET_SLOW_FREQEUNCY || freq == 0)
  {
    freq = TIMER_GET_SLOW_FREQEUNCY;
  }
  int32_t a1 = freq >> 6 ;
  int32_t a2 = a1 * mult ;
  context->freq1 = (a2 + 128) >> 8 ; 
  context->freq = freq;
}

static void _timer_calibrate(TIMER_ContextType *context)
{
  _timer_start_calibration();
  while(TIMER_GET_SLOW_CLK_IRQ == 0);
  _get_calibration_data(context);
}

static uint32_t us_to_systime(uint32_t time)
{
  uint32_t t1, t2;
  t1 = time * 0x68;
  t2 = time * 0xDB;
  return (t1 >> 8) + (t2 >> 16);
}

/**
 * @brief  Translate us to MTU
 * @param  time: Time expressed in us to be translated in MTU
 * @retval Machine Time Units
 */
static uint32_t us_to_machinetime(uint32_t time)
{
  return blue_unit_conversion(us_to_systime(time),TIMER_Context.freq1, MULT64_THR_FREQ);
}

static uint64_t get_system_time_and_machine(TIMER_ContextType *context, uint32_t *current_machine_time)
{
  uint32_t difftime;
  uint64_t new_time = context->cumulative_time;
  *current_machine_time = WAKEUP->ABSOLUTE_TIME;
  difftime = TIME_ABSDIFF(*current_machine_time, context->last_machine_time);
  new_time += blue_unit_conversion(difftime,context->period1, MULT64_THR_PERIOD);
  return new_time;
}

/* This function is used to get current system time */
static uint64_t get_system_time(TIMER_ContextType *context)
{
  uint32_t current_machine_time;
  return get_system_time_and_machine(context, &current_machine_time);
}

static void update_cal_delay(TIMER_ContextType *context)
{
  uint8_t tx_delay_start = (blueglob->TXDELAYSTART*125/1000)+1;/*TBR*/
  blueglob->WAKEUPINITDELAY =  blue_unit_conversion(WAKEUP_INIT_DELAY, context->freq1, MULT64_THR_FREQ);
  context->tim12_delay_mt = us_to_machinetime(blueglob->TIMER12INITDELAYCAL);
  context->tx_cal_delay = us_to_machinetime(blueglob->TRANSMITCALDELAYCHK + tx_delay_start);
  context->tx_no_cal_delay = us_to_machinetime(blueglob->TRANSMITNOCALDELAYCHK + tx_delay_start);
  context->rx_cal_delay = us_to_machinetime(blueglob->RECEIVECALDELAYCHK);
  context->rx_no_cal_delay = us_to_machinetime(blueglob->RECEIVENOCALDELAYCHK);
}

/* This function update the system time after a calibration.
 * If the user calls too often this function, you could have rounding issues in the integer maths.
 */
static void update_system_time(TIMER_ContextType *context)
{
  uint32_t current_machine_time;
  current_machine_time = WAKEUP->ABSOLUTE_TIME;
  uint32_t period = context->last_period1;
  context->cumulative_time = context->last_calibration_time + \
  blue_unit_conversion(TIME_ABSDIFF(current_machine_time,
                                      context->last_calibration_machine_time),
                                      period, MULT64_THR_PERIOD);
  context->last_machine_time = current_machine_time;
  context->last_calibration_machine_time = current_machine_time;
  context->last_calibration_time = context->cumulative_time;
  context->last_period1 = context->period1;
}

static void _update_xtal_startup_time(uint16_t hs_startup_time, int32_t freq1)
{
  int32_t time1 = blue_unit_conversion(hs_startup_time, freq1, MULT64_THR_FREQ);
  if(time1 >= 4096)
    time1 = 4095;
  if(time1 < 16)
    time1 = 16;
  /*Mode0 is connected/used by the HW*/
  TIMER_Context.wakeup_time_offset = (time1 >> 4);
  WAKEUP->WAKEUP_OFFSET[0] = TIMER_Context.wakeup_time_offset;
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

/** @defgroup TIMER_Exported_Functions TIMER Exported Functions
* @{
*/

/**
 * @brief  Initialize the TIMER functionality
 * @retval None
 */
void TIMER_Init(TIMER_InitType* TIMER_InitStruct)
{
  TIMER_Context.hs_startup_time = TIMER_InitStruct->XTAL_StartupTime;
  uint8_t tx_delay_start = (blueglob->TXDELAYSTART*125/1000)+1;
  
  if (TIMER_InitStruct->TIMER_PeriodicCalibration || TIMER_InitStruct->TIMER_InitialCalibration) {
    /* Make sure any pending calibration is over */
    while((TIMER_GET_SLOW_CLK_IRQ) == 0);
    /* Set SLOW_COUNT to 23, that is calibrate over 24 clock periods, this number
    cannot be changed without changing all the integer maths function in the
    file	*/
    RADIO_CTRL->CLK32COUNT_REG |= 23;
    _timer_calibrate(&TIMER_Context);
    /* For first time set last to current */
    TIMER_Context.last_period1 = TIMER_Context.period1;
  }
  else {
    /* Assume fix frequency at 32.768 kHz */
    TIMER_Context.last_period1 = 0x00190000;
    TIMER_Context.period1 = 0x00190000 ;
    TIMER_Context.freq1 = 0x0028F5C2 ;
    TIMER_Context.period = 23437;
    TIMER_Context.freq = 23456748;
  }
  TIMER_Context.periodic_calibration = TIMER_InitStruct->TIMER_PeriodicCalibration;
  _update_xtal_startup_time(TIMER_Context.hs_startup_time, TIMER_Context.freq1);
  TIMER_Context.last_setup_time = 0;
  TIMER_Context.cumulative_time = 0;
  TIMER_Context.last_machine_time = WAKEUP->ABSOLUTE_TIME;
  TIMER_Context.last_calibration_machine_time = TIMER_Context.last_machine_time;
  TIMER_Context.last_calibration_time = 0;
  update_cal_delay(&TIMER_Context);
  TIMER_Context.tx_cal_delay_st = us_to_systime(blueglob->TRANSMITCALDELAYCHK + tx_delay_start) + \
                                    WAKEUP_INIT_DELAY;
  TIMER_Context.tx_no_cal_delay_st = us_to_systime(blueglob->TRANSMITNOCALDELAYCHK + tx_delay_start) + \
                                     WAKEUP_INIT_DELAY;
  TIMER_Context.rx_cal_delay_st = us_to_systime(blueglob->RECEIVECALDELAYCHK) + \
                                     WAKEUP_INIT_DELAY;
  TIMER_Context.rx_no_cal_delay_st = us_to_systime(blueglob->RECEIVENOCALDELAYCHK) + \
                                     WAKEUP_INIT_DELAY;
}

/**
 * @brief  Perform a low speed clock calibration and store results in the global context.
 *         It updates the XTAL startup time and the interpolator configuration.
 *         It updates also the cumulative STU variable, so it should be called peiodically to manage timer wrapping,
 *         regardless of actual need of periodic calibration.
 *         This function is not re-entrant since it updates the context variable storing the system time.
 * @retval None
 */
void TIMER_Calibrate(void)
{
  if (TIMER_Context.periodic_calibration) {
    TIMER_ContextType ContextToUpdate = TIMER_Context;
    _timer_calibrate(&ContextToUpdate);
    _update_xtal_startup_time(ContextToUpdate.hs_startup_time, ContextToUpdate.freq1);
    update_cal_delay(&ContextToUpdate);
    ATOMIC_SECTION_BEGIN();
    /* Copying only the updated fields.
    Faster than memcpy: TIMER_Context = ContextToUpdate;*/
    TIMER_Context.period = ContextToUpdate.period;
    TIMER_Context.freq = ContextToUpdate.freq;
    TIMER_Context.freq1 = ContextToUpdate.freq1;
    TIMER_Context.period1 = ContextToUpdate.period1;
    TIMER_Context.last_period1 = ContextToUpdate.last_period1;
    TIMER_Context.tx_cal_delay = ContextToUpdate.tx_cal_delay;
    TIMER_Context.tx_no_cal_delay = ContextToUpdate.tx_no_cal_delay;
    TIMER_Context.rx_cal_delay = ContextToUpdate.rx_cal_delay;
    TIMER_Context.rx_no_cal_delay = ContextToUpdate.rx_no_cal_delay;
    TIMER_Context.tim12_delay_mt = ContextToUpdate.tim12_delay_mt;
    update_system_time(&TIMER_Context);
    ATOMIC_SECTION_END();
  }
  else
  {
    ATOMIC_SECTION_BEGIN();
    update_system_time(&TIMER_Context);
    ATOMIC_SECTION_END();
  }
}

/**
 * @brief  Start the calibration routine.
 * @retval None
 */
void TIMER_StartCalibration(void)
{
  if (TIMER_Context.periodic_calibration) {
    _timer_start_calibration();
  }
}

/**
 * @brief  Return TRUE if a calibration is on going. It relies on the value of the interrupt status.
 *         Assumption is that no other modules are managing the interrupt status of the calibrator.
 * @retval TRUE if calibration is running, FALSE otherwise.
 */
BOOL TIMER_IsCalibrationRunning(void)
{
  /* Normally the calibration is triggered automatically by hardware only at power up (or hardware reset),
  all other calibrations are started by software */
  return ((TIMER_GET_SLOW_CLK_IRQ) == 0);
}

/**
 * @brief   Records the result of the last calibration in the internal context.
 *          It updates the XTAL startup time.
 *          It updates also the cumulative STU variable, so it should be called peiodically to manage timer wrapping,
 *          regardless of actual need of periodic calibration.
 * @warning This function is not re-entrant since it updates the context variable storing the system time.
 *          It should be called only in user context and not in interrupt context.
 * @retval  None
 */
void TIMER_UpdateCalibrationData(void)
{
  if (TIMER_Context.periodic_calibration) {
    TIMER_ContextType ContextToUpdate = TIMER_Context;
    _get_calibration_data(&ContextToUpdate);
    _update_xtal_startup_time(ContextToUpdate.hs_startup_time, ContextToUpdate.freq1);
    update_cal_delay(&ContextToUpdate);
    ATOMIC_SECTION_BEGIN();
    /* Copying only the updated fields.
    Faster than memcpy: TIMER_Context = ContextToUpdate;*/
    TIMER_Context.period = ContextToUpdate.period;
    TIMER_Context.freq = ContextToUpdate.freq;
    TIMER_Context.freq1 = ContextToUpdate.freq1;
    TIMER_Context.period1 = ContextToUpdate.period1;
    TIMER_Context.last_period1 = ContextToUpdate.last_period1;
    TIMER_Context.tx_cal_delay = ContextToUpdate.tx_cal_delay;
    TIMER_Context.tx_no_cal_delay = ContextToUpdate.tx_no_cal_delay;
    TIMER_Context.rx_cal_delay = ContextToUpdate.rx_cal_delay;
    TIMER_Context.rx_no_cal_delay = ContextToUpdate.rx_no_cal_delay;
    TIMER_Context.tim12_delay_mt = ContextToUpdate.tim12_delay_mt;
    update_system_time(&TIMER_Context);
    ATOMIC_SECTION_END();
  }
  else
  {
    ATOMIC_SECTION_BEGIN();
    update_system_time(&TIMER_Context);
    ATOMIC_SECTION_END();
  }
}

/**
 * @brief  Return the current system time in system time unit (STU).
 *         This is a counter that grows since the power up of the system and it never wraps.
 * @return Current system time
 */
uint64_t TIMER_GetCurrentSysTime(void)
{
  return get_system_time(&TIMER_Context);
}

/**
 * @brief   Return the system time referred to the absolute machine time passed as parameter.
 * @param   time: Absolute machine time in the future
 * @warning User should guarantee that call to this function are performed in a non-interruptible context.
 * @return  STU value 
 */
uint64_t TIMER_GetFutureSysTime(uint32_t time)
{
  uint32_t delta_systime = blue_unit_conversion(TIME_DIFF(time, TIMER_Context.last_machine_time), TIMER_Context.period1, MULT64_THR_PERIOD);
  return TIMER_Context.cumulative_time+delta_systime;
}

/**
 * @brief   Return the system time referred to the absolute machine time passed as parameter.
 * @param   time: Absolute machine time in the past
 * @warning User should guarantee that call to this function are performed in a non-interruptible context.
 * @return  STU value 
 */
uint64_t TIMER_GetPastSysTime(uint32_t time)
{
  uint32_t delta_systime, current_machine_time;
  uint64_t current_system_time = get_system_time_and_machine(&TIMER_Context, &current_machine_time);
  delta_systime = blue_unit_conversion(TIME_DIFF(current_machine_time, time), TIMER_Context.period1, MULT64_THR_PERIOD);
  return current_system_time-delta_systime;
}

/**
 * @brief  Return the current calibration data.
 * @retval None
 */
void TIMER_GetCurrentCalibrationData(TIMER_CalibrationType *data)
{
  data->periodic_calibration = TIMER_Context.periodic_calibration;
  data->freq = TIMER_Context.freq;
  data->last_calibration_time = TIMER_Context.last_calibration_time;
  data->period = TIMER_Context.period;
  data->last_calibration_machine_time = TIMER_Context.last_calibration_machine_time; /* Last machine time when calibration was performed */
}

/**
 * @brief  Disable Timer2.
 * @retval None
 */
void TIMER_ClearRadioTimer2(void)
{
  /*It is not possible to disable timer2
  without disabling timer1.*/
  TIMER_DISABLE_TIMER12;
}

/**
 * @brief  Disable Wakeup Timer and Timer1.
 * @retval None
 */
void TIMER_ClearRadioTimerValue(void)
{
  /*It is not possible to disable timer1
  without disabling timer2.*/
  TIMER_DISABLE_RADIO_TIMERS;
}

/**
 * @brief  Return the status of the Radio timers and the last value programmed in the register.
 * @note   When Timer2 is on schedule, the time is expressed in microseconds, otherwise in absolute machine time units.
 * @param  time: pointer to value which is going to have time value.
 * @retval 0 if no timer has been programmed.
 * @retval 1 if Timer1 has been programmed.
 * @retval 2 if Timer2 has been programmed.
 * @retval 3 if Wakeup Timer has been programmed.
 */
uint8_t TIMER_GetRadioTimerValue(uint32_t *time)
{
  if(TIMER_GET_BLUE_WAKEUP_EN)
  {
    *time = WAKEUP->BLUE_WAKEUP_TIME;
    return WAKEUP_TIMER_BUSY;
  }
  else if(TIMER_GET_TIMER1_STATUS) 
  {
    *time = BLUE->TIMEOUTREG;
    return TIMER1_BUSY;
  }
  else if(TIMER_GET_TIMER2_STATUS)
  {
    *time = BLUE->TIMEOUTREG;
    return TIMER2_BUSY;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief Returns the last setup time in absolute units needed to the hardware for the last 
 *        radio operation. Intended to be used only inside the timer module library.
 */
uint32_t __TIMER_GetSysRfSetupTime(void)
{
  return TIMER_Context.last_setup_time;
}

/**
 * @brief   Set the wakeup time to the specified delay. The delay is converted in machine time and only 28 most significant bits
 *          are taken into account. The XTAL startup time is not taken into account for the wakeup, i.e. the system does not wait for
 *          the XTAL startup time parameter to trigger the interrupt.
 *          The delay is translated into machine time unit (MTU) and it is assigned to the wakeup register.
 * @param   delay: Delay from the current time expressed in system time unit (STU). Range is 0 to maximum value of STU. 
 *          The maximum value STU is dependent on the speed of the low speed oscillator.
 *          A value too small will force the timer to wrap, so it is reccommended to use at least 5-10 STU.
 * @param   allow_sleep: Setting it to zero will prevent hardware to go to deep sleep,
 *          if other code commands the system to go to deep sleep.
 * @warning This function should be called with interrupts disabled to avoid programming the timer with a value in the past
 * @return  Current time in MTU.
 */
uint32_t TIMER_SetWakeupTime(uint32_t delay, BOOL allow_sleep)
{
  uint32_t current_time;
  delay = blue_unit_conversion(delay, TIMER_Context.freq1, MULT64_THR_FREQ) ;
  /* If the delay is too small round to minimum 2 tick */
  delay = MAX(32,delay); 
  current_time = WAKEUP->ABSOLUTE_TIME;
  /* 4 least significant bits are not taken into account. Then let's round the value */
  WAKEUP->CM0_WAKEUP_TIME = ((current_time + (delay + 8)) & TIMER_MAX_VALUE);
  WAKEUP->BLUE_SLEEP_REQUEST_MODE |= WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN;
  TIMER_ENABLE_CM0_SLEEP_REQ;
  return current_time;
}

#if HOST_WAKEUP_FIX_ENABLE
/**
 * @brief   Set the wakeup time to the specified delay. The delay is converted in machine time and only 28 most significant bits
 *          are taken into account. The XTAL startup time is not taken into account for the wakeup, i.e. the system does not wait for
 *          the XTAL startup time parameter to trigger the interrupt. If is it possible the wakeup timer is programmed too.
 *          The delay is translated into machine time unit (MTU) and it is assigned to the wakeup register.
 * @param   delay: Delay from the current time expressed in system time unit (STU). Range is 0 to maximum value of STU. 
 *          The maximum value STU is dependent on the speed of the low speed oscillator.
 *          A value too small will force the timer to wrap, so it is reccommended to use at least 5-10 STU.
 * @param   share: flag that indicates if the wakeup timer has to be programmed too. 
 *          if other code commands the system to go to deep sleep.
 * @warning This function should be called with interrupts disabled to avoid programming the timer with a value in the past.
 * @warning To be considered only if HOST_WAKEUP_FIX_ENABLE is 1.
 * @return  Current time in MTU.
 */
uint32_t TIMER_SetRadioHostWakeupTime(uint32_t delay, BOOL* share)
{
  uint32_t current_time;

  delay = blue_unit_conversion(delay, TIMER_Context.freq1, MULT64_THR_FREQ) ;
  /* If the delay is too small round to minimum 2 tick */
  delay = MAX(32,delay); 
  current_time = WAKEUP->ABSOLUTE_TIME;
  /* 4 least significant bits are not taken into account. Then let's round the value */
  WAKEUP->CM0_WAKEUP_TIME = ((current_time + (delay + 8)) & TIMER_MAX_VALUE);
  WAKEUP->BLUE_SLEEP_REQUEST_MODE |= WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN;
  TIMER_ENABLE_CM0_SLEEP_REQ;
  if ((TIMER_GET_TIMER1_STATUS || TIMER_GET_TIMER2_STATUS || (*share != TRUE)))
  {
    *share = FALSE;
    return current_time;
  }
  _set_controller_as_host();
  /* 4 least significant bits are not taken into account. Then let's round the value */
  WAKEUP->BLUE_WAKEUP_TIME = ((current_time + delay + 8) & 0xFFFFFFF0);
  TIMER_BLUE_SET_REQ_MODE(0);
  TIMER_ENABLE_BLUE_SLEEP_REQ;
  return current_time;
}
#endif

/**
 * @brief   Programs either the Wakeup timer or Timer1. Both timers are able to trigger the radio sequencer.
 *          Then, they are able to start a transmission or a reception according to the configured radio ram tables.
 *          Only the wakeup timer is able to let the device out from sleep.
 *          The wakeup timer is programmed if the anolag part has enough time to settle after the wakeup or not.
 *          The timeout passed as parameter represents the moment where the first bit must be transmitted or the 
 *          receive window must be opened.
 *          Since the radio needs some time to setup, the final timeout programmed is compensated by certain 
 *          time intervals according to the kind of operation (Tx or Rx), calibration request and programmed timer.
 *          The wakeup offset is compensated automatically by the hardware.
 *          The CPU wakes up at timeout minus wakeup_offset. if the wakeup timer is programmed, the BLE event triggers
 *          when the absolute time mathches the 28 MSB of the timeout. Otherwise the trigger event occurs considering all 32 bits.
 * @param   timeout: absolute starting time of the desired operation expressed in STU. 
 *                   If this absolute time is less then the current time, the timer will wrap.
 *                   The maximum value STU is dependent on the speed of the low speed oscillator.
 * @param   event_type: 1 Tx event.
                        0 Rx event
 * @param   cal_req: 1 pll calibartion is requested.
                    0 pll calibartion is not requested.
 * @warning This function should be called with interrupts disabled to avoid programming the timer with a value in the past
 * @retval  0 if a correct timeout has been programmed in the timeout register
 * @retval  1 if a correct timeout cannot be programmed
 */
uint8_t TIMER_SetRadioTimerValue(uint32_t timeout, BOOL event_type, BOOL cal_req)
{
  uint32_t current_time, delay, radio_init_delay, device_delay, relTimeout;
  /*choose the 2nd init duration. Check the event_type and cal. request*/
  if(event_type == TX)
  {
    if(cal_req)
    {
      radio_init_delay = TIMER_Context.tx_cal_delay;
      device_delay = TIMER_Context.tx_cal_delay_st;
    }
    else
    {
      radio_init_delay = TIMER_Context.tx_no_cal_delay; 
      device_delay = TIMER_Context.tx_cal_delay_st;
    }
  }
  else
  {
    if(cal_req)
    {
      radio_init_delay = TIMER_Context.rx_cal_delay;
      device_delay = TIMER_Context.tx_cal_delay_st;
    }
    else
    {
      radio_init_delay = TIMER_Context.rx_no_cal_delay; 
      device_delay = TIMER_Context.tx_cal_delay_st;
    }
  } 
  
  /* At this point, it is care of the upper layers to guarantee that the timeout represents an absolute time in the future */
  relTimeout = timeout - (uint32_t)get_system_time_and_machine(&TIMER_Context,&current_time);
  /*Check if the timeout is beyond the wakeup time offset. Then program either the WakeUp timer or the Timer1*/
  if (relTimeout > device_delay + TIMER_Context.hs_startup_time + MARGIN_EXT)
  {
    /*The timeout is after the wakeup_time_offset, So it is ok to program the wakeup timer*/
    delay = blue_unit_conversion(relTimeout, TIMER_Context.freq1, MULT64_THR_FREQ) \
                                                             - blueglob->WAKEUPINITDELAY \
                                                             - radio_init_delay;
    WAKEUP->BLUE_WAKEUP_TIME = ((current_time + delay) & TIMER_MAX_VALUE);
    TIMER_BLUE_SET_REQ_MODE(0);
    TIMER_DISABLE_TIMER12;
    TIMER_ENABLE_BLUE_SLEEP_REQ;
    radio_init_delay += blueglob->WAKEUPINITDELAY;
  }
  else
  {
    delay = blue_unit_conversion(relTimeout , TIMER_Context.freq1, MULT64_THR_FREQ) \
                                                            - TIMER_Context.tim12_delay_mt \
                                                            - radio_init_delay;
    TIMER_SET_TIMER1((current_time + delay) & TIMER_MAX_VALUE);
    TIMER_DISABLE_WAKEUP_TIMER;
    radio_init_delay += TIMER_Context.tim12_delay_mt;
  }
  
#if HOST_WAKEUP_FIX_ENABLE
  blueglob->BYTE4 |= 1<<7;
  blueglob->BYTE22 = 0xF0;
  blueglob->BYTE23 = 0xFF;
#endif
  
  /*Basic low level check with an extra margin of machine units */
  if ((delay + radio_init_delay) < (radio_init_delay + 5))
  {
    TIMER_DISABLE_RADIO_TIMERS;
    return 1;
  }
  TIMER_Context.last_setup_time = blue_unit_conversion(radio_init_delay, TIMER_Context.period1, MULT64_THR_PERIOD);
  return 0;
}

/**
 * @brief Program the radio timer (a.k.a Timer1) as close as possible.
 *        The current time is sampled and increased by two.
 *        It means that the timer is going to trigger in a timer interval that goes
 *        from one to two machine time units. 
 */
void TIMER_SetRadioCloseTimeout(void)
{
  ATOMIC_SECTION_BEGIN();
  uint32_t current_time = WAKEUP->ABSOLUTE_TIME;
  TIMER_SET_TIMER1((current_time + 2) & TIMER_MAX_VALUE);
  ATOMIC_SECTION_END();
}

/**
 * @brief Enable CPU wakeup interrupt towards the CPU.
 */
void TIMER_Enable_CPU_WKUP(void)
{
  WAKEUP->WAKEUP_CM0_IRQ_STATUS |= 1;
  WAKEUP->WAKEUP_CM0_IRQ_ENABLE |= 1;
  NVIC_EnableIRQ(CPU_WKUP_IRQn);
}

/**
 * @brief Disable CPU wakeup interrupt towards the CPU.
 */
void TIMER_Disable_CPU_WKUP(void)
{
  NVIC_DisableIRQ(CPU_WKUP_IRQn);
  WAKEUP->WAKEUP_CM0_IRQ_STATUS |= 1;
  WAKEUP->WAKEUP_CM0_IRQ_ENABLE = 0;
}

/**
 * @brief  Return timer capture register value in STU.
 * @return STU value 
 */
uint64_t TIMER_GetAnchorPoint(void)
{
  return TIMER_GetPastSysTime(BLUE->TIMERCAPTUREREG);
}

/**
 * @brief   Return the MTU corresponding to the STU passed as parameter.
 * @param   time: STU amount to be converted in MTU
 * @warning This function is not re-entrant since it updates the context variable storing the system time. It should be called only in
 *          user context and not in interrupt context.
 * @return  MTU value 
 */
uint32_t TIMER_SysTimeToMachineTime(int32_t time)
{
  return blue_unit_conversion(time, TIMER_Context.freq1, MULT64_THR_FREQ);
}

/**
 * @brief   Return the STU corresponding to the MTU passed as parameter.
 * @param   time: MTU amount to be converted in STU
 * @warning This function is not re-entrant since it updates the context variable storing the system time. It should be called only in
 *          user context and not in interrupt context.
 * @return  STU value 
 */
uint32_t TIMER_MachineTimeToSysTime(uint32_t time)
{
   return blue_unit_conversion(time, TIMER_Context.period1, MULT64_THR_PERIOD);
}

/**
 * @brief  Translate time in microseconds into sys time units.
 * @return STU value
 */
uint32_t TIMER_UsToSystime(uint32_t time)
{
  return us_to_systime(time);
}

/**
 * @brief  Translate time in microseconds into machine time units.
 * @return STU value 
 */
uint32_t TIMER_UsToMachinetime(uint32_t time)
{
  return us_to_machinetime(time);
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
