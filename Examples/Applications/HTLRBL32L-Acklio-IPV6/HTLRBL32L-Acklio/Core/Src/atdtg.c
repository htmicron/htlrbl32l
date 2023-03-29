/**
 * @copyright 2021-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * @author Flavien Moullec flavien@ackl.io
 *
 * @brief Implementation of AT SCHC commands for Datagram layer
 */

#include <ctype.h>
#include <string.h>

#include "atdtg.h"
#include "fullsdkdtg.h"
#include "fullsdkextapi.h"
#include "helpers.h"
#include "tiny_sscanf.h"
#include "HT_gatt_db.h"

#ifndef NB_MAX_SOCKET
// By default, we support only one socket with AT command module.
#define NB_MAX_SOCKET 1
#endif

// Size of transmission/reception buffers.
#define APP_RECEIVE_MAX_LENGTH MAX_PAYLOAD_SIZE
#define APP_TRANSMISSION_MAX_LENGTH MAX_PAYLOAD_SIZE

#define MAX_IPV6_ADDRESS_STR_LEN 39
#define MAX_IPV4_ADDRESS_STR_LEN 15

#define AT_EXTSENDB "+SCHC=SENDB"
#define AT_EXTSEND "+SCHC=SEND"
#define AT_SOCKET "+SCHC=SOCKET"
#define AT_BIND "+SCHC=BIND"
#define AT_CLOSE "+SCHC=CLOSE"

extern volatile last_downlink_t last_downlink;


enum
{
  FREE = 0,
  IN_USE = 1
};

const at_command_t at_dtg_api_command[NB_DTG_API_AT_COMMANDS] = {
    {
        .string = AT_EXTSENDB,
        .size_string = sizeof(AT_EXTSENDB) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_EXTSENDB ": Sends binary data through FullSDK\n",
#endif
        .get = at_return_error,
        .set = at_ext_send_b,
        .run = at_return_error,
    },

    {
        .string = AT_EXTSEND,
        .size_string = sizeof(AT_EXTSEND) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_EXTSEND ": Sends data through FullSDK\n",
#endif
        .get = at_return_error,
        .set = at_ext_send,
        .run = at_return_error,
    },

    {
        .string = AT_SOCKET,
        .size_string = sizeof(AT_SOCKET) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_SOCKET ": Creates a datagram socket\n",
#endif
        .get = at_return_error,
        .set = at_return_error,
        .run = at_socket,
    },

    {
        .string = AT_BIND,
        .size_string = sizeof(AT_BIND) - 1,
#ifndef NO_HELP
        .help_string =
            "AT" AT_BIND
            ": Binds host IP address and port to a datagram socket\n",
#endif
        .get = at_return_error,
        .set = at_bind,
        .run = at_return_error,
    },

    {
        .string = AT_CLOSE,
        .size_string = sizeof(AT_CLOSE) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_CLOSE ": Closes a datagram socket\n",
#endif
        .get = at_return_error,
        .set = at_close,
        .run = at_return_error,
    },
};

typedef struct
{
  dtg_socket_t *socket;
  uint8_t id;
  bool status;
  uint8_t rx_buf[APP_RECEIVE_MAX_LENGTH];
  uint8_t tx_buf[APP_TRANSMISSION_MAX_LENGTH];
} socket_ctx_t;

static socket_ctx_t sockets[NB_MAX_SOCKET];

/**
 * @brief IPv6 Address and port for FullSDK
 */
dtg_sockaddr_t sockaddr;

