/**
 * @copyright 2021-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief AT SCHC commands for Datagram layer
 */

#ifndef AT_DTG_H
#define AT_DTG_H

#include <stdint.h>

#include "at.h"

/**
 * @brief Number of DTG_API AT commands
 */
#define NB_DTG_API_AT_COMMANDS 5

/**
 * @brief AT commands list
 */
extern const at_command_t at_dtg_api_command[NB_DTG_API_AT_COMMANDS];

/**
 * @brief Creates a datagram socket
 * @param Param represented in ASCII format
 * @retval AT_OK if OK otherwise AT_ERROR
 */
at_status_t at_socket(const char *param, uint8_t *error);

/**
 * @brief Binds host IP address and port to a datagram socket
 * @param Param represented in ASCII format
 * @retval AT_OK if OK otherwise AT_ERROR
 */
at_status_t at_bind(const char *param, uint8_t *error);

/**
 * @brief Closes a datagram socket
 * @param Param represented in ASCII format
 * @retval AT_OK if OK otherwise AT_ERROR
 */
at_status_t at_close(const char *param, uint8_t *error);

/**
 * @brief Sends data through FullSDK
 * @param Param represented in ASCII format
 * @retval AT_OK if OK otherwise AT_ERROR
 */
at_status_t at_ext_send(const char *param, uint8_t *error);

/**
 * @brief Sends data through FullSDK
 * @param Param represented in hexadecimal format
 * @retval AT_OK if OK otherwise AT_ERROR
 */
at_status_t at_ext_send_b(const char *param, uint8_t *error);

#endif /* AT_DTG_H */
