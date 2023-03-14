/**
 *
 * Copyright (c) 2021 HT Micron Semicondutors S.A.
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

#include "i2c.h"
#include "main.h"

I2C_HandleTypeDef hi2c;

int32_t MX_I2C2_Init(void) {
	/* (uint32_t)0x10320309 = I2C TIMING in Fast Mode                  */
	/* (uint32_t)0x00200204 = I2C TIMING in Fast Mode plus             */

	hi2c.Instance = I2C1;
	hi2c.Init.Timing = 0x10320309;
	hi2c.Init.OwnAddress1 = 0;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.OwnAddress2 = 0;
	hi2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c) != HAL_OK)
		while(1);

	/** Configure Analogue filter */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c, I2C_ANALOGFILTER_DISABLE) != HAL_OK)
		while(1);

	/** Configure Digital filter */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c, 2) != HAL_OK)
		while(1);

	return BSP_ERROR_NONE;
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) {
	GPIO_InitTypeDef GPIO_InitStruct;

	if(hi2c->Instance == I2C1) {
		/* Peripheral clock enable */
		__HAL_RCC_GPIOA_CLK_ENABLE();

		/* SCL GPIO config */
		GPIO_InitStruct.Pin = GPIO_PIN_0;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF0_I2C1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF0_I2C1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2C1_CLK_ENABLE();
	}
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c) {
	if(hi2c->Instance == I2C1) {
		/* Peripheral clock disable */
		__HAL_RCC_I2C1_CLK_DISABLE();

		/**I2Cx GPIO Configuration*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);
	}
}

int32_t BSP_I2C_MspDeInit(void) {
	HAL_I2C_MspDeInit(&hi2c);

	return BSP_ERROR_NONE;
}
