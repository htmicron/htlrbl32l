#include "stack_user_cfg.h"

#if (defined(CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED) &&\
     (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
tBleStatus hci_le_set_data_length(uint16_t Connection_Handle,
                                  uint16_t Tx_Octets,
                                  uint16_t Tx_Time)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_suggested_default_data_length(uint16_t* Suggested_Max_Tx_Octets,
                                                     uint16_t* Suggested_Max_Tx_Time)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_write_suggested_default_data_length(uint16_t Suggested_Max_Tx_Octets,
                                                      uint16_t Suggested_Max_Tx_Time)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_maximum_data_length(uint16_t* Supported_Max_Tx_Octets,
                                           uint16_t* Supported_Max_Tx_Time,
                                           uint16_t* Supported_Max_Rx_Octets,
                                           uint16_t* Supported_Max_Rx_Time)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#endif
