/**
******************************************************************************
* @file    ble_controller_bluenrg_lp.c
* @author  AMS - RF Application Team
* @brief   This file provides implementation of BLE controller interface.
*          WARNING: This module is used by Bluetooth LE stack. Do not use this
*          module while Bluetooth LE stack is active.
*
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
#include "ble_controller.h"
#include "ble_controller_bluenrg_lp.h"

/** @defgroup BLE_Controller_BlueNRG_LP  BLE Manager
* @{
*/

/** @defgroup BLE_Controller_BlueNRG_LP_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup BLE_Controller_BlueNRG_LP_Private_Defines Private Defines
* @{
*/

#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
__disable_irq(); \
  /* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

/**
* @}
*/

/** @defgroup BLE_Controller_BlueNRG_LP_Private_Variables Private Variables
* @{
*/


/**
* @}
*/

/** @defgroup BLE_Controller_BlueNRG_LP_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup BLE_Controller_BlueNRG_LP_Private_FunctionPrototypes Private Function Prototypes
* @{
*/


/**
* @}
*/

/** @defgroup BLE_Controller_BlueNRG_LP_Private_Functions Private Functions
* @{
*/

/**
* @}
*/

/** @defgroup BLE_Controller_BlueNRG_LP_Public_Functions Public Functions
* @{
*/

BLECNTR_ResultStatus BLECNTR_Init(void)
{


  return BLECNTR_SUCCESS;
}


BLECNTR_ResultStatus BLECNTR_Deinit(void)
{

  return BLECNTR_SUCCESS;
}


/* ------------------------------------------------------------------------------
*  volatile uint32_t hot_table_radio_config_u32[]
*
*  Hot table radio configuration storage.
*  This variable is only used during the smart power management 
*  procedure 
*  ------------------------------------------------------------------------------ */
/* Round up HOT_TABLE_SIZE to an integer number of words then add 4 words for table management pointers */
volatile uint32_t hot_table_radio_config_u32[((HOT_TABLE_SIZE+3)>>2)+4]= {0x00};

 
/* Moved from the Stack library to the application environment
 * 
 */
