/*
 * HAL_wrappers.c
 *
 *  Created on: Oct 25, 2019
 *      Author: christian.lehmen
 */

#include "hal_wrappers.h"
#include "spi.h"
#include "peripheral_init.h"

static GpioIrqHandler *GpioIrq[16] = { NULL };

/* Private function prototypes -----------------------------------------------*/

static uint8_t HW_GPIO_GetBitPos(uint16_t GPIO_Pin);

/* Exported functions ---------------------------------------------------------*/
/*!
 * @brief Initializes the given GPIO object
 *
 * @param  GPIOx: where x can be (A..E and H)
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @param [IN] initStruct  GPIO_InitTypeDef intit structure
 * @retval none
 */
void HW_GPIO_Init( GPIO_TypeDef* port, uint16_t GPIO_Pin, GPIO_InitTypeDef* initStruct)
{
	if(port ==GPIOB){
			__HAL_RCC_GPIOB_CLK_ENABLE();
	}else{
			__HAL_RCC_GPIOA_CLK_ENABLE();
	}
		
  //__HAL_RCC_GPIOA_CLK_ENABLE();
	//__HAL_RCC_GPIOB_CLK_ENABLE();
  //RCC_GPIO_CLK_ENABLE(  (uint32_t) port);

  initStruct->Pin = GPIO_Pin ;

  HAL_GPIO_Init( port, initStruct );
}

/*!
 * @brief Records the interrupt handler for the GPIO  object
 *
 * @param  GPIOx: where x can be (A..E and H)
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @param [IN] prio       NVIC priority (0 is highest)
 * @param [IN] irqHandler  points to the  function to execute
 * @retval none
 */
void HW_GPIO_SetIrq( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t prio,  GpioIrqHandler *irqHandler )
{
  IRQn_Type IRQnb;

  uint32_t BitPos = HW_GPIO_GetBitPos( GPIO_Pin ) ;

  if ( irqHandler != NULL)
  {
    GpioIrq[ BitPos ] = irqHandler;

    IRQnb = MSP_GetIRQn( GPIO_Pin );

    HAL_NVIC_SetPriority( IRQnb , prio);

    HAL_NVIC_EnableIRQ( IRQnb );
  }
  else
  {
    GpioIrq[ BitPos ] = NULL;
  }
}

/*!
 * @brief Execute the interrupt from the object
 *
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @retval none
 */
void HW_GPIO_IrqHandler( uint16_t GPIO_Pin )
{
	uint32_t BitPos = HW_GPIO_GetBitPos( GPIO_Pin );

  if ( GpioIrq[ BitPos ]  != NULL)
  {

    GpioIrq[ BitPos ] ( NULL );

  }
}
/*!
 * @brief Writes the given value to the GPIO output
 *
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @param [IN] value New GPIO output value
 * @retval none
 */
void HW_GPIO_Write( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,  uint32_t value ){

  HAL_GPIO_WritePin( GPIOx, GPIO_Pin , (GPIO_PinState) value );
}

/*!
 * @brief Reads the current GPIO input value
 *
 * @param  GPIOx: where x can be (A..E and H)
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @retval value   Current GPIO input value
 */
uint32_t HW_GPIO_Read( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin ){

  return HAL_GPIO_ReadPin( GPIOx, GPIO_Pin);
}

/*!
 * @brief Get the position of the bit set in the GPIO_Pin
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @retval the position of the bit
 */
static uint8_t HW_GPIO_GetBitPos(uint16_t GPIO_Pin)
{
  uint8_t PinPos=0;

  if ( ( GPIO_Pin & 0xFF00 ) != 0) { PinPos |= 0x8; }
  if ( ( GPIO_Pin & 0xF0F0 ) != 0) { PinPos |= 0x4; }
  if ( ( GPIO_Pin & 0xCCCC ) != 0) { PinPos |= 0x2; }
  if ( ( GPIO_Pin & 0xAAAA ) != 0) { PinPos |= 0x1; }

  return PinPos;
}

