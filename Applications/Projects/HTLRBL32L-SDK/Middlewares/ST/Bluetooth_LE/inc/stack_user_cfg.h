
/**
  ******************************************************************************
  * @file    stack_user_cfg.h
  * @author  AMS - RF Application team
  * @version V1.1.0
  * @date    08 April 2021
  * @brief   BLE stack modular configuration options header file
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
* \section BLE_Config BLE stack configuration options  

    - The BLE stack v3.1 supports the following outstanding features:
      -- Controller Privacy
      -- LE Secure Connections
      -- Controller Master
      -- Controller Data Length Extension
      -- LE 2M PHY
      -- LE Coded PHY
      -- Extended Advertising
      -- Periodic Advertising and Synchronizer
      -- L2CAP Connection Oriented Channels
      -- Constant Tone Extension
      -- LE Power Control & Path Loss Monitoring
    - In order to configure the BLE stack v3.1 or later the following predefined options are available:
        
        - BLE stack full configuration: all the outstanding features are included. 
          - To enable this configuration, the user is requested to add the following preprocessor option
            to project configuration: 
            
            BLE_STACK_FULL_CONF
        
        - BLE stack basic configuration: none of the outstanding features is included.
          - To enable this configuration, the user is requested to add the following preprocessor option
            to project configuration: 
            
            BLE_STACK_BASIC_CONF 
        
        - BLE stack configuration with Slave Only mode and Data Length Extension:
          - To enable this configuration, the user is requested to add the following preprocessor option
            to project configuration:
            
            BLE_STACK_SLAVE_DLE_CONF 
        
        - BLE stack configuration with Slave Only mode, Data Length Extension, LE 2M PHY, and LE Coded PHY.
          - To enable this configuration, the user is requested to add the following preprocessor option
            to project configuration:
            
            BLE_STACK_SLAVE_DLE_LE_2M_CODED_CONF
       
        - BLE custom stack configuration defined on header file custom_ble_stack_conf.h placed on application Inc folder. 
          - To enable this configuration, the user is requested to add the following preprocessor option
            to project configuration:
            
            BLE_STACK_CUSTOM_CONF    

       
**/

#ifndef _STACK_USER_CFG_H_
#define _STACK_USER_CFG_H_

#include <bluenrg_lp_api.h>
#include <system_util.h>
#include <stdint.h>

/* --------------------- BLE stack configuration options --------------------------------------------------- */


/** @defgroup BLE_Stack_Config BLE Stack Modular Configuration
 *  @li BLE_STACK_BASIC_CONF: only basic features are enabled (no Controller Privacy, no LE Secure Connections,
    no Master GAP role, no Data Length Extension)
 *  @li BLE_STACK_FULL_CONF: all features are enabled
 *  @li BLE_STACK_SLAVE_DLE_CONF : Slave + Data Length Extension enabled (if available)
 *  @li BLE_STACK_SLAVE_DLE_LE_2M_CODED_CONF : Slave + Data Length Extension enabled  + PHY 2M/Coded PHY (if available)
 *  @li BLE_STACK_CUSTOM_CONF: custom configuration options defined on header file custom_ble_stack_conf.h
 *
 *  Uncomment one of the lines or define the configuration in your toolchain compiler preprocessor.
 *  @note It is mandatory to define one (and only one) of the options.
 *  @{
 */

/* #define BLE_STACK_BASIC_CONF */
/* #define BLE_STACK_FULL_CONF */
/* #define BLE_STACK_SLAVE_DLE_CONF */
/* #define BLE_STACK_SLAVE_DLE_LE_2M_CODED_CONF */
/* #define BLE_STACK_CUSTOM_CONF */

/**
 * @}
 */

/* --------------------- BLE stack configuration options and associated module inclusion -------------------- */

#if !(defined(BLE_STACK_FULL_CONF)                  ||\
      defined(BLE_STACK_BASIC_CONF)                 ||\
      defined(BLE_STACK_SLAVE_DLE_CONF)             ||\
      defined(BLE_STACK_SLAVE_DLE_LE_2M_CODED_CONF) ||\
      defined(BLE_STACK_CUSTOM_CONF))
#  error "No BLE_STACK_*_CONF has been defined."
#endif


/**
 * @brief Full BLE stack configuration
 */
#if defined(BLE_STACK_FULL_CONF)
#  define CONTROLLER_PRIVACY_ENABLED                  (1U) /* Controller Privacy feature:                ENABLED  */
#  define CONTROLLER_MASTER_ENABLED                   (1U) /* Master role:                               ENABLED  */
#    define SECURE_CONNECTIONS_ENABLED                (1U) /* LE Secure Connections feature:             ENABLED  */
#    define CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED  (1U) /* Data Length Extension feature:             ENABLED  */
#    define CONTROLLER_2M_CODED_PHY_ENABLED           (1U) /* LE 2M + Coded PHYs:                        ENABLED  */
#    define CONTROLLER_EXT_ADV_SCAN_ENABLED           (1U) /* Extended Advertising and Scanning feature: ENABLED  */
#    define L2CAP_COS_ENABLED                         (1U) /* L2CAP COS feature:                         ENABLED  */
#    define CONTROLLER_PERIODIC_ADV_ENABLED           (1U) /* Periodic Advertising and Synchronizer:     ENABLED  */
#    define CONTROLLER_CTE_ENABLED                    (0U) /* Constant Tone Extension:                   DISABLED */
#    define CONTROLLER_POWER_CONTROL_ENABLED          (1U) /* Power Control & Path Loss Monitoring:      ENABLED  */

/**
 * @brief Basic BLE stack configuration
 */
#elif defined(BLE_STACK_BASIC_CONF)
#  define CONTROLLER_PRIVACY_ENABLED                  (0U) /* Controller Privacy feature:                DISABLED */
#  define SECURE_CONNECTIONS_ENABLED                  (0U) /* LE Secure Connections feature:             DISABLED */
#  define CONTROLLER_MASTER_ENABLED                   (0U) /* Master role:                               DISABLED */
#  define CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED    (0U) /* Data Length Extension feature:             DISABLED */
#  define CONTROLLER_2M_CODED_PHY_ENABLED             (0U) /* LE 2M + Coded PHYs:                        DISABLED */
#  define CONTROLLER_EXT_ADV_SCAN_ENABLED             (0U) /* Extended Advertising and Scanning feature: DISABLED */
#  define L2CAP_COS_ENABLED                           (0U) /* L2CAP COS feature:                         DISABLED */
#  define CONTROLLER_PERIODIC_ADV_ENABLED             (0U) /* Periodic Advertising and Synchronizer:     DISABLED */
#  define CONTROLLER_CTE_ENABLED                      (0U) /* Constant Tone Extension:                   DISABLED */
#  define CONTROLLER_POWER_CONTROL_ENABLED            (0U) /* Power Control & Path Loss Monitoring:      DISABLED */

/**
 * @brief BLE stack configuration: only Slave role with Data Length Extension feature enabled
 */
#elif defined(BLE_STACK_SLAVE_DLE_CONF)
#  define CONTROLLER_PRIVACY_ENABLED                  (0U) /* Controller Privacy feature:                DISABLED */
#  define SECURE_CONNECTIONS_ENABLED                  (0U) /* LE Secure Connections feature:             DISABLED */
#  define CONTROLLER_MASTER_ENABLED                   (0U) /* Master role:                               DISABLED */
#  define CONTROLLER_2M_CODED_PHY_ENABLED             (0U) /* LE 2M + Coded PHYs:                        DISABLED */
#  define CONTROLLER_EXT_ADV_SCAN_ENABLED             (0U) /* Extended Advertising and Scanning feature: DISABLED */
#  define L2CAP_COS_ENABLED                           (0U) /* L2CAP COS feature:                         DISABLED */
#  define CONTROLLER_PERIODIC_ADV_ENABLED             (0U) /* Periodic Advertising and Synchronizer:     DISABLED */
#  define CONTROLLER_CTE_ENABLED                      (0U) /* Constant Tone Extension:                   DISABLED */
#  define CONTROLLER_POWER_CONTROL_ENABLED            (0U) /* Power Control & Path Loss Monitoring:      DISABLED */
#    define CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED  (1U) /* Data Length Extension feature:             ENABLED  */

/**
 * @brief BLE stack configuration: only Slave role with Data Length Extension feature and LE 2M + Coded PHYs
 */
#elif defined(BLE_STACK_SLAVE_DLE_LE_2M_CODED_CONF)
#  define CONTROLLER_PRIVACY_ENABLED                  (0U) /* Controller Privacy feature:                DISABLED */
#  define SECURE_CONNECTIONS_ENABLED                  (0U) /* LE Secure Connections feature:             DISABLED */
#  define CONTROLLER_MASTER_ENABLED                   (0U) /* Master role:                               DISABLED */
#  define CONTROLLER_EXT_ADV_SCAN_ENABLED             (0U) /* Extended Advertising and Scanning feature: DISABLED */
#  define L2CAP_COS_ENABLED                           (0U) /* L2CAP COS feature:                         DISABLED */
#  define CONTROLLER_PERIODIC_ADV_ENABLED             (0U) /* Periodic Advertising and Synchronizer:     DISABLED */
#  define CONTROLLER_CTE_ENABLED                      (0U) /* Constant Tone Extension:                   DISABLED */
#  define CONTROLLER_POWER_CONTROL_ENABLED            (0U) /* Power Control & Path Loss Monitoring:      DISABLED */
#    define CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED  (1U) /* Data Length Extension feature:             ENABLED  */
#    define CONTROLLER_2M_CODED_PHY_ENABLED           (1U) /* LE 2M + Coded PHYs:                        ENABLED  */
#elif defined(BLE_STACK_CUSTOM_CONF)
#  include "custom_ble_stack_conf.h"
#endif

tBleStatus GAP_set_advertising_configuration_ucfg(uint8_t Advertising_Handle,
                                                  uint8_t Discoverability_Mode,
                                                  uint16_t Advertising_Event_Properties,
                                                  uint32_t Primary_Advertising_Interval_Min,
                                                  uint32_t Primary_Advertising_Interval_Max,
                                                  uint8_t Primary_Advertising_Channel_Map,
                                                  uint8_t Peer_Address_Type,
                                                  uint8_t Peer_Address[6],
                                                  uint8_t Advertising_Filter_Policy,
                                                  int8_t Advertising_Tx_Power,
                                                  uint8_t Primary_Advertising_PHY,
                                                  uint8_t Secondary_Advertising_Max_Skip,
                                                  uint8_t Secondary_Advertising_PHY,
                                                  uint8_t Advertising_SID,
                                                  uint8_t Scan_Request_Notification_Enable);
tBleStatus GAP_set_advertising_configuration_ucfg_weak(uint8_t Advertising_Handle,
                                                       uint8_t Discoverability_Mode,
                                                       uint16_t Advertising_Event_Properties,
                                                       uint32_t Primary_Advertising_Interval_Min,
                                                       uint32_t Primary_Advertising_Interval_Max,
                                                       uint8_t Primary_Advertising_Channel_Map,
                                                       uint8_t Peer_Address_Type,
                                                       uint8_t Peer_Address[6],
                                                       uint8_t Advertising_Filter_Policy,
                                                       int8_t Advertising_Tx_Power,
                                                       uint8_t Primary_Advertising_PHY,
                                                       uint8_t Secondary_Advertising_Max_Skip,
                                                       uint8_t Secondary_Advertising_PHY,
                                                       uint8_t Advertising_SID,
                                                       uint8_t Scan_Request_Notification_Enable);
