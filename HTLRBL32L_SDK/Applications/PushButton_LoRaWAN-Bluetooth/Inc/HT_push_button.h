/*
  _    _ _______   __  __ _____ _____ _____   ____  _   _
 | |  | |__   __| |  \/  |_   _/ ____|  __ \ / __ \| \ | |
 | |__| |  | |    | \  / | | || |    | |__) | |  | |  \| |
 |  __  |  | |    | |\/| | | || |    |  _  /| |  | | . ` |
 | |  | |  | |    | |  | |_| || |____| | \ \| |__| | |\  |
 |_|  |_|  |_|    |_|  |_|_____\_____|_|  \_\\____/|_| \_|
 =================== Advanced R&D ========================

*/

/*!
 * \file HT_push_button.h
 * \brief Push Button LoRa+BLE application.
 * \author HT Micron Advanced R&D
 * \link support_iot@htmicron.com.br
 * \version 1.0
 * \date Junuary 17, 2022
 */

#ifndef __HT_API__
#define __HT_API__

/* Includes  ------------------------------------------------------------------*/
#include "main.h"
#include "LoRaMac.h"

/* Defines  ------------------------------------------------------------------*/
#define PAYLOAD_SIZE 19 										/** </ 19 + event = 20 bytes */

/* Typedef -----------------------------------------------------------*/

/**
 * \enum HT_Event
 * \brief Specifies all events that can gerenate a LoRa transmission.
 */
typedef enum {
	PUSH_BUTTON = 0,											/* </ Event caused by a push button. Button could be implemented in mobile app. */
	WRITE_PAYLOAD												/* </ Event caused by the write without response characteristic. */
} HT_Event;

/**
 * \enum HT_Fsm
 * \brief Finite State Machine definition.
 */
typedef enum {
	SM_WAIT_FOR_EVENT = 0,										/* </ Wait for an event state. */
	SM_PUSH_BUTTON_HANDLER,										/* </ Push button handler state. */
	SM_WRITE_PAYLOAD_HANDLER,									/* </ Write without response handler state. */
	SM_SEND_FRAME,												/* </ Send LoRa frame state. */
	SM_RX_LORA													/* </ RX LoRa state. */
} HT_Fsm;

/**
 * \enum HT_LoRa_Process
 * \brief LoRaWAN process typedef.
 */
typedef enum {
	PROCESS_LORA_TX,											/* </ LoRa TX process. */
	PROCESS_LORA_RX_WINDOW_2,									/* </ LoRa RX window 2 process. */
	PROCESS_LORA_READY											/* </ LoRa ready. */
} HT_LoRa_Process;

/**
 * \struct HT_Payload
 * \brief LoRa payload.
 */
typedef struct {
	uint8_t event;												/* </ Event buffer. */
	uint8_t data[PAYLOAD_SIZE];									/* </ Data buffer. */
} HT_Payload;

/* Functions ------------------------------------------------------------------*/

/*!******************************************************************
 * \fn void HT_PB_app(void)
 * \brief Application tick function.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_app(void);

/*!******************************************************************
 * \fn void HT_PB_ConfigWakeupIO(void)
 * \brief Configures all wake up sources.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_ConfigWakeupIO(void);

/*!******************************************************************
 * \fn HT_LoRa_Process HT_PB_GetLoraProcess(void)
 * \brief Gets the current LoRa process. This flag is used to handle the RX windows of the LoRa protocol.
 * 	The user button will be enabled again after both RX windows be closed.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval HT_LoRa_Process 	Current LoRa process.
 *******************************************************************/
HT_LoRa_Process HT_PB_GetLoraProcess(void);

/*!******************************************************************
 * \fn static void HT_PB_SetState(HT_Fsm new_state)
 * \brief Sets a new FSM state.
 *
 * \param[in]  HT_Fsm new_state		New state.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_SetState(HT_Fsm new_state);

/*!******************************************************************
 * \fn void HT_PB_SetLoraProcess(HT_LoRa_Process process)
 * \brief Sets a new LoRa process. This flag is used to handle the RX windows of the LoRa protocol.
 * 	The user button will be enabled again after both RX windows be closed.
 *
 * \param[in]  HT_LoRa_Process process	New LoRa process.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HT_PB_SetLoraProcess(HT_LoRa_Process process);

#endif /* __HT_API__ */

/************************ HT MICRON SEMICONDUCTORS S.A - HT_push_button.h *****END OF FILE****/
