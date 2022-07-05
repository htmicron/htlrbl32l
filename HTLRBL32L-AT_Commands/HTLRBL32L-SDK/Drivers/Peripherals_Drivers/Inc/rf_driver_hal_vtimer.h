/**
******************************************************************************
* @file    rf_driver_hal_vtimer.h 
* @author  RF Application Team
* @brief   Virtual timer and Radio timer high level APIs
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
#ifndef RF_DRIVER_HAL_VTIMER_H
#define RF_DRIVER_HAL_VTIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "rf_driver_ll_timer.h"
#include "rf_driver_hal_power_manager.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */ 

/** @addtogroup VTIMER
  * @{
  */

/** @defgroup VTIMER_Exported_Types VTIMER Exported Types
  * @{
  */ 

typedef enum {
  RADIO_TIMER_OFF = 0,
  RADIO_TIMER_PENDING = 1,
} TimerStatus; 

typedef void (*VTIMER_CallbackType)(void *);
typedef struct VTIMER_HandleTypeS {
	uint64_t expiryTime; /*!< Managed internally when the timer is started */
	VTIMER_CallbackType callback; /*!< Pointer to the user callback */
	BOOL active; /*!< Managed internally when the timer is started */
	struct VTIMER_HandleTypeS *next; /*!< Managed internally when the timer is started */
	void *userData; /*!< Pointer to user data */
} VTIMER_HandleType;

typedef struct HAL_VTIMER_InitS {
  uint16_t XTAL_StartupTime;             /*!< XTAL startup in 2.44 us unit */
 /**
 * Enable initial estimation of the frequency of the Low Speed Oscillator, otherwise it will be assumed fixed at 32.768 kHz.
 * Ignored if periodic calibration is active (PeriodicCalibrationInterval != 0).
 */
  BOOL EnableInitialCalibration;                
  uint32_t PeriodicCalibrationInterval;  /*!< Periodic calibration interval in ms, to disable set to 0 */
} HAL_VTIMER_InitType;

/**
  * @}
  */ 

/** @defgroup VTIMER_Exported_Constants VTIMER Exported Constants
* @{
*/

/**
 * @brief Margin to add to the calibration interval in order to guarantee
 *        enough time to program the radio timer after the calibration.
 *        It is expressed in STU.
  */
#define RADIO_ACTIVITY_MARGIN (204800)

#define HAL_VTIMER_PLL_CALIB_REQ            (0x01U)
#define HAL_VTIMER_PLL_CALIB_NOT_REQ        (0x00U)
#define HAL_VTIMER_TX_EVENT                 (0x01U)
#define HAL_VTIMER_RX_EVENT                 (0x00U)

/*Radio timer clearing process return values*/
#define HAL_VTIMER_SUCCESS  (0x00U)
#define HAL_VTIMER_LATE     (0x01U)
#define HAL_VTIMER_CRITICAL (0x02U)

/**
* @}
*/ 

/** @defgroup VTIMER_Exported_Functions VTIMER Exported Functions
  * @{
  */

/**
 * @brief Starts a one-shot virtual timer for the given relative timeout value expressed in ms
 * @param  timerHandle: The virtual timer
 * @param msRelTimeout: The relative time, from current time, expressed in ms
 * @retval 0 if the timerHandle is valid.
 * @retval 1 if the timerHandle is not valid. It is already started.
 */
int HAL_VTIMER_StartTimerMs(VTIMER_HandleType *timerHandle, uint32_t msRelTimeout);

/**
 * @brief Stops the one-shot virtual timer specified if found
 * @param  timerHandle: The virtual timer
 * @retval None
 */
void HAL_VTIMER_StopTimer(VTIMER_HandleType *timerHandle);

/**
 * @brief  This function returns the current reference time expressed in system time units.
 *         The returned value can be used as absolute time parameter where needed in the other
 *         HAL_VTIMER* APIs
 * @return absolute current time expressed in system time units.
 */
uint64_t HAL_VTIMER_GetCurrentSysTime(void);

/**
 * @brief This function returns the sum of an absolute time and a signed relative time.
 * @param  sysTime: Absolute time expressed in internal time units.
 * @param  msTime: Signed relative time expressed in ms.
 * @return 64bit resulting absolute time expressed in internal time units.
 */
uint64_t HAL_VTIMER_AddSysTimeMs(uint64_t sysTime, int32_t msTime);