tBleStatus GAP_set_extended_advertising_configuration(uint8_t Advertising_Handle,
                                                      uint8_t Discoverability_Mode,
                                                      uint16_t Advertising_Event_Properties,
                                                      uint32_t Primary_Advertising_Interval_Min,
                                                      uint32_t Primary_Advertising_Interval_Max,
                                                      uint8_t Primary_Advertising_Channel_Map,
                                                      uint8_t Peer_Address_Type,
                                                      uint8_t Peer_Address[6],
                                                      uint8_t Advertising_Filter_Policy,
                                                      int8_t Advertising_Tx_Power,
                                                      uint8_t Primary_Advertising_PHY,
                                                      uint8_t Secondary_Advertising_Max_Skip,
                                                      uint8_t Secondary_Advertising_PHY,
                                                      uint8_t Advertising_SID,
                                                      uint8_t Scan_Request_Notification_Enable);

tBleStatus GAP_set_scan_response_data_ucfg(uint8_t Advertising_Handle,
                                           uint16_t Scan_Response_Data_Length,
                                           uint8_t* Scan_Response_Data);
tBleStatus GAP_set_scan_response_data_ucfg_weak(uint8_t Advertising_Handle,
                                                uint16_t Scan_Response_Data_Length,
                                                uint8_t* Scan_Response_Data);
tBleStatus GAP_set_extended_scan_response_data(uint8_t Advertising_Handle,
                                               uint16_t Scan_Response_Data_Length,
                                               uint8_t* Scan_Response_Data);

tBleStatus GAP_set_advertising_data_ucfg(uint8_t Advertising_Handle,
                                         uint8_t Operation,
                                         uint16_t Advertising_Data_Length,
                                         uint8_t* Advertising_Data);
tBleStatus GAP_set_advertising_data_ucfg_weak(uint8_t Advertising_Handle,
                                              uint8_t Operation,
                                              uint16_t Advertising_Data_Length,
                                              uint8_t* Advertising_Data);
tBleStatus GAP_set_extended_advertising_data(uint8_t Advertising_Handle,
                                             uint8_t Operation,
                                             uint16_t Advertising_Data_Length,
                                             uint8_t* Advertising_Data);

tBleStatus GAP_set_advertising_enable_ucfg(uint8_t Enable,
                                           uint8_t Num_Of_Sets,
                                           Advertising_Set_Parameters_t* Advertising_Set_Parameters);
tBleStatus GAP_set_advertising_enable_ucfg_weak(uint8_t Enable,
                                                uint8_t Num_Of_Sets,
                                                Advertising_Set_Parameters_t* Advertising_Set_Parameters);
tBleStatus GAP_set_extended_advertising_enable(uint8_t Enable,
                                               uint8_t Num_Of_Sets,
                                               Advertising_Set_Parameters_t* Advertising_Set_Parameters);

void GAP_hci_le_advertising_set_terminated_evt_hndl_ucfg(uint8_t status,
                                                         uint8_t Advertising_Handle);
void GAP_hci_le_advertising_set_terminated_evt_hndl_ucfg_weak(uint8_t status,
                                                              uint8_t Advertising_Handle);
void GAP_hci_le_advertising_set_terminated_evt_hndl(uint8_t status,
                                                    uint8_t Advertising_Handle);

void GAP_slave_connection_complete_handler_ucfg(uint16_t connectionHandle);
void GAP_slave_connection_complete_handler_ucfg_weak(uint16_t connectionHandle);
void GAP_slave_connection_complete_handler(uint16_t connectionHandle);

tBleStatus GAP_enable_controller_privacy_ucfg(uint8_t* gapRole,
                                              uint8_t* numServiceRec);
tBleStatus GAP_enable_controller_privacy_ucfg_weak(uint8_t* gapRole,
                                                   uint8_t* numServiceRec);
tBleStatus GAP_enable_controller_privacy(uint8_t* gapRole,
                                         uint8_t* numServiceRec);

tBleStatus GAP_check_and_set_role_ucfg(uint8_t* gapRole,
                                       uint8_t role);
tBleStatus GAP_check_and_set_role_ucfg_weak(uint8_t* gapRole,
                                            uint8_t role);
tBleStatus GAP_check_and_set_role(uint8_t* gapRole,
                                  uint8_t role);

tBleStatus GAP_add_device_to_white_and_resolving_list_ucfg(uint8_t lists,
                                                           uint8_t addr_type,
                                                           uint8_t addr[6]);
tBleStatus GAP_add_device_to_white_and_resolving_list_ucfg_weak(uint8_t lists,
                                                                uint8_t addr_type,
                                                                uint8_t addr[6]);
tBleStatus GAP_add_device_to_white_and_resolving_list_full(uint8_t lists,
                                                           uint8_t addr_type,
                                                           uint8_t addr[6]);

tBleStatus GAP_clear_white_and_resolving_list_ucfg(uint8_t lists);
tBleStatus GAP_clear_white_and_resolving_list_ucfg_weak(uint8_t lists);
tBleStatus GAP_clear_white_and_resolving_list_full(uint8_t lists);

tBleStatus GAP_set_controller_random_address_ucfg(uint8_t random_address[6]);
tBleStatus GAP_set_controller_random_address_ucfg_weak(uint8_t random_address[6]);
tBleStatus GAP_set_controller_random_address_extended(uint8_t random_address[6]);

tBleStatus GAP_create_connection_ucfg(uint8_t* peer_address,
                                      uint8_t peer_address_type,
                                      uint8_t own_address_type,
                                      uint8_t initiator_filter_policy,
                                      uint8_t phys);
tBleStatus GAP_create_connection_ucfg_weak(uint8_t* peer_address,
                                           uint8_t peer_address_type,
                                           uint8_t own_address_type,
                                           uint8_t initiator_filter_policy,
                                           uint8_t phys);
tBleStatus GAP_create_connection_ext(uint8_t* peer_address,
                                     uint8_t peer_address_type,
                                     uint8_t own_address_type,
                                     uint8_t initiator_filter_policy,
                                     uint8_t phys);

tBleStatus GAP_set_scan_parameters_ucfg(uint8_t own_address_type,
                                        uint8_t phys);
tBleStatus GAP_set_scan_parameters_ucfg_weak(uint8_t own_address_type,
                                             uint8_t phys);
tBleStatus GAP_set_scan_parameters_ext(uint8_t own_address_type,
                                       uint8_t phys);

tBleStatus GAP_enable_disable_scan_ucfg(BOOL enable,
                                        uint8_t duplicate_filtering);
tBleStatus GAP_enable_disable_scan_ucfg_weak(BOOL enable,
                                             uint8_t duplicate_filtering);
tBleStatus GAP_enable_disable_scan_legacy(BOOL enable,
                                          uint8_t duplicate_filtering);
tBleStatus GAP_enable_disable_scan_ext(BOOL enable,
                                       uint8_t duplicate_filtering);

tBleStatus GAP_discover_peer_name_ucfg(void);
tBleStatus GAP_discover_peer_name_ucfg_weak(void);
tBleStatus GAP_discover_peer_name(void);

void GAP_master_connection_complete_handler_ucfg(uint8_t status,
                                                 uint16_t connectionHandle);
void GAP_master_connection_complete_handler_ucfg_weak(uint8_t status,
                                                      uint16_t connectionHandle);
void GAP_master_connection_complete_handler(uint8_t status,
                                            uint16_t connectionHandle);

BOOL GAP_parse_connectable_advertising_report_ucfg(uint8_t* adv_buf,
                                                   BOOL extended);
BOOL GAP_parse_connectable_advertising_report_ucfg_weak(uint8_t* adv_buf,
                                                        BOOL extended);
BOOL GAP_parse_connectable_advertising_report(uint8_t* adv_buf,
                                              BOOL extended);

BOOL GAP_parse_advertising_report_ucfg(uint8_t* adv_buf,
                                       BOOL extended);
BOOL GAP_parse_advertising_report_ucfg_weak(uint8_t* adv_buf,
                                            BOOL extended);
BOOL GAP_parse_advertising_report(uint8_t* adv_buf,
                                  BOOL extended);

void GAP_DiscProcTimeoutcb_ucfg(uint8_t timer_id);
void GAP_DiscProcTimeoutcb_ucfg_weak(uint8_t timer_id);
void GAP_DiscProcTimeoutcb(uint8_t timer_id);

tBleStatus GAP_suspend_resume_active_advertising_sets_ucfg(BOOL resume);
tBleStatus GAP_suspend_resume_active_advertising_sets_ucfg_weak(BOOL resume);
tBleStatus GAP_suspend_resume_active_advertising_sets_extended(BOOL resume);

uint32_t cte_csr_ucfg(void);
uint32_t cte_csr_ucfg_weak(void);
uint32_t cte_csr(void);

uint8_t hci_le_check_own_address_type_max_value_ucfg(void);
uint8_t hci_le_check_own_address_type_max_value_ucfg_weak(void);
uint8_t hci_le_check_own_address_type_max_value(void);

uint32_t data_length_extension_csr_ucfg(void);
uint32_t data_length_extension_csr_ucfg_weak(void);
uint32_t data_length_extension_csr(void);

uint32_t pcl_csr_ucfg(void);
uint32_t pcl_csr_ucfg_weak(void);
uint32_t pcl_csr(void);

uint32_t phy_upd_csr_ucfg(void);
uint32_t phy_upd_csr_ucfg_weak(void);
uint32_t phy_upd_csr(void);

uint32_t PRIV_controller_privacy_csr_ucfg(void);
uint32_t PRIV_controller_privacy_csr_ucfg_weak(void);
uint32_t PRIV_controller_privacy_csr(void);

uint32_t master_csr_ucfg(void);
uint32_t master_csr_ucfg_weak(void);
uint32_t master_csr(void);

tBleStatus LLC_test_check_cte_params_ucfg(void* params);
tBleStatus LLC_test_check_cte_params_ucfg_weak(void* params);
tBleStatus LLC_test_check_cte_params(void* params);

void hci_le_advertising_report_event_cb_ucfg(uint8_t header_type,
                                             uint8_t* buff_p);
void hci_le_advertising_report_event_cb_ucfg_weak(uint8_t header_type,
                                                  uint8_t* buff_p);
void hci_le_advertising_report_event_cb(uint8_t header_type,
                                        uint8_t* buff_p);

void hci_le_read_local_p256_public_key_complete_event_cb_ucfg(uint8_t header_type,
                                                              uint8_t* buff_p);
void hci_le_read_local_p256_public_key_complete_event_cb_ucfg_weak(uint8_t header_type,
                                                                   uint8_t* buff_p);
void hci_le_read_local_p256_public_key_complete_event_cb(uint8_t header_type,
                                                         uint8_t* buff_p);

void hci_le_generate_dhkey_complete_event_cb_ucfg(uint8_t header_type,
                                                  uint8_t* buff_p);
void hci_le_generate_dhkey_complete_event_cb_ucfg_weak(uint8_t header_type,
                                                       uint8_t* buff_p);
void hci_le_generate_dhkey_complete_event_cb(uint8_t header_type,
                                             uint8_t* buff_p);

void hci_le_direct_advertising_report_event_cb_ucfg(uint8_t header_type,
                                                    uint8_t* buff_p);
