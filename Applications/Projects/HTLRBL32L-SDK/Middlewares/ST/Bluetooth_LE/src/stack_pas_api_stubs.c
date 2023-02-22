#include "stack_user_cfg.h"

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
     (CONTROLLER_PERIODIC_ADV_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
tBleStatus aci_gap_set_periodic_advertising_configuration(uint8_t Advertising_Handle,
                                                          uint16_t Periodic_Advertising_Interval_Min,
                                                          uint16_t Periodic_Advertising_Interval_Max,
                                                          uint16_t Periodic_Advertising_Properties)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_periodic_advertising_enable(uint8_t Enable,
                                                   uint8_t Advertising_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_periodic_advertising_data(uint8_t Advertising_Handle,
                                                 uint8_t Advertising_Data_Length,
                                                 uint8_t* Advertising_Data)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_periodic_advertising_create_sync(uint8_t Options,
                                                    uint8_t Advertising_SID,
                                                    uint8_t Advertising_Address_Type,
                                                    uint8_t Advertiser_Address[6],
                                                    uint16_t Skip,
                                                    uint16_t Sync_Timeout,
                                                    uint8_t Sync_CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_periodic_advertising_create_sync_cancel(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_periodic_advertising_terminate_sync(uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_periodic_advertising_receive_enable(uint16_t Sync_Handle,
                                                           uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_add_device_to_periodic_advertiser_list(uint8_t Advertiser_Address_Type,
                                                          uint8_t Advertiser_Address[6],
                                                          uint8_t Advertising_SID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_remove_device_from_periodic_advertising_list(uint8_t Advertiser_Address_Type,
                                                                uint8_t Advertiser_Address[6],
                                                                uint8_t Advertising_SID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_clear_periodic_advertiser_list(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_read_periodic_advertiser_list_size(uint8_t* Periodic_Advertiser_List_Size)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                      uint16_t Service_Data,
                                                      uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_periodic_advertising_set_info_transfer(uint16_t Connection_Handle,
                                                          uint16_t Service_Data,
                                                          uint8_t Advertising_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                     uint8_t Mode,
                                                                     uint16_t Skip,
                                                                     uint16_t Sync_Timeout,
                                                                     uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                             uint16_t Skip,
                                                                             uint16_t Sync_Timeout,
                                                                             uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#if (defined(CONTROLLER_CTE_ENABLED) &&\
            (CONTROLLER_CTE_ENABLED == 1))
tBleStatus hci_le_set_connectionless_cte_transmit_parameters(uint8_t Advertising_Handle,
                                                             uint8_t CTE_Length,
                                                             uint8_t CTE_Type,
                                                             uint8_t CTE_Count,
                                                             uint8_t Switching_Pattern_Length,
                                                             uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_CTE_ENABLED) &&\
            (CONTROLLER_CTE_ENABLED == 1))
tBleStatus hci_le_set_connectionless_cte_transmit_enable(uint8_t Advertising_Handle,
                                                         uint8_t CTE_Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_CTE_ENABLED) &&\
            (CONTROLLER_CTE_ENABLED == 1))
tBleStatus hci_le_set_connectionless_iq_sampling_enable(uint16_t Sync_Handle,
                                                        uint8_t Sampling_Enable,
                                                        uint8_t Slot_Durations,
                                                        uint8_t Max_Sampled_CTEs,
                                                        uint8_t Switching_Pattern_Length,
                                                        uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

tBleStatus hci_le_set_periodic_advertising_enable(uint8_t Enable,
                                                  uint8_t Advertising_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_periodic_advertising_create_sync(uint8_t Options,
                                                   uint8_t Advertising_SID,
                                                   uint8_t Advertising_Address_Type,
                                                   uint8_t Advertiser_Address[6],
                                                   uint16_t Skip,
                                                   uint16_t Sync_Timeout,
                                                   uint8_t Sync_CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_periodic_advertising_create_sync_cancel(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_periodic_advertising_terminate_sync(uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_add_device_to_periodic_advertiser_list(uint8_t Advertiser_Address_Type,
                                                         uint8_t Advertiser_Address[6],
                                                         uint8_t Advertising_SID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_remove_device_from_periodic_advertising_list(uint8_t Advertiser_Address_Type,
                                                               uint8_t Advertiser_Address[6],
                                                               uint8_t Advertising_SID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_clear_periodic_advertiser_list(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_periodic_advertiser_list_size(uint8_t* Periodic_Advertiser_List_Size)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_periodic_advertising_receive_enable(uint16_t Sync_Handle,
                                                          uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                            uint16_t Skip,
                                                                            uint16_t Sync_Timeout,
                                                                            uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                    uint8_t Mode,
                                                                    uint16_t Skip,
                                                                    uint16_t Sync_Timeout,
                                                                    uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_periodic_advertising_set_info_transfer(uint16_t Connection_Handle,
                                                         uint16_t Service_Data,
                                                         uint8_t Advertising_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                     uint16_t Service_Data,
                                                     uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#endif
