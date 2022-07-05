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
 * \file HT_iks01a2_api.h
 * \brief HT LoRaWAN + TagoIO Dashboard application.
 * \author HT Micron Advanced R&D
 * \link support_iot@htmicron.com.br
 * \version 1.0
 * \date January 18, 2022
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HT_IKS01A2_API_H__
#define __HT_IKS01A2_API_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rf_driver_hal_i2c_ex.h"
#include "lorawan_setup.h"
#include "i2c.h"

/* Defines --------------------------------------------------------------------*/

#define HTS221_READ_ADDR	0xBF			/* </ HTS221 read address. */
#define HTS221_WRITE_ADDR	0xBE			/* </ HTS221 write address. */

#define APP_SENSORS_DUTYCYCLE   15000		/* </ Timer timeout in milliseconds. */

#define I2C_APP_TIMEOUT	500					/* </ I2C timeout. */

/* Typedef --------------------------------------------------------------------*/

/**
 * \struct HT_payload
 * \brief LoRaWAN Payload.
 */
typedef struct {
	 int16_t temperature;					/* </ Temperature value. */
	 uint16_t humi;							/* </ Humidity value. */
	 uint8_t p;								/* </ Pressure value. */
} __attribute__((packed)) HT_payload;

/* Function Prototypes  -------------------------------------------------------*/

/*!******************************************************************
 * \fn void HT_IKS01A2_InitSensors(void)
 * \brief Initializes all sensors and also the timer that will manage the whole application.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_IKS01A2_InitSensors(void);

#endif /* __HT_IKS01A2_API_H__ */

/************************ HT MICRON SEMICONDUCTORS S.A - HT_iks01a2_api.h *****END OF FILE****/
