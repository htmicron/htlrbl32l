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
 * \file HT_gatt_db.h
 * \brief GATT configuration for Push Button LoRa+BLE application.
 * \author HT Micron Advanced R&D
 * \link support_iot@htmicron.com.br
 * \version 1.0
 * \date July 03, 2021
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HT_GATT_DB_H__
#define __HT_GATT_DB_H__

/* Includes  ------------------------------------------------------------------*/
#include "main.h"

/* Functions  ------------------------------------------------------------------*/

/*!******************************************************************
 * \fn tBleStatus Add_Env_Service(void)
 * \brief Add environment service.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
tBleStatus Add_Env_Service(void);

/*!******************************************************************
 * \fn tBleStatus Add_Frame_Notify_Service(void)
 * \brief Add notify service.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
tBleStatus Add_Frame_Notify_Service(void);

#endif /* __GATT_DB_H__ */

/************************ HT MICRON SEMICONDUCTORS S.A - HT_gatt_db.h *****END OF FILE****/
