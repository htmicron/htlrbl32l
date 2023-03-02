/**
 * @copyright 2021-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief AT SCHC commands for Management layer
 */

#ifndef AT_MGT_H
#define AT_MGT_H

#include <stdbool.h>

#include "at.h"
#include "fullsdkmgt.h"

bool fullsdk_is_busy(void);

mgt_status_t fullsdk_mgt_init(void);

void fullsdk_process(void);

/**
 * @brief Prints the version of the fullsdk running
 * @param Param represented in ASCII format
 * @retval AT_OK
 */
at_status_t at_fullsdk_version_get(const char *param, uint8_t *error);

/**
 * @brief This function selects the SDK API to be used (NET or DTG)
 * @param param API
 * @param error A pointer where an error code can be stored
 * @retval at_status_t
 */
at_status_t at_set_fullsdk_api(const char *param, uint8_t *error);

/**
 * @brief This function allows to add a template
 * @param param template
 * @param error A pointer where an error code can be stored
 * @retval at_status_t
 */
at_status_t at_set_tpl(const char *param, uint8_t *error);

/**
 * @brief This function allows to add payload compression rules
 *
 * @param param rules
 * @param error A pointer where an error code can be stored
 * @return at_status_t
 */
at_status_t at_set_payload_rules(const char *param, uint8_t *error);

/**
 * @brief This function allows to get the ID of the current template
 * @param param
 * @param error A pointer where an error code can be stored
 * @retval at_status_t
 */
at_status_t at_get_tpl_id(const char *param, uint8_t *error);

/**
 * @brief This function allows to get the number of parameters of the current
 * template
 * @param param
 * @param error A pointer where an error code can be stored
 * @retval at_status_t
 */
at_status_t at_get_nb_tpl_params(const char *param, uint8_t *error);

/**
 * @brief This function clear the template parameters
 *
 * @param[in] param not used
 * @param error A pointer where an error code can be stored
 * @return at_status_t
 */
at_status_t at_clear_tpl_params(const char *param, uint8_t *error);

/**
 * @brief This function allows to set a template parameter
 *
 * @param[in] param A list of template parameters (indexes,value)
 * @param error A pointer where an error code can be stored
 * @return at_status_t
 */
at_status_t at_set_template_params(const char *param, uint8_t *error);

/**
 * @brief This function allows to get a template parameter
 *
 * @param[in] param A list of comma separated template parameter indexes
 * @param error A pointer where an error code can be stored
 * @return at_status_t
 */
at_status_t at_get_template_params(const char *param, uint8_t *error);

/**
 * @brief Triggers a synchronization procedure with the IPCore
 * @param param represented in ASCII format
 * @return AT_OK or AT_SCHC_MGT_ERROR
 */
at_status_t at_sync(const char *param, uint8_t *error);

/**
 * @brief Allows to enable/disable class A polling as well as uplink suspension
 *
 * @param param Represented in ASCII format
 * @return AT_OK, AT_SCHC_MGT_ERROR or AT_PARAM_ERROR
 */
at_status_t at_schc_conf_poll(const char *param, uint8_t *error);

/**
 * @brief Triggers class A polling by sending an empty uplink frame
 *
 * @param param Represented in ASCII format
 * @return AT_OK, AT_SCHC_MGT_ERROR or AT_PARAM_ERROR
 */
at_status_t at_schc_trigger_poll(const char *param, uint8_t *error);

/**
 * @brief  Get device IP address
 * @param  String string of the AT command
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_fullsdk_ip_get(const char *param, uint8_t *error);

#endif /* AT_MGT_H */
