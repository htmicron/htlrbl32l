/**
 * @file atapi.h
 * @copyright 2021-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief AT SCHC commands for Network layer
 */

#ifndef AT_NET_H
#define AT_NET_H

#include <stdint.h>

#include "at.h"

/**
 * @brief Number of NET_API AT commands
 */
#define NB_NET_API_AT_COMMANDS 1

/**
 * @brief AT commands list
 */
extern const at_command_t at_net_api_command[NB_NET_API_AT_COMMANDS];

/**
 * @brief This function allows to send raw data through FullSDK
 *
 * @param[in] param The data to send (hexadecimal representation)
 * @param[out] error A pointer where an error code can be stored
 * @return at_status_t
 */
at_status_t at_send_raw_binary_data(const char *param, uint8_t *error);

#endif /* AT_NET_H */
