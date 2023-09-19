
/*******************************************************
 * File Name        : main.c
 * Author             : Christian Lehmen
 * Date               : 20-November-2020
 * Description      : Certification Firmware - LoRaWAN 1.0.2
 *********************************************************/

//DEBUG CONFIG FILE:
#ifdef DEBUG
#include "debug_configs.h"
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "ht_crypto.h"
#include "stsafea_core.h"
#include "i2c.h"
#include "crc.h"
#include "peripheral_init.h"

NO_INIT(uint32_t dyn_alloc_a[DYNAMIC_MEMORY_SIZE >> 2]);


RNG_HandleTypeDef hrng;

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	uint8_t status_code = 0;

	/* System initialization function */
	//if (SystemInit(SYSCLK_64M, BLE_SYSCLK_NONE) != SUCCESS) {
	if (SystemInit(SYSCLK_DIRECT_HSE, BLE_SYSCLK_32M) != SUCCESS){
		/* Error during system clock configuration take appropriate action */
		while(1);
	}
	HAL_Init();
	IRQHandler_Config();
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	MX_GPIO_LP_Init();
	MX_SPI1_Init();
	MX_I2C2_Init();
	MX_CRC_Init();
	MX_RTC_Init();
	MX_RNG_Init(&hrng);

	HSM_Init();

	printf("HTLRBL32L - Push Button LoRaWAN + Bluetooth Application\n");

	LORAWAN_init(DEFAULT_REGION);
	while(!LORA_JoinStatus()){ // wait for join accept
		LORAWAN_tick();
	}

	ModulesInit();

	HT_BLE_BleConfig();
	HT_BLE_SetDeviceConnectable();

	HT_PB_ConfigWakeupIO();

	HT_PB_Counter_init();

	while (1){
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
void Error_Handler(void)
{
	/* User can add his own implementation to report the HAL error return state */
	printf("Error_Handler\n");
	while(1);
}

void HSM_Init(){

	uint8_t status_code = 0;
#ifdef STSAFE
#ifdef HT_CRYPTO
	if(keys_provisioned()){
#endif

		status_code = ht_crypto_init();
		if(status_code){
			printf("STSAFE-A1xx NOT initialized. \n");
			while(1);
		}

#ifdef HT_CRYPTO
	}else{
		printf("LoRaWAN keys are NOT set, please flash&run provisioner firmware to set the keys\n");
		//while(1);
	}
#endif
#ifndef HT_CRYPTO
	ht_crypto_hibernate();
#endif
#endif
}



#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	F
	/* Infinite loop */
	while (1)
	{
	}
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
