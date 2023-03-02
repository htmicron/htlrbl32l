/******************** (C) COPYRIGHT 2020 STMicroelectronics ********************
* File Name          : gatt_profile.c
* Author             : SRA - BLE stack team
* Description        : Generic Attribute Profile Service (GATT)
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/******************************************************************************
 * INCLUDE HEADER FILES
 *****************************************************************************/
#include "gatt_profile.h"
#include <string.h>
#include "osal.h"
#include "bluenrg_lp_api.h"

/******************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************/
/**
 *@defgroup Service Changed Characteristic value.
 *@{
 */
/**
 * Characteristic value buffer.
 */
static const uint8_t gatt_chr_srv_changed_buff[GATT_CHR_SERVICE_CHANGED_VALUE_LEN] =
                                                {0x00U, 0x00U, 0xffU, 0xffU};

static const ble_gatt_val_buffer_def_t gatt_chr_srv_changed_value_buff = {
    .buffer_len = GATT_CHR_SERVICE_CHANGED_VALUE_LEN,
    .buffer_p = (uint8_t *)gatt_chr_srv_changed_buff,
};
/**
 *@}
 */

/**
 *@defgroup Client Supported Feature Characteristic value.
 *@{
 */
/**
 * The following buffer store the Client Supported Feature characteristic
 * value, as described in 7.2 CLIENT SUPPORTED FEATURES - BLUETOOTH CORE
 * SPECIFICATION Version 5.1 | Vol 3, Part G page 2403.
 * The assigned bits are reported in Table 7.6: Client Supported Features
 * bit assignments.
 */
static uint8_t gatt_client_supp_feature_buff[BLE_GATT_SRV_CLIENT_SUP_FEATURE_SIZE_X_CONN(GATT_SRV_MAX_CONN)];

static const ble_gatt_val_buffer_def_t gatt_client_supp_feature_val_buff = {
    .buffer_len = BLE_GATT_SRV_CLIENT_SUP_FEATURE_SIZE_X_CONN(GATT_SRV_MAX_CONN),
    .buffer_p = gatt_client_supp_feature_buff,
};
/**
 *@}
 */

/**
 * Service Changed CCCD.
 */
BLE_GATT_SRV_CCCD_DECLARE(gatt_chr_srv_changed,
                          GATT_SRV_MAX_CONN,
                          BLE_GATT_SRV_CCCD_PERM_DEFAULT,
                          BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG);

static const ble_gatt_chr_def_t gatt_chrs[] = {
    {
        /**< Service Changed Characteristic. */
        .properties = BLE_GATT_SRV_CHAR_PROP_INDICATE,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_SERVICE_CHANGE_CHR_UUID),
        .val_buffer_p = (ble_gatt_val_buffer_def_t *)&gatt_chr_srv_changed_value_buff,
        .descrs = {
            .descrs_p = &BLE_GATT_SRV_CCCD_DEF_NAME(gatt_chr_srv_changed),
            .descr_count = 1U,
        },
    },
    {
        /**< Client Supported Features Characteristic. */
        .properties = BLE_GATT_SRV_CHAR_PROP_READ | BLE_GATT_SRV_CHAR_PROP_WRITE,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_CLIENT_SUPP_FEATURE_CHR_UUID),
        .val_buffer_p = (ble_gatt_val_buffer_def_t *)&gatt_client_supp_feature_val_buff,
    },
    {
        /**< Database Hash Characteristic. Value buffer is allocated into the stack. */
        .properties = BLE_GATT_SRV_CHAR_PROP_READ,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_DB_HASH_CHR_UUID),
    }
};

static const ble_gatt_srv_def_t gatt_srvc = {
    .type = BLE_GATT_SRV_PRIMARY_SRV_TYPE,
    .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_GATT_SERVICE_UUID),
    .chrs = {
        .chrs_p = (ble_gatt_chr_def_t *)gatt_chrs,
        .chr_count = 3U,
    },
};

tBleStatus Gatt_profile_init()
{
    return aci_gatt_srv_add_service((ble_gatt_srv_def_t *)&gatt_srvc);
}

tBleStatus Gatt_profile_set_access_permission(uint16_t attr_h, uint8_t perm)
{
    uint16_t cccd_handle;

    cccd_handle = aci_gatt_srv_get_descriptor_handle(
                            &BLE_GATT_SRV_CCCD_DEF_NAME(gatt_chr_srv_changed));
    if ((cccd_handle != BLE_ATT_INVALID_ATTR_HANDLE) && (cccd_handle == attr_h))
    {
        /**
         * Clear previous set access permissions.
         */
        BLE_GATT_SRV_CCCD_DEF_NAME(gatt_chr_srv_changed).properties &=
                                        ~BLE_GATT_SRV_CHAR_PROP_ACCESS_PERM_MASK;
        BLE_GATT_SRV_CCCD_DEF_NAME(gatt_chr_srv_changed).properties |= (perm &
                                        BLE_GATT_SRV_CHAR_PROP_ACCESS_PERM_MASK);

        return BLE_STATUS_SUCCESS;
    }
    else
    {
        return BLE_STATUS_FAILED;
    }
}

tBleStatus Gatt_profile_set_security_permission(uint16_t attr_h, uint8_t perm)
{
    uint16_t cccd_handle;

    cccd_handle = aci_gatt_srv_get_descriptor_handle(
                            &BLE_GATT_SRV_CCCD_DEF_NAME(gatt_chr_srv_changed));
    if ((cccd_handle != BLE_ATT_INVALID_ATTR_HANDLE) && (cccd_handle == attr_h))
    {
        if ((perm & (BLE_GATT_SRV_PERM_ENCRY_READ |
                     BLE_GATT_SRV_PERM_AUTHEN_READ)) != 0U)
        {
            /**
             * <<Readable with no authentication or authorization.
             *   Writable with authentication and authorization defined by a
             *   higher layer specification or is implementation specific.>>
             *
             * Table 3.10: Client Characteristic Configuration declaration
             * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part G page 1556
             */
            return BLE_STATUS_NOT_ALLOWED;
        }

        BLE_GATT_SRV_CCCD_DEF_NAME(gatt_chr_srv_changed).permissions = perm;

        return BLE_STATUS_SUCCESS;
    }
    else
    {
        return BLE_STATUS_FAILED;
    }
}

uint16_t Gatt_profile_get_service_handle(void)
{
    return aci_gatt_srv_get_service_handle((ble_gatt_srv_def_t *)&gatt_srvc);
}

ble_gatt_srv_def_t *Gatt_profile_get_service_definition_p(void)
{
    return (ble_gatt_srv_def_t *)&gatt_srvc;
}

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
