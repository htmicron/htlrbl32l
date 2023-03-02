/**
 * @copyright 2021-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief Implementation of AT SCHC commands for template management
 */

#include "atmgt.h"
#include "fullsdkextapi.h"
#include "fullsdkl2.h"
#include "fullsdkschc.h"
#include "helpers.h"
#include "tiny_sscanf.h"

// TODO: put formula of required memory size in function of a given template
// size
#ifndef TPL_MEMORY_SIZE
#define TPL_MEMORY_SIZE 1000
#endif

#ifndef PAYLOAD_MEMORY_SIZE
#define PAYLOAD_MEMORY_SIZE 1500
#endif

static uint8_t tpl_memory_area[TPL_MEMORY_SIZE];
static uint8_t payload_memory_area[PAYLOAD_MEMORY_SIZE];

at_status_t at_get_tpl_id(const char *param, uint8_t *error)
{
  uint8_t id;
  (void)param;

  mgt_status_t status = mgt_get_template_id(&id);
  if (status != MGT_SUCCESS)
  {
    *error = status;
    return AT_SCHC_MGT_ERROR;
  }

  AT_PRINTF("%d\n", id);
  return AT_OK;
}

at_status_t at_get_nb_tpl_params(const char *param, uint8_t *error)
{
  uint8_t nb;
  (void)param;

  mgt_status_t status = mgt_get_nb_template_params(&nb);
  if (status != MGT_SUCCESS)
  {
    *error = status;
    return AT_SCHC_MGT_ERROR;
  }

  AT_PRINTF("%d\n", nb);
  return AT_OK;
}

static bool load_rules(const char *buf, uint16_t buf_size)
{
  char hex[3] = {0};
  uint16_t size = 0;

  while (buf_size > 1)
  {
    hex[0] = buf[size * 2];
    hex[1] = buf[size * 2 + 1];

    if (tiny_sscanf(hex, "%hhx", &buf[size]) != 1)
    {
      return false;
    }

    size++;
    buf_size -= 2;
  }

  // We don't expect parameters anymore
  if (buf_size != 0)
  {
    return false;
  }
  return true;
}

at_status_t at_set_tpl(const char *param, uint8_t *error)
{

  APP_LOG(TS_OFF, VLEVEL_M,"templateconfig: %s\n",param);
  const char *buf = param;
  //const char *buf ="b1008418960186010101010101818302181c8e880c040102000081410602880d080101000081410002880e140101000081440001234502880f1001010008814200000288100801010000814111028811080101000081414002881218400102000081000288131840010200008101028814184001020000810202881518400102000081030288161001020000810402881710010200008105028818181001010004814200000288181910010100058142000002a4d9";
  uint16_t buf_size = strlen(param);

  APP_LOG(TS_OFF, VLEVEL_M,"buf_size: %d\n",buf_size);
  if (buf_size == 0 || !load_rules(buf, buf_size))
  {
    return AT_PARAM_ERROR;
  }

  // Provision template

  mgt_status_t status = mgt_provision_header_rules(
      (const uint8_t *)buf, buf_size / 2, tpl_memory_area, TPL_MEMORY_SIZE);
  if (status != MGT_SUCCESS)
  {
    *error = status;
    return AT_SCHC_MGT_ERROR;
  }

  return AT_OK;
}

at_status_t at_clear_tpl_params(const char *param, uint8_t *error)
{
  // We just reset the template parameters
  mgt_status_t status = mgt_reset_template_params();
  if (status != MGT_SUCCESS)
  {
    *error = status;
    return AT_SCHC_MGT_ERROR;
  }

  return AT_OK;
}

at_status_t at_set_payload_rules(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t buf_size = strlen(param);

  if (buf_size == 0 || !load_rules(buf, buf_size))
  {
    return AT_PARAM_ERROR;
  }

  // Provision template
  mgt_status_t status = mgt_provision_payload_rules(
      (const uint8_t *)buf, buf_size / 2, payload_memory_area, PAYLOAD_MEMORY_SIZE);
  if (status != MGT_SUCCESS)
  {
    return AT_SCHC_MGT_ERROR;
  }

  return AT_OK;
}
