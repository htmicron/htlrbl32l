
/**
  ******************************************************************************
  * @file    stack_user_cfg.c
  * @author  AMS - RF Application team
  * @version V1.1.0
  * @date    08 April 2021
  * @brief   BLE stack modular configuration options file
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
      -- Power Control & Path Loss Monitoring
    
    - In order to configure the BLE stack v3.1 or later the following options are available:
        
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

#include "stack_user_cfg.h"

/* check whether all the configuration flag macros are defined */
#if !defined(CONTROLLER_PRIVACY_ENABLED)
#error "CONTROLLER_PRIVACY_ENABLED is not defined"
#endif
#if !defined(SECURE_CONNECTIONS_ENABLED)
#error "SECURE_CONNECTIONS_ENABLED is not defined"
#endif
#if !defined(CONTROLLER_MASTER_ENABLED)
#error "CONTROLLER_MASTER_ENABLED is not defined"
#endif
#if !defined(CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED)
#error "CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED is not defined"
#endif
#if !defined(CONTROLLER_2M_CODED_PHY_ENABLED)
#error "CONTROLLER_2M_CODED_PHY_ENABLED is not defined"
#endif
#if !defined(CONTROLLER_EXT_ADV_SCAN_ENABLED)
#error "CONTROLLER_EXT_ADV_SCAN_ENABLED is not defined"
#endif
#if !defined(L2CAP_COS_ENABLED)
#error "L2CAP_COS_ENABLED is not defined"
#endif
#if !defined(CONTROLLER_PERIODIC_ADV_ENABLED)
#error "CONTROLLER_PERIODIC_ADV_ENABLED is not defined"
#endif
#if !defined(CONTROLLER_CTE_ENABLED)
#error "CONTROLLER_CTE_ENABLED is not defined"
#endif
#if !defined(CONTROLLER_POWER_CONTROL_ENABLED)
#error "CONTROLLER_POWER_CONTROL_ENABLED is not defined"
#endif

/* check whether all the dependencies between the configuration flag macros are met */
#if (CONTROLLER_PERIODIC_ADV_ENABLED == 1) && \
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 0)
#error "CONTROLLER_PERIODIC_ADV_ENABLED cannot be 1"
#endif


