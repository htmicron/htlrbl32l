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

/* Includes  ------------------------------------------------------------------*/

#include "uart.h"

/* Variables  -----------------------------------------------------------------*/

UART_HandleTypeDef huart1;

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

	return ch;
}

/* Functions  ------------------------------------------------------------------*/

void MX_USART1_UART_Init(void) {

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200U;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&huart1) != HAL_OK) {
		printf("Error HAL_UART_Init\n");
		Error_Handler();
	}

	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK) {
		printf("Error HAL_UARTEx_SetTxFifoThreshold\n");
		Error_Handler();
	}

	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK) {
		printf("Error HAL_UARTEx_SetRxFifoThreshold\n");
		Error_Handler();
	}

	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK ) {
		printf("Error HAL_UARTEx_DisableFifoMode\n");
		Error_Handler();
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {

	if (huart->Instance == USART1) {
		__HAL_RCC_USART_FORCE_RESET();
		__HAL_RCC_USART_RELEASE_RESET();
		/* Peripheral clock disable */
		__HAL_RCC_USART_CLK_DISABLE();

		/**USART1 GPIO Configuration
		PA9/AF0     ------> USART1_TX
    	PA8/AF0     ------> USART1_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8 | GPIO_PIN_9);
	}
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
	GPIO_InitTypeDef GPIO_InitStruct;

	if (huart->Instance == USART1) {
		/* Peripheral clock enable */
		__HAL_RCC_USART_CLK_ENABLE();

		/**USART1 GPIO Configuration
		PA9/AF0     ------> USART1_TX
		PA8/AF0     ------> USART1_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_8;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}

/************************ HT MICRON SEMICONDUCTORS S.A - uart.c *****END OF FILE****/

