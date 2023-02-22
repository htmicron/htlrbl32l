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

/* Includes  ------------------------------------------------------------------*/

#include "HT_push_button.h"

/* Variables  -----------------------------------------------------------------*/

WakeupSourceConfig_TypeDef wakeupIO; 
PowerSaveLevels stopLevel;

volatile HT_Fsm state = SM_WAIT_FOR_EVENT;
volatile HT_LoRa_Process lora_process = PROCESS_LORA_READY;
extern RxDoneParams RxBuffer;
static uint8_t payload[] = {"HelloWorld"};

/* Function Prototypes  -------------------------------------------------------*/

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
 * \fn static void HT_PB_SendLoraFrame(void)
 * \brief Sends a LoRaWAN frame containing what was received by bluetooth.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void HT_PB_SendLoraFrame(void);

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

/* Functions  ----------------------------------------------------------------*/

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

	tx_payload.Buff = payload;
	tx_payload.BuffSize = strlen((char *)payload);
	tx_payload.Port = LORAWAN_APP_PORT;

	lora_process = PROCESS_LORA_TX;
	lorawan_send(&tx_payload);
}

static void HT_PB_WaitForEventState(void) {
	state = SM_WAIT_FOR_EVENT;

	/* Power Save Request */
	if(lora_process == PROCESS_LORA_READY) {
#if DEEP_SLEEP_MODE == 1
		printf("\r\nSleeping....\n");
		HT_PB_RadioSleep();
		HAL_PWR_MNGR_Request(POWER_SAVE_LEVEL_STOP_NOTIMER, wakeupIO, &stopLevel);		
#else
		HT_GPIO_EnableButtonIRQN();
#endif		
	}
}

static void HT_PB_PushButtonState(void) {
	printf("Push button handler state...\n");

	state = SM_SEND_FRAME;
}

static void HT_PB_SendFrameState(void) {

	printf("Send frame state...\n");
	HT_PB_SendLoraFrame();

	state = SM_WAIT_FOR_EVENT;
}

static void HT_PB_RxLoraState(void) {
	printf("LoRa downlink received: {");
	for (uint8_t i = 0; i < RxBuffer.Size; i++)
		printf(" %02X ", RxBuffer.Payload[i]);
	printf("}\n");

	state = SM_WAIT_FOR_EVENT;
}

void HT_PB_Fsm(void) {

	switch (state) {
	case SM_WAIT_FOR_EVENT:
		HT_PB_WaitForEventState();
		break;
	case SM_PUSH_BUTTON_HANDLER:
		HT_PB_PushButtonState();
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

/************************ HT MICRON SEMICONDUCTORS S.A - HT_push_button.c *****END OF FILE****/
