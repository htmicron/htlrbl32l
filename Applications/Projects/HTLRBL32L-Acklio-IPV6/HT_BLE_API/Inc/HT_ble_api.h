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
 * \file HT_ble_api.h
 * \brief Bluetooth Low Energy API for Push Button LoRa+BLE application.
 * \author HT Micron Advanced R&D
 * \link support_iot@htmicron.com.br
 * \version 1.0
 * \date July 03, 2021
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HT_BLE_API__
#define __HT_BLE_API__

/* Includes  ------------------------------------------------------------------*/
#include "main.h"
#include "HT_push_button.h"
#include "HT_gatt_db.h"

/* Defines  ------------------------------------------------------------------*/

/* Advertising interval */
#define ADV_INTERVAL_FAST_MS  100            
#define ADV_INTERVAL_SLOW_MS  1000

/* Push Button LoRa+BLE Bluetooth characteristics. */
#define APP_UUID    0x19,0x95,0xd5,0xa5,0x02,0x00,0xe3,0xa9,0xe2,0x11,0x77,0xe4,0x20,0x55,0x2e,0xa3
#define APP_SRV_UUID    0x19,0x96,0xd5,0xa5,0x02,0x00,0xe3,0xa9,0xe2,0x11,0x77,0xe4,0x20,0x55,0x2e,0xa3

/* Functions  ------------------------------------------------------------------*/

/*!******************************************************************
 * \fn void HT_BLE_SetDeviceConnectable(void)
 * \brief Set connectable mode.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_BLE_SetDeviceConnectable(void);

/*!******************************************************************
 * \fn void HT_BLE_BleConfig(void)
 * \brief Init bluetooth stack.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_BLE_BleConfig(void);

/*!******************************************************************
 * \fn void HT_BLE_ConfigureDeviceAdvertising(uint16_t adv_interval)
 * \brief Configure bluetooth advertising interval.
 *
 * \param[in]  uint16_t adv_interval             Advertising interval
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_BLE_ConfigureDeviceAdvertising(uint16_t adv_interval);

/*!******************************************************************
 * \fn void HT_BLE_DisableConnectableDevice(void)
 * \brief Disable connectable mode.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_BLE_DisableConnectableDevice(void);

#endif /* __HT_BLE_API__ */

/************************ HT MICRON SEMICONDUCTORS S.A - HT_bke_api.h *****END OF FILE****/