void BLECNTR_InitGlobal(void)
{
    uint8_t index; 
    uint8_t udra_flag = 0; 
    
    BLECNTR_GlobDisableBlue();
    
    /* Configure the timing parameters for the 1st initialization phase*/
    BLECNTR_GlobSetWakeupinitdelay(WAKEUPINITDELAY_MT);
    BLECNTR_GlobWriteTimer12initdelaycal(TIMER12_INIT_DELAY_CAL);
    BLECNTR_GlobWriteTimer2initdelaynocal(TIMER2_INIT_DELAY_NO_CAL);

     /* Configure the timing parameters for the 2nd initialization phase*/
    BLECNTR_GlobWriteRcvdelay(RECEIVE_CAL_DELAY_CHECK);
    BLECNTR_GlobWriteRcvdelay1(RECEIVE_NO_CAL_DELAY_CHECK);
    BLECNTR_GlobSetInitRadioDelayTxCal(TRANSMIT_CAL_DELAY_CHECK);
    BLECNTR_GlobSetInitRadioDelayTxNocal(TRANSMIT_NO_CAL_DELAY_CHECK);

    
    /* Initial and final TX delays: control the on-air start time of the TX packet
    *  and the length of the packet "tail" after last bit is transmitted
    */
    BLECNTR_GlobWriteTxdelay(TX_DELAY_START);
    BLECNTR_GlobWriteTxdelayEnd(TX_DELAY_END);
    
    /* Timeout for TX ready signal from the radio FSM after the 2nd init phase
    *  has expired
    */
    BLECNTR_GlobWriteTxReadyTimeout(TX_READY_TIMEOUT);

    /* Timing for the various programming phases of the radio, modem and memory
    *  pointers.
    */ 
    BLECNTR_GlobWriteConfigEnd(CONFIG_END_DURATION);
    BLECNTR_GlobWriteTxDataReadyCheck(TX_DATA_READY_CHECK);

    BLECNTR_GlobSetChkflagautoclearena();                /* Enable autoclear of the ACTIVE bit in the GlobalStatMach */
    BLECNTR_GlobEnableIntnoactivelerrorInt();           /* Enable Interrupt at the timer trig event, when Active bit is not set */

    BLECNTR_GlobSetDefaultAntennaid(0x01U);

    if (((LL_SYSCFG_GetDeviceVersion()<<4)|LL_SYSCFG_GetDeviceRevision()) >= LL_BLUENRG_LP_CUT_20) {
      udra_flag = 1;
    }
    
  if (udra_flag) {
      /* The commands in the hot table start at word 4
       * The words 0 t0 2 are used to point to the command list
       * for the various trigger events, word 3 is a null command
       * (see function BLECNTR_SetRadioConfigData)
       */
      uint8_t *hot_table_radio_config = (uint8_t *)&hot_table_radio_config_u32[4];
      index = 0;
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_CBIAS1_ANA_ENG;
      hot_table_radio_config[index++] = RRM->CBIAS1_ANA_ENG;
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_CBIAS0_ANA_ENG;
      hot_table_radio_config[index++] = RRM->CBIAS0_ANA_ENG;
    
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_RXADC_ANA_USR;
      hot_table_radio_config[index++] = RRM->RXADC_ANA_USR;    
     
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_AFC1_DIG_ENG;
      hot_table_radio_config[index++] = RRM->AFC1_DIG_ENG;
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_CR0_DIG_ENG;
      hot_table_radio_config[index++] = RRM->CR0_DIG_ENG;
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_CR0_LR;
      hot_table_radio_config[index++] = RRM->CR0_LR;
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_LR_RSSI_THR_DIG_ENG;
      hot_table_radio_config[index++] = RRM->LR_RSSI_THR_DIG_ENG;
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_LR_PD_THR_DIG_ENG;
      hot_table_radio_config[index++] = RRM->LR_PD_THR_DIG_ENG;
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_LR_AAC_THR_DIG_ENG;
      hot_table_radio_config[index++] = RRM->LR_AAC_THR_DIG_ENG;
      hot_table_radio_config[index++] = 0x01;
      hot_table_radio_config[index++] = RRM_VIT_CONF_DIG_ENG;
      hot_table_radio_config[index++] = RRM->VIT_CONF_DIG_ENG;
      hot_table_radio_config[index++] = 0x00;
    }
    
    hot_table_radio_config_u32[0] = (uint32_t)(&hot_table_radio_config_u32[4]); /* Point to Port 0 command list 1 executed when Wakeup timer triggers */
    hot_table_radio_config_u32[1] = (uint32_t)(&hot_table_radio_config_u32[4]); /* Point to Port 0 command list 2 executed when Timer1 triggers       */
    hot_table_radio_config_u32[2] = (uint32_t)(&hot_table_radio_config_u32[3]); /* Point to Port 0 command list 3 executed when Timer2 triggers       */
    hot_table_radio_config_u32[3] = 0x00000000;                /* Null command */
    BLECNTR_GlobSetRadioConfigP(hot_table_radio_config_u32);
    BLECNTR_GlobReloadRadioConfigP();
    BLECNTR_GlobEnableOverrunAct2Int();
}

