/**
 *
 * Copyright (c) 2022 HT Micron Semicondutors S.A.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "HT_push_button.h"

#define CounterMiliSec	7000 // modified

WakeupSourceConfig_TypeDef wakeupIO; 
PowerSaveLevels stopLevel;

volatile uint8_t set_connectable = 0;
uint8_t connected = 0;

HT_Payload payload = {0};
HT_Fsm state = SM_WAIT_FOR_EVENT;
HT_Event event;

HT_LoRa_Process lora_process = PROCESS_LORA_READY;

static TimerEvent_t PushCounter; // modified
static int PushCounterFlag = 1; // modified

//extern LoRaMacRadioEvents_t LoRaMacRadioEvents; // modified
extern lora_AppData_t AppData; // modified
//extern RxDoneParams RxBuffer;

uint8_t rx_flag = 0;

/*!******************************************************************
 * \fn static void HT_PB_SendLoraFrame(void);
 * \brief Sends a LoRaWAN frame containing what was received by bluetooth.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_PB_SendLoraFrame(void);

/*!******************************************************************
 * \fn static void HT_PB_WritePayloadState(void)
 * \brief Write without response handler state.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_PB_WritePayloadState(void);

/*!******************************************************************
 * \fn static void HT_PB_SendFrameState(void)
 * \brief Send a LoRa frame based on the previous event.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_PB_SendFrameState(void);

/*!******************************************************************
 * \fn static void HT_PB_PushButtonState(void)
 * \brief Push button handler state.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_PB_PushButtonState(void);

/*!******************************************************************
 * \fn static void HT_PB_WaitForEventState(void)
 * \brief Keep waiting for an event.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_PB_WaitForEventState(void);

/*!******************************************************************
 * \fn static void HT_PB_RxLoraState(void)
 * \brief LoRaWAN RX handler. Saves RX buffer to send it in the next bluetooth read event.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_PB_RxLoraState(void);

/*!******************************************************************
 * \fn static void HT_PB_Fsm(void)
 * \brief Finite state machine function.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_PB_Fsm(void);

static void OnPushCounterEvent(void *context);

void HT_PB_SetState(HT_Fsm new_state) {
	state = new_state;
}

void HT_PB_SetLoraProcess(HT_LoRa_Process process) {
	lora_process = process;
}

HT_LoRa_Process HT_PB_GetLoraProcess(void) {
	return lora_process;
}

void HT_PB_ConfigWakeupIO(void) {
	wakeupIO.RTC_enable = 0;
	wakeupIO.IO_Mask_Low_polarity = WAKEUP_PA4;
	wakeupIO.IO_Mask_High_polarity = 0;
	wakeupIO.LPU_enable = 0;
}

static void HT_PB_RadioSleep(void){
	SleepParams_t params = {0};

	params.Fields.WarmStart = 1;
	SX126xSetSleep(params);
}

static void HT_PB_SendLoraFrame(void) {
	lora_AppData_t tx_payload;

	if(strlen((char *)payload.data) == 0)
		sprintf((char *)payload.data, "Hello, World!");

	tx_payload.Buff = (uint8_t *)&payload;
	tx_payload.BuffSize = strlen((char *)payload.data) == 0 ? PAYLOAD_SIZE + 1 : strlen((char *)payload.data) + 1;
	tx_payload.Port = LORAWAN_APP_PORT;

  	lora_process = PROCESS_LORA_TX;
	lorawan_send(&tx_payload);
	
	HT_GPIO_EnableButtonIRQN();
}

static void HT_PB_WaitForEventState(void) {
	
	state = SM_WAIT_FOR_EVENT;
                    
	/* Power Save Request */
	if(lora_process == PROCESS_LORA_READY) {
		HT_PB_RadioSleep();
		HAL_PWR_MNGR_Request(POWER_SAVE_LEVEL_STOP_NOTIMER, wakeupIO, &stopLevel);
	}
}

static void HT_PB_PushButtonState(void) {
	if(PushCounterFlag){
		TimerStop(&PushCounter); // stop counter
		PushCounterFlag = 0;
		event = PUSH_BUTTON;
		state = SM_SEND_FRAME;
		TimerStart(&PushCounter); // start counter
	}
}

static void HT_PB_SendFrameState(void) {
	uint8_t size = strlen((char *)payload.data);
	
	HT_PB_SendLoraFrame();

	memset(payload.data, 0, sizeof(payload.data));
	state = SM_WAIT_FOR_EVENT;
}

static void HT_PB_RxLoraState(void) {
	printf("LoRa downlink received: {");
	for (uint8_t i = 0; i < AppData.BuffSize; i++)
		printf(" %02X ", AppData.Buff[i]);
	printf("}\n");

	rx_flag = 1;
	state = SM_WAIT_FOR_EVENT;
	lora_process = PROCESS_LORA_READY;
}

static void HT_PB_WritePayloadState(void) {
	if(PushCounterFlag){
		TimerStop(&PushCounter); // stop counter
		PushCounterFlag = 0;
		event = WRITE_PAYLOAD;
		state = SM_SEND_FRAME;
		TimerStart(&PushCounter); // start counter
	}
}

static void HT_PB_Fsm(void) {

	switch (state) {
	case SM_WAIT_FOR_EVENT:
		HT_PB_WaitForEventState();
		break;
	case SM_PUSH_BUTTON_HANDLER:
		HT_PB_PushButtonState();
		break;
	case SM_WRITE_PAYLOAD_HANDLER:
		HT_PB_WritePayloadState();
		break;
	case SM_SEND_FRAME:
		HT_PB_SendFrameState();
		break;
	case SM_RX_LORA:
		HT_PB_RxLoraState();
		break;
	default:
		printf("Invalid state!\n");
		break;
	}
}

void HT_PB_app(void) {
    
	if(LORA_JoinStatus()){
	if (set_connectable) {
        HT_BLE_SetDeviceConnectable();
        set_connectable = 0;
   }
	HT_PB_Fsm();
	}
}

void HT_PB_Counter_init(void){
	//Sets callback function
	TimerInit(&PushCounter, OnPushCounterEvent);
	//Sets alarm total time
    TimerSetValue(&PushCounter, CounterMiliSec);
    TimerStart(&PushCounter);
}

static void OnPushCounterEvent(void *context){
	PushCounterFlag = 1;
	lora_process = PROCESS_LORA_READY;
}
/************************ HT MICRON SEMICONDUCTORS S.A - HT_push_button.c *****END OF FILE****/
