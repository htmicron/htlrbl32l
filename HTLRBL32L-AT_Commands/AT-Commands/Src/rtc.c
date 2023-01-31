/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include <math.h>
#include "rtc.h"
#include "utils.h"

/* USER CODE BEGIN 0 */
static RTC_AlarmTypeDef RTC_AlarmStructure;
static void HW_RTC_StartWakeUpAlarm( uint32_t timeoutValue );
static void HW_RTC_SetAlarmConfig( void );
static RtcTimerContext_t RtcTimerContext;
static uint64_t HW_RTC_GetCalendarValue(  RTC_DateTypeDef* RTC_DateStruct, RTC_TimeTypeDef* RTC_TimeStruct  );

void HW_RTC_Init( void ){

	HW_RTC_SetAlarmConfig();
	HW_RTC_SetTimerContext( );

}
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
		printf("Error HAL_RTC_Init\n");
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.SubSeconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
	  printf("Error HAL_RTC_SetTime\n");

    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
		printf("Error HAL_RTC_SetDate\n");

    Error_Handler();
  }
  /** Enable the Alarm A 
  */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x0;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
		printf("Error HAL_RTC_SetAlarm_IT\n");

    Error_Handler();
  }
    HAL_NVIC_SetPriority(RTC_IRQn,0);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
	
	
	HW_RTC_Init();
}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    /* RTC clock enable */
    __HAL_RCC_RTC_CLK_ENABLE();
   // __HAL_RCC_RTCAPB_CLK_ENABLE();

    /* RTC interrupt Init */
//    HAL_NVIC_SetPriority(RTC_IRQn, 0);
//    HAL_NVIC_EnableIRQ(RTC_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_CLK_DISABLE();
//    __HAL_RCC_RTCAPB_CLK_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
TimerTime_t RtcTempCompensation( TimerTime_t period, float temperature )
{
    float k = RTC_TEMP_COEFFICIENT;
    float kDev = RTC_TEMP_DEV_COEFFICIENT;
    float t = RTC_TEMP_TURNOVER;
    float tDev = RTC_TEMP_DEV_TURNOVER;
    float interim = 0.0;
    float ppm = 0.0;

    if( k < 0.0f )
    {
        ppm = ( k - kDev );
    }
    else
    {
        ppm = ( k + kDev );
    }
    interim = ( temperature - ( t - tDev ) );
    ppm *=  interim * interim;

    // Calculate the drift in time
    interim = ( ( float ) period * ppm ) / 1000000;
    // Calculate the resulting time period
    interim += period;
    interim = floor( interim );

    if( interim < 0.0f )
    {
        interim = ( float )period;
    }

    // Calculate the resulting period
    return ( TimerTime_t ) interim;
}

static void HW_RTC_SetAlarmConfig( void )
{
  HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A);
}

void HW_RTC_SetAlarm( uint32_t timeout ){
  /* we don't go in Low Power mode for timeout below MIN_ALARM_DELAY */
//  if ( (MIN_ALARM_DELAY + McuWakeUpTimeCal ) < ((timeout - HW_RTC_GetTimerElapsedTime( ) )) )
//  {
    //LPM_SetStopMode(LPM_RTC_Id , LPM_Enable );
//  }
//  else
//  {
//    LPM_SetStopMode(LPM_RTC_Id , LPM_Disable );
//  }

//  /*In case stop mode is required */
//  if( LPM_GetMode() == LPM_StopMode )
//  {
//    timeout = timeout -  McuWakeUpTimeCal;
//  }

  HW_RTC_StartWakeUpAlarm( timeout );
}

uint32_t HW_RTC_GetCalendarTime( uint16_t *mSeconds)
{
  RTC_TimeTypeDef RTC_TimeStruct ;
  RTC_DateTypeDef RTC_DateStruct;
  uint32_t ticks;

  uint64_t calendarValue = HW_RTC_GetCalendarValue( &RTC_DateStruct, &RTC_TimeStruct );

  uint32_t seconds = (uint32_t) (calendarValue >> N_PREDIV_S);

  ticks =  (uint32_t) calendarValue&PREDIV_S;

  *mSeconds = HW_RTC_Tick2ms(ticks);

  return seconds;
}

TimerTime_t HW_RTC_Tick2ms( uint32_t tick ){

/*return( ( timeMicroSec * RTC_ALARM_TIME_BASE ) ); */
  uint32_t seconds = tick>>N_PREDIV_S;
  tick = tick&PREDIV_S;
  return  ( ( seconds*1000 ) + ((tick*1000)>>N_PREDIV_S) );
}

uint32_t HW_RTC_GetTimerValue( void ){

  RTC_TimeTypeDef RTC_TimeStruct;
  RTC_DateTypeDef RTC_DateStruct;

  uint32_t CalendarValue = (uint32_t) HW_RTC_GetCalendarValue(&RTC_DateStruct, &RTC_TimeStruct );

  return( CalendarValue );
}


