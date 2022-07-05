/**
  ******************************************************************************
  * @file    rf_driver_ll_radio_2g4.c
  * @author  RF Application Team
  * @brief   This file provides all the BlueNRG-LP Radio Driver APIs.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "rf_driver_hal_vtimer.h"
#include "rf_driver_ll_radio_2g4.h"
#include <osal.h>

#ifdef  USE_FULL_ASSERT
  #include "rf_driver_assert.h"
#else
  #define assert_param(expr) ((void)0UL)
#endif

#define RSSI_OFFSET 119

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

/** @defgroup RADIO RADIO
  * @brief RADIO low level driver
  * @{
  */


/** @defgroup RADIO_Private_Constants RADIO Private Constants
  * @{
  */ 

/** @defgroup Sequencer_timeouts Sequencer Timeouts
  * @{
  */
    
/*initDelay*/
#define INITDELAY_WAKEUP          0x20U
#define INITDELAY_TIMER12_CAL     0x3FU
#define INITDELAY_TIMER2_NOCAL    0x9U

/*Init_radio_delay*/
#define DELAYCHK_TRANSMIT_CAL     0x76U
#define DELAYCHK_TRANSMIT_NOCAL   0x3AU
#define DELAYCHK_RECEIVE_CAL      0x74U
#define DELAYCHK_RECEIVE_NOCAL    0x38U

/*ConfigEndDuration*/
#define CONFIG_END_DURATION       0x14U

/*DataInit phase start*/
#define CHECK_TXDATAREADY         0x5U

/*TX parameters init*/
#define TXREADY_TIMEOUT          0x2U
#define TXDELAY_START            0x10U
#define TXDELAY_END              0x10U

