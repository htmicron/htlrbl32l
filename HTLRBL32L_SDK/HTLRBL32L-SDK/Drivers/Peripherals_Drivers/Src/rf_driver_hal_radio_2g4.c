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
#include "rf_driver_hal_radio_2g4.h"
#include "rf_driver_hal_vtimer.h"

/* Access address used only to sense medium with HAL_RADIO_CarrierSense() */
#define FAKE_NETWORK_ID 0xAAAAAAAA

#define TIME_DIFF(a, b)       ((int32_t)(a - b))

static ActionPacket aPacket[2]; 
static uint32_t networkID = 0x88DF88DF;

static uint8_t CondRoutineTrue(ActionPacket* p)
{
  return TRUE;
}

static uint8_t dataRoutineNull(ActionPacket* current_action_packet, ActionPacket* next)
{
  return TRUE;
}

static uint8_t CondRoutineRxTrue(ActionPacket* p)
{
  /* received a packet */
  if((p->status & BLUE_INTERRUPT1REG_RCVOK) != 0){
    /* packet received without CRC error */ 
    return TRUE;
  }
  return FALSE; 
}


/**
* @brief  This routine sets the network ID field for packet transmission and filtering for the receiving.
*         Only two devices with same networkID can communicate with each other.
* @param  ID: network ID based on bluetooth specification:
*           1. It shall have no more than six consecutive zeros or ones.
*           2. It shall not have all four octets equal.
*           3. It shall have no more than 24 transitions.
*           4. It shall have a minimum of two transitions in the most significant six bits.
*
* @retval uint8_t: return value
*           - 0x00 : Success.
*           - 0xC0 : Invalid parameter.
*/
uint8_t HAL_RADIO_SetNetworkID(uint32_t ID)
{
  networkID = ID;
  return 0;
}


/**
* @brief  This routine sends a packet on a specific channel and at a specific time.
* @param  channel: Frequency channel between 0 to 39.
* @param  wakeup_time: Time of transmission in us. This is relative time regarding now.
*         Minimum wakeup_time of 230 us. TBR
* @param  txBuffer: Pointer to TX data buffer. Second byte of this buffer must be the length of the data.
* @param  Callback: This function is being called as data routine.
*         First ActionPacket is current action packet and the second one is next action packet.
* @retval uint8_t return value
*           - 0x00 : Success.
*           - 0xC0 : Invalid parameter.
*           - 0xC4 : Radio is busy, receiving has not been triggered.
*/
uint8_t HAL_RADIO_SendPacket(uint8_t channel, 
                             uint32_t wakeup_time, 
                             uint8_t* txBuffer, 
                             uint8_t (*Callback)(ActionPacket*, ActionPacket*))
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t dummy,time;
  
  time = (uint32_t)TIMER_GetCurrentSysTime() + TIMER_UsToSystime(wakeup_time);
  
  if(channel > 39) {
    returnValue = INVALID_PARAMETER_C0;
  }
  
  if(RADIO_GetStatus(&dummy) != BLUE_IDLE_0) {
    returnValue = RADIO_BUSY_C4;
  }
  
  if(returnValue == SUCCESS_0) {
    uint8_t map[5]= {0xFF,0xFF,0xFF,0xFF,0xFF};
    RADIO_SetChannelMap(0, &map[0]);
    RADIO_SetChannel(0, channel, 0);
    RADIO_SetTxAttributes(0, networkID, 0x555555);

    aPacket[0].StateMachineNo = STATE_MACHINE_0;
    aPacket[0].ActionTag =  TXRX | PLL_TRIG;
    aPacket[0].WakeupTime = time;
    aPacket[0].MaxReceiveLength = 0; /* does not affect for Tx */
    aPacket[0].data = txBuffer;
    aPacket[0].next_true = NULL_0;
    aPacket[0].next_false = NULL_0;
    aPacket[0].condRoutine = CondRoutineTrue;
    aPacket[0].dataRoutine = Callback;
    
    RADIO_SetReservedArea(&aPacket[0]); 
    returnValue = RADIO_MakeActionPacketPending(&aPacket[0]);
  }
  
  return returnValue; 
}