static uint16_t parse_ipv6(const char *addrstr, uint8_t *_address,
                           uint16_t _address_size)
{
  uint16_t accumulator = 0;
  uint8_t colon_count = 0;
  uint8_t pos = 0;
  uint16_t last_char_idx = 0;

  // Step 1: look for position of ::, and count colons after it
  for (uint8_t i = 1; i <= MAX_IPV6_ADDRESS_STR_LEN; i++)
  {
    if (addrstr[i] == ':')
    {
      if (addrstr[i - 1] == ':')
      {
        // Double colon!
        colon_count = 14;
      }
      else if (colon_count)
      {
        // Count backwards the number of colons after the ::
        colon_count -= 2;
      }
    }
    else if (addrstr[i] == ',')
      break;
  }

  // Step 2: convert from ascii to binary
  for (uint8_t i = 0; i <= MAX_IPV6_ADDRESS_STR_LEN && pos < 16; i++)
  {
    if (addrstr[i] == ':' || addrstr[i] == ',')
    {
      _address[pos] = accumulator >> 8;
      _address[pos + 1] = accumulator;
      accumulator = 0;

      if (colon_count && i && addrstr[i - 1] == ':')
      {
        pos = colon_count;
      }
      else
      {
        pos += 2;
      }
    }
    else
    {
      int8_t val = asciiHexToInt(addrstr[i]);
      if (val == -1)
      {
        // Not hex or colon: fail
        return 0;
      }
      else
      {
        accumulator <<= 4;
        accumulator |= val;
      }
    }

    if (addrstr[i] == ',')
    {
      last_char_idx = i;
      break;
    }
  }

  // Success
  return last_char_idx;
}

static uint16_t parse_ipv4(const char *addrstr, uint8_t *_address,
                           uint16_t _address_size)
{
  uint16_t last_char_idx = 0;

  // Step 1: look for position of,.
  for (uint8_t i = 1; i <= MAX_IPV4_ADDRESS_STR_LEN; i++)
  {
    if (addrstr[i] == ',')
    {
      last_char_idx = i;
      break;
    }
  }

  // Convert address to integer
  char c;
  c = *addrstr;
  unsigned int integer = 0;
  int val;
  int i, j = 0;
  for (j = 0; j < 4 && c != '\0'; j++)
  {
    if (!isdigit(c))
    { // first char is 0
      return 0;
    }
    val = 0;
    for (i = 0; i < 3; i++)
    {
      if (isdigit(c))
      {
        val = (val * 10) + (c - '0');
        c = *++addrstr;
      }
      else
        break;
    }
    if (val < 0 || val > 255)
    {
      return 0;
    }
    integer = (integer << 8) | val;
    c = *++addrstr;
  }

  _address[0] = (uint8_t)(integer >> 24);
  _address[1] = (uint8_t)(integer >> 16);
  _address[2] = (uint8_t)(integer >> 8);
  _address[3] = (uint8_t)integer;

  // Success
  return last_char_idx;
}

static dtg_status_t fullsdk_socket(uint8_t *socket_id)
{
  if (!join_flag)
  {
    return DTG_CONN_ERR;
  }

  for (uint8_t i = 0; i < NB_MAX_SOCKET; i++)
  {
    socket_ctx_t *socket_ctx = &sockets[i];
    if (sockets[i].status == FREE)
    {
      socket_ctx->socket =
          dtg_socket(socket_ctx->rx_buf, APP_RECEIVE_MAX_LENGTH,
                     socket_ctx->tx_buf, APP_TRANSMISSION_MAX_LENGTH);
      if (socket_ctx->socket == DTG_INVALID_SOCKET)
      {
        APP_PRINTF("=> fullsdk_socket - socket %d creation error\n",
                  socket_ctx->id);
        return DTG_ERROR;
      }

      // Update  socket info.
      socket_ctx->status = IN_USE;
      socket_ctx->id = i;
      *socket_id = i;

      return DTG_SUCCESS;
    }
  }

  // No socket available.
  return DTG_NO_SOCKET_ERR;
}