/*RX parameter init*/
#define RCV_TIMEOUT              0x100

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup RADIO_Private_Macros RADIO Private Macros
  * @{
  */

#define IS_STATE_VALID(STATEMACHINE_NO) (STATEMACHINE_NO < STATEMACHINE_COUNT)
#define IS_POWERLEVEL_VALID(POWER) (POWER < 0x20)
#define IS_RFCHANNEL_VALID(RF_CHANNEL) (RF_CHANNEL <40)
#define IS_FREQOFFSET_VALID(FREQ_OFFSET) (FREQ_OFFSET >2)
#define IS_PHY_VALID(PHY) (PHY==PHY_1M || PHY==PHY_2M || PHY==PHY_CODED_S_2 || PHY==PHY_CODED_S_8)
#define IS_PREALEN_VALID(PREA) (PREA < 16)

#define IRQBLUE                 (BLE_TX_RX_IRQn)
#define IRQRADIO_CTRL           (RADIO_CTRL_IRQn)
#define IRQWAKEUP_BLUE          (BLE_WKUP_IRQn)
#define IRQWAKEUP_CPU           (CPU_WKUP_IRQn)

#define MASK_INTERRUPTS() __disable_irq(); 
#define UNMASK_INTERRUPTS() __enable_irq();

#define DISABLE_INTERRUPT(irqNum)            {NVIC_DisableIRQ(irqNum);}
#define ENABLE_INTERRUPT(irqNum)             {NVIC_EnableIRQ(irqNum);}

/**
  * @}
  */ 

/** @defgroup RADIO_Private_Variables RADIO Private Variables
  * @{
  */

RadioGlobalParameters_t globalParameters;

/**
  * @}
  */ 

/** @defgroup RADIO_Private_Functions RADIO Private Functions 
  * @{
  */

/**
 * @brief  Read RSSI
 * @retval int8_t: RSSI in dBm
 */
int8_t RADIO_ReadRSSI(void)
{
  int32_t rssi_dbm;
  uint32_t rssi0 = RRM->RSSI0_DIG_OUT;
  uint32_t rssi1 = RRM->RSSI1_DIG_OUT;
 
  uint32_t rssi_int16 = ((rssi1&0xFF)<<8)|(rssi0&0xFF);
  uint32_t reg_agc = RRM->AGC_DIG_OUT;
   
  if ((rssi_int16 == 0U) || (reg_agc > 0xbU))
  {
    rssi_dbm = 127 ;
  }
  else
  {
    rssi_dbm = (int32_t)reg_agc * 6 - RSSI_OFFSET;//127 ;
    while (rssi_int16 > 30U)
    {
      rssi_dbm = rssi_dbm + 6 ;
      rssi_int16 = (rssi_int16 >> 1) ;
    }
    rssi_dbm = rssi_dbm + (int32_t)(uint32_t)((417U*rssi_int16 + 18080U)>>10) ;
  }
  return (int8_t)rssi_dbm;
}

/**
  * @}
  */ 

/** @defgroup RADIO_Exported_Functions RADIO Exported Functions
  * @{
  */

/**
 * @brief  Radio ISR.
 *         Besides, next packet is scheduled here.
 * @retval None
 */
void RADIO_IRQHandler(void)
{
  uint32_t int_value = BLUE->INTERRUPT1REG;

  /* clear interrupts */
  BLUE->INTERRUPT1REG = int_value;

  if ( (int_value & BLUE_INTERRUPT1REG_DONE) != 0) {
  
    ActionPacket* next, *actionPacketBackup;
    BlueTransStruct *p;
    uint32_t time;
    
    /* Copy status in order for callback to access it. */ 
    globalParameters.current_action_packet->status = int_value | \
                                            (BLUE->STATUSREG & BLUE_STATUSREG_PREVTRANSMIT_Msk);
    
    if((globalParameters.current_action_packet->condRoutine(globalParameters.current_action_packet) ) == TRUE) {
      next = globalParameters.current_action_packet->next_true;
    }
    else {
      next = globalParameters.current_action_packet->next_false;
    }
    /*The radio event is started. So here a check on the next packet of the event is made*/
    if(next == NULL_0) {
      /* timer2 off */
      TIMER_DISABLE_RADIO_TIMERS;
      MODIFY_REG(blueglob->BYTE4,GLOBAL_BYTE4_ACTIVE_Msk,BLUE_IDLE_0);
    }
    else {
      blueglob->BYTE4 = (next->StateMachineNo | GLOBAL_BYTE4_ACTIVE_Msk);
      p= &next->trans_packet;
      MODIFY_REG((bluedata + next->StateMachineNo)->BYTE0,STATEMACH_BYTE0_TXMODE_Msk,next->trans_config);/* Transmission or reception*/
      (bluedata + next->StateMachineNo)->TXPOINT = BLUE_STRUCT_PTR_CAST(p);
      (bluedata + next->StateMachineNo)->RCVPOINT = BLUE_STRUCT_PTR_CAST(p);
      (bluedata + next->StateMachineNo)->MAXRECEIVEDLENGTH = next->MaxReceiveLength;

      /* Packet will execute on time specified by WakeupTime */
      if((next->ActionTag & TIMER_WAKEUP ) !=0){
        /* timer2 off */
        TIMER_DISABLE_TIMER12;

        /* program timer at next->wakeuptime */
        if((next->ActionTag & RELATIVE ) !=0) {
          time = TIMER_GetCurrentSysTime() + TIMER_UsToSystime(next->WakeupTime);
          HAL_VTIMER_SetRadioTimerValue(time,(next->trans_config == STATEMACH_BYTE0_TXMODE_Msk),(next->ActionTag & PLL_TRIG));
        }
        else {
          HAL_VTIMER_SetRadioTimerValue(next->WakeupTime,(next->trans_config == STATEMACH_BYTE0_TXMODE_Msk),(next->ActionTag & PLL_TRIG));
        }
      } 
      else {
        /* back to back */
      }
    }
    
    /* Accept the packet even with CRC Error */
    if( ( (int_value & BLUE_INTERRUPT1REG_RCVOK) != 0) || ( (int_value & BLUE_INTERRUPT1REG_RCVCRCERR) != 0) ) {
      /* read RSSI */
      globalParameters.current_action_packet->rssi =  RADIO_ReadRSSI();
      
      /* bluedata->config = bluedata->config ^ 0x80 ;  toggle NESN bit
      bluedata->config = bluedata->config & 0x7F ;  //reset NESN bit */
      
      /* read time stamp */
      globalParameters.current_action_packet->timestamp_receive = TIMER_GetAnchorPoint();
    }
    else if( (int_value & BLUE_INTERRUPT1REG_RCVTIMEOUT) != 0) {
      /* read RSSI even if a timeout happens */
      globalParameters.current_action_packet->rssi =  RADIO_ReadRSSI();
    }
    
    actionPacketBackup = globalParameters.current_action_packet;
    globalParameters.current_action_packet = next;
    actionPacketBackup->dataRoutine(actionPacketBackup, next);
  }
  
  /* If the device is configured with 
     System clock = 64 MHz and BLE clock = 16 MHz
     a register read is necessary to end fine  
     the clear interrupt register operation,
     due the AHB down converter latency */
  int_value = BLUE->INTERRUPT1REG;
  
  return ;
}

/**
 * @brief  This routine force the radio to be stopped. After calling this function,
 *         the ISR is not triggered unless, "MakeActionPacketPending" API called again.
 * @retval 0 if the radio activity has been cleared successfully.
 * @retval 1 if it is too late to clear the last radio activity.
 * @retval 2 if it might not be possible to clear the last radio activity.
 */
uint8_t RADIO_StopActivity(void)
{
  uint8_t retval;
  MASK_INTERRUPTS();
  MODIFY_REG(blueglob->BYTE4,GLOBAL_BYTE4_ACTIVE_Msk,BLUE_IDLE_0);
  retval = HAL_VTIMER_ClearRadioTimerValue();
  globalParameters.current_action_packet = 0;
  UNMASK_INTERRUPTS();
  return retval;     
}

/**
 * @brief  This routine sets the channel map. If channel map is not in use, do not use it. The
 *         chan_remap constant is a 37-bit vector, one bit per channel from 0 to 36, with the
 *         LSB corresponding to the channel 0. If the corresponding bit is set, the channel is in use; if it is cleared,
 *         there is an automatic remap to another channel, as defined in the Bluetooth Low
 *         Energy specification. 
 *         Setting all bits of the array to one, disables the channel remapping, and this is the mode
 *         that should be used if the Bluetooth channel remap is not in use.
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  chan_remap: a 37-bit vector, one bit per channel from 0 to 36, with the LSB corresponding to the channel 0 
 * @retval None
 */
void RADIO_SetChannelMap(uint8_t StateMachineNo,uint8_t *chan_remap)
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));  
    
  for(uint8_t i = 0; i < 5; i++) {
    (bluedata + StateMachineNo)->USEDCHANNELFLAGS[i] = chan_remap[i];
  }
  (bluedata + StateMachineNo)->USEDCHANNELFLAGS[4] &= 0x1F;
  return;
}

