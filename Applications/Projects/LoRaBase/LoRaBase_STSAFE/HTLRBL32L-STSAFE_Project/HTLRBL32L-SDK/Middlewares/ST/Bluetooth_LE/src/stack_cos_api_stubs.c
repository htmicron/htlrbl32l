#include "stack_user_cfg.h"

#if (defined(L2CAP_COS_ENABLED) &&\
     (L2CAP_COS_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
tBleStatus aci_l2cap_cfc_connection_req(uint16_t Connection_Handle,
                                        uint16_t SPSM,
                                        uint16_t CID,
                                        uint16_t MTU,
                                        uint16_t MPS,
                                        uint8_t CFC_Policy,
                                        uint16_t RX_SDU_Buffer_Size,
                                        void* RX_SDU_Buffer)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

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
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_send_flow_control_credits(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t RX_Credits,
                                               uint8_t CFC_Policy,
                                               uint16_t* RX_Credit_Balance)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_disconnect(uint16_t Connection_Handle,
                                uint16_t CID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_transmit_sdu_data(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       uint16_t SDU_Length,
                                       uint8_t* SDU_Data)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_extract_sdu_data(uint16_t Connection_Handle,
                                      uint16_t CID,
                                      uint16_t SDU_Data_Buffer_Size,
                                      void* SDU_Data_Buffer,
                                      uint16_t* SDU_Length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#endif
