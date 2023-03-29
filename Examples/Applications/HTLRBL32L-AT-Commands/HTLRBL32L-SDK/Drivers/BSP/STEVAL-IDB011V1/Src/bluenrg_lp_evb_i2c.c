/**
  ******************************************************************************
  * @file    bluenrg_lp_evb_ll_i2c.c
  * @author  RF Application Team
  * @brief   his file provides set of firmware functions the I2C communication
  *          with the LPS22HH pressure sensor available on BlueNRGLP-EVB Kit.
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
#include "bluenrg_lp_evb_i2c.h"
#include "rf_driver_ll_i2c.h"

#include "lps22hh_reg.h"


/** @addtogroup BSP
  * @{
  */ 

/** @defgroup BSP_BLUENRGLP_I2C BSP BlueNRG-LP I2C
  * @{
  */ 


/** @defgroup BSP_BLUENRGLP_I2C_Exported_Functions Exported Functions
  * @{
  */ 


/**
  * @brief  Configures the I2C interface used for the sensor LPS22HH.
  * @param  None
  * @retval None
  */
void BSP_I2C_Init(void)
{
  /* Initialize the GPIOs associated to the I2C port */
  BSP_I2C_DATA_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_I2C_DATA_GPIO_PORT, BSP_I2C_DATA_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_I2C_DATA_GPIO_PORT, BSP_I2C_DATA_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_I2C_DATA_GPIO_PORT, BSP_I2C_DATA_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_I2C_DATA_GPIO_PORT, BSP_I2C_DATA_PIN, BSP_I2C_DATA_GPIO_PULL);
  BSP_I2C_DATA_GPIO_AF();

  BSP_I2C_CLK_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_I2C_CLK_GPIO_PORT, BSP_I2C_CLK_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_I2C_CLK_GPIO_PORT, BSP_I2C_CLK_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_I2C_CLK_GPIO_PORT, BSP_I2C_CLK_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_I2C_CLK_GPIO_PORT, BSP_I2C_CLK_PIN, BSP_I2C_CLK_GPIO_PULL);
  BSP_I2C_CLK_GPIO_AF();

  /* Initialize the I2C clock */
  BSP_I2C_CLK_ENABLE();

  LL_I2C_Disable(BSP_I2C);
  
  /* Configure the SDA setup, hold time and the SCL high, low period
   * For Fast-mode 400 kHz, PRESC | 0h | SCLDEL | SDADEL | SCLH | SCLL
   *                          1h  | 0h |    3h  |   2h   |  03h |  09h
   */
  LL_I2C_SetTiming(BSP_I2C, 0x10320309);

  /* Enable Clock stretching */
  LL_I2C_EnableClockStretching(BSP_I2C);

  /* Enable Peripheral in I2C mode */
  LL_I2C_SetMode(BSP_I2C, LL_I2C_MODE_I2C);

  /* Enable the I2C peripheral */
  LL_I2C_Enable(BSP_I2C);

  /* Enable I2C transfer complete/error interrupts:
   *  - Enable Receive Interrupt
   *  - Enable Not acknowledge received interrupt
   *  - Enable Error interrupts
   *  - Enable Stop interrupt
   */
//  LL_I2C_EnableIT_TX(BSP_I2C);
//  LL_I2C_EnableIT_RX(BSP_I2C);
//  LL_I2C_EnableIT_TC(BSP_I2C);
//  LL_I2C_EnableIT_NACK(BSP_I2C);
//  LL_I2C_EnableIT_ERR(BSP_I2C);
//  LL_I2C_EnableIT_STOP(BSP_I2C);
}


/**
  * @brief  Deinitialize the I2C interface used for the sensor LPS22HH.
  * @param  None
  * @retval None
  */
