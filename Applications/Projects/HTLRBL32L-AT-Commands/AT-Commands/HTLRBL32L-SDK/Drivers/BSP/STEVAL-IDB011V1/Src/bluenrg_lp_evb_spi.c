/**
  ******************************************************************************
  * @file    bluenrg_lp_evb_ll_spi.c
  * @author  RF Application Team
  * @brief   his file provides set of firmware functions the SPI communication
  *          with the inertial module LSM6DS0 available on BlueNRGLP-EVB Kit.
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
#include "bluenrg_lp_evb_spi.h"
#include "rf_driver_ll_spi.h"

#include "lsm6dsox_reg.h"


/** @addtogroup BSP
  * @{
  */ 

/** @defgroup BSP_BLUENRGLP_SPI BSP BlueNRG-LP SPI
  * @{
  */ 


/** @defgroup BSP_BLUENRGLP_SPI_Exported_Functions Exported Functions
  * @{
  */ 


/**
  * @brief  Configures the SPI interface used for the inertial module sensor LSM6DSO.
  * @param  None
  * @retval None
  */
void BSP_SPI_Init(void)
{
  /* Initialize the GPIOs associated to the SPI port */
  BSP_SPI_MISO_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, LL_GPIO_PULL_NO);
  BSP_SPI_MISO_GPIO_AF();

  BSP_SPI_MOSI_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, LL_GPIO_PULL_DOWN);
  BSP_SPI_MOSI_GPIO_AF();

  BSP_SPI_SCK_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, LL_GPIO_PULL_DOWN);
  BSP_SPI_SCK_GPIO_AF();

  BSP_SPI_CS_SENSOR1_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinSpeed(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN, LL_GPIO_PULL_UP);
  LL_GPIO_SetOutputPin(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN);

  /* Initialize the SPI clock */
  BSP_SPI_CLK_ENABLE();

  /* SPI parameter configuration*/
  LL_SPI_SetMode(BSP_SPI, LL_SPI_MODE_MASTER);
  LL_SPI_SetStandard(BSP_SPI, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_SetTransferDirection(BSP_SPI, LL_SPI_FULL_DUPLEX);
  LL_SPI_SetClockPolarity(BSP_SPI, BSP_SPI_CLK_POLARITY);
  LL_SPI_SetClockPhase(BSP_SPI, BSP_SPI_CLK_PHASE);
  LL_SPI_SetNSSMode(BSP_SPI, LL_SPI_NSS_SOFT);
  LL_SPI_SetDataWidth(BSP_SPI, LL_SPI_DATAWIDTH_8BIT);
  LL_SPI_SetTransferBitOrder(BSP_SPI, LL_SPI_MSB_FIRST);
  LL_SPI_DisableCRC(BSP_SPI);
  LL_SPI_DisableNSSPulseMgt(BSP_SPI);
  LL_SPI_SetBaudRatePrescaler(BSP_SPI, LL_SPI_BAUDRATEPRESCALER_DIV4); /* 8 MHz */

  /* Configure the SPI RX FIFO threshold to 1 byte */
  LL_SPI_SetRxFIFOThreshold(BSP_SPI, LL_SPI_RX_FIFO_TH_QUARTER);

  /* Enable the SPI */
  LL_SPI_Enable(BSP_SPI);
  
}


/**
  * @brief  Deinitialize the SPI interface used for the inertial module LSM6DSO.
  * @param  None
  * @retval None
  */
void BSP_SPI_DeInit(void)
{
  /* Disable the SPI interrupts */
  LL_SPI_DisableIT_TXE(BSP_SPI);
  LL_SPI_DisableIT_RXNE(BSP_SPI);

  /* Disable the SPI peripheral */
  LL_SPI_Disable(BSP_SPI);

  /* Disable the SPI clock */
  BSP_SPI_CLK_DISABLE();

  /* Reset the SPI pins */
  LL_GPIO_SetPinMode(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, LL_GPIO_PULL_NO);

  LL_GPIO_SetPinMode(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, LL_GPIO_PULL_NO);

  LL_GPIO_SetPinMode(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, LL_GPIO_PULL_NO);

  LL_GPIO_SetPinMode(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN, LL_GPIO_PULL_NO);
}


/**
  * @brief  SPI write function used for the inertial module LSM6DSO.
  * @param  handle: handle. 
  * @param  Reg: Reg. 
  * @param  pBuff: pBuff. 
  * @param  nBuffSize: nBuffSize. 
  * @retval None
  */
