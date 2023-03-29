/**
 * @file fullsdkschc.h
 * @copyright 2018-2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Thibaut Artis thibaut.artis@ackl.io
 *
 * @brief API to modify preset fragmentation profiles
 */

#ifndef FULLSDKSCHC_H
#define FULLSDKSCHC_H

#include "fullsdkl2a.h"

/**
 * @brief This function allows to modify the value of the retransmission timer
 * used by the current profile
 *
 * @param[in] rt_exp_time the new value for the retransmission timer
 */
void schc_set_retransmission_timer(uint32_t rt_exp_time);

/**
 * @brief This function allows to modify the value of the inactivity timer
 * used by the current profile
 *
 * @param[in] it_exp_time the new value for the inactivity timer
 */
void schc_set_inactivity_timer(uint32_t it_exp_time);

/**
 * @brief This function allows to activate polling for downlink sessions as well
 * as suspending uplink sessions in the meanwhile
 *
 * @param[in] enable true for enabling, false for disabling
 * @param[in] suspend_uplinks true for enabling, false for disabling
 *
 */
void schc_set_polling_status(bool enable, bool suspend_uplinks);

/**
 * @brief This funtion allows to set the value of the ACK_REQ_DN_OPPORTUNITY
 * value in the computation of the ACK retransmission timer expiration
 * This function is only used with ACKAlways downlink fragmentation mode.
 *
 * @param ack_req_dn_opportunity the new value for ACK_REQ_DN_OPPORTUNITY
 */
void schc_set_schc_ack_req_dn_opportunity(uint8_t ack_req_dn_opportunity);

/**
 * @brief This function allows to set the value of the idle polling timer that
 * is used to create downlink opportunities on quasi-bidirectional links.
 * This function is only used with ACKAlways downlink fragmentation mode.
 *
 * @param time the new value for the polling timer in ms
 */
void schc_set_idle_polling_timer(uint32_t time);

/**
 * @brief This function allows to set the value of the ACK retransmission timer
 * that is used to create downlink opportunities on quasi-bidirectional links.
 * This function is only used with ACKAlways downlink fragmentation mode.
 *
 * @param time the new value for the polling timer in ms
 */
void schc_set_ack_retransmission_timer(uint32_t time);

/**
 * @brief This function allows to set the value of MAX ACK REQUESTS which
 * indicates the number of time a sender will send an ACK before sending an
 * ABORT message
 *
 * @param max_ack_req the new value for MAX ACK REQUESTS
 */
void schc_set_max_ack_req(uint8_t max_ack_req);

#endif // FULLSDKSCHC_H

