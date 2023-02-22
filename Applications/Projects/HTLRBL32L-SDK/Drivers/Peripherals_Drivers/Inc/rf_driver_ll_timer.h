/**
******************************************************************************
* @file    rf_driver_ll_timer.h
* @author  RF Application Team
* @brief   This file contains all the functions prototypes for the TIMER 
*          firmware library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BLUENRGLP_TIMER_H
#define BLUENRGLP_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "bluenrg_lpx.h"
#include "rf_driver_ll_radio_2g4.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

/** @addtogroup TIMER
  * @{
  */ 

/** @defgroup TIMER_Exported_Types TIMER Exported Types
  * @{
  */ 

/** 
  * @brief Structure definition of TIMER initialization
  */ 
typedef struct
{
  uint16_t XTAL_StartupTime;      /*!< XTAL startup in 2.44 us unit */
  /**
 * Enable initial estimation of the frequency of the Low Speed Oscillator, otherwise it will be assumed fixed at 32.768 kHz.
 * Ignored if periodic calibration is active (TIMER_PeriodicCalibration = TRUE).
 */
  BOOL TIMER_InitialCalibration;
  BOOL TIMER_PeriodicCalibration; /*!< Assume that 32 KHz clock requires periodic calibration, i.e. varies with temperature */
} TIMER_InitType;

typedef struct timer_calibration_s {
  uint64_t last_calibration_time; /** Absolute system time when last calibration was performed */
  uint32_t period; /** Number of 16 MHz clock cycles in (2*(SLOW_COUNT+1) low speed oscillator periods */
  uint32_t freq; /** 2^39/period */
  uint8_t  periodic_calibration; /** Tells whether periodic hardware calibration is needed or not */
  uint32_t last_calibration_machine_time; /** Last machine time when calibration was performed */

} TIMER_CalibrationType;

/**
  * @}
  */ 

/** @defgroup TIMER_Exported_Constants TIMER Exported Constants
  * @{
  */

#define HOST_WAKEUP_FIX_ENABLE (1)
    
/** @defgroup TIMER_Ticks_Definition TIMER Ticks Definition
  * @{
  */
#define TIMER_SYSTICK_PER_FIVE_SECONDS (2048000)
#define TIMER_SYSTICK_PER_SECOND       (409600)
#define TIMER_SYSTICK_PER_10MS         (4096)
/**
  * @}
  */

#define TIMER1_BUSY         (0x01U)
#define TIMER2_BUSY         (0x02U)
#define WAKEUP_TIMER_BUSY   (0x03U)

/** This define represents the marging we take for long sleep to allow the system to
    avoid to have the counter wrapping. It is expressed in machine time, so it is variable
    when using internal RO */
#define TIMER_WRAPPING_MARGIN (4096)
/** This #define represents the number of significant bits in the timer */
#define TIMER_BITS (32)
#define TIMER_MAX_VALUE (0xFFFFFFFFU >> (32-TIMER_BITS))

/**
  * @}
  */ 

/** @defgroup TIMER_Exported_Macros TIMER Exported Macros
  * @{
  */ 

#define TIMER_GET_SLOW_FREQEUNCY            (RADIO_CTRL->CLK32FREQUENCY_REG & RADIO_CTRL_CLK32FREQUENCY_REG_SLOW_FREQUENCY)
#define TIMER_GET_SLOW_PERIOD               (RADIO_CTRL->CLK32PERIOD_REG & RADIO_CTRL_CLK32PERIOD_REG_SLOW_PERIOD)
#define TIMER_GET_SLOW_CLK_IRQ              (RADIO_CTRL->RADIO_CONTROL_IRQ_STATUS & RADIO_CTRL_RADIO_CONTROL_IRQ_STATUS_SLOW_CLK_IRQ)

#define TIMER_DISABLE_TIMER12               BLUE->TIMEOUTDESTREG = 0U;
#define TIMER_DISABLE_WAKEUP_TIMER          WAKEUP->BLUE_SLEEP_REQUEST_MODE &= ~(WAKEUP_BLUE_SLEEP_REQUEST_MODE_BLE_WAKEUP_EN)
#define TIMER_DISABLE_RADIO_TIMERS          {\
                                             BLUE->TIMEOUTDESTREG = 0U;\
                                             TIMER_DISABLE_WAKEUP_TIMER;\
                                            }
#define TIMER_DISABLE_CM0_TIMER             WAKEUP->CM0_SLEEP_REQUEST_MODE &= ~(WAKEUP_CM0_SLEEP_REQUEST_MODE_CPU_WAKEUP_EN)