/* Calculate the Timeout to be programmed on Timer2 to obtain a give T_IFS
 * when the next packet is a transmit one
*/
uint32_t BLECNTR_GeTimer2TimeoutForIfs(uint32_t T_Ifs, BLECNTR_Transaction Transaction, BOOL Cal_Enabled)
{
    uint32_t Timeout = T_Ifs;
    uint32_t Tx_Delay_Comp;
    uint32_t Init_Delay;
    
    if(Transaction == BLECNTR_RxTx)
    {
        /* The correction values below have been determined by sniffer
         * T_IFS measurements in connection, initiating and active
         * scanning
         */
        const int32_t Adjust_Value = 4;
        Tx_Delay_Comp = (TX_DELAY_START>>3) + Adjust_Value;
    }
    else if(Transaction == BLECNTR_TxRx)
    {
        /* The correction values below have been set to correspond to the hardcoded
         * values used in prrevious versions of the stack.
         * They could be optimized after careful analysis of timing margins and
         * AGC behavior.
         */
        const int32_t Adjust_Value = 4;
        Tx_Delay_Comp = (TX_DELAY_END>>3) + Adjust_Value;
    }
    else if(Transaction == BLECNTR_TxTx)
    {
        /* The correction values below have been determined by sniffer
         * T_IFS measurements in extended advertising (AUX_CHAIN_IND)
         */
        const int32_t Adjust_Value = 1;
        Tx_Delay_Comp = ((TX_DELAY_START + TX_DELAY_END)>>3) + Adjust_Value;
    }
    else
    {
        Tx_Delay_Comp = 0;
    }

    if((Transaction == BLECNTR_RxTx) || (Transaction == BLECNTR_TxTx))
    {
        if(Cal_Enabled == TRUE)
        {
            Init_Delay = TIMER12_INIT_DELAY_CAL + RADIO_FSM_TX_DELAY_CAL;
        }
        else
        {
            Init_Delay = TIMER2_INIT_DELAY_NO_CAL + RADIO_FSM_TX_DELAY_NO_CAL;
        }
    }
    else if((Transaction == BLECNTR_TxRx) || (Transaction == BLECNTR_RxRx))
    {
        /* The calculation below is based on the following sequence:
         * - When Timer2 expires the sequencer performs the 1st initalization step and sends
         *   a take_req to the radio
         * - When TIMER12_INIT_DELAY_CAL or TIMER2_INIT_DELAY_NO_CAL expire the sequencer sends
         *   a tx_rx_req to the radio
         * - When the radio FSM reaches the RX state (after RADIO_FSM_RX_DELAY_CAL or
         *   RADIO_FSM_RX_DELAY_NO_CAL) the demodulator is turned on
         *
         * The sum of Timer2 timeout +  TIMER(1)2_INIT_DELAY(_NO)_CAL + RADIO_FSM_RX_DELAY(_NO)_CAL
         * must be equal to the T IFS.
         *
         * The current calculation of Timer2 for TX-RX events is sligthly conservative
         * since it soes not consider the delay from digital modulator to antenna and from
         * antenna to digital demodulator. As a consequence the demodulator is turned on
         * a few microseconds earlier than stricty needed.
         */
        if(Cal_Enabled == TRUE)
        {
            Init_Delay = TIMER12_INIT_DELAY_CAL + RADIO_FSM_RX_DELAY_CAL;
        }
        else
        {
            Init_Delay = TIMER2_INIT_DELAY_NO_CAL + RADIO_FSM_RX_DELAY_NO_CAL;
        }
    }
    else
    {
    }

    Timeout -= (Init_Delay + Tx_Delay_Comp);
    
    return Timeout;
}

void BLECNTR_ClearInterrupt(uint32_t x)
{
    LL_RADIO_BlueSetInterrupt1RegRegister(x);
}

void BLECNTR_ClearSemareq()
{
    LL_RADIO_BlueSetClearSemaphoreRequest(0x1U);
}

uint32_t* BLECNTR_GetCipherTextPtr()
{
    return (uint32_t*)&BLUE->MANAESCIPHERTEXT0REG;
}

uint32_t* BLECNTR_GetClrTextPtr()
{
    return (uint32_t*)&BLUE->MANAESCLEARTEXT0REG;
}

uint32_t* BLECNTR_GetEncKeyPtr()
{
    return (uint32_t*)&BLUE->MANAESKEY0REG;
}

BOOL BLECNTR_GetEncryptDoneStatus()
{
    return (BOOL)!LL_RADIO_BlueGetManAESStatusBusy();
}

uint8_t BLECNTR_GetIqsamplesMissingError(void)
{
  return (uint8_t)0;
}

uint8_t BLECNTR_GetIqsamplesNumber(void)
{
  return (uint8_t)0;
}

uint8_t BLECNTR_getIqsamplesReady(void)
{
  return (uint8_t)0;
}

uint8_t BLECNTR_GetIsrLatency()
{
    return (uint8_t)LL_RADIO_BlueGetInterrupt1Latency();
}

uint32_t BLECNTR_GetTimercapture()
{
    return LL_RADIO_BlueGetTimerCapture();
}

void BLECNTR_GlobDisableBlue()
{
    LL_RADIO_GlobalDisableBlue();
}

void BLECNTR_GlobEnableBlue()
{
    LL_RADIO_GlobalEnableBlue();
}

void BLECNTR_GlobEnableIntnoactivelerrorInt()
{
   LL_RADIO_NoActiveLErrorInterrupt_Enable();
}

void BLECNTR_GlobEnableOverrunAct2Int()
{
    LL_RADIO_Active2ErrorInterrupt_Enable();
}

uint8_t BLECNTR_GlobGetDefaultAntennaid()
{
#if defined(GLOBAL_WORD6_DEFAULTANTENNAID_Msk)
    return (uint8_t)LL_RADIO_GetDefaultAntennaID();
#else
    return (uint8_t)0;
#endif
}