/**
 * @brief  This routine sets the channel and the channel increment. Channel and channel
 *         increment follows channel mapping corresponding to Bluetooth specification.
 *         RF channel 0:  2402 MHz -> channel 37
 *         RF channel 1:  2404 MHz -> channel 0
 *         RF channel 2:  2406 MHz -> channel 1
 *         ...
 *         RF channel 11: 2424 MHz -> channel 10
 *         RF channel 12: 2426 MHz -> channel 38
 *         RF channel 13: 2428 MHz -> channel 11
 *         RF channel 14: 2430 MHz -> channel 12
 *         ...
 *         RF channel 38: 2478 MHz -> channel 36
 *         RF channel 39: 2480 MHz -> channel 39
 *
 *         For the channel 37, 38 and 39 (RF channel 0, 12, 39):
 *          - The crc_init value should always be 0x555555.
 *          - There is no encryption.
 *          - The channel increment is dedicated, the channel sequence is:
 *            37 -> 38 -> 39 -> 37 -> ... while for the other channels is:
 *            0 -> 1 -> ... -> 36 -> 0 -> ...
 *            There is no channel map for these three channels.
 *            Valid values for packet length for these channels are from 6 to 37.
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  channel: frequency channel. From 0 to 39.
 * @param  channel_increment: determines the hoping value.
 * @retval None
 */
void RADIO_SetChannel(uint8_t StateMachineNo, uint8_t channel, uint8_t channel_increment) 
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo)); 
  assert_param(IS_RFCHANNEL_VALID(channel)); 

  MODIFY_REG((bluedata + StateMachineNo)->BYTE0,STATEMACH_BYTE0_UCHAN_Msk,channel);
  /*if TxRxPack.incchan = 0, then remap_chan is used as physical channel*/
  MODIFY_REG((bluedata + StateMachineNo)->BYTE1,STATEMACH_BYTE1_REMAP_CHAN_Msk,channel);
  (bluedata + StateMachineNo)->HOPINCR = channel_increment;
  return;
}

/**
 * @brief  This routine sets the NetworkID and the CRC init.
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  NetworkID: The NetworkID is the ID of the device.
 *         The user shall ensure that the NetworkID meets the following requirements:
 *           - It shall have no more than six consecutive zeros or ones.
 *           - It shall not have all four octets equal.
 *           - It shall have no more than 24 transitions.
 *           - It shall have a minimum of two transitions in the most significant six bits.   
 * @param  crc_init: CRC initilization value.
 *         This value must be 0x555555 when channel frequency is one of these values: 37, 38, 39.
 * @retval None
 */
void RADIO_SetTxAttributes(uint8_t StateMachineNo, uint32_t NetworkID, uint32_t crc_init)
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo)); 

  (bluedata + StateMachineNo)->ACCADDR = NetworkID;
  (bluedata + StateMachineNo)->CRCINIT[0] = crc_init;
  (bluedata + StateMachineNo)->CRCINIT[1] = crc_init >> 8;
  (bluedata + StateMachineNo)->CRCINIT[2] = crc_init >> 16;
  return; 
}

/**
 * @brief  This routine sets the 40-bit receive and transmit packet count, to be used in
 *         encryption calculation.
 *         Both are pointers to char, and set the 39-bit counter + 1-bit MSB as defined in the
 *         Bluetooth Low Energy spec. One is for transmit packets, the other is for receive packets.
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  count_tx: 40-bit transmit packet count, to be used in encryption nounce calculation.
 * @param  count_rcv: 40-bit receive packet count, to be used in encryption nounce calculation.
 * @retval None
 */
void RADIO_SetEncryptionCount(uint8_t StateMachineNo, uint8_t *count_tx, uint8_t *count_rcv) 
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));
 
  for(uint8_t i = 0; i < 5; i++) {
    (bluedata + StateMachineNo)->PCNTRCV[i] = count_rcv[i];
    (bluedata + StateMachineNo)->PCNTTX[i] = count_tx[i];
  }
  return; 
}

/**
 * @brief  This routines sets the 8-byte encryption initial vector, and the 16-byte encryption key.
 *         The definition of the encryption key and its initial value is according the Bluetooth Low Energy spec.
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  enc_iv: 8-byte encryption initial vector.
 * @param  enc_key: 16-byte encryption key.
 * @retval None
 */
