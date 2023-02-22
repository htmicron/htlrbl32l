/**
  ******************************************************************************
  * @file    bluenrg_lp_evb_ll_digmic.c
  * @author  RF Application Team
  * @brief   his file provides set of firmware functions to initialize the
  *          PDM pins connected to the digital microphone MP34DT05-A.
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
#include "bluenrg_lp_evb_mic.h"

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup BSP_BLUENRGLP_MIC BSP BlueNRG-LP Microphone pins
  * @{
  */ 


/** @defgroup BSP_BLUENRGLP_MIC_Exported_Functions Exported Functions
  * @{
  */ 


/**
  * @brief  Configures the PDM interface used to interface the digital microphone MP34DT05-A.
  * @param  None
  * @retval None
  */
void BSP_DIGMIC_Init(void)
{
  /* Initialize the GPIOs associated to the PDM port */
  BSP_PDM_CLK_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_PDM_CLK_GPIO_PORT, BSP_PDM_CLK_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_PDM_CLK_GPIO_PORT, BSP_PDM_CLK_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_PDM_CLK_GPIO_PORT, BSP_PDM_CLK_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_PDM_CLK_GPIO_PORT, BSP_PDM_CLK_PIN, LL_GPIO_PULL_NO);
  BSP_PDM_CLK_GPIO_AF();

  BSP_PDM_DATA_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_PDM_DATA_GPIO_PORT, BSP_PDM_DATA_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_PDM_DATA_GPIO_PORT, BSP_PDM_DATA_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_PDM_DATA_GPIO_PORT, BSP_PDM_DATA_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_PDM_DATA_GPIO_PORT, BSP_PDM_DATA_PIN, LL_GPIO_PULL_NO);
  BSP_PDM_DATA_GPIO_AF();

}


/**
  * @brief  Deinitialize the PDM interface used to interface the digital microphone MP34DT05-A.
  * @param  None
  * @retval None
  */
void BSP_DIGMIC_DeInit(void)
{
  /* Reset the GPIOs associated to the PDM port */
  LL_GPIO_SetPinMode(BSP_PDM_CLK_GPIO_PORT, BSP_PDM_CLK_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_PDM_CLK_GPIO_PORT, BSP_PDM_CLK_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_PDM_CLK_GPIO_PORT, BSP_PDM_CLK_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_PDM_CLK_GPIO_PORT, BSP_PDM_CLK_PIN, LL_GPIO_PULL_NO);

  LL_GPIO_SetPinMode(BSP_PDM_DATA_GPIO_PORT, BSP_PDM_DATA_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_PDM_DATA_GPIO_PORT, BSP_PDM_DATA_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_PDM_DATA_GPIO_PORT, BSP_PDM_DATA_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_PDM_DATA_GPIO_PORT, BSP_PDM_DATA_PIN, LL_GPIO_PULL_NO);
}



/**
  * @brief  Configures the Analog microphone interface used to interface the analog microphone.
  * @param  None
  * @retval None
  */
void BSP_ANAMIC_Init(void)
{
  /* Initialize the GPIOs associated to the analog microphone port */
  BSP_ANAMIC_VIN_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_ANAMIC_VIN_GPIO_PORT, BSP_ANAMIC_VIN_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_ANAMIC_VIN_GPIO_PORT, BSP_ANAMIC_VIN_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_ANAMIC_VIN_GPIO_PORT, BSP_ANAMIC_VIN_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_ANAMIC_VIN_GPIO_PORT, BSP_ANAMIC_VIN_PIN, LL_GPIO_PULL_NO);

  BSP_ANAMIC_VBIAS_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_ANAMIC_VBIAS_GPIO_PORT, BSP_ANAMIC_VBIAS_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_ANAMIC_VBIAS_GPIO_PORT, BSP_ANAMIC_VBIAS_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_ANAMIC_VBIAS_GPIO_PORT, BSP_ANAMIC_VBIAS_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_ANAMIC_VBIAS_GPIO_PORT, BSP_ANAMIC_VBIAS_PIN, LL_GPIO_PULL_NO);

}


/**
  * @brief  Deinitialize the Analog microphone interface used to interface the analog microphone.
  * @param  None
  * @retval None
  */
void BSP_ANAMIC_DeInit(void)
{
  /* Reset the GPIOs associated to the analog microphone port */
  LL_GPIO_SetPinMode(BSP_ANAMIC_VIN_GPIO_PORT, BSP_ANAMIC_VIN_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_ANAMIC_VIN_GPIO_PORT, BSP_ANAMIC_VIN_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_ANAMIC_VIN_GPIO_PORT, BSP_ANAMIC_VIN_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_ANAMIC_VIN_GPIO_PORT, BSP_ANAMIC_VIN_PIN, LL_GPIO_PULL_NO);

  LL_GPIO_SetPinMode(BSP_ANAMIC_VBIAS_GPIO_PORT, BSP_ANAMIC_VBIAS_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_ANAMIC_VBIAS_GPIO_PORT, BSP_ANAMIC_VBIAS_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_ANAMIC_VBIAS_GPIO_PORT, BSP_ANAMIC_VBIAS_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_ANAMIC_VBIAS_GPIO_PORT, BSP_ANAMIC_VBIAS_PIN, LL_GPIO_PULL_NO);
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