uint8_t BLECNTR_GlobGetWakeupinitdelay()
{
    return (uint8_t) LL_RADIO_GetWakeupInitDelay();
}

void BLECNTR_GlobReloadRadioConfigP()
{
    *(uint32_t*)(RRM_BASE + 0x10U) = 0x01U;
}

void BLECNTR_GlobSetChkflagautoclearena()
{
    LL_RADIO_ChkFlagAutoclearEnable_Enable();
}

void BLECNTR_GlobSetDefaultAntennaid(uint8_t x)
{
#if defined(GLOBAL_WORD6_DEFAULTANTENNAID_Msk)
    LL_RADIO_SetDefaultAntennaID((uint32_t)x);
#else
    /* nothing to do */
#endif
}

void BLECNTR_GlobSetInitRadioDelayTxCal(uint8_t x)
{
    LL_RADIO_SetTransmitCalDelayChk((uint32_t) x);
}

void BLECNTR_GlobSetInitRadioDelayTxNocal(uint8_t x)
{
    LL_RADIO_SetTransmitNoCalDelayChk((uint32_t) x);
}

void BLECNTR_GlobSetRadioConfigP(volatile uint32_t* x)
{
    LL_RADIO_SetRadioConfigurationAddressPointer(x[0]);
}

void BLECNTR_GlobSetWakeupinitdelay(uint8_t x)
{
    LL_RADIO_SetWakeupInitDelay((uint32_t) x);
}

void BLECNTR_GlobWriteConfigEnd(uint8_t x)
{
    LL_RADIO_SetConfigurationEndDuration((uint32_t) x);
}

void BLECNTR_GlobWritePeriodslow(uint16_t x)
{
    /* nothing to do */
}

void BLECNTR_GlobWriteRcvdelay(uint8_t x)
{
    LL_RADIO_SetReceivedCalDelayChk((uint32_t) x);
}

void BLECNTR_GlobWriteRcvdelay1(uint8_t x)
{
    LL_RADIO_SetReceivedNoCalDelayChk((uint32_t) x);
}

void BLECNTR_GlobWriteSlot(uint8_t slotNo)
{
    LL_RADIO_SetCurrentConnectionMachineNumber((uint32_t) slotNo);
}

void BLECNTR_GlobWriteTimer12initdelaycal(uint8_t x)
{
    LL_RADIO_SetTimer12InitDelayCal((uint32_t) x);
}

void BLECNTR_GlobWriteTimer2initdelaynocal(uint8_t x)
{
    LL_RADIO_SetTimer12InitDelayNoCal((uint32_t) x);
}

void BLECNTR_GlobWriteTxDataReadyCheck(uint8_t x)
{
    LL_RADIO_SetTxDataReadyCheck((uint32_t) x);
}

void BLECNTR_GlobWriteTxReadyTimeout(uint8_t x)
{
	LL_RADIO_SetTransmissionReadyTimeout((uint32_t) x);
}

void BLECNTR_GlobWriteTxdelay(uint8_t x)
{
    LL_RADIO_SetTxDelayStart((uint32_t) x);
}

void BLECNTR_GlobWriteTxdelayEnd(uint8_t x)
{
    LL_RADIO_SetTxDelayEnd((uint32_t) x);
}

uint32_t BLECNTR_IntGetIntStatusAnyHwError(uint32_t x)
{
    return (uint32_t)(x & ANY_HW_ERROR_INTERRUPT_Msk);
}

uint32_t BLECNTR_IntGetIntStatusRxOverflowError(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RXOVERFLOWERROR_Msk);
}

uint32_t BLECNTR_IntGetIntStatusBitAct2Error(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_ACTIVE2ERROR_Msk);
}

uint32_t BLECNTR_IntGetIntStatusBitTimerOverrun(uint32_t x)
{
    return 0;
}

#if defined(BLUE_STATUSREG_RCVCRCERR_Msk)
uint32_t BLECNTR_IntGetIntStatusCrcErr(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RCVCRCERR_Msk);
}
#endif

#if defined(BLUE_STATUSREG_DONE_Msk)
uint32_t BLECNTR_IntGetIntStatusDone(uint32_t x)
{
	return (uint32_t)(x & BLUE_STATUSREG_DONE_Msk);
}
#endif

#if defined(BLUE_STATUSREG_ENCERROR_Msk)
uint32_t BLECNTR_IntGetIntStatusEncErr(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_ENCERROR_Msk);
}
#endif