void RADIO_SetEncryptionAttributes(uint8_t StateMachineNo, uint8_t *enc_iv, uint8_t *enc_key) 
{   
  uint8_t i = 0;
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));
  
  for(i = 0; i < 8; i++) {
    (bluedata + StateMachineNo)->ENCRYPTIV[i] = enc_iv[i];
    (bluedata + StateMachineNo)->ENCRYPTK[i] = enc_key[i];
  }
  for(i = 8; i < 16; i++) {
    (bluedata + StateMachineNo)->ENCRYPTK[i] = enc_key[i];
  }
  
  return; 
}

/**
 * @brief  Set the maximum length of a received packet. 
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  MaxReceivedLength: Upper limit for the lenght of a received packet.
 *                            From 0 to 255 bytes.
 * @retval None
 */
void RADIO_SetMaxReceivedLength(uint8_t StateMachineNo, uint8_t MaxReceivedLength)
{
  (bluedata+StateMachineNo)->MAXRECEIVEDLENGTH = MaxReceivedLength;
  return;
}

/**
 * @brief  Initializes the time between back-to-back radio transmissions.
 * @param  back_to_back_time: time between two packets if wakeupTimer is not used. Resolution is 1 us.
 * @retval None
 */
void RADIO_SetBackToBackTime(uint32_t back_to_back_time)
{
  globalParameters.back2backTime = back_to_back_time;
  return;
}


/**
 * @brief Phy selection
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  phy:
 *         0x0  PHY is not coded 1Mbps
 *         0x1  PHY is not coded 2Mbps
 *         0x4  PHY is coded 1Mbps with S=8
 *         0x6  PHY is coded 1Mbps with S=2
 * @retval None
 */
void RADIO_SetPhy(uint8_t StateMachineNo, uint8_t phy)
{
  assert_param(IS_PHY_VALID(phy));
  
  MODIFY_REG((bluedata + StateMachineNo)->BYTE3,STATEMACH_BYTE3_TXPHY_Msk,phy);
  MODIFY_REG((bluedata + StateMachineNo)->BYTE3,STATEMACH_BYTE3_RXPHY_Msk,phy<<4);

  return;
}

/**
 * @brief  This routine turns encrypt ON and OFF. When the encryption is enabled, the hardware will add 4 bytes
 *         at the end of the packet as MIC (Message Authentication Code). So the user need to add 4 byte to the
 *         length of the packet. The parameters enable the encryption for both. There are two separated parameters
 *         for this function just compliance with previous version of the driver.
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  EncryptFlagTx: DISABLE: encryption is turned OFF for both TX and RX operations.
 *              ENABLE: encryption is turned OFF for both TX and RX operations.
 *         This parameter can be: ENABLE or DISABLE.
 * @param  EncryptFlagRcv: encryption is turned OFF for both TX and RX operations.
 *              ENABLE: encryption is turned OFF for both TX and RX operations.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RADIO_SetEncryptFlags(uint8_t StateMachineNo, FunctionalState EncryptFlagTx, FunctionalState EncryptFlagRcv)
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));
  assert_param(IS_FUNCTIONAL_STATE(EncryptFlagTx));
  assert_param(IS_FUNCTIONAL_STATE(EncryptFlagRcv));
  
  if(EncryptFlagTx==ENABLE || EncryptFlagRcv==ENABLE)
  {
    (bluedata + StateMachineNo)->BYTE2 |= STATEMACH_BYTE2_ENCRYPTON_Msk;
    (bluedata + StateMachineNo)->BYTE35 |= STATEMACH_BYTE35_INTENCERROR_Msk;
  }
  else
  {
    (bluedata + StateMachineNo)->BYTE2 &= (~STATEMACH_BYTE2_ENCRYPTON_Msk);
  }
  (bluedata + StateMachineNo)->BYTE35 |= STATEMACH_BYTE35_INTRXOVERFLOWERROR_Msk;
  return;
}

/**
 * @brief  Set the receive window length.
 *         Define the maximum duration to stay in reception without any preamble
 *         and access address detection.
 * @param  ReceiveTimeout: receive window length in microseconds.
 * @retval None
 */
