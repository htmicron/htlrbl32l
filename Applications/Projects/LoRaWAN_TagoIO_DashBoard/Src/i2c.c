#include "i2c.h"
#include "main.h"
#include "lorawan_setup.h"

I2C_HandleTypeDef hi2c;	


int32_t MX_I2C2_Init(void) {

	hi2c.Instance = I2C2;
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
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c, 0) != HAL_OK)
		while(1);

	return BSP_ERROR_NONE;
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) {
	GPIO_InitTypeDef GPIO_InitStruct;

	if(hi2c->Instance == I2C2) {
		/* Peripheral clock enable */
		__HAL_RCC_GPIOB_CLK_ENABLE();

		/* SCL GPIO config */
		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF0_I2C2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF0_I2C2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2C2_CLK_ENABLE();
	}
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{

  if(hi2c->Instance==I2C2)
  {
    __HAL_RCC_I2C1_CLK_DISABLE();
		
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);
  }
}
