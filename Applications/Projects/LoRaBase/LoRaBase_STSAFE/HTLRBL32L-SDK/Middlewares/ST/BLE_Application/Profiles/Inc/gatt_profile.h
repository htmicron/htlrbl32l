/**
  ******************************************************************************
  * @file    gatt_profile.h
  * @author  RF Application team
  * @version V1.0.0
  * @date    31 March 2020
  * @brief   Header file for Generic Attribute Profile Service (GATT)
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT STMicroelectronics</center></h2>
  ******************************************************************************
  */
#ifndef GATT_PROFILE_H
#define GATT_PROFILE_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "stdint.h"
#include "system_util.h"
#include "ble_status.h"

#include "bluenrg_lp_api.h"
/******************************************************************************
 * CONSTANT SYMBOLS
 *****************************************************************************/
#if defined(CONFIG_NUM_MAX_LINKS)
#define GATT_SRV_MAX_CONN                                   (CONFIG_NUM_MAX_LINKS)
#else
#define GATT_SRV_MAX_CONN                                   (8U)
#endif

#define GATT_CHR_SERVICE_CHANGED_VALUE_LEN                  (4U)

/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/

/**
 * @brief Initialize GATT Profile
 *
 * @return void
 *
 */
tBleStatus Gatt_profile_init(void);

/**
 * @brief Change access permission for the provided attribute handle.
 *
 * @param attr_h The requested attribute handle to change.
 * @param perm the new permission value.
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the access permission are set
 * - BLE_STATUS_FAILED: the requested attribute is not in the GATT service group
 *                     or the attribute can't be altered.
 *
 */
tBleStatus Gatt_profile_set_access_permission(uint16_t attr_h, uint8_t perm);

/**
 * @brief Change security permission for the provided attribute handle.
 *
 * @param attr_h The requested attribute handle to change.
 * @param perm the new permission value.
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the security permission are set.
 * - BLE_STATUS_NOT_ALLOWED: the requested permissions are not allowed.
 * - BLE_STATUS_FAILED: the requested attribute is not in the GATT service group
 *                     or the attribute can't be altered.
 *
 */
tBleStatus Gatt_profile_set_security_permission(uint16_t attr_h, uint8_t perm);

/**
 * @brief Retrieve GATT profile service handle.
 *
 * @return: service handle.
 *
 */
uint16_t Gatt_profile_get_service_handle(void);

/**
 * @brief Retrieve GATT service definition pointer.
 *
 * @return: service definition pointer.
 *
 */
ble_gatt_srv_def_t *Gatt_profile_get_service_definition_p(void);

#endif

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
