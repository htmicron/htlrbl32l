/**
 * @file fullsdkmgt.h
 * @copyright 2018-2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Pascal Bodin - pascal@ackl.io
 *
 * @brief Public Management layer interface
 */

#ifndef FULLSDK_MGT_H
#define FULLSDK_MGT_H

#include <stdbool.h>
#include <stdint.h>

#define MGT_PROTO_SIZE 128u

/**
 * Status values that can be returned by layer functions.
 */
typedef enum
{
  MGT_SUCCESS,
  MGT_ERROR,
  MGT_CONN_ERR,
  MGT_MEM_ERR,
  MGT_OPERATION_NOT_SUPPORTED_ERR,
  MGT_L2A_ERR,
  MGT_FRM_ERR,
  MGT_MUX_ERR,
  MGT_SYNC_ERR,
  MGT_CD_ERR,
  MGT_REQ_CALLBACK_ERR,
  MGT_NOT_INIT_ERR,
  MGT_TPL_NOT_INIT_ERR,
  MGT_NETWORK_PROTOCOL_ERR,
  MGT_TPL_CRC_ERR,
  MGT_TPL_PARSER_ERR,
  MGT_TPL_INVALID_PARAM_ID,
  MGT_TPL_INVALID_PARAM,
  MGT_TPL_UNSUPPORTED_STACK_ERR,
  MGT_DTGS_ERR,
} mgt_status_t;

/**
 * @brief Declaration of callbacks called by the layer. They must be defined by
 * the client code, and are provided to the layer initialization function.
 *
 * The implementation of some of them is optional.
 */

/**
 * @brief Callback used to signal that the layer requires processing. The
 * callback must set a flag that is then checked by the client code main loop.
 *
 * When the main loop sees that the flag is set, it must call mgt_process().
 *
 * @note This callback must be defined
 */
typedef void (*mgt_processing_required_t)(void);

/**
 * @brief Callback used to signal that connectivity status changed. Unavailable
 * connectivity means that data can't be sent to a remote host, and data
 * can't be received from a remote host.
 *
 * @note Implementation is mandatory.
 *
 * @param[in] state connectivity state:
 *   - MGT_SUCCESS: connectivity is available now
 *   - MGT_CONN_ERR: connectivity is no more available due L2 connectivity error
 */
typedef void (*mgt_connectivity_state_t)(mgt_status_t state);

/**
 * @brief Callback used to start the timer with the identifier provided as
 * parameter.
 *
 * @param[in] duration expiration time in ms
 * @param[in] id timer identifier
 */
typedef void (*mgt_start_timer_t)(uint8_t id, uint32_t duration);

/**
 * @brief Callback used to stop the timer with the identifier provided as
 * parameter.
 *
 * @param[in] id timer identifier
 */
typedef void (*mgt_stop_timer_t)(uint8_t id);

/**
 * @brief Callback used to signal the result of the synchronization bootstrap
 * phase to the application.
 *
 * @note Implementation is mandatory when mgt_sync_bootstrap function is called.
 *
 * @param[in] state bootstrap state
 *   - MGT_SUCCESS: bootstrap phase succeded
 *   - MGT_SYNC_ERR: bootstrap phase failed
 */
typedef void (*mgt_sync_bootstrap_result_t)(mgt_status_t state);

/**
 * @brief List of callbacks, for layer initialization.
 */
typedef struct
{
  mgt_processing_required_t processing_required;
  mgt_connectivity_state_t connectivity_state;
  mgt_start_timer_t start_timer;
  mgt_stop_timer_t stop_timer;
  mgt_sync_bootstrap_result_t sync_bootstrap_result;
} mgt_callbacks_t;