int32_t BSP_SPI_Write(void *handle, uint8_t Reg, uint8_t *pBuff, uint16_t nBuffSize)
{
  /* Open the SPI communication by drive low the CS pin */
  LL_GPIO_ResetOutputPin(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN);
  
  while(LL_SPI_IsActiveFlag_TXE(BSP_SPI) == 0); /* TODO: add a SW timeout */
  
  /* Send the register address */
  LL_SPI_TransmitData8(BSP_SPI, Reg);
  
  /* Wait for the TX flag */
  while(LL_SPI_IsActiveFlag_RXNE(BSP_SPI) == 0); /* TODO: add a SW timeout */
  
  /* Read the available data */
  LL_SPI_ReceiveData8(BSP_SPI);
  
  for(uint16_t i = 0; i < nBuffSize; i++) {
    /* Wait for the TX flag */
    while(LL_SPI_IsActiveFlag_TXE(BSP_SPI) == 0); /* TODO: add a SW timeout */
    
    /* Send the data available */
    LL_SPI_TransmitData8(BSP_SPI, pBuff[i]);
    
    /* Wait for the TX flag */
    while(LL_SPI_IsActiveFlag_RXNE(BSP_SPI) == 0); /* TODO: add a SW timeout */
    
    /* Read the available data */
    LL_SPI_ReceiveData8(BSP_SPI);
  }
  
  /* Wait for the Busy flag */
  while(LL_SPI_IsActiveFlag_BSY(BSP_SPI) == 1);
  
  /* Close the SPI communication by drive high the CS pin */
  LL_GPIO_SetOutputPin(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN);
  
  return 0;
}


/**
  * @brief  SPI read function used for the inertial module LSM6DSO.
  * @param  handle: handle. 
  * @param  Reg: Reg. 
  * @param  pBuff: pBuff. 
  * @param  nBuffSize: nBuffSize. 
  * @retval None
  */
int32_t BSP_SPI_Read(void *handle, uint8_t Reg, uint8_t *pBuff, uint16_t nBuffSize)
{
  /* Open the SPI communication by drive low the CS pin */
  LL_GPIO_ResetOutputPin(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN);
  
  while(LL_SPI_IsActiveFlag_TXE(BSP_SPI) == 0); /* TODO: add a SW timeout */
  
  LL_SPI_TransmitData8(BSP_SPI, (Reg | 0x80) );
  
  /* Wait for the TX flag */
  while(LL_SPI_IsActiveFlag_RXNE(BSP_SPI) == 0); /* TODO: add a SW timeout */
  
  /* Read the available data */
  LL_SPI_ReceiveData8(BSP_SPI);
  
  for(uint16_t i = 0; i < nBuffSize; i++) {
    /* Wait for the TX flag */
    while(LL_SPI_IsActiveFlag_TXE(BSP_SPI) == 0); /* TODO: add a SW timeout */
    
    /* Send the data available */
    LL_SPI_TransmitData8(BSP_SPI, 0xFF);
    
    /* Wait for the TX flag */
    while(LL_SPI_IsActiveFlag_RXNE(BSP_SPI) == 0); /* TODO: add a SW timeout */
    
    /* Read the available data */
    pBuff[i] = LL_SPI_ReceiveData8(BSP_SPI);
  }
  
  /* Wait for the Busy flag */
  while(LL_SPI_IsActiveFlag_BSY(BSP_SPI) == 1);
  
  /* Close the SPI communication by drive high the CS pin */
  LL_GPIO_SetOutputPin(BSP_SPI_CS_SENSOR1_GPIO_PORT, BSP_SPI_CS_SENSOR1_PIN);
  
  return 0;
}


/**
* @brief  Configures GPIO connected to the INT1 of the inertial sensor as Input IRQ.
* @param  None
* @retval None
*/
void BSP_SPI_GpioInt_Init(void)
{
  BSP_SENSOR1_INT_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_SENSOR1_INT_GPIO_PORT, BSP_SENSOR1_INT_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(BSP_SENSOR1_INT_GPIO_PORT, BSP_SENSOR1_INT_PIN, LL_GPIO_PULL_NO);
  
  /* Enable System Config clock */
  LL_APB0_EnableClock(LL_APB0_PERIPH_SYSCFG);
  
  LL_EXTI_SetTrigger(BSP_SENSOR1_INT_EXTI_LINE_TRIGGER, BSP_SENSOR1_INT_EXTI_LINE);
  LL_EXTI_ClearInterrupt(BSP_SENSOR1_INT_EXTI_LINE);
  LL_EXTI_EnableIT(BSP_SENSOR1_INT_EXTI_LINE);
  
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_SetPriority(BSP_SENSOR1_INT_EXTI_IRQn, IRQ_LOW_PRIORITY);
  NVIC_EnableIRQ(BSP_SENSOR1_INT_EXTI_IRQn);
  
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
