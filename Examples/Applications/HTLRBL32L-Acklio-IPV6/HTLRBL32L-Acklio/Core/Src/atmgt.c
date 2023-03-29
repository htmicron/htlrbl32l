/**
 * @copyright 2021-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief Implementation of AT SCHC commands for Management layer
 */

#include "atmgt.h"
#include "fullsdkextapi.h"
#include "fullsdkl2.h"
#include "fullsdkschc.h"
#include "helpers.h"
#include "tiny_sscanf.h"


#include "main.h"

#define MAX_PAYLOAD_SIZE 1024
#define MAX_MTU_SIZE 255

// Memory block size provided to mgt_initialize
#define MEM_BLOCK_SIZE                                                         \
  (MAX_MTU_SIZE * 4u + (MAX_PAYLOAD_SIZE + MGT_PROTO_SIZE) * 4u)
static uint8_t mgt_mem_block[MEM_BLOCK_SIZE];

static bool mgt_process_request = false;



// Timers
static timer_obj_t sdk_timers[6];

// Defined in at.c.
extern bool join_flag;

extern volatile uint8_t nwk_joined;
extern volatile uint8_t synced;

// Callbacks for timers
static void sdk_timer_1_event(void *context)
{
  mgt_timer_timeout(0);
}

static void sdk_timer_2_event(void *context)
{
  mgt_timer_timeout(1);
}

static void sdk_timer_3_event(void *context)
{
  mgt_timer_timeout(2);
}

static void sdk_timer_4_event(void *context)
{
  mgt_timer_timeout(3);
}

static void sdk_timer_5_event(void *context)
{
  mgt_timer_timeout(4);
}

static void sdk_timer_6_event(void *context)
{
  mgt_timer_timeout(5);
}

static void mgt_start_timer(uint8_t id, uint32_t duration)
{
  platform_timer_set_duration_start(&sdk_timers[id], duration);
  platform_timer_start(&sdk_timers[id]);
}

static void mgt_stop_timer(uint8_t id)
{
  platform_timer_stop(&sdk_timers[id]);
}

static void mgt_bootstrap_result(mgt_status_t state)
{
  if (state == MGT_SUCCESS)
  {
    AT_PRINTF("+SYNCOK\n");
    synced = true;
  }
  else
  {
    AT_PRINTF("+SYNCFAIL,%d\n", state);
  }
}

static void mgt_connectivity_state(mgt_status_t state)
{
  if (state == MGT_SUCCESS)
  {
    AT_PRINTF("+JOINED\n");
    join_flag = true;
    nwk_joined = true;
  }
}

static void mgt_processing_required(void)
{
  mgt_process_request = true;
}

bool fullsdk_is_busy(void)
{
  return mgt_process_request;
}

mgt_status_t fullsdk_mgt_init(void)
{
  platform_timer_add(&sdk_timers[0], 0, sdk_timer_1_event, NULL);
  platform_timer_add(&sdk_timers[1], 1, sdk_timer_2_event, NULL);
  platform_timer_add(&sdk_timers[2], 2, sdk_timer_3_event, NULL);
  platform_timer_add(&sdk_timers[3], 3, sdk_timer_4_event, NULL);
  platform_timer_add(&sdk_timers[4], 4, sdk_timer_5_event, NULL);
  platform_timer_add(&sdk_timers[5], 5, sdk_timer_6_event, NULL);

  // Initialize MGT layer.
  mgt_callbacks_t callbacks = {mgt_processing_required, mgt_connectivity_state,
                               mgt_start_timer, mgt_stop_timer,
                               mgt_bootstrap_result};
  mgt_status_t status =
      mgt_initialize(&callbacks, mgt_mem_block, MEM_BLOCK_SIZE, MAX_MTU_SIZE,
                     MAX_PAYLOAD_SIZE);
  if (status != MGT_SUCCESS)
  {
    return status;
  }

  return MGT_SUCCESS;
}

void fullsdk_process(void)
{
  if (!join_flag)
  {
    return;
  }

  if (mgt_process_request)
  {
    mgt_process_request = false;
    mgt_status_t mgt_status = mgt_process();
    if (mgt_status != MGT_SUCCESS)
    {
      AT_PRINTF("=> fullsdk_process - error in mgt_process:%d\n\r", mgt_status);
    }
  }
}

at_status_t at_fullsdk_version_get(const char *param, uint8_t *error)
{
  (void)param;
  AT_PRINTF("%s\n", mgt_get_version());
  return AT_OK;
}

at_status_t at_set_fullsdk_api(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t buf_size = strlen(param);

  if (buf_size != 1)
  {
    return AT_PARAM_ERROR;
  }

  if (sdk_init)
  {
    // It is not possible to change the API after FulLSDK API initialization.
    return AT_ERROR;
  }

  switch (buf[0])
  {
    case 'N':
      dtg_api_enabled = false;
      break;
    case 'D':
      dtg_api_enabled = true;
      break;
    default:
      return AT_PARAM_ERROR;
  }
  return AT_OK;
}

