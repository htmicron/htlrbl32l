/**
 * @file fullsdknet.h
 * @copyright 2018-2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief Public Network layer interface
 */

#ifndef FULLSDK_NET_H
#define FULLSDK_NET_H

#include <stdint.h>

#define IPV6_ADDRESS_LENGTH_BYTES 16
#define IPV4_ADDRESS_LENGTH_BYTES 4
#define IP_ADDRESS_MAX_LENGTH_BYTES IPV6_ADDRESS_LENGTH_BYTES

/**
 * Status values that can be returned by layer functions.
 */
typedef enum
{
  NET_SUCCESS,
  NET_ERROR,
  NET_INTERFACE_NOT_AVAILABLE_ERR,
  NET_BUFFER_ERR,
  NET_REQ_CALLBACK_ERR,
  NET_L2_ERR,
  NET_SEND_ABORT_ERR,
  NET_RECV_ABORT_ERR,
  NET_CD_ERR,
  NET_RULES_NOT_FOUND_ERR,
  NET_TPL_PARAMS_ERR,
  NET_BUSY_ERR,
  NET_INTERNAL_ERR,
} net_status_t;

/**
 * @brief Declaration of callbacks called by the layer. They must be defined by
 * the client code, and are provided to the layer initialization function.
 */

/**
 * @brief Callback used to return the result of a transmission request. The
 * callback provides the status of the request (success or error) and, in case
 * of error, a value that depends on the layer two. In case of success, error
 * value is undefined.
 *
 * @note Implementation is mandatory.
 *
 * @param[in] status status of the request:
 *   - NET_SUCCESS: data successfully transmitted
 *   - NET_ERROR: internal error
 *   - NET_L2_ERR: error from L2 layer
 *   - NET_SEND_ABORT_ERR: session aborted by the sender
 *   - NET_RECV_ABORT_ERR: session aborted by the receiver
 * @param[in] error additional information in case of error, depending on layer
 * two
 */
typedef void (*net_transmission_result_t)(net_status_t status, uint16_t error);

/**
 * @brief Callback used to return received data. The buffer containing received
 * data is the one provided to the Network layer initialization function. It's
 * up to the client code to save received data, if required. The Network layer
 * guarantees that no write operation to the buffer will be performed by the
 * layer until this callback returns. This can lead to reception overrun and
 * message loss if reception throughput is high and callback execution takes too
 * long.
 *
 * If the buffer provided at Network layer initialization is not long enough to
 * store received data, an error is reported, and received data must not be
 * used.
 *
 * If an overrun is detected, an error is reported.
 *
 * @note Implementation is mandatory.
 *
 * @param[in] buffer buffer containing received raw data
 * @param[in] data_size size in bytes of received data
 * @param[in] status no data is raised to the user in case of error
 *   - NET_SUCCESS: success, received data can be used
 *   - NET_ERROR: internal error
 *   - NET_BUFFER_ERR: receive buffer is too small
 *   - NET_OVERRUN_ERR: data received before the consumption of the previous
 *   - NET_L2_ERR: L2 error
 *   - NET_SEND_ABORT_ERR: session aborted by the sender
 *   - NET_RECV_ABORT_ERR: session aborted by the receiver
 *   - NET_CD_ERR: error during decompression
 *   - NET_RULES_NOT_FOUND_ERR: decompression rule not found
 *
 * If status is not equal to NET_SUCCESS, buffer parameter is set to NULL.
 */
typedef void (*net_data_received_t)(const uint8_t *buffer, uint16_t data_size,
                                    net_status_t status);

/**
 * List of callbacks, for layer initialization.
 */
typedef struct
{
  net_transmission_result_t transmission_result;
  net_data_received_t data_received;
} net_callbacks_t;

/**
 * @brief This function initializes the Network layer. It should be called only
 * once.
 *
 * @param[in] callbacks callbacks
 *
 * @return status of the initialization:
 *   - NET_SUCCESS: success
 *   - NET_REQ_CALLBACK_ERR: a mandatory callback is not defined
 */
net_status_t net_initialize(const net_callbacks_t *callbacks);

/**
 * @brief This function requests the transmission of a raw data. This data has
 * to be an IPv6/UDP packet.
 *
 * net_transmission_result_t callback is called on completion of the request.
 *
 * @param[in] data raw data to be sent
 * @param[in] data_size size in bytes of data to be transmitted
 *
 * @return status of the request:
 * - NET_SUCCESS: success
 * - NET_BUSY_ERR: layer is busy, request is ignored
 * - NET_L2_ERR: error returned by layer two
 * - NET_TPL_PARAMS_ERR: template parameters are not completely configured
 * - NET_BUFFER_ERR
 */
net_status_t net_sendto(const uint8_t *data, uint16_t data_size);

#endif /* FULLSDK_NET_H_ */