/**
* @brief  This routine sends a packet on a specific channel and at a certain time then wait for receiving acknowledge.
* @param  channel: Frequency channel between 0 to 39.
* @param  wakeup_time: Time of transmission based on us. This is relative time regarding now.
*         Minimum wakeup_time of 250 us. TBR
* @param  txBuffer: Pointer to TX data buffer. Secound byte of this buffer must be the length of the data.
* @param  rxBuffer: Pointer to RX data buffer. Secound byte of this buffer must be the length of the data.
* @param  receive_timeout: Time of RX window used to wait for the packet on us.
* @param  receive_length: number of bytes that the link layer accepts in reception.
* @param  callback: This function is being called as data routine.
*         First ActionPacket is current action packet and the second one is next action packet.
* @retval uint8_t return value
*           - 0x00 : Success.
*           - 0xC0 : Invalid parameter.
*           - 0xC4 : Radio is busy, receiving has not been triggered.
*/
uint8_t HAL_RADIO_SendPacketWithAck(uint8_t channel, 
                                    uint32_t wakeup_time, 
                                    uint8_t* txBuffer, 
                                    uint8_t* rxBuffer,
                                    uint32_t receive_timeout, 
                                    uint8_t receive_length,
                                    uint8_t (*Callback)(ActionPacket*, ActionPacket*))
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t dummy,time;
  
  time = (uint32_t)TIMER_GetCurrentSysTime() + TIMER_UsToSystime(wakeup_time);
  
  if(channel > 39) {
    returnValue = INVALID_PARAMETER_C0;      
  }

  if(RADIO_GetStatus(&dummy) != BLUE_IDLE_0) {
    returnValue = RADIO_BUSY_C4;
  }
      
  uint8_t map[5]= {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
  RADIO_SetChannelMap(0, &map[0]);
  RADIO_SetChannel(0, channel, 0);
  RADIO_SetTxAttributes(0, networkID, 0x555555);
  RADIO_SetGlobalReceiveTimeout(receive_timeout);
  
  aPacket[0].StateMachineNo = 0;
  aPacket[0].ActionTag = TXRX | PLL_TRIG;
  aPacket[0].WakeupTime = time;
  aPacket[0].MaxReceiveLength = 0; /* does not affect for Tx */
  aPacket[0].data = txBuffer;
  aPacket[0].next_true = &aPacket[1];
  aPacket[0].next_false = &aPacket[1];
  aPacket[0].condRoutine = CondRoutineTrue;
  aPacket[0].dataRoutine = dataRoutineNull;
  
  aPacket[1].StateMachineNo = STATE_MACHINE_0;   
  aPacket[1].ActionTag = 0;   
  aPacket[1].WakeupTime = time;
  aPacket[1].MaxReceiveLength = receive_length; 
  aPacket[1].data = rxBuffer; 
  aPacket[1].next_true = NULL_0;
  aPacket[1].next_false = NULL_0;    
  aPacket[1].condRoutine = CondRoutineTrue;
  aPacket[1].dataRoutine = Callback;

  RADIO_SetReservedArea(&aPacket[0]);
  RADIO_SetReservedArea(&aPacket[1]);
  returnValue = RADIO_MakeActionPacketPending(&aPacket[0]);    
    
  return returnValue; 
}


static uint8_t CarrierSenseCallback(ActionPacket* p, ActionPacket* next)
{  
  return TRUE;  
}