at_status_t at_set_template_params(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t buf_size = strlen(param);
  uint32_t val;
  uint16_t index;

  if (!join_flag)
  {
    *error = MGT_L2A_ERR;
    return AT_SCHC_MGT_ERROR;
  }

  while (buf_size > 1)
  {
    // Extract indexes
    if (tiny_sscanf(buf, "%u", &val) != 1)
    {
      return AT_PARAM_ERROR;
    }
    if (val > 65535)
    {
      return AT_PARAM_ERROR;
    }

    index = (uint16_t)val;
    int pos = get_int_len(val);

    buf += pos;
    buf_size -= pos;

    if (buf[0] != ',')
    {
      return AT_PARAM_ERROR;
    }

    buf++;
    buf_size--;

    // Extract parameter and set the template parameter
    char hex[3] = {0};
    uint8_t size = 0;

    while (buf_size > 1 && buf[2 * size] != ',')
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

    mgt_status_t status = mgt_set_template_param(index, (const uint8_t *)buf, size);
    if (status != MGT_SUCCESS)
    {
      *error = status;
      return AT_SCHC_MGT_ERROR;
    }

    buf += 2 * size;

    // No more parameters
    if (buf_size == 0)
    {
      return AT_OK;
    }

    // We expect a new index, parameter tuple
    if (buf[0] != ',')
    {
      return AT_PARAM_ERROR;
    }

    buf++;
    buf_size--;
  }

  return AT_OK;
}

at_status_t at_get_template_params(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t buf_size = strlen(param);
  uint32_t val;
  uint8_t index;

  uint8_t *value;
  uint16_t value_length;
  int pos;

  while (buf_size > 0)
  {
    // Extract indexes
    if (tiny_sscanf(buf, "%u", &val) != 1)
    {
      return AT_PARAM_ERROR;
    }
    if (val > 255)
    {
      return AT_PARAM_ERROR;
    }

    index = (uint8_t)val;
    pos = get_int_len(val);

    buf += pos;
    buf_size -= pos;

    mgt_status_t status = mgt_get_template_param(index, &value, &value_length);
    if (status != MGT_SUCCESS)
    {
      *error = status;
      return AT_SCHC_MGT_ERROR;
    }

    AT_PRINTF("%d,", index);
    for (uint16_t i = 0; i < value_length; i++)
    {
      AT_PRINTF("%02X", value[i]);
    }
    AT_PRINTF("\n");

    // No more parameters
    if (buf_size == 0)
    {
      return AT_OK;
    }

    // We expect a new index, parameter tuple
    if (buf[0] != ',')
    {
      return AT_PARAM_ERROR;
    }

    buf++;
    buf_size--;
  }

  return AT_OK;
}

at_status_t at_sync(const char *param, uint8_t *error)
{
  if (!join_flag)
  {
    *error = MGT_L2A_ERR;
    return AT_SCHC_MGT_ERROR;
  }

  const char *buf = param;
  uint16_t buf_size = strlen(param);
  uint32_t val;

  // Extract retransmission_delay
  if (tiny_sscanf(buf, "%u", &val) != 1)
  {
    return AT_PARAM_ERROR;
  }

  int pos = get_int_len(val);
  uint32_t retransmission_delay = val;

  buf += pos;
  buf_size -= pos;

  if (buf[0] != ',')
  {
    return AT_PARAM_ERROR;
  }

  buf++;
  buf_size--;

  // Extract max_retrans
  if (tiny_sscanf(buf, "%u", &val) != 1)
  {
    return AT_PARAM_ERROR;
  }
  if (val > 255)
  {
    return AT_PARAM_ERROR;
  }

  uint8_t max_retrans = (uint8_t)val;
  pos = get_int_len(val);

  buf += pos;
  buf_size -= pos;

  // We don't expect parameters anymore
  if (buf_size != 0)
  {
    return AT_PARAM_ERROR;
  }

  *error = mgt_sync_bootstrap(retransmission_delay, max_retrans);
  return *error == MGT_SUCCESS ? AT_OK : AT_SCHC_MGT_ERROR;
}

at_status_t at_schc_conf_poll(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t buf_size = strlen(param);

  char class;
  if (l2_get_class(&class) != L2_SUCCESS)
  {
    return AT_L2_ERROR;
  }

  if (!join_flag || class != 'A')
  {
    *error = MGT_L2A_ERR;
    return AT_SCHC_MGT_ERROR;
  }

  if (buf_size < 3)
  {
    *error = AT_PARAM_ERROR;
    return AT_PARAM_ERROR;
  }

  bool enable = false;
  bool suspend_uplinks = false;

  switch (buf[0])
  {
    case '0':
      enable = false;
      break;
    case '1':
      enable = true;
      break;
    default:
      return AT_PARAM_ERROR;
  }

  buf++;
  buf_size--;
  if (buf[0] != ',')
  {
    return AT_PARAM_ERROR;
  }
  buf++;
  buf_size--;

  switch (buf[0])
  {
    case '0':
      suspend_uplinks = false;
      break;
    case '1':
      suspend_uplinks = true;
      break;
    default:
      return AT_PARAM_ERROR;
  }
  schc_set_polling_status(enable, suspend_uplinks);
  return AT_OK;
}

at_status_t at_schc_trigger_poll(const char *param, uint8_t *error)
{
  if (!join_flag)
  {
    *error = MGT_L2A_ERR;
    return AT_SCHC_MGT_ERROR;
  }

  if ((*error = mgt_trigger_polling()) != MGT_SUCCESS)
  {
    return AT_SCHC_MGT_ERROR;
  }

  return AT_OK;
}

at_status_t at_fullsdk_ip_get(const char *param, uint8_t *error)
{
  (void)param;

  uint8_t ip_address[IP_ADDRESS_MAX_LENGTH_BYTES];

  mgt_status_t status =
      mgt_get_ipv6_address(ip_address, IP_ADDRESS_MAX_LENGTH_BYTES);
  if (status != MGT_SUCCESS)
  {
    *error = status;
    return AT_SCHC_MGT_ERROR;
  }

  print_16_02x_2(ip_address);

  return AT_OK;
}
