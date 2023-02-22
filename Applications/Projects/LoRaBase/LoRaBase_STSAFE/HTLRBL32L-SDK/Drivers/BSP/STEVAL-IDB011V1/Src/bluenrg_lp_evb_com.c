/**
  ******************************************************************************
  * @file    bluenrg_lp_evb_ll_com.c
  * @author  RF Application Team
  * @brief   his file provides set of firmware functions the UART communication.
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
#include <stdio.h>
#include "bluenrg_lp_evb_com.h"
#include "rf_driver_ll_usart.h"
/** @addtogroup BSP
  * @{
  */ 

/** @defgroup BSP_BLUENRGLP_COM BSP BlueNRG-LP COM
  * @{
  */ 

/** @defgroup BSP_BLUENRGLP_COM_Private_Defines            Private Defines
 * @{
 */
#define READ_DATA_SIZE      1024
#define READ_BUFFER_IS_EMPTY() (Read_ptr_in == Read_ptr_out)

/**
 * @}
 */


/** @defgroup BSP_BLUENRGLP_COM_Private_TypesDefinitions    Private Types Definitions
 * @{
 */

/**
 * @brief  IO_Receive_Data User callback 
 */
typedef struct _BSP_COM_RxDataCb
{
  /**
   * callback to notify the applicatio with the received I/O data
   */ 
  BSP_COM_RxDataCb_t RxDataUserCb;
} BSP_COM_RxDataCb_st;

/**
 * @}
 */


/** @defgroup BSP_BLUENRGLP_COM_Private_Variable    Private Variable
 * @{
 */

/* RX data user callback used to handle received data from BSP UART channel */
static BSP_COM_RxDataCb_st BSP_COM_RxDataCb;

static uint8_t  Read_Buffer[READ_DATA_SIZE]; 
static uint32_t Read_ptr_in = 0;
static uint32_t Read_ptr_out = 0;

/**
 * @}
 */


/** @defgroup BSP_BLUENRGLP_COM_Private_Function_Declaration    Private Function_Declaration
 * @{
 */
static void Read_Buffer_Push(uint8_t byte);
static uint8_t Read_Buffer_Pop(uint8_t *byte);

/**
 * @}
 */


/** @defgroup BSP_BLUENRGLP_COM_Exported_Functions Exported Functions
  * @{
  */ 


/**
  * @brief  Configures the UART interface.
  * @param  pRxDataCb user callback for handling the data received
  *         if NULL: the UART IRQ is not configured.
  * @retval None
  */
