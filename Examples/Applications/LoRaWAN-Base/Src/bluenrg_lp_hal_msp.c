/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/bluenrg_lp_hal_msp.c
  * @author  RF Application Team
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics. 
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
#include "main.h"
#include "peripheral_init.h"
#include "radio.h"
#include "rf_driver_ll_pwr.h"
#include "rf_driver_hal_rng.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
 
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng);

/* External functions --------------------------------------------------------*/

void MX_GPIO_LP_Init(void) {
	//	LL_PWR_EnablePDA(LL_PWR_PUPD_IO0);
	//	LL_PWR_EnablePDA(LL_PWR_PUPD_IO1);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO2);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO3);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO4);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO5);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO6);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO7);
		LL_PWR_EnablePUA(LL_PWR_PUPD_IO8);
		LL_PWR_EnablePUA(LL_PWR_PUPD_IO9);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO10);
		LL_PWR_EnablePUA(LL_PWR_PUPD_IO11);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO12);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO13);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO14);
		LL_PWR_EnablePDA(LL_PWR_PUPD_IO15);

		LL_PWR_EnablePDB(LL_PWR_PUPD_IO0);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO1);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO2);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO3);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO4);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO5);
	//	LL_PWR_EnablePUB(LL_PWR_PUPD_IO6);
	//	LL_PWR_EnablePUB(LL_PWR_PUPD_IO7);
		LL_PWR_EnablePUB(LL_PWR_PUPD_IO8);
		LL_PWR_EnablePUB(LL_PWR_PUPD_IO9);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO10);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO11);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO12);
		LL_PWR_EnablePDB(LL_PWR_PUPD_IO13);
		LL_PWR_EnablePUB(LL_PWR_PUPD_IO14);
		LL_PWR_EnablePUB(LL_PWR_PUPD_IO15);
}

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* System interrupt init*/
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn,0);
  __HAL_RCC_SYSCFG_CLK_ENABLE();

}

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(huart->Instance==USART1)
  {

    /* Peripheral clock enable */
    __HAL_RCC_USART_CLK_ENABLE();

  
    /**USART1 GPIO Configuration    
    PA9/AF0     ------> USART1_TX
    PA8/AF0     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  }

}

/**
* @brief USART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param husart: USART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART1)
  {
    __HAL_RCC_USART_FORCE_RESET();
    __HAL_RCC_USART_RELEASE_RESET();
    /* Peripheral clock disable */
    __HAL_RCC_USART_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
		PA9/AF0     ------> USART1_TX
    PA8/AF0     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_9);

  }

}
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(hspi->Instance==SPI1)
  {
    /* Peripheral clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
  
		//MISO
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		//SCLK
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN; //PULLDOWN
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//MOSI SIP
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN; //PULLDOWN
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  }	

}

/**
* @brief SPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
  if(hspi->Instance==SPI1)
  {
    /* Reset peripherals */
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();

    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PA13     ------> SPI1_SCK
    PA14     ------> SPI1_MISO
    PB14     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_13|GPIO_PIN_14);
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14);
  }

}

EXTI_HandleTypeDef HEXTI_InitStructure;

/**
  * @brief IRQ Handler Configuration Function
  * @param None
  * @retval None
  */
void IRQHandler_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  
  EXTI_ConfigTypeDef EXTI_Config_InitStructure;
  
  /* Enable GPIOC clock */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Configure PB.4 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  EXTI_Config_InitStructure.Line =    EXTI_LINE_PB4;
  EXTI_Config_InitStructure.Trigger = EXTI_TRIGGER_RISING_EDGE;
  EXTI_Config_InitStructure.Type =    EXTI_TYPE_EDGE;
   
  HAL_EXTI_SetConfigLine(&HEXTI_InitStructure, &EXTI_Config_InitStructure);
  HAL_EXTI_RegisterCallback(&HEXTI_InitStructure, HAL_EXTI_COMMON_CB_ID, (void(*) (uint32_t))RadioOnDioIrq);
  HAL_EXTI_Cmd(&HEXTI_InitStructure , ENABLE);
  
  HAL_EXTI_ClearPending(&HEXTI_InitStructure);
  
  /* Enable and set line 10 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(GPIOB_IRQn,2);
  HAL_NVIC_EnableIRQ(GPIOB_IRQn);
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	
	HAL_GPIO_WritePin(GPIOA, RADIO_NSS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, RADIO_NRST_Pin, GPIO_PIN_SET);
	
	
	/*Configure GPIO pins : PAPin PAPin PAPin */
	GPIO_InitStruct.Pin = RADIO_NRST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(RADIO_NRST_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = RADIO_NSS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(RADIO_NSS_Port, &GPIO_InitStruct);


	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = RADIO_BUSY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(RADIO_BUSY_Port, &GPIO_InitStruct);
	
	HAL_NVIC_EnableIRQ( GPIOB_IRQn);

	
	GPIO_InitStruct.Pin = RADIO_SWITCH_ENABLE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(RADIO_SWITCH_ENABLE_Port, &GPIO_InitStruct);


	GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_5|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
 
 
}

void MX_RNG_Init(RNG_HandleTypeDef *hrng)
{
	hrng->Instance = RNG;
		if (HAL_RNG_Init(hrng) != HAL_OK)
	{
			Error_Handler();
	}
}

void HAL_RNG_MspInit(RNG_HandleTypeDef* hrng)
{
  if(hrng->Instance==RNG)
  {
    /* Peripheral clock enable */
    __HAL_RCC_RNG_CLK_ENABLE();
  }
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
