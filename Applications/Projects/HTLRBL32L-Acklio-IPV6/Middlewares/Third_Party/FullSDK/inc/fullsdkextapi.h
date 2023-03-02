/**
 * @file fullsdkextapi.h
 * @copyright 2018-2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * Template interface.
 */

#ifndef FULLSDK_EXT_API_H
#define FULLSDK_EXT_API_H

#include <stdint.h>

#include "fullsdkmgt.h"

/**
 * List of supported network protocols.
 */
typedef enum
{
  MGT_NET_IPV6,
  MGT_NET_IPV4,
} mgt_net_protocol_t;

/**
 * @brief Provision SCHC compression rules in a binary format. This function
 * must be called after `mgt_initialize`.
 *
 * @note This function should be called only when the FullSDK library is
 * supporting dynamic rule loading.
 *
 * @param[in] bin_rules SCHC rules in a binary format.
 * @param[in] bin_rules_len the length of bin_rules, in bytes
 * @param[in] memory a memory area that can be used by the parser
 * @param[in] memory_len the length of the memory area
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_ERROR: error
 *   - MGT_MEM_ERR: memory_ptr is not large enough
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 *   - MGT_TPL_CRC_ERR: failure to validate the data's CRC
 *   - MGT_TPL_PARSER_ERR: error while reading data
 *   - MGT_OPERATION_NOT_SUPPORTED_ERR: operation not supported
 *   - MGT_TPL_UNSUPPORTED_STACK_ERR: template's stack not supported
 */
mgt_status_t mgt_provision_header_rules(const uint8_t *const bin_rules,
                                        uint16_t bin_rules_len,
                                        uint8_t *const memory_ptr,
                                        uint16_t memory_len);

/**
 * @brief Provision payload pattern rules in a binary format. This function must
 * be called after `mgt_provision_header_rules`.
 *
 * @note This function should be called only when the FullSDK library is
 * supporting dynamic payload patterns loading.
 *
 * @param[in] bin_rules payload pattern rules in a binary format.
 * @param[in] bin_rules_len the length of bin_rules, in bytes
 * @param[in] memory a memory area that can be used by the parser
 * @param[in] memory_len the length of the memory area
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_ERROR: error
 *   - MGT_MEM_ERR: memory_ptr is not large enough
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 *   - MGT_TPL_CRC_ERR: failure to validate the data's CRC
 *   - MGT_TPL_PARSER_ERR: error while reading data
 *   - MGT_OPERATION_NOT_SUPPORTED_ERR: operation not supported
 *   - MGT_TPL_UNSUPPORTED_STACK_ERR: template's stack not supported
 */
mgt_status_t mgt_provision_payload_rules(const uint8_t *const bin_rules,
                                         uint16_t bin_rules_len,
                                         uint8_t *const memory_ptr,
                                         uint16_t memory_len);

/**
 * @brief This function returns the template ID of the current template.
 *
 * @param[out] id template id
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 *   - MGT_TPL_NOT_INIT_ERR: the template is not yet initialized
 */
mgt_status_t mgt_get_template_id(uint8_t *id);

/**
 * @brief This function sets the parameter to the corresponding index in the
 * template.
 *
 * @param[in] index 0-based index corresponding to the template
 * parameters to set. Check the documentation given along the rules binary file
 * for more information.
 * @param[in] value the value to associate to the parameters
 * @param[in] size the size of the given value in bytes
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_ERROR: inconsistent parameter length
 *   - MGT_OPERATION_NOT_SUPPORTED_ERR: operation not supported
 *   - MGT_MEM_ERR: the memory area provided at provisioning is full
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 *   - MGT_TPL_NOT_INIT_ERR: the template is not yet initialized
 *   - MGT_TPL_INVALID_PARAM_ID: the index used is invalid
 *   - MGT_TPL_INVALID_PARAM: the size of the value provided is incorrect
 */
mgt_status_t mgt_set_template_param(uint8_t index, const uint8_t *value,
                                    uint16_t size);

/**
 * @brief This function gets the parameter to the corresponding index in the
 * template.
 *
 * @param[in] index 0-based index corresponding to the template
 * parameters to retrieve. Check the documentation given along the rules binary
 * file for more information.
 * @param[in,out] value the value associated to the index
 * @param[in,out] size the size of the given value in bytes
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_ERROR: inconsistent parameter length
 *   - MGT_OPERATION_NOT_SUPPORTED_ERR: operation not supported
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 *   - MGT_TPL_NOT_INIT_ERR: the template is not yet initialized
 */
mgt_status_t mgt_get_template_param(uint8_t index, uint8_t **value,
                                    uint16_t *size);

/**
 * @brief This function returns the number of configurable parameters
 *
 * @param[out] nb number of configurable parameters
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 *   - MGT_TPL_NOT_INIT_ERR: the template is not yet initialized
 */
mgt_status_t mgt_get_nb_template_params(uint8_t *nb);

/**
 * @brief Clears the template parameters in the memory.
 * This function is typically called when the `mgt_set_template_param` returns a
 * `MGT_MEM_ERR`.
 * The user will need to set again all the template parameters after.
 * If calling this function is not enough, it means that the provided
 * `memory_ptr` to `mgt_provision_header_rules` is too small.
 *
 * @note This function might not be implemented
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 *   - MGT_TPL_NOT_INIT_ERR: the template is not yet initialized
 */
mgt_status_t mgt_reset_template_params(void);

/**
 * @brief This function return the network protocol.
 *
 * @param[in,out] type network protocol
 *
 * @return operation status:
 *   - MGT_SUCCESS: success
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 *   - MGT_NETWORK_PROTOCOL_ERR: invalid network protocol
 */
mgt_status_t mgt_get_network_protocol(mgt_net_protocol_t *type);

/**
 * @brief This function returns the IPv6 address set for the datagram layer.
 *
 * @param[in,out] addr address of a buffer where the 16-byte IPv6 address will
 *   be written
 * @param[in] size size of addr buffer in bytes
 *
 * @return operation status:
 *   - MGT_SUCCESS: success
 *   - MGT_MEM_ERR: input buffer is too small
 *   - MGT_OPERATION_NOT_SUPPORTED_ERR
 *   - MGT_NETWORK_PROTOCOL_ERR: invalid network protocol
 *   - MGT_TPL_NOT_INIT_ERR: the template is not yet initialized
 *   - MGT_TPL_INVALID_PARAM: template parameters are not configured
 *
 * @note If status is not equal to MGT_SUCCESS, addr value must be ignored.
 */
mgt_status_t mgt_get_ipv6_address(uint8_t *addr, uint8_t size);

#endif /* FULLSDK_EXT_API_H_ */

