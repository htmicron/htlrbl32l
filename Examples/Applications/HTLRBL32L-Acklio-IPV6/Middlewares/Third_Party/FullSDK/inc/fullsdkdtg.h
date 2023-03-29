/**
 * @file fullsdkdtg.h
 * @copyright 2018-2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Pascal Bodin - pascal@ackl.io
 *
 * @brief Public Datagram layer interface
 */

#ifndef FULLSDK_DTG_H
#define FULLSDK_DTG_H

#include <stdbool.h>
#include <stdint.h>

#define IPV6_ADDRESS_LENGTH_BYTES 16
#define IPV4_ADDRESS_LENGTH_BYTES 4
#define IP_ADDRESS_MAX_LENGTH_BYTES IPV6_ADDRESS_LENGTH_BYTES
#define IP_PORT_LENGTH_BYTES 2
#define DTG_INVALID_SOCKET NULL

/**
 * typedef
 */
typedef struct dtg_socket_s dtg_socket_t;

/**
 * @brief socket address structure
 */
typedef struct
{
  uint8_t addr[IP_ADDRESS_MAX_LENGTH_BYTES];
  uint8_t port[IP_PORT_LENGTH_BYTES];
} dtg_sockaddr_t;

/**
 * @brief extended socket address structure
 */
typedef struct
{
  uint8_t type;
  uint8_t *addr;
  uint16_t len;
  uint8_t port[IP_PORT_LENGTH_BYTES];
} dtg_extended_sockaddr_t;

/**
 * Status values that can be returned by layer functions.
 */
typedef enum
{
  DTG_SUCCESS,
  DTG_ERROR,
  DTG_CONN_ERR,
  DTG_BUFFER_ERR,
  DTG_OVERRUN_ERR,
  DTG_BUSY_ERR,
  DTG_NO_BIND_ERR,
  DTG_NO_SOCKET_ERR,
  DTG_NOT_IMPL_ERR,
  DTG_TOO_BIG_ERR,
  DTG_L2_ERR,
  DTG_SEND_ABORT_ERR,
  DTG_RECV_ABORT_ERR,
  DTG_INTERNAL_ERR,
  DTG_CD_ERROR,
  DTG_RULES_NOT_FOUND_ERR,
  DTG_REQ_CALLBACK_ERR,
  DTG_INTERFACE_NOT_AVAILABLE_ERR,
  DTG_ADDR_ERR,
  DTG_NOT_IPV6_ERR,
  DTG_NOT_INITIALIZED,
  DTG_TPL_PARAMS_ERR,
} dtg_status_t;

/**
 * @note Declaration of callbacks called by the layer. They must be defined by
 * the client code, and are provided to the layer initialization function
 * or to the socket creation function.
 */

/**
 * @brief Callback used to return the result of a transmission request. The
 * callback provides the status of the request (success or error) and, in case
 * of error, a value that depends on the layer two. In case of success, error
 * value is undefined.
 *
 * @note Implementation is mandatory.
 *
 * @param[in] socket socket for which transmission result is returned
 * @param[in] status status of the request:
 *   - DTG_SUCCESS: data successfully transmitted
 *   - DTG_ERROR: internal error
 *   - DTG_L2_ERR: error from L2 layer
 *   - DTG_SEND_ABORT_ERR: session aborted by the sender
 *   - DTG_RECV_ABORT_ERR: session aborted by the receiver
 * @param[in] error additional information in case of error, depending on layer
 * two
 */
typedef void (*dtg_transmission_result_t)(const dtg_socket_t *socket,
                                          dtg_status_t status, uint16_t error);

/**
 * @brief Callback used to return received data. The buffer containing received
 * data is the one provided to the socket creation function. It's up to the
 * client code to save received data, if required. The DTG layer guarantees that
 * no write operation to the buffer will be performed by the layer until this
 * callback returns. This can lead to reception overrun and message loss if
 * reception throughput is high and callback execution takes too long.
 *
 * In the same way it is the responsibility of the client code to save the
 * information contained in p_remote if it needs to use it later on.
 *
 * If buffer provided at socket creation time is not long enough to store
 * received data, an error is reported, and received data must not be used.
 *
 * If an overrun is detected, an error is reported.
 *
 *
 * @note Implementation is mandatory.
 *
 * @param[in] socket socket for which transmission result is returned
 * @param[in] p_buffer buffer containing received data
 * @param[in] data_size size in bytes of received data
 * @param[in] p_remote IP address and UDP source port of the sender.
 * @param[in] status no data is raised to the user in case of error
 *   - DTG_SUCCESS: success, received data can be used
 *   - DTG_ERROR: internal error
 *   - DTG_BUFFER_ERR: receive buffer is too small
 *   - DTG_L2_ERR: L2 error
 *   - DTG_SEND_ABORT_ERR: session aborted by the sender
 *   - DTG_RECV_ABORT_ERR: session aborted by the receiver
 *   - DTG_CD_ERROR: decompression error
 *   - DTG_RULES_NOT_FOUND_ERR: decompression rule not found
 *   - DTG_OVERRUN_ERR: data received before the consumption of the previous one
 *   - DTG_INTERNAL_ERR: received data pointer is not valid or received data
 * size is zero
 * @note if status is not equal to DTG_SUCCESS, p_buffer and p_remote parameters
 * are set to NULL.
 */