#define TIMER_GET_TIMER1_STATUS             (BLUE->TIMEOUTDESTREG == BLUE_TIMEOUTDESTREG_DESTINATION_1)
#define TIMER_GET_TIMER2_STATUS             (BLUE->TIMEOUTDESTREG == (BLUE_TIMEOUTDESTREG_DESTINATION_1 | BLUE_TIMEOUTDESTREG_DESTINATION_0))
#define TIMER_GET_BLUE_WAKEUP_EN            WAKEUP->BLUE_SLEEP_REQUEST_MODE & WAKEUP_BLUE_SLEEP_REQUEST_MODE_BLE_WAKEUP_EN

#define TIMER_SET_TIMER1(time)              {\
                                             BLUE->TIMEOUTREG = time;\
                                             BLUE->TIMEOUTDESTREG = BLUE_TIMEOUTDESTREG_DESTINATION_1;\
                                            }

#define TIMER_ENABLE_BLUE_SLEEP_REQ         WAKEUP->BLUE_SLEEP_REQUEST_MODE |= (WAKEUP_BLUE_SLEEP_REQUEST_MODE_BLE_WAKEUP_EN | WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN)
#define TIMER_ENABLE_CM0_SLEEP_REQ          WAKEUP->CM0_SLEEP_REQUEST_MODE |= WAKEUP_CM0_SLEEP_REQUEST_MODE_CPU_WAKEUP_EN

#define TIMER_BLUE_SET_REQ_MODE(req_mode)   (MODIFY_REG(WAKEUP->BLUE_SLEEP_REQUEST_MODE,WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_REQ_MODE,req_mode))

/**
  * @}
  */ 

/**
 * @brief  Translate MTU to STU and vice-versa. It is implemented using integer operation.
 */
uint32_t blue_unit_conversion(uint32_t time, uint32_t period_freq, uint32_t thr);

/** @defgroup TIMER_Exported_Functions TIMER Exported Functions
  * @{
  */

/**
  * @brief  Initialize the TIMER functionality
  * @retval None
  */
void TIMER_Init(TIMER_InitType* TIMER_InitStruct);

/**
  * @brief  Perform a low speed clock calibration and store results in the global context.
  *         It updates the XTAL startup time and the interpolator configuration.
  *         It updates also the cumulative STU variable, so it should be called peiodically to manage timer wrapping,
  *         regardless of actual need of periodic calibration.
  *         This function is not re-entrant since it updates the context variable storing the system time.
  * @retval   None
*/
void TIMER_Calibrate(void);

/**
  * @brief  Start the calibration routine.
  * @retval None
  */
void TIMER_StartCalibration(void);

/**
  * @brief  Return TRUE if a calibration is on going. It relies on the value of the interrupt status.
  *         Assumption is that no other modules are managing the interrupt status of the calibrator.
* @retval   TRUE if calibration is running, FALSE otherwise.
*/
BOOL TIMER_IsCalibrationRunning(void);

/**
  * @brief  Records the result of the last calibration in the internal context.
 *          It updates the XTAL startup time.
  *         It updates also the cumulative STU variable, so it should be called peiodically to manage timer wrapping,
  *         regardless of actual need of periodic calibration.
  * @warning This function is not re-entrant since it updates the context variable storing the system time.
  *          It should be called only in user context and not in interrupt context.
* @retval   None
*/
void TIMER_UpdateCalibrationData(void);

/**
 * @brief   Set the wakeup time to the specified delay. The delay is converted in machine time and only 28 most significant bits
  *         are taken into account. The XTAL startup time is not taken into account for the wakeup, i.e. the system does not wait for
  *         the XTAL startup time parameter to trigger the interrupt.
  *         The delay is translated into machine time unit (MTU) and it is assigned to the wakeup register.
  * @param  delay: Delay from the current time expressed in system time unit (STU). Range is 0 to maximum value of STU. 
*         The maximum value STU is dependent on the speed of the low speed oscillator.
*         A value too small will force the timer to wrap, so it is reccommended to use at least 5-10 STU.
* @param  allow_sleep: Setting it to zero will prevent hardware to go to deep sleep,
*         if other code commands the system to go to deep sleep.
* @warning This function should be called with interrupts disabled to avoid programming the timer with a value in the past
 * @return  Current time in MTU.
*/
uint32_t TIMER_SetWakeupTime(uint32_t delay, BOOL allow_sleep);

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
uint32_t TIMER_SetRadioHostWakeupTime(uint32_t delay, BOOL* share);
#endif

/**
  * @brief  Return the current calibration data.
  * @retval None
  */
void TIMER_GetCurrentCalibrationData(TIMER_CalibrationType *data);

/**
* @brief  Return the MTU corresponding to the STU passed as parameter.
 * @param   time: STU amount to be converted in MTU
* @warning This function is not re-entrant since it updates the context variable storing the system time. It should be called only in
* user context and not in interrupt context.
 * @return  MTU value 
*/
uint32_t TIMER_SysTimeToMachineTime(int32_t time);

