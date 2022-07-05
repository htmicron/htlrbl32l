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

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* System initialization function */
	if (SystemInit(SYSCLK_64M, BLE_SYSCLK_NONE) != SUCCESS){
		/* Error during system clock configuration take appropriate action */
		while (1);
	}

	HAL_Init();
	IRQHandler_Config();
	MX_GPIO_Init();
	MX_USART1_UART_Init();
#if DEEP_SLEEP_MODE == 1
	MX_GPIO_LP_Init();
#endif
	MX_SPI1_Init();
	MX_RTC_Init();

	LORAWAN_init(DEFAULT_REGION);

#if DEEP_SLEEP_MODE == 1
	HT_PB_ConfigWakeupIO();
#endif

	printf("HTLRBL32L - Push Button APP\n");

	while (1) {

		LORAWAN_tick();
		HT_PB_Fsm();
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