uint32_t HW_RTC_SetTimerContext( void ){

  RtcTimerContext.Rtc_Time = ( uint32_t ) HW_RTC_GetCalendarValue( &RtcTimerContext.RTC_Calndr_Date, &RtcTimerContext.RTC_Calndr_Time );

  return ( uint32_t ) RtcTimerContext.Rtc_Time;
}

static uint64_t HW_RTC_GetCalendarValue( RTC_DateTypeDef* RTC_DateStruct, RTC_TimeTypeDef* RTC_TimeStruct ){

	//printf("Acquiring calendar value\n");
  uint64_t calendarValue = 0;
//  uint32_t first_read;
  uint32_t correction;
  uint32_t seconds;

  /* Get Time and Date*/
  HAL_RTC_GetTime( &hrtc, RTC_TimeStruct, RTC_FORMAT_BIN );

   /* make sure it is correct due to asynchronus nature of RTC*/
 // do {
   // first_read = LL_RTC_TIME_GetSubSecond(RTC);
	HAL_RTC_GetTime( &hrtc, RTC_TimeStruct, RTC_FORMAT_BIN );
  	HAL_RTC_GetDate( &hrtc, RTC_DateStruct, RTC_FORMAT_BIN );
	//	printf("first read: %u\n",first_read);
		//HAL_Delay(1);
		
// // } while (first_read != LL_RTC_TIME_GetSubSecond(RTC) );

  /* calculte amount of elapsed days since 01/01/2000 */
  seconds= DIVC( (DAYS_IN_YEAR*3 + DAYS_IN_LEAP_YEAR)* RTC_DateStruct->Year , 4);

  correction = ( (RTC_DateStruct->Year % 4) == 0 ) ? DAYS_IN_MONTH_CORRECTION_LEAP : DAYS_IN_MONTH_CORRECTION_NORM ;

  seconds +=( DIVC( (RTC_DateStruct->Month-1)*(30+31) ,2 ) - (((correction>> ((RTC_DateStruct->Month-1)*2) )&0x3)));

  seconds += (RTC_DateStruct->Date -1);

  /* convert from days to seconds */
  seconds *= SECONDS_IN_1DAY;

  seconds += ( ( uint32_t )RTC_TimeStruct->Seconds +
             ( ( uint32_t )RTC_TimeStruct->Minutes * SECONDS_IN_1MINUTE ) +
             ( ( uint32_t )RTC_TimeStruct->Hours * SECONDS_IN_1HOUR ) ) ;

  

  calendarValue = (((uint64_t) seconds)<<N_PREDIV_S) + ( PREDIV_S - RTC_TimeStruct->SubSeconds);
//	printf("calendarValue: %lu\n",(uint64_t)calendarValue);
  return( calendarValue );
}


uint32_t HW_RTC_GetTimerElapsedTime( void ){

  RTC_TimeTypeDef RTC_TimeStruct;
  RTC_DateTypeDef RTC_DateStruct;

  uint32_t CalendarValue = (uint32_t) HW_RTC_GetCalendarValue(&RTC_DateStruct, &RTC_TimeStruct );

  return( ( uint32_t )( CalendarValue - RtcTimerContext.Rtc_Time ));
}

uint32_t HW_RTC_GetTimerContext( void ){

  return RtcTimerContext.Rtc_Time;
}

void HW_RTC_StopAlarm( void )
{
  /* Disable the Alarm A interrupt */
  HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A );
  /* Clear RTC Alarm Flag */
  __HAL_RTC_ALARM_CLEAR_FLAG( &hrtc, RTC_FLAG_ALRAF);
  /* Clear the EXTI's line Flag for RTC Alarm */
//  __HAL_RTC_ALARM_EXTI_CLEAR_FLAG();
}

uint32_t HW_RTC_ms2Tick( TimerTime_t timeMilliSec )
{
/*return( ( timeMicroSec / RTC_ALARM_TIME_BASE ) ); */
  return ( uint32_t) ( ( ((uint64_t)timeMilliSec) * CONV_DENOM ) / CONV_NUMER );
}

uint32_t HW_RTC_GetMinimumTimeout( void )
{
  return( MIN_ALARM_DELAY );
}

void HW_RTC_BKUPWrite( uint32_t Data0, uint32_t Data1)
{
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, Data0);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, Data1);
}

void HW_RTC_BKUPRead( uint32_t *Data0, uint32_t *Data1)
{
  *Data0=HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0);
  *Data1=HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
}