void hci_le_direct_advertising_report_event_cb_ucfg_weak(uint8_t header_type,
                                                         uint8_t* buff_p);
void hci_le_direct_advertising_report_event_cb(uint8_t header_type,
                                               uint8_t* buff_p);

void hci_le_extended_advertising_report_event_cb_ucfg(uint8_t header_type,
                                                      uint8_t* buff_p);
void hci_le_extended_advertising_report_event_cb_ucfg_weak(uint8_t header_type,
                                                           uint8_t* buff_p);
void hci_le_extended_advertising_report_event_cb(uint8_t header_type,
                                                 uint8_t* buff_p);

void hci_le_scan_timeout_event_cb_ucfg(uint8_t header_type,
                                       uint8_t* buff_p);
void hci_le_scan_timeout_event_cb_ucfg_weak(uint8_t header_type,
                                            uint8_t* buff_p);
void hci_le_scan_timeout_event_cb(uint8_t header_type,
                                  uint8_t* buff_p);

void hci_le_advertising_set_terminated_event_cb_ucfg(uint8_t header_type,
                                                     uint8_t* buff_p);
void hci_le_advertising_set_terminated_event_cb_ucfg_weak(uint8_t header_type,
                                                          uint8_t* buff_p);
void hci_le_advertising_set_terminated_event_cb(uint8_t header_type,
                                                uint8_t* buff_p);

void hci_le_data_length_change_event_cb_ucfg(uint8_t header_type,
                                             uint8_t* buff_p);
void hci_le_data_length_change_event_cb_ucfg_weak(uint8_t header_type,
                                                  uint8_t* buff_p);
void hci_le_data_length_change_event_cb(uint8_t header_type,
                                        uint8_t* buff_p);

void hci_le_phy_update_complete_event_cb_ucfg(uint8_t header_type,
                                              uint8_t* buff_p);
void hci_le_phy_update_complete_event_cb_ucfg_weak(uint8_t header_type,
                                                   uint8_t* buff_p);
void hci_le_phy_update_complete_event_cb(uint8_t header_type,
                                         uint8_t* buff_p);

void hci_le_periodic_advertising_sync_established_event_cb_ucfg(uint8_t header_type,
                                                                uint8_t* buff_p);
void hci_le_periodic_advertising_sync_established_event_cb_ucfg_weak(uint8_t header_type,
                                                                     uint8_t* buff_p);
void hci_le_periodic_advertising_sync_established_event_cb(uint8_t header_type,
                                                           uint8_t* buff_p);

void hci_le_periodic_advertising_report_event_cb_ucfg(uint8_t header_type,
                                                      uint8_t* buff_p);
void hci_le_periodic_advertising_report_event_cb_ucfg_weak(uint8_t header_type,
                                                           uint8_t* buff_p);
void hci_le_periodic_advertising_report_event_cb(uint8_t header_type,
                                                 uint8_t* buff_p);

void hci_le_periodic_advertising_sync_lost_event_cb_ucfg(uint8_t header_type,
                                                         uint8_t* buff_p);
void hci_le_periodic_advertising_sync_lost_event_cb_ucfg_weak(uint8_t header_type,
                                                              uint8_t* buff_p);
void hci_le_periodic_advertising_sync_lost_event_cb(uint8_t header_type,
                                                    uint8_t* buff_p);

void hci_le_scan_request_received_event_cb_ucfg(uint8_t header_type,
                                                uint8_t* buff_p);
void hci_le_scan_request_received_event_cb_ucfg_weak(uint8_t header_type,
                                                     uint8_t* buff_p);
void hci_le_scan_request_received_event_cb(uint8_t header_type,
                                           uint8_t* buff_p);

void hci_le_connectionless_iq_report_event_cb_ucfg(uint8_t header_type,
                                                   uint8_t* buff_p);
void hci_le_connectionless_iq_report_event_cb_ucfg_weak(uint8_t header_type,
                                                        uint8_t* buff_p);
void hci_le_connectionless_iq_report_event_cb(uint8_t header_type,
                                              uint8_t* buff_p);

void hci_le_connection_iq_report_event_cb_ucfg(uint8_t header_type,
                                               uint8_t* buff_p);
void hci_le_connection_iq_report_event_cb_ucfg_weak(uint8_t header_type,
                                                    uint8_t* buff_p);
void hci_le_connection_iq_report_event_cb(uint8_t header_type,
                                          uint8_t* buff_p);

void hci_le_cte_request_failed_event_cb_ucfg(uint8_t header_type,
                                             uint8_t* buff_p);
void hci_le_cte_request_failed_event_cb_ucfg_weak(uint8_t header_type,
                                                  uint8_t* buff_p);
void hci_le_cte_request_failed_event_cb(uint8_t header_type,
                                        uint8_t* buff_p);

void hci_le_periodic_advertising_sync_transfer_received_event_cb_ucfg(uint8_t header_type,
                                                                      uint8_t* buff_p);
void hci_le_periodic_advertising_sync_transfer_received_event_cb_ucfg_weak(uint8_t header_type,
                                                                           uint8_t* buff_p);
void hci_le_periodic_advertising_sync_transfer_received_event_cb(uint8_t header_type,
                                                                 uint8_t* buff_p);

void hci_le_path_loss_threshold_event_cb_ucfg(uint8_t header_type,
                                              uint8_t* buff_p);
void hci_le_path_loss_threshold_event_cb_ucfg_weak(uint8_t header_type,
                                                   uint8_t* buff_p);
void hci_le_path_loss_threshold_event_cb(uint8_t header_type,
                                         uint8_t* buff_p);

void hci_le_transmit_power_reporting_event_cb_ucfg(uint8_t header_type,
                                                   uint8_t* buff_p);
void hci_le_transmit_power_reporting_event_cb_ucfg_weak(uint8_t header_type,
                                                        uint8_t* buff_p);
void hci_le_transmit_power_reporting_event_cb(uint8_t header_type,
                                              uint8_t* buff_p);

void aci_l2cap_cfc_connection_event_cb_ucfg(uint8_t header_type,
                                            uint8_t* buff_p);
void aci_l2cap_cfc_connection_event_cb_ucfg_weak(uint8_t header_type,
                                                 uint8_t* buff_p);
void aci_l2cap_cfc_connection_event_cb(uint8_t header_type,
                                       uint8_t* buff_p);

void aci_l2cap_disconnection_complete_event_cb_ucfg(uint8_t header_type,
                                                    uint8_t* buff_p);
void aci_l2cap_disconnection_complete_event_cb_ucfg_weak(uint8_t header_type,
                                                         uint8_t* buff_p);
void aci_l2cap_disconnection_complete_event_cb(uint8_t header_type,
                                               uint8_t* buff_p);

void aci_l2cap_flow_control_credit_event_cb_ucfg(uint8_t header_type,
                                                 uint8_t* buff_p);
void aci_l2cap_flow_control_credit_event_cb_ucfg_weak(uint8_t header_type,
                                                      uint8_t* buff_p);
void aci_l2cap_flow_control_credit_event_cb(uint8_t header_type,
                                            uint8_t* buff_p);

void aci_l2cap_sdu_data_tx_event_cb_ucfg(uint8_t header_type,
                                         uint8_t* buff_p);
void aci_l2cap_sdu_data_tx_event_cb_ucfg_weak(uint8_t header_type,
                                              uint8_t* buff_p);
void aci_l2cap_sdu_data_tx_event_cb(uint8_t header_type,
                                    uint8_t* buff_p);

void aci_l2cap_sdu_data_rx_event_cb_ucfg(uint8_t header_type,
                                         uint8_t* buff_p);
void aci_l2cap_sdu_data_rx_event_cb_ucfg_weak(uint8_t header_type,
                                              uint8_t* buff_p);
void aci_l2cap_sdu_data_rx_event_cb(uint8_t header_type,
                                    uint8_t* buff_p);

tBleStatus L2C_cos_process_cfc_mode_command_ucfg(void* params);
tBleStatus L2C_cos_process_cfc_mode_command_ucfg_weak(void* params);
tBleStatus L2C_cos_process_cfc_mode_command(void* params);

BOOL L2C_cos_is_pdu_cframe_cfc_command_opcode_ucfg(uint8_t opCode);
BOOL L2C_cos_is_pdu_cframe_cfc_command_opcode_ucfg_weak(uint8_t opCode);
BOOL L2C_cos_is_pdu_cframe_cfc_command_opcode(uint8_t opCode);

uint32_t l2c_cos_csr_ucfg(void);
uint32_t l2c_cos_csr_ucfg_weak(void);
uint32_t l2c_cos_csr(void);

tBleStatus L2C_cos_cfc_init_ucfg(void);
tBleStatus L2C_cos_cfc_init_ucfg_weak(void);
tBleStatus L2C_cos_cfc_init(void);

void L2C_cos_process_pending_actions_tsk_ucfg(uint16_t task_idx);
void L2C_cos_process_pending_actions_tsk_ucfg_weak(uint16_t task_idx);
void L2C_cos_process_pending_actions_tsk(uint16_t task_idx);

void L2C_cos_reset_any_pending_channel_ucfg(uint16_t connection_handle);
void L2C_cos_reset_any_pending_channel_ucfg_weak(uint16_t connection_handle);
void L2C_cos_reset_any_pending_channel(uint16_t connection_handle);

void L2C_cos_physical_link_disconnection_hndl_ucfg(uint16_t connection_handle);
void L2C_cos_physical_link_disconnection_hndl_ucfg_weak(uint16_t connection_handle);
void L2C_cos_physical_link_disconnection_hndl(uint16_t connection_handle);

void L2C_cos_perform_sdu_segmentation_tsk_ucfg(uint16_t task_idx);
void L2C_cos_perform_sdu_segmentation_tsk_ucfg_weak(uint16_t task_idx);
void L2C_cos_perform_sdu_segmentation_tsk(uint16_t task_idx);

void L2C_cos_transmit_pdu_packets_tsk_ucfg(uint16_t task_idx);
void L2C_cos_transmit_pdu_packets_tsk_ucfg_weak(uint16_t task_idx);
void L2C_cos_transmit_pdu_packets_tsk(uint16_t task_idx);

void L2C_cos_perform_pdu_reassembly_tsk_ucfg(uint16_t task_idx);
void L2C_cos_perform_pdu_reassembly_tsk_ucfg_weak(uint16_t task_idx);
void L2C_cos_perform_pdu_reassembly_tsk(uint16_t task_idx);

tBleStatus L2C_cos_le_frame_data_hndl_ucfg(void* params);
tBleStatus L2C_cos_le_frame_data_hndl_ucfg_weak(void* params);
tBleStatus L2C_cos_le_frame_data_hndl(void* params);

void aci_hal_scan_req_report_event_cb_ucfg(uint8_t header_type,
                                           uint8_t* buff_p);
void aci_hal_scan_req_report_event_cb_ucfg_weak(uint8_t header_type,
                                                uint8_t* buff_p);
void aci_hal_scan_req_report_event_cb(uint8_t header_type,
                                      uint8_t* buff_p);

tBleStatus LL_Read_RSSI_ucfg(int8_t* rssiVal,
                             uint16_t connHandle);
tBleStatus LL_Read_RSSI_ucfg_weak(int8_t* rssiVal,
                                  uint16_t connHandle);
