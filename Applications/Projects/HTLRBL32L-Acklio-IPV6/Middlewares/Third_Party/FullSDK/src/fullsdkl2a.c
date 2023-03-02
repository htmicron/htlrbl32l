/**
 * Copyright (C) 2018-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Pascal Bodin - pascal@ackl.io
 *
 * This file provides the implementation of L2A layer for V1.3.1 of ST LoRaWAN
 * stack, for class A only, for EU868 band. The ruleID is send in the FPort as
 * specified in the SCHC over LoRaWAN document:
 * https://tools.ietf.org/html/draft-ietf-lpwan-schc-over-lorawan-04.
 *
 * It relies mainly on the upper interface (the one defined in ST lora.h) and on
 * some slight modifications to the upper layer and to the MAC layer.
 *
 * The time to next possible TX is estimated, according to the results of tests
 * performed for possible data rates. get_next_tx_delay() returns a value which
 * is supposed to be used right after the transmission result callback has been
 * called. Then, the value does not change, until next transmission.
 *
 * Transmission result callback is called after the RX windows.
 *
 * If l2a_send_data() is called before transmission result callback has been
 * called, it returns a busy status code. If it is called after the callback
 * call but before time to next possible TX, the LoRaWAN stack returns an error,
 * that will be returned by l2a_send_data().
 *
 * Connectivity lost callback is never called.
 */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if (defined (ATMODEM_APP))
#else
#include "common.h"
#endif
#include "LmHandlerTypes.h"
#include "LmHandler.h"
#include "lora_info.h"
#include "sys_app.h"

#include "fullsdkl2a.h"



#define ACTIVE_REGION                           LORAMAC_REGION_EU868
#define LORAWAN_DEFAULT_CLASS                   CLASS_C
#define LORAWAN_ADR_STATE                       LORAMAC_HANDLER_ADR_OFF
#define LORAWAN_DEFAULT_DATA_RATE               DR_3
#define LORAWAN_DEFAULT_PING_SLOT_PERIODICITY   4
#define LORAWAN_DEFAULT_ACTIVATION_TYPE         ACTIVATION_TYPE_OTAA
#define LORAWAN_APP_DATA_BUFFER_MAX_SIZE        242

// LoRaWAN ruleID byte size.
#define LORAWAN_RULEID_BYTE_SIZE 1

// LoRaWAN default confirm state.
#define LORAWAN_DEFAULT_CONFIRM_MSG_STATE LORAWAN_UNCONFIRMED_MSG

#if (defined (ATMODEM_APP))
// EUIs and key, defined in fullsdkl2.c.
extern uint8_t app_key[];
extern uint8_t dev_eui[];
extern uint8_t join_eui[];
extern DeviceClass_t device_class;
#endif

static ActivationType_t ActivationType = LORAWAN_DEFAULT_ACTIVATION_TYPE;

// User application buffer.
static uint8_t AppDataBuffer[LORAWAN_APP_DATA_BUFFER_MAX_SIZE];
// User application data structure.
static LmHandlerAppData_t AppData = { 0, 0, AppDataBuffer };

// This global variable must be defined in L2A layer and initialized
// to L2A_DEFAULT. Its use is reserved.
l2a_technology_t l2a_technology = L2A_DEFAULT;

// Configuration values.
static l2a_callbacks_t callbacks;

static uint8_t *received_data_buffer;
static uint16_t received_data_buffer_size;

// Flags describing what kind of processing is required.
static bool process_l2 = false;
static bool tx_result_event = false;
static bool retransmission = false;

// Current state.
// connectivity and busy flags do not need volatile keyword
// because they are modified by tasks executed in background
// context only.
static bool connectivity = false;
static bool busy = false;
// in_error is set to false when a severe error is detected.
// The layer is then considered as unusable.
static bool in_error = false;
// Last transmission status
static l2a_status_t last_tx_status = L2A_SUCCESS;
// Last L2 transmission error.
static uint8_t last_l2_tx_status;
static UTIL_TIMER_Time_t next_tx_delay = 0;
static UTIL_TIMER_Object_t retransmission_timer;
// Device IID
//static uint8_t device_iid[8];

static void onMacProcessNotify(void);
static void onJoinRequest(LmHandlerJoinParams_t *params);
static void onTxData(LmHandlerTxParams_t *params);
static void onRxData(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params);
static void onClassChange(DeviceClass_t class);
static void l2a_action_tx_status(l2a_status_t status, uint8_t l2_status);
static void retransmission_timer_event_fct(void *context);



