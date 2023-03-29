/**
 * @file fullsdkl2a.h
 * @copyright 2018-2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Pascal Bodin - pascal@ackl.io
 *
 * @brief Public L2A layer interface
 */

#ifndef FULLSDK_L2A_H
#define FULLSDK_L2A_H

#include <stdbool.h>
#include <stdint.h>


/**
 * Status values that can be returned by layer functions.
 */
typedef enum
{
  L2A_SUCCESS,
  L2A_L2_ERROR,
  L2A_REQ_CALLBACK_ERR,
  L2A_CONNECT_ERR,
  L2A_BUSY_ERR,
  L2A_BUFFER_ERR,
  L2A_OVERRUN_ERR,
  L2A_INTERNAL_ERR,
} l2a_status_t;

/**
 * Supported L2 technologies.
 */
typedef enum
{
  L2A_DEFAULT,
  L2A_DEFAULT_CLASS_A,
  L2A_LORA,
  L2A_SIGFOX,
} l2a_technology_t;

/**
 * @brief Declaration of callbacks called by the layer. They must be defined by
 * the client code, and are provided to the layer initialization function in an
 * array.
 *
 */

/**
 * @brief Callback used to signal that the layer requires processing. The
 * callback must set a flag that is then checked by the client code main loop.
 *
 * When the main loop sees that the flag is set, it must call l2a_process().
 *
 * @note Implementation is mandatory.
 */
typedef void (*l2a_processing_required_t)(void);

/**
 * @brief Callback used to return the result of a transmission request. The
 * callback provides the status of the request (success or error) and, in case
 * of error, a value that depends on the layer two. In case of success, error
 * value is undefined.
 *
 * @note Implementation is mandatory.
 *
 * @param[in] status status of the request:
 *   - L2A_SUCCESS: data successfully transmitted
 *   - L2A_L2_ERROR: error in transmission
 * @param[in] error additional information in case of error, depending on layer
 * two
 */
typedef void (*l2a_transmission_result_t)(l2a_status_t status, uint16_t error);

/**
 * @brief Callback used to return received data. The buffer containing received
 * data is the one provided at initialization time. It's up to the client code
 * to save received data, if required. The L2A layer must guarantee that no
 * write operation to the buffer will be performed by the layer until this
 * callback returns. This could lead to reception overrun and message loss if
 * reception throughput is high and callback execution takes too long.
 *
 * @note Implementation is mandatory.
 *
 * @param[in] size size in bytes of received data
 * @param[in] status:
 *   - L2A_SUCCESS: success, received data can be used
 *   - L2A_BUFFER_ERR: receive buffer is too small, received data
 *         must be ignored
 *   - L2A_OVERRUN_ERR: receive overrun, received data must be ignored
 *   - L2A_L2_ERROR: error in reception
 */
typedef void (*l2a_data_received_t)(uint16_t size, l2a_status_t status);

/**
 * @brief Callback used to inform that connectivity is lost (e.g. the device is
 * out of network coverage).
 *
 * @note Implementation is optional.
 */
typedef void (*l2a_connectivity_lost_t)(void);

/**
 * @brief Callback used to inform that connectivity is available (e.g. joined,
 * for LoRaWAN). This callback is called at least once after layer
 * initialization, as soon as the device can exchange data with a remote
 * application through the network.
 *
 * @note Implementation is mandatory.
 */
typedef void (*l2a_connectivity_available_t)(void);

/**
 * List of callbacks, for layer initialization.
 */
typedef struct
{
  l2a_processing_required_t processing_required;
  l2a_transmission_result_t transmission_result;
  l2a_data_received_t data_received;
  l2a_connectivity_lost_t connectivity_lost;
  l2a_connectivity_available_t connectivity_available;
} l2a_callbacks_t;

/**
 * @brief This function initializes L2A layer.
 *
 * All mandatory callbacks must be provided. An optional callback set to NULL
 * means that the callback is not available.
 *
 * @note Implementation is mandatory.
 *
 * @param[in] pp_callbacks callbacks
 * @param[in] p_receive_buffer buffer allocated by the client code used to store
 * received data
 * @param[in] receive_buffer_size size of the receive buffer
 *
 * @return status of the initialization:
 *   - L2A_SUCCESS: success
 *   - L2A_REQ_CALLBACK_ERR: a mandatory callback is not defined
 */
