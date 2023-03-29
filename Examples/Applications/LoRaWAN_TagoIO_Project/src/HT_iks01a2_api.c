/**
 *
 * Copyright (c) 2022 HT Micron Semicondutors S.A.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifdef HT_SENSORS

/* Includes ------------------------------------------------------------------*/

#include "HT_iks01a2_api.h"

/* Function Prototypes  -------------------------------------------------------*/

/*!******************************************************************
 * \fn static void HT_IKS01A2_HTS221_Init(void)
 * \brief Initializes HTS221 sensor.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_IKS01A2_HTS221_Init(void);

/*!******************************************************************
 * \fn static void OnSensorsTimerEvent(void)
 * \brief Sensor timer callback.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void OnSensorsTimerEvent(void *context);  

/*!******************************************************************
 * \fn static void HT_IKS01A2_LSP22HB_Init(void)
 * \brief Initializes LSP22HB sensor.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_IKS01A2_LSP22HB_Init(void);

/*!******************************************************************
 * \fn static void HT_IKS01A2_InitTimer(void)
 * \brief Initializes a timer that manage the periodicity of the measurements with the sensors board.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_IKS01A2_InitTimer(void);

/*!******************************************************************
 * \fn static float HT_IKS01A2_ReadTemperatureHTS221(void)
 * \brief Read and returns the temperature value measured by HTS221 sensor.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval Temperature value in float.
 *******************************************************************/
static float HT_IKS01A2_ReadTemperatureHTS221(void);

/*!******************************************************************
 * \fn static float HT_IKS01A2_ReadHumidity(void)
 * \brief Read and returns the humidity value.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval Humidity value in float.
 *******************************************************************/
static float HT_IKS01A2_ReadHumidity(void);

/*!******************************************************************
 * \fn static float HT_IKS01A2_ReadPressure(void)
 * \brief Read and returns the pressure value.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval Pressure value in float.
 *******************************************************************/
static float HT_IKS01A2_ReadPressure(void);

/*!******************************************************************
 * \fn static void HT_IKS01A2_CalibrateTemperatureHTS221(void)
 * \brief Calibrates the temperature of the HTS221 sensor.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_IKS01A2_CalibrateTemperatureHTS221(void);

/*!******************************************************************
 * \fn static void HT_IKS01A2_CalibrateHumidityHTS221(void)
 * \brief Calibrates the humidity of the HTS221 sensor.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_IKS01A2_CalibrateHumidityHTS221(void);

/*!******************************************************************
 * \fn static void HT_IKS01A2_TxLora(void)
 * \brief Send a LoRa uplink to update the dashboard data.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_IKS01A2_TxLora(void);

/* Variables  -----------------------------------------------------------------*/

static TimerEvent_t sensorsTimer;
uint16_t T0_degC, T1_degC;
int16_t T0_OUT, T1_OUT, T_OUT;
float temp = 0.0;
float P = 0.0;

uint16_t H0_T0_OUT, H1_T0_OUT, H_T_OUT;
float humidity = 0.0;
uint16_t H0_rH_x2, H1_rH_x2, H0_rH, H1_rH;

HT_payload buff = {0};

/* Functions  ----------------------------------------------------------------*/

static void HT_IKS01A2_HTS221_Init(void){
	uint8_t reg = 0x82;	

	HAL_I2C_Mem_Write(&hi2c2, HTS221_WRITE_ADDR, 0x20, I2C_MEMADD_SIZE_8BIT, &reg, 1, I2C_APP_TIMEOUT);
	HT_IKS01A2_CalibrateTemperatureHTS221(); /* Gets HTS221 sensor calibration data */	
}

static void HT_IKS01A2_LSP22HB_Init(void){
	uint8_t buffer[2];

	buffer[0] = 0X3A;    
	buffer[1] = 0X10;
	
	HAL_I2C_Mem_Write(&hi2c2, 0xBA, 0x10, I2C_MEMADD_SIZE_8BIT,&buffer[0],1,I2C_APP_TIMEOUT); //REG1
	HAL_I2C_Mem_Write(&hi2c2, 0xBA, 0x11, I2C_MEMADD_SIZE_8BIT,&buffer[1],1,I2C_APP_TIMEOUT); //REG2
	
	HT_IKS01A2_CalibrateHumidityHTS221();	/* Gets LSP22HB sensor calibration data */
}

static void HT_IKS01A2_CalibrateTemperatureHTS221(void){
	uint8_t buffer[2];
	uint8_t T0_degC_x8_u8, T1_degC_x8_u8, x;
	
	buffer[0] = 0;
	
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x32, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1,I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x33, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1,I2C_APP_TIMEOUT);
	T0_degC_x8_u8 = buffer[0] & 0xFF;
	T1_degC_x8_u8 = buffer[1] & 0xFF;
	
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x35, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1,I2C_APP_TIMEOUT);
	x = buffer[0] &0x0F;
	T0_degC = ((x & 0x03) * 256) + T0_degC_x8_u8;
	T1_degC = ((x & 0x0C) * 64) + T1_degC_x8_u8;
	
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x3C, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1,I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x3D, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1,I2C_APP_TIMEOUT);
	T0_OUT = ((buffer[1] & 0xFF) * 256) + (buffer[0] & 0xFF);

	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x3E, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1,I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x3F, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1,I2C_APP_TIMEOUT);
	T1_OUT = ((buffer[1] & 0xFF) * 256) + (buffer[0] & 0xFF);
}