// LoRaWAN callbacks.
static LmHandlerCallbacks_t LmHandlerCallbacks =
{
  .GetBatteryLevel =           GetBatteryLevel,
  .GetTemperature =            GetTemperatureLevel,
  .GetUniqueId =               GetUniqueId,
  .GetDevAddr =                GetDevAddr,
  .OnMacProcess =              onMacProcessNotify,
  .OnJoinRequest =             onJoinRequest,
  .OnTxData =                  onTxData,
  .OnRxData =                  onRxData,
  .OnClassChange =             onClassChange
};

// LoRaWAN parameters.
static LmHandlerParams_t LmHandlerParams =
{
  .ActiveRegion =             ACTIVE_REGION,
  .DefaultClass =             LORAWAN_DEFAULT_CLASS,
  .AdrEnable =                LORAWAN_ADR_STATE,
  .TxDatarate =               LORAWAN_DEFAULT_DATA_RATE,
  .PingPeriodicity =          LORAWAN_DEFAULT_PING_SLOT_PERIODICITY
};

l2a_status_t l2a_initialize(const l2a_callbacks_t *pp_callbacks,
                            uint8_t *p_receive_buffer,
                            uint16_t receive_buffer_size)
{
  // Copy all pointers.
  if (pp_callbacks == NULL)
  {
    in_error = true;
    return L2A_REQ_CALLBACK_ERR;
  }
  callbacks = *pp_callbacks;
  // Check that mandatory callbacks are provided.
  if (callbacks.processing_required == NULL)
    in_error = true;
  if (callbacks.transmission_result == NULL)
    in_error = true;
  if (callbacks.data_received == NULL)
    in_error = true;
  if (callbacks.connectivity_available == NULL)
    in_error = true;
  if (in_error)
    return L2A_REQ_CALLBACK_ERR;

  received_data_buffer = p_receive_buffer;
  received_data_buffer_size = receive_buffer_size;

  UTIL_TIMER_Create(&retransmission_timer, 0xFFFFFFFFU, UTIL_TIMER_ONESHOT, retransmission_timer_event_fct, NULL);

  LoraInfo_Init();

  LmHandlerInit(&LmHandlerCallbacks);

#if (defined (ATMODEM_APP))
  // For ATModem application, we have to set device class, as set
  // by AT+JOIN command.
  if (device_class != 0)
  {
    LmHandlerParams.DefaultClass = device_class;
  }
#endif /* ATMODEM_APP */
  LmHandlerConfigure(&LmHandlerParams);

#if (defined (ATMODEM_APP))
  // For ATModem application, we have to set EUIs and key from
  // the values that were set by AT+DEUI, AT+APPEUI and AT+APPKEY
  // commands.
  MibRequestConfirm_t mibReq;
  mibReq.Type = MIB_DEV_EUI;
  mibReq.Param.DevEui = dev_eui;
  LoRaMacMibSetRequestConfirm(&mibReq);
  mibReq.Type = MIB_JOIN_EUI;
  mibReq.Param.JoinEui = join_eui;
  LoRaMacMibSetRequestConfirm(&mibReq);
  LmHandlerSetNwkKey(app_key);
#endif /* ATMODEM_APP */

  LmHandlerJoin(ActivationType);

  return L2A_SUCCESS;
}

