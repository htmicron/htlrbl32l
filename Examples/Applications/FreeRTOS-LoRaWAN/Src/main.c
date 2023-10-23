
/*******************************************************
 * File Name        : main.c
 * Author           : Christian Lehmen, Eduardo Mendel
 * Date             : 18-October-2023
 * Description      : FreeRTOS - LoRaWAN 1.0.2
 *********************************************************/

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

#define TEST_TASK_PRIORITY		            ( tskIDLE_PRIORITY + 1 )
#define	LORA_TASK_PRIORITY		            ( tskIDLE_PRIORITY + 2 )



RNG_HandleTypeDef hrng;

/* Mutex used to avoid that the LoRaWAN Stack Tick can be interrupted
 * another thread. */
SemaphoreHandle_t LoRaSemaphoreHandle;
/* Mutex used to access UART resource */
SemaphoreHandle_t UARTSemaphoreHandle;

TaskHandle_t testHandle;
TaskHandle_t loraHandle;

TickType_t testLastTick = 0;

void createTasks( void );

/*
LoRaWAN related configs
#include "lorawandefines.h"
 */

/**
 * @brief  The application entry point.
 * @retval int
 */
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
	MX_I2C2_Init();
	MX_CRC_Init();
	MX_RTC_Init();
	MX_GPIO_LP_Init();
	MX_RNG_Init(&hrng);

	HSM_Init();

	UARTSemaphoreHandle = xSemaphoreCreateMutex();
	LoRaSemaphoreHandle = xSemaphoreCreateMutex();


	if(LoRaSemaphoreHandle==NULL || UARTSemaphoreHandle==NULL)
	{
		while(1);
	}

	createTasks();

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

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */

static void LORATask( void *pvParameters )
{
	uint8_t lastvalue;
	if(xSemaphoreTake(LoRaSemaphoreHandle, portMAX_DELAY) == pdTRUE)
	{
		LORAWAN_init(DEFAULT_REGION);
		xSemaphoreGive(LoRaSemaphoreHandle);
		while(1)
		{
			if(xSemaphoreTake(LoRaSemaphoreHandle, portMAX_DELAY) == pdTRUE)
			{
				LORAWAN_tick();
				xSemaphoreGive(LoRaSemaphoreHandle);
				if(SX126xGetOperatingMode() == MODE_SLEEP && pMacCtxFlags->Value == 0 && (xTaskGetTickCount() - testLastTick > 3000))
				{
					printf("\nLORA TASK SUSPENDED!\n");
					vTaskResume(testHandle);
					vTaskSuspend(loraHandle);
				}

			}
		}
	}

}

static void testTask( void *pvParameters )
{
	while(1)
	{
		if(pMacCtxFlags->Value == 0)
		{
			PRINTF("\n\n============= TEST TASK =============\nTick count: %d\n=====================================\n\n", xTaskGetTickCount());

		}
		testLastTick = xTaskGetTickCount();
		vTaskResume(loraHandle);
	}
}

void createTasks( void )
{

	xTaskCreate(LORATask,"LoRa", configMINIMAL_STACK_SIZE+400, NULL, LORA_TASK_PRIORITY, &loraHandle);

	xTaskCreate( testTask, "Test", configMINIMAL_STACK_SIZE+100, NULL, TEST_TASK_PRIORITY, &testHandle );
	vTaskSuspend(testHandle);
	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following
  line will never be reached.  If the following line does execute, then
  there was insufficient FreeRTOS heap memory available for the idle and/or
  timer tasks	to be created.  See the memory management section on the
  FreeRTOS web site for more details. */
	for( ;; );
}

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
  configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
  function that will get called if a call to pvPortMalloc() fails.
  pvPortMalloc() is called internally by the kernel whenever a task, queue,
  timer or semaphore is created.  It is also called by various parts of the
  demo application.  If heap_1.c or heap_2.c are used, then the size of the
  heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
  FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
  to query the size of free heap space that remains (although it does not
  provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
  to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
  task.  It is essential that code added to this hook function never attempts
  to block in any way (for example, call xQueueReceive() with a block time
  specified, or call vTaskDelay()).  If the application makes use of the
  vTaskDelete() API function (as this demo application does) then it is also
  important that vApplicationIdleHook() is permitted to return to its calling
  function, because it is the responsibility of the idle task to clean up
  memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
  configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
  function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
  configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
  added here, but the tick hook is called from an interrupt context, so
  code must not attempt to block, and only the interrupt safe FreeRTOS API
  functions can be used (those that end in FromISR()). */
}
/*-----------------------------------------------------------*/

void Error_Handler(void)
{
	/* User can add his own implementation to report the HAL error return state */
	printf("Error_Handler\n");
	while(1);
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
