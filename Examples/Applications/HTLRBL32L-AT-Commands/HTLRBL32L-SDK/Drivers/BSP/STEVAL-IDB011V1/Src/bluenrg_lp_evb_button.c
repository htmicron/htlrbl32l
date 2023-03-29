/**
******************************************************************************
* @file    bluenrg_lp_evb_ll_button.c
* @author  RF Application Team
* @brief   This file provides set of firmware functions to manage push-button
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
#include "bluenrg_lp_evb_button.h"

/** @addtogroup BSP
* @{
*/

/** @defgroup BSP_BLUENRGLP_BUTTON BSP BlueNRG-LP button
* @{
*/


/** @defgroup BSP_BLUENRGLP_BUTTON_Exported_Functions Exported Functions
* @{
*/

/**
* @brief  Configures Button GPIO and EXTI Line.
* @param  Button: Specifies the Button to be configured.
*   This parameter can be one of following parameters:
*     @arg BSP_PUSH1
*     @arg BSP_PUSH2
* @param  ButtonMode: Specifies Button mode.
*   This parameter can be one of following parameters:   
*     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
*     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
*                            generation capability  
* @retval None
*/
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  /* Configure the button */
  if(Button == BSP_PUSH1) {
    BSP_PUSH1_GPIO_CLK_ENABLE();
    LL_GPIO_SetPinMode(BSP_PUSH1_GPIO_PORT, BSP_PUSH1_PIN, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(BSP_PUSH1_GPIO_PORT, BSP_PUSH1_PIN, LL_GPIO_PULL_NO);
  }
  else if(Button == BSP_PUSH2) {
    BSP_PUSH2_GPIO_CLK_ENABLE();
    LL_GPIO_SetPinMode(BSP_PUSH2_GPIO_PORT, BSP_PUSH2_PIN, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(BSP_PUSH2_GPIO_PORT, BSP_PUSH2_PIN, LL_GPIO_PULL_NO);
  }
  
  if(ButtonMode == BUTTON_MODE_EXTI) {
    
    /* Enable System Config clock */
    LL_APB0_EnableClock(LL_APB0_PERIPH_SYSCFG);

    if(Button == BSP_PUSH1) {
      LL_EXTI_SetTrigger(BSP_PUSH1_EXTI_LINE_TRIGGER, BSP_PUSH1_EXTI_LINE);
      LL_EXTI_ClearInterrupt(BSP_PUSH1_EXTI_LINE);
      LL_EXTI_EnableIT(BSP_PUSH1_EXTI_LINE);

      /* Enable and set Button EXTI Interrupt to the lowest priority */
      NVIC_SetPriority(BSP_PUSH1_EXTI_IRQn, IRQ_LOW_PRIORITY);
      NVIC_EnableIRQ(BSP_PUSH1_EXTI_IRQn);
    }
    else if(Button == BSP_PUSH2) {
      LL_EXTI_SetTrigger(BSP_PUSH2_EXTI_LINE_TRIGGER, BSP_PUSH2_EXTI_LINE);
      LL_EXTI_ClearInterrupt(BSP_PUSH2_EXTI_LINE);
      LL_EXTI_EnableIT(BSP_PUSH2_EXTI_LINE);

      /* Enable and set Button EXTI Interrupt to the lowest priority */
      NVIC_SetPriority(BSP_PUSH2_EXTI_IRQn, IRQ_LOW_PRIORITY);
      NVIC_EnableIRQ(BSP_PUSH2_EXTI_IRQn);
    }
  }
}


/**
* @brief  Push Button DeInit.
* @param  Button: Button to be configured
*   This parameter can be one of following parameters:
*     @arg BSP_PUSH1
*     @arg BSP_PUSH2
* @note PB DeInit does not disable the GPIO clock
* @retval None
*/
void BSP_PB_DeInit(Button_TypeDef Button)
{
  /* Deinitialization of the button */
  if(Button == BSP_PUSH1) {
    LL_EXTI_DisableIT(BSP_PUSH1_EXTI_LINE);
    LL_EXTI_ClearInterrupt(BSP_PUSH1_EXTI_LINE);
    LL_GPIO_SetPinMode(BSP_PUSH1_GPIO_PORT, BSP_PUSH1_PIN, LL_GPIO_MODE_ANALOG);
  }
  else if(Button == BSP_PUSH2) {
    LL_EXTI_DisableIT(BSP_PUSH2_EXTI_LINE);
    LL_EXTI_ClearInterrupt(BSP_PUSH2_EXTI_LINE);
    LL_GPIO_SetPinMode(BSP_PUSH2_GPIO_PORT, BSP_PUSH2_PIN, LL_GPIO_MODE_ANALOG);
  }
}


/**
* @brief  Returns the selected Button state.
* @param  Button: Specifies the Button to be checked.
*   This parameter can be one of following parameters:
*     @arg BSP_PUSH1
*     @arg BSP_PUSH2
* @retval The Button GPIO pin value.
*/
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  uint32_t tmp = 0;
  
  if(Button == BSP_PUSH1) {
    tmp = LL_GPIO_IsInputPinSet(BSP_PUSH1_GPIO_PORT, BSP_PUSH1_PIN);
  }
  else if(Button == BSP_PUSH2) {
    tmp =  LL_GPIO_IsInputPinSet(BSP_PUSH2_GPIO_PORT, BSP_PUSH2_PIN);
  }
  return tmp;
}


/**
* @brief  Returns the pending bit associated to the button.
* @param  Button: Specifies the Button to be checked.
*   This parameter can be one of following parameters:
*     @arg BSP_PUSH1
*     @arg BSP_PUSH2
* @retval The pending bit associated to the button.
*/
uint32_t BSP_PB_GetITPendingBit(Button_TypeDef Button)
{
  uint32_t tmp = 0;
  
  if(Button == BSP_PUSH1) {
    tmp = LL_EXTI_IsInterruptPending(BSP_PUSH1_EXTI_LINE);
  }
  else if(Button == BSP_PUSH2) {
    tmp = LL_EXTI_IsInterruptPending(BSP_PUSH2_EXTI_LINE);
  }
  return tmp;
}


/**
* @brief  Clear the pending bit associated to the button.
* @param  Button: Specifies the Button to be checked.
*   This parameter can be one of following parameters:
*     @arg BSP_PUSH1
*     @arg BSP_PUSH2
* @retval The Button GPIO pin value.
*/
void BSP_PB_ClearITPendingBit(Button_TypeDef Button)
{
  if(Button == BSP_PUSH1) {
    LL_EXTI_ClearInterrupt(BSP_PUSH1_EXTI_LINE);
  }
  else if(Button == BSP_PUSH2) {
    LL_EXTI_ClearInterrupt(BSP_PUSH2_EXTI_LINE);
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