/**
* @brief  This funtion puts the radio in RX state to read the RSSI.
* @note   The function uses a busy loop to wait for the RSSI value and then exits
*         from RX state.
* @param      channel: Frequency channel between 0 to 39.
* @param[out] rssi: the measured RSSI value on the channel
* @retval uint8_t return value
*           - 0x00 : Success.
*           - 0xC0 : Invalid parameter.
*           - 0xC4 : Radio is busy, receiving has not been triggered.
*/
uint8_t HAL_RADIO_CarrierSense(uint8_t channel, int8_t *rssi)
{
  uint8_t ret;
  uint16_t loop = 0;
  uint32_t *DEMOD_DIG_TST_p = (uint32_t*)0x60001564;
  uint32_t end_time;
  static uint8_t buffer[1];
  
  *rssi = 127;
    
  uint8_t networkID_tmp = networkID;
  
  networkID = FAKE_NETWORK_ID;
  
  ret = HAL_RADIO_ReceivePacket(channel, 240, buffer, 1000, sizeof(buffer), CarrierSenseCallback);
  
  networkID = networkID_tmp;
  
  if(ret)
    return ret;
  
  /* loop variable just to protect from inifinite loop */
  while((RRM->FSM_STATUS_DIG_OUT & RRM_FSM_STATUS_DIG_OUT_STATUS) != 0x1A && loop++ < 60000);  
  end_time = WAKEUP->ABSOLUTE_TIME + 20;
  while(TIME_DIFF(end_time,WAKEUP->ABSOLUTE_TIME) > 0);
  *DEMOD_DIG_TST_p = 0x02;
  /* Need to wait at least 3 BLE clocks. In worst case (sysclock = 64 MHz and blesysclk = 16 MHz) 
     this means 12 cpu cycles. Some cycles are already used by the call to RADIO_ReadRSSI()
     and at the beginning of the function. */
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  *rssi = RADIO_ReadRSSI();
    *DEMOD_DIG_TST_p = 0x00;
  BLUE->CMDREG = BLUE_CMDREG_TXRXSKIP;
  
  return 0;
}


/**
* @brief  This routine receives a packet on a specific channel and at a certain time.
* @param  channel: Frequency channel between 0 to 39.
* @param  wakeup_time: Time of transmission based on us. This is relative time regarding now.
*         Minimum wakeup_time of 230 us. TBR
* @param  rxBuffer: Pointer to RX data buffer. Second byte of this buffer must be the length of the data.
* @param  receive_timeout: Time of RX window used to wait for the packet on us.
* @param  receive_length: number of bytes that the link layer accepts in reception.
* @param  callback: This function is being called as data routine.
*         First ActionPacket is current action packet and the second one is next action packet.
* @retval uint8_t return value
*           - 0x00 : Success.
*           - 0xC0 : Invalid parameter.
*           - 0xC4 : Radio is busy, receiving has not been triggered.
*/
uint8_t HAL_RADIO_ReceivePacket(uint8_t channel, 
                                uint32_t wakeup_time, 
                                uint8_t* rxBuffer,
                                uint32_t receive_timeout,                       
                                uint8_t receive_length, 
                                uint8_t (*Callback)(ActionPacket*, ActionPacket*))
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t dummy,time;
  
  time = (uint32_t)TIMER_GetCurrentSysTime() + TIMER_UsToSystime(wakeup_time);
  
  if(channel > 39) {
    returnValue = INVALID_PARAMETER_C0;
  }
  
  if(RADIO_GetStatus(&dummy) != BLUE_IDLE_0) {
    returnValue = RADIO_BUSY_C4;
  }
  
  if(returnValue == SUCCESS_0) {
    uint8_t map[5]= {0xFF,0xFF,0xFF,0xFF,0xFF};
    RADIO_SetChannelMap(0, &map[0]);
    RADIO_SetChannel(0, channel, 0);
    RADIO_SetTxAttributes(0, networkID, 0x555555);
    RADIO_SetGlobalReceiveTimeout(receive_timeout);
    
    
    aPacket[0].StateMachineNo = STATE_MACHINE_0;
    aPacket[0].ActionTag =  PLL_TRIG;
    aPacket[0].WakeupTime = time;
    aPacket[0].MaxReceiveLength = receive_length;
    aPacket[0].data = rxBuffer;
    aPacket[0].next_true = NULL_0;
    aPacket[0].next_false = NULL_0;
    aPacket[0].condRoutine = CondRoutineTrue;
    aPacket[0].dataRoutine = Callback;
    
    RADIO_SetReservedArea(&aPacket[0]);
    returnValue = RADIO_MakeActionPacketPending(&aPacket[0]);
  }
  
  return returnValue;
}