l2a_status_t l2a_initialize(const l2a_callbacks_t *pp_callbacks,
                            uint8_t *p_receive_buffer,
                            uint16_t receive_buffer_size);

/**
 * @brief This function retrieves the L2 technology used for the transmission.
 * This information is needed to determine the SCHC Technology profile used for
 * the transmission and fragmentation.
 *
 * @note Implementation is mandatory.
 *
 * @return the L2 technology
 *  - L2A_DEFAULT: use default SCHC profile
 *  - L2A_LORA: use LoRa SCHC technology profile
 *  - L2A_SIGFOX: use Sigfox technology profile
 *  - L2A_BCDMA: use B-CDMA technology profile
 */
l2a_technology_t l2a_get_technology(void);

/**
 * @brief This function requests a transmission of data. It returns immediately,
 * with a status that informs whether the request has been recorded with success
 * or not.
 *
 * The buffer containing data to be sent must be kept available until the
 * l2a_transmission_result_t callback is called.
 *
 * If a transmission request is already active, an error is returned.
 *
 * Final result of the transmission will be returned by the
 * l2a_transmission_result_t callback.
 *
 * When the data size is 1 bytes and the value 0x00, it corresponds to the empty
 * frame of the L2 technology used. It is up to the integrator to send the
 * corresponding empty frame according to the L2 technology.
 *
 * @note Implementation is mandatory.
 *
 * @param[in] p_data buffer containing data to be sent
 * @param[in] data_size size in bytes of data to be transmitted
 *
 * @return status of the request:
 * - L2A_SUCCESS: success
 * - L2A_L2_ERROR: L2 did not accept request
 * - L2A_CONNECT_ERR: connectivity is not available, request ignored
 * - L2A_BUSY_ERR: a transmission request is already active, request ignored
 * - L2A_REQ_CALLBACK_ERR: required callback not defined
 * - L2A_INTERNAL_ERR: can't be used due to an internal error
 */
l2a_status_t l2a_send_data(const uint8_t *p_data, uint16_t data_size);

/**
 * @brief This function returns the MTU (maximum size in bytes) of data that
 * can be sent at next transmission.
 *
 * @note Implementation is mandatory, but it could be that this information is
 * not available for some layer two implementations. In this case, the function
 * must return 0.
 *
 * @return maximum size in bytes of data that can be sent
 */
uint16_t l2a_get_mtu(void);

/**
 * @brief This function assigns to the input parameter the address of the buffer
 * that contains the device IID.
 *
 * @param[in] dev_iid buffer to be set with the address of the device IID buffer
 *
 * @note Implementation is mandatory, but it could be that this information is
 * not available for some layer two implementations or the derivation function
 * fails due to some reason. In these cases, the function must return false.
 *
 * @return status:
 * - true: success
 * - false: error
 */
bool l2a_get_dev_iid(uint8_t **dev_iid);

/**
 * @brief This function returns the time in ms to wait for before requesting
 * another transmission. It must be called right after the
 * l2a_transmission_result_t callback has been called.
 *
 * @note Implementation is mandatory
 *
 * @param[in] data_size size in bytes of data which has just been transmitted.
 * If data_size is set to 0, data size of previously sent data is used
 *
 * @return delay in ms before the next transmission window, UINT32_MAX
 * if error.
 */
uint32_t l2a_get_next_tx_delay(uint16_t data_size);

/**
 * @brief This function performs layer processing, when some has to be done. It
 * must be called at least every time l2a_processing_required_t callback
 * has been called. It must not be called from the callback.
 *
 * @note Implementation is mandatory.
 *
 * @return status:
 * - L2A_SUCCESS: success
 * - L2A_INTERNAL_ERR: internal error
 */
l2a_status_t l2a_process(void);

#endif /* FULLSDK_L2A_H_ */