tBleStatus LL_Read_RSSI(int8_t* rssiVal,
                        uint16_t connHandle);

BOOL LL_phy_upd_pending_ucfg(uint8_t conn_idx);
BOOL LL_phy_upd_pending_ucfg_weak(uint8_t conn_idx);
BOOL LL_phy_upd_pending(uint8_t conn_idx);

void LLC_conn_process_rx_cte_ucfg(void* params,
                                  uint8_t cte_type);
void LLC_conn_process_rx_cte_ucfg_weak(void* params,
                                       uint8_t cte_type);
void LLC_conn_process_rx_cte(void* params,
                             uint8_t cte_type);

void LL_cpe_init_length_update_ucfg(void);
void LL_cpe_init_length_update_ucfg_weak(void);
void LL_cpe_init_length_update(void);

void LL_cpe_init_phy_update_ucfg(void);
void LL_cpe_init_phy_update_ucfg_weak(void);
void LL_cpe_init_phy_update(void);

void LL_cpe_init_cte_ucfg(void);
void LL_cpe_init_cte_ucfg_weak(void);
void LL_cpe_init_cte(void);

void LL_cpe_init_past_ucfg(void);
void LL_cpe_init_past_ucfg_weak(void);
void LL_cpe_init_past(void);

void LL_cpe_init_pcl_ucfg(void);
void LL_cpe_init_pcl_ucfg_weak(void);
void LL_cpe_init_pcl(void);

void LL_conn_upd_max_tx_time_coded_ucfg(void* params);
void LL_conn_upd_max_tx_time_coded_ucfg_weak(void* params);
void LL_conn_upd_max_tx_time_coded(void* params);

void LL_conn_upd_data_length_change_event_ucfg(void* params);
void LL_conn_upd_data_length_change_event_ucfg_weak(void* params);
void LL_conn_upd_data_length_change_event(void* params);

void LLC_conn_init_cte_ctxt_ucfg(uint8_t conn_idx);
void LLC_conn_init_cte_ctxt_ucfg_weak(uint8_t conn_idx);
void LLC_conn_init_cte_ctxt(uint8_t conn_idx);

BOOL LLC_cte_request_procedure_ucfg(void* params);
BOOL LLC_cte_request_procedure_ucfg_weak(void* params);
BOOL LLC_cte_request_procedure(void* params);

void LLC_connection_cte_response_pause_resume_ucfg(uint8_t conn_idx,
                                                   uint8_t tx_phy);
void LLC_connection_cte_response_pause_resume_ucfg_weak(uint8_t conn_idx,
                                                        uint8_t tx_phy);
void LLC_connection_cte_response_pause_resume(uint8_t conn_idx,
                                              uint8_t tx_phy);

void LLC_connection_cte_response_disable_ucfg(uint8_t conn_idx,
                                              uint8_t taskslot_no);
void LLC_connection_cte_response_disable_ucfg_weak(uint8_t conn_idx,
                                                   uint8_t taskslot_no);
void LLC_connection_cte_response_disable(uint8_t conn_idx,
                                         uint8_t taskslot_no);

void LL_past_reload_txctrl_packet_ucfg(uint8_t conn_idx,
                                       uint8_t* pdu_ptr);
void LL_past_reload_txctrl_packet_ucfg_weak(uint8_t conn_idx,
                                            uint8_t* pdu_ptr);
void LL_past_reload_txctrl_packet(uint8_t conn_idx,
                                  uint8_t* pdu_ptr);

void LL_past_initialize_connect_context_ucfg(uint8_t conn_idx);
void LL_past_initialize_connect_context_ucfg_weak(uint8_t conn_idx);
void LL_past_initialize_connect_context(uint8_t conn_idx);

void LL_past_default_params_ucfg(uint8_t conn_idx);
void LL_past_default_params_ucfg_weak(uint8_t conn_idx);
void LL_past_default_params(uint8_t conn_idx);

void LLC_conn_init_pcl_ctxt_ucfg(uint8_t conn_idx);
void LLC_conn_init_pcl_ctxt_ucfg_weak(uint8_t conn_idx);
void LLC_conn_init_pcl_ctxt(uint8_t conn_idx);

void LLC_pcl_hal_cntxt_init_ucfg(uintptr_t pcl_cntxt_p);
void LLC_pcl_hal_cntxt_init_ucfg_weak(uintptr_t pcl_cntxt_p);
void LLC_pcl_hal_cntxt_init(uintptr_t pcl_cntxt_p);

void LLC_pcl_incr_rx_packets_ucfg(uint8_t conn_idx);
void LLC_pcl_incr_rx_packets_ucfg_weak(uint8_t conn_idx);
void LLC_pcl_incr_rx_packets(uint8_t conn_idx);

void LLC_pcl_update_avg_rssi_ucfg(void* params);
void LLC_pcl_update_avg_rssi_ucfg_weak(void* params);
void LLC_pcl_update_avg_rssi(void* params);

void LLC_pcl_set_radio_tx_power_conn_start_ucfg(uint8_t conn_idx);
void LLC_pcl_set_radio_tx_power_conn_start_ucfg_weak(uint8_t conn_idx);
void LLC_pcl_set_radio_tx_power_conn_start(uint8_t conn_idx);

void LLC_pcl_set_radio_tx_power_and_eval_indication_ucfg(uint8_t conn_idx,
                                                         BOOL send_ind,
                                                         int8_t ind_delta,
                                                         BOOL change_txpower);
void LLC_pcl_set_radio_tx_power_and_eval_indication_ucfg_weak(uint8_t conn_idx,
                                                              BOOL send_ind,
                                                              int8_t ind_delta,
                                                              BOOL change_txpower);
void LLC_pcl_set_radio_tx_power_and_eval_indication(uint8_t conn_idx,
                                                    BOOL send_ind,
                                                    int8_t ind_delta,
                                                    BOOL change_txpower);

BOOL LLC_pcl_offline_processing_ucfg(uint8_t conn_idx);
BOOL LLC_pcl_offline_processing_ucfg_weak(uint8_t conn_idx);
BOOL LLC_pcl_offline_processing(uint8_t conn_idx);

uint8_t LLC_pcl_get_number_of_phys_ucfg(void);
uint8_t LLC_pcl_get_number_of_phys_ucfg_weak(void);
uint8_t LLC_pcl_get_number_of_phys(void);

void LL_phy_upd_compute_data_PDU_length_params_ucfg(void* params);
void LL_phy_upd_compute_data_PDU_length_params_ucfg_weak(void* params);
void LL_phy_upd_compute_data_PDU_length_params(void* params);

tBleStatus LL_phy_update_init_ucfg(void);
tBleStatus LL_phy_update_init_ucfg_weak(void);
tBleStatus LL_phy_update_init(void);

tBleStatus LL_phy_update_init_per_st_data_ucfg(uint8_t conn_idx);
tBleStatus LL_phy_update_init_per_st_data_ucfg_weak(uint8_t conn_idx);
tBleStatus LL_phy_update_init_per_st_data(uint8_t conn_idx);

void LLC_blueapi_cte_ucfg(void* params);
void LLC_blueapi_cte_ucfg_weak(void* params);
void LLC_blueapi_cte(void* params);

void LLC_connless_process_rx_cte_ucfg(BOOL iq_samples_ready,
                                      void* params,
                                      uint8_t iq_samples_number,
                                      uint8_t rx_cte_type,
                                      uint8_t channel);
void LLC_connless_process_rx_cte_ucfg_weak(BOOL iq_samples_ready,
                                           void* params,
                                           uint8_t iq_samples_number,
                                           uint8_t rx_cte_type,
                                           uint8_t channel);
void LLC_connless_process_rx_cte(BOOL iq_samples_ready,
                                 void* params,
                                 uint8_t iq_samples_number,
                                 uint8_t rx_cte_type,
                                 uint8_t channel);

BOOL LLC_check_iq_samples_ready_ucfg(uint8_t* iq_samples_number,
                                     uint8_t* channel,
                                     uint8_t taskslot_no);
BOOL LLC_check_iq_samples_ready_ucfg_weak(uint8_t* iq_samples_number,
                                          uint8_t* channel,
                                          uint8_t taskslot_no);
BOOL LLC_check_iq_samples_ready(uint8_t* iq_samples_number,
                                uint8_t* channel,
                                uint8_t taskslot_no);

void LLC_test_process_rx_cte_ucfg(void* params);
void LLC_test_process_rx_cte_ucfg_weak(void* params);
void LLC_test_process_rx_cte(void* params);

void LLC_test_set_cte_ucfg(void* params);
void LLC_test_set_cte_ucfg_weak(void* params);
void LLC_test_set_cte(void* params);

tBleStatus LL_eadv_max_supported_data_check_ucfg(uint16_t Data_Length,
                                                 void* linkpointer);
tBleStatus LL_eadv_max_supported_data_check_ucfg_weak(uint16_t Data_Length,
                                                      void* linkpointer);
tBleStatus LL_eadv_max_supported_data_check(uint16_t Data_Length,
                                            void* linkpointer);

void LL_eadv_start_extended_ucfg(void* pointer);
void LL_eadv_start_extended_ucfg_weak(void* pointer);
void LL_eadv_start_extended(void* pointer);

uint8_t ext_adv_scan_enabled_ucfg(void);
uint8_t ext_adv_scan_enabled_ucfg_weak(void);
uint8_t ext_adv_scan_enabled(void);

tBleStatus LL_Clear_Advertising_Sets_ucfg(void);
tBleStatus LL_Clear_Advertising_Sets_ucfg_weak(void);
tBleStatus LL_Clear_Advertising_Sets(void);

tBleStatus LL_Remove_Advertising_Set_ucfg(uint16_t Advertising_Handle);
tBleStatus LL_Remove_Advertising_Set_ucfg_weak(uint16_t Advertising_Handle);
tBleStatus LL_Remove_Advertising_Set(uint16_t Advertising_Handle);

BOOL LL_extended_adv_add_enable_sync_info_auxind_pdu_ucfg(void* pointer);
BOOL LL_extended_adv_add_enable_sync_info_auxind_pdu_ucfg_weak(void* pointer);
BOOL LL_extended_adv_add_enable_sync_info_auxind_pdu(void* pointer);

void LL_escan_ScanStopCancel_ucfg(void);
void LL_escan_ScanStopCancel_ucfg_weak(void);
void LL_escan_ScanStopCancel(void);

tBleStatus LL_Set_Extended_Scan_Enable_ucfg(void* pExtScanEnable_dummy);
tBleStatus LL_Set_Extended_Scan_Enable_ucfg_weak(void* pExtScanEnable_dummy);
tBleStatus LL_Set_Extended_Scan_Enable(void* pExtScanEnable_dummy);

void LL_escan_ScanStart_ucfg(void);
void LL_escan_ScanStart_ucfg_weak(void);
void LL_escan_ScanStart(void);

void LL_escan_push_hci_le_extended_advertising_report_event_ucfg(void* pointer,
                                                                 uint8_t len,
                                                                 uint8_t offset,
                                                                 uint8_t event_type);
void LL_escan_push_hci_le_extended_advertising_report_event_ucfg_weak(void* pointer,
                                                                      uint8_t len,
                                                                      uint8_t offset,
                                                                      uint8_t event_type);
void LL_escan_push_hci_le_extended_advertising_report_event(void* pointer,
                                                            uint8_t len,
                                                            uint8_t offset,
                                                            uint8_t event_type);

