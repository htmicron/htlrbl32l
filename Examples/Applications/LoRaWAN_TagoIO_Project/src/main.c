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

//DEBUG CONFIG FILE:
#ifdef DEBUG
#include "debug_configs.h"
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "uart.h"
#include "spi.h"
#include "rtc.h"
#include "crc.h"
#include "i2c.h"
#include "sx126x.h"
#include "sx126x_board.h"
#include "radio.h"
#include "peripheral_init.h"
#include "lorawan_setup.h"
#include "lora-test.h"
#include "LoRaMac.h"
#include "hal_wrappers.h"
#include "ht_crypto.h"
#include "stsafea_core.h"

RNG_HandleTypeDef hrng;

int main(void) {
	uint8_t status_code = 0;

	 /* System initialization function */
  if (SystemInit(SYSCLK_64M, BLE_SYSCLK_NONE) != SUCCESS) {
    /* Error during system clock configuration take appropriate action */
    while(1);
  }
	 
  	HAL_Init();
	IRQHandler_Config();		
	MX_GPIO_Init();				
	MX_USART1_UART_Init();
	MX_SPI1_Init();
	MX_I2C1_Init();
	MX_I2C2_Init();
	MX_CRC_Init();
	MX_RTC_Init();
	MX_GPIO_LP_Init();
	MX_RNG_Init(&hrng);
	
	printf("HTLRBL32 - Web Platform (TagoIO) Application\n");	
	
	#ifdef HT_CRYPTO

		if(keys_provisioned()){
			status_code = ht_crypto_init();
			if(status_code){
				printf("STSAFE-A1xx NOT initialized. \n");
			while(1){}
			}
		}else{
			printf("LoRaWAN keys are NOT set, please flash&run provisioner firmware to set the keys\n");
			while(1);
		}
	#endif


	LORAWAN_init(DEFAULT_REGION);	
	
#ifdef HT_SENSORS
	HT_IKS01A2_InitSensors();		/*Initialize sensors config.*/
#else
	//ADC Initialization
	APP_ADC_Init();
	APP_DMA_Init();
#endif
	while(1) {
		LORAWAN_tick(); /*handle radio routine*/
	}

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
