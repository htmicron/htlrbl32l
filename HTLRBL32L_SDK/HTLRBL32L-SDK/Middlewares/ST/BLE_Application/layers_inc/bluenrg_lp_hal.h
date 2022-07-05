/**
  ******************************************************************************
  * @file    rf_driver_hal.h
  * @author  AMS - RF Application team
  * @version V1.0.0
  * @date    23-May-2019
  * @brief   Header file with HAL define for BlueNRG-LP
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
  * <h2><center>&copy; COPYRIGHT 2019 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#ifndef __BLUENRG_HAL_H__
#define __BLUENRG_HAL_H__

/**
 *@addtogroup HAL HAL
 *@{
 */
/**
 *@addtogroup HAL_constants HAL/LL Constants
 *@brief Constants for Hardware abstraction Layer and Link Layer.
 *@{
 */

/**
 * @name Configuration values.
 * See @ref aci_hal_write_config_data() and @ref aci_hal_read_config_data().
 * @{
 */
#define CONFIG_DATA_PUBADDR_OFFSET                  (0x00) /**< Bluetooth public address */
#define CONFIG_DATA_ER_OFFSET                       (0x08) /**< Encryption root key used to derive LTK and CSRK */
#define CONFIG_DATA_IR_OFFSET                       (0x18) /**< Identity root key used to derive LTK and CSRK */
#define CONFIG_DATA_LL_WITHOUT_HOST                 (0x2C) /**< Switch on/off Link Layer only mode. Set to 1 to disable Host.
 	 	 	 	 	 	 	 	 	 	 	 	 	 It can be written only if aci_hal_write_config_data() is the first command
 	 	 	 	 	 	 	 	 	 	 	 	 	 after reset. */
#define CONFIG_DATA_STATIC_RANDOM_ADDRESS           (0x2E) /**< To set the static random address used by the stack, instead of the one stored in NVM. */
#define CONFIG_DATA_STORED_STATIC_RANDOM_ADDRESS    (0x80) /**< The static random address stored in NVM. */
#define CONFIG_DATA_DEBUG_KEY                       (0xD0) /**< Use debug key for secure connections. */
#define CONFIG_DATA_DLE                             (0xD1) /**< To set the maximum allowed parameter values for Data Length Extension */
/**
 * @}
 */

/**
 * @name Length for configuration values.
 * See @ref aci_hal_write_config_data() and @ref aci_hal_read_config_data().
 * @{
 */
#define CONFIG_DATA_PUBADDR_LEN                 (6)
#define CONFIG_DATA_ER_LEN                      (16)
#define CONFIG_DATA_IR_LEN                      (16)
#define CONFIG_DATA_LL_WITHOUT_HOST_LEN         (1)
#define CONFIG_DATA_STATIC_RANDOM_ADDRESS_LEN   (6)
#define CONFIG_DATA_DEBUG_KEY_LEN               (1)
#define CONFIG_DATA_DLE_LEN                     (1)
/**
 * @}
 */

/**
 * @}
 */


/**
 * @name HAL_FW_Error_Types Types for fw error event
 * @brief See aci_hal_fw_error_event().
 * @{
 */

#define HAL_FW_L2CAP_RECOMBINATION_ERROR            0x01 /**< L2CAP layer failed recombining a PDU */
#define HAL_FW_GATT_UNEXPECTED_RESPONSE_ERROR       0x02 /**< GATT layer received an unexpteced response. Peer probably violated the ATT protocol. */
#define HAL_FW_GATT_SEQUENTIAL_PROTOCOL_ERROR       0x03 /**< GATT layer received an unexpteced request. Peer probably violated the sequentiality of ATT protocol. */
#define HAL_FW_BONDING_DB_FULL_GATTSERVICE_ERROR    0x04 /**< No space to store info GATT database info in NVM. Database needs to be cleaned up (remove invalidated records) or some bonding entries need to be removed. */
#define HAL_FW_BONDING_DB_FULL_PAIRING_ERROR        0x05 /**< No space to store bonding info in NVM. Database needs to be cleaned up (remove invalidated records) or some bonding entries need to be removed. */
#define HAL_FW_SCHEDULER_OVERRUN_ERROR              0x06 /**< Link Layer scheduler failed to reschedule slots for too many times. This may indicate an unrecoverable situation. A system reset is recommended. */ 

/**
 * @}
 */

/**
 * @}
 */


#endif /* __BLUENRG_HAL_ACI_H__ */
