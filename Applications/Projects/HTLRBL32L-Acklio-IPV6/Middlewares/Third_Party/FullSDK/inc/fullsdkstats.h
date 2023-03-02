/**
 * @file fullsdkstats.h
 * @copyright 2018-2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief FullSDK metrics API
 */

#ifndef FULLSDKSTATS_H
#define FULLSDKSTATS_H

#include <stdint.h>

/**
 * @brief Number of SCHC unfragmented packets transmitted by the library.
 *
 * @return uint32_t counter value
 */
uint32_t stats_schc_packets_tx_counter(void);

/**
 * @brief Number of SCHC unfragmented packets received by the library.
 *
 * @return uint32_t counter value
 */
uint32_t stats_schc_packets_rx_counter(void);

/**
 * @brief Number of SCHC fragments transmitted by the library.
 *
 * @return uint32_t counter value
 */
uint32_t stats_schc_fragments_tx_counter(void);

/**
 * @brief Number of SCHC fragments received by the library.
 *
 * @return uint32_t counter value
 */
uint32_t stats_schc_fragments_rx_counter(void);

/**
 * @brief Number of SCHC ACK transmitted by the library.
 *
 * @return uint32_t counter value
 */
uint32_t stats_schc_ack_tx_counter(void);

/**
 * @brief Number of SCHC ACK received by the library.
 *
 * @return uint32_t counter value
 */
uint32_t stats_schc_ack_rx_counter(void);

/**
 * @brief Reset all the counters to 0.
 */
void stats_reset(void);

#endif // FULLSDKSTATS_H

