/**
 * @copyright 2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief Implementation of AT SCHC commands without template management
 */

#include "atmgt.h"
#include "fullsdkextapi.h"
#include "fullsdkl2.h"
#include "fullsdkschc.h"
#include "helpers.h"
#include "tiny_sscanf.h"

at_status_t at_set_tpl(const char *param, uint8_t *error)
{
  return AT_NOT_IMPLEMENTED;
}

at_status_t at_clear_tpl_params(const char *param, uint8_t *error)
{
  return AT_NOT_IMPLEMENTED;
}

at_status_t at_get_tpl_id(const char *param, uint8_t *error)
{
  return AT_NOT_IMPLEMENTED;
}

at_status_t at_get_nb_tpl_params(const char *param, uint8_t *error)
{
  return AT_NOT_IMPLEMENTED;
}

at_status_t at_set_payload_rules(const char *param, uint8_t *error)
{
  return AT_NOT_IMPLEMENTED;
}