void RADIO_SetGlobalReceiveTimeout(uint32_t ReceiveTimeout)
{
  /* Set the Rx window Timeout expressed as: 4^(RCVTIMEOUT_19_18)*RCVTIMEOUT_17_0 */
  if(ReceiveTimeout < 0x40000) {
    blueglob->RCVTIMEOUT[0] =   (ReceiveTimeout)       & 0x000000FF ;
    blueglob->RCVTIMEOUT[1] =   (ReceiveTimeout >> 8)  & 0x000000FF ;
    blueglob->RCVTIMEOUT[2] =   (ReceiveTimeout >> 16) & 0x00000003 ;
  }
  else if(ReceiveTimeout < 0x100000) {
    blueglob->RCVTIMEOUT[0] =   (ReceiveTimeout >> 2)  & 0x000000FF ;
    blueglob->RCVTIMEOUT[1] =   (ReceiveTimeout >> 10) & 0x000000FF ;
    blueglob->RCVTIMEOUT[2] =   (ReceiveTimeout >> 18) & 0x00000003 ;
    
    blueglob->RCVTIMEOUT[2] |= 0x04;
  }
  else if(ReceiveTimeout < 0x400000) {
    blueglob->RCVTIMEOUT[0] =   (ReceiveTimeout >> 4)  & 0x000000FF ;
    blueglob->RCVTIMEOUT[1] =   (ReceiveTimeout >> 12) & 0x000000FF ;
    blueglob->RCVTIMEOUT[2] =   (ReceiveTimeout >> 20) & 0x00000003 ;
    
    blueglob->RCVTIMEOUT[2] |= 0x08;  
  }
  else if(ReceiveTimeout < 0x1000000) {
    blueglob->RCVTIMEOUT[0] =   (ReceiveTimeout >> 6)  & 0x000000FF ;
    blueglob->RCVTIMEOUT[1] =   (ReceiveTimeout >> 14) & 0x000000FF ;
    blueglob->RCVTIMEOUT[2] =   (ReceiveTimeout >> 22) & 0x00000003 ;
    
    blueglob->RCVTIMEOUT[2] |= 0x0C; 
  }
  else {
    /* error */
  }
}

/**
 * @brief  This routine should be called after writing/modifying an action packet, and before it
 *         is executed via either the API mechanism, or the next mechanism.
 * @param  p: pointer to action packet.
 * @retval None
 */
void RADIO_SetReservedArea(ActionPacket *p)
{  
  uint32_t relTimeout;
  
  /*Init to 0 the TxRxPack*/
  Osal_MemSet((void *)(&(p->trans_packet)), 0U, sizeof(p->trans_packet));

  /*Set the TxRxPack for the next transaction. The list cannot be empty.
  At least,it can be composed by one only packet that points to itself*/
  p->trans_packet.NEXTPTR = BLUE_STRUCT_PTR_CAST(&(p->trans_packet));

  /* Set the buffer that contains the values to send or that stores 
  the data received */
  p->trans_packet.DATAPTR = BLUE_DATA_PTR_CAST(p->data);
  
  /* Compensate the radio setup time from the back2back time */
  relTimeout = globalParameters.back2backTime - 70;
    
  /*Check if there is some action to perform next*/
//  if (p->next_false || p->next_true){ /* Host timer workaround */
    /* Set the Timeout for the Timer2 */
  p->trans_packet.TIMER2[0] = relTimeout & 0xFF;
  p->trans_packet.TIMER2[1] = (relTimeout >> 8) & 0xFF;
  p->trans_packet.BYTE14 = (relTimeout >> 16) & TXRXPACK_BYTE14_TIMER2_19_16_Msk;
  /*Enable relative timer*/
  p->trans_packet.BYTE14 |= TXRXPACK_BYTE14_TIMER2EN_Msk;
//  }
  
  /* TrigDone or TrigReceive */
  if((p->ActionTag & TIMESTAMP_POSITION) == 0) {
    p->trans_packet.BYTE14 |= TIMESTAMP_POSITION_LASTBIT;
  }
  else {
    p->trans_packet.BYTE14 |= TIMESTAMP_POSITION_ACCESSADDRESS;
  }
  
  p->trans_packet.BYTE4 |= TXRXPACK_BYTE4_KEEPSEMAREQ_Msk |\
                           (p->ActionTag & INC_CHAN) |\
                           (p->ActionTag & PLL_TRIG);

  p->trans_packet.BYTE5 |= (p->ActionTag & WHITENING_DISABLE) |\
                            TXRXPACK_BYTE5_TXDATAREADY_Msk |\
                            TXRXPACK_BYTE5_ALLTABLEREADY_Msk;
  
  /* Enable all interrupts */
  p->trans_packet.BYTE15 = TXRXPACK_BYTE15_INT_EN_Msk; 
  
    /* By Default the next action is considered as next_true */
  if((p->next_true->ActionTag & TXRX) != 0) {
    /* Set the type of the next activity */ 
    p->trans_packet.BYTE5 |= TXRXPACK_BYTE5_NEXTTXMODE_Msk;
  }

  p->trans_config = 0; // Rx  
  if( (p->ActionTag & TXRX) != 0) {
    p->trans_config = STATEMACH_BYTE0_TXMODE_Msk; // Tx
  }
  return ;
}


/**
 * @brief  This routine should be called for the first actionPacket that needs to be scheduled
 *         on the radio. For it to work OK, the WakeupTime should be valid.
 *         Subsequent packets can be dispatched using the same process, or by providing non-NULL pointers
 *         to the next_true and next_false pointers of the ActionPacket.
 * @param  p: pointer to action packet.
 * @retval uint8_t with following values:
 *          - 0x00 : Success.
 *          - 0xC4 : Radio is busy, action packet has not been executed.
 */
