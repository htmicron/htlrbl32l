/**
 *
 * Copyright (c) 2021 HT Micron Semicondutors S.A.
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

#include "main.h"
#include "ble_const.h"
#include "bluenrg_lp_stack.h"
#include "clock.h"
#include "gp_timer.h"
#include "HT_gatt_db.h"
#include "osal.h"
#include "HT_ble_api.h"
#include "HT_push_button.h"

#include "lorawan_setup.h" // modified
#include "lora.h"

uint16_t envSensServHandle, pushButtonCharHandle, writePayloadCharHandle, appCharHandle;

extern uint16_t connection_handle;

extern HT_Payload payload;
extern HT_Fsm state;
extern HT_Event event;
extern lora_AppData_t AppData; // modified
//extern RxDoneParams RxBuffer;
extern uint8_t rx_flag;

/* RC service, control point characteristics definition */
static const ble_gatt_chr_def_t app_chars[] = {
    {
        .properties = BLE_GATT_SRV_CHAR_PROP_READ | BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = BLE_GATT_SRV_MAX_ENCRY_KEY_SIZE,
        .uuid = BLE_UUID_INIT_128(APP_UUID),
    },                          
};

/* RC Service definition */
static const ble_gatt_srv_def_t app_service = {
   .type = BLE_GATT_SRV_PRIMARY_SRV_TYPE,
   .uuid = BLE_UUID_INIT_128(APP_SRV_UUID),
   .chrs = {
       .chrs_p = (ble_gatt_chr_def_t *)app_chars,
       .chr_count = 1U,
   },
};    

tBleStatus Add_Env_Service(void) {
    tBleStatus ret;

    ret = aci_gatt_srv_add_service((ble_gatt_srv_def_t *)&app_service);

    if (ret != BLE_STATUS_SUCCESS) {
        printf("Error while adding Env service.\n");
        return BLE_STATUS_ERROR;
    }

    appCharHandle = aci_gatt_srv_get_char_decl_handle((ble_gatt_chr_def_t *)&app_chars[0]);

    return BLE_STATUS_SUCCESS;
}

void aci_gatt_srv_write_event(uint16_t Connection_Handle, uint8_t Resp_Needed, uint16_t Attribute_Handle, uint16_t Data_Length, uint8_t Data[])
{
    uint8_t att_error = BLE_ATT_ERR_NONE;

    if(Data[0] != '\0') {
        state = SM_WRITE_PAYLOAD_HANDLER;
        memcpy(payload.data, Data, ((Data_Length <= PAYLOAD_SIZE) ? Data_Length : PAYLOAD_SIZE));
    } else {
        att_error = 1;
    }

    if (Resp_Needed == 1U)
        aci_gatt_srv_resp(Connection_Handle, 0, att_error, 0, NULL);
}

void aci_gatt_srv_read_event(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint16_t Data_Offset) {
    if (Attribute_Handle == appCharHandle + 1) {
        state = SM_PUSH_BUTTON_HANDLER;
        sprintf((char *)payload.data, "Hello, World!");

        if(rx_flag)
        	aci_gatt_srv_resp(Connection_Handle, Attribute_Handle, Data_Offset, AppData.BuffSize, AppData.Buff);
//            aci_gatt_srv_resp(Connection_Handle, Attribute_Handle, Data_Offset, RxBuffer.Size, RxBuffer.Payload);
        else
            aci_gatt_srv_resp(Connection_Handle, Attribute_Handle, Data_Offset, strlen((char *)payload.data), 
                payload.data);
    }
}

/************************ HT MICRON SEMICONDUCTORS S.A - HT_gatt_db.c *****END OF FILE****/