void BSP_COM_Init(BSP_COM_RxDataCb_t pRxDataCb)
{
  /* Initialize the GPIOs associated to the UART port */
  BSP_UART_TX_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, LL_GPIO_PULL_UP);
  BSP_UART_TX_GPIO_AF();

  BSP_UART_RX_GPIO_CLK_ENABLE();
  LL_GPIO_SetPinMode(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, LL_GPIO_PULL_UP);
  BSP_UART_RX_GPIO_AF();

  /* Initialize the UART clock */
  BSP_UART_CLK_ENABLE();

  /* UART parameter configuration*/
  LL_USART_SetBaudRate(BSP_UART, LL_USART_PRESCALER_DIV1, LL_USART_OVERSAMPLING_16, BSP_UART_BAUDRATE);
  LL_USART_ConfigCharacter(BSP_UART, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
  LL_USART_SetTransferDirection(BSP_UART, LL_USART_DIRECTION_TX_RX);
  LL_USART_SetHWFlowCtrl(BSP_UART, LL_USART_HWCONTROL_NONE);

  LL_USART_SetRXFIFOThreshold(BSP_UART, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetTXFIFOThreshold(BSP_UART, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_EnableFIFO(BSP_UART);

  LL_USART_ConfigAsyncMode(BSP_UART);
  
  /* Enable the UART */
  LL_USART_Enable(BSP_UART);

  /* If the user callback is not NULL */
  if(pRxDataCb != NULL) {
    /* Record the user callback for handling the RX data */
    BSP_COM_RxDataCb.RxDataUserCb = pRxDataCb;

    /* Enable the RX not empty interrupt */
    LL_USART_EnableIT_RXNE(BSP_UART);

    /* Enable the UART IRQ */
    NVIC_SetPriority(BSP_UART_IRQn, IRQ_HIGH_PRIORITY);
    NVIC_EnableIRQ(BSP_UART_IRQn);
#ifdef __GNUC__
  setvbuf(stdout, NULL, _IONBF, 0);
#endif
  }

}



/**
  * @brief  Deinitialize the UART interface.
  * @param  None
  * @retval None
  */
void BSP_COM_DeInit(void)
{
  /* Disable the UART interrupts */
  LL_USART_DisableIT_RXNE(BSP_UART);
  NVIC_DisableIRQ(BSP_UART_IRQn);

  /* Disable the UART peripheral */
  LL_USART_Disable(BSP_UART);

  /* Disable the UART clock */
  BSP_UART_CLK_DISABLE();

  /* Reset the UART pins */
  LL_GPIO_SetPinMode(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, LL_GPIO_PULL_NO);

  LL_GPIO_SetPinMode(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinSpeed(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, LL_GPIO_PULL_NO);
}


/**
  * @brief  Send N bytes through the UART port.
  * @param  pBuff: pBuff. 
  * @param  nBuffSize: nBuffSize. 
  * @retval None
  */
void BSP_COM_Write(uint8_t *pBuff, uint8_t nBuffSize)
{
  for (uint8_t i = 0; i < nBuffSize; i++) {

    /* Wait for TX FIFO not full flag to be raised */
    while (LL_USART_IsActiveFlag_TXE(BSP_UART) == 0);

    /* Send the byte to the UART */
    LL_USART_TransmitData8(BSP_UART, pBuff[i]);
  }
}


/**
  * @brief  Get the received data read function.
  * @param  pData: pData. 
  * @param  nBuffSize: nBuffSize. 
  * @retval None
  */
uint8_t BSP_COM_Read(uint8_t *pData)
{
  uint8_t tmp = 0;

  /* If the user callback is not NULL */
  if(BSP_COM_RxDataCb.RxDataUserCb != NULL) {
    tmp = Read_Buffer_Pop(pData);

#ifdef __CC_ARM
    if(*(int *)pData == EOF)
      return 0;
#endif
  }
  /* If the user callback is NULL, then the management of the reception is done manually */
  else {
    if(LL_USART_IsActiveFlag_RXNE(BSP_UART) == 1) {
      *pData = LL_USART_ReceiveData8(BSP_UART);
      tmp = 1; 
    }
  }

  return tmp; /* 1: character has been read, 0: no character */
}


void BSP_COM_IRQHandler(void)
{
  uint8_t read_data; 
  
  /* If the user callback is not NULL */
  if(BSP_COM_RxDataCb.RxDataUserCb != NULL) {

    /* If the RX FIFO is Not Empty */
    if(LL_USART_IsActiveFlag_RXNE(BSP_UART) == 1)   {

      /* Read a byte from the RX FIFO */
      read_data = LL_USART_ReceiveData8(BSP_UART);
      
      /* Send the data received to the user RX callback */
      BSP_COM_RxDataCb.RxDataUserCb(&read_data, 1);
    }
  }
}


/**
 * @brief  Push a buffer in the read buffer
 * @param  pRxDataBuff data to be pushed
 * @param  nDataSize number of byte to read
 * @retval None
 */
void BSP_COM_RxDataUserCb(uint8_t * pRxDataBuff, uint16_t nDataSize)
{
  for(uint16_t i = 0; i < nDataSize; i++){
      Read_Buffer_Push(pRxDataBuff[i]);
  }
}

/**
 * @brief  Check if UART TX FIFO is empty or not.
 * @retval TRUE if FIFO is not empty, FALSE otherwise.
 */
uint8_t BSP_COM_TxFifoNotEmpty(void)
{
  return (LL_USART_IsActiveFlag_TXFE(BSP_UART) == RESET);
}

/**
 * @brief  Check if UART is BUSY or not.
 * @retval TRUE if UART is BUSY, FALSE otherwise.
 */
uint8_t BSP_COM_UARTBusy(void)
{
  if ((LL_USART_IsActiveFlag_TXE_TXFNF(BSP_UART) == RESET) ||
      (LL_USART_IsActiveFlag_TC(BSP_UART) == RESET))
    return TRUE;
  
  return FALSE;
}


/**
  * @}
  */ 


/** @defgroup BSP_BLUENRGLP_COM_Privated_Functions Privated Functions
  * @{
  */ 

/**
 * @brief  Push a byte in the read buffer
 * @param  byte to be pushed
 * @retval None
 */
static void Read_Buffer_Push(uint8_t byte)
{
  Read_Buffer[Read_ptr_in] = byte;
  
  Read_ptr_in++;
  
  /* To avoid buffer overflow */
  if(Read_ptr_in == READ_DATA_SIZE)
  {
    Read_ptr_in = 0;
  }        
}

/**
 * @brief  Pop out a byte from the read buffer
 * @param  byte to be read
 * @retval 0 if buffer empty, 1 otherwise
 */
static uint8_t Read_Buffer_Pop(uint8_t *byte)
{
  if(READ_BUFFER_IS_EMPTY())
    return 0;
  
  *byte = Read_Buffer[Read_ptr_out];
  Read_ptr_out++;
  
  if(Read_ptr_out == READ_DATA_SIZE)
    Read_ptr_out = 0;  
  
  return 1;
}



#ifdef __ICCARM__
#include <yfuns.h>

size_t __write(int handle, const unsigned char * buffer, size_t size)
{
  size_t nChars = 0;

  if (handle != _LLIO_STDOUT && handle != _LLIO_STDERR) {
    return _LLIO_ERROR;
  }

  if (buffer == 0) {
    // This means that we should flush internal buffers.
    //spin until TX complete (TX is idle)
    return 0;
  }

  while(size--) {
    BSP_COM_Write((uint8_t *)buffer++, 1);
    ++nChars;
  }

  return nChars;
}

size_t __read(int handle, unsigned char * buffer, size_t size)
{
  size_t bytes = 0;
  
  while (bytes < size) {
    if (Read_Buffer_Pop(buffer+bytes))
      bytes++;
  }
  return bytes;
}

int putchar(int c)
{
  __write(_LLIO_STDOUT, (const unsigned char *)&c, 1);
  return c;
}

#else
#ifdef __CC_ARM

#include <stdio.h>
/* keil debug port defines */
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever needed */ };
FILE __stdout;
FILE __stdin;

/* KEIL fputc implementation template allowing to redirect printf output towards serial port (UART/USB) */
int fputc(int c, FILE *f)
{  
  BSP_COM_Write((uint8_t *)&c, 1);
  
  return 1;
}


int fgetc (FILE *f) {
  int data = 0;
  while (Read_Buffer_Pop((uint8_t *)&data) != SUCCESS);
  return data;
}

#else
#ifdef __GNUC__
#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

/* Variables */
#undef errno
extern int errno;

#undef putchar

int putchar(int c)
{
  BSP_COM_Write((uint8_t *)&c, 1);
  return c;
}


int _close(int32_t file)
{
  return -1;
}


int _fstat(int32_t file, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int32_t file)
{
  return 1;
}

int _lseek(int32_t file, int32_t ptr, int32_t dir)
{
  return 0;
}

int _write(int fd, char *str, int len)
{
  for(int i=0;i<len;i++) {
	BSP_COM_Write( (uint8_t *)&str[i], 1);
  }
  return len;
  
}

int _read(int handle, unsigned char * buffer, size_t size)
{
  int bytes = 0;

  while (bytes < size) {
    if (Read_Buffer_Pop(buffer+bytes)==SUCCESS)
    bytes++;
    else {
      if (bytes)
        break;
    }
  }
  return bytes;
}


uint8_t __io_getcharNonBlocking(uint8_t *data)
{
  if(Read_Buffer_Pop(data) == SUCCESS) {
    return 1;
  }
  else {
    return 0;
  }
}

#endif
#endif
#endif

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