void LL_escan_extended_adv_receive_process_ucfg(void* linkpointer,
                                                uint8_t phyindex,
                                                BOOL anonymous_flag,
                                                BOOL receive_address_present_flag,
                                                uint32_t* received_receive_address);
void LL_escan_extended_adv_receive_process_ucfg_weak(void* linkpointer,
                                                     uint8_t phyindex,
                                                     BOOL anonymous_flag,
                                                     BOOL receive_address_present_flag,
                                                     uint32_t* received_receive_address);
void LL_escan_extended_adv_receive_process(void* linkpointer,
                                           uint8_t phyindex,
                                           BOOL anonymous_flag,
                                           BOOL receive_address_present_flag,
                                           uint32_t* received_receive_address);

BOOL LL_escan_EauxIsr_ucfg(void* pointer);
BOOL LL_escan_EauxIsr_ucfg_weak(void* pointer);
BOOL LL_escan_EauxIsr(void* pointer);

void LL_Set_Extented_conn_Params_ucfg(uint8_t phy_index,
                                      uint8_t index,
                                      Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters);
void LL_Set_Extented_conn_Params_ucfg_weak(uint8_t phy_index,
                                           uint8_t index,
                                           Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters);
void LL_Set_Extented_conn_Params(uint8_t phy_index,
                                 uint8_t index,
                                 Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters);

void LL_periodic_event_terminate_decision_routine_ucfg(void* pointer);
void LL_periodic_event_terminate_decision_routine_ucfg_weak(void* pointer);
void LL_periodic_event_terminate_decision_routine(void* pointer);

void LL_periodicadv_init_ucfg(uint8_t number_of_periodicadv_contexts,
                              void* LL_periodicadv_context_periodic_per_array);
void LL_periodicadv_init_ucfg_weak(uint8_t number_of_periodicadv_contexts,
                                   void* LL_periodicadv_context_periodic_per_array);
void LL_periodicadv_init(uint8_t number_of_periodicadv_contexts,
                         void* LL_periodicadv_context_periodic_per_array);

void LL_periodicadv_periodicenable_ucfg(void* periodic_per_pointer);
void LL_periodicadv_periodicenable_ucfg_weak(void* periodic_per_pointer);
void LL_periodicadv_periodicenable(void* periodic_per_pointer);

uint8_t periodic_csr_ucfg(void);
uint8_t periodic_csr_ucfg_weak(void);
uint8_t periodic_csr(void);

tBleStatus LL_LE_Set_periodic_adv_data_ptr_function_ucfg(uint16_t advertising_handle,
                                                         uint16_t data_length,
                                                         uint8_t* data);
tBleStatus LL_LE_Set_periodic_adv_data_ptr_function_ucfg_weak(uint16_t advertising_handle,
                                                              uint16_t data_length,
                                                              uint8_t* data);
tBleStatus LL_LE_Set_periodic_adv_data_ptr_function(uint16_t advertising_handle,
                                                    uint16_t data_length,
                                                    uint8_t* data);

BOOL LL_periodicadv_update_sync_info_field_ucfg(void* periodic_context_ptr,
                                                uint8_t* packet,
                                                uint32_t myanchor);
BOOL LL_periodicadv_update_sync_info_field_ucfg_weak(void* periodic_context_ptr,
                                                     uint8_t* packet,
                                                     uint32_t myanchor);
BOOL LL_periodicadv_update_sync_info_field(void* periodic_context_ptr,
                                           uint8_t* packet,
                                           uint32_t myanchor);

uint8_t LL_periodicadv_prepare_periodic_advertising_payload_ucfg(void* pointer,
                                                                 uint8_t packet_type,
                                                                 uint8_t extended_flags_and_data_indication,
                                                                 uint8_t* packet);
uint8_t LL_periodicadv_prepare_periodic_advertising_payload_ucfg_weak(void* pointer,
                                                                      uint8_t packet_type,
                                                                      uint8_t extended_flags_and_data_indication,
                                                                      uint8_t* packet);
uint8_t LL_periodicadv_prepare_periodic_advertising_payload(void* pointer,
                                                            uint8_t packet_type,
                                                            uint8_t extended_flags_and_data_indication,
                                                            uint8_t* packet);

void LL_periodicadv_init_periodic_advertising_context_per_ucfg(void* periodic_per_pointer_dummy);
void LL_periodicadv_init_periodic_advertising_context_per_ucfg_weak(void* periodic_per_pointer_dummy);
void LL_periodicadv_init_periodic_advertising_context_per(void* periodic_per_pointer_dummy);

void LL_padv_adjust_cte_count_with_interval_ucfg(void* pointer,
                                                 BOOL no_data_length_set,
                                                 uint16_t data_length);
void LL_padv_adjust_cte_count_with_interval_ucfg_weak(void* pointer,
                                                      BOOL no_data_length_set,
                                                      uint16_t data_length);
void LL_padv_adjust_cte_count_with_interval(void* pointer,
                                            BOOL no_data_length_set,
                                            uint16_t data_length);

void LL_pscan_restore_pa_list_ucfg(void* pointer);
void LL_pscan_restore_pa_list_ucfg_weak(void* pointer);
void LL_pscan_restore_pa_list(void* pointer);

void LL_periodicscan_deploy_or_connect_periodic_ucfg(void* sync_info_field,
                                                     uint32_t* address_with_SID,
                                                     uint8_t phy,
                                                     uint8_t tx_power,
                                                     BOOL past_mode,
                                                     uint32_t connect_anchor,
                                                     uint8_t conn_idx,
                                                     void* periodicperpointer_dummy,
                                                     uint32_t* privateaddress);
void LL_periodicscan_deploy_or_connect_periodic_ucfg_weak(void* sync_info_field,
                                                          uint32_t* address_with_SID,
                                                          uint8_t phy,
                                                          uint8_t tx_power,
                                                          BOOL past_mode,
                                                          uint32_t connect_anchor,
                                                          uint8_t conn_idx,
                                                          void* periodicperpointer_dummy,
                                                          uint32_t* privateaddress);
void LL_periodicscan_deploy_or_connect_periodic(void* sync_info_field,
                                                uint32_t* address_with_SID,
                                                uint8_t phy,
                                                uint8_t tx_power,
                                                BOOL past_mode,
                                                uint32_t connect_anchor,
                                                uint8_t conn_idx,
                                                void* periodicperpointer_dummy,
                                                uint32_t* privateaddress);

BOOL LL_periodicscan_check_received_txaddress_true_on_accept_ucfg(uint32_t* received_transmit_address);
BOOL LL_periodicscan_check_received_txaddress_true_on_accept_ucfg_weak(uint32_t* received_transmit_address);
BOOL LL_periodicscan_check_received_txaddress_true_on_accept(uint32_t* received_transmit_address);

void LL_periodicscan_init_ucfg(uint8_t number_of_periodic_contexts,
                               void* periodic_context_complete_p,
                               void* pointer,
                               uint8_t PeriodicListSizeLog2,
                               void* PeriodicIDList,
                               void* cpf_past_procedure_overall_context,
                               uint8_t num_connect_link,
                               void* cpf_past_procedure_connect_context_per);
void LL_periodicscan_init_ucfg_weak(uint8_t number_of_periodic_contexts,
                                    void* periodic_context_complete_p,
                                    void* pointer,
                                    uint8_t PeriodicListSizeLog2,
                                    void* PeriodicIDList,
                                    void* cpf_past_procedure_overall_context,
                                    uint8_t num_connect_link,
                                    void* cpf_past_procedure_connect_context_per);
void LL_periodicscan_init(uint8_t number_of_periodic_contexts,
                          void* periodic_context_complete_p,
                          void* pointer,
                          uint8_t PeriodicListSizeLog2,
                          void* PeriodicIDList,
                          void* cpf_past_procedure_overall_context,
                          uint8_t num_connect_link,
                          void* cpf_past_procedure_connect_context_per);

BOOL LL_pscan_validate_CTE_type_ucfg(void* params,
                                     uint8_t CTE_type);
BOOL LL_pscan_validate_CTE_type_ucfg_weak(void* params,
                                          uint8_t CTE_type);
BOOL LL_pscan_validate_CTE_type(void* params,
                                uint8_t CTE_type);

BOOL LL_periodicscan_cancel_slot_cte_ucfg(void* pointer_complete,
                                          void* pointer_per);
BOOL LL_periodicscan_cancel_slot_cte_ucfg_weak(void* pointer_complete,
                                               void* pointer_per);
BOOL LL_periodicscan_cancel_slot_cte(void* pointer_complete,
                                     void* pointer_per);

void LL_priv_vOwnPrivateAddress_ucfg(uint32_t* Own,
                                     uint32_t* Peer,
                                     uint8_t is_ISR);
void LL_priv_vOwnPrivateAddress_ucfg_weak(uint32_t* Own,
                                          uint32_t* Peer,
                                          uint8_t is_ISR);
void LL_priv_vOwnPrivateAddress(uint32_t* Own,
                                uint32_t* Peer,
                                uint8_t is_ISR);

void LL_priv_u8OfflineProcessing_ucfg(uint16_t task_idx);
void LL_priv_u8OfflineProcessing_ucfg_weak(uint16_t task_idx);
void LL_priv_u8OfflineProcessing(uint16_t task_idx);

void LL_priv_vPeerPrivateAddress_ucfg(uint32_t* Peer,
                                      uint8_t is_ISR);
void LL_priv_vPeerPrivateAddress_ucfg_weak(uint32_t* Peer,
                                           uint8_t is_ISR);
void LL_priv_vPeerPrivateAddress(uint32_t* Peer,
                                 uint8_t is_ISR);

uint8_t LL_priv_u32ProcessAdvPacket_ucfg(uint32_t* ReceivedTransmitAddress,
                                         uint8_t PduType,
                                         uint32_t* PeerIDAddress,
                                         uint8_t AdvertisingEventproperties,
                                         uint8_t filterPolicy,
                                         uint32_t* peer_addr,
                                         uint16_t advertisinghandle);
uint8_t LL_priv_u32ProcessAdvPacket_ucfg_weak(uint32_t* ReceivedTransmitAddress,
                                              uint8_t PduType,
                                              uint32_t* PeerIDAddress,
                                              uint8_t AdvertisingEventproperties,
                                              uint8_t filterPolicy,
                                              uint32_t* peer_addr,
                                              uint16_t advertisinghandle);
uint8_t LL_priv_u32ProcessAdvPacket(uint32_t* ReceivedTransmitAddress,
                                    uint8_t PduType,
                                    uint32_t* PeerIDAddress,
                                    uint8_t AdvertisingEventproperties,
                                    uint8_t filterPolicy,
                                    uint32_t* peer_addr,
                                    uint16_t advertisinghandle);

uint8_t LL_priv_u32ProcessScanPacketTx_ucfg(uint32_t* ReceivedTransmitAddress,
                                            uint32_t* PeerIDaddress,
                                            uint8_t isScanner,
                                            uint8_t* initPeerAddr,
                                            uint8_t initPeerAddrType,
                                            uint8_t LocalFilterPolicy,
                                            uint8_t resolvedirect,
                                            uint8_t* DatabaseEntry);
