/**
  ******************************************************************************
  * @file    link_layer.h
  * @author  AMS - RF Application team
  * @version V1.0.0
  * @date    23-May-2019
  * @brief   Header file for Bluetooth LE link layer constants.
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
#ifndef _LINK_LAYER_H
#define _LINK_LAYER_H

/**
 *@addtogroup GAP GAP
 *@brief Generic Access Profile
 *@{
 */

/**
 * @defgroup Link_Layer Link Layer constants and types
 * @brief Constants and types related to Link Layer functions
 * @{
 */

/**
 * Bluetooth 48 bit address (in little-endian order).
 */
typedef	uint8_t	tBDAddr[6];


/**
 *@name Bluetooth address types
 * Bluetooth address types
 *@{
 */
#define PUBLIC_ADDR                 (0)
#define RANDOM_ADDR                 (1)
#define STATIC_RANDOM_ADDR          (1)
#define RESOLVABLE_PRIVATE_ADDR     (2)
#define NON_RESOLVABLE_PRIVATE_ADDR (3)
/**
 * @}
 */

/**
 * @name Advertising events properties
 * @{
 */
#define ADV_PROP_NONE                     0x00
#define ADV_PROP_CONNECTABLE              0x01
#define ADV_PROP_SCANNABLE                0x02
#define ADV_PROP_DIRECTED                 0x04
#define ADV_PROP_HDC_DIRECTED             0x08
#define ADV_PROP_LEGACY                   0x10
#define ADV_PROP_ANONYMOUS                0x20
#define ADV_PROP_INCLUDE_TX_POWER         0x40
/**
 * @}
 */

/**
 * @name Advertising channels
 * @{
 */
#define ADV_CH_37  0x01
#define ADV_CH_38  0x02
#define ADV_CH_39  0x04
#define ADV_CH_ALL 0x07
/**
 * @}
 */

/**
 * @name Scan types
 * @{
 */
#define PASSIVE_SCAN    0
#define ACTIVE_SCAN     1
/**
 * @}
 */

/**
 * @name Duplicate filtering
 * @{
 */
#define DUPLICATE_FILTER_DISABLED                   0
#define DUPLICATE_FILTER_ENABLED                    1
#define DUPLICATE_FILTER_ENABLED_FOR_SCAN_PERIOD    2
/**
 * @}
 */

/**
 * @name Bitmasks for Link Layer PHYs
 * @{
 */
#define LE_1M_PHY_BIT       0x01
#define LE_2M_PHY_BIT       0x02
#define LE_CODED_PHY_BIT    0x04

/**
 * @}
 */
   
/**
 * @name Values for Link Layer PHYs
 * @{
 */
#define LE_1M_PHY           0x01
#define LE_2M_PHY           0x02
#define LE_CODED_PHY        0x03
#define LE_CODED_PHY_S8     0x03
#define LE_CODED_PHY_S2     0x04

/**
 * @}
 */

/**
 *@name Advertising filter policy
 *Advertising policy for filtering (white list related) 
 *@{
 */
#define ADV_NO_WHITE_LIST_USE           (0x00)  /**< Process scan and connection requests from all devices (i.e., the White List is not in use) */
#define ADV_WHITE_LIST_FOR_ONLY_SCAN    (0x01)  /**< Process connection requests from all devices and only scan requests from devices that are in the White List */
#define ADV_WHITE_LIST_FOR_ONLY_CONN    (0x02)  /**< Process scan requests from all devices and only connection requests from devices that are in the White List */
#define ADV_WHITE_LIST_FOR_ALL          (0x03)  /**< Process scan and connection requests only from devices in the White List. */
/**
 * @}
 */

/**
 *@name Scanning filter policy
 *Advertising policy for filtering (white list related) 
 *@{
 */
/** Accept all advertising and scan response PDUs except directed advertising PDUs not addressed to this device */
#define SCAN_ACCEPT_ALL                                  (0x00)
/** Accept only advertising and scan response PDUs from devices where
  * the advertiser’s address is in the White List. Directed advertising PDUs
  * which are not addressed to this device shall be ignored */
#define SCAN_ACCEPT_WHITE_LIST_ONLY                      (0x01)
/** Accept all advertising and scan response PDUs except directed advertising
  * PDUs where the initiator’s identity address does not address this
  * device.
  *
  * Note: Directed advertising PDUs where the initiator’s address is a
  * resolvable private address that cannot be resolved are also accepted. */
#define SCAN_ACCEPT_ALL_N_USE_RESOLVING_LIST               (0x02)
/** Accept all advertising and scan response PDUs except:
 * @li advertising and scan response PDUs where the advertiser’s identity
 * address is not in the White List; and
 * @li directed advertising PDUs where the initiator’s identity address does
 * not address this device
 *
 * Note: Directed advertising PDUs where the initiator’s address is a
 * resolvable private address that cannot be resolved are also accepted. */
