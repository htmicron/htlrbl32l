/**
 ******************************************************************************
 * @file    ble_controller.h
 * @author  AMS - RF Application Team
 * @brief   This file contains all the functions prototypes for the BLE CONTROLLER.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BLECNTR_H
#define BLECNTR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "system_util.h"
  
/** @addtogroup BLECNTR_Peripheral  BLE CONTROLLER
 * @{
 */

/** @defgroup BLECNTR_Exported_Types Exported Types
 * @{
 */
	
/* Enumerated values used to report the RNG result status after a process */
typedef enum
{
  BLECNTR_SUCCESS     =  0,
  BLECNTR_ERROR,
  BLECNTR_ERROR_TIMEOUT
} BLECNTR_ResultStatus;


typedef struct {
    volatile uint32_t WORD0;
    volatile uint32_t WORD1;
    volatile uint32_t WORD2;
    volatile uint32_t WORD3;
    volatile uint32_t WORD4;
} BLECNTR_TXRXPACK_TypeDef; 
    
typedef enum
{
    BLECNTR_TxRx = 0,
    BLECNTR_RxTx,
    BLECNTR_TxTx,
    BLECNTR_RxRx
} BLECNTR_Transaction;
/**
 * @}
 */

/** @defgroup BLECNTR_Exported_Constants  Exported Constants
 * @{
 */


/* Start of declarations relative to the Blue HW registers 
 * Note that the declaration of BLUE_t is redundant w.r.t the declaration of
 * BLUE_TypeDef done in file BlueNRG_LP.h but it is currently needed beacause
 * most APIs use the bit fields declared in BLUE_t
 */

#ifndef LL_PHY_CODED
#define LL_PHY_CODED 0x04U
#endif

#ifndef CONV_ADR
#define CONV_ADR(ADDR) ((uint8_t*)(ADDR))
#endif

#ifndef BLUE_TRANS_STRUCT_PTR_CAST
#define BLUE_TRANS_STRUCT_PTR_CAST(PTR) ((BlueTransStruct*)(void*)(uint8_t*)(PTR))
#endif


#define PHY_1MBPS          (0x0U)
#define PHY_2MBPS          (0x1U)
#define PHY_CODED_S2       (0x6U)
#define PHY_CODED_S8       (0x4U)

#define BIT_TX_SKIP (0x0UL)

/**
 * @}
 */

/** @defgroup BLECNTR_Exported_Macros           Exported Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup BLECNTR_Exported_Functions        Exported Functions
 * @{
 */
BLECNTR_ResultStatus BLECNTR_Init(void);

BLECNTR_ResultStatus BLECNTR_Deinit(void);