uint8_t LL_priv_u32ProcessScanPacketTx_ucfg_weak(uint32_t* ReceivedTransmitAddress,
                                                 uint32_t* PeerIDaddress,
                                                 uint8_t isScanner,
                                                 uint8_t* initPeerAddr,
                                                 uint8_t initPeerAddrType,
                                                 uint8_t LocalFilterPolicy,
                                                 uint8_t resolvedirect,
                                                 uint8_t* DatabaseEntry);
uint8_t LL_priv_u32ProcessScanPacketTx(uint32_t* ReceivedTransmitAddress,
                                       uint32_t* PeerIDaddress,
                                       uint8_t isScanner,
                                       uint8_t* initPeerAddr,
                                       uint8_t initPeerAddrType,
                                       uint8_t LocalFilterPolicy,
                                       uint8_t resolvedirect,
                                       uint8_t* DatabaseEntry);

uint8_t LL_priv_u32ProcessScanPacketRx_ucfg(uint32_t* ReceivedReceiveAddress,
                                            uint8_t LocalFilterPolicy,
                                            uint32_t* own_addr_used,
                                            uint8_t PointerToDataBase,
                                            uint8_t resolvedirect);
uint8_t LL_priv_u32ProcessScanPacketRx_ucfg_weak(uint32_t* ReceivedReceiveAddress,
                                                 uint8_t LocalFilterPolicy,
                                                 uint32_t* own_addr_used,
                                                 uint8_t PointerToDataBase,
                                                 uint8_t resolvedirect);
uint8_t LL_priv_u32ProcessScanPacketRx(uint32_t* ReceivedReceiveAddress,
                                       uint8_t LocalFilterPolicy,
                                       uint32_t* own_addr_used,
                                       uint8_t PointerToDataBase,
                                       uint8_t resolvedirect);

void LL_priv_SynchPeerIDList_And_WhiteIDList_ucfg(void);
void LL_priv_SynchPeerIDList_And_WhiteIDList_ucfg_weak(void);
void LL_priv_SynchPeerIDList_And_WhiteIDList(void);

void LL_priv_Init_ResolvedPart_ucfg(BOOL general_init);
void LL_priv_Init_ResolvedPart_ucfg_weak(BOOL general_init);
void LL_priv_Init_ResolvedPart(BOOL general_init);

BOOL Data_Len_Update_Offline_Processing_ucfg(void* params,
                                             uint32_t ctrl_flds);
BOOL Data_Len_Update_Offline_Processing_ucfg_weak(void* params,
                                                  uint32_t ctrl_flds);
BOOL Data_Len_Update_Offline_Processing(void* params,
                                        uint32_t ctrl_flds);

tBleStatus ll_write_supported_data_ucfg(uint16_t Supported_Max_Tx_Octets,
                                        uint16_t Supported_Max_Tx_Time,
                                        uint16_t Supported_Max_Rx_Octets,
                                        uint16_t Supported_Max_Rx_Time);
tBleStatus ll_write_supported_data_ucfg_weak(uint16_t Supported_Max_Tx_Octets,
                                             uint16_t Supported_Max_Tx_Time,
                                             uint16_t Supported_Max_Rx_Octets,
                                             uint16_t Supported_Max_Rx_Time);
tBleStatus ll_write_supported_data(uint16_t Supported_Max_Tx_Octets,
                                   uint16_t Supported_Max_Tx_Time,
                                   uint16_t Supported_Max_Rx_Octets,
                                   uint16_t Supported_Max_Rx_Time);

void LL_Get_Supported_States_ucfg(uint8_t states[8]);
void LL_Get_Supported_States_ucfg_weak(uint8_t states[8]);
void LL_Get_Supported_States(uint8_t states[8]);

tBleStatus LL_Start_Encryption_ucfg(uint16_t connHandle,
                                    uint8_t* randNum,
                                    uint8_t* ediv,
                                    uint8_t* ltk);
tBleStatus LL_Start_Encryption_ucfg_weak(uint16_t connHandle,
                                         uint8_t* randNum,
                                         uint8_t* ediv,
                                         uint8_t* ltk);
tBleStatus LL_Start_Encryption(uint16_t connHandle,
                               uint8_t* randNum,
                               uint8_t* ediv,
                               uint8_t* ltk);

void aci_gap_numeric_comparison_value_event_cb_ucfg(uint8_t header_type,
                                                    uint8_t* buff_p);
void aci_gap_numeric_comparison_value_event_cb_ucfg_weak(uint8_t header_type,
                                                         uint8_t* buff_p);
void aci_gap_numeric_comparison_value_event_cb(uint8_t header_type,
                                               uint8_t* buff_p);

void aci_gap_keypress_notification_event_cb_ucfg(uint8_t header_type,
                                                 uint8_t* buff_p);
void aci_gap_keypress_notification_event_cb_ucfg_weak(uint8_t header_type,
                                                      uint8_t* buff_p);
void aci_gap_keypress_notification_event_cb(uint8_t header_type,
                                            uint8_t* buff_p);

tBleStatus smp_MI_Start_Encryption_ucfg(void* params);
tBleStatus smp_MI_Start_Encryption_ucfg_weak(void* params);
tBleStatus smp_MI_Start_Encryption(void* params);

void smp_Execute_Actions_wrt_Current_State_MI_excerpt_ucfg(void* params);
void smp_Execute_Actions_wrt_Current_State_MI_excerpt_ucfg_weak(void* params);
void smp_Execute_Actions_wrt_Current_State_MI_excerpt(void* params);

tBleStatus smp_Process_Rx_Packet_wrt_Current_State_MI_excerpt_ucfg(void* params);
tBleStatus smp_Process_Rx_Packet_wrt_Current_State_MI_excerpt_ucfg_weak(void* params);
tBleStatus smp_Process_Rx_Packet_wrt_Current_State_MI_excerpt(void* params);

tBleStatus smp_sc_MI_PairingResponse_Receive_sc_excerpt_ucfg(void* params);
tBleStatus smp_sc_MI_PairingResponse_Receive_sc_excerpt_ucfg_weak(void* params);
tBleStatus smp_sc_MI_PairingResponse_Receive_sc_excerpt(void* params);

void smp_sc_MI_Pairing_Phase_2AS1_Start_sc_excerpt_ucfg(void* params);
void smp_sc_MI_Pairing_Phase_2AS1_Start_sc_excerpt_ucfg_weak(void* params);
void smp_sc_MI_Pairing_Phase_2AS1_Start_sc_excerpt(void* params);

void smp_sc_SR_Pairing_Phase_2AS1_Start_sc_excerpt_ucfg(void* params);
void smp_sc_SR_Pairing_Phase_2AS1_Start_sc_excerpt_ucfg_weak(void* params);
void smp_sc_SR_Pairing_Phase_2AS1_Start_sc_excerpt(void* params);

void smp_sc_MI_PairingConfirm_Send_sc_excerpt_ucfg(void* params);
void smp_sc_MI_PairingConfirm_Send_sc_excerpt_ucfg_weak(void* params);
void smp_sc_MI_PairingConfirm_Send_sc_excerpt(void* params);

tBleStatus smp_sc_MI_PairingRandom_Receive_sc_excerpt1_ucfg(void* params);
tBleStatus smp_sc_MI_PairingRandom_Receive_sc_excerpt1_ucfg_weak(void* params);
tBleStatus smp_sc_MI_PairingRandom_Receive_sc_excerpt1(void* params);

void smp_sc_MI_PairingRandom_Receive_sc_excerpt2_ucfg(void* params);
void smp_sc_MI_PairingRandom_Receive_sc_excerpt2_ucfg_weak(void* params);
void smp_sc_MI_PairingRandom_Receive_sc_excerpt2(void* params);

void smp_sc_SR_PairingConfirm_Receive_sc_excerpt_ucfg(void* params);
void smp_sc_SR_PairingConfirm_Receive_sc_excerpt_ucfg_weak(void* params);
void smp_sc_SR_PairingConfirm_Receive_sc_excerpt(void* params);

void smp_sc_SR_PairingRandom_Receive_sc_excerpt_ucfg(void* params);
void smp_sc_SR_PairingRandom_Receive_sc_excerpt_ucfg_weak(void* params);
void smp_sc_SR_PairingRandom_Receive_sc_excerpt(void* params);

BOOL smp_execute_actions_wrt_state_sc_phase1to2_ucfg(void* params);
BOOL smp_execute_actions_wrt_state_sc_phase1to2_ucfg_weak(void* params);
BOOL smp_execute_actions_wrt_state_sc_phase1to2(void* params);

void smp_execute_actions_wrt_state_sc_phase2as2_ucfg(void* params);
void smp_execute_actions_wrt_state_sc_phase2as2_ucfg_weak(void* params);
void smp_execute_actions_wrt_state_sc_phase2as2(void* params);

tBleStatus smp_Process_Rx_Packet_wrt_Current_State_sc_excerpt_ucfg(void* params);
tBleStatus smp_Process_Rx_Packet_wrt_Current_State_sc_excerpt_ucfg_weak(void* params);
tBleStatus smp_Process_Rx_Packet_wrt_Current_State_sc_excerpt(void* params);

tBleStatus smp_Process_Rx_Packet_Exception_Cases_sc_excerpt_ucfg(void* params);
tBleStatus smp_Process_Rx_Packet_Exception_Cases_sc_excerpt_ucfg_weak(void* params);
tBleStatus smp_Process_Rx_Packet_Exception_Cases_sc_excerpt(void* params);

void smp_execute_actions_wrt_state_sc_phase2as2_mi_ucfg(void* params);
void smp_execute_actions_wrt_state_sc_phase2as2_mi_ucfg_weak(void* params);
void smp_execute_actions_wrt_state_sc_phase2as2_mi(void* params);

void SMP_process_sc_ecc_pk_generation_tsk_ucfg(uint16_t task_idx);
void SMP_process_sc_ecc_pk_generation_tsk_ucfg_weak(uint16_t task_idx);
void SMP_process_sc_ecc_pk_generation_tsk(uint16_t task_idx);

void smp_sc_init_ucfg(BOOL useDebugKey);
void smp_sc_init_ucfg_weak(BOOL useDebugKey);
void smp_sc_init(BOOL useDebugKey);

tBleStatus smp_sc_continue_on_exclusive_sc_pairing_ucfg(void* params);
tBleStatus smp_sc_continue_on_exclusive_sc_pairing_ucfg_weak(void* params);
tBleStatus smp_sc_continue_on_exclusive_sc_pairing(void* params);

tBleStatus smp_sc_generate_new_local_oob_data_ucfg(void);
tBleStatus smp_sc_generate_new_local_oob_data_ucfg_weak(void);
tBleStatus smp_sc_generate_new_local_oob_data(void);

void smp_sc_update_statistics_on_pairing_complete_ucfg(void* params);
void smp_sc_update_statistics_on_pairing_complete_ucfg_weak(void* params);
void smp_sc_update_statistics_on_pairing_complete(void* params);

uint32_t secure_connections_csr_ucfg(void);
uint32_t secure_connections_csr_ucfg_weak(void);
uint32_t secure_connections_csr(void);

void smp_sc_hci_le_read_local_p256_public_key_complete_evt_hndl_ucfg(uint8_t status,
                                                                     uint8_t local_p256_public_key[64]);
void smp_sc_hci_le_read_local_p256_public_key_complete_evt_hndl_ucfg_weak(uint8_t status,
                                                                          uint8_t local_p256_public_key[64]);
