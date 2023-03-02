/**
 ******************************************************************************
 * @file    nvm_db_upper_layer.c
 * @author  AMS - RF Application Team
 * @brief   Adaptation layer between NVM database manager and Bluetooth LE stack
 *          interface for NVM data.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include "rf_driver_ll_flash.h"
#include "rf_driver_hal_vtimer.h"
#include "nvm_db.h"
#include "nvm_db_conf.h"
#include "bleplat.h"
#include "bluenrg_lp_stack.h"
#include "link_layer.h"

void BLEPLAT_Init(void);

/** @defgroup NVM_UpperLayer  NVM Upper layer
 * @{
 */

/** @defgroup NVM_UpperLayer_TypesDefinitions Private Type Definitions
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_UpperLayer_Private_Defines Private Defines
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_UpperLayer_Private_Macros Private Macros
 * @{
 */

#define DEBUG_GPIO2_HIGH()
#define DEBUG_GPIO2_LOW()

#ifdef DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/**
 * @}
 */

/** @defgroup NVM_UpperLayer_Private_Variables Private Variables
 * @{
 */

static NVMDB_HandleType sec_gatt_db_h, device_id_db_h, *curr_handle_p;

/**
 * @}
 */

/** @defgroup NVM_UpperLayer_External_Variables External Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_UpperLayer_Private_FunctionPrototypes Private Function Prototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_UpperLayer_Private_Functions Private Functions
 * @{
 */

/* Implementation of the function needed by NVM manager to safely execute Flash
 * operations while radio is active. */
uint8_t NVMDB_TimeCheck(int32_t time)
{    
  uint32_t current_time, next_radio_activity_time;
  
  current_time = HAL_VTIMER_GetCurrentSysTime();  
    
  if(BLE_STACK_ReadNextRadioActivity(&next_radio_activity_time) == LL_IDLE)
    return TRUE;  
  
  if((int32_t)(next_radio_activity_time - current_time) > time)
    return TRUE;
  
  return FALSE;
  
}

/**
 * @}
 */

/** @defgroup NVM_UpperLayer_Public_Functions Public Functions
 * @{
 */

void BLEPLAT_Init(void)
{
  NVMDB_Init();

  NVMDB_HandleInit(SEC_GATT_BD, &sec_gatt_db_h);
  NVMDB_HandleInit(DEVICE_ID_DB, &device_id_db_h);
  curr_handle_p = &sec_gatt_db_h;
}

bleplat_nvm_status BLEPLAT_NvmAdd( bleplat_nvm_record_type type,
                           const uint8_t* data,
                           uint16_t size,
                           const uint8_t* extra_data,
                           uint16_t extra_size )
{
  NVMDB_status_t ret;

  if(type == BLEPLAT_NVM_TYPE_DEVICE_ID)
  {
    curr_handle_p = &device_id_db_h;
  }
  else
  {
    curr_handle_p = &sec_gatt_db_h;
  }

  DEBUG_GPIO2_HIGH();

  ret = NVMDB_AppendRecord(curr_handle_p, type, size, data, extra_size, extra_data);

  DEBUG_GPIO2_LOW();

  if(ret == NVMDB_STATUS_OK)
  {
    return BLEPLAT_OK;
  }

  if(ret == NVMDB_STATUS_FULL_DB)
  {
    return BLEPLAT_FULL;
  }

  return BLEPLAT_BUSY;
}

bleplat_nvm_status BLEPLAT_NvmGet( bleplat_nvm_record_mode mode,
                           bleplat_nvm_record_type type,
                           uint16_t offset,
                           uint8_t* data,
                           uint16_t size )
{
  NVMDB_RecordSizeType size_out;
  NVMDB_status_t ret;
  NVMDB_IdType db_id;

  if(type == BLEPLAT_NVM_TYPE_DEVICE_ID)
  {
    curr_handle_p = &device_id_db_h;
    db_id = 1;
  }
  else
  {
    curr_handle_p = &sec_gatt_db_h;
    db_id = 0;
  }

  if(mode == BLEPLAT_NVM_CURRENT)
  {
    ret = NVMDB_ReadCurrentRecord(curr_handle_p, offset, data, size, &size_out);
  }
  else
  {
    if(mode == BLEPLAT_NVM_FIRST)
    {
      NVMDB_HandleInit(db_id, curr_handle_p);
    }
    ret = NVMDB_ReadNextRecord(curr_handle_p, type, offset, data, size, &size_out);
  }

  if(ret == NVMDB_STATUS_OK)
  {
    return BLEPLAT_OK;
  }

  if(ret == NVMDB_STATUS_END_OF_DB)
  {
    return BLEPLAT_EOF;
  }

  return BLEPLAT_BUSY;
}

int BLEPLAT_NvmCompare(uint16_t offset, const uint8_t *data, uint16_t size)
{
  int ret;

  ret = NVMDB_CompareCurrentRecord(curr_handle_p, offset, data, size);

  if(ret == 0)
  {
    return BLEPLAT_OK;
  }
  else if(ret < 0)
  {
    return size;
  }
  else
  {
    return BLEPLAT_EOF;
  }
}

void BLEPLAT_NvmDiscard(bleplat_nvm_record_mode mode)
{
  DEBUG_GPIO2_HIGH();
  if(mode == BLEPLAT_NVM_CURRENT)
  {
    if(curr_handle_p == &device_id_db_h) // Do not allow to erase device ID data.
    {
      return;
    }
    NVMDB_DeleteRecord(curr_handle_p);
  }
  else if(mode == BLEPLAT_NVM_ALL)
  {

    NVMDB_Erase(SEC_GATT_BD);

    /* Implementation that does not cause an immediate flash erase.
       NVMDB_HandleInit(SEC_GATT_BD, &sec_gatt_db_h);

       while(1)
       {
       NVMDB_RecordSizeType size_out;
       NVMDB_status_t ret;

       ret = NVMDB_ReadNextRecord(&sec_gatt_db_h, ALL_TYPES, 0, NULL, 0, &size_out);
       if(ret == NVMDB_STATUS_OK)
        NVMDB_DeleteRecord(&sec_gatt_db_h);
       else
        return;
       }*/
  }
  DEBUG_GPIO2_LOW();
}

/**
 * @}
 */

/**
 * @}
 */