l2a_status_t l2a_send_data(const uint8_t *p_data, uint16_t data_size)
{
  if (in_error)
  {
    return L2A_INTERNAL_ERR;
  }
  // We are supposed to receive at least the rule ID.
  if (data_size < LORAWAN_RULEID_BYTE_SIZE)
  {
    return L2A_INTERNAL_ERR;
  }
  if (!connectivity)
  {
    l2a_action_tx_status(L2A_CONNECT_ERR, LORAMAC_EVENT_INFO_STATUS_OK);
    return L2A_SUCCESS;
  }
  if (busy)
  {
    l2a_action_tx_status(L2A_BUSY_ERR, LORAMAC_EVENT_INFO_STATUS_OK);
    return L2A_SUCCESS;
  }
  if (data_size + LORAWAN_RULEID_BYTE_SIZE > LORAWAN_APP_DATA_BUFFER_MAX_SIZE)
  {
    l2a_action_tx_status(L2A_L2_ERROR, LORAMAC_EVENT_INFO_STATUS_OK);
    return L2A_SUCCESS;
  }

  // Save the rule ID into the FPort.
  AppData.Port = p_data[0];
  AppData.Buffer = (uint8_t *)(&p_data[1]);
  AppData.BufferSize = (uint8_t)data_size - 1;
  // At this stage, we can request L2 to send data.
  //
  // LmHandlerSend() may return with LORAMAC_HANDLER_DUTYCYCLE_RESTRICTED, in which case
  // nextTxIn contains the time that must be waited for before retransmitting.
  // In this case, we start a timer, wait for returned time, and transmit again.
  UTIL_TIMER_Time_t nextTxIn;
  LmHandlerErrorStatus_t status = LmHandlerSend(&AppData, LORAMAC_HANDLER_UNCONFIRMED_MSG,
                                                &nextTxIn,
                                                false);  // allowDelayedTx
  if (status == LORAMAC_HANDLER_DUTYCYCLE_RESTRICTED)
  {
    APP_LOG(TS_ON, VLEVEL_L, "=> l2a_send_data - duty cycle restriction, waiting for %u\n\r", nextTxIn);
    // Add a small offset, to be sure to wait longer than duty cycle delay.
    UTIL_TIMER_SetPeriod(&retransmission_timer, nextTxIn + 100);
    UTIL_TIMER_Start(&retransmission_timer);
    next_tx_delay = nextTxIn;
    busy = true;
    // Pointer to message buffer is kept in AppData. L2A interface requires that the buffer
    // containing the message is kept allocated until the end of transmission is signaled.
    return L2A_SUCCESS;
  }
  if (status != LORAMAC_HANDLER_SUCCESS)
  {
    APP_LOG(TS_ON, VLEVEL_L, "=> l2a_send_data - error from LmHandlerSend - %d - nextTxIn: %u\n\r", status, nextTxIn);
    l2a_action_tx_status(L2A_L2_ERROR, status);
    return L2A_SUCCESS;
  }
  // At this stage, send request accepted.
  APP_LOG(TS_ON, VLEVEL_L, "=> l2a_send_data - success from LmHandlerSend - nextTxIn: %u\n\r", nextTxIn);
  busy = true;

  // Remember next TX delay.
  next_tx_delay = nextTxIn;

  return L2A_SUCCESS;
}

l2a_technology_t l2a_get_technology(void)
{
  return l2a_technology;
}

uint16_t l2a_get_mtu(void)
{
  LoRaMacTxInfo_t txInfo;

  if (LoRaMacQueryTxPossible(0, &txInfo) != LORAMAC_STATUS_OK)
  {
    APP_LOG(TS_ON, VLEVEL_L, "=> l2a_get_mtu - error from LoRaMacQueryTxPossible\n\r");
    return 0;
  }
  APP_LOG(TS_ON, VLEVEL_L, "=> l2a_get_mtu - MaxPossibleApplicationDataSize %d\n\r",
          txInfo.MaxPossibleApplicationDataSize);
  return (uint16_t)txInfo.MaxPossibleApplicationDataSize;
}

uint32_t l2a_get_next_tx_delay(uint16_t data_size)
{
  (void)data_size;  // To prevent compiler warning about unused parameter.
  APP_LOG(TS_ON, VLEVEL_L, "=> next_tx_delay: %u\n\r", next_tx_delay);
  return next_tx_delay;
}

l2a_status_t l2a_process(void)

{
  if (in_error)
  {
    return L2A_INTERNAL_ERR;
  }

  if (process_l2)
  {
    process_l2 = false;
    LmHandlerProcess();
  }

  if (tx_result_event)
  {
    tx_result_event = false;
    callbacks.transmission_result(last_tx_status, 0);
    last_tx_status = L2A_SUCCESS;
  }

  if (retransmission)
  {
    retransmission = false;
    UTIL_TIMER_Time_t nextTxIn;
    LmHandlerErrorStatus_t status = LmHandlerSend(&AppData, LORAMAC_HANDLER_UNCONFIRMED_MSG,
                                                  &nextTxIn,
                                                  false);  // allowDelayedTx
    if (status == LORAMAC_HANDLER_DUTYCYCLE_RESTRICTED)
    {
      APP_LOG(TS_ON, VLEVEL_L, "=> l2a_send_data - still duty cycle restriction - %u\n\r", nextTxIn);
      // Add an offset, to be sure not to recall the retransmission immediatly when nextTxIn is 0
      // (which happens).
      UTIL_TIMER_SetPeriod(&retransmission_timer, nextTxIn + 100);
      UTIL_TIMER_Start(&retransmission_timer);
      next_tx_delay = nextTxIn;
      // Pointer to message buffer is kept in AppData. L2A interface requires that the buffer
      // containing the message is kept allocated until the end of transmission is signaled.
    } else if (status != LORAMAC_HANDLER_SUCCESS)
    {
      APP_LOG(TS_ON, VLEVEL_L, "=> l2a_send_data - error from LmHandlerSend 2 - %d - nextTxIn: %u\n\r", status, nextTxIn);
      l2a_action_tx_status(L2A_L2_ERROR, status);
      busy = false;
      return L2A_SUCCESS;
    }
    // At this stage, send request accepted.
    APP_LOG(TS_ON, VLEVEL_L, "=> l2a_send_data - success from LmHandlerSend 2 - nextTxIn: %u\n\r", nextTxIn);
    // Remember next TX delay.
    next_tx_delay = nextTxIn;
  }

  return L2A_SUCCESS;
}

