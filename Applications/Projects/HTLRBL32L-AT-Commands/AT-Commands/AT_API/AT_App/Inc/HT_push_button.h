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
 * \date July 03, 2021
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
	PROCESS_LORA_TX,
	PROCESS_LORA_RX_WINDOW_2,
	PROCESS_LORA_IDLE
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
 * \fn void HT_PB_Fsm(void)
 * \brief Finite state machine function.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_Fsm(void);

/*!******************************************************************
 * \fn void HT_PB_WritePayloadState(void)
 * \brief Write without response handler state.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_WritePayloadState(void);

/*!******************************************************************
 * \fn void HT_PB_SendFrameState(void)
 * \brief Send a LoRa frame based on the previous event.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_SendFrameState(void);

/*!******************************************************************
 * \fn void HT_PB_PushButtonState(void)
 * \brief Push button handler state.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_PushButtonState(void);

/*!******************************************************************
 * \fn void HT_PB_WaitForEventState(void)
 * \brief Keep waiting for an event.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_WaitForEventState(void);

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
 * \fn void HT_PB_SendLoraFrame(void)
 * \brief Sends a LoRaWAN frame containing what was received by bluetooth.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_SendLoraFrame(void);

/*!******************************************************************
 * \fn void HT_PB_RxLoraState(void)
 * \brief LoRaWAN RX handler. Saves RX buffer to send it in the next bluetooth read event.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_PB_RxLoraState(void);

#endif /* __HT_API__ */

/************************ HT MICRON SEMICONDUCTORS S.A - HT_push_button.h *****END OF FILE****/