uint16_t HW_SPI_InOut( uint16_t txData )
{
  uint16_t rxData ;

  HAL_SPI_TransmitReceive( &hspi1, ( uint8_t * ) &txData, ( uint8_t* ) &rxData, 1, HAL_MAX_DELAY);

  return rxData;
}
//uint16_t HW_SPI_InOut( uint16_t txData )
//{
////	HAL_Delay(150);
////	printf("HW_SPI_InOut\n");
//	HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0 );
//	//	
//	////HAL_SPI_TransmitReceive( &hspi1, ( uint8_t * ) &txData, ( uint8_t* ) &rxData, 1, HAL_MAX_DELAY);
//	//	
//	//HAL_SPI_Transmit( &hspi1, ( uint8_t * ) &txData, 1, HAL_MAX_DELAY);

//	//HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 1 );

//	//return rxData;
//	//}
//	//	//##########################################################################################################################################################################
//	//__IO uint8_t ubNbDataToReceive = 1;
//	//__IO uint8_t ubReceiveIndex = 0;
//	//	
//	//__IO uint8_t ubNbDataToTransmit = 1;
//	//__IO uint8_t ubTransmitIndex = 0;
//	//	
//	//	while(ubNbDataToReceive > 0)
//	//  {
//	//    /* Check TXE flag to transmit data */
//	//    if(( LL_SPI_IsActiveFlag_TXE(hspi1.Instance)) && (ubNbDataToTransmit > 0))
//	//    {
//	//      /* Transmit 16bit Data */
//	//      LL_SPI_TransmitData8(hspi1.Instance, txData);
//	//      ubNbDataToTransmit--;
//	//    }
//	//    /* Check RXE flag */
//	//    if(LL_SPI_IsActiveFlag_RXNE(hspi1.Instance))
//	//    {
//	//      /* Receive 16bit Data */
//	//      rxData = LL_SPI_ReceiveData8(hspi1.Instance);
//	//      ubNbDataToReceive--;
//	//    }
//	//  }

//	 // return rxData;

//		//##########################################################################################################################################################################
//	//		


//	//printf("SPI ENABLED? %d\n",LL_SPI_IsEnabled(hspi1.Instance));
//	//printf("LL_SPI_IsActiveFlag_TXE: %d\n",LL_SPI_IsActiveFlag_TXE(hspi1.Instance));
//	////HAL_Delay(50);


//	HAL_SPI_Init(&hspi1);
//	LL_SPI_Enable(hspi1.Instance);
//		
//	//HAL_Delay(50);



//	HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0 );


//	uint16_t aTxBuffer = txData;
//	uint8_t ubNbDataToTransmit;
//	//uint8_t ubTransmitIndex = 0;

//	/* Buffer used for reception */
//	uint16_t aRxBuffer;
//	uint8_t ubNbDataToReceive;

//	ubNbDataToReceive = 1;
//	ubNbDataToTransmit = 1;
//	//uint8_t ubReceiveIndex = 0;
//		 while(ubNbDataToReceive > 0)
//		{
//			/* Check TXE flag to transmit data */
//			if(( LL_SPI_IsActiveFlag_TXE(hspi1.Instance)) && (ubNbDataToTransmit > 0))
//			{
//				/* Transmit 16bit Data */
//				LL_SPI_TransmitData16(hspi1.Instance, aTxBuffer);
//				ubNbDataToTransmit--;
//			}
//			/* Check RXE flag */

//			if(LL_SPI_IsActiveFlag_RXNE(hspi1.Instance))
//			{
//				/* Receive 16bit Data */
//				aRxBuffer = LL_SPI_ReceiveData16(hspi1.Instance);
//				ubNbDataToReceive--;
//			}
//		}


//		
//		
//	HAL_SPI_DeInit(&hspi1);
//	LL_SPI_Disable(hspi1.Instance);
////HAL_Delay(50);

//return aRxBuffer;
//}
//##########################################################################################################################################################################