uint8_t RADIO_MakeActionPacketPending(ActionPacket *p)
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t time;
  uint32_t dummyTime;
  if(RADIO_GetStatus(&dummyTime) == BLUE_IDLE_0)
  {
    uint8_t  statemachineNo;
    BlueTransStruct *p1 ; 
    
    /* timer2 off */
    TIMER_DISABLE_TIMER12;
    
    statemachineNo = 0x7F & p->StateMachineNo;
    
    blueglob->BYTE4 = (p->StateMachineNo | GLOBAL_BYTE4_ACTIVE_Msk);
      
    p1= &p->trans_packet;
    (bluedata + statemachineNo)->RCVPOINT = BLUE_STRUCT_PTR_CAST(p1);
    (bluedata + statemachineNo)->TXPOINT = BLUE_STRUCT_PTR_CAST(p1);
    (bluedata + statemachineNo)->MAXRECEIVEDLENGTH = p->MaxReceiveLength;
    
    globalParameters.current_action_packet = p;
    
    MODIFY_REG((bluedata + statemachineNo)->BYTE0,STATEMACH_BYTE0_TXMODE_Msk,p->trans_config);/* Transmission or reception */
    
    /* program timer at next->wakeuptime */
    MASK_INTERRUPTS();
    if((p->ActionTag & RELATIVE ) !=0) {
      time = TIMER_GetCurrentSysTime() + TIMER_UsToSystime(p->WakeupTime);
      returnValue = HAL_VTIMER_SetRadioTimerValue(time,(p->trans_config == STATEMACH_BYTE0_TXMODE_Msk),(p->ActionTag & PLL_TRIG));
    }
    else{ /*absolute time*/
      returnValue = HAL_VTIMER_SetRadioTimerValue(p->WakeupTime,(p->trans_config == STATEMACH_BYTE0_TXMODE_Msk),(p->ActionTag & PLL_TRIG));
    }

    UNMASK_INTERRUPTS();
  }
  else {
    returnValue = RADIO_BUSY_C4;
  }
  return returnValue;
}


/**
 * @brief  Initializes the radio.
 * @retval None
 */
void RADIO_Init(void)
{     
  DISABLE_INTERRUPT(BLE_TX_RX_IRQn);
  
  /*Disable the controller sequencer and radio timers*/
  blueglob->BYTE4 = BLUE_IDLE_0;
  TIMER_DISABLE_RADIO_TIMERS;
    
  /*Set InitDelay*/
  blueglob->WAKEUPINITDELAY = INITDELAY_WAKEUP;
  blueglob->TIMER12INITDELAYCAL = INITDELAY_TIMER12_CAL;
  blueglob->TIMER2INITDELAYNOCAL = INITDELAY_TIMER2_NOCAL;

  /*Set Init_radio_delay*/
  blueglob->TRANSMITCALDELAYCHK = DELAYCHK_TRANSMIT_CAL;
  blueglob->TRANSMITNOCALDELAYCHK = DELAYCHK_TRANSMIT_NOCAL;
  blueglob->RECEIVECALDELAYCHK = DELAYCHK_RECEIVE_CAL;
  blueglob->RECEIVENOCALDELAYCHK = DELAYCHK_RECEIVE_NOCAL;

  /*Set ConfigEndDuration*/
  blueglob->CONFIGENDDURATION = CONFIG_END_DURATION;

  /*Set DataInit phase start*/
  blueglob->TXDATAREADYCHECK = CHECK_TXDATAREADY;

  /*TX parameters init*/
  blueglob->TXREADYTIMEOUT = TXREADY_TIMEOUT;
  blueglob->TXDELAYSTART = TXDELAY_START;
  blueglob->BYTE15 = TXDELAY_END & GLOBAL_BYTE15_TXDELAYEND_Msk;
  
  /*RX parameter init*/
  RADIO_SetGlobalReceiveTimeout(RCV_TIMEOUT);
  RADIO_SetTxPower(MAX_OUTPUT_RF_POWER);
  RADIO_SetEncryptFlags(0, DISABLE, DISABLE);
  
  globalParameters.back2backTime = BACK_TO_BACK_TIME;
  globalParameters.tone_start_stop_flag = 0;
  
  /*Clear all interrupts of the BLUE Controller*/
  uint32_t int_val_tmp = BLUE->INTERRUPT1REG;
  BLUE->INTERRUPT1REG = int_val_tmp;

  /*BLE wake up IRQ Status clearing and enable*/
  WAKEUP->WAKEUP_BLE_IRQ_STATUS |= 1;
  WAKEUP->WAKEUP_BLE_IRQ_ENABLE |= 1;
  
  ENABLE_INTERRUPT(BLE_TX_RX_IRQn);

  /* If the device is configured with 
     System clock = 64 MHz and BLE clock = 16 MHz
     a register read is necessary to end fine  
     the clear interrupt register operation,
     due the AHB down converter latency */ 
  int_val_tmp = BLUE->INTERRUPT1REG;

  return;
}

/**
 * @brief  Get the status of the radio and if it is active
 *         the last programmed value in MTU.
 * @param  time: where to store the last value programmed.
 * @retval 0 if the radio controller is IDLE or no timer has been programmed
 * @retval 1 if the radio is ACTIVE and a radio timer has been programmed 
 */