void smp_sc_hci_le_read_local_p256_public_key_complete_evt_hndl(uint8_t status,
                                                                uint8_t local_p256_public_key[64]);

void smp_sc_hci_le_generate_dhkey_complete_evt_hndl_ucfg(uint8_t status,
                                                         uint8_t DHKey[32]);
void smp_sc_hci_le_generate_dhkey_complete_evt_hndl_ucfg_weak(uint8_t status,
                                                              uint8_t DHKey[32]);
void smp_sc_hci_le_generate_dhkey_complete_evt_hndl(uint8_t status,
                                                    uint8_t DHKey[32]);

tBleStatus aci_gap_start_connection_update_api(uint16_t Connection_Handle,
                                               uint16_t Conn_Interval_Min,
                                               uint16_t Conn_Interval_Max,
                                               uint16_t Conn_Latency,
                                               uint16_t Supervision_Timeout,
                                               uint16_t Minimum_CE_Length,
                                               uint16_t Maximum_CE_Length);

tBleStatus aci_gap_send_pairing_req_api(uint16_t Connection_Handle,
                                        uint8_t Force_Rebond);

tBleStatus aci_gap_numeric_comparison_value_confirm_yesno_api(uint16_t Connection_Handle,
                                                              uint8_t Confirm_Yes_No);

tBleStatus aci_gap_passkey_input_api(uint16_t Connection_Handle,
                                     uint8_t Input_Type);

tBleStatus aci_gap_set_scan_configuration_api(uint8_t duplicate_filtering,
                                              uint8_t scanning_filter_policy,
                                              uint8_t phy,
                                              uint8_t scan_type,
                                              uint16_t scan_interval,
                                              uint16_t scan_window);

tBleStatus aci_gap_set_connection_configuration_api(uint8_t phy,
                                                    uint16_t conn_interval_min,
                                                    uint16_t conn_interval_max,
                                                    uint16_t conn_latency,
                                                    uint16_t supervision_timeout,
                                                    uint16_t minimum_ce_length,
                                                    uint16_t maximum_ce_length);

tBleStatus aci_gap_create_connection_api(uint8_t Initiating_PHY,
                                         uint8_t Peer_Address_Type,
                                         uint8_t Peer_Address[6]);

tBleStatus aci_gap_start_procedure_api(uint8_t procedure_code,
                                       uint8_t phys,
                                       uint16_t duration,
                                       uint16_t period);

tBleStatus aci_gap_discover_name_api(uint8_t PHYs,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6]);

tBleStatus aci_gap_terminate_proc_api(uint8_t Procedure_Code);

tBleStatus aci_gap_set_periodic_advertising_configuration_api(uint8_t Advertising_Handle,
                                                              uint16_t Periodic_Advertising_Interval_Min,
                                                              uint16_t Periodic_Advertising_Interval_Max,
                                                              uint16_t Periodic_Advertising_Properties);

tBleStatus aci_gap_set_periodic_advertising_enable_api(uint8_t Enable,
                                                       uint8_t Advertising_Handle);

tBleStatus aci_gap_set_periodic_advertising_data_api(uint8_t Advertising_Handle,
                                                     uint8_t Advertising_Data_Length,
                                                     uint8_t* Advertising_Data);

tBleStatus aci_gap_periodic_advertising_create_sync_api(uint8_t Options,
                                                        uint8_t Advertising_SID,
                                                        uint8_t Advertising_Address_Type,
                                                        uint8_t Advertiser_Address[6],
                                                        uint16_t Skip,
                                                        uint16_t Sync_Timeout,
                                                        uint8_t Sync_CTE_Type);

tBleStatus aci_gap_periodic_advertising_create_sync_cancel_api(void);

tBleStatus aci_gap_periodic_advertising_terminate_sync_api(uint16_t Sync_Handle);

tBleStatus aci_gap_set_periodic_advertising_receive_enable_api(uint16_t Sync_Handle,
                                                               uint8_t Enable);

tBleStatus aci_gap_add_device_to_periodic_advertiser_list_api(uint8_t Advertiser_Address_Type,
                                                              uint8_t Advertiser_Address[6],
                                                              uint8_t Advertising_SID);

tBleStatus aci_gap_remove_device_from_periodic_advertising_list_api(uint8_t Advertiser_Address_Type,
                                                                    uint8_t Advertiser_Address[6],
                                                                    uint8_t Advertising_SID);

tBleStatus aci_gap_clear_periodic_advertiser_list_api(void);

tBleStatus aci_gap_read_periodic_advertiser_list_size_api(uint8_t* Periodic_Advertiser_List_Size);

tBleStatus aci_gap_periodic_advertising_sync_transfer_api(uint16_t Connection_Handle,
                                                          uint16_t Service_Data,
                                                          uint16_t Sync_Handle);

tBleStatus aci_gap_periodic_advertising_set_info_transfer_api(uint16_t Connection_Handle,
                                                              uint16_t Service_Data,
                                                              uint8_t Advertising_Handle);

tBleStatus aci_gap_set_periodic_advertising_sync_transfer_parameters_api(uint16_t Connection_Handle,
                                                                         uint8_t Mode,
                                                                         uint16_t Skip,
                                                                         uint16_t Sync_Timeout,
                                                                         uint8_t CTE_Type);

tBleStatus aci_gap_set_default_periodic_advertising_sync_transfer_parameters_api(uint8_t Mode,
                                                                                 uint16_t Skip,
                                                                                 uint16_t Sync_Timeout,
                                                                                 uint8_t CTE_Type);

tBleStatus aci_gap_remove_advertising_set_api(uint8_t Advertising_Handle);

tBleStatus aci_gap_clear_advertising_sets_api(void);

tBleStatus aci_hal_set_le_power_control_api(uint8_t Enable,
                                            uint8_t PHY,
                                            int8_t RSSI_Target,
                                            uint8_t RSSI_Hysteresis,
                                            int8_t Initial_TX_Power,
                                            uint8_t RSSI_Filtering_Coefficient);

tBleStatus aci_l2cap_connection_parameter_update_resp_api(uint16_t Connection_Handle,
                                                          uint16_t Conn_Interval_Min,
                                                          uint16_t Conn_Interval_Max,
                                                          uint16_t Slave_latency,
                                                          uint16_t Timeout_Multiplier,
                                                          uint16_t Minimum_CE_Length,
                                                          uint16_t Maximum_CE_Length,
                                                          uint8_t Identifier,
                                                          uint8_t Accept);

tBleStatus aci_l2cap_cfc_connection_req_api(uint16_t Connection_Handle,
                                            uint16_t SPSM,
                                            uint16_t CID,
                                            uint16_t MTU,
                                            uint16_t MPS,
                                            uint8_t CFC_Policy,
                                            uint16_t RX_SDU_Buffer_Size,
                                            void* RX_SDU_Buffer);

tBleStatus aci_l2cap_cfc_connection_resp_api(uint16_t Connection_Handle,
                                             uint8_t Identifier,
                                             uint16_t CID,
                                             uint16_t MTU,
                                             uint16_t MPS,
                                             uint16_t Result,
                                             uint8_t CFC_Policy,
                                             uint16_t RX_SDU_Buffer_Size,
                                             void* RX_SDU_Buffer);

tBleStatus aci_l2cap_send_flow_control_credits_api(uint16_t Connection_Handle,
                                                   uint16_t CID,
                                                   uint16_t RX_Credits,
                                                   uint8_t CFC_Policy,
                                                   uint16_t* RX_Credit_Balance);

tBleStatus aci_l2cap_disconnect_api(uint16_t Connection_Handle,
                                    uint16_t CID);

tBleStatus aci_l2cap_transmit_sdu_data_api(uint16_t Connection_Handle,
                                           uint16_t CID,
                                           uint16_t SDU_Length,
                                           uint8_t* SDU_Data);

tBleStatus aci_l2cap_extract_sdu_data_api(uint16_t Connection_Handle,
                                          uint16_t CID,
                                          uint16_t SDU_Data_Buffer_Size,
                                          void* SDU_Data_Buffer,
                                          uint16_t* SDU_Length);

tBleStatus hci_le_set_host_channel_classification_api(uint8_t LE_Channel_Map[5]);

tBleStatus hci_le_set_connectionless_cte_transmit_parameters_api(uint8_t Advertising_Handle,
                                                                 uint8_t CTE_Length,
                                                                 uint8_t CTE_Type,
                                                                 uint8_t CTE_Count,
                                                                 uint8_t Switching_Pattern_Length,
                                                                 uint8_t* Antenna_IDs);

tBleStatus hci_le_set_connectionless_cte_transmit_enable_api(uint8_t Advertising_Handle,
                                                             uint8_t CTE_Enable);

tBleStatus hci_le_set_connectionless_iq_sampling_enable_api(uint16_t Sync_Handle,
                                                            uint8_t Sampling_Enable,
                                                            uint8_t Slot_Durations,
                                                            uint8_t Max_Sampled_CTEs,
                                                            uint8_t Switching_Pattern_Length,
                                                            uint8_t* Antenna_IDs);

tBleStatus hci_le_set_connection_cte_receive_parameters_api(uint16_t Connection_Handle,
                                                            uint8_t Sampling_Enable,
                                                            uint8_t Slot_Durations,
                                                            uint8_t Switching_Pattern_Length,
                                                            uint8_t* Antenna_IDs);

tBleStatus hci_le_set_connection_cte_transmit_parameters_api(uint16_t Connection_Handle,
                                                             uint8_t CTE_Type,
                                                             uint8_t Switching_Pattern_Length,
                                                             uint8_t* Antenna_IDs);

tBleStatus hci_le_connection_cte_request_enable_api(uint16_t Connection_Handle,
                                                    uint8_t Enable,
                                                    uint16_t CTE_Request_Interval,
                                                    uint8_t Requested_CTE_Length,
                                                    uint8_t Requested_CTE_Type);

tBleStatus hci_le_connection_cte_response_enable_api(uint16_t Connection_Handle,
                                                     uint8_t Enable);

tBleStatus hci_le_read_antenna_information_api(uint8_t* Supported_Switching_Sampling_Rates,
                                               uint8_t* Num_Antennae,
                                               uint8_t* Max_Switching_Pattern_Length,
                                               uint8_t* Max_CTE_Length);

tBleStatus hci_le_start_encryption_api(uint16_t Connection_Handle,
                                       uint8_t Random_Number[8],
                                       uint16_t Encrypted_Diversifier,
                                       uint8_t Long_Term_Key[16]);

tBleStatus hci_le_read_local_p256_public_key_api(void);

tBleStatus hci_le_generate_dhkey_api(uint8_t Remote_P256_Public_Key[64]);

tBleStatus hci_le_set_extended_advertising_parameters_api(uint8_t Advertising_Handle,
                                                          uint16_t Advertising_Event_Properties,
                                                          uint8_t Primary_Advertising_Interval_Min[3],
                                                          uint8_t Primary_Advertising_Interval_Max[3],
                                                          uint8_t Primary_Advertising_Channel_Map,
                                                          uint8_t Own_Address_Type,
                                                          uint8_t Peer_Address_Type,
                                                          uint8_t Peer_Address[6],
                                                          uint8_t Advertising_Filter_Policy,
                                                          int8_t Advertising_Tx_Power,
                                                          uint8_t Primary_Advertising_PHY,
                                                          uint8_t Secondary_Advertising_Max_Skip,
                                                          uint8_t Secondary_Advertising_PHY,
                                                          uint8_t Advertising_SID,
                                                          uint8_t Scan_Request_Notification_Enable,
                                                          int8_t* Selected_Tx_Power);

