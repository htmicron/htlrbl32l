/*
  _    _ _______   __  __ _____ _____ _____   ____  _   _
 | |  | |__   __| |  \/  |_   _/ ____|  __ \ / __ \| \ | |
 | |__| |  | |    | \  / | | || |    | |__) | |  | |  \| |
 |  __  |  | |    | |\/| | | || |    |  _  /| |  | | . ` |
 | |  | |  | |    | |  | |_| || |____| | \ \| |__| | |\  |
 |_|  |_|  |_|    |_|  |_|_____\_____|_|  \_\\____/|_| \_|
 =================== Advanced R&D ========================

*/

/*!
 * \file rtc.h
 * \brief This file contains all the function prototypes for the rtc.c file
 * \author HT Micron Advanced R&D
 * \link support_iot@htmicron.com.br
 * \version 1.0
 * \date January 05, 2022
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H__
#define __RTC_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>
#include "utils.h"

extern RTC_HandleTypeDef hrtc;

void MX_RTC_Init(void);

void HW_RTC_Init(void);

#define RTC_ASYNCH_PREDIV    0x7F
#define RTC_SYNCH_PREDIV     0x0FF

#define DIVC( X, N ) ( ( ( X ) + ( N ) -1 ) / ( N ) )
#define MIN_ALARM_DELAY               3 /* in ticks */

/* subsecond number of bits */
#define N_PREDIV_S                 8

/* Synchonuous prediv  */
#define PREDIV_S                  ((1<<N_PREDIV_S)-1)

/* Asynchonuous prediv   */
#define PREDIV_A                  (1<<(15-N_PREDIV_S))-1

/* Sub-second mask definition  */
#define HW_RTC_ALARMSUBSECONDMASK (N_PREDIV_S<<RTC_ALRMASSR_MASKSS_Pos)

/* RTC Time base in us */
#define USEC_NUMBER               1000000
#define MSEC_NUMBER               (USEC_NUMBER/1000)
#define RTC_ALARM_TIME_BASE       (USEC_NUMBER>>N_PREDIV_S)

#define COMMON_FACTOR        3
#define CONV_NUMER                (MSEC_NUMBER>>COMMON_FACTOR)
#define CONV_DENOM                (1<<(N_PREDIV_S-COMMON_FACTOR))

#define DAYS_IN_LEAP_YEAR                        ( ( uint32_t )  366U )
#define DAYS_IN_YEAR                             ( ( uint32_t )  365U )
#define SECONDS_IN_1DAY                          ( ( uint32_t )86400U )
#define SECONDS_IN_1HOUR                         ( ( uint32_t ) 3600U )
#define SECONDS_IN_1MINUTE                       ( ( uint32_t )   60U )
#define MINUTES_IN_1HOUR                         ( ( uint32_t )   60U )
#define HOURS_IN_1DAY                            ( ( uint32_t )   24U )

#define  DAYS_IN_MONTH_CORRECTION_NORM     ((uint32_t) 0x99AAA0 )
#define  DAYS_IN_MONTH_CORRECTION_LEAP     ((uint32_t) 0x445550 )
#define MIN_ALARM_DELAY               3 /* in ticks */

#define RTC_TEMP_COEFFICIENT                            ( -0.035 )

/*!
 * \brief Temperature coefficient deviation of the clock source
 */
#define RTC_TEMP_DEV_COEFFICIENT                        ( 0.0035 )

/*!
 * \brief Turnover temperature of the clock source
 */
#define RTC_TEMP_TURNOVER                               ( 25.0 )

/*!
 * \brief Turnover temperature deviation of the clock source
 */
#define RTC_TEMP_DEV_TURNOVER                           ( 5.0 )


/*!
 * Number of days in each month on a normal year
 */
static const uint8_t DaysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/*!
 * Number of days in each month on a leap year
 */
static const uint8_t DaysInMonthLeapYear[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

TimerTime_t RtcTempCompensation( TimerTime_t period, float temperature );

void HW_RTC_SetAlarm( uint32_t timeout );

typedef struct {
  uint32_t  Rtc_Time; /* Reference time */
  RTC_TimeTypeDef RTC_Calndr_Time; /* Reference time in calendar format */
  RTC_DateTypeDef RTC_Calndr_Date; /* Reference date in calendar format */
} RtcTimerContext_t;

TimerTime_t HW_RTC_Tick2ms( uint32_t tick );
uint32_t HW_RTC_GetCalendarTime( uint16_t *mSeconds);
uint32_t HW_RTC_GetTimerValue( void );
uint32_t HW_RTC_SetTimerContext( void );
uint32_t HW_RTC_GetTimerContext( void );
uint32_t HW_RTC_GetTimerElapsedTime( void );
void HW_RTC_StopAlarm( void );
uint32_t HW_RTC_ms2Tick( TimerTime_t timeMilliSec );
uint32_t HW_RTC_GetMinimumTimeout( void );
void HW_RTC_BKUPWrite( uint32_t Data0, uint32_t Data1);
void HW_RTC_BKUPRead( uint32_t *Data0, uint32_t *Data1);

#endif /*__ rtc_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
