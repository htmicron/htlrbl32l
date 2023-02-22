#include "stack_user_cfg.h"

#if (defined(CONTROLLER_MASTER_ENABLED) &&\
     (CONTROLLER_MASTER_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
tBleStatus aci_gap_start_connection_update(uint16_t Connection_Handle,
                                           uint16_t Conn_Interval_Min,
                                           uint16_t Conn_Interval_Max,
                                           uint16_t Conn_Latency,
                                           uint16_t Supervision_Timeout,
                                           uint16_t Minimum_CE_Length,
                                           uint16_t Maximum_CE_Length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_send_pairing_req(uint16_t Connection_Handle,
                                    uint8_t Force_Rebond)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_scan_configuration(uint8_t duplicate_filtering,
                                          uint8_t scanning_filter_policy,
                                          uint8_t phy,
                                          uint8_t scan_type,
                                          uint16_t scan_interval,
                                          uint16_t scan_window)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_connection_configuration(uint8_t phy,
                                                uint16_t conn_interval_min,
                                                uint16_t conn_interval_max,
                                                uint16_t conn_latency,
                                                uint16_t supervision_timeout,
                                                uint16_t minimum_ce_length,
                                                uint16_t maximum_ce_length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_create_connection(uint8_t Initiating_PHY,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_start_procedure(uint8_t procedure_code,
                                   uint8_t phys,
                                   uint16_t duration,
                                   uint16_t period)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_discover_name(uint8_t PHYs,
                                 uint8_t Peer_Address_Type,
                                 uint8_t Peer_Address[6])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_terminate_proc(uint8_t Procedure_Code)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

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
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_start_encryption(uint16_t Connection_Handle,
                                   uint8_t Random_Number[8],
                                   uint16_t Encrypted_Diversifier,
                                   uint8_t Long_Term_Key[16])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_scan_parameters(uint8_t LE_Scan_Type,
                                      uint16_t LE_Scan_Interval,
                                      uint16_t LE_Scan_Window,
                                      uint8_t Own_Address_Type,
                                      uint8_t Scanning_Filter_Policy)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_scan_enable(uint8_t LE_Scan_Enable,
                                  uint8_t Filter_Duplicates)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

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
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_create_connection_cancel(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_connection_update(uint16_t Connection_Handle,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#endif