#if defined(BLUE_STATUSREG_RCVLENGTHERROR_Msk)
uint32_t BLECNTR_IntGetIntStatusLenErr(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RCVLENGTHERROR_Msk);
}
#endif

#if defined(BLUE_STATUSREG_NOACTIVELERROR_Msk)
uint32_t BLECNTR_IntGetIntStatusNoactiveError(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_NOACTIVELERROR_Msk);
}
#endif

#if defined(BLUE_STATUSREG_RCVOK_Msk)
uint32_t BLECNTR_IntGetIntStatusRxOk(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RCVOK_Msk);
}
#endif

#if defined(BLUE_STATUSREG_RCVTIMEOUT_Msk)
uint32_t BLECNTR_IntGetIntStatusTimeout(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RCVTIMEOUT_Msk);
}
#endif

#if defined(BLUE_STATUSREG_TIMECAPTURETRIG_Msk)
uint32_t BLECNTR_IntGetIntStatusTrigRcv(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_TIMECAPTURETRIG_Msk);
}
#endif

#if defined(BLUE_STATUSREG_PREVTRANSMIT_Msk)
uint32_t BLECNTR_IntGetIntStatusTxDone(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_PREVTRANSMIT_Msk);
}
#endif

#if defined(BLUE_STATUSREG_TXOK_Msk)
uint32_t BLECNTR_IntGetIntStatusTxOk(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_TXOK_Msk);
}
#endif


void BLECNTR_PacketClrCrcinitSel(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetCRCInitializationSelector((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x0);
}

void BLECNTR_PacketClrCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP)
{
  /* nothing to do */
}

void BLECNTR_PacketClrIncChan(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IncrementerChannel_Disable((TXRXPACK_TypeDef*)packetP);
}

