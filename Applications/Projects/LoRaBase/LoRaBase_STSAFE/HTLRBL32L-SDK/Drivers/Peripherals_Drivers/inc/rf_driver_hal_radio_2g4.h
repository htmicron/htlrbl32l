/**
  ******************************************************************************
  * @file    rf_driver_ll_radio_2g4.h
  * @author  RF Application Team
  * @brief   BlueNRG-LP HAL radio APIs 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#ifndef RF_DRIVER_HAL_RADIO_H
#define RF_DRIVER_HAL_RADIO_H

#include "rf_driver_ll_radio_2g4.h"

uint8_t HAL_RADIO_SendPacket(uint8_t channel, 
                    uint32_t wakeup_time, 
                    uint8_t* txBuffer, 
                    uint8_t (*Callback)(ActionPacket*, ActionPacket*) );
                          
uint8_t HAL_RADIO_SendPacketWithAck(uint8_t channel, 
                                 uint32_t wakeup_time, 
                                 uint8_t* txBuffer, 
                                 uint8_t* rxBuffer,
                                 uint32_t receive_timeout,
                                 uint8_t receive_length,
                                 uint8_t (*Callback)(ActionPacket*, ActionPacket*));
                                
uint8_t HAL_RADIO_ReceivePacket(uint8_t channel, 
                      uint32_t wakeup_time, 
                      uint8_t* rxBuffer,
                      uint32_t receive_timeout,
                      uint8_t receive_length, 
                      uint8_t (*Callback)(ActionPacket*, ActionPacket*));

uint8_t HAL_RADIO_ReceivePacketWithAck(uint8_t channel, 
                             uint32_t wakeup_time,
                             uint8_t* rxBuffer, 
                             uint8_t* txBuffer,
                             uint32_t receive_timeout,
                             uint8_t receive_length, 
                             uint8_t (*Callback)(ActionPacket*, ActionPacket*));
                        
uint8_t HAL_RADIO_SetNetworkID(uint32_t ID);

uint8_t HAL_RADIO_CarrierSense(uint8_t channel, int8_t *rssi);

#endif /* RF_DRIVER_HAL_RADIO_H */