/**
 * @brief This function initializes the MGT layer.
 *
 * Size of the memory that must be provided should be equal to or bigger than
 * the value calculated with the formula below:
 * ```
 * memory_size = max_mtu_size * 4 + (max_payload_size + MGT_PROTO_SIZE) * n
 * n = 4 if multicast is enabled
 * n = 3 if multicast is disabled
 * ```
 *
 * @param[in] user_callbacks callbacks
 * @param[in] mem_block the memory block that FullSDK can use
 * @param[in] mem_block_size size of the memory block in bytes
 * @param[in] max_mtu_size maximum number of bytes that can be received from or
 * transmitted on the layer 2
 * @param[in] max_payload_size size of the longest payload that will be received
 * or sent
 *
 * @return status of the initialization:
 *   - MGT_SUCCESS: success
 *   - MGT_MEM_ERR: mem_block parameter is NULL
 *   - MGT_L2A_ERR: error return by the L2A layer
 *   - MGT_MUX_ERR: error return by the Mux layer
 *   - MGT_FRM_ERR: error return by the FRM layer
 *   - MGT_SYNC_ERR: error return by the Sync layer
 *   - MGT_CD_ERR: error return by the C/D layer
 *   - MGT_REQ_CALLBACK_ERR: a mandatory callback is not defined
 */

mgt_status_t mgt_initialize(const mgt_callbacks_t *user_callbacks,
                            uint8_t *const mem_block, uint16_t mem_block_size,
                            uint16_t max_mtu_size, uint16_t max_payload_size);

/**
 * @brief This function is used to synchronize the SDK with the SCHC gateway.
 * @note This functionality is optional.
 *
 * @param[in] retransmission_delay delay between each request retransmission (in
 * ms)
 * @param[in] max_retrans maximum number of request retransmission before
 * considering the synchronization has failed
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_SYNC_ERR: error return by the Sync layer
 *   - MGT_FRM_ERR: error return by the FRM layer
 *   - MGT_OPERATION_NOT_SUPPORTED_ERR: operation not supported
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 */
mgt_status_t mgt_sync_bootstrap(uint32_t retransmission_delay,
                                uint8_t max_retrans);

/**
 * @brief This function must be called to activate the polling
 * machanism. This feature can be used on quasi-bidirectional links with a L2
 * technologies where an uplink must be sent to receive a downlink.
 *
 * @param[in] suspend_uplinks suspends uplink transmission until the end of the
 * downlink session.
 */
void mgt_enable_polling(bool suspend_uplinks);

/**
 * @brief This function must be called every time a polling packet has to be
 * sent by the application. This feature can be used on quasi-bidirectional
 * links with a L2 technologies where an uplink must be sent to receive a
 * downlink.
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_L2A_ERR: error in transmission
 *   - MGT_ERROR: error
 *   - MGT_NOT_INIT_ERR: the SDK is not yet initialized
 */
mgt_status_t mgt_trigger_polling(void);

/**
 * @brief This function provides the version of the library.
 *
 * @return pointer to an array providing the version of the library.
 */
const char *mgt_get_version(void);

/**
 * @brief This function must be called by client code when the timer with the
 * corresponding identifier expires.
 * The application should provide 6 timers, meaning the id argument may take a
 * value from 0 up to 5.
 * In case the Secure DTG layer is used then the application should provide 2
 * additional timers, bringing the maximum value the id argument can take up to
 * 7
 *
 * @param[in] timer identifier
 */
void mgt_timer_timeout(uint8_t id);

/**
 * @brief This function performs layer processing, when some has to be done. It
 * must be called at least every time mgt_processing_required_t callback
 * has been called. It must not be called from the callback.
 *
 * @return operation status
 *   - MGT_SUCCESS: success
 *   - MGT_ERROR: layer is in error state, it must be reinitialized
 *   - MGT_L2A_ERR: error return by the L2A layer
 *   - MGT_MUX_ERR: error return by the Mux layer
 *   - MGT_FRM_ERR: error return by the FRM layer
 *   - MGT_SYNC_ERR: error return by the Sync layer
 *   - MGT_CD_ERR: error return by the C/D layer
 */
mgt_status_t mgt_process(void);

#endif /* FULLSDK_MGT_H */

