/**
  ******************************************************************************
  * @file    hal_miscutil.h
  * @author  AMS - RF Application team
  * @version V1.0.0
  * @date    3-April-2019
  * @brief   Header file for HW miscellaneous utilities.
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
  * <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#ifndef __HAL_MISCUTIL_H__
#define __HAL_MISCUTIL_H__

#include <stdint.h>
#include "crash_handler.h"
#include "system_util.h"

#define DIE_ID_BLUENRG_LP     ((uint8_t)3)
#define JTAG_ID_CODE_LP       ((uint32_t)0x0201E041)

/**
 * @brief A structure that represents part information details
 *
 */
typedef struct PartInfoS {
  /** DIE ID number */
  uint8_t  die_id;
  /** Die major number */
  uint8_t  die_major;
  /** Die cut number */
  uint8_t  die_cut;
  /** JTAG ID */
  uint32_t jtag_id_code;
  /** Flash size in bytes */
  uint32_t flash_size;
  /** Flash size in bytes */
  uint32_t ram_size;
} PartInfoType;

/** 
 * @brief This function return a structure with information about the device
 * 
 * @param[out] partInfo Pointer to a PartInfoType structure
 *
 * @retval None
 */
void HAL_GetPartInfo(PartInfoType *partInfo);
/**
 * @brief Get Crash Information utility
 * 
 * This function return the crash information that are stored in RAM, by hard
 * handler, nmi handler and assert handler.
 * This function reset the crash information stored in RAM before it returns.
 * So it avoid to report the same crash information after a normal reboot.
 * 
 * @param[out] crashInfo Pointer to a crash_info_t structure
 *
 * @retval None
 */
void HAL_GetCrashInfo(crash_info_t *crashInfo);
/**
 * @brief Set Crash Information utility
 * 
 * This function stores crash information in RAM and reset the device
 * Crash information can be retrieved by using API HAL_GetCrashInfo
 * 
 * @param[in] msp Stack pointer containg crash info
 * @param[out] signature CRash reason signature
 *
 * @retval None
 */
void HAL_CrashHandler(uint32_t msp, uint32_t signature);

/**
  * @brief  Configure the radio to be able to reach 8dbm output power
  * @note   This function should not be called by the the application if the
  *         BLE stack is used. Instead, user must call
  *         aci_hal_set_tx_power_level() to change output power mode.
  * @param  state Enable or disable the ability to reach 8 dBm. This parameter
  *               can be set either to ENABLE or DISABLE.
  * @retval None
  */
void HAL_SetHighPower(FunctionalState state);


#endif /* __HAL_MISCUTIL_H__ */