static dtg_status_t fullsdk_bind(uint8_t socket_id, dtg_sockaddr_t sockaddr)
{
  if (!join_flag)
  {
    return DTG_CONN_ERR;
  }

  if (socket_id >= NB_MAX_SOCKET)
  {
    return DTG_NO_SOCKET_ERR;
  }

  socket_ctx_t *socket_ctx = &sockets[socket_id];

  // Socket is not allocated.
  if (socket_ctx->status != IN_USE)
  {
    return DTG_NO_SOCKET_ERR;
  }

  // Bind the socket.
  return dtg_bind(socket_ctx->socket, &sockaddr);
}

static dtg_status_t fullsdk_close(uint8_t socket_id)
{
  if (!join_flag)
  {
    return DTG_CONN_ERR;
  }

  if (socket_id >= NB_MAX_SOCKET)
  {
    return DTG_NO_SOCKET_ERR;
  }

  socket_ctx_t *socket_ctx = &sockets[socket_id];

  // Socket is not allocated.
  if (socket_ctx->status != IN_USE)
  {
    return DTG_NO_SOCKET_ERR;
  }

  // Deallocate socket.
  socket_ctx->status = FREE;

  return dtg_close(socket_ctx->socket);
}

static dtg_status_t fullsdk_send(uint8_t socket_id, const uint8_t *p_data,
                                 uint16_t data_size, dtg_sockaddr_t sockaddr)
{
  if (!join_flag)
  {
    return DTG_CONN_ERR;
  }

  if (socket_id >= NB_MAX_SOCKET)
  {
    return DTG_NO_SOCKET_ERR;
  }

  socket_ctx_t *socket_ctx = &sockets[socket_id];

  // Socket is not allocated.
  if (socket_ctx->status != IN_USE)
  {
    return DTG_NO_SOCKET_ERR;
  }

  return dtg_sendto(socket_ctx->socket, p_data, data_size, &sockaddr);
}

static void dtg_transmission_result(const dtg_socket_t *socket,
                                    dtg_status_t status, uint16_t error)
{
  for (uint8_t i = 0; i < NB_MAX_SOCKET; i++)
  {
    socket_ctx_t *socket_ctx = &sockets[i];
    if (socket_ctx->socket == socket)
    {
      if (status == DTG_SUCCESS)
      {
        AT_PRINTF("+SENDOK,%d\n", socket_ctx->id);
      }
      else
      {
        AT_PRINTF("+SENDFAIL:%d,%d,%d\n", socket_ctx->id, status, error);
      }
      return;
    }
  }

  // We drop the event as there is no socket matching.
}

static void dtg_data_received(const dtg_socket_t *socket, uint8_t *p_buffer,
                              uint16_t data_size,
                              const dtg_sockaddr_t *p_remote,
                              dtg_status_t status)
{
  for (uint8_t i = 0; i < NB_MAX_SOCKET; i++)
  {
    socket_ctx_t *socket_ctx = &sockets[i];
    if (socket_ctx->socket == socket)
    {

      if (status == DTG_SUCCESS)
      {
    	last_downlink.size=data_size;
    	memcpy(last_downlink.payload, p_buffer,data_size);


        AT_PRINTF("+RECVOK,%d:", socket_ctx->id);
        for (uint16_t i = 0; i < data_size; i++)
        {
          //AT_PRINTF("%02X", p_buffer[i]);
        	AT_PRINTF("%02X",last_downlink.payload[i]);

        }
        AT_PRINTF("\n");
      }
      else
      {
        AT_PRINTF("+RECVFAIL:%d,%d\n", socket_ctx->id, status);
      }
      return;
    }
  }

  // We drop the event as there is no socket matching.
}

static dtg_status_t fullsdk_dtg_init(void)
{
  // Initialize DTG interface
  dtg_callbacks_t dtg_callbacks = {dtg_transmission_result, dtg_data_received};

  // Clear sockets context.
  memset((void *)&sockets, 0, sizeof(socket_ctx_t));

  dtg_status_t status = dtg_initialize(&dtg_callbacks);
  if (status != DTG_SUCCESS)
  {
    return status;
  }

  sdk_init = true;

  return DTG_SUCCESS;
}

