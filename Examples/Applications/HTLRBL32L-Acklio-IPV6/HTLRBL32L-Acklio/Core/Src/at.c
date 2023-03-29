/**
 ******************************************************************************
 * @file    at.c
 * @author  MCD Application Team
 * @brief   at command API
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "at.h"
#include "atdtg.h"
#include "atmgt.h"
#include "atnet.h"
#include "fullsdkl2.h"
#include "fullsdkmgt.h"
#include "helpers.h"
#include "platform.h"
#include "tiny_sscanf.h"

/**
 * @brief Max size of the data that can be received
 */
#define MAX_RECEIVED_DATA 1024
/* Private variables ---------------------------------------------------------*/

#define APP_VERSION "1.0.0"

// join_flag is set to true once joined.
bool join_flag = false;
bool sdk_init = false;
bool dtg_api_enabled = false;

/* Exported functions ------------------------------------------------------- */

at_status_t at_return_error(const char *param, uint8_t *error)
{
  return AT_ERROR;
}

at_status_t at_not_implemented_error(const char *param, uint8_t *error)
{
  return AT_NOT_IMPLEMENTED;
}

at_status_t at_reset(const char *param, uint8_t *error)
{
  platform_reset();

  return AT_OK;
}

at_status_t at_DevEUI_get(const char *param, uint8_t *error)
{
  uint8_t *dev_eui;

  dev_eui = l2_get_dev_eui();
  print_8_02x(dev_eui);

  return AT_OK;
}

at_status_t at_DevEUI_set(const char *param, uint8_t *error)
{
  uint8_t dev_eui[8];
  if (tiny_sscanf(param, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &dev_eui[0],
                  &dev_eui[1], &dev_eui[2], &dev_eui[3], &dev_eui[4],
                  &dev_eui[5], &dev_eui[6], &dev_eui[7]) != 8)
  {
    return AT_PARAM_ERROR;
  }

  l2_set_dev_eui(dev_eui);

  return AT_OK;
}

at_status_t at_JoinEUI_get(const char *param, uint8_t *error)
{
  uint8_t *join_eui;

  join_eui = l2_get_join_eui();
  print_8_02x(join_eui);

  return AT_OK;
}

at_status_t at_JoinEUI_set(const char *param, uint8_t *error)
{
  uint8_t join_eui[8];
  if (tiny_sscanf(param, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                  &join_eui[0], &join_eui[1], &join_eui[2], &join_eui[3],
                  &join_eui[4], &join_eui[5], &join_eui[6], &join_eui[7]) != 8)
  {
    return AT_PARAM_ERROR;
  }

  l2_set_join_eui(join_eui);

  return AT_OK;
}

at_status_t at_AppKey_get(const char *param, uint8_t *error)
{
  print_16_02x(l2_get_app_key());

  return AT_OK;
}

at_status_t at_AppKey_set(const char *param, uint8_t *error)
{

  uint8_t app_key[16];

  if (sscanf_16_hhx(param, app_key) != 16)
  {
    return AT_PARAM_ERROR;
  }

  l2_set_app_key(app_key);

  return AT_OK;
}

at_status_t at_ADR_get(const char *param, uint8_t *error)
{
  bool adr;

  if (l2_get_adr(&adr) != L2_SUCCESS)
  {
    return AT_L2_ERROR;
  }

  print_d(adr);

  return AT_OK;
}

at_status_t at_ADR_set(const char *param, uint8_t *error)
{
  switch (param[0])
  {
    case '0':
    case '1':
      l2_set_adr(param[0] - '0');
      break;
    default:
      return AT_PARAM_ERROR;
  }

  return AT_OK;
}

at_status_t at_DataRate_get(const char *param, uint8_t *error)
{
  uint8_t dr;

  if (l2_get_dr(&dr) != L2_SUCCESS)
  {
    return AT_L2_ERROR;
  }

  print_d(dr);

  return AT_OK;
}

at_status_t at_DataRate_set(const char *param, uint8_t *error)
{
  int8_t data_rate;

  if (tiny_sscanf(param, "%hhu", &data_rate) != 1)
  {
    return AT_PARAM_ERROR;
  }
  if (data_rate > 6)
  {
    return AT_PARAM_ERROR;
  }

  l2_set_dr(data_rate);

  return AT_OK;
}

static int8_t convert_string_to_region(const char *param)
{
  for (size_t i = 0; i < L2_MAX_SUPPORTED_REGION; i++)
  {
    if (strcmp(regions[i].str, param) == 0)
    {
      return regions[i].id;
    }
  }

  return -1;
}

static const char *convert_region_to_string(l2_region_id_t region)
{
  for (size_t i = 0; i < L2_MAX_SUPPORTED_REGION; i++)
  {
    if (regions[i].id == region)
    {
      return regions[i].str;
    }
  }

  return NULL;
}

at_status_t at_ActiveRegion_get(const char *param, uint8_t *error)
{
  l2_region_id_t id;
  if (l2_get_active_region(&id) != L2_SUCCESS)
  {
    return AT_L2_ERROR;
  }

  const char *region = convert_region_to_string(id);
  if (region == NULL)
  {
    return AT_L2_ERROR;
  }

  AT_PRINTF("%s\n", region);

  return AT_OK;
}

at_status_t at_ActiveRegion_set(const char *param, uint8_t *error)
{
  int8_t region = convert_string_to_region(param);

  if (region != -1)
  {
    if (l2_set_active_region(region) != L2_SUCCESS)
    {
      return AT_L2_ERROR;
    }

    return AT_OK;
  }

  return AT_ERROR;
}

at_status_t at_Join(const char *param, uint8_t *error)
{
  char class = param[0];
  if ((class != 'A') && (class != 'C'))
  {
    return AT_PARAM_ERROR;
  }
  // The check above ensure that l2_set_class can't return an error.
  // l2_set_class only stores the class.
  l2_set_class(class);

  // Initialize SDK MGT layer.
  mgt_status_t status = fullsdk_mgt_init();
  if (status != MGT_SUCCESS)
  {
    *error = status;
    return AT_SCHC_MGT_ERROR;
  }

  join_flag = true;

  return AT_OK;
}

at_status_t at_version_get(const char *param, uint8_t *error)
{
  AT_PRINTF("ATModem " APP_VERSION " %s\n", l2_get_version());

  return AT_OK;
}
