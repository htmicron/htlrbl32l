/**
 ******************************************************************************
 * @file    ble_controller_bluenrg_lp.h
 * @author  AMS - RF Application Team
 * @brief   This file contains all the functions prototypes for the BlueNRG-LP BLE CONTROLLER.
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
#ifndef BLECNTR_BLUENRG_LP_H
#define BLECNTR_BLUENRG_LP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_ll_radio_2g4.h"
#include "rf_driver_ll_bus.h"
#include "rf_driver_ll_system.h"  
#include "system_bluenrg_lp.h"
#include "bluenrg_lpx.h"
#include "osal.h"
  
/** @addtogroup BLE_Controller_BlueNRG_LP_Peripheral  BLE CONTROLLER
 * @{
 */

/** @defgroup BLE_Controller_BlueNRG_LP_Exported_Types Exported Types
 * @{
 */
/**
 * @}
 */

/** @defgroup BLE_Controller_BlueNRG_LP_Exported_Constants  Exported Constants
 * @{
 */
  

#if defined(__ARMCC_VERSION)
#pragma anon_unions
#endif
 
#define ANY_HW_ERROR_INTERRUPT_Msk ( \
        BLUE_STATUSREG_ADDPOINTERROR_Msk      |  \
        BLUE_STATUSREG_RXOVERFLOWERROR_Msk    |  \
        BLUE_STATUSREG_TXERROR_0_Msk          |  \
        BLUE_STATUSREG_TXERROR_1_Msk          |  \
        BLUE_STATUSREG_TXERROR_2_Msk          |  \
        BLUE_STATUSREG_TXERROR_3_Msk          |  \
        BLUE_STATUSREG_TXERROR_4_Msk          |  \
        BLUE_STATUSREG_ALLTABLEREADYERROR_Msk | \
        BLUE_STATUSREG_TXDATAREADYERROR_Msk   | \
        BLUE_STATUSREG_NOACTIVELERROR_Msk     | \
        BLUE_STATUSREG_INITDELAYERROR_Msk     | \
        BLUE_STATUSREG_SEMATIMEOUTERROR_Msk   | \
        BLUE_STATUSREG_ACTIVE2ERROR_Msk       | \
        BLUE_STATUSREG_CONFIGERROR_Msk          \
        )
/**
 * @}
 */



/** @defgroup BLE_Controller_BlueNRG_LP_Exported_Functions        Exported Functions
 * @{
 */


#   define WAKEUPINITDELAY_MT                   (64U)
#   define TIMER12_INIT_DELAY_CAL               (63U)
#   define TIMER2_INIT_DELAY_NO_CAL              (9U)

#   define RCV_LEN_MARGIN_US                    (16U)
#   define TX_DELAY_START                       (16U) 
#   define TX_DELAY_END                         (16U)

#   define RADIO_FSM_RX_DELAY_CAL              (116U)
#   define RADIO_FSM_RX_DELAY_NO_CAL            (56U)
#   define RADIO_FSM_TX_DELAY_CAL              (118U)
#   define RADIO_FSM_TX_DELAY_NO_CAL            (58U)

#   define RECEIVE_CAL_DELAY_CHECK              (RADIO_FSM_RX_DELAY_CAL)
#   define RECEIVE_NO_CAL_DELAY_CHECK           (RADIO_FSM_RX_DELAY_NO_CAL)
#   define TRANSMIT_CAL_DELAY_CHECK             (RADIO_FSM_TX_DELAY_CAL)
#   define TRANSMIT_NO_CAL_DELAY_CHECK          (RADIO_FSM_TX_DELAY_NO_CAL)

#   define CONFIG_END_DURATION                  (20U)
#   define TX_DATA_READY_CHECK                   (5U)
#   define TX_READY_TIMEOUT                      (2U)

/**
 * @}
 */


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* BLECNTR_BLUENRG_LP_H */
