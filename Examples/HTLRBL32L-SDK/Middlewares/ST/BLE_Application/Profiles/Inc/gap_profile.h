/**
  ******************************************************************************
  * @file    gap_profile.h
  * @author  RF Application team
  * @version V1.0.0
  * @date    31 March 2020
  * @brief   Header file for Generic Access Profile Service (GAP)
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
#ifndef GAP_PROFILE_H
#define GAP_PROFILE_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "system_util.h"
#include "ble_status.h"

#include "bluenrg_lp_api.h"
/******************************************************************************
 * CONSTANT SYMBOLS
 *****************************************************************************/
#define GAP_CHR_DEVICE_NAME_VAL_LEN_MAX     (50U)
#define GAP_CHR_APPEARANCE_VAL_LEN          (2U)
#define GAP_CHR_PERIPH_PREF_CONN_PARAMS_LEN (8U)
#define GAP_CHR_CENTRAL_ADDR_RESOLUTION_LEN (1U)

/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/

/**
 * @brief Initialize GAP Profile
 *
 * @return void
 *
 */
tBleStatus Gap_profile_init(uint8_t role,
                            uint8_t privacy_type,
                            uint8_t device_name_max_len);

/**
 * @brief Return attribute handles.
 *
 * @param[out] srvc_h GAP Service attribute handle.
 * @param[out] dev_name_h Device Name Characteristic attribute handle.
 * @param[out] appearance_h Appearance Characteristic attribute handle.
 *
 * @return void
 */
void Gap_profile_get_handles(uint16_t *srvc_h,
                             uint16_t *dev_name_h,
                             uint16_t *appearance_h);

/**
 * @brief Set device name value.
 *
 * @param offset Offset from which start to write the device name.
 * @param length Data length.
 * @param[in] dev_name_p Pointer to the data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the characteristic value is updated correctly
 * - BLE_STATUS_INVALID_PARAMS: invalid parameter.
 *
 */
tBleStatus Gap_profile_set_dev_name(uint16_t offset,
                                    uint16_t length,
                                    uint8_t *dev_name_p);

/**
 * @brief Set appearance value.
 *
 * @param offset Offset from which start to write appearance value.
 * @param length Data length.
 * @param[in] appearance_p Pointer to the data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the characteristic value is updated correctly
 * - BLE_STATUS_INVALID_PARAMS: invalid parameter.
 *
 */
tBleStatus Gap_profile_set_appearance(uint16_t offset,
                                      uint16_t length,
                                      uint8_t *appearance_p);

/**
 * @brief Set preferred connection parameter value.
 *
 * @param offset Offset from which start to write value.
 * @param length Data length.
 * @param[in] pref_conn_param_p Pointer to the data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the characteristic value is updated correctly
 * - BLE_STATUS_INVALID_PARAMS: invalid parameter.
 *
 */
tBleStatus Gap_profile_set_pref_conn_par(uint16_t offset,
                                         uint16_t length,
                                         uint8_t *pref_conn_param_p);

/**
 * @brief Set GAP characteristic value.
 *
 * @param attr_h Attribute handle to write.
 * @param val_offset Offset from which start to write the device name.
 * @param val_length Data length.
 * @param[in] val_p Pointer to the data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the characteristic value is updated correctly
 * - BLE_STATUS_INVALID_PARAMS: invalid parameter.
 *
 */
tBleStatus Gap_profile_set_char_value(uint16_t attr_h,
                                      uint16_t val_offset,
                                      uint16_t val_length,
                                      uint8_t *val_p);

/**
 * @brief Change access permission for the provided attribute handle.
 *
 * @param attr_h The requested attribute handle to change.
 * @param perm the new permission value.
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the access permission are set
 * - BLE_STATUS_FAILED: the requested attribute is not in the GAP service group
 *                      or the attribute can't be altered.
 *
 */
tBleStatus Gap_profile_set_access_permission(uint16_t attr_h, uint8_t perm);

/**
 * @brief Change security permission for the provided attribute handle.
 *
 * @param attr_h The requested attribute handle to change.
 * @param perm the new permission value.
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the security permission are set.
 * - BLE_STATUS_NOT_ALLOWED: the requested permissions are not allowed.
 * - BLE_STATUS_FAILED: the requested attribute is not in the GAP service group
 *                      or the attribute can't be altered.
 *
 */
tBleStatus Gap_profile_set_security_permission(uint16_t attr_h, uint8_t perm);

/**
 * @brief Retrieve GAP profile service handle.
 *
 * @return: service handle.
 *
 */
uint16_t Gap_profile_get_service_handle(void);

/**
 * @brief Retrieve GAP service definition pointer.
 *
 * @return: service definition pointer.
 *
 */
ble_gatt_srv_def_t *Gap_profile_get_service_definition_p(void);

#endif

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