tBleStatus hci_le_set_advertising_set_random_address_api(uint8_t Advertising_Handle,
                                                         uint8_t Advertising_Random_Address[6]);

tBleStatus hci_le_set_extended_advertising_enable_api(uint8_t Enable,
                                                      uint8_t Number_of_Sets,
                                                      Advertising_Set_Parameters_t* Advertising_Set_Parameters);

tBleStatus hci_le_read_number_of_supported_advertising_sets_api(uint8_t* Num_Supported_Advertising_Sets);

tBleStatus hci_le_remove_advertising_set_api(uint8_t Advertising_Handle);

tBleStatus hci_le_clear_advertising_sets_api(void);

tBleStatus hci_le_set_periodic_advertising_parameters_api(uint8_t Advertising_Handle,
                                                          uint16_t Periodic_Advertising_Interval_Min,
                                                          uint16_t Periodic_Advertising_Interval_Max,
                                                          uint16_t Periodic_Advertising_Properties);

tBleStatus hci_le_set_periodic_advertising_enable_api(uint8_t Enable,
                                                      uint8_t Advertising_Handle);

tBleStatus hci_le_set_extended_scan_parameters_api(uint8_t Own_Address_Type,
                                                   uint8_t Scanning_Filter_Policy,
                                                   uint8_t Scanning_PHYs,
                                                   Extended_Scan_Parameters_t* Extended_Scan_Parameters);

tBleStatus hci_le_set_extended_scan_enable_api(uint8_t Enable,
                                               uint8_t Filter_Duplicates,
                                               uint16_t Duration,
                                               uint16_t Period);

tBleStatus hci_le_extended_create_connection_api(uint8_t Initiating_Filter_Policy,
                                                 uint8_t Own_Address_Type,
                                                 uint8_t Peer_Address_Type,
                                                 uint8_t Peer_Address[6],
                                                 uint8_t Initiating_PHYs,
                                                 Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters);

tBleStatus hci_le_periodic_advertising_create_sync_api(uint8_t Options,
                                                       uint8_t Advertising_SID,
                                                       uint8_t Advertising_Address_Type,
                                                       uint8_t Advertiser_Address[6],
                                                       uint16_t Skip,
                                                       uint16_t Sync_Timeout,
                                                       uint8_t Sync_CTE_Type);

tBleStatus hci_le_periodic_advertising_create_sync_cancel_api(void);

tBleStatus hci_le_periodic_advertising_terminate_sync_api(uint16_t Sync_Handle);

tBleStatus hci_le_add_device_to_periodic_advertiser_list_api(uint8_t Advertiser_Address_Type,
                                                             uint8_t Advertiser_Address[6],
                                                             uint8_t Advertising_SID);

tBleStatus hci_le_remove_device_from_periodic_advertising_list_api(uint8_t Advertiser_Address_Type,
                                                                   uint8_t Advertiser_Address[6],
                                                                   uint8_t Advertising_SID);

tBleStatus hci_le_clear_periodic_advertiser_list_api(void);

tBleStatus hci_le_read_periodic_advertiser_list_size_api(uint8_t* Periodic_Advertiser_List_Size);

tBleStatus hci_le_set_periodic_advertising_receive_enable_api(uint16_t Sync_Handle,
                                                              uint8_t Enable);

tBleStatus hci_le_set_default_periodic_advertising_sync_transfer_parameters_api(uint8_t Mode,
                                                                                uint16_t Skip,
                                                                                uint16_t Sync_Timeout,
                                                                                uint8_t CTE_Type);

tBleStatus hci_le_set_periodic_advertising_sync_transfer_parameters_api(uint16_t Connection_Handle,
                                                                        uint8_t Mode,
                                                                        uint16_t Skip,
                                                                        uint16_t Sync_Timeout,
                                                                        uint8_t CTE_Type);

tBleStatus hci_le_periodic_advertising_set_info_transfer_api(uint16_t Connection_Handle,
                                                             uint16_t Service_Data,
                                                             uint8_t Advertising_Handle);

tBleStatus hci_le_periodic_advertising_sync_transfer_api(uint16_t Connection_Handle,
                                                         uint16_t Service_Data,
                                                         uint16_t Sync_Handle);

tBleStatus hci_le_set_data_length_api(uint16_t Connection_Handle,
                                      uint16_t Tx_Octets,
                                      uint16_t Tx_Time);

tBleStatus hci_le_read_suggested_default_data_length_api(uint16_t* Suggested_Max_Tx_Octets,
                                                         uint16_t* Suggested_Max_Tx_Time);

tBleStatus hci_le_write_suggested_default_data_length_api(uint16_t Suggested_Max_Tx_Octets,
                                                          uint16_t Suggested_Max_Tx_Time);

tBleStatus hci_le_read_maximum_data_length_api(uint16_t* Supported_Max_Tx_Octets,
                                               uint16_t* Supported_Max_Tx_Time,
                                               uint16_t* Supported_Max_Rx_Octets,
                                               uint16_t* Supported_Max_Rx_Time);

tBleStatus hci_le_enhanced_read_transmit_power_level_api(uint16_t Connection_Handle,
                                                         uint8_t PHY,
                                                         int8_t* Current_TX_Power_Level,
                                                         int8_t* Max_TX_Power_Level);

tBleStatus hci_le_read_remote_transmit_power_level_api(uint16_t Connection_Handle,
                                                       uint8_t PHY);

tBleStatus hci_le_set_path_loss_reporting_parameters_api(uint16_t Connection_Handle,
                                                         uint8_t High_Threshold,
                                                         uint8_t High_Hysteresis,
                                                         uint8_t Low_Threshold,
                                                         uint8_t Low_Hysteresis,
                                                         uint16_t Min_Time_Spent);

tBleStatus hci_le_set_path_loss_reporting_enable_api(uint16_t Connection_Handle,
                                                     uint8_t Enable);

tBleStatus hci_le_set_transmit_power_reporting_enable_api(uint16_t Connection_Handle,
                                                          uint8_t Local_Enable,
                                                          uint8_t Remote_Enable);

tBleStatus hci_le_read_phy_api(uint16_t Connection_Handle,
                               uint8_t* TX_PHY,
                               uint8_t* RX_PHY);

tBleStatus hci_le_set_default_phy_api(uint8_t ALL_PHYS,
                                      uint8_t TX_PHYS,
                                      uint8_t RX_PHYS);

tBleStatus hci_le_set_phy_api(uint16_t Connection_Handle,
                              uint8_t ALL_PHYS,
                              uint8_t TX_PHYS,
                              uint8_t RX_PHYS,
                              uint16_t PHY_options);

tBleStatus hci_le_remove_device_from_resolving_list_api(uint8_t Peer_Identity_Address_Type,
                                                        uint8_t Peer_Identity_Address[6]);

tBleStatus hci_le_add_device_to_resolving_list_api(uint8_t Peer_Identity_Address_Type,
                                                   uint8_t Peer_Identity_Address[6],
                                                   uint8_t Peer_IRK[16],
                                                   uint8_t Local_IRK[16]);

tBleStatus hci_le_set_resolvable_private_address_timeout_api(uint16_t RpaTimeout);

tBleStatus hci_le_set_address_resolution_enable_api(uint8_t AddressResolutionEnable);

tBleStatus hci_le_read_peer_resolvable_address_api(uint8_t Peer_Identity_Address_Type,
                                                   uint8_t Peer_Identity_Address[6],
                                                   uint8_t Peer_Resolvable_Address[6]);

tBleStatus hci_le_read_local_resolvable_address_api(uint8_t Peer_Identity_Address_Type,
                                                    uint8_t Peer_Identity_Address[6],
                                                    uint8_t Local_Resolvable_Address[6]);

tBleStatus hci_le_read_resolving_list_size_api(uint8_t* resolving_List_Size);

tBleStatus hci_le_clear_resolving_list_api(void);

tBleStatus hci_le_set_privacy_mode_api(uint8_t Peer_Identity_Address_Type,
                                       uint8_t Peer_Identity_Address[6],
                                       uint8_t Privacy_Mode);

tBleStatus hci_le_set_scan_parameters_api(uint8_t LE_Scan_Type,
                                          uint16_t LE_Scan_Interval,
                                          uint16_t LE_Scan_Window,
                                          uint8_t Own_Address_Type,
                                          uint8_t Scanning_Filter_Policy);

tBleStatus hci_le_set_scan_enable_api(uint8_t LE_Scan_Enable,
                                      uint8_t Filter_Duplicates);

tBleStatus hci_le_create_connection_api(uint16_t LE_Scan_Interval,
                                        uint16_t LE_Scan_Window,
                                        uint8_t Initiator_Filter_Policy,
                                        uint8_t Peer_Address_Type,
                                        uint8_t Peer_Address[6],
                                        uint8_t Own_Address_Type,
                                        uint16_t Conn_Interval_Min,
                                        uint16_t Conn_Interval_Max,
                                        uint16_t Conn_Latency,
                                        uint16_t Supervision_Timeout,
                                        uint16_t Minimum_CE_Length,
                                        uint16_t Maximum_CE_Length);

tBleStatus hci_le_create_connection_cancel_api(void);

tBleStatus hci_le_connection_update_api(uint16_t Connection_Handle,
                                        uint16_t Conn_Interval_Min,
                                        uint16_t Conn_Interval_Max,
                                        uint16_t Conn_Latency,
                                        uint16_t Supervision_Timeout,
                                        uint16_t Minimum_CE_Length,
                                        uint16_t Maximum_CE_Length);

tBleStatus hci_le_enhanced_receiver_test_api(uint8_t RX_Frequency,
                                             uint8_t Phy,
                                             uint8_t Modulation_index);

tBleStatus hci_le_receiver_test_v3_api(uint8_t RX_Channel,
                                       uint8_t PHY,
                                       uint8_t Modulation_Index,
                                       uint8_t Expected_CTE_Length,
                                       uint8_t Expected_CTE_Type,
                                       uint8_t Slot_Durations,
                                       uint8_t Switching_Pattern_Length,
                                       uint8_t* Antenna_IDs);

tBleStatus hci_le_enhanced_transmitter_test_api(uint8_t TX_Frequency,
                                                uint8_t Length_Of_Test_Data,
                                                uint8_t Packet_Payload,
                                                uint8_t Phy);

tBleStatus hci_le_transmitter_test_v3_api(uint8_t TX_Channel,
                                          uint8_t Test_Data_Length,
                                          uint8_t Packet_Payload,
                                          uint8_t PHY,
                                          uint8_t CTE_Length,
                                          uint8_t CTE_Type,
                                          uint8_t Switching_Pattern_Length,
                                          uint8_t* Antenna_IDs);

tBleStatus hci_le_transmitter_test_v4_api(uint8_t TX_Channel,
                                          uint8_t Test_Data_Length,
                                          uint8_t Packet_Payload,
                                          uint8_t PHY,
                                          uint8_t CTE_Length,
                                          uint8_t CTE_Type,
                                          uint8_t Switching_Pattern_Length,
                                          uint8_t* Antenna_IDs,
                                          int8_t Transmit_Power_Level);


void Get_Random_Addr(uint8_t *randBdAddr);

#endif /* _STACK_USER_CFG_H_ */

