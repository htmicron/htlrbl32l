#include "stack_user_cfg.h"

#if (defined(CONTROLLER_CTE_ENABLED) &&\
     (CONTROLLER_CTE_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
tBleStatus hci_le_set_connectionless_cte_transmit_parameters(uint8_t Advertising_Handle,
                                                             uint8_t CTE_Length,
                                                             uint8_t CTE_Type,
                                                             uint8_t CTE_Count,
                                                             uint8_t Switching_Pattern_Length,
                                                             uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_connectionless_cte_transmit_enable(uint8_t Advertising_Handle,
                                                         uint8_t CTE_Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_connectionless_iq_sampling_enable(uint16_t Sync_Handle,
                                                        uint8_t Sampling_Enable,
                                                        uint8_t Slot_Durations,
                                                        uint8_t Max_Sampled_CTEs,
                                                        uint8_t Switching_Pattern_Length,
                                                        uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_connection_cte_receive_parameters(uint16_t Connection_Handle,
                                                        uint8_t Sampling_Enable,
                                                        uint8_t Slot_Durations,
                                                        uint8_t Switching_Pattern_Length,
                                                        uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_connection_cte_transmit_parameters(uint16_t Connection_Handle,
                                                         uint8_t CTE_Type,
                                                         uint8_t Switching_Pattern_Length,
                                                         uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_connection_cte_request_enable(uint16_t Connection_Handle,
                                                uint8_t Enable,
                                                uint16_t CTE_Request_Interval,
                                                uint8_t Requested_CTE_Length,
                                                uint8_t Requested_CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_connection_cte_response_enable(uint16_t Connection_Handle,
                                                 uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_antenna_information(uint8_t* Supported_Switching_Sampling_Rates,
                                           uint8_t* Num_Antennae,
                                           uint8_t* Max_Switching_Pattern_Length,
                                           uint8_t* Max_CTE_Length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_receiver_test_v3(uint8_t RX_Channel,
                                   uint8_t PHY,
                                   uint8_t Modulation_Index,
                                   uint8_t Expected_CTE_Length,
                                   uint8_t Expected_CTE_Type,
                                   uint8_t Slot_Durations,
                                   uint8_t Switching_Pattern_Length,
                                   uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_transmitter_test_v3(uint8_t TX_Channel,
                                      uint8_t Test_Data_Length,
                                      uint8_t Packet_Payload,
                                      uint8_t PHY,
                                      uint8_t CTE_Length,
                                      uint8_t CTE_Type,
                                      uint8_t Switching_Pattern_Length,
                                      uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#endif