#define SCAN_ACCEPT_WHITE_LIST_ONLY_N_USE_RESOLVING_LIST   (0x03)
/**
 * @}
 */

/**
 * @name Link Layer State
 * @{
 */   
#define LL_IDLE         0x00
#define LL_ADV          0x01
#define LL_CONN_SLAVE   0x02
#define LL_SCAN         0x03
#define LL_CONN_REQ     0x04
#define LL_CONN_MASTER  0x05
#define LL_TX_TEST      0x06
#define LL_RX_TEST      0x07
/**
 * @}
 */

/**
 * @name Reason for hci_le_transmit_power_reporting_event()
 * @{
 */
#define LOCAL_TX_POWER_CHANGE               0x00
#define REMOTE_TX_POWER_CHANGE              0x01
#define READ_REMOTE_TX_POWER_COMPLETE       0x02
/**
 * @}
 */

/**
 * @name Transmit_Power_Level value
 * @{
 */
#define POWER_NOT_MANAGED                   0x7E
#define POWER_NA                            0x7F
/**
 * @}
 */

/**
 * @name Transmit_Power_Level_Flag values
 * @{
 */
#define MIN_TX_POWER_BIT                    0x01
#define MAX_TX_POWER_BIT                    0x02
/**
 * @}
 */
   
/**
 * @name LE Event Mask
 * @see hci_le_set_event_mask()
 * @{
 */
#define HCI_LE_EVT_MASK_BYTE0_CONNECTION_COMPLETE                                         (0x01U)
#define HCI_LE_EVT_MASK_BYTE0_ADVERTISING_REPORT                                          (0x02U)
#define HCI_LE_EVT_MASK_BYTE0_CONNECTION_UPDATE_COMPLETE                                  (0x04U)
#define HCI_LE_EVT_MASK_BYTE0_READ_REMOTE_FEATURES_COMPLETE                               (0x08U)
#define HCI_LE_EVT_MASK_BYTE0_LTK_REQUEST                                                 (0x10U)
#define HCI_LE_EVT_MASK_BYTE0_REMOTE_CONNECTION_PARAMETER_REQUEST                         (0x20U)
#define HCI_LE_EVT_MASK_BYTE0_DATA_LEN_CHANGE                                             (0x40U)
#define HCI_LE_EVT_MASK_BYTE0_READ_LOCAL_P256_COMPLETE                                    (0x80U)
#define HCI_LE_EVT_MASK_BYTE1_GENERATE_DHKEY_COMPLETE                                     (0x01U)
#define HCI_LE_EVT_MASK_BYTE1_ENHANCED_CONNECTION_COMPLETE                                (0x02U)
#define HCI_LE_EVT_MASK_BYTE1_DIRECTED_ADVERTISING_REPORT                                 (0x04U)
#define HCI_LE_EVT_MASK_BYTE1_PHY_UPDATE_COMPLETE                                         (0x08U)
#define HCI_LE_EVT_MASK_BYTE1_EXTENDED_ADVERTISING_REPORT                                 (0x10U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_SYNC_ESTABLISHED                       (0x20U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_REPORT                                 (0x40U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_SYNC_LOST                              (0x80U)
#define HCI_LE_EVT_MASK_BYTE2_SCAN_TIMEOUT                                                (0x01U)
#define HCI_LE_EVT_MASK_BYTE2_ADVERTISING_SET_TERMINATED                                  (0x02U)
#define HCI_LE_EVT_MASK_BYTE2_SCAN_REQUEST_RECEIVED                                       (0x04U)
#define HCI_LE_EVT_MASK_BYTE2_CHANNEL_SELECTION_ALGORITHM                                 (0x08U)
#define HCI_LE_EVT_MASK_BYTE2_CONNECTIONLESS_IQ_REPORT                                    (0x10U)
#define HCI_LE_EVT_MASK_BYTE2_CONNECTION_IQ_REPORT                                        (0x20U)
#define HCI_LE_EVT_MASK_BYTE2_CTE_REQUEST_FAILED                                          (0x40U)
#define HCI_LE_EVT_MASK_BYTE2_PERIODIC_ADVERTISING_SYNC_TRANSFER                          (0x80U)
#define HCI_LE_EVT_MASK_BYTE3_PATH_LOSS_THRESHOLD                                         (0x80U)
#define HCI_LE_EVT_MASK_BYTE4_TRANSMIT_POWER_REPORTING                                    (0x01U)
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#endif /* _LINK_LAYER_H */