void BLECNTR_InitGlobal(void);
void BLECNTR_ClearInterrupt(uint32_t x);
void BLECNTR_ClearSemareq(void);
uint32_t* BLECNTR_GetCipherTextPtr(void);
uint32_t* BLECNTR_GetClrTextPtr(void);
uint32_t* BLECNTR_GetEncKeyPtr(void);
BOOL BLECNTR_GetEncryptDoneStatus(void);
uint8_t BLECNTR_GetIqsamplesMissingError(void);
uint8_t BLECNTR_GetIqsamplesNumber(void);
uint8_t BLECNTR_getIqsamplesReady(void);
uint8_t BLECNTR_GetIsrLatency(void);
uint32_t BLECNTR_GetTimercapture(void);
void BLECNTR_GlobDisableBlue(void);
void BLECNTR_GlobEnableBlue(void);
void BLECNTR_GlobEnableIntnoactivelerrorInt(void);
void BLECNTR_GlobEnableOverrunAct2Int(void);
uint8_t BLECNTR_GlobGetDefaultAntennaid(void);
uint8_t BLECNTR_GlobGetWakeupinitdelay(void);
void BLECNTR_GlobReloadRadioConfigP(void);
void BLECNTR_GlobSetChkflagautoclearena(void);
void BLECNTR_GlobSetDefaultAntennaid(uint8_t x);
void BLECNTR_GlobSetInitRadioDelayTxCal(uint8_t x);
void BLECNTR_GlobSetInitRadioDelayTxNocal(uint8_t x);
void BLECNTR_GlobSetRadioConfigP(volatile uint32_t* x);
void BLECNTR_GlobSetWakeupinitdelay(uint8_t x);
void BLECNTR_GlobWriteConfigEnd(uint8_t x);
void BLECNTR_GlobWritePeriodslow(uint16_t x);
void BLECNTR_GlobWriteRcvdelay(uint8_t x);
void BLECNTR_GlobWriteRcvdelay1(uint8_t x);
void BLECNTR_GlobWriteSlot(uint8_t slotNo);
void BLECNTR_GlobWriteTimer12initdelaycal(uint8_t x);
void BLECNTR_GlobWriteTimer2initdelaynocal(uint8_t x);
void BLECNTR_GlobWriteTxDataReadyCheck(uint8_t x);
void BLECNTR_GlobWriteTxReadyTimeout(uint8_t x);
void BLECNTR_GlobWriteTxdelay(uint8_t x) ;
void BLECNTR_GlobWriteTxdelayEnd(uint8_t x);
uint32_t BLECNTR_IntGetIntStatusAnyHwError(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusRxOverflowError(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusBitAct2Error(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusBitTimerOverrun(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusCrcErr(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusDone(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusEncErr(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusLenErr(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusNoactiveError(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusRxOk(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusTimeout(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusTrigRcv(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusTxDone(uint32_t x);
uint32_t BLECNTR_IntGetIntStatusTxOk(uint32_t x);
void BLECNTR_PacketClrCrcinitSel(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketClrCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketClrIncChan(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketClrPllTrig(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketDisableWhitening(BLECNTR_TXRXPACK_TypeDef* packetP);
uint8_t BLECNTR_PacketGetCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP);
uint8_t* BLECNTR_PacketGetDataPtr(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketInitTo0(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetAdvPduFormat(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetCrcinitSel(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetCteSamplingEn(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetDataPduFormat(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetDataPtr(BLECNTR_TXRXPACK_TypeDef* packetP, void* dataP);
void BLECNTR_PacketSetIncChan(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetIntCrcErr(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetIntDone(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetIntRcvOk(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetIntTimeout(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetIntTrigRcv(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetIntTxOk(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetKeepsemareq(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetNextPtr(BLECNTR_TXRXPACK_TypeDef* packetP, BLECNTR_TXRXPACK_TypeDef* packetNextP);
void BLECNTR_PacketSetNextRxMode(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetNextSlot(BLECNTR_TXRXPACK_TypeDef* packetP, uint8_t slot);
void BLECNTR_PacketSetNextTxMode(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetNsEn(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetPllTrig(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetRxReady(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetTimeout(BLECNTR_TXRXPACK_TypeDef* packetP, uint32_t x);
void BLECNTR_PacketSetTimer2Active(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetTimerTrigDone(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetTimerTrigRcv(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_PacketSetTxReady(BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_SetRadioConfig(uint8_t* value);
void BLECNTR_SetRcvLen(BLECNTR_TXRXPACK_TypeDef* packetP, uint32_t rcvLen);
void BLECNTR_SmCteOff(uint8_t smNo);
void BLECNTR_SmCteOn(uint8_t smNo);
void BLECNTR_SmEnRadioConfig(uint8_t smNo, uint32_t enable);
void BLECNTR_SmEncOff(uint8_t smNo);
void BLECNTR_SmEncOn(uint8_t smNo);
uint32_t BLECNTR_SmGetAccessAddr(uint8_t smNo);
void BLECNTR_SmGetChannelMap(uint8_t smNo, uint8_t* chanMap);
uint8_t BLECNTR_SmGetCteAntennaPatternLen(uint8_t smNo);
uint8_t BLECNTR_SmGetCteAodNaoa(uint8_t smNo);
uint8_t BLECNTR_SmGetCteSlotWidth(uint8_t smNo);
uint8_t BLECNTR_SmGetCteStatus(uint8_t smNo);
uint8_t BLECNTR_SmGetCteTime(uint8_t smNo);
uint32_t* BLECNTR_SmGetEncIvPtr(uint8_t smNo);
uint32_t* BLECNTR_SmGetEncKeyPtr(uint8_t smNo);
uint8_t BLECNTR_SmGetEncStatus(uint8_t smNo);
uint8_t BLECNTR_SmGetHopIncr(uint8_t smNo);
uint8_t BLECNTR_SmGetMode(uint8_t smNo);
uint8_t* BLECNTR_SmGetPrevRxPacketDataPtr(uint8_t smNo);
BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetPrevRxPacketPtr(uint8_t smNo) ;
uint8_t* BLECNTR_SmGetPrevTxPacketDataPtr(uint8_t smNo);
BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetPrevTxPacketPtr(uint8_t smNo);
uint8_t BLECNTR_SmGetRemapChan(uint8_t smNo);
void BLECNTR_SmGetRxCount(uint8_t smNo, uint32_t* packetCount);
uint8_t BLECNTR_SmGetRxPhy(uint8_t smNo);
BLECNTR_TXRXPACK_TypeDef* BLECNTR_SmGetTxPacketPtr(uint8_t smNo);
uint8_t BLECNTR_SmGetTxPhy(uint8_t smNo);
uint8_t BLECNTR_SmGetTxPwr(uint8_t smNo);
uint8_t BLECNTR_SmGetUnmappedChan(uint8_t smNo);
void BLECNTR_SmInitTo0(uint8_t smNo);
void BLECNTR_SmSetAccessAddr(uint8_t smNo, uint32_t x);
void BLECNTR_SmSetChannelMap(uint8_t smNo, uint8_t* chanMap);
void BLECNTR_SmSetCrcInit(uint8_t smNo, uint32_t x);
void BLECNTR_SmSetCteAntennaPatternLen(uint8_t smNo, uint8_t antPattLen);
void BLECNTR_SmSetCteAntennaPatternPtr(uint8_t smNo, uint8_t* antPattP);
void BLECNTR_SmSetCteAoa(uint8_t smNo);
void BLECNTR_SmSetCteAod(uint8_t smNo);
void BLECNTR_SmSetCteIqsamplesPtr(uint8_t smNo, uint32_t* iqSamplesP);
void BLECNTR_SmSetCteMaxIqsamplesNumb(uint8_t smNo, uint8_t iqsamplesNumb);
void BLECNTR_SmSetCteSlotWidth(uint8_t smNo, uint32_t cteSlot);
void BLECNTR_SmSetCteTime(uint8_t smNo, uint8_t cteTime);
void BLECNTR_SmSetDataLength(uint8_t smNo, uint8_t length);
void BLECNTR_SmSetDataLengthExtnEn(uint8_t smNo);
void BLECNTR_SmSetHopIncr(uint8_t smNo, uint8_t x);
void BLECNTR_SmSetRemapChan(uint8_t smNo, uint8_t chan);
void BLECNTR_SmSetRxCount(uint8_t smNo, uint32_t* packetCount);
void BLECNTR_SmSetRxCountDirectionBit(uint8_t smNo);
void BLECNTR_SmSetRxMode(uint8_t smNo);
void BLECNTR_SmSetRxPacketPtr(uint8_t smNo, BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_SmSetRxPhy(uint8_t smNo, uint8_t rxPhy);
void BLECNTR_SmSetTxCount(uint8_t smNo, uint32_t* packetCount);
void BLECNTR_SmSetTxCountDirectionBit(uint8_t smNo);
void BLECNTR_SmSetTxMode(uint8_t smNo);
void BLECNTR_SmSetTxPacketPtr(uint8_t smNo, BLECNTR_TXRXPACK_TypeDef* packetP);
void BLECNTR_SmSetTxPhy(uint8_t smNo, uint8_t txPhy);
void BLECNTR_SmSetTxPwr(uint8_t smNo, uint8_t paLevel);
void BLECNTR_SmSetUnmappedChan(uint8_t smNo, uint8_t chan);
void BLECNTR_SmToggleNesn(uint8_t smNo);
void BLECNTR_SmToggleSn(uint8_t smNo);
void BLECNTR_StartEncrypt(void);
uint32_t BLECNTR_TimeDiff(uint32_t x, uint32_t y);
uint8_t BLECNTR_DemodDelaySt(uint8_t RxPHY);
uint32_t BLECNTR_GeTimer2TimeoutForIfs(uint32_t T_Ifs, BLECNTR_Transaction Transaction, BOOL Cal_Enabled);


/**
  * @}
  */


/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* BLECNTR_H */