uint8_t RADIO_GetStatus(uint32_t *time)
{
  uint8_t retValue = BLUE_IDLE_0;
  if((blueglob->BYTE4 & GLOBAL_BYTE4_ACTIVE_Msk) != 0)
  {   
    retValue = TIMER_GetRadioTimerValue(time);
  }
  return retValue;
}

/**
 * @brief  Configures the transmit power level.
 * @param  PowerLevel: power level which should set to this value.
 *         See the documentation inside the datasheet.
 * @retval None
 */
void RADIO_SetTxPower(uint8_t PowerLevel) 
{
  /* Check the parameters */
  assert_param(IS_POWERLEVEL_VALID(PowerLevel)); 
  
  for(int n = 0; n <STATEMACHINE_COUNT ; n++) {
    (bluedata+n)->PAPOWER = PowerLevel;
  }
  return;
}


/**
 * @brief  Restore default preamble length to one byte.
 * @param  StateMachineNo: state machine number in multi state. 
 * @retval None
 */
void RADIO_SetDefaultPreambleLen(uint8_t StateMachineNo) 
{
  (bluedata+StateMachineNo)->BYTE34 &= ~(STATEMACH_BYTE34_ENAPREAMBLEREP_Msk);
  return;
}

/**
 * @brief  Set how many times repeat the preamble.
 * @param  StateMachineNo: state machine number in multi state.
 * @param  PreaLen: preamble length in byte for coded or uncoded phy.
 * @retval None
 */
void RADIO_SetPreambleRep(uint8_t StateMachineNo, uint8_t PreaRep) 
{
  /* Check the parameters */
   assert_param(IS_PREALEN_VALID(PreaRep)); 

  (bluedata+StateMachineNo)->BYTE34 |= STATEMACH_BYTE34_ENAPREAMBLEREP_Msk;
  (bluedata+StateMachineNo)->BYTE34 |= (PreaRep & STATEMACH_BYTE34_PREAMBLEREP_Msk);
  return;
}

/**
 * @brief  Enable or disable the CRC hardware functionality.
 * By default the CRC hardware feature is enabled. So, it can be enabled again
 * if it has been disabled.
 * If disabled, the CRC will be neither checked in reception nor appended in transmission.
 * @warning ALPHA version. In reception just ignore the CRC error and don't use this feature.
 * @param  StateMachineNo: state machine number in multi state. 
 * @param  hwCRC:
 *         - ENABLE: enable the CRC hardware feature.
 *         - DISABLE: disable the CRC hardware feature. 
 * @retval None
 */
void RADIO_DisableCRC(uint8_t StateMachineNo, FunctionalState hwCRC) 
{
  if(hwCRC != DISABLE)
  {
    (bluedata+StateMachineNo)->BYTE34 &= ~STATEMACH_BYTE34_DISABLECRC_Msk;
  }
  else
  {
    (bluedata+StateMachineNo)->BYTE34 |= STATEMACH_BYTE34_DISABLECRC_Msk;
  }
  return;
}

/**
 * @brief  Starts tone transmission on selected channel.
 *         This API is dedicated for test and destroys context and multistate.
 *         So, after calling this function the radio should be re-initialized.
 * @param  RF_Channel: radio frequency channel number from 0 to 39.
 * @param  powerLevel: power level which should set.
 * @param  freq_offset: Specify if the tone must be emitted with an offset from the channel center frequency.
 *         If 0, the tone is emitted at the channel center frequency.
 *         If 1 or 2, the device will continuously emit the tone at the center
 *         frequency plus or minus 250 kHz respectively..
 * @retval None
 */
