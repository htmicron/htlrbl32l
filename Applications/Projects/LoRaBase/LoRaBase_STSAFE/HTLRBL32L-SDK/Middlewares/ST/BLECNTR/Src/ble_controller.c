/**
******************************************************************************
* @file    ble_controller.c
* @author  AMS - RF Application Team
* @brief   This file provides weak functions for BLE controller.
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
#include "rf_driver_ll_rng.h"
#include "rf_driver_ll_bus.h"


/** @defgroup BLE_Controller  BLE CONTROLLER
* @{
*/

/** @defgroup BLECNTR_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup BLECNTR_Private_Defines Private Defines
* @{
*/
/**
* @}
*/

/** @defgroup BLECNTR_Private_Macros Private Macros
* @{
*/
/**
* @}
*/

/** @defgroup BLECNTR_Private_Variables Private Variables
* @{
*/  
/**
* @}
*/

/** @defgroup BLECNTR_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup BLECNTR_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
/**
* @}
*/

/** @defgroup BLECNTR_Public_Functions Public Functions
* @{
*/
WEAK_FUNCTION(BLECNTR_ResultStatus BLECNTR_Init(void))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(BLECNTR_ResultStatus BLECNTR_Deinit(void))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_InitGlobal(void))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_GeTimer2TimeoutForIfs(uint32_t T_Ifs, BLECNTR_Transaction Transaction, BOOL Cal_Enabled))
{
  return 0;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_ClearInterrupt(uint32_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_ClearSemareq())
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t* BLECNTR_GetCipherTextPtr())
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t* BLECNTR_GetClrTextPtr())
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t* BLECNTR_GetEncKeyPtr())
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(BOOL BLECNTR_GetEncryptDoneStatus())
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_GetIqsamplesMissingError(void))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_GetIqsamplesNumber(void))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_getIqsamplesReady(void))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}


WEAK_FUNCTION(uint8_t BLECNTR_GetIsrLatency())
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_GetTimercapture())
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobDisableBlue())
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobEnableBlue())
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobEnableIntnoactivelerrorInt())
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobEnableOverrunAct2Int())
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_GlobGetDefaultAntennaid())
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_GlobGetWakeupinitdelay())
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobReloadRadioConfigP())
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobSetChkflagautoclearena())
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobSetDefaultAntennaid(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobSetInitRadioDelayTxCal(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobSetInitRadioDelayTxNocal(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobSetRadioConfigP(volatile uint32_t* x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobSetWakeupinitdelay(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteConfigEnd(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWritePeriodslow(uint16_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteRcvdelay(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteRcvdelay1(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteSlot(uint8_t slotNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteTimer12initdelaycal(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteTimer2initdelaynocal(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteTxDataReadyCheck(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteTxReadyTimeout(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteTxdelay(uint8_t x) )
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_GlobWriteTxdelayEnd(uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusAnyHwError(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusRxOverflowError(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusBitAct2Error(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusBitTimerOverrun(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusCrcErr(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusDone(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusEncErr(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusLenErr(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusNoactiveError(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusRxOk(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusTimeout(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusTrigRcv(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusTxDone(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_IntGetIntStatusTxOk(uint32_t x))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketClrCrcinitSel(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketClrCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketClrIncChan(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketClrPllTrig(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketDisableWhitening(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_PacketGetCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP)) 
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}


WEAK_FUNCTION(uint8_t* BLECNTR_PacketGetDataPtr(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketInitTo0(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetAdvPduFormat(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetCrcinitSel(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetDataPduFormat(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetDataPtr(BLECNTR_TXRXPACK_TypeDef* packetP, void* dataP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetIncChan(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetIntCrcErr(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetIntDone(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetIntRcvOk(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetIntTimeout(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetIntTrigRcv(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetIntTxOk(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetKeepsemareq(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetNextPtr(BLECNTR_TXRXPACK_TypeDef* packetP, BLECNTR_TXRXPACK_TypeDef* packetNextP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetNextRxMode(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetNextSlot(BLECNTR_TXRXPACK_TypeDef* packetP, uint8_t slot))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetNextTxMode(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetNsEn(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetPllTrig(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetRxReady(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetTimeout(BLECNTR_TXRXPACK_TypeDef* packetP, uint32_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetTimer2Active(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetTimerTrigDone(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetTimerTrigRcv(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_PacketSetTxReady(BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SetRadioConfig(uint8_t* value))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SetRcvLen(BLECNTR_TXRXPACK_TypeDef* packetP, uint32_t rcvLen))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmCteOff(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmCteOn(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmEnRadioConfig(uint8_t smNo, uint32_t enable))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmEncOff(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmEncOn(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_SmGetAccessAddr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmGetChannelMap(uint8_t smNo, uint8_t* chanMap))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetCteAntennaPatternLen(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetCteAodNaoa(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetCteSlotWidth(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetCteStatus(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetCteTime(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t* BLECNTR_SmGetEncIvPtr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t* BLECNTR_SmGetEncKeyPtr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetEncStatus(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetHopIncr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetMode(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t* BLECNTR_SmGetPrevRxPacketDataPtr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetPrevRxPacketPtr(uint8_t smNo) )
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t* BLECNTR_SmGetPrevTxPacketDataPtr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetPrevTxPacketPtr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetRemapChan(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmGetRxCount(uint8_t smNo, uint32_t* packetCount))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetRxPhy(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetTxPacketPtr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetTxPhy(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetTxPwr(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_SmGetUnmappedChan(uint8_t smNo))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmInitTo0(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetAccessAddr(uint8_t smNo, uint32_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetChannelMap(uint8_t smNo, uint8_t* chanMap))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetCrcInit(uint8_t smNo, uint32_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}


WEAK_FUNCTION(void BLECNTR_SmSetCteAntennaPatternLen(uint8_t smNo, uint8_t antPattLen))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetCteAntennaPatternPtr(uint8_t smNo, uint8_t* antPattP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetCteAoa(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetCteAod(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetCteIqsamplesPtr(uint8_t smNo, uint32_t* iqSamplesP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetCteMaxIqsamplesNumb(uint8_t smNo, uint8_t iqsamplesNumb))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetCteSlotWidth(uint8_t smNo, uint32_t cteSlot))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetCteTime(uint8_t smNo, uint8_t cteTime))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetDataLength(uint8_t smNo, uint8_t length))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetDataLengthExtnEn(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetHopIncr(uint8_t smNo, uint8_t x))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetRemapChan(uint8_t smNo, uint8_t chan))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetRxCount(uint8_t smNo, uint32_t* packetCount))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetRxCountDirectionBit(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetRxMode(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetRxPacketPtr(uint8_t smNo, BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetRxPhy(uint8_t smNo, uint8_t rxPhy))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetTxCount(uint8_t smNo, uint32_t* packetCount))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetTxCountDirectionBit(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetTxMode(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetTxPacketPtr(uint8_t smNo, BLECNTR_TXRXPACK_TypeDef* packetP))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetTxPhy(uint8_t smNo, uint8_t txPhy))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetTxPwr(uint8_t smNo, uint8_t paLevel))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmSetUnmappedChan(uint8_t smNo, uint8_t chan))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmToggleNesn(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_SmToggleSn(uint8_t smNo))
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(void BLECNTR_StartEncrypt())
{
  return;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint32_t BLECNTR_TimeDiff(uint32_t x, uint32_t y))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(uint8_t BLECNTR_DemodDelaySt(uint8_t RxPHY))
{
  return BLECNTR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}


/**
* @}
*/

  