/*
* *****************************************************************************
*                      BLE Stack INTERNAL core functions
* *****************************************************************************
*/

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
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
                                                  uint8_t Scan_Request_Notification_Enable)
{
    return GAP_set_extended_advertising_configuration(Advertising_Handle,
                                                      Discoverability_Mode,
                                                      Advertising_Event_Properties,
                                                      Primary_Advertising_Interval_Min,
                                                      Primary_Advertising_Interval_Max,
                                                      Primary_Advertising_Channel_Map,
                                                      Peer_Address_Type,
                                                      Peer_Address,
                                                      Advertising_Filter_Policy,
                                                      Advertising_Tx_Power,
                                                      Primary_Advertising_PHY,
                                                      Secondary_Advertising_Max_Skip,
                                                      Secondary_Advertising_PHY,
                                                      Advertising_SID,
                                                      Scan_Request_Notification_Enable);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_scan_response_data_ucfg(uint8_t Advertising_Handle,
                                           uint16_t Scan_Response_Data_Length,
                                           uint8_t* Scan_Response_Data)
{
    return GAP_set_extended_scan_response_data(Advertising_Handle,
                                               Scan_Response_Data_Length,
                                               Scan_Response_Data);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_advertising_data_ucfg(uint8_t Advertising_Handle,
                                         uint8_t Operation,
                                         uint16_t Advertising_Data_Length,
                                         uint8_t* Advertising_Data)
{
    return GAP_set_extended_advertising_data(Advertising_Handle,
                                             Operation,
                                             Advertising_Data_Length,
                                             Advertising_Data);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_advertising_enable_ucfg(uint8_t Enable,
                                           uint8_t Num_Of_Sets,
                                           Advertising_Set_Parameters_t* Advertising_Set_Parameters)
{
    return GAP_set_extended_advertising_enable(Enable,
                                               Num_Of_Sets,
                                               Advertising_Set_Parameters);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void GAP_hci_le_advertising_set_terminated_evt_hndl_ucfg(uint8_t status,
                                                         uint8_t Advertising_Handle)
{
    GAP_hci_le_advertising_set_terminated_evt_hndl(status,
                                                   Advertising_Handle);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void GAP_slave_connection_complete_handler_ucfg(uint16_t connectionHandle)
{
    GAP_slave_connection_complete_handler(connectionHandle);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus GAP_enable_controller_privacy_ucfg(uint8_t* gapRole,
                                              uint8_t* numServiceRec)
{
    return GAP_enable_controller_privacy(gapRole,
                                         numServiceRec);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus GAP_check_and_set_role_ucfg(uint8_t* gapRole,
                                       uint8_t role)
{
    return GAP_check_and_set_role(gapRole,
                                  role);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus GAP_add_device_to_white_and_resolving_list_ucfg(uint8_t lists,
                                                           uint8_t addr_type,
                                                           uint8_t addr[6])
{
    return GAP_add_device_to_white_and_resolving_list_full(lists,
                                                           addr_type,
                                                           addr);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus GAP_clear_white_and_resolving_list_ucfg(uint8_t lists)
{
    return GAP_clear_white_and_resolving_list_full(lists);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_controller_random_address_ucfg(uint8_t random_address[6])
{
    return GAP_set_controller_random_address_extended(random_address);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_create_connection_ucfg(uint8_t* peer_address,
                                      uint8_t peer_address_type,
                                      uint8_t own_address_type,
                                      uint8_t initiator_filter_policy,
                                      uint8_t phys)
{
    return GAP_create_connection_ext(peer_address,
                                     peer_address_type,
                                     own_address_type,
                                     initiator_filter_policy,
                                     phys);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_scan_parameters_ucfg(uint8_t own_address_type,
                                        uint8_t phys)
{
    return GAP_set_scan_parameters_ext(own_address_type,
                                       phys);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_enable_disable_scan_ucfg(BOOL enable,
                                        uint8_t duplicate_filtering)
{
    return GAP_enable_disable_scan_ext(enable,
                                       duplicate_filtering);
}
#else
tBleStatus GAP_enable_disable_scan_ucfg(BOOL enable,
                                        uint8_t duplicate_filtering)
{
    return GAP_enable_disable_scan_legacy(enable,
                                          duplicate_filtering);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus GAP_discover_peer_name_ucfg(void)
{
    return GAP_discover_peer_name();
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
void GAP_master_connection_complete_handler_ucfg(uint8_t status,
                                                 uint16_t connectionHandle)
{
    GAP_master_connection_complete_handler(status,
                                           connectionHandle);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
BOOL GAP_parse_connectable_advertising_report_ucfg(uint8_t* adv_buf,
                                                   BOOL extended)
{
    return GAP_parse_connectable_advertising_report(adv_buf,
                                                    extended);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
BOOL GAP_parse_advertising_report_ucfg(uint8_t* adv_buf,
                                       BOOL extended)
{
    return GAP_parse_advertising_report(adv_buf,
                                        extended);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
void GAP_DiscProcTimeoutcb_ucfg(uint8_t timer_id)
{
    GAP_DiscProcTimeoutcb(timer_id);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_suspend_resume_active_advertising_sets_ucfg(BOOL resume)
{
    return GAP_suspend_resume_active_advertising_sets_extended(resume);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
uint32_t cte_csr_ucfg(void)
{
    return cte_csr();
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint8_t hci_le_check_own_address_type_max_value_ucfg(void)
{
    return hci_le_check_own_address_type_max_value();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
uint32_t data_length_extension_csr_ucfg(void)
{
    return data_length_extension_csr();
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
uint32_t pcl_csr_ucfg(void)
{
    return pcl_csr();
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
uint32_t phy_upd_csr_ucfg(void)
{
    return phy_upd_csr();
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint32_t PRIV_controller_privacy_csr_ucfg(void)
{
    return PRIV_controller_privacy_csr();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
uint32_t master_csr_ucfg(void)
{
    return master_csr();
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus LLC_test_check_cte_params_ucfg(void* params)
{
    return LLC_test_check_cte_params(params);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
void hci_le_advertising_report_event_cb_ucfg(uint8_t header_type,
                                             uint8_t* buff_p)
{
    hci_le_advertising_report_event_cb(header_type,
                                       buff_p);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void hci_le_read_local_p256_public_key_complete_event_cb_ucfg(uint8_t header_type,
                                                              uint8_t* buff_p)
{
    hci_le_read_local_p256_public_key_complete_event_cb(header_type,
                                                        buff_p);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void hci_le_generate_dhkey_complete_event_cb_ucfg(uint8_t header_type,
                                                  uint8_t* buff_p)
{
    hci_le_generate_dhkey_complete_event_cb(header_type,
                                            buff_p);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void hci_le_direct_advertising_report_event_cb_ucfg(uint8_t header_type,
                                                    uint8_t* buff_p)
{
    hci_le_direct_advertising_report_event_cb(header_type,
                                              buff_p);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void hci_le_extended_advertising_report_event_cb_ucfg(uint8_t header_type,
                                                      uint8_t* buff_p)
{
    hci_le_extended_advertising_report_event_cb(header_type,
                                                buff_p);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void hci_le_scan_timeout_event_cb_ucfg(uint8_t header_type,
                                       uint8_t* buff_p)
{
    hci_le_scan_timeout_event_cb(header_type,
                                 buff_p);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void hci_le_advertising_set_terminated_event_cb_ucfg(uint8_t header_type,
                                                     uint8_t* buff_p)
{
    hci_le_advertising_set_terminated_event_cb(header_type,
                                               buff_p);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) ||\
    (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
void hci_le_data_length_change_event_cb_ucfg(uint8_t header_type,
                                             uint8_t* buff_p)
{
    hci_le_data_length_change_event_cb(header_type,
                                       buff_p);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) ||\
          (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
void hci_le_phy_update_complete_event_cb_ucfg(uint8_t header_type,
                                              uint8_t* buff_p)
{
    hci_le_phy_update_complete_event_cb(header_type,
                                        buff_p);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_MASTER_ENABLED == 1)
void hci_le_periodic_advertising_sync_established_event_cb_ucfg(uint8_t header_type,
                                                                uint8_t* buff_p)
{
    hci_le_periodic_advertising_sync_established_event_cb(header_type,
                                                          buff_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_MASTER_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_MASTER_ENABLED == 1)
void hci_le_periodic_advertising_report_event_cb_ucfg(uint8_t header_type,
                                                      uint8_t* buff_p)
{
    hci_le_periodic_advertising_report_event_cb(header_type,
                                                buff_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_MASTER_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_MASTER_ENABLED == 1)
void hci_le_periodic_advertising_sync_lost_event_cb_ucfg(uint8_t header_type,
                                                         uint8_t* buff_p)
{
    hci_le_periodic_advertising_sync_lost_event_cb(header_type,
                                                   buff_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void hci_le_scan_request_received_event_cb_ucfg(uint8_t header_type,
                                                uint8_t* buff_p)
{
    hci_le_scan_request_received_event_cb(header_type,
                                          buff_p);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void hci_le_connectionless_iq_report_event_cb_ucfg(uint8_t header_type,
                                                   uint8_t* buff_p)
{
    hci_le_connectionless_iq_report_event_cb(header_type,
                                             buff_p);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void hci_le_connection_iq_report_event_cb_ucfg(uint8_t header_type,
                                               uint8_t* buff_p)
{
    hci_le_connection_iq_report_event_cb(header_type,
                                         buff_p);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void hci_le_cte_request_failed_event_cb_ucfg(uint8_t header_type,
                                             uint8_t* buff_p)
{
    hci_le_cte_request_failed_event_cb(header_type,
                                       buff_p);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void hci_le_periodic_advertising_sync_transfer_received_event_cb_ucfg(uint8_t header_type,
                                                                      uint8_t* buff_p)
{
    hci_le_periodic_advertising_sync_transfer_received_event_cb(header_type,
                                                                buff_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void hci_le_path_loss_threshold_event_cb_ucfg(uint8_t header_type,
                                              uint8_t* buff_p)
{
    hci_le_path_loss_threshold_event_cb(header_type,
                                        buff_p);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void hci_le_transmit_power_reporting_event_cb_ucfg(uint8_t header_type,
                                                   uint8_t* buff_p)
{
    hci_le_transmit_power_reporting_event_cb(header_type,
                                             buff_p);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void aci_l2cap_cfc_connection_event_cb_ucfg(uint8_t header_type,
                                            uint8_t* buff_p)
{
    aci_l2cap_cfc_connection_event_cb(header_type,
                                      buff_p);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void aci_l2cap_disconnection_complete_event_cb_ucfg(uint8_t header_type,
                                                    uint8_t* buff_p)
{
    aci_l2cap_disconnection_complete_event_cb(header_type,
                                              buff_p);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void aci_l2cap_flow_control_credit_event_cb_ucfg(uint8_t header_type,
                                                 uint8_t* buff_p)
{
    aci_l2cap_flow_control_credit_event_cb(header_type,
                                           buff_p);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void aci_l2cap_sdu_data_tx_event_cb_ucfg(uint8_t header_type,
                                         uint8_t* buff_p)
{
    aci_l2cap_sdu_data_tx_event_cb(header_type,
                                   buff_p);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void aci_l2cap_sdu_data_rx_event_cb_ucfg(uint8_t header_type,
                                         uint8_t* buff_p)
{
    aci_l2cap_sdu_data_rx_event_cb(header_type,
                                   buff_p);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus L2C_cos_process_cfc_mode_command_ucfg(void* params)
{
    return L2C_cos_process_cfc_mode_command(params);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
BOOL L2C_cos_is_pdu_cframe_cfc_command_opcode_ucfg(uint8_t opCode)
{
    return L2C_cos_is_pdu_cframe_cfc_command_opcode(opCode);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
uint32_t l2c_cos_csr_ucfg(void)
{
    return l2c_cos_csr();
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus L2C_cos_cfc_init_ucfg(void)
{
    return L2C_cos_cfc_init();
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void L2C_cos_process_pending_actions_tsk_ucfg(uint16_t task_idx)
{
    L2C_cos_process_pending_actions_tsk(task_idx);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void L2C_cos_reset_any_pending_channel_ucfg(uint16_t connection_handle)
{
    L2C_cos_reset_any_pending_channel(connection_handle);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void L2C_cos_physical_link_disconnection_hndl_ucfg(uint16_t connection_handle)
{
    L2C_cos_physical_link_disconnection_hndl(connection_handle);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void L2C_cos_perform_sdu_segmentation_tsk_ucfg(uint16_t task_idx)
{
    L2C_cos_perform_sdu_segmentation_tsk(task_idx);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void L2C_cos_transmit_pdu_packets_tsk_ucfg(uint16_t task_idx)
{
    L2C_cos_transmit_pdu_packets_tsk(task_idx);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
void L2C_cos_perform_pdu_reassembly_tsk_ucfg(uint16_t task_idx)
{
    L2C_cos_perform_pdu_reassembly_tsk(task_idx);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus L2C_cos_le_frame_data_hndl_ucfg(void* params)
{
    return L2C_cos_le_frame_data_hndl(params);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void aci_hal_scan_req_report_event_cb_ucfg(uint8_t header_type,
                                           uint8_t* buff_p)
{
    aci_hal_scan_req_report_event_cb(header_type,
                                     buff_p);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
tBleStatus LL_Read_RSSI_ucfg(int8_t* rssiVal,
                             uint16_t connHandle)
{
    return LL_Read_RSSI(rssiVal,
                        connHandle);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
BOOL LL_phy_upd_pending_ucfg(uint8_t conn_idx)
{
    return LL_phy_upd_pending(conn_idx);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LLC_conn_process_rx_cte_ucfg(void* params,
                                  uint8_t cte_type)
{
    LLC_conn_process_rx_cte(params,
                            cte_type);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
void LL_cpe_init_length_update_ucfg(void)
{
    LL_cpe_init_length_update();
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
void LL_cpe_init_phy_update_ucfg(void)
{
    LL_cpe_init_phy_update();
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LL_cpe_init_cte_ucfg(void)
{
    LL_cpe_init_cte();
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_cpe_init_past_ucfg(void)
{
    LL_cpe_init_past();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void LL_cpe_init_pcl_ucfg(void)
{
    LL_cpe_init_pcl();
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
void LL_conn_upd_max_tx_time_coded_ucfg(void* params)
{
    LL_conn_upd_max_tx_time_coded(params);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
void LL_conn_upd_data_length_change_event_ucfg(void* params)
{
    LL_conn_upd_data_length_change_event(params);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LLC_conn_init_cte_ctxt_ucfg(uint8_t conn_idx)
{
    LLC_conn_init_cte_ctxt(conn_idx);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
BOOL LLC_cte_request_procedure_ucfg(void* params)
{
    return LLC_cte_request_procedure(params);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LLC_connection_cte_response_pause_resume_ucfg(uint8_t conn_idx,
                                                   uint8_t tx_phy)
{
    LLC_connection_cte_response_pause_resume(conn_idx,
                                             tx_phy);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LLC_connection_cte_response_disable_ucfg(uint8_t conn_idx,
                                              uint8_t taskslot_no)
{
    LLC_connection_cte_response_disable(conn_idx,
                                        taskslot_no);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_past_reload_txctrl_packet_ucfg(uint8_t conn_idx,
                                       uint8_t* pdu_ptr)
{
    LL_past_reload_txctrl_packet(conn_idx,
                                 pdu_ptr);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_past_initialize_connect_context_ucfg(uint8_t conn_idx)
{
    LL_past_initialize_connect_context(conn_idx);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_past_default_params_ucfg(uint8_t conn_idx)
{
    LL_past_default_params(conn_idx);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void LLC_conn_init_pcl_ctxt_ucfg(uint8_t conn_idx)
{
    LLC_conn_init_pcl_ctxt(conn_idx);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void LLC_pcl_hal_cntxt_init_ucfg(uintptr_t pcl_cntxt_p)
{
    LLC_pcl_hal_cntxt_init(pcl_cntxt_p);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void LLC_pcl_incr_rx_packets_ucfg(uint8_t conn_idx)
{
    LLC_pcl_incr_rx_packets(conn_idx);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void LLC_pcl_update_avg_rssi_ucfg(void* params)
{
    LLC_pcl_update_avg_rssi(params);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void LLC_pcl_set_radio_tx_power_conn_start_ucfg(uint8_t conn_idx)
{
    LLC_pcl_set_radio_tx_power_conn_start(conn_idx);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
void LLC_pcl_set_radio_tx_power_and_eval_indication_ucfg(uint8_t conn_idx,
                                                         BOOL send_ind,
                                                         int8_t ind_delta,
                                                         BOOL change_txpower)
{
    LLC_pcl_set_radio_tx_power_and_eval_indication(conn_idx,
                                                   send_ind,
                                                   ind_delta,
                                                   change_txpower);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
BOOL LLC_pcl_offline_processing_ucfg(uint8_t conn_idx)
{
    return LLC_pcl_offline_processing(conn_idx);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
uint8_t LLC_pcl_get_number_of_phys_ucfg(void)
{
    return LLC_pcl_get_number_of_phys();
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
    (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
void LL_phy_upd_compute_data_PDU_length_params_ucfg(void* params)
{
    LL_phy_upd_compute_data_PDU_length_params(params);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
          (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus LL_phy_update_init_ucfg(void)
{
    return LL_phy_update_init();
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus LL_phy_update_init_per_st_data_ucfg(uint8_t conn_idx)
{
    return LL_phy_update_init_per_st_data(conn_idx);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void LLC_blueapi_cte_ucfg(void* params)
{
    LLC_blueapi_cte(params);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void LLC_connless_process_rx_cte_ucfg(BOOL iq_samples_ready,
                                      void* params,
                                      uint8_t iq_samples_number,
                                      uint8_t rx_cte_type,
                                      uint8_t channel)
{
    LLC_connless_process_rx_cte(iq_samples_ready,
                                params,
                                iq_samples_number,
                                rx_cte_type,
                                channel);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
BOOL LLC_check_iq_samples_ready_ucfg(uint8_t* iq_samples_number,
                                     uint8_t* channel,
                                     uint8_t taskslot_no)
{
    return LLC_check_iq_samples_ready(iq_samples_number,
                                      channel,
                                      taskslot_no);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LLC_test_process_rx_cte_ucfg(void* params)
{
    LLC_test_process_rx_cte(params);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LLC_test_set_cte_ucfg(void* params)
{
    LLC_test_set_cte(params);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus LL_eadv_max_supported_data_check_ucfg(uint16_t Data_Length,
                                                 void* linkpointer)
{
    return LL_eadv_max_supported_data_check(Data_Length,
                                            linkpointer);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void LL_eadv_start_extended_ucfg(void* pointer)
{
    LL_eadv_start_extended(pointer);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
uint8_t ext_adv_scan_enabled_ucfg(void)
{
    return ext_adv_scan_enabled();
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus LL_Clear_Advertising_Sets_ucfg(void)
{
    return LL_Clear_Advertising_Sets();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus LL_Remove_Advertising_Set_ucfg(uint16_t Advertising_Handle)
{
    return LL_Remove_Advertising_Set(Advertising_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
BOOL LL_extended_adv_add_enable_sync_info_auxind_pdu_ucfg(void* pointer)
{
    return LL_extended_adv_add_enable_sync_info_auxind_pdu(pointer);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void LL_escan_ScanStopCancel_ucfg(void)
{
    LL_escan_ScanStopCancel();
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus LL_Set_Extended_Scan_Enable_ucfg(void* pExtScanEnable_dummy)
{
    return LL_Set_Extended_Scan_Enable(pExtScanEnable_dummy);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void LL_escan_ScanStart_ucfg(void)
{
    LL_escan_ScanStart();
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void LL_escan_push_hci_le_extended_advertising_report_event_ucfg(void* pointer,
                                                                 uint8_t len,
                                                                 uint8_t offset,
                                                                 uint8_t event_type)
{
    LL_escan_push_hci_le_extended_advertising_report_event(pointer,
                                                           len,
                                                           offset,
                                                           event_type);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void LL_escan_extended_adv_receive_process_ucfg(void* linkpointer,
                                                uint8_t phyindex,
                                                BOOL anonymous_flag,
                                                BOOL receive_address_present_flag,
                                                uint32_t* received_receive_address)
{
    LL_escan_extended_adv_receive_process(linkpointer,
                                          phyindex,
                                          anonymous_flag,
                                          receive_address_present_flag,
                                          received_receive_address);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
BOOL LL_escan_EauxIsr_ucfg(void* pointer)
{
    return LL_escan_EauxIsr(pointer);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void LL_Set_Extented_conn_Params_ucfg(uint8_t phy_index,
                                      uint8_t index,
                                      Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters)
{
    LL_Set_Extented_conn_Params(phy_index,
                                index,
                                Extended_Create_Connection_Parameters);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void LL_periodic_event_terminate_decision_routine_ucfg(void* pointer)
{
    LL_periodic_event_terminate_decision_routine(pointer);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_periodicadv_init_ucfg(uint8_t number_of_periodicadv_contexts,
                              void* LL_periodicadv_context_periodic_per_array)
{
    LL_periodicadv_init(number_of_periodicadv_contexts,
                        LL_periodicadv_context_periodic_per_array);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_periodicadv_periodicenable_ucfg(void* periodic_per_pointer)
{
    LL_periodicadv_periodicenable(periodic_per_pointer);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
uint8_t periodic_csr_ucfg(void)
{
    return periodic_csr();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus LL_LE_Set_periodic_adv_data_ptr_function_ucfg(uint16_t advertising_handle,
                                                         uint16_t data_length,
                                                         uint8_t* data)
{
    return LL_LE_Set_periodic_adv_data_ptr_function(advertising_handle,
                                                    data_length,
                                                    data);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
BOOL LL_periodicadv_update_sync_info_field_ucfg(void* periodic_context_ptr,
                                                uint8_t* packet,
                                                uint32_t myanchor)
{
    return LL_periodicadv_update_sync_info_field(periodic_context_ptr,
                                                 packet,
                                                 myanchor);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
uint8_t LL_periodicadv_prepare_periodic_advertising_payload_ucfg(void* pointer,
                                                                 uint8_t packet_type,
                                                                 uint8_t extended_flags_and_data_indication,
                                                                 uint8_t* packet)
{
    return LL_periodicadv_prepare_periodic_advertising_payload(pointer,
                                                               packet_type,
                                                               extended_flags_and_data_indication,
                                                               packet);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_periodicadv_init_periodic_advertising_context_per_ucfg(void* periodic_per_pointer_dummy)
{
    LL_periodicadv_init_periodic_advertising_context_per(periodic_per_pointer_dummy);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void LL_padv_adjust_cte_count_with_interval_ucfg(void* pointer,
                                                 BOOL no_data_length_set,
                                                 uint16_t data_length)
{
    LL_padv_adjust_cte_count_with_interval(pointer,
                                           no_data_length_set,
                                           data_length);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void LL_pscan_restore_pa_list_ucfg(void* pointer)
{
    LL_pscan_restore_pa_list(pointer);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_periodicscan_deploy_or_connect_periodic_ucfg(void* sync_info_field,
                                                     uint32_t* address_with_SID,
                                                     uint8_t phy,
                                                     uint8_t tx_power,
                                                     BOOL past_mode,
                                                     uint32_t connect_anchor,
                                                     uint8_t conn_idx,
                                                     void* periodicperpointer_dummy,
                                                     uint32_t* privateaddress)
{
    LL_periodicscan_deploy_or_connect_periodic(sync_info_field,
                                               address_with_SID,
                                               phy,
                                               tx_power,
                                               past_mode,
                                               connect_anchor,
                                               conn_idx,
                                               periodicperpointer_dummy,
                                               privateaddress);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
BOOL LL_periodicscan_check_received_txaddress_true_on_accept_ucfg(uint32_t* received_transmit_address)
{
    return LL_periodicscan_check_received_txaddress_true_on_accept(received_transmit_address);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void LL_periodicscan_init_ucfg(uint8_t number_of_periodic_contexts,
                               void* periodic_context_complete_p,
                               void* pointer,
                               uint8_t PeriodicListSizeLog2,
                               void* PeriodicIDList,
                               void* cpf_past_procedure_overall_context,
                               uint8_t num_connect_link,
                               void* cpf_past_procedure_connect_context_per)
{
    LL_periodicscan_init(number_of_periodic_contexts,
                         periodic_context_complete_p,
                         pointer,
                         PeriodicListSizeLog2,
                         PeriodicIDList,
                         cpf_past_procedure_overall_context,
                         num_connect_link,
                         cpf_past_procedure_connect_context_per);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
BOOL LL_pscan_validate_CTE_type_ucfg(void* params,
                                     uint8_t CTE_type)
{
    return LL_pscan_validate_CTE_type(params,
                                      CTE_type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
BOOL LL_periodicscan_cancel_slot_cte_ucfg(void* pointer_complete,
                                          void* pointer_per)
{
    return LL_periodicscan_cancel_slot_cte(pointer_complete,
                                           pointer_per);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void LL_priv_vOwnPrivateAddress_ucfg(uint32_t* Own,
                                     uint32_t* Peer,
                                     uint8_t is_ISR)
{
    LL_priv_vOwnPrivateAddress(Own,
                               Peer,
                               is_ISR);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void LL_priv_u8OfflineProcessing_ucfg(uint16_t task_idx)
{
    LL_priv_u8OfflineProcessing(task_idx);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void LL_priv_vPeerPrivateAddress_ucfg(uint32_t* Peer,
                                      uint8_t is_ISR)
{
    LL_priv_vPeerPrivateAddress(Peer,
                                is_ISR);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint8_t LL_priv_u32ProcessAdvPacket_ucfg(uint32_t* ReceivedTransmitAddress,
                                         uint8_t PduType,
                                         uint32_t* PeerIDAddress,
                                         uint8_t AdvertisingEventproperties,
                                         uint8_t filterPolicy,
                                         uint32_t* peer_addr,
                                         uint16_t advertisinghandle)
{
    return LL_priv_u32ProcessAdvPacket(ReceivedTransmitAddress,
                                       PduType,
                                       PeerIDAddress,
                                       AdvertisingEventproperties,
                                       filterPolicy,
                                       peer_addr,
                                       advertisinghandle);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint8_t LL_priv_u32ProcessScanPacketTx_ucfg(uint32_t* ReceivedTransmitAddress,
                                            uint32_t* PeerIDaddress,
                                            uint8_t isScanner,
                                            uint8_t* initPeerAddr,
                                            uint8_t initPeerAddrType,
                                            uint8_t LocalFilterPolicy,
                                            uint8_t resolvedirect,
                                            uint8_t* DatabaseEntry)
{
    return LL_priv_u32ProcessScanPacketTx(ReceivedTransmitAddress,
                                          PeerIDaddress,
                                          isScanner,
                                          initPeerAddr,
                                          initPeerAddrType,
                                          LocalFilterPolicy,
                                          resolvedirect,
                                          DatabaseEntry);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint8_t LL_priv_u32ProcessScanPacketRx_ucfg(uint32_t* ReceivedReceiveAddress,
                                            uint8_t LocalFilterPolicy,
                                            uint32_t* own_addr_used,
                                            uint8_t PointerToDataBase,
                                            uint8_t resolvedirect)
{
    return LL_priv_u32ProcessScanPacketRx(ReceivedReceiveAddress,
                                          LocalFilterPolicy,
                                          own_addr_used,
                                          PointerToDataBase,
                                          resolvedirect);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void LL_priv_SynchPeerIDList_And_WhiteIDList_ucfg(void)
{
    LL_priv_SynchPeerIDList_And_WhiteIDList();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void LL_priv_Init_ResolvedPart_ucfg(BOOL general_init)
{
    LL_priv_Init_ResolvedPart(general_init);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
BOOL Data_Len_Update_Offline_Processing_ucfg(void* params,
                                             uint32_t ctrl_flds)
{
    return Data_Len_Update_Offline_Processing(params,
                                              ctrl_flds);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
tBleStatus ll_write_supported_data_ucfg(uint16_t Supported_Max_Tx_Octets,
                                        uint16_t Supported_Max_Tx_Time,
                                        uint16_t Supported_Max_Rx_Octets,
                                        uint16_t Supported_Max_Rx_Time)
{
    return ll_write_supported_data(Supported_Max_Tx_Octets,
                                   Supported_Max_Tx_Time,
                                   Supported_Max_Rx_Octets,
                                   Supported_Max_Rx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
void LL_Get_Supported_States_ucfg(uint8_t states[8])
{
    LL_Get_Supported_States(states);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus LL_Start_Encryption_ucfg(uint16_t connHandle,
                                    uint8_t* randNum,
                                    uint8_t* ediv,
                                    uint8_t* ltk)
{
    return LL_Start_Encryption(connHandle,
                               randNum,
                               ediv,
                               ltk);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void aci_gap_numeric_comparison_value_event_cb_ucfg(uint8_t header_type,
                                                    uint8_t* buff_p)
{
    aci_gap_numeric_comparison_value_event_cb(header_type,
                                              buff_p);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void aci_gap_keypress_notification_event_cb_ucfg(uint8_t header_type,
                                                 uint8_t* buff_p)
{
    aci_gap_keypress_notification_event_cb(header_type,
                                           buff_p);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus smp_MI_Start_Encryption_ucfg(void* params)
{
    return smp_MI_Start_Encryption(params);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
void smp_Execute_Actions_wrt_Current_State_MI_excerpt_ucfg(void* params)
{
    smp_Execute_Actions_wrt_Current_State_MI_excerpt(params);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus smp_Process_Rx_Packet_wrt_Current_State_MI_excerpt_ucfg(void* params)
{
    return smp_Process_Rx_Packet_wrt_Current_State_MI_excerpt(params);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus smp_sc_MI_PairingResponse_Receive_sc_excerpt_ucfg(void* params)
{
    return smp_sc_MI_PairingResponse_Receive_sc_excerpt(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_MI_Pairing_Phase_2AS1_Start_sc_excerpt_ucfg(void* params)
{
    smp_sc_MI_Pairing_Phase_2AS1_Start_sc_excerpt(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_SR_Pairing_Phase_2AS1_Start_sc_excerpt_ucfg(void* params)
{
    smp_sc_SR_Pairing_Phase_2AS1_Start_sc_excerpt(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_MI_PairingConfirm_Send_sc_excerpt_ucfg(void* params)
{
    smp_sc_MI_PairingConfirm_Send_sc_excerpt(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus smp_sc_MI_PairingRandom_Receive_sc_excerpt1_ucfg(void* params)
{
    return smp_sc_MI_PairingRandom_Receive_sc_excerpt1(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_MI_PairingRandom_Receive_sc_excerpt2_ucfg(void* params)
{
    smp_sc_MI_PairingRandom_Receive_sc_excerpt2(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_SR_PairingConfirm_Receive_sc_excerpt_ucfg(void* params)
{
    smp_sc_SR_PairingConfirm_Receive_sc_excerpt(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_SR_PairingRandom_Receive_sc_excerpt_ucfg(void* params)
{
    smp_sc_SR_PairingRandom_Receive_sc_excerpt(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
BOOL smp_execute_actions_wrt_state_sc_phase1to2_ucfg(void* params)
{
    return smp_execute_actions_wrt_state_sc_phase1to2(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_execute_actions_wrt_state_sc_phase2as2_ucfg(void* params)
{
    smp_execute_actions_wrt_state_sc_phase2as2(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus smp_Process_Rx_Packet_wrt_Current_State_sc_excerpt_ucfg(void* params)
{
    return smp_Process_Rx_Packet_wrt_Current_State_sc_excerpt(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus smp_Process_Rx_Packet_Exception_Cases_sc_excerpt_ucfg(void* params)
{
    return smp_Process_Rx_Packet_Exception_Cases_sc_excerpt(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONTROLLER_MASTER_ENABLED == 1)
void smp_execute_actions_wrt_state_sc_phase2as2_mi_ucfg(void* params)
{
    smp_execute_actions_wrt_state_sc_phase2as2_mi(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONTROLLER_MASTER_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void SMP_process_sc_ecc_pk_generation_tsk_ucfg(uint16_t task_idx)
{
    SMP_process_sc_ecc_pk_generation_tsk(task_idx);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_init_ucfg(BOOL useDebugKey)
{
    smp_sc_init(useDebugKey);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus smp_sc_continue_on_exclusive_sc_pairing_ucfg(void* params)
{
    return smp_sc_continue_on_exclusive_sc_pairing(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus smp_sc_generate_new_local_oob_data_ucfg(void)
{
    return smp_sc_generate_new_local_oob_data();
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_update_statistics_on_pairing_complete_ucfg(void* params)
{
    smp_sc_update_statistics_on_pairing_complete(params);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
uint32_t secure_connections_csr_ucfg(void)
{
    return secure_connections_csr();
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_hci_le_read_local_p256_public_key_complete_evt_hndl_ucfg(uint8_t status,
                                                                     uint8_t local_p256_public_key[64])
{
    smp_sc_hci_le_read_local_p256_public_key_complete_evt_hndl(status,
                                                               local_p256_public_key);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
void smp_sc_hci_le_generate_dhkey_complete_evt_hndl_ucfg(uint8_t status,
                                                         uint8_t DHKey[32])
{
    smp_sc_hci_le_generate_dhkey_complete_evt_hndl(status,
                                                   DHKey);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */


/*
* *****************************************************************************
*                      BLE Stack API functions
* *****************************************************************************
*/

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_gap_start_connection_update(uint16_t Connection_Handle,
                                           uint16_t Conn_Interval_Min,
                                           uint16_t Conn_Interval_Max,
                                           uint16_t Conn_Latency,
                                           uint16_t Supervision_Timeout,
                                           uint16_t Minimum_CE_Length,
                                           uint16_t Maximum_CE_Length)
{
    return aci_gap_start_connection_update_api(Connection_Handle,
                                               Conn_Interval_Min,
                                               Conn_Interval_Max,
                                               Conn_Latency,
                                               Supervision_Timeout,
                                               Minimum_CE_Length,
                                               Maximum_CE_Length);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_gap_send_pairing_req(uint16_t Connection_Handle,
                                    uint8_t Force_Rebond)
{
    return aci_gap_send_pairing_req_api(Connection_Handle,
                                        Force_Rebond);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus aci_gap_numeric_comparison_value_confirm_yesno(uint16_t Connection_Handle,
                                                          uint8_t Confirm_Yes_No)
{
    return aci_gap_numeric_comparison_value_confirm_yesno_api(Connection_Handle,
                                                              Confirm_Yes_No);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus aci_gap_passkey_input(uint16_t Connection_Handle,
                                 uint8_t Input_Type)
{
    return aci_gap_passkey_input_api(Connection_Handle,
                                     Input_Type);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_gap_set_scan_configuration(uint8_t duplicate_filtering,
                                          uint8_t scanning_filter_policy,
                                          uint8_t phy,
                                          uint8_t scan_type,
                                          uint16_t scan_interval,
                                          uint16_t scan_window)
{
    return aci_gap_set_scan_configuration_api(duplicate_filtering,
                                              scanning_filter_policy,
                                              phy,
                                              scan_type,
                                              scan_interval,
                                              scan_window);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_gap_set_connection_configuration(uint8_t phy,
                                                uint16_t conn_interval_min,
                                                uint16_t conn_interval_max,
                                                uint16_t conn_latency,
                                                uint16_t supervision_timeout,
                                                uint16_t minimum_ce_length,
                                                uint16_t maximum_ce_length)
{
    return aci_gap_set_connection_configuration_api(phy,
                                                    conn_interval_min,
                                                    conn_interval_max,
                                                    conn_latency,
                                                    supervision_timeout,
                                                    minimum_ce_length,
                                                    maximum_ce_length);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_gap_create_connection(uint8_t Initiating_PHY,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6])
{
    return aci_gap_create_connection_api(Initiating_PHY,
                                         Peer_Address_Type,
                                         Peer_Address);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_gap_start_procedure(uint8_t procedure_code,
                                   uint8_t phys,
                                   uint16_t duration,
                                   uint16_t period)
{
    return aci_gap_start_procedure_api(procedure_code,
                                       phys,
                                       duration,
                                       period);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_gap_discover_name(uint8_t PHYs,
                                 uint8_t Peer_Address_Type,
                                 uint8_t Peer_Address[6])
{
    return aci_gap_discover_name_api(PHYs,
                                     Peer_Address_Type,
                                     Peer_Address);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_gap_terminate_proc(uint8_t Procedure_Code)
{
    return aci_gap_terminate_proc_api(Procedure_Code);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_periodic_advertising_configuration(uint8_t Advertising_Handle,
                                                          uint16_t Periodic_Advertising_Interval_Min,
                                                          uint16_t Periodic_Advertising_Interval_Max,
                                                          uint16_t Periodic_Advertising_Properties)
{
    return aci_gap_set_periodic_advertising_configuration_api(Advertising_Handle,
                                                              Periodic_Advertising_Interval_Min,
                                                              Periodic_Advertising_Interval_Max,
                                                              Periodic_Advertising_Properties);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_periodic_advertising_enable(uint8_t Enable,
                                                   uint8_t Advertising_Handle)
{
    return aci_gap_set_periodic_advertising_enable_api(Enable,
                                                       Advertising_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_periodic_advertising_data(uint8_t Advertising_Handle,
                                                 uint8_t Advertising_Data_Length,
                                                 uint8_t* Advertising_Data)
{
    return aci_gap_set_periodic_advertising_data_api(Advertising_Handle,
                                                     Advertising_Data_Length,
                                                     Advertising_Data);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_create_sync(uint8_t Options,
                                                    uint8_t Advertising_SID,
                                                    uint8_t Advertising_Address_Type,
                                                    uint8_t Advertiser_Address[6],
                                                    uint16_t Skip,
                                                    uint16_t Sync_Timeout,
                                                    uint8_t Sync_CTE_Type)
{
    return aci_gap_periodic_advertising_create_sync_api(Options,
                                                        Advertising_SID,
                                                        Advertising_Address_Type,
                                                        Advertiser_Address,
                                                        Skip,
                                                        Sync_Timeout,
                                                        Sync_CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_create_sync_cancel(void)
{
    return aci_gap_periodic_advertising_create_sync_cancel_api();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_terminate_sync(uint16_t Sync_Handle)
{
    return aci_gap_periodic_advertising_terminate_sync_api(Sync_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_periodic_advertising_receive_enable(uint16_t Sync_Handle,
                                                           uint8_t Enable)
{
    return aci_gap_set_periodic_advertising_receive_enable_api(Sync_Handle,
                                                               Enable);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_add_device_to_periodic_advertiser_list(uint8_t Advertiser_Address_Type,
                                                          uint8_t Advertiser_Address[6],
                                                          uint8_t Advertising_SID)
{
    return aci_gap_add_device_to_periodic_advertiser_list_api(Advertiser_Address_Type,
                                                              Advertiser_Address,
                                                              Advertising_SID);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_remove_device_from_periodic_advertising_list(uint8_t Advertiser_Address_Type,
                                                                uint8_t Advertiser_Address[6],
                                                                uint8_t Advertising_SID)
{
    return aci_gap_remove_device_from_periodic_advertising_list_api(Advertiser_Address_Type,
                                                                    Advertiser_Address,
                                                                    Advertising_SID);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_clear_periodic_advertiser_list(void)
{
    return aci_gap_clear_periodic_advertiser_list_api();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_read_periodic_advertiser_list_size(uint8_t* Periodic_Advertiser_List_Size)
{
    return aci_gap_read_periodic_advertiser_list_size_api(Periodic_Advertiser_List_Size);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                      uint16_t Service_Data,
                                                      uint16_t Sync_Handle)
{
    return aci_gap_periodic_advertising_sync_transfer_api(Connection_Handle,
                                                          Service_Data,
                                                          Sync_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_set_info_transfer(uint16_t Connection_Handle,
                                                          uint16_t Service_Data,
                                                          uint8_t Advertising_Handle)
{
    return aci_gap_periodic_advertising_set_info_transfer_api(Connection_Handle,
                                                              Service_Data,
                                                              Advertising_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                     uint8_t Mode,
                                                                     uint16_t Skip,
                                                                     uint16_t Sync_Timeout,
                                                                     uint8_t CTE_Type)
{
    return aci_gap_set_periodic_advertising_sync_transfer_parameters_api(Connection_Handle,
                                                                         Mode,
                                                                         Skip,
                                                                         Sync_Timeout,
                                                                         CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                             uint16_t Skip,
                                                                             uint16_t Sync_Timeout,
                                                                             uint8_t CTE_Type)
{
    return aci_gap_set_default_periodic_advertising_sync_transfer_parameters_api(Mode,
                                                                                 Skip,
                                                                                 Sync_Timeout,
                                                                                 CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus aci_gap_remove_advertising_set(uint8_t Advertising_Handle)
{
    return aci_gap_remove_advertising_set_api(Advertising_Handle);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus aci_gap_clear_advertising_sets(void)
{
    return aci_gap_clear_advertising_sets_api();
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
tBleStatus aci_hal_set_le_power_control(uint8_t Enable,
                                        uint8_t PHY,
                                        int8_t RSSI_Target,
                                        uint8_t RSSI_Hysteresis,
                                        int8_t Initial_TX_Power,
                                        uint8_t RSSI_Filtering_Coefficient)
{
    return aci_hal_set_le_power_control_api(Enable,
                                            PHY,
                                            RSSI_Target,
                                            RSSI_Hysteresis,
                                            Initial_TX_Power,
                                            RSSI_Filtering_Coefficient);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus aci_l2cap_connection_parameter_update_resp(uint16_t Connection_Handle,
                                                      uint16_t Conn_Interval_Min,
                                                      uint16_t Conn_Interval_Max,
                                                      uint16_t Slave_latency,
                                                      uint16_t Timeout_Multiplier,
                                                      uint16_t Minimum_CE_Length,
                                                      uint16_t Maximum_CE_Length,
                                                      uint8_t Identifier,
                                                      uint8_t Accept)
{
    return aci_l2cap_connection_parameter_update_resp_api(Connection_Handle,
                                                          Conn_Interval_Min,
                                                          Conn_Interval_Max,
                                                          Slave_latency,
                                                          Timeout_Multiplier,
                                                          Minimum_CE_Length,
                                                          Maximum_CE_Length,
                                                          Identifier,
                                                          Accept);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus aci_l2cap_cfc_connection_req(uint16_t Connection_Handle,
                                        uint16_t SPSM,
                                        uint16_t CID,
                                        uint16_t MTU,
                                        uint16_t MPS,
                                        uint8_t CFC_Policy,
                                        uint16_t RX_SDU_Buffer_Size,
                                        void* RX_SDU_Buffer)
{
    return aci_l2cap_cfc_connection_req_api(Connection_Handle,
                                            SPSM,
                                            CID,
                                            MTU,
                                            MPS,
                                            CFC_Policy,
                                            RX_SDU_Buffer_Size,
                                            RX_SDU_Buffer);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus aci_l2cap_cfc_connection_resp(uint16_t Connection_Handle,
                                         uint8_t Identifier,
                                         uint16_t CID,
                                         uint16_t MTU,
                                         uint16_t MPS,
                                         uint16_t Result,
                                         uint8_t CFC_Policy,
                                         uint16_t RX_SDU_Buffer_Size,
                                         void* RX_SDU_Buffer)
{
    return aci_l2cap_cfc_connection_resp_api(Connection_Handle,
                                             Identifier,
                                             CID,
                                             MTU,
                                             MPS,
                                             Result,
                                             CFC_Policy,
                                             RX_SDU_Buffer_Size,
                                             RX_SDU_Buffer);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus aci_l2cap_send_flow_control_credits(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t RX_Credits,
                                               uint8_t CFC_Policy,
                                               uint16_t* RX_Credit_Balance)
{
    return aci_l2cap_send_flow_control_credits_api(Connection_Handle,
                                                   CID,
                                                   RX_Credits,
                                                   CFC_Policy,
                                                   RX_Credit_Balance);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus aci_l2cap_disconnect(uint16_t Connection_Handle,
                                uint16_t CID)
{
    return aci_l2cap_disconnect_api(Connection_Handle,
                                    CID);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus aci_l2cap_transmit_sdu_data(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       uint16_t SDU_Length,
                                       uint8_t* SDU_Data)
{
    return aci_l2cap_transmit_sdu_data_api(Connection_Handle,
                                           CID,
                                           SDU_Length,
                                           SDU_Data);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (L2CAP_COS_ENABLED == 1)
tBleStatus aci_l2cap_extract_sdu_data(uint16_t Connection_Handle,
                                      uint16_t CID,
                                      uint16_t SDU_Data_Buffer_Size,
                                      void* SDU_Data_Buffer,
                                      uint16_t* SDU_Length)
{
    return aci_l2cap_extract_sdu_data_api(Connection_Handle,
                                          CID,
                                          SDU_Data_Buffer_Size,
                                          SDU_Data_Buffer,
                                          SDU_Length);
}
#endif /* (L2CAP_COS_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1) ||\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_host_channel_classification(uint8_t LE_Channel_Map[5])
{
    return hci_le_set_host_channel_classification_api(LE_Channel_Map);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) ||\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_set_connectionless_cte_transmit_parameters(uint8_t Advertising_Handle,
                                                             uint8_t CTE_Length,
                                                             uint8_t CTE_Type,
                                                             uint8_t CTE_Count,
                                                             uint8_t Switching_Pattern_Length,
                                                             uint8_t* Antenna_IDs)
{
    return hci_le_set_connectionless_cte_transmit_parameters_api(Advertising_Handle,
                                                                 CTE_Length,
                                                                 CTE_Type,
                                                                 CTE_Count,
                                                                 Switching_Pattern_Length,
                                                                 Antenna_IDs);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_set_connectionless_cte_transmit_enable(uint8_t Advertising_Handle,
                                                         uint8_t CTE_Enable)
{
    return hci_le_set_connectionless_cte_transmit_enable_api(Advertising_Handle,
                                                             CTE_Enable);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_set_connectionless_iq_sampling_enable(uint16_t Sync_Handle,
                                                        uint8_t Sampling_Enable,
                                                        uint8_t Slot_Durations,
                                                        uint8_t Max_Sampled_CTEs,
                                                        uint8_t Switching_Pattern_Length,
                                                        uint8_t* Antenna_IDs)
{
    return hci_le_set_connectionless_iq_sampling_enable_api(Sync_Handle,
                                                            Sampling_Enable,
                                                            Slot_Durations,
                                                            Max_Sampled_CTEs,
                                                            Switching_Pattern_Length,
                                                            Antenna_IDs);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_set_connection_cte_receive_parameters(uint16_t Connection_Handle,
                                                        uint8_t Sampling_Enable,
                                                        uint8_t Slot_Durations,
                                                        uint8_t Switching_Pattern_Length,
                                                        uint8_t* Antenna_IDs)
{
    return hci_le_set_connection_cte_receive_parameters_api(Connection_Handle,
                                                            Sampling_Enable,
                                                            Slot_Durations,
                                                            Switching_Pattern_Length,
                                                            Antenna_IDs);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_set_connection_cte_transmit_parameters(uint16_t Connection_Handle,
                                                         uint8_t CTE_Type,
                                                         uint8_t Switching_Pattern_Length,
                                                         uint8_t* Antenna_IDs)
{
    return hci_le_set_connection_cte_transmit_parameters_api(Connection_Handle,
                                                             CTE_Type,
                                                             Switching_Pattern_Length,
                                                             Antenna_IDs);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_connection_cte_request_enable(uint16_t Connection_Handle,
                                                uint8_t Enable,
                                                uint16_t CTE_Request_Interval,
                                                uint8_t Requested_CTE_Length,
                                                uint8_t Requested_CTE_Type)
{
    return hci_le_connection_cte_request_enable_api(Connection_Handle,
                                                    Enable,
                                                    CTE_Request_Interval,
                                                    Requested_CTE_Length,
                                                    Requested_CTE_Type);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_connection_cte_response_enable(uint16_t Connection_Handle,
                                                 uint8_t Enable)
{
    return hci_le_connection_cte_response_enable_api(Connection_Handle,
                                                     Enable);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_read_antenna_information(uint8_t* Supported_Switching_Sampling_Rates,
                                           uint8_t* Num_Antennae,
                                           uint8_t* Max_Switching_Pattern_Length,
                                           uint8_t* Max_CTE_Length)
{
    return hci_le_read_antenna_information_api(Supported_Switching_Sampling_Rates,
                                               Num_Antennae,
                                               Max_Switching_Pattern_Length,
                                               Max_CTE_Length);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus hci_le_start_encryption(uint16_t Connection_Handle,
                                   uint8_t Random_Number[8],
                                   uint16_t Encrypted_Diversifier,
                                   uint8_t Long_Term_Key[16])
{
    return hci_le_start_encryption_api(Connection_Handle,
                                       Random_Number,
                                       Encrypted_Diversifier,
                                       Long_Term_Key);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus hci_le_read_local_p256_public_key(void)
{
    return hci_le_read_local_p256_public_key_api();
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (SECURE_CONNECTIONS_ENABLED == 1)
tBleStatus hci_le_generate_dhkey(uint8_t Remote_P256_Public_Key[64])
{
    return hci_le_generate_dhkey_api(Remote_P256_Public_Key);
}
#endif /* (SECURE_CONNECTIONS_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_advertising_parameters(uint8_t Advertising_Handle,
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
                                                      int8_t* Selected_Tx_Power)
{
    return hci_le_set_extended_advertising_parameters_api(Advertising_Handle,
                                                          Advertising_Event_Properties,
                                                          Primary_Advertising_Interval_Min,
                                                          Primary_Advertising_Interval_Max,
                                                          Primary_Advertising_Channel_Map,
                                                          Own_Address_Type,
                                                          Peer_Address_Type,
                                                          Peer_Address,
                                                          Advertising_Filter_Policy,
                                                          Advertising_Tx_Power,
                                                          Primary_Advertising_PHY,
                                                          Secondary_Advertising_Max_Skip,
                                                          Secondary_Advertising_PHY,
                                                          Advertising_SID,
                                                          Scan_Request_Notification_Enable,
                                                          Selected_Tx_Power);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_advertising_set_random_address(uint8_t Advertising_Handle,
                                                     uint8_t Advertising_Random_Address[6])
{
    return hci_le_set_advertising_set_random_address_api(Advertising_Handle,
                                                         Advertising_Random_Address);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_advertising_enable(uint8_t Enable,
                                                  uint8_t Number_of_Sets,
                                                  Advertising_Set_Parameters_t* Advertising_Set_Parameters)
{
    return hci_le_set_extended_advertising_enable_api(Enable,
                                                      Number_of_Sets,
                                                      Advertising_Set_Parameters);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_read_number_of_supported_advertising_sets(uint8_t* Num_Supported_Advertising_Sets)
{
    return hci_le_read_number_of_supported_advertising_sets_api(Num_Supported_Advertising_Sets);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_remove_advertising_set(uint8_t Advertising_Handle)
{
    return hci_le_remove_advertising_set_api(Advertising_Handle);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_clear_advertising_sets(void)
{
    return hci_le_clear_advertising_sets_api();
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_periodic_advertising_parameters(uint8_t Advertising_Handle,
                                                      uint16_t Periodic_Advertising_Interval_Min,
                                                      uint16_t Periodic_Advertising_Interval_Max,
                                                      uint16_t Periodic_Advertising_Properties)
{
    return hci_le_set_periodic_advertising_parameters_api(Advertising_Handle,
                                                          Periodic_Advertising_Interval_Min,
                                                          Periodic_Advertising_Interval_Max,
                                                          Periodic_Advertising_Properties);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_periodic_advertising_enable(uint8_t Enable,
                                                  uint8_t Advertising_Handle)
{
    return hci_le_set_periodic_advertising_enable_api(Enable,
                                                      Advertising_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_scan_parameters(uint8_t Own_Address_Type,
                                               uint8_t Scanning_Filter_Policy,
                                               uint8_t Scanning_PHYs,
                                               Extended_Scan_Parameters_t* Extended_Scan_Parameters)
{
    return hci_le_set_extended_scan_parameters_api(Own_Address_Type,
                                                   Scanning_Filter_Policy,
                                                   Scanning_PHYs,
                                                   Extended_Scan_Parameters);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_scan_enable(uint8_t Enable,
                                           uint8_t Filter_Duplicates,
                                           uint16_t Duration,
                                           uint16_t Period)
{
    return hci_le_set_extended_scan_enable_api(Enable,
                                               Filter_Duplicates,
                                               Duration,
                                               Period);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_extended_create_connection(uint8_t Initiating_Filter_Policy,
                                             uint8_t Own_Address_Type,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Initiating_PHYs,
                                             Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters)
{
    return hci_le_extended_create_connection_api(Initiating_Filter_Policy,
                                                 Own_Address_Type,
                                                 Peer_Address_Type,
                                                 Peer_Address,
                                                 Initiating_PHYs,
                                                 Extended_Create_Connection_Parameters);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_create_sync(uint8_t Options,
                                                   uint8_t Advertising_SID,
                                                   uint8_t Advertising_Address_Type,
                                                   uint8_t Advertiser_Address[6],
                                                   uint16_t Skip,
                                                   uint16_t Sync_Timeout,
                                                   uint8_t Sync_CTE_Type)
{
    return hci_le_periodic_advertising_create_sync_api(Options,
                                                       Advertising_SID,
                                                       Advertising_Address_Type,
                                                       Advertiser_Address,
                                                       Skip,
                                                       Sync_Timeout,
                                                       Sync_CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_create_sync_cancel(void)
{
    return hci_le_periodic_advertising_create_sync_cancel_api();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_terminate_sync(uint16_t Sync_Handle)
{
    return hci_le_periodic_advertising_terminate_sync_api(Sync_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_add_device_to_periodic_advertiser_list(uint8_t Advertiser_Address_Type,
                                                         uint8_t Advertiser_Address[6],
                                                         uint8_t Advertising_SID)
{
    return hci_le_add_device_to_periodic_advertiser_list_api(Advertiser_Address_Type,
                                                             Advertiser_Address,
                                                             Advertising_SID);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_remove_device_from_periodic_advertising_list(uint8_t Advertiser_Address_Type,
                                                               uint8_t Advertiser_Address[6],
                                                               uint8_t Advertising_SID)
{
    return hci_le_remove_device_from_periodic_advertising_list_api(Advertiser_Address_Type,
                                                                   Advertiser_Address,
                                                                   Advertising_SID);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_clear_periodic_advertiser_list(void)
{
    return hci_le_clear_periodic_advertiser_list_api();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_read_periodic_advertiser_list_size(uint8_t* Periodic_Advertiser_List_Size)
{
    return hci_le_read_periodic_advertiser_list_size_api(Periodic_Advertiser_List_Size);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_periodic_advertising_receive_enable(uint16_t Sync_Handle,
                                                          uint8_t Enable)
{
    return hci_le_set_periodic_advertising_receive_enable_api(Sync_Handle,
                                                              Enable);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                            uint16_t Skip,
                                                                            uint16_t Sync_Timeout,
                                                                            uint8_t CTE_Type)
{
    return hci_le_set_default_periodic_advertising_sync_transfer_parameters_api(Mode,
                                                                                Skip,
                                                                                Sync_Timeout,
                                                                                CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                    uint8_t Mode,
                                                                    uint16_t Skip,
                                                                    uint16_t Sync_Timeout,
                                                                    uint8_t CTE_Type)
{
    return hci_le_set_periodic_advertising_sync_transfer_parameters_api(Connection_Handle,
                                                                        Mode,
                                                                        Skip,
                                                                        Sync_Timeout,
                                                                        CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_set_info_transfer(uint16_t Connection_Handle,
                                                         uint16_t Service_Data,
                                                         uint8_t Advertising_Handle)
{
    return hci_le_periodic_advertising_set_info_transfer_api(Connection_Handle,
                                                             Service_Data,
                                                             Advertising_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                     uint16_t Service_Data,
                                                     uint16_t Sync_Handle)
{
    return hci_le_periodic_advertising_sync_transfer_api(Connection_Handle,
                                                         Service_Data,
                                                         Sync_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
tBleStatus hci_le_set_data_length(uint16_t Connection_Handle,
                                  uint16_t Tx_Octets,
                                  uint16_t Tx_Time)
{
    return hci_le_set_data_length_api(Connection_Handle,
                                      Tx_Octets,
                                      Tx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
tBleStatus hci_le_read_suggested_default_data_length(uint16_t* Suggested_Max_Tx_Octets,
                                                     uint16_t* Suggested_Max_Tx_Time)
{
    return hci_le_read_suggested_default_data_length_api(Suggested_Max_Tx_Octets,
                                                         Suggested_Max_Tx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
tBleStatus hci_le_write_suggested_default_data_length(uint16_t Suggested_Max_Tx_Octets,
                                                      uint16_t Suggested_Max_Tx_Time)
{
    return hci_le_write_suggested_default_data_length_api(Suggested_Max_Tx_Octets,
                                                          Suggested_Max_Tx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
tBleStatus hci_le_read_maximum_data_length(uint16_t* Supported_Max_Tx_Octets,
                                           uint16_t* Supported_Max_Tx_Time,
                                           uint16_t* Supported_Max_Rx_Octets,
                                           uint16_t* Supported_Max_Rx_Time)
{
    return hci_le_read_maximum_data_length_api(Supported_Max_Tx_Octets,
                                               Supported_Max_Tx_Time,
                                               Supported_Max_Rx_Octets,
                                               Supported_Max_Rx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
tBleStatus hci_le_enhanced_read_transmit_power_level(uint16_t Connection_Handle,
                                                     uint8_t PHY,
                                                     int8_t* Current_TX_Power_Level,
                                                     int8_t* Max_TX_Power_Level)
{
    return hci_le_enhanced_read_transmit_power_level_api(Connection_Handle,
                                                         PHY,
                                                         Current_TX_Power_Level,
                                                         Max_TX_Power_Level);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
tBleStatus hci_le_read_remote_transmit_power_level(uint16_t Connection_Handle,
                                                   uint8_t PHY)
{
    return hci_le_read_remote_transmit_power_level_api(Connection_Handle,
                                                       PHY);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
tBleStatus hci_le_set_path_loss_reporting_parameters(uint16_t Connection_Handle,
                                                     uint8_t High_Threshold,
                                                     uint8_t High_Hysteresis,
                                                     uint8_t Low_Threshold,
                                                     uint8_t Low_Hysteresis,
                                                     uint16_t Min_Time_Spent)
{
    return hci_le_set_path_loss_reporting_parameters_api(Connection_Handle,
                                                         High_Threshold,
                                                         High_Hysteresis,
                                                         Low_Threshold,
                                                         Low_Hysteresis,
                                                         Min_Time_Spent);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
tBleStatus hci_le_set_path_loss_reporting_enable(uint16_t Connection_Handle,
                                                 uint8_t Enable)
{
    return hci_le_set_path_loss_reporting_enable_api(Connection_Handle,
                                                     Enable);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_POWER_CONTROL_ENABLED == 1)
tBleStatus hci_le_set_transmit_power_reporting_enable(uint16_t Connection_Handle,
                                                      uint8_t Local_Enable,
                                                      uint8_t Remote_Enable)
{
    return hci_le_set_transmit_power_reporting_enable_api(Connection_Handle,
                                                          Local_Enable,
                                                          Remote_Enable);
}
#endif /* (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus hci_le_read_phy(uint16_t Connection_Handle,
                           uint8_t* TX_PHY,
                           uint8_t* RX_PHY)
{
    return hci_le_read_phy_api(Connection_Handle,
                               TX_PHY,
                               RX_PHY);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus hci_le_set_default_phy(uint8_t ALL_PHYS,
                                  uint8_t TX_PHYS,
                                  uint8_t RX_PHYS)
{
    return hci_le_set_default_phy_api(ALL_PHYS,
                                      TX_PHYS,
                                      RX_PHYS);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus hci_le_set_phy(uint16_t Connection_Handle,
                          uint8_t ALL_PHYS,
                          uint8_t TX_PHYS,
                          uint8_t RX_PHYS,
                          uint16_t PHY_options)
{
    return hci_le_set_phy_api(Connection_Handle,
                              ALL_PHYS,
                              TX_PHYS,
                              RX_PHYS,
                              PHY_options);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_remove_device_from_resolving_list(uint8_t Peer_Identity_Address_Type,
                                                    uint8_t Peer_Identity_Address[6])
{
    return hci_le_remove_device_from_resolving_list_api(Peer_Identity_Address_Type,
                                                        Peer_Identity_Address);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_add_device_to_resolving_list(uint8_t Peer_Identity_Address_Type,
                                               uint8_t Peer_Identity_Address[6],
                                               uint8_t Peer_IRK[16],
                                               uint8_t Local_IRK[16])
{
    return hci_le_add_device_to_resolving_list_api(Peer_Identity_Address_Type,
                                                   Peer_Identity_Address,
                                                   Peer_IRK,
                                                   Local_IRK);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_set_resolvable_private_address_timeout(uint16_t RpaTimeout)
{
    return hci_le_set_resolvable_private_address_timeout_api(RpaTimeout);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_set_address_resolution_enable(uint8_t AddressResolutionEnable)
{
    return hci_le_set_address_resolution_enable_api(AddressResolutionEnable);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_read_peer_resolvable_address(uint8_t Peer_Identity_Address_Type,
                                               uint8_t Peer_Identity_Address[6],
                                               uint8_t Peer_Resolvable_Address[6])
{
    return hci_le_read_peer_resolvable_address_api(Peer_Identity_Address_Type,
                                                   Peer_Identity_Address,
                                                   Peer_Resolvable_Address);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_read_local_resolvable_address(uint8_t Peer_Identity_Address_Type,
                                                uint8_t Peer_Identity_Address[6],
                                                uint8_t Local_Resolvable_Address[6])
{
    return hci_le_read_local_resolvable_address_api(Peer_Identity_Address_Type,
                                                    Peer_Identity_Address,
                                                    Local_Resolvable_Address);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_read_resolving_list_size(uint8_t* resolving_List_Size)
{
    return hci_le_read_resolving_list_size_api(resolving_List_Size);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_clear_resolving_list(void)
{
    return hci_le_clear_resolving_list_api();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_set_privacy_mode(uint8_t Peer_Identity_Address_Type,
                                   uint8_t Peer_Identity_Address[6],
                                   uint8_t Privacy_Mode)
{
    return hci_le_set_privacy_mode_api(Peer_Identity_Address_Type,
                                       Peer_Identity_Address,
                                       Privacy_Mode);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus hci_le_set_scan_parameters(uint8_t LE_Scan_Type,
                                      uint16_t LE_Scan_Interval,
                                      uint16_t LE_Scan_Window,
                                      uint8_t Own_Address_Type,
                                      uint8_t Scanning_Filter_Policy)
{
    return hci_le_set_scan_parameters_api(LE_Scan_Type,
                                          LE_Scan_Interval,
                                          LE_Scan_Window,
                                          Own_Address_Type,
                                          Scanning_Filter_Policy);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus hci_le_set_scan_enable(uint8_t LE_Scan_Enable,
                                  uint8_t Filter_Duplicates)
{
    return hci_le_set_scan_enable_api(LE_Scan_Enable,
                                      Filter_Duplicates);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus hci_le_create_connection(uint16_t LE_Scan_Interval,
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
                                    uint16_t Maximum_CE_Length)
{
    return hci_le_create_connection_api(LE_Scan_Interval,
                                        LE_Scan_Window,
                                        Initiator_Filter_Policy,
                                        Peer_Address_Type,
                                        Peer_Address,
                                        Own_Address_Type,
                                        Conn_Interval_Min,
                                        Conn_Interval_Max,
                                        Conn_Latency,
                                        Supervision_Timeout,
                                        Minimum_CE_Length,
                                        Maximum_CE_Length);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus hci_le_create_connection_cancel(void)
{
    return hci_le_create_connection_cancel_api();
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_MASTER_ENABLED == 1)
tBleStatus hci_le_connection_update(uint16_t Connection_Handle,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length)
{
    return hci_le_connection_update_api(Connection_Handle,
                                        Conn_Interval_Min,
                                        Conn_Interval_Max,
                                        Conn_Latency,
                                        Supervision_Timeout,
                                        Minimum_CE_Length,
                                        Maximum_CE_Length);
}
#endif /* (CONTROLLER_MASTER_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus hci_le_enhanced_receiver_test(uint8_t RX_Frequency,
                                         uint8_t Phy,
                                         uint8_t Modulation_index)
{
    return hci_le_enhanced_receiver_test_api(RX_Frequency,
                                             Phy,
                                             Modulation_index);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_receiver_test_v3(uint8_t RX_Channel,
                                   uint8_t PHY,
                                   uint8_t Modulation_Index,
                                   uint8_t Expected_CTE_Length,
                                   uint8_t Expected_CTE_Type,
                                   uint8_t Slot_Durations,
                                   uint8_t Switching_Pattern_Length,
                                   uint8_t* Antenna_IDs)
{
    return hci_le_receiver_test_v3_api(RX_Channel,
                                       PHY,
                                       Modulation_Index,
                                       Expected_CTE_Length,
                                       Expected_CTE_Type,
                                       Slot_Durations,
                                       Switching_Pattern_Length,
                                       Antenna_IDs);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus hci_le_enhanced_transmitter_test(uint8_t TX_Frequency,
                                            uint8_t Length_Of_Test_Data,
                                            uint8_t Packet_Payload,
                                            uint8_t Phy)
{
    return hci_le_enhanced_transmitter_test_api(TX_Frequency,
                                                Length_Of_Test_Data,
                                                Packet_Payload,
                                                Phy);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_transmitter_test_v3(uint8_t TX_Channel,
                                      uint8_t Test_Data_Length,
                                      uint8_t Packet_Payload,
                                      uint8_t PHY,
                                      uint8_t CTE_Length,
                                      uint8_t CTE_Type,
                                      uint8_t Switching_Pattern_Length,
                                      uint8_t* Antenna_IDs)
{
    return hci_le_transmitter_test_v3_api(TX_Channel,
                                          Test_Data_Length,
                                          Packet_Payload,
                                          PHY,
                                          CTE_Length,
                                          CTE_Type,
                                          Switching_Pattern_Length,
                                          Antenna_IDs);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) ||\
    (CONTROLLER_POWER_CONTROL_ENABLED == 1)
tBleStatus hci_le_transmitter_test_v4(uint8_t TX_Channel,
                                      uint8_t Test_Data_Length,
                                      uint8_t Packet_Payload,
                                      uint8_t PHY,
                                      uint8_t CTE_Length,
                                      uint8_t CTE_Type,
                                      uint8_t Switching_Pattern_Length,
                                      uint8_t* Antenna_IDs,
                                      int8_t Transmit_Power_Level)
{
    return hci_le_transmitter_test_v4_api(TX_Channel,
                                          Test_Data_Length,
                                          Packet_Payload,
                                          PHY,
                                          CTE_Length,
                                          CTE_Type,
                                          Switching_Pattern_Length,
                                          Antenna_IDs,
                                          Transmit_Power_Level);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) ||\
          (CONTROLLER_POWER_CONTROL_ENABLED == 1) */

