/*!
 * \file      sx1262dvk1cas-board.c
 *
 * \brief     Target board SX1261DVK1BAS shield driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 */
/**
  ******************************************************************************
  * @file    sx1262dvk1cas.c
  * @author  MCD Application Team
  * @brief   driver sx1262dvk1cas board
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

#include "radio.h"
#include "sx126x_board.h"
#include "hal_wrappers.h"
#include "peripheral_init.h"
#include "utils.h"

void SX126xIoInit( void )
{/*unused*/}

void SX126xIoIrqInit( DioIrqHandler dioIrq )
{/*unused*/}

void SX126xIoDeInit( void )
{/*unused*/}

uint32_t SX126xGetBoardTcxoWakeupTime( void )
{
    return BOARD_TCXO_WAKEUP_TIME;
}

void SX126xReset( void )
{
	GPIO_InitTypeDef initStruct = { 0 };

	initStruct.Mode =GPIO_MODE_OUTPUT_PP;
	initStruct.Pull = GPIO_NOPULL;
	initStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HW_GPIO_Init( RADIO_NRST_Port, RADIO_NRST_Pin, &initStruct );
	HW_GPIO_Write( RADIO_NRST_Port, RADIO_NRST_Pin, 0 );

	initStruct.Mode = GPIO_MODE_ANALOG;
	HW_GPIO_Init( RADIO_NRST_Port, RADIO_NRST_Pin, &initStruct );
	HW_GPIO_Write( RADIO_NRST_Port, RADIO_NRST_Pin, 1); // internal pull-up

}

void SX126xWaitOnBusy( void )
{
    while( HW_GPIO_Read(RADIO_BUSY_Port, RADIO_BUSY_Pin) == 1 );

}

void SX126xWakeup( void )
{
    //NSS = 0;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0 );
    HW_SPI_InOut(RADIO_GET_STATUS);
    HW_SPI_InOut(0);
    //NSS = 1;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 1 );
    // Wait for chip to be ready.
    SX126xWaitOnBusy( );
}

void SX126xWriteCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
   SX126xCheckDeviceReady( );


	HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0);
	
  HW_SPI_InOut(command);


  for( uint16_t i = 0; i < size; i++ ){
				HW_SPI_InOut( buffer[i] );
    }
	HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 1 );
		

    if( command != RADIO_SET_SLEEP )
    {
        SX126xWaitOnBusy( );
    }

}

uint8_t SX126xReadCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    uint8_t status = 0;

    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0 );

    HW_SPI_InOut(command);
    status = HW_SPI_InOut(0x00 );
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = HW_SPI_InOut( 0 );
    }

    //NSS = 1;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 1 );

    SX126xWaitOnBusy( );

    return status;
}

void SX126xWriteRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0 );
    
    HW_SPI_InOut(RADIO_WRITE_REGISTER );
    HW_SPI_InOut(( address & 0xFF00 ) >> 8 );
    HW_SPI_InOut(address & 0x00FF );
    
    for( uint16_t i = 0; i < size; i++ )
    {
        HW_SPI_InOut(buffer[i] );
    }

    //NSS = 1;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 1 );

    SX126xWaitOnBusy( );
}

void SX126xWriteRegister( uint16_t address, uint8_t value )
{
    SX126xWriteRegisters( address, &value, 1 );
}

void SX126xReadRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0 );

    HW_SPI_InOut(RADIO_READ_REGISTER);
    HW_SPI_InOut(( address & 0xFF00) >> 8 );
    HW_SPI_InOut(address & 0x00FF);
    HW_SPI_InOut(0);
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = HW_SPI_InOut( 0 );
    }
    //NSS = 1;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 1 );

    SX126xWaitOnBusy( );
}

uint8_t SX126xReadRegister( uint16_t address )
{
    uint8_t data;
    SX126xReadRegisters( address, &data, 1 );
    return data;
}

void SX126xWriteBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0 );

    HW_SPI_InOut( RADIO_WRITE_BUFFER );
    HW_SPI_InOut( offset );

    for( uint16_t i = 0; i < size; i++ )
    {
        HW_SPI_InOut( buffer[i] );

    }

    //NSS = 1;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 1 );

    SX126xWaitOnBusy( );
}


void SX126xReadBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 0 );

    HW_SPI_InOut( RADIO_READ_BUFFER );
    HW_SPI_InOut( offset );
    HW_SPI_InOut( 0 );
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = HW_SPI_InOut( 0 );
    }
    
    //NSS = 1;
    HW_GPIO_Write( RADIO_NSS_Port, RADIO_NSS_Pin, 1 );

    SX126xWaitOnBusy( );
}
void SX126xSetRfTxPower( int8_t power )
{
    SX126xSetTxParams( power, RADIO_RAMP_40_US );
}



uint8_t SX126xGetPaSelect( uint32_t channel )
{
	  return SX1262;
}
void SX126xAntSwOn(void){
		HW_GPIO_Write( RADIO_SWITCH_ENABLE_Port, RADIO_SWITCH_ENABLE_Pin, 1 );
}
void SX126xAntSwOff(void){
		HW_GPIO_Write( RADIO_SWITCH_ENABLE_Port, RADIO_SWITCH_ENABLE_Pin, 0 );
}

bool SX126xCheckRfFrequency( uint32_t frequency )
{
    // Implement check. Currently all frequencies are supported
    return true;
}

bool SX126xBoardIsTcxoPresent(void)
{ /*no TCXO on board*/
  return false;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