uint8_t RADIO_StartTone(uint8_t RF_Channel, uint8_t powerLevel, uint8_t freq_offset)
{
  /* Check the parameters */
  assert_param(IS_RFCHANNEL_VALID(RF_Channel)); 
  assert_param(IS_POWERLEVEL_VALID(powerLevel));
  assert_param(IS_FREQOFFSET_VALID(freq_offset)); /*TBR*/
  
  uint8_t retVal;
  uint32_t dummyTime;
  
  if (globalParameters.tone_start_stop_flag != 0U)
  {        
    retVal = 1;
  }
  else
  {
    if ((RF_Channel >= 40U) || (freq_offset>2U)) /*TBR*/
    {  
      retVal = 1;
    }
    else
    {
      if (RADIO_GetStatus(&dummyTime) == BLUE_IDLE_0)
      {
        globalParameters.tone_start_stop_flag = 1;
        /* [EM:] Calculate the synt divide factor for 16 MHz quarts and +250 kHz offset wrt the channel center frequency
        *  Algorithmically MAK = F_rf*(2^20)/32 = F_rf*(2^15)
        *  With F_rf = (2402+2*RF_Channel)+0.25 MHz
        *  K corresponds to b19-b0  of MAK
        *  A corresponds to b22-b20 of MAK
        *  M corresponds to b27-b23 of MAK
        */
        uint32_t kHz_250_scaled = 8192; // = 0.250*2^20/32
        uint32_t MAK = ((2402UL+2UL*RF_Channel)<<15);
        
        if (freq_offset == 1U)
        {
          MAK += kHz_250_scaled;
        }
        else if (freq_offset == 2U)
        {
          MAK -= kHz_250_scaled;
        }
        else
        {
        }        
        
        uint8_t  M  = ((uint8_t)(MAK>>23)&0x1FU);
        uint8_t  A  = ((uint8_t)(MAK>>20)&0x07U);
        uint32_t K = (MAK&0x000FFFFFUL)+1UL;
        
        uint32_t MOD3_DIG_TEST = (M<<3) | (A & 0x7U);
        uint32_t MOD2_DIG_TEST = (K>>12) & 0xFFU;
        uint32_t MOD1_DIG_TEST = (K>> 4) & 0xFFU;
        uint32_t MOD0_DIG_TEST = ((K&0x0FU)<<4) | 0x09U;
        uint32_t RADIO_FSM_USR = ((powerLevel)<<3) | 0x06;
        
        RRM->RADIO_FSM_USR = RADIO_FSM_USR;    
        RRM->MOD3_DIG_TST = MOD3_DIG_TEST;
        RRM->MOD2_DIG_TST = MOD2_DIG_TEST;
        RRM->MOD1_DIG_TST = MOD1_DIG_TEST;
        RRM->MOD0_DIG_TST = MOD0_DIG_TEST;
        
        /* Take control of the radio FSM through the test bus */
        RRM->DTB5_DIG_ENG = 0x09;
        uint32_t* rrm_udra_test = ((uint32_t *)&RRM->RRM_CTRL) + 0x01;
        *rrm_udra_test = 0x03;
        RRM->DTB5_DIG_ENG = 0x39;
        while (RRM->FSM_STATUS_DIG_OUT != 0x04);
        RRM->DTB5_DIG_ENG = 0x3B;
        retVal = 0;
      }
      else
      {
        retVal = 1;
      }
    }
  }
  return retVal;
}

/**
 * @brief  This routine starts tone transmission.
 *         This API is dedicated for test and destroys context and multistate.
 *         So, after calling this function the radio should be re-initialized.
 * @param  None
 * @retval None
 */
uint8_t RADIO_StopTone()
{
  uint8_t retVal;
  
  if (globalParameters.tone_start_stop_flag != 0U)
  {
    globalParameters.tone_start_stop_flag = 0;
    /* Release control of the radio FSM through the test bus */
    RRM->DTB5_DIG_ENG = 0x00;
    uint32_t* rrm_udra_test = ((uint32_t *)&RRM->RRM_CTRL) + 0x01;
    *rrm_udra_test = 0x00;
    retVal = 0;
  }
  else
  {
    retVal = 1;
  }
  return retVal;
}


/**
 * @brief  Encrypts plain text data using AES encryption with given input key and
 *         128 bit block size
 * @param  Key: encryption key to be used.
 * @param  plainData: text data to be encrypted.
 * @param  cypherData: contains the encrypted data.
 * @retval None
 */
void RADIO_EncryptPlainData(uint8_t *Key, 
                            uint8_t *plainData,
                            uint8_t *cypherData)
{   
  uint32_t key[4] ;
  uint32_t cleartext[4] ;
  uint32_t ciphertext[4] ;
  volatile uint32_t ii ;
  
  for(uint8_t i = 0; i < 4; i++) {
    key[i] = ((uint32_t)Key[i*4]) | ((uint32_t)Key[i*4+1])<<8 | ((uint32_t)Key[i*4+2])<<16 | ((uint32_t)Key[i*4+3])<<24;
    cleartext[i] = ((uint32_t)plainData[i*4]) | ((uint32_t)plainData[i*4+1])<<8 | ((uint32_t)plainData[i*4+2])<<16 | ((uint32_t)plainData[i*4+3])<<24;
  }
  
  BLUE->MANAESKEY0REG = key[3];
  BLUE->MANAESKEY1REG = key[2];
  BLUE->MANAESKEY2REG = key[1];
  BLUE->MANAESKEY3REG = key[0];
  
  BLUE->MANAESCLEARTEXT0REG = cleartext[3];
  BLUE->MANAESCLEARTEXT1REG = cleartext[2];
  BLUE->MANAESCLEARTEXT2REG = cleartext[1];
  BLUE->MANAESCLEARTEXT3REG = cleartext[0];
  
  BLUE->MANAESCMDREG = 1;

  ii = 0 ;
  while((BLUE->MANAESSTATREG == 0) && ii < 100)
  { 
    ii++;
  }
  
  ciphertext[0] = BLUE->MANAESCIPHERTEXT3REG;
  ciphertext[1] = BLUE->MANAESCIPHERTEXT2REG;
  ciphertext[2] = BLUE->MANAESCIPHERTEXT1REG;
  ciphertext[3] = BLUE->MANAESCIPHERTEXT0REG;

  for(uint8_t i = 0; i < 4; i++) {
    cypherData[i*4] = ((uint8_t)ciphertext[i]);
    cypherData[i*4+1] = (uint8_t)(ciphertext[i]>>8);
    cypherData[i*4+2] = (uint8_t)(ciphertext[i]>>16);
    cypherData[i*4+3] = (uint8_t)(ciphertext[i]>>24);
  }
  
  return ;
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

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
