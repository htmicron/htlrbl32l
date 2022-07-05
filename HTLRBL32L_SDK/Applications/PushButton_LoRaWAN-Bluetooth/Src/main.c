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

/* Includes ------------------------------------------------------------------*/

#include "main.h"

NO_INIT(uint32_t dyn_alloc_a[DYNAMIC_MEMORY_SIZE >> 2]);

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* System initialization function */
	if (SystemInit(SYSCLK_DIRECT_HSE, BLE_SYSCLK_32M) != SUCCESS){
		/* Error during system clock configuration take appropriate action */
		while (1);
	}

	HAL_Init();
	IRQHandler_Config();
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	MX_GPIO_LP_Init();
	MX_SPI1_Init();
	MX_RTC_Init();

	ModulesInit();

	LORAWAN_init(DEFAULT_REGION);

	HT_BLE_BleConfig();
	HT_BLE_SetDeviceConnectable();

	HT_PB_ConfigWakeupIO();

	printf("HTLRBL32L - Push Button LoRaWAN + Bluetooth Application\n");

	while (1) {

		ModulesTick();
		LORAWAN_tick();
		HT_PB_app();

	}
}

void ModulesInit(void) {
	uint8_t ret;
	BLE_STACK_InitTypeDef BLE_STACK_InitParams = BLE_STACK_INIT_PARAMETERS;

	LL_AHB_EnableClock(LL_AHB_PERIPH_PKA|LL_AHB_PERIPH_RNG);

	/* BlueNRG-LP stack init */
	ret = BLE_STACK_Init(&BLE_STACK_InitParams);
	if (ret != BLE_STATUS_SUCCESS) {
		printf("Error in BLE_STACK_Init() 0x%02x\r\n", ret);
		while(1);
	}

	BLECNTR_InitGlobal();

	HAL_VTIMER_InitType VTIMER_InitStruct = {HS_STARTUP_TIME, INITIAL_CALIBRATION, CALIBRATION_INTERVAL};
	HAL_VTIMER_Init(&VTIMER_InitStruct);

	BLEPLAT_Init();
	if (PKAMGR_Init() == PKAMGR_ERROR)
		while(1);

	if (RNGMGR_Init() != RNGMGR_SUCCESS)
		while(1);

	/* Init the AES block */
	AESMGR_Init();
}

void ModulesTick(void) {
	/* Timer tick */
	HAL_VTIMER_Tick();

	/* Bluetooth stack tick */
	BLE_STACK_Tick();

	/* NVM manager tick */
	NVMDB_Tick();
}

void hci_hardware_error_event(uint8_t Hardware_Code) {
	if (Hardware_Code <= 0x03) {
		printf("Error code: 0x%02X\n", Hardware_Code);
		NVIC_SystemReset();
	}
}

void aci_hal_fw_error_event(uint8_t FW_Error_Type, uint8_t Data_Length, uint8_t Data[]) {
	if (FW_Error_Type <= 0x03) {
		uint16_t connHandle;

		/* Data field is the connection handle where error has occurred */
		connHandle = LE_TO_HOST_16(Data);

		aci_gap_terminate(connHandle, BLE_ERROR_TERMINATED_REMOTE_USER);
	}
}

PowerSaveLevels App_PowerSaveLevel_Check(PowerSaveLevels level) {
	return POWER_SAVE_LEVEL_STOP_NOTIMER;
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {

	/* User can add his own implementation to report the HAL error return state */
	printf("Error_Handler!\n");
	while (1);
}

/************************ HT MICRON SEMICONDUCTORS S.A - main.c *****END OF FILE****/