typedef void (*dtg_data_received_t)(const dtg_socket_t *socket,
                                    uint8_t *p_buffer, uint16_t data_size,
                                    const dtg_sockaddr_t *p_remote,
                                    dtg_status_t status);

/**
 * List of callbacks, for interface initialization.
 */
typedef struct
{
  dtg_transmission_result_t transmission_result;
  dtg_data_received_t data_received;
} dtg_callbacks_t;

/**
 * @brief This function initializes the datagram interface. It should be called
 * only once.
 *
 * @param[in] callbacks callbacks
 *
 * @return status of the initialization:
 *   - DTG_SUCCESS: success
 *   - DTG_REQ_CALLBACK_ERR: a mandatory callback is not defined
 *   - DTG_TPL_PARAMS_ERR: template parameters are not fully configured
 *   - DTG_NOT_IMPL_ERR: protocol not implemented
 */
dtg_status_t dtg_initialize(const dtg_callbacks_t *callbacks);

/**
 * @brief This function creates a socket. A socket must be created for any
 * communication.
 *
 * @param[in] p_receive_buffer buffer allocated by the client code used to store
 * received data
 * @param[in] receive_buffer_size size of the receive buffer
 * @param[in] p_transmission_buffer buffer allocated by the client code used to
 * store transmitted data
 * @param[in] transmission_buffer_size size of the transmission buffer
 *
 * @note the received data must be accessed with the pointer returned by the
 * reception callback only. The receive buffer provided in this function should
 * not be accessed directly.
 *
 * @return socket (a pointer to an opaque structure) or
 *   DTG_INVALID_SOCKET in case of error
 */
dtg_socket_t *dtg_socket(uint8_t *p_receive_buffer,
                         uint16_t receive_buffer_size,
                         uint8_t *p_transmission_buffer,
                         uint16_t transmission_buffer_size);

/**
 * @brief This function closes the socket and aborts any fragmentation session
 *
 * @param[in] socket socket to clear
 *
 * @return status of the bind:
 *   - DTG_SUCCESS: success
 *   - DTG_NO_SOCKET_ERR: error
 *   - DTG_ERROR: error
 */
dtg_status_t dtg_close(dtg_socket_t *socket);

/**
 * @brief This function binds a socket to a local port.
 *
 * It must be called before any send or receive operation is performed on
 * the socket, unless the layer is configured for no IP headers.
 *
 * @param[in] socket socket to bind
 * @param[in] p_sockaddr structure defining IP source address and UDP source
 * port
 *
 * @return status of the bind:
 *   - DTG_SUCCESS: success
 *   - DTG_NO_SOCKET_ERR: no socket available
 *   - DTG_NOT_INITIALIZED: dtg_initialize() has not been called
 *   - DTG_ADDR_ERR: IPv6 address passed for socket is not the same than
 *       the address configured by dtg_set_ipv6_*()
 *   - DTG_TPL_PARAMS_ERR: template parameters are not fully configured
 */
dtg_status_t dtg_bind(dtg_socket_t *socket, const dtg_sockaddr_t *p_sockaddr);

/**
 * @brief This function requests the transmission of a message to a remote host.
 *
 * dtg_transmission_result_t callback is called on completion of the request.
 *
 * @param[in] socket socket
 * @param[in] p_data buffer containing data to be sent
 * @param[in] data_size size in bytes of data to be transmitted
 * @param[in] p_dest_addr address and port of remote application
 *
 * @return status of the request:
 * - DTG_SUCCESS: success
 * - DTG_CONN_ERR: connectivity is no more available
 * - DTG_BUSY_ERR: layer is busy, request is ignored
 * - DTG_NO_BIND_ERR: bind has not been called and IP headers are requested
 * - DTG_TOO_BIG_ERR: data is too large to be sent without fragmentation
 * - DTG_L2_ERR: error returned by layer two
 * - DTG_NO_SOCKET_ERR: provided socket structure is not valid
 * - DTG_BUFFER_ERR: provided buffer size is bigger than supported
 * - DTG_CD_ERROR: C/D layer error
 * - DTG_TPL_PARAMS_ERR: template parameters are not completely configured
 * - DTG_ERROR: F/R layer unhandled error
 */
dtg_status_t dtg_sendto(dtg_socket_t *socket, const uint8_t *p_data,
                        uint16_t data_size, const dtg_sockaddr_t *p_dest_addr);

#endif /* FULLSDK_DTG_H */