/**
 * @brief  Returns the difference between two absolute times: sysTime1-sysTime2.
 * The resulting value is expressed in ms.
 * @param  sysTime2: Absolute time expressed in internal time units.
 * @param  sysTime1: Absolute time expressed in internal time units.
 * @return resulting signed relative time expressed in ms.
 */
int64_t HAL_VTIMER_DiffSysTimeMs(uint64_t sysTime1, uint64_t sysTime2);

/**
 * @brief Starts a one-shot virtual timer for the given absolute timeout value
 *        expressed in internal time units.
 * @param timerHandle: The virtual timer
 * @param time: Absolute time expressed in STU.
 * @retval 0 if the timerHandle is valid.
 * @retval 1 if the timerHandle is not valid. It is already started.
*/
int HAL_VTIMER_StartTimerSysTime(VTIMER_HandleType *timerHandle, uint64_t time);

/**
 * @brief Returns the absolute expiry time of a running timer expressed in internal time units.
 * @param timerHandle: The virtual timer
 * @param sysTime: Absolute time expressed in internal time units.
 */
int HAL_VTIMER_ExpiryTime(VTIMER_HandleType *timerHandle, uint64_t *sysTime);

/**
 * @brief Initialize the timer module. It must be placed in the initialization
 *         section of the application.
 * @retval None
*/
void HAL_VTIMER_Init(HAL_VTIMER_InitType *HAL_TIMER_InitStruct);

/**
 * @brief Timer module state machine. Check and schedule the calibration.
 * Check expired timers and execute user callback.
 * It must be placed inside the infinite loop.
 * @retval None
*/
void HAL_VTIMER_Tick(void);

/**
 * @brief Return the consensus of the Virtual timer management to go in sleep.
 * @retval TRUE if all vtimers have been served and the calibration procedure has already finished. 
 * @retval FALSE if the vtimer Tick is still busy.
*/
BOOL HAL_VTIMER_SleepCheck(void);

/**
 * @brief  Virtual timer Timeout Callback. It signals that a host timeout occured.
 * @retval None
 */
void HAL_VTIMER_TimeoutCallback(void);

/**
 * @brief   If the wakeup timer triggers for a host wakeup, a pending radio activity is programmed.
 *          If the wakeup timer triggers for a radio activity, a pending virtual timer callback is executed.
 * @warning To be considered only if HOST_WAKEUP_FIX_ENABLE is 1.
 * @retval  None
 */
void HAL_VTIMER_WakeUpCallback(void);

/**
 * @brief  Radio activity finished.
 * @retval None
 */
void HAL_VTIMER_RadioTimerIsr(void);

/**
 * @brief  Returns the number of timers in the queue.
  *@return number of timers in the queue.
*/
uint32_t HAL_VTIMER_GetPendingTimers(void);

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
uint8_t HAL_VTIMER_SetRadioTimerValue(uint32_t time, uint8_t event_type, uint8_t cal_req);

/**
 * @brief Disable Timer2. 
 * @retval None
*/
void HAL_VTIMER_StopRadioTimer2(void);

/**
 * @brief  Return the status of the radio timer.
 *         The timeout of the last radio timer activity taken into account by the Timer Module
 *         is saved in the variable passed as parameter.
 * @param time: Pointer of the variable where the time of the last radio activity scheduled is stored
 *               The time is expressed in STU.
 * @retval 0 if no radio timer is pending.
 * @retval 1 if a radio timer is pending.
*/
TimerStatus HAL_VTIMER_GetRadioTimerValue(uint64_t *time);

/**
 * @brief  Clear the last radio activity scheduled disabling the radio timers too.
 *         Furthermore, it returns if the timeout is too close with respect the current time and
 *         the radio activity might not be cleared in time.
 * @retval 0 if the radio activity has been cleared successfully.
 * @retval 1 if it is too late to clear the last radio activity.
 * @retval 2 if it might not be possible to clear the last radio activity.
*/
uint8_t HAL_VTIMER_ClearRadioTimerValue(void);

/**
 * @brief  Get the last anchorPoint in system time unit.
 * @return TimerCapture register in system time unit.
*/
uint64_t HAL_VTIMER_GetAnchorPoint(void);

/**
 * @brief  Returns the admitted sleep mode according to the next timer activity.
 * @return Sleep mode 
*/
PowerSaveLevels HAL_VTIMER_PowerSaveLevelCheck(PowerSaveLevels level);

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

#endif /*RF_DRIVER_HAL_VTIMER_H */
/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/  