bool l2a_get_dev_iid(uint8_t **dev_iid)
{
  return false;
}

/***********************************
 *  Callbacks used by LoRaWAN layer.
 ***********************************/

/**
 * This callback is called by LoRaWAN background task. Consequently,
 * it's atomic. We don't have to add any specific protection mechanism
 * to ensure atomic read of the reception buffer by the user application.
 */
static void onRxData(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params)
{
  // appData may be NULL.
  if (appData == NULL)
  {
    APP_LOG(TS_ON, VLEVEL_M, "NULL appData, ignored\n");
    return;
  }
  if (params->Status != LORAMAC_EVENT_INFO_STATUS_OK)
  {
    callbacks.data_received(0, L2A_L2_ERROR);
    return;
  }
  if (appData->BufferSize + LORAWAN_RULEID_BYTE_SIZE > received_data_buffer_size)
  {
    // We return length of received data, anyway.
    callbacks.data_received(appData->BufferSize + LORAWAN_RULEID_BYTE_SIZE,
                            L2A_BUFFER_ERR);
    return;
  }
  // At this stage, our reception buffer is OK.
  // Move LoRaWAN stack reception buffer and the rule ID extracted from FPort to
  // our own buffer.
  received_data_buffer[0] = appData->Port;
  memcpy(&received_data_buffer[1], appData->Buffer, appData->BufferSize);
  APP_LOG(TS_ON, VLEVEL_M, "Received %u bytes\n",
          appData->BufferSize + LORAWAN_RULEID_BYTE_SIZE);
  APP_LOG(TS_ON, VLEVEL_M, "Datarate: %d - RSSI: %d - SNR: %d\n",
          params->Datarate, params->Rssi, params->Snr);
  callbacks.data_received(appData->BufferSize + LORAWAN_RULEID_BYTE_SIZE,
                          L2A_SUCCESS);
}

static void onJoinRequest(LmHandlerJoinParams_t *params)
{
  if (params->Status == LORAMAC_HANDLER_SUCCESS)
  {
    APP_LOG(TS_ON, VLEVEL_M, "onJoinRequest success\n");
    connectivity = true;
    callbacks.connectivity_available();
  }
}

static void onClassChange(DeviceClass_t class)
{
#if defined (APP_LOG_ENABLED) && (APP_LOG_ENABLED == 1)
  char class_c;
  switch (class)
  {
    case CLASS_A:
      class_c = 'A';
      break;
    case CLASS_B:
      class_c = 'B';
      break;
    case CLASS_C:
      class_c = 'C';
      break;
    default:
      class_c = 'B';
  }
#endif
  APP_LOG(TS_ON, VLEVEL_L, "LoRa class switched to %c\n\r", class_c);
}

static void onTxData(LmHandlerTxParams_t *params)
{
  busy = false;
  // Inform about end of transmission for application data only:
  // filter out end of transmission of JOIN message.
  if (connectivity)
  {
    if (params->Status == LORAMAC_EVENT_INFO_STATUS_OK)
    {
      l2a_action_tx_status(L2A_SUCCESS, LORAMAC_EVENT_INFO_STATUS_OK);
    }
    else
    {
      l2a_action_tx_status(L2A_L2_ERROR, params->Status);
    }
  }
}

static void onMacProcessNotify(void)
{
  process_l2 = true;
  callbacks.processing_required();
}

static void l2a_action_tx_status(l2a_status_t status, uint8_t l2_status)
{
  tx_result_event = true;
  last_tx_status = status;
  last_l2_tx_status = l2_status;
  callbacks.processing_required();
}

static void retransmission_timer_event_fct(void *context)
{
  retransmission = true;
  callbacks.processing_required();
}
