/**
  ******************************************************************************
  * @file    sx1261dvk1bas.h
  * @author  MCD Application Team
  * @brief   This file contains definitions shared IO definitions for SX126x
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SX1261DVK1BAS_H__
#define __SX1261DVK1BAS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "sx1261dvk1bas_conf.h"
/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef void (DioIrqHandler)(void);
/*!
 * Hardware IO IRQ callback function definition
 */
typedef enum
{
  RFSW_OFF = 0,
  RFSW_RX,
  RFSW_RFO_LP,
  RFSW_RFO_HP,
  RFSW_RFO_LF,
  RFSW_ON
} RfSw_TypeDef;

typedef enum
{
  CONF_RFO_LP_HP = 0,
  CONF_RFO_LP = 1,
  CONF_RFO_HP = 2,
  CONF_RFO_LF = 3,
} TxConfig_TypeDef;

/* RADIO_DIO_TypeDef is defined in case SX1261DVK1BAS_RADIO_IRQHandler() API is used */
typedef enum
{
  RADIO_DIO_1 = 1U,

} RADIO_DIO_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define IRQ_HIGH_PRIORITY  0

#define SX1261                                      1
#define SX1262                                      2

/* Exported variables------------------------------------------------------- */
extern EXTI_HandleTypeDef hRADIO_DIO_exti[RADIO_DIOn];

/* Exported functions ------------------------------------------------------- */

/*!
 * \brief Initializes the radio I/Os pins interface
 */
void SX1261DVK1BAS_RADIO_IoInit(void);

/*!
 * \brief Initializes DIO IRQ handlers
 *
 * \param [IN] irqHandlers Array containing the IRQ callback functions
 */
void SX1261DVK1BAS_RADIO_IoIrqInit(DioIrqHandler **irqHandlers);

/*!
 * \brief De-initializes the radio I/Os pins interface.
 *
 * \remark Useful when going in MCU low power modes
 */
void SX1261DVK1BAS_RADIO_IoDeInit(void);

/*!
 * \brief HW Reset of the radio
 */
void SX1261DVK1BAS_RADIO_Reset(void);

/*!
 * \brief Blocking loop to wait while the Busy pin in high
 */
void SX1261DVK1BAS_RADIO_WaitOnBusy(void);

/*!
 * \brief Set the antenna switch on the requested input
 * \param  requested input
 */
void SX1261DVK1BAS_RADIO_SetAntSw(RfSw_TypeDef state);

/*!
 * \brief Wakes up the radio
 */
void SX1261DVK1BAS_RADIO_WakeUp(void);

/*!
 * \brief Send a command that write and read data to the radio
 *
 * \param  [in]   txData        data to be sent
 * \return [out]  rxdata        data to be read
 */
uint16_t SX1261DVK1BAS_RADIO_SendRecv(uint16_t txData);

/*!
 * \brief Chip select of the board
 *
 * \param  [in]   state       0 state is 0, 1 otherwise
 */
void SX1261DVK1BAS_RADIO_ChipSelect(int32_t state);

/*!
 * \brief Gets the board PA selection configuration
 *
 * \param [IN] channel Channel frequency in Hz
 * \retval PaSelect RegPaConfig PaSelect value
 */
uint8_t SX1261DVK1BAS_RADIO_GetPaSelect(uint32_t channel);

/*!
 * \brief Checks if the given RF frequency is supported by the hardware
 *
 * \param [IN] frequency RF frequency to be checked
 * \retval isSupported [true: supported, false: unsupported]
 */
bool SX1261DVK1BAS_RADIO_CheckRfFrequency(uint32_t frequency);

/*!
 * \brief Get Board Wake Up time
 * \param  none
 * \retval Wakeup time
 */
uint32_t SX1261DVK1BAS_RADIO_GetWakeUpTime(void);

/*!
 * \brief Checks if tcxo is present
 *
 * \retval [true: tcxo, false: no tcxo]
 */
bool SX1261DVK1BAS_RADIO_BoardIsTcxo(void);

/*!
 * \brief Set Led Tx
 *
 * \retval [true: on, false: off]
 */
void SX1261DVK1BAS_RADIO_BoardSetLedTx(bool state);

/*!
 * \brief Set Led Rx
 *
 * \retval [true: on, false: off]
 */
void SX1261DVK1BAS_RADIO_BoardSetLedRx(bool state);

/*!
 * \brief SPI Bus init
 */
void SX1261DVK1BAS_RADIO_Bus_Init(void);

/*!
 * \brief SPI Bus Deinit
 */
void SX1261DVK1BAS_RADIO_Bus_deInit(void);

#ifdef __cplusplus
}
#endif


#endif /* __SX1261DVK1BAS_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