static void HT_IKS01A2_CalibrateHumidityHTS221(void){
	uint8_t buffer[2];
	
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x30, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1 , I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x31, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1 , I2C_APP_TIMEOUT);
	H0_rH_x2 = buffer[0];
	H1_rH_x2 = buffer[1];
	
	H0_rH = H0_rH_x2 >> 1;  
	H1_rH = H1_rH_x2 >> 1;  
	
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x36, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1 , I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x37, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1 , I2C_APP_TIMEOUT);
	
	H0_T0_OUT = ((buffer[1] & 0xFF) * 256) + (buffer[0] & 0xFF); 
	
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x3A, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1 , I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x3B, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1 , I2C_APP_TIMEOUT);
	
	H1_T0_OUT = ((buffer[1] & 0xFF) * 256) + (buffer[0] & 0xFF); 
}

static void HT_IKS01A2_InitTimer(void){
	TimerInit( &sensorsTimer, OnSensorsTimerEvent ); /* Timer initialization */
    TimerSetValue( &sensorsTimer, APP_SENSORS_DUTYCYCLE);	/* Sets alarm total time */			
	TimerStart(&sensorsTimer);	/* Callback call */
}

static void OnSensorsTimerEvent( void* context ){
	HAL_I2C_MspInit(&hi2c2);
	HT_IKS01A2_ReadTemperatureHTS221();		/* Reads HTS221 temperature data */
	HT_IKS01A2_ReadHumidity();							/* Reads HTS221 humidity data */
	HT_IKS01A2_ReadPressure();							/* Reads LSP22HB pressure data */
	HAL_I2C_MspDeInit(&hi2c2);
	TimerStart(&sensorsTimer);
	HT_IKS01A2_TxLora();										/* Sends Lora packet to the gateway */			
}

static float HT_IKS01A2_ReadTemperatureHTS221(void){
	uint8_t buffer[2];
	
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x2A, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1, I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x2B, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1, I2C_APP_TIMEOUT);
	T_OUT = ((buffer[1]*256) + buffer[0]);
	
	temp = ((T1_degC - T0_degC) / 8.0) * (T_OUT - T0_OUT) / (T1_OUT - T0_OUT) + (T0_degC / 8.0);

	return temp;
}

static float HT_IKS01A2_ReadHumidity(void) {	
	uint8_t buffer[2];
	
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x28, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1 , I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, HTS221_READ_ADDR, 0x29, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1 , I2C_APP_TIMEOUT);
	
	H_T_OUT = ((buffer[1] & 0xFF) * 256) + (buffer[0] & 0xFF);;
	
	humidity = ((float)((H1_rH - H0_rH) * (H_T_OUT - H0_T0_OUT))/(float)(H1_T0_OUT - H0_T0_OUT)) + H0_rH;

	return humidity;	
}

static float HT_IKS01A2_ReadPressure(void){
	uint8_t buffer[3];
	int32_t aux;
		
	HAL_I2C_Mem_Read(&hi2c2, 0xBB, 0x28, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1,I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, 0xBB, 0x29, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1,I2C_APP_TIMEOUT);
	HAL_I2C_Mem_Read(&hi2c2, 0xBB, 0x2A, I2C_MEMADD_SIZE_8BIT, &buffer[2], 1,I2C_APP_TIMEOUT);
	
	aux = (((uint32_t)buffer[2]) << 16) | (((uint32_t)buffer[1]) << 8) | ((uint32_t)buffer[0]);
	P = ((float)aux)/4095; /* Return pressure in hPa */
	P = P * 0.0009869233;  /* Convert pressure to atm */
	
	return P;
}

static void HT_IKS01A2_TxLora(void){
	HT_payload buff;
	lora_AppData_t appData;
		
	buff.temperature = temp*100;
	buff.humi = humidity*100;
	buff.p = P*100;
	
	/*
	printf("temperature: %.2f  ---- %04X\n", temp, buff.temperature);
	printf("humidity: %.2f  ---- %04X\n",humidity, buff.humi);
	printf("pressure: %.2f  ---- %04X\n",P, buff.p);
	printf("\nBuffer TX: 0x%04X%04X%02X", buff.temperature, buff.humi, buff.p);
	*/

	appData.Buff = (uint8_t *)&buff;

	appData.BuffSize = sizeof(HT_payload);
	appData.Port = LORAWAN_APP_PORT;
	
	lorawan_send(&appData);
}

void HT_IKS01A2_InitSensors(void){
	HT_IKS01A2_HTS221_Init();			/* Initializes HTS221 temperature and humidity sensor */
	HT_IKS01A2_LSP22HB_Init();			/* Initializes LSP22HB pressure sensor */
	HT_IKS01A2_InitTimer();				/* Initializes application timer */
}

#endif

/************************ HT MICRON SEMICONDUCTORS S.A - HT_iks01a2_api.c *****END OF FILE****/