void BSP_I2C_DeInit(void)
{
  /* Disable I2C transfer complete/error interrupts */
  LL_I2C_ClearFlag_TXE(BSP_I2C);
  LL_I2C_ClearFlag_NACK(BSP_I2C);
  LL_I2C_ClearFlag_STOP(BSP_I2C);

  LL_I2C_DisableIT_TX(BSP_I2C);
  LL_I2C_DisableIT_RX(BSP_I2C);
  LL_I2C_DisableIT_TC(BSP_I2C);
  LL_I2C_DisableIT_NACK(BSP_I2C);
  LL_I2C_DisableIT_ERR(BSP_I2C);
  LL_I2C_DisableIT_STOP(BSP_I2C);

  /* Disable the I2C peripheral */
  LL_I2C_Disable(BSP_I2C);

  /* Disable the I2C clock */
  BSP_I2C_CLK_DISABLE();

  /* Reset the I2C pins */
  LL_GPIO_SetPinMode(BSP_LED1_GPIO_PORT, BSP_I2C_DATA_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_LED1_GPIO_PORT, BSP_I2C_DATA_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_LED1_GPIO_PORT, BSP_I2C_DATA_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_LED1_GPIO_PORT, BSP_I2C_DATA_PIN, LL_GPIO_PULL_NO);

  LL_GPIO_SetPinMode(BSP_LED2_GPIO_PORT, BSP_I2C_CLK_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_LED2_GPIO_PORT, BSP_I2C_CLK_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_LED2_GPIO_PORT, BSP_I2C_CLK_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_LED2_GPIO_PORT, BSP_I2C_CLK_PIN, LL_GPIO_PULL_NO);
}


/**
  * @brief  I2C write function used for the LPS22HH pressure sensor.
  * @param  handle: handle. 
  * @param  Reg: Reg. 
  * @param  pBuff: pBuff. 
  * @param  nBuffSize: nBuffSize. 
  * @retval None
  */
int32_t BSP_I2C_Write(void *handle, uint8_t Reg, uint8_t *pBuff, uint16_t nBuffSize)
{
  /* Initialize the handle transfer */
  LL_I2C_HandleTransfer(BSP_I2C, LPS22HH_I2C_ADD_L, LL_I2C_ADDRSLAVE_7BIT, nBuffSize+1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

  /* Wait for the TX Empty flag */
  while(LL_I2C_IsActiveFlag_TXE(BSP_I2C) == 0); /* TODO: add a SW timeout */
  
  /* Get the received byte from the RX FIFO */
  LL_I2C_TransmitData8(BSP_I2C, (Reg | 0x80)); // |0x80 auto-increment
  
  /* Wait for the TX Empty flag */
  while(LL_I2C_IsActiveFlag_TXE(BSP_I2C) == 0); /* TODO: add a SW timeout */
  
  for(uint16_t i = 0; i < nBuffSize; i++) {
    /* Wait for the TX flag */
    while(LL_I2C_IsActiveFlag_TXIS(BSP_I2C) == 0); /* TODO: add a SW timeout */

    /* Fill the TX FIFO with data */
    LL_I2C_TransmitData8(BSP_I2C, pBuff[i]);
  }

  /* Wait for the Transfer Complete flag */
//  while(LL_I2C_IsActiveFlag_TC(BSP_I2C) == 0);

  return 0;
}


/**
  * @brief  I2C read function used for the LPS22HH pressure sensor.
  * @param  handle: handle. 
  * @param  Reg: Reg. 
  * @param  pBuff: pBuff. 
  * @param  nBuffSize: nBuffSize. 
  * @retval None
  */
int32_t BSP_I2C_Read(void *handle, uint8_t Reg, uint8_t *pBuff, uint16_t nBuffSize)
{
  /* Initialize the handle transfer */
  LL_I2C_HandleTransfer(BSP_I2C, LPS22HH_I2C_ADD_L, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
  
  /* Wait for the TX Empty flag */
  while(LL_I2C_IsActiveFlag_TXE(BSP_I2C) == 0); /* TODO: add a SW timeout */
  
  /* Get the received byte from the RX FIFO */
  LL_I2C_TransmitData8(BSP_I2C, (Reg | 0x80)); // |0x80 auto-increment
  
  /* Wait for the TX Empty flag */
  while(LL_I2C_IsActiveFlag_TXE(BSP_I2C) == 0); /* TODO: add a SW timeout */
  
  /* Wait for the Transfer Complete flag */
//  while(LL_I2C_IsActiveFlag_TC(BSP_I2C) == 0);  
  
  /* Initialize the handle transfer */
  LL_I2C_HandleTransfer(BSP_I2C, LPS22HH_I2C_ADD_L, LL_I2C_ADDRSLAVE_7BIT, nBuffSize, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

  for(uint16_t i = 0; i < nBuffSize; i++) {
    /* Wait for the RX Not Empty flag */
    while(LL_I2C_IsActiveFlag_RXNE(BSP_I2C) == 0); /* TODO: add a SW timeout */

    /* Get the received byte from the RX FIFO */
    pBuff[i] = LL_I2C_ReceiveData8(BSP_I2C);
  }

  /* Wait for the Transfer Complete flag */
//    while(LL_I2C_IsActiveFlag_TC(BSP_I2C) == 0);

  return 0;
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
