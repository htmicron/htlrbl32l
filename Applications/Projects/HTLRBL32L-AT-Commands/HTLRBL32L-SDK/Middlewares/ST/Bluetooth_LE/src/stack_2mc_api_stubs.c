#include "stack_user_cfg.h"

#if (defined(CONTROLLER_2M_CODED_PHY_ENABLED) &&\
     (CONTROLLER_2M_CODED_PHY_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
tBleStatus hci_le_read_phy(uint16_t Connection_Handle,
                           uint8_t* TX_PHY,
                           uint8_t* RX_PHY)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_default_phy(uint8_t ALL_PHYS,
                                  uint8_t TX_PHYS,
                                  uint8_t RX_PHYS)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_phy(uint16_t Connection_Handle,
                          uint8_t ALL_PHYS,
                          uint8_t TX_PHYS,
                          uint8_t RX_PHYS,
                          uint16_t PHY_options)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_enhanced_receiver_test(uint8_t RX_Frequency,
                                         uint8_t Phy,
                                         uint8_t Modulation_index)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_enhanced_transmitter_test(uint8_t TX_Frequency,
                                            uint8_t Length_Of_Test_Data,
                                            uint8_t Packet_Payload,
                                            uint8_t Phy)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#endif
