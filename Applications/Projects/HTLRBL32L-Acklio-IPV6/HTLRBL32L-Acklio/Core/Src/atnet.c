/**
 * @copyright 2021-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief Implementation of AT SCHC commands for Network layer
 */

#include <string.h>

#include "atnet.h"
#include "fullsdkextapi.h"
#include "fullsdkmgt.h"
#include "fullsdknet.h"
#include "helpers.h"
#include "tiny_sscanf.h"

#define AT_SCHC_SENDB "+SCHC=SENDB"

static net_status_t fullsdk_net_init(void);

const at_command_t at_net_api_command[NB_NET_API_AT_COMMANDS] = {{
    .string = AT_SCHC_SENDB,
    .size_string = sizeof(AT_SCHC_SENDB) - 1,
#ifndef NO_HELP
    .help_string = "AT" AT_SCHC_SENDB ": Sends raw data through FullSDK\n",
#endif
    .get = at_return_error,
    .set = at_send_raw_binary_data,
    .run = at_return_error,
}};

at_status_t at_send_raw_binary_data(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t buf_size = strlen(param);
  uint16_t size = 0;
  char hex[3];

  if (!join_flag)
  {
    *error = NET_L2_ERR;
    return AT_SCHC_NET_ERROR;
  }

  if (!sdk_init)
  {
    // Initialize the Network API only once.
    net_status_t status = fullsdk_net_init();
    if (status != NET_SUCCESS)
    {
      *error = status;
      return AT_SCHC_NET_ERROR;
    }
  }

  if (buf_size < 2)
  {
    return AT_PARAM_ERROR;
  }

  hex[2] = 0;
  while (buf_size > 1)
  {
    hex[0] = buf[size * 2];
    hex[1] = buf[size * 2 + 1];
    if (tiny_sscanf(hex, "%hhx", &buf[size]) != 1)
    {
      return AT_PARAM_ERROR;
    }
    size++;
    buf_size -= 2;
  }

  net_status_t status = net_sendto((const uint8_t *)buf, size);
  if (status != NET_SUCCESS)
  {
    *error = status;
    return AT_SCHC_NET_ERROR;
  }
  return AT_OK;
}

static void net_transmission_result(net_status_t status, uint16_t error)
{
  if (status != NET_SUCCESS)
  {
    AT_PRINTF("+SENDFAIL,%d,%d\n", status, error);
    return;
  }

  AT_PRINTF("+SENDOK\n");
}

static void net_data_received(const uint8_t *buffer, uint16_t data_size,
                              net_status_t status)
{
  if (status != NET_SUCCESS)
  {
    AT_PRINTF("+RECVFAIL,%d\n", status);
    return;
  }

  AT_PRINTF("+RECVOK,");
  for (uint16_t i = 0; i < data_size; i++)
  {
    AT_PRINTF("%02X", buffer[i]);
  }
  AT_PRINTF("\n");
}

static net_status_t fullsdk_net_init(void)
{
  // Initialize NET interface.
  net_callbacks_t net_callbacks = {net_transmission_result, net_data_received};

  net_status_t status = net_initialize(&net_callbacks);
  if (status != NET_SUCCESS)
  {
    return status;
  }

  sdk_init = true;

  return NET_SUCCESS;
}