at_status_t at_socket(const char *param, uint8_t *error)
{
  uint8_t socket_id;

  if (!sdk_init)
  {
    // Initialize the Datagram API only once.
    dtg_status_t status = fullsdk_dtg_init();
    if (status != DTG_SUCCESS)
    {
      *error = status;
      return AT_SCHC_DTG_ERROR;
    }
  }

  dtg_status_t status = fullsdk_socket(&socket_id);
  if (status != DTG_SUCCESS)
  {
    *error = status;
    return AT_SCHC_DTG_ERROR;
  }
  print_d(socket_id);
  return AT_OK;
}

at_status_t at_close(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint8_t socket_id;

  switch (buf[0])
  {
    case '0':
      socket_id = 0;
      break;
    case '1':
      socket_id = 1;
      break;
    default:
      return AT_PARAM_ERROR;
  }

  dtg_status_t status = fullsdk_close(socket_id);
  if (status != DTG_SUCCESS)
  {
    *error = status;
    return AT_SCHC_DTG_ERROR;
  }
  return AT_OK;
}

at_status_t at_ext_send_b(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t buf_size = strlen(param);
  int pos = 0;
  uint16_t last_char_idx;
  uint16_t size = 0;
  char hex[3];
  uint8_t socket_id;

  memset(sockaddr.addr, 0, sizeof(sockaddr.addr));

  switch (buf[0])
  {
    case '0':
      socket_id = 0;
      break;
    case '1':
      socket_id = 1;
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

  // Fetch network protocol.
  mgt_net_protocol_t protocol;
  mgt_status_t mgt_status = mgt_get_network_protocol(&protocol);
  if (mgt_status != MGT_SUCCESS)
  {
    *error = mgt_status;
    return AT_SCHC_MGT_ERROR;
  }

  switch (protocol)
  {
    case MGT_NET_IPV6:
      last_char_idx = parse_ipv6(buf, sockaddr.addr, sizeof(sockaddr.addr));
      break;
    case MGT_NET_IPV4:
      last_char_idx = parse_ipv4(buf, sockaddr.addr, sizeof(sockaddr.addr));
      break;
    default:
      return AT_PARAM_ERROR;
  }
  if (last_char_idx == 0)
  {
    return AT_PARAM_ERROR;
  }
  buf += last_char_idx;
  buf_size -= last_char_idx;

  if (buf[0] != ',')
  {
    return AT_PARAM_ERROR;
  }
  buf++;
  buf_size--;

  uint32_t fport = 0;
  if (tiny_sscanf(buf, "%u", &fport) != 1)
  {
    return AT_PARAM_ERROR;
  }
  if (fport > 65535)
  {
    return AT_PARAM_ERROR;
  }
  sockaddr.port[0] = (((uint16_t)fport) & 0xFF00) >> 8;
  sockaddr.port[1] = ((uint16_t)fport) & 0x00FF;

  pos = get_int_len(fport);
  buf += pos;
  buf_size -= pos;

  if (buf[0] != ',')
  {
    return AT_PARAM_ERROR;
  }
  buf++;
  buf_size--;

  if (buf_size == 0)
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

  dtg_status_t status =
      fullsdk_send(socket_id, (const uint8_t *)buf, size, sockaddr);
  if (status != DTG_SUCCESS)
  {
    *error = status;
    return AT_SCHC_DTG_ERROR;
  }
  return AT_OK;
}

at_status_t at_ext_send(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t buf_size = strlen(param);
  int pos = 0;
  uint16_t last_char_idx;
  uint8_t socket_id;

  memset(sockaddr.addr, 0, sizeof(sockaddr.addr));

  switch (buf[0])
  {
    case '0':
      socket_id = 0;
      break;
    case '1':
      socket_id = 1;
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

  // Fetch network protocol.
  mgt_net_protocol_t protocol;
  mgt_status_t mgt_status = mgt_get_network_protocol(&protocol);
  if (mgt_status != MGT_SUCCESS)
  {
    *error = mgt_status;
    return AT_SCHC_MGT_ERROR;
  }

  switch (protocol)
  {
    case MGT_NET_IPV6:
      last_char_idx = parse_ipv6(buf, sockaddr.addr, sizeof(sockaddr.addr));
      break;
    case MGT_NET_IPV4:
      last_char_idx = parse_ipv4(buf, sockaddr.addr, sizeof(sockaddr.addr));
      break;
    default:
      return AT_PARAM_ERROR;
  }
  if (last_char_idx == 0)
  {
    return AT_PARAM_ERROR;
  }
  buf += last_char_idx;
  buf_size -= last_char_idx;

  if (buf[0] != ',')
  {
    return AT_PARAM_ERROR;
  }
  buf++;
  buf_size--;

  uint32_t fport = 0;
  if (tiny_sscanf(buf, "%u", &fport) != 1)
  {
    return AT_PARAM_ERROR;
  }
  if (fport > 65535)
  {
    return AT_PARAM_ERROR;
  }
  sockaddr.port[0] = (((uint16_t)fport) & 0xFF00) >> 8;
  sockaddr.port[1] = ((uint16_t)fport) & 0x00FF;

  pos = get_int_len(fport);
  buf += pos;
  buf_size -= pos;

  if (buf[0] != ',')
  {
    return AT_PARAM_ERROR;
  }
  buf++;
  buf_size--;

  if (buf_size == 0)
  {
    return AT_PARAM_ERROR;
  }

  dtg_status_t status =
      fullsdk_send(socket_id, (const uint8_t *)buf, buf_size, sockaddr);
  if (status != DTG_SUCCESS)
  {
    *error = status;
    return AT_SCHC_DTG_ERROR;
  }
  return AT_OK;
}

at_status_t at_bind(const char *param, uint8_t *error)
{
  const char *buf = param;
  uint16_t lastCharIdx;
  uint8_t socket_id;

  memset(sockaddr.addr, 0, sizeof(sockaddr.addr));

  switch (buf[0])
  {
    case '0':
      socket_id = 0;
      break;
    case '1':
      socket_id = 1;
      break;
    default:
      return AT_PARAM_ERROR;
  }
  buf++;

  if (buf[0] != ',')
  {
    return AT_PARAM_ERROR;
  }
  buf++;

  // Fetch network protocol.
  mgt_net_protocol_t protocol;
  mgt_status_t mgt_status = mgt_get_network_protocol(&protocol);
  if (mgt_status != MGT_SUCCESS)
  {
    *error = mgt_status;
    return AT_SCHC_MGT_ERROR;
  }

  switch (protocol)
  {
    case MGT_NET_IPV6:
      lastCharIdx = parse_ipv6(buf, sockaddr.addr, sizeof(sockaddr.addr));
      break;
    case MGT_NET_IPV4:
      lastCharIdx = parse_ipv4(buf, sockaddr.addr, sizeof(sockaddr.addr));
      break;
    default:
      return AT_PARAM_ERROR;
  }
  if (lastCharIdx == 0)
  {
    return AT_PARAM_ERROR;
  }
  buf += lastCharIdx;
  if (buf[0] != ',')
  {
    return AT_PARAM_ERROR;
  }
  buf++;
  uint32_t fport = 0;
  if (tiny_sscanf(buf, "%u", &fport) != 1)
  {
    return AT_PARAM_ERROR;
  }
  if (fport > 65535)
  {
    return AT_PARAM_ERROR;
  }
  sockaddr.port[0] = (((uint16_t)fport) & 0xFF00) >> 8;
  sockaddr.port[1] = ((uint16_t)fport) & 0x00FF;

  dtg_status_t status = fullsdk_bind(socket_id, sockaddr);
  if (status != DTG_SUCCESS)
  {
    *error = status;
    return AT_SCHC_DTG_ERROR;
  }
  return AT_OK;
}
