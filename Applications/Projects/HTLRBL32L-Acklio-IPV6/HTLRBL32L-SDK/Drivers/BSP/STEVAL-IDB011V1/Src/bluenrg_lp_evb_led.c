/**
  ******************************************************************************
  * @file    bluenrg_lp_evb_ll_led.c
  * @author  RF Application Team
  * @brief   his file provides set of firmware functions to manage LEDs
  *          available on BlueNRGLP-EVB Kit from STMicroelectronics.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lp_evb_led.h"

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup BSP_BLUENRGLP_LED BSP BlueNRG-LP LED
  * @{
  */
    
/** @addtogroup RCC_LL_Private_Macros
  * @{
  */

#if BSP_LED_INVERTED_LOGIC
#define LED_ON(port,pin) LL_GPIO_ResetOutputPin(port, pin)
#define LED_OFF(port,pin) LL_GPIO_SetOutputPin(port, pin)
#else
#define LED_ON(port,pin) LL_GPIO_SetOutputPin(port, pin)
#define LED_OFF(port,pin) LL_GPIO_ResetOutputPin(port, pin)
#endif 

/**
  * @}
  */
       

/** @defgroup BSP_BLUENRGLP_LED_Exported_Functions Exported Functions
  * @{
  */ 


/**
  * @brief  Configures LED GPIO.
  * @param  Led: LED to be configured. 
  *          This parameter can be one of the following values:
  *            @arg BSP_LED1
  *            @arg BSP_LED2
  *            @arg BSP_LED3
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  /* Configure the LED pin and turn off it */
  if(Led == BSP_LED1) {
    BSP_LED1_GPIO_CLK_ENABLE();
    LED_OFF(BSP_LED1_GPIO_PORT, BSP_LED1_PIN);

    LL_GPIO_SetPinMode(BSP_LED1_GPIO_PORT, BSP_LED1_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(BSP_LED1_GPIO_PORT, BSP_LED1_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(BSP_LED1_GPIO_PORT, BSP_LED1_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(BSP_LED1_GPIO_PORT, BSP_LED1_PIN, LL_GPIO_PULL_UP);
  }
  else if(Led == BSP_LED2) {
    BSP_LED2_GPIO_CLK_ENABLE();
    LED_OFF(BSP_LED2_GPIO_PORT, BSP_LED2_PIN);

    LL_GPIO_SetPinMode(BSP_LED2_GPIO_PORT, BSP_LED2_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(BSP_LED2_GPIO_PORT, BSP_LED2_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(BSP_LED2_GPIO_PORT, BSP_LED2_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(BSP_LED2_GPIO_PORT, BSP_LED2_PIN, LL_GPIO_PULL_UP);
  }
  else if(Led == BSP_LED3) {
    BSP_LED3_GPIO_CLK_ENABLE();
    LED_OFF(BSP_LED3_GPIO_PORT, BSP_LED3_PIN);

    LL_GPIO_SetPinMode(BSP_LED3_GPIO_PORT, BSP_LED3_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinSpeed(BSP_LED3_GPIO_PORT, BSP_LED3_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(BSP_LED3_GPIO_PORT, BSP_LED3_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(BSP_LED3_GPIO_PORT, BSP_LED3_PIN, LL_GPIO_PULL_UP);
  }
}


/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be de-init. 
  *   This parameter can be one of the following values:
  *     @arg  BSP_LED1
  *     @arg  BSP_LED2
  *     @arg  BSP_LED3
  * @note Led DeInit does not disable the GPIO clock
  * @retval None
  */
void BSP_LED_DeInit(Led_TypeDef Led)
{
  /* Turn off the LED pin and deconfigure it */
  if(Led == BSP_LED1) {
    LED_OFF(BSP_LED1_GPIO_PORT, BSP_LED1_PIN);
    
    LL_GPIO_SetPinMode(BSP_LED1_GPIO_PORT, BSP_LED1_PIN, LL_GPIO_MODE_ANALOG);
    LL_GPIO_SetPinSpeed(BSP_LED1_GPIO_PORT, BSP_LED1_PIN, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetPinOutputType(BSP_LED1_GPIO_PORT, BSP_LED1_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinPull(BSP_LED1_GPIO_PORT, BSP_LED1_PIN, LL_GPIO_PULL_NO);
  }
  else if(Led == BSP_LED2) {
    LED_OFF(BSP_LED2_GPIO_PORT, BSP_LED2_PIN);
    
    LL_GPIO_SetPinMode(BSP_LED2_GPIO_PORT, BSP_LED2_PIN, LL_GPIO_MODE_ANALOG);
    LL_GPIO_SetPinSpeed(BSP_LED2_GPIO_PORT, BSP_LED2_PIN, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetPinOutputType(BSP_LED2_GPIO_PORT, BSP_LED2_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinPull(BSP_LED2_GPIO_PORT, BSP_LED2_PIN, LL_GPIO_PULL_NO);
  }
  else if(Led == BSP_LED3) {
    LED_OFF(BSP_LED3_GPIO_PORT, BSP_LED3_PIN);
    
    LL_GPIO_SetPinMode(BSP_LED3_GPIO_PORT, BSP_LED3_PIN, LL_GPIO_MODE_ANALOG);
    LL_GPIO_SetPinSpeed(BSP_LED3_GPIO_PORT, BSP_LED3_PIN, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetPinOutputType(BSP_LED3_GPIO_PORT, BSP_LED3_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinPull(BSP_LED3_GPIO_PORT, BSP_LED3_PIN, LL_GPIO_PULL_NO);

  }
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg BSP_LED1
  *     @arg BSP_LED2
  *     @arg BSP_LED3
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
  if(Led == BSP_LED1) {
    LED_ON(BSP_LED1_GPIO_PORT, BSP_LED1_PIN);
  }
  else if(Led == BSP_LED2) {
    LED_ON(BSP_LED2_GPIO_PORT, BSP_LED2_PIN);
  }
  else if(Led == BSP_LED3) {
    LED_ON(BSP_LED3_GPIO_PORT, BSP_LED3_PIN);
  }
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg BSP_LED1
  *     @arg BSP_LED2
  *     @arg BSP_LED3
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  if(Led == BSP_LED1) {
    LED_OFF(BSP_LED1_GPIO_PORT, BSP_LED1_PIN);
  }
  else if(Led == BSP_LED2) {
    LED_OFF(BSP_LED2_GPIO_PORT, BSP_LED2_PIN);
  }
  else if(Led == BSP_LED3) {
    LED_OFF(BSP_LED3_GPIO_PORT, BSP_LED3_PIN);
  }
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg BSP_LED1
  *     @arg BSP_LED2
  *     @arg BSP_LED3
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  if(Led == BSP_LED1) {
    LL_GPIO_TogglePin(BSP_LED1_GPIO_PORT, BSP_LED1_PIN);
  }
  else if(Led == BSP_LED2) {
    LL_GPIO_TogglePin(BSP_LED2_GPIO_PORT, BSP_LED2_PIN);
  }
  else if(Led == BSP_LED3) {
    LL_GPIO_TogglePin(BSP_LED3_GPIO_PORT, BSP_LED3_PIN);
  }
}

/**
  * @}
  */ 


/**
  * @}
  */  
    
/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