/**
* @brief  Return the STU corresponding to the MTU passed as parameter.
* @param  time: MTU amount to be converted in STU
* @warning This function is not re-entrant since it updates the context variable storing the system time. It should be called only in
* user context and not in interrupt context.
 * @return  STU value 
*/
uint32_t TIMER_MachineTimeToSysTime(uint32_t time);

/**
* @brief  Return the system time referred to the absolute machine time passed as parameter.
* @param  time: Absolute machine time in the future
* @warning User should guarantee that call to this function are performed in a non-interruptible context.
 * @return  STU value 
*/
uint64_t TIMER_GetFutureSysTime(uint32_t time);

/**
  * @brief   Return the current system time in system time unit (STU).
  *          This is a counter that grows since the power up of the system and it never wraps.
 * @return Current system time
*/
uint64_t TIMER_GetCurrentSysTime(void);

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
*         The maximum value STU is dependent on the speed of the low speed oscillator.
 * @param   event_type: 1 Tx event.
                        0 Rx event
 * @param   cal_req: 1 PLL calibartion is requested.
                     0 PLL calibartion is not requested.
* @warning This function should be called with interrupts disabled to avoid programming the timer with a value in the past
 * @retval  0 if a correct timeout has been programmed in the timeout register
 * @retval  1 if a correct timeout cannot be programmed
*/
uint8_t TIMER_SetRadioTimerValue(uint32_t timeout, BOOL event_type, BOOL cal_req);

/**
* @brief  Program the radio timer (a.k.a Timer1) as close as possible.
* The current time is sampled and increased by two.
* It means that the timer is going to trigger in a timer interval that goes
* from one to two machine time units. 
*/
void TIMER_SetRadioCloseTimeout(void);

/**
* @brief  Return timer capture register value in STU.
 * @return STU value 
*/
uint64_t TIMER_GetAnchorPoint(void);

/**
  * @brief  Disable Wakeup Timer and Timer1.
  * @retval None
  */
void TIMER_ClearRadioTimerValue(void);

/**
 * @brief  Return the status of the Radio timers and the last value programmed in the register.
 * @note   When Timer2 is on schedule, the time is expressed in microseconds, otherwise in absolute machine time units.
 * @param  time: pointer to value which is going to have time value.
 * @retval 0 if no timer has been programmed.
 * @retval 1 if Timer1 has been programmed.
 * @retval 2 if Timer2 has been programmed.
 * @retval 3 if Wakeup Timer has been programmed.
  */
uint8_t TIMER_GetRadioTimerValue(uint32_t *time);

/**
 * @brief  Disable Timer2.
  * @retval None
  */
void TIMER_ClearRadioTimer2(void);

/**
 * @brief   Return the system time referred to the absolute machine time passed as parameter.
 * @param   time: Absolute machine time in the past
 * @warning User should guarantee that call to this function are performed in a non-interruptible context.
 * @return  STU value 
*/
uint64_t TIMER_GetPastSysTime(uint32_t time);

/**
* @brief  Translate time in microseconds into sys time units.
 * @return STU value
*/
uint32_t TIMER_UsToSystime(uint32_t time);

/**
* @brief  Translate time in microseconds into machine time units.
 * @return STU value 
*/
uint32_t TIMER_UsToMachinetime(uint32_t time);

/**
 * @brief Enable CPU wakeup interrupt towards the CPU.
*/
void TIMER_Enable_CPU_WKUP(void);

/**
 * @brief Disable CPU wakeup interrupt towards the CPU.
*/
void TIMER_Disable_CPU_WKUP(void);

/**
 * @brief Returns the last setup time in absolute units needed to the hardware for the last 
 *        radio operation. Intended to be used only inside the timer module library.
 */
uint32_t __TIMER_GetSysRfSetupTime(void);

/**
 * @brief Get the current absolute time expressed in machine absolute time unit.
 */
__STATIC_INLINE uint32_t TIMER_GetCurrentMachineTime(void) { return WAKEUP->ABSOLUTE_TIME; }

/**
 * @brief Set the value of a host timeout in machine absolute time units.
 */
__STATIC_INLINE void TIMER_SetHostTimeoutReg(uint32_t value) { WAKEUP->CM0_WAKEUP_TIME = value; }

/**
 * @brief Get the value of a host timeout in machine absolute time units.
 */
__STATIC_INLINE uint32_t TIMER_GetHostTimeoutReg(uint32_t value) { return WAKEUP->CM0_WAKEUP_TIME; }

/**
 * @brief Set the value of a blue controller wakeup time in machine absolute time units.
 */
__STATIC_INLINE void TIMER_SetTimeoutReg(uint32_t value) { WAKEUP->BLUE_WAKEUP_TIME = value; }

/**
 * @brief Get the value of a blue controller wakeup time in machine absolute time units.
 */
__STATIC_INLINE uint32_t TIMER_GetTimeoutReg(uint32_t value) { return WAKEUP->BLUE_WAKEUP_TIME; }

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* BLUENRGLP_TIMER_H */

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