/**
* @brief  This routine receives a packet on a specific channel and at a certain time.
*         Then sends a packet as an acknowledgment.
* @param  channel: frequency channel between 0 to 39.
* @param  wakeup_time: time of transmission based on us. This is relative time regarding now.
*         Minimum wakeup_time of 250 us. TBR
* @param  rxBuffer: points to received data buffer. second byte of this buffer determines the length of the data.
* @param  txBuffer: points to data buffer to send. secound byte of this buffer must be the length of the buffer.
* @param  receive_timeout: Time of RX window used to wait for the packet on us.
* @param  receive_length: number of bytes that the link layer accepts in reception.
* @param  callback: This function is being called as data routine.
*         First ActionPacket is current action packet and the second one is next action packet.
* @retval uint8_t return value
*           - 0x00 : Success.
*           - 0xC0 : Invalid parameter.
*           - 0xC4 : Radio is busy, receiving has not been triggered.
*/
uint8_t HAL_RADIO_ReceivePacketWithAck(uint8_t channel, 
                                       uint32_t wakeup_time,
                                       uint8_t* rxBuffer, 
                                       uint8_t* txBuffer,
                                       uint32_t receive_timeout,
                                       uint8_t receive_length, 
                                       uint8_t (*Callback)(ActionPacket*, ActionPacket*))
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t dummy,time;
  
  time = (uint32_t)TIMER_GetCurrentSysTime() + TIMER_UsToSystime(wakeup_time);
  
  if(channel > 39) {
    returnValue = INVALID_PARAMETER_C0;      
  }
  
  if(RADIO_GetStatus(&dummy) != BLUE_IDLE_0) {
    returnValue = RADIO_BUSY_C4;
  }
    
  if(returnValue == SUCCESS_0) {
    uint8_t map[5]= {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
  
    RADIO_SetChannelMap(0, &map[0]);
    RADIO_SetChannel(0, channel, 0);
    RADIO_SetTxAttributes(0, networkID, 0x555555);
    RADIO_SetGlobalReceiveTimeout(receive_timeout);
    
    aPacket[0].StateMachineNo = STATE_MACHINE_0;
    aPacket[0].ActionTag =  PLL_TRIG;
    aPacket[0].WakeupTime = time;
    aPacket[0].MaxReceiveLength = receive_length;
    aPacket[0].data = rxBuffer;
    aPacket[0].next_true = &aPacket[1];
    aPacket[0].next_false = NULL_0;
    aPacket[0].condRoutine = CondRoutineRxTrue;
    aPacket[0].dataRoutine = Callback;
        
    aPacket[1].StateMachineNo = STATE_MACHINE_0;
    aPacket[1].ActionTag =  TXRX;
    aPacket[1].WakeupTime = time;
    aPacket[1].MaxReceiveLength = 0; /* does not affect for Tx */
    aPacket[1].data = txBuffer;
    aPacket[1].next_true = NULL_0;
    aPacket[1].next_false = NULL_0;
    aPacket[1].condRoutine = CondRoutineTrue;
    aPacket[1].dataRoutine = Callback;
    
    RADIO_SetReservedArea(&aPacket[0]); 
    RADIO_SetReservedArea(&aPacket[1]); 
    returnValue = RADIO_MakeActionPacketPending(&aPacket[0]);
  }
  
  return returnValue; 
}
/******************* (C) COPYRIGHT 2019 STMicroelectronics *****END OF FILE****/