void BLECNTR_PacketClrPllTrig(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetCalibrationRequest((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x0);
}

void BLECNTR_PacketDisableWhitening(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetDisableWhitening((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

uint8_t BLECNTR_PacketGetCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP)
{
  return (uint8_t)0;

}

uint8_t* BLECNTR_PacketGetDataPtr(BLECNTR_TXRXPACK_TypeDef* packetP)
{
//todo mm1mm check it
    return (uint8_t*)CONV_ADR(LL_RADIO_GetDataPointer((TXRXPACK_TypeDef*)packetP));
}

void BLECNTR_PacketInitTo0(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    Osal_MemSet((void*)packetP, 0, sizeof(TXRXPACK_WORD_TypeDef));
}

void BLECNTR_PacketSetAdvPduFormat(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetAdvertise((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetCrcinitSel(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetCRCInitializationSelector((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP)
{
  /* nothing to do */
}

void BLECNTR_PacketSetDataPduFormat(BLECNTR_TXRXPACK_TypeDef* packetP)
{
     LL_RADIO_SetAdvertise((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x0);
}

void BLECNTR_PacketSetDataPtr(BLECNTR_TXRXPACK_TypeDef* packetP, void* dataP)
{
    LL_RADIO_SetDataPointer((TXRXPACK_TypeDef*)packetP, BLUE_DATA_PTR_CAST(dataP));
}

void BLECNTR_PacketSetIncChan(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IncrementerChannel_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLECNTR_PacketSetIntCrcErr(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IntRcvCRCErr_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLECNTR_PacketSetIntDone(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IntDone_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLECNTR_PacketSetIntRcvOk(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IntRcvOk_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLECNTR_PacketSetIntTimeout(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IntRcvTimeout_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLECNTR_PacketSetIntTrigRcv(BLECNTR_TXRXPACK_TypeDef* packetP)
{
  //LL_RADIO_SetIntRcvTrig((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1U);
  //INTRCVTRIG is the bit 29 of WORD3 -> todo : check it -> now there is a field called INTTIMECAMPTURE here
  LL_RADIO_SetIntTimeCapture((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1U);
}

void BLECNTR_PacketSetIntTxOk(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetIntTxOk((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetKeepsemareq(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetKeepSemaRequest((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetNextPtr(BLECNTR_TXRXPACK_TypeDef* packetP, BLECNTR_TXRXPACK_TypeDef* packetNextP)
{
    LL_RADIO_SetNextPointer((TXRXPACK_TypeDef*)packetP, (uint32_t) BLUE_STRUCT_PTR_CAST((TXRXPACK_TypeDef*)packetNextP));
}

void BLECNTR_PacketSetNextRxMode(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetNextTxMode((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x0);
}

void BLECNTR_PacketSetNextSlot(BLECNTR_TXRXPACK_TypeDef* packetP, uint8_t slot)
{
    /* nothing to do */
}

void BLECNTR_PacketSetNextTxMode(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetNextTxMode((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetNsEn(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_AutomaticSnNesnHardwareMechanism_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLECNTR_PacketSetPllTrig(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetCalibrationRequest((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetRxReady(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetAllTableDataReady((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetTimeout(BLECNTR_TXRXPACK_TypeDef* packetP, uint32_t x)
{
    LL_RADIO_SetTimer2Triggering((TXRXPACK_TypeDef*)packetP, x);
}

void BLECNTR_PacketSetTimer2Active(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_Timer2_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLECNTR_PacketSetTimerTrigDone(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetTrigDone((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetTimerTrigRcv(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetTrigRcv((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_PacketSetTxReady(BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetTransmissionDataReady((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
    LL_RADIO_SetAllTableDataReady((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLECNTR_SetRadioConfig(uint8_t* value)
{
    /* nothing to do */
}

void BLECNTR_SetRcvLen(BLECNTR_TXRXPACK_TypeDef* packetP, uint32_t rcvLen)
{
  (void)packetP;
  LL_RADIO_SetReceiveWindowTimeout((uint32_t) (rcvLen & 0xFFFFFU)); 
}


void BLECNTR_SmCteOff(uint8_t smNo)
{
  /* nothing to do */
}

void BLECNTR_SmCteOn(uint8_t smNo)
{
  /* nothing to do */
}

void BLECNTR_SmEnRadioConfig(uint8_t smNo, uint32_t enable)
{
    if(enable)
	    LL_RADIO_RadioCommandList_Enable(smNo);
	else
	    LL_RADIO_RadioCommandList_Disable(smNo);
}

void BLECNTR_SmEncOff(uint8_t smNo)
{
    LL_RADIO_Encryption_Disable(smNo);
    LL_RADIO_ReceiveEncryptionErrorInterrupt_Disable(smNo);
}

void BLECNTR_SmEncOn(uint8_t smNo)
{
    LL_RADIO_Encryption_Enable(smNo);
    LL_RADIO_ReceiveEncryptionErrorInterrupt_Enable(smNo);
}

uint32_t BLECNTR_SmGetAccessAddr(uint8_t smNo)
{
    return LL_RADIO_GetAccessAddress(smNo);
}

void BLECNTR_SmGetChannelMap(uint8_t smNo, uint8_t* chanMap)
{
    chanMap[0] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_15_0(smNo));
    chanMap[1] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_15_0(smNo) >> 8U);
    chanMap[2] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_36_16(smNo));
    chanMap[3] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_36_16(smNo) >> 8U);
    chanMap[4] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_36_16(smNo) >> 16U);
}

uint8_t BLECNTR_SmGetCteAntennaPatternLen(uint8_t smNo)
{
  return (uint8_t)0;
}

uint8_t BLECNTR_SmGetCteAodNaoa(uint8_t smNo)
{
  return (uint8_t)0;
}

uint8_t BLECNTR_SmGetCteSlotWidth(uint8_t smNo)
{
  return (uint8_t)0;
}

uint8_t BLECNTR_SmGetCteStatus(uint8_t smNo)
{
  return (uint8_t)0;
}

uint8_t BLECNTR_SmGetCteTime(uint8_t smNo)
{
  return (uint8_t)0;
}

uint32_t* BLECNTR_SmGetEncIvPtr(uint8_t smNo)
{
    return (uint32_t*)&(bluedata + smNo)->ENCRYPTIV[0];
}

uint32_t* BLECNTR_SmGetEncKeyPtr(uint8_t smNo)
{
	return (uint32_t*)&(bluedata + smNo)->ENCRYPTK[0];
}

uint8_t BLECNTR_SmGetEncStatus(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_Encryption_IsEnabled(smNo);
}

uint8_t BLECNTR_SmGetHopIncr(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetHopIncrement(smNo);
}

uint8_t BLECNTR_SmGetMode(uint8_t smNo)
{
    return LL_RADIO_TxMode_IsEnabled(smNo);
}

uint8_t* BLECNTR_SmGetPrevRxPacketDataPtr(uint8_t smNo)   
{
    return (uint8_t*)CONV_ADR(BLUE_TRANS_STRUCT_PTR_CAST(LL_RADIO_GetRcvPointPrevious(smNo))->DATAPTR);
}

BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetPrevRxPacketPtr(uint8_t smNo)   
{
    return (BLECNTR_TXRXPACK_TypeDef*)BLUE_TRANS_STRUCT_PTR_CAST(CONV_ADR(LL_RADIO_GetRcvPointPrevious(smNo)));
}

uint8_t* BLECNTR_SmGetPrevTxPacketDataPtr(uint8_t smNo)   
{
    return (uint8_t*)CONV_ADR(BLUE_TRANS_STRUCT_PTR_CAST(LL_RADIO_GetTxPointPrevious(smNo))->DATAPTR);
}

BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetPrevTxPacketPtr(uint8_t smNo)  
{
    return (BLECNTR_TXRXPACK_TypeDef*)BLUE_TRANS_STRUCT_PTR_CAST(CONV_ADR(LL_RADIO_GetTxPointPrevious(smNo)));
}

uint8_t BLECNTR_SmGetRemapChan(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetRemapChannel(smNo);
}

void BLECNTR_SmGetRxCount(uint8_t smNo, uint32_t* packetCount)
{

    packetCount[0] = LL_RADIO_GetPacketCounterRx_23_0(smNo);
    packetCount[0] = packetCount[0] | ((uint32_t)LL_RADIO_GetPacketCounterRx_39_24(smNo) << 24U);
    packetCount[1] = LL_RADIO_GetPacketCounterRx_39_24(smNo) >> 8U;
}

uint8_t BLECNTR_SmGetRxPhy(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetReceptionPhy(smNo);
}

BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetTxPacketPtr(uint8_t smNo)
{
    return (BLECNTR_TXRXPACK_TypeDef*)BLUE_TRANS_STRUCT_PTR_CAST(CONV_ADR(LL_RADIO_GetTxPoint(smNo)));
}

uint8_t BLECNTR_SmGetTxPhy(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetTransmissionPhy(smNo);
}

uint8_t BLECNTR_SmGetTxPwr(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetPAPower(smNo);
}

uint8_t BLECNTR_SmGetUnmappedChan(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetUnmappedChannel(smNo);
}

void BLECNTR_SmInitTo0(uint8_t smNo)
{
  Osal_MemSet((void*)&bluedata[smNo], 0, sizeof(STATMACH_TypeDef));
  BLECNTR_SmEnRadioConfig(smNo, 0x01);
}

void BLECNTR_SmSetAccessAddr(uint8_t smNo, uint32_t x)
{
    LL_RADIO_SetAccessAddress(smNo, x);
}

void BLECNTR_SmSetChannelMap(uint8_t smNo, uint8_t* chanMap)
{
    uint32_t value = (uint32_t)chanMap[0] | ((uint32_t)chanMap[1] << 8U);
    LL_RADIO_SetUsedChannelFlags_15_0(smNo, value);
    value = (uint32_t)chanMap[2] | ((uint32_t)chanMap[3] << 8U) | ((uint32_t)chanMap[4] << 16U);
    LL_RADIO_SetUsedChannelFlags_36_16(smNo, value);
}

void BLECNTR_SmSetCrcInit(uint8_t smNo, uint32_t x)
{
  LL_RADIO_SetCRCInitializationValue(smNo, x);
}


void BLECNTR_SmSetCteAntennaPatternLen(uint8_t smNo, uint8_t antPattLen)
{
  /* nothing to do */
}

void BLECNTR_SmSetCteAntennaPatternPtr(uint8_t smNo, uint8_t* antPattP)
{
  /* nothing to do */
}

void BLECNTR_SmSetCteAoa(uint8_t smNo)
{
  /* nothing to do */
}

void BLECNTR_SmSetCteAod(uint8_t smNo)
{
  /* nothing to do */
}

void BLECNTR_SmSetCteIqsamplesPtr(uint8_t smNo, uint32_t* iqSamplesP)
{
  /* nothing to do */
}

void BLECNTR_SmSetCteMaxIqsamplesNumb(uint8_t smNo, uint8_t iqsamplesNumb)
{
  /* nothing to do */
}

void BLECNTR_SmSetCteSlotWidth(uint8_t smNo, uint32_t cteSlot)
{
  /* nothing to do */
}

void BLECNTR_SmSetCteTime(uint8_t smNo, uint8_t cteTime)
{
  /* nothing to do */
}

void BLECNTR_SmSetDataLength(uint8_t smNo, uint8_t length)
{
    LL_RADIO_SetMaximumReceiveLength(smNo, (uint32_t) length);
}

void BLECNTR_SmSetDataLengthExtnEn(uint8_t smNo)
{
    /* nothing to do */
}

void BLECNTR_SmSetHopIncr(uint8_t smNo, uint8_t x)
{
    LL_RADIO_SetHopIncrement(smNo, (uint32_t) x);
}

void BLECNTR_SmSetRemapChan(uint8_t smNo, uint8_t chan)
{
    LL_RADIO_SetRemapChannel(smNo, chan);
}

void BLECNTR_SmSetRxCount(uint8_t smNo, uint32_t* packetCount)
{
    LL_RADIO_SetPacketCounterRx_23_0(smNo, (uint32_t) packetCount[0]);
    uint32_t value = (uint32_t)(packetCount[1] << 8U) | (uint32_t)(packetCount[0] >> 24U);
    LL_RADIO_SetPacketCounterRx_39_24(smNo, value);
}

void BLECNTR_SmSetRxCountDirectionBit(uint8_t smNo)
{
    uint32_t value = LL_RADIO_GetPacketCounterRx_39_24(smNo) | 0x8000U;
    LL_RADIO_SetPacketCounterRx_39_24(smNo, value);
}

void BLECNTR_SmSetRxMode(uint8_t smNo)
{
    LL_RADIO_TxMode_Disable(smNo);
}

void BLECNTR_SmSetRxPacketPtr(uint8_t smNo, BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetRcvPoint(smNo, (uint32_t) BLUE_STRUCT_PTR_CAST((TXRXPACK_TypeDef*)packetP));
}

void BLECNTR_SmSetRxPhy(uint8_t smNo, uint8_t rxPhy)
{
    LL_RADIO_SetReceptionPhy(smNo, (uint32_t) rxPhy);
}   

void BLECNTR_SmSetTxCount(uint8_t smNo, uint32_t* packetCount)
{
    LL_RADIO_SetPacketCounterTx_31_0(smNo, (uint32_t) packetCount[0]);
    LL_RADIO_SetPacketCounterTx_39_32(smNo, (uint32_t) packetCount[1]);
}

void BLECNTR_SmSetTxCountDirectionBit(uint8_t smNo)
{
    uint32_t value =  (LL_RADIO_GetPacketCounterTx_39_32(smNo) | 0x00000080U);
    LL_RADIO_SetPacketCounterTx_39_32(smNo,  value);
}

void BLECNTR_SmSetTxMode(uint8_t smNo)
{
    LL_RADIO_TxMode_Enable(smNo);
}

void BLECNTR_SmSetTxPacketPtr(uint8_t smNo, BLECNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetTxPoint(smNo, (uint32_t) BLUE_STRUCT_PTR_CAST((TXRXPACK_TypeDef*)packetP));
}

void BLECNTR_SmSetTxPhy(uint8_t smNo, uint8_t txPhy)
{
    LL_RADIO_SetTransmissionPhy(smNo, (uint32_t) txPhy);
}

void BLECNTR_SmSetTxPwr(uint8_t smNo, uint8_t paLevel)
{
    LL_RADIO_SetPAPower(smNo, (uint32_t) paLevel);
}

void BLECNTR_SmSetUnmappedChan(uint8_t smNo, uint8_t chan)
{
    LL_RADIO_SetUnmappedChannel(smNo, (uint32_t) chan);
}

void BLECNTR_SmToggleNesn(uint8_t smNo)
{
  LL_RADIO_ToggleNextExpectedSequenceNumber(smNo);
}

void BLECNTR_SmToggleSn(uint8_t smNo)
{
    LL_RADIO_ToggleSequenceNumber(smNo);
}

void BLECNTR_StartEncrypt()
{
     LL_RADIO_BlueSetManAESCmdStart(0x1U);
}

uint32_t BLECNTR_TimeDiff(uint32_t x, uint32_t y)
{
    return (uint32_t)(x - y);
}

uint8_t BLECNTR_DemodDelaySt(uint8_t RxPHY)
{
    return (uint8_t)((LL_PHY_CODED == RxPHY) ? 0x9DU : 0x12U);
}


/**
* @}
*/

/**
* @}
*/