static void HW_RTC_StartWakeUpAlarm( uint32_t timeoutValue )
{
  uint16_t rtcAlarmSubSeconds = 0;
  uint16_t rtcAlarmSeconds = 0;
  uint16_t rtcAlarmMinutes = 0;
  uint16_t rtcAlarmHours = 0;
  uint16_t rtcAlarmDays = 0;
  RTC_TimeTypeDef RTC_TimeStruct = RtcTimerContext.RTC_Calndr_Time;
  RTC_DateTypeDef RTC_DateStruct = RtcTimerContext.RTC_Calndr_Date;

  HW_RTC_StopAlarm( );

  /*reverse counter */
  rtcAlarmSubSeconds =  PREDIV_S - RTC_TimeStruct.SubSeconds;
  rtcAlarmSubSeconds += ( timeoutValue & PREDIV_S);
  /* convert timeout  to seconds */
  timeoutValue >>= N_PREDIV_S;  /* convert timeout  in seconds */
 
  /*convert microsecs to RTC format and add to 'Now' */
  rtcAlarmDays =  RTC_DateStruct.Date;
  while (timeoutValue >= SECONDS_IN_1DAY)
  {
    timeoutValue -= SECONDS_IN_1DAY;
    rtcAlarmDays++;
  }

  /* calc hours */
  rtcAlarmHours = RTC_TimeStruct.Hours;
	//printf("=======\nReference Time\n=======\nRTC hours: %u\n",RTC_TimeStruct.Hours);
  while (timeoutValue >= SECONDS_IN_1HOUR)
  {
    timeoutValue -= SECONDS_IN_1HOUR;
    rtcAlarmHours++;
  }

  /* calc minutes */
  rtcAlarmMinutes = RTC_TimeStruct.Minutes;
	//printf("RTC minutes: %u\n",RTC_TimeStruct.Minutes);

  while (timeoutValue >= SECONDS_IN_1MINUTE)
  {
    timeoutValue -= SECONDS_IN_1MINUTE;
    rtcAlarmMinutes++;
  }

  /* calc seconds */
  rtcAlarmSeconds =  RTC_TimeStruct.Seconds + timeoutValue;
 //printf("RTC seconds: %u\n",RTC_TimeStruct.Seconds);
  /***** correct for modulo********/
  while (rtcAlarmSubSeconds >= (PREDIV_S+1))
  {
    rtcAlarmSubSeconds -= (PREDIV_S+1);
    rtcAlarmSeconds++;
  }

  while (rtcAlarmSeconds >= SECONDS_IN_1MINUTE)
  {
    rtcAlarmSeconds -= SECONDS_IN_1MINUTE;
    rtcAlarmMinutes++;
  }

  while (rtcAlarmMinutes >= MINUTES_IN_1HOUR)
  {
    rtcAlarmMinutes -= MINUTES_IN_1HOUR;
    rtcAlarmHours++;
  }

  while (rtcAlarmHours >= HOURS_IN_1DAY)
  {
    rtcAlarmHours -= HOURS_IN_1DAY;
    rtcAlarmDays++;
  }

  if( RTC_DateStruct.Year % 4 == 0 )
  {
    if( rtcAlarmDays > DaysInMonthLeapYear[ RTC_DateStruct.Month - 1 ] )
    {
      rtcAlarmDays = rtcAlarmDays % DaysInMonthLeapYear[ RTC_DateStruct.Month - 1 ];
    }
  }
  else
  {
    if( rtcAlarmDays > DaysInMonth[ RTC_DateStruct.Month - 1 ] )
    {
      rtcAlarmDays = rtcAlarmDays % DaysInMonth[ RTC_DateStruct.Month - 1 ];
    }
  }

  /* Set RTC_AlarmStructure with calculated values*/
  RTC_AlarmStructure.AlarmTime.SubSeconds = PREDIV_S-rtcAlarmSubSeconds;
  RTC_AlarmStructure.AlarmSubSecondMask  = RTC_ALARMSUBSECONDMASK_NONE;
	RTC_AlarmStructure.AlarmTime.Seconds = rtcAlarmSeconds;
  RTC_AlarmStructure.AlarmTime.Minutes = rtcAlarmMinutes;
  RTC_AlarmStructure.AlarmTime.Hours   = rtcAlarmHours;
  RTC_AlarmStructure.AlarmDateWeekDay    = ( uint8_t )rtcAlarmDays;
  RTC_AlarmStructure.AlarmTime.TimeFormat   = RTC_TimeStruct.TimeFormat;
  RTC_AlarmStructure.AlarmDateWeekDaySel   = RTC_ALARMDATEWEEKDAYSEL_DATE;
  RTC_AlarmStructure.AlarmMask       = RTC_ALARMMASK_NONE;
  RTC_AlarmStructure.Alarm = RTC_ALARM_A;
  RTC_AlarmStructure.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  RTC_AlarmStructure.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;

//	printf("========\nALARM: \nSeconds:%u\nMinutes:%u\nHours: %u\nWeekDay:%u\nSubseconds:%u\n========\n",RTC_AlarmStructure.AlarmTime.Seconds,RTC_AlarmStructure.AlarmTime.Minutes,
	//RTC_AlarmStructure.AlarmTime.Hours,RTC_AlarmStructure.AlarmDateWeekDay,RTC_AlarmStructure.AlarmTime.SubSeconds);
	
	  /* Set RTC_Alarm */
	HAL_RTC_SetAlarm_IT( &hrtc, &RTC_AlarmStructure, RTC_FORMAT_BIN );
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
