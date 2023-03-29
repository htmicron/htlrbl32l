#include "stack_user_cfg.h"

#if (defined(CONTROLLER_POWER_CONTROL_ENABLED) &&\
     (CONTROLLER_POWER_CONTROL_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
tBleStatus aci_hal_set_le_power_control(uint8_t Enable,
                                        uint8_t PHY,
                                        int8_t RSSI_Target,
                                        uint8_t RSSI_Hysteresis,
                                        int8_t Initial_TX_Power,
                                        uint8_t RSSI_Filtering_Coefficient)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_enhanced_read_transmit_power_level(uint16_t Connection_Handle,
                                                     uint8_t PHY,
                                                     int8_t* Current_TX_Power_Level,
                                                     int8_t* Max_TX_Power_Level)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_remote_transmit_power_level(uint16_t Connection_Handle,
                                                   uint8_t PHY)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_path_loss_reporting_parameters(uint16_t Connection_Handle,
                                                     uint8_t High_Threshold,
                                                     uint8_t High_Hysteresis,
                                                     uint8_t Low_Threshold,
                                                     uint8_t Low_Hysteresis,
                                                     uint16_t Min_Time_Spent)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_path_loss_reporting_enable(uint16_t Connection_Handle,
                                                 uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_transmit_power_reporting_enable(uint16_t Connection_Handle,
                                                      uint8_t Local_Enable,
                                                      uint8_t Remote_Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#if (defined(CONTROLLER_CTE_ENABLED) &&\
            (CONTROLLER_CTE_ENABLED == 0))
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
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#endif
