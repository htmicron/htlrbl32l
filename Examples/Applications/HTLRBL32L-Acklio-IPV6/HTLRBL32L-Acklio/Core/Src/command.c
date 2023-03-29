/**
 ******************************************************************************
 * @file    command.c
 * @author  MCD Application Team
 * @brief   main command driver dedicated to command AT
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
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "at.h"
#include "atdtg.h"
#include "atmgt.h"
#include "atnet.h"

/* Private define ------------------------------------------------------------*/
// We support a payload of 1024 bytes in binary, so 2048 bytes in ASCII.
// Moreover there is at least 62 bytes of AT-command overhead. and the rest is
// the safety margin.
#define CMD_SIZE (2 * MAX_PAYLOAD_SIZE + 256)
#define CIRC_BUFF_SIZE 8
#define HELP_DISPLAY_FLUSH_DELAY 100
#define AT_ERROR_RX_CHAR 0x01

/* AT Command strings. Commands start with AT */
#define AT_RESET "Z"
#define AT_DEUI "+DEUI"
#define AT_APPKEY "+APPKEY"
#define AT_JOINEUI                                                             \
  "+APPEUI" /*to match with V1.0.x specification- For V1.1.x "+APPEUI" will be \
               replaced by "+JOINEUI"*/
#define AT_ADR "+ADR"
#define AT_DR "+DR"
#define AT_REGION "+REGION"
#define AT_JOIN "+JOIN"
#define AT_VER "+VER"

// SCHC AT commands
#define AT_FSDKVER "+SCHC=VERSION"
#define AT_SCHC_API "+SCHC=API"
#define AT_SCHC_TPL_SET "+SCHC=TPL,SET"
#define AT_SCHC_TPL_PAYLOAD_SET "+SCHC=TPLPAYLOAD,SET"
#define AT_SCHC_TPL_GET_ID "+SCHC=TPL,GETID"
#define AT_SCHC_TPLPARAMS_CLR "+SCHC=TPLPARAMS,CLR"
#define AT_SCHC_TPLPARAMS_SET "+SCHC=TPLPARAMS,SET"
#define AT_SCHC_TPLPARAMS_GET "+SCHC=TPLPARAMS,GET"
#define AT_SCHC_TPLPARAMS_NB "+SCHC=TPLPARAMS,NB"
#define AT_SCHC_SYNC "+SCHC=SYNC"
#define AT_SCHC_CONF_POLL "+SCHC=CONF_POLL"
#define AT_SCHC_TRIGGER_POLL "+SCHC=TRG_POLL"
#define AT_GETIP "+SCHC=IP"

/**
 * @brief  Array corresponding to the description of each possible AT Error
 */
static const char *const at_status_description[] = {
    "OK\n",                     /* AT_OK */
    "AT_ERROR\n",               /* AT_ERROR */
    "AT_PARAM_ERROR\n",         /* AT_PARAM_ERROR */
    "AT_TEST_PARAM_OVERFLOW\n", /* AT_TEST_PARAM_OVERFLOW */
    "AT_RX_ERROR\n",            /* AT_RX_ERROR */
    "AT_L2_ERROR\n",            /* AT_L2_ERROR */
    "AT_NOT_IMPLEMENTED\n",     /* AT_NOT_IMPLEMENTED */
    "AT_PLATFORM_ERROR\n",      /* AT_PLATFORM_ERROR */
    "AT_ERROR,1",               /* AT MGT error */
    "AT_ERROR,2",               /* AT DTG error */
    "AT_ERROR,3",               /* AT NET error */
    "error unknown\n",          /* AT_MAX */
};

static void com_error(at_status_t status, uint8_t error)
{
  if (status > AT_MAX)
  {
    status = AT_MAX;
  }

  if (status < AT_SCHC_MGT_ERROR || status == AT_MAX)
  {
    // No secondary error code
    AT_PRINTF(at_status_description[status]);
    return;
  }

  AT_PRINTF("%s,%u\n", at_status_description[status], error);
}

/**
 * @brief  Array of all supported AT Commands
 */
static const at_command_t at_command[] = {
    {
        .string = AT_RESET,
        .size_string = sizeof(AT_RESET) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_RESET ": Trig a reset of the MCU\n",
#endif
        .get = at_return_error,
        .set = at_return_error,
        .run = at_reset,
    },

#ifndef NO_KEY_ADDR_EUI
    {
        .string = AT_DEUI,
        .size_string = sizeof(AT_DEUI) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_DEUI ": Get or Set the Device EUI\n",
#endif
        .get = at_DevEUI_get,
        .set = at_DevEUI_set,
        .run = at_return_error,
    },
#endif

#ifndef NO_KEY_ADDR_EUI
    {
        .string = AT_APPKEY,
        .size_string = sizeof(AT_APPKEY) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_APPKEY ": Get or Set the Application Key\n",
#endif
        .get = at_AppKey_get,
        .set = at_AppKey_set,
        .run = at_return_error,
    },
#endif

#ifndef NO_KEY_ADDR_EUI
    {
        .string = AT_JOINEUI,
        .size_string = sizeof(AT_JOINEUI) - 1,
#ifndef NO_HELP
        /* .help_string = "AT"AT_JOINEUI ": Get or Set the Join Eui\n",*/ /* refer
                                                                               to comment in at.h file*/
        .help_string = "AT" AT_JOINEUI ": Get or Set the App Eui\n",
#endif
        .get = at_JoinEUI_get,
        .set = at_JoinEUI_set,
        .run = at_return_error,
    },
#endif

    {
        .string = AT_ADR,
        .size_string = sizeof(AT_ADR) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_ADR ": Get or Set the Adaptive Data Rate "
                       "setting. (0: off, 1: on)\n",
#endif
        .get = at_ADR_get,
        .set = at_ADR_set,
        .run = at_return_error,
    },

    {
        .string = AT_DR,
        .size_string = sizeof(AT_DR) - 1,
#ifndef NO_HELP
        .help_string =
            "AT" AT_DR
            ": Get or Set the Data Rate. (0-6 corresponding to DR_X)\n",
#endif
        .get = at_DataRate_get,
        .set = at_DataRate_set,
        .run = at_return_error,
    },

    {
        .string = AT_REGION,
        .size_string = sizeof(AT_REGION) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_REGION ": Get or Set the active region\n",
#endif
        .get = at_ActiveRegion_get,
        .set = at_ActiveRegion_set,
        .run = at_return_error,
    },

    {
        .string = AT_JOIN,
        .size_string = sizeof(AT_JOIN) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_JOIN ": Join network\n",
#endif
        .get = at_return_error,
        .set = at_Join,
        .run = at_return_error,
    },

    {
        .string = AT_VER,
        .size_string = sizeof(AT_VER) - 1,
#ifndef NO_HELP
        .help_string =
            "AT" AT_VER ": Get the version of the ATModem application\n",
#endif
        .get = at_version_get,
        .set = at_return_error,
        .run = at_return_error,
    },

    {
        .string = AT_FSDKVER,
        .size_string = sizeof(AT_FSDKVER) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_FSDKVER ": Prints the fullsdk version\n",
#endif
        .get = at_return_error,
        .set = at_return_error,
        .run = at_fullsdk_version_get,
    },

    {
        .string = AT_SCHC_API,
        .size_string = sizeof(AT_SCHC_API) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_SCHC_API ": Selects the API (N or D)\n",
#endif
        .get = at_return_error,
        .set = at_set_fullsdk_api,
        .run = at_return_error,
    },

    {
        .string = AT_SCHC_TPL_SET,
        .size_string = sizeof(AT_SCHC_TPL_SET) - 1,
#ifndef NO_HELP
        .help_string =
            "AT" AT_SCHC_TPL_SET ": Sets a template in the volatile memory\n",
#endif
        .get = at_return_error,
        .set = at_set_tpl,
        .run = at_return_error,
    },

    {
        .string = AT_SCHC_TPL_PAYLOAD_SET,
        .size_string = sizeof(AT_SCHC_TPL_PAYLOAD_SET) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_SCHC_TPL_PAYLOAD_SET
                       ": Loads payload compression rules in the memory\n",
#endif
        .get = at_return_error,
        .set = at_set_payload_rules,
        .run = at_return_error,
    },

    {
        .string = AT_SCHC_TPL_GET_ID,
        .size_string = sizeof(AT_SCHC_TPL_GET_ID) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_SCHC_TPL_GET_ID
                       ": Returns the ID of the current template\n",
#endif
        .get = at_return_error,
        .set = at_return_error,
        .run = at_get_tpl_id,
    },

    {
        .string = AT_SCHC_TPLPARAMS_NB,
        .size_string = sizeof(AT_SCHC_TPLPARAMS_NB) - 1,
#ifndef NO_HELP
        .help_string =
            "AT" AT_SCHC_TPLPARAMS_NB
            ": Returns the number of parameters of the current template\n",
#endif
        .get = at_return_error,
        .set = at_return_error,
        .run = at_get_nb_tpl_params,
    },

    {
        .string = AT_SCHC_TPLPARAMS_SET,
        .size_string = sizeof(AT_SCHC_TPLPARAMS_SET) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_SCHC_TPLPARAMS_SET
                       ": Set template parameters as index,value list\n",
#endif
        .get = at_return_error,
        .set = at_set_template_params,
        .run = at_return_error,
    },
    {
        .string = AT_SCHC_TPLPARAMS_GET,
        .size_string = sizeof(AT_SCHC_TPLPARAMS_GET) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_SCHC_TPLPARAMS_GET
                       ": Get template parameters as index,value list\n",
#endif
        .get = at_return_error,
        .set = at_get_template_params,
        .run = at_return_error,
    },

    {
        .string = AT_SCHC_TPLPARAMS_CLR,
        .size_string = sizeof(AT_SCHC_TPLPARAMS_CLR) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_SCHC_TPLPARAMS_CLR
                       ": Clear the template parameters memory region\n",
#endif
        .get = at_return_error,
        .set = at_return_error,
        .run = at_clear_tpl_params,
    },

    {
        .string = AT_SCHC_SYNC,
        .size_string = sizeof(AT_SCHC_SYNC) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_SCHC_SYNC ": Starts synchronization procedure\n",
#endif
        .get = at_return_error,
        .set = at_sync,
        .run = at_return_error,
    },

    {
        .string = AT_SCHC_CONF_POLL,
        .size_string = sizeof(AT_SCHC_CONF_POLL) - 1,
#ifndef NO_HELP
        .help_string =
            "AT" AT_SCHC_CONF_POLL ": Configures class A polling, 1st param: "
            "enable, 2nd param: suspend uplinks\n",
#endif
        .get = at_return_error,
        .set = at_schc_conf_poll,
        .run = at_return_error,
    },

    {
        .string = AT_SCHC_TRIGGER_POLL,
        .size_string = sizeof(AT_SCHC_TRIGGER_POLL) - 1,
#ifndef NO_HELP
        .help_string =
            "AT" AT_SCHC_TRIGGER_POLL
            ": Triggers the polling mechanism, sends an empty frame\n",
#endif
        .get = at_return_error,
        .set = at_return_error,
        .run = at_schc_trigger_poll,
    },

    {
        .string = AT_GETIP,
        .size_string = sizeof(AT_GETIP) - 1,
#ifndef NO_HELP
        .help_string = "AT" AT_GETIP ": Prints the IP address of the device\n",
#endif
        .get = at_return_error,
        .set = at_return_error,
        .run = at_fullsdk_ip_get,
    },

};

/* Private function prototypes -----------------------------------------------*/

/**
 * @brief  Parse a command and process it
 * @param  The command
 * @retval None
 */
static void parse_cmd(const char *cmd);

/* Exported functions
 * ---------------------------------------------------------*/
static void CMD_GetChar(uint8_t *rxChar);

static char circBuffer[CIRC_BUFF_SIZE];
static char command[CMD_SIZE];
static unsigned i = 0;
static uint32_t widx = 0;
static uint32_t ridx = 0;
static uint32_t charCount = 0;
static bool circBuffOverflow = false;

void CMD_Init(void)
{
  platform_set_uart_rx_callback(CMD_GetChar);
  widx = 0;
  ridx = 0;
  charCount = 0;
  i = 0;
  circBuffOverflow = false;
}

static void CMD_GetChar(uint8_t *rxChar)
{
  charCount++;
  if (charCount == (CIRC_BUFF_SIZE + 1))
  {
    circBuffOverflow = true;
    charCount--;
  }
  else
  {
    circBuffer[widx++] = *rxChar;
    if (widx == CIRC_BUFF_SIZE)
    {
      widx = 0;
    }
  }
}

void CMD_Process(void)
{
  /* Process all commands */
  if (circBuffOverflow)
  {
    com_error(AT_TEST_PARAM_OVERFLOW, 0);
    /*Full flush in case of overflow */
    CRITICAL_SECTION_BEGIN();
    ridx = widx;
    charCount = 0;
    circBuffOverflow = false;
    CRITICAL_SECTION_END();
    i = 0;
  }

  while (charCount != 0)
  {
#if 0 /* echo On    */
  PRINT_AT("%c", circBuffer[ridx]);
#endif

    if (circBuffer[ridx] == AT_ERROR_RX_CHAR)
    {
      ridx++;
      if (ridx == CIRC_BUFF_SIZE)
      {
        ridx = 0;
      }
      CRITICAL_SECTION_BEGIN();
      charCount--;
      CRITICAL_SECTION_END();
      com_error(AT_RX_ERROR, 0);
      i = 0;
    }
    else if ((circBuffer[ridx] == '\r') || (circBuffer[ridx] == '\n'))
    {
      ridx++;
      if (ridx == CIRC_BUFF_SIZE)
      {
        ridx = 0;
      }
      CRITICAL_SECTION_BEGIN();
      charCount--;
      CRITICAL_SECTION_END();

      if (i != 0)
      {
        command[i] = '\0';
        parse_cmd(command);
        i = 0;
      }
    }
    else if (i == (CMD_SIZE - 1))
    {
      i = 0;
      com_error(AT_TEST_PARAM_OVERFLOW, 0);
    }
    else
    {
      command[i++] = circBuffer[ridx++];
      if (ridx == CIRC_BUFF_SIZE)
      {
        ridx = 0;
      }
      CRITICAL_SECTION_BEGIN();
      charCount--;
      CRITICAL_SECTION_END();
    }
  }
}

static bool process_at_cmd(const char *cmd, const at_command_t *command,
                           at_status_t *status, uint8_t *error)
{
  if (strncmp(cmd, command->string, command->size_string) != 0)
  {
    // Command doesn't match.
    return false;
  }

  /* point to the string after the command to parse it */
  cmd += command->size_string;

  /* parse after the command */
  switch (cmd[0])
  {
    case '\0': /* nothing after the command */
      *status = command->run(cmd, error);
      break;
    case ',': /* SCHC extension commands */
      *status = command->set(cmd + 1, error);
      break;
    case '=':
      if ((cmd[1] == '?') && (cmd[2] == '\0'))
      {
        *status = command->get(cmd + 1, error);
      }
      else
      {
        *status = command->set(cmd + 1, error);
      }
      break;
    case '?':
#ifndef NO_HELP
      AT_PRINTF(command->help_string);
#endif
      *status = AT_OK;
      break;
  }

  return true;
}

static void parse_cmd(const char *cmd)
{
  at_status_t status = AT_OK;
  uint8_t error = 0;
  bool found = false;
  int i;

  if ((cmd[0] != 'A') || (cmd[1] != 'T'))
  {
    status = AT_ERROR;
  }
  else if (cmd[2] == '\0')
  {
    /* status = AT_OK; */
  }
  else if (cmd[2] == '?')
  {
#ifdef NO_HELP
#else
    AT_PRINTF("AT+<CMD>?        : Help on <CMD>\n"
              "AT+<CMD>         : Run <CMD>\n"
              "AT+<CMD>=<value> : Set the value\n"
              "AT+<CMD>=?       : Get the value\n");
    // L2/MGT help.
    for (i = 0; i < (sizeof(at_command) / sizeof(at_command_t)); i++)
    {
      AT_PRINTF(at_command[i].help_string);
    }
    if (dtg_api_enabled)
    {
      // DTG API help.
      for (i = 0; i < (sizeof(at_dtg_api_command) / sizeof(at_command_t)); i++)
      {
        AT_PRINTF(at_dtg_api_command[i].help_string);
      }
    }
    else
    {
      // NET API help.
      for (i = 0; i < (sizeof(at_net_api_command) / sizeof(at_command_t)); i++)
      {
        AT_PRINTF(at_net_api_command[i].help_string);
      }
    }
    /* Wait for the message queue to be flushed in order
       not to disturb following com_error() display */
    platform_delay_ms(HELP_DISPLAY_FLUSH_DELAY);
#endif
  }
  else
  {
    // Check standard AT commands.
    status = AT_ERROR;
    cmd += 2;

    for (i = 0; i < (sizeof(at_command) / sizeof(at_command_t)); i++)
    {
      found = process_at_cmd(cmd, &at_command[i], &status, &error);
      if (found)
      {
        break;
      }
    }
    if (dtg_api_enabled)
    {
      // Check DTG API AT commands.
      for (i = 0; i < (sizeof(at_dtg_api_command) / sizeof(at_command_t)); i++)
      {
        found = process_at_cmd(cmd, &at_dtg_api_command[i], &status, &error);
        if (found)
        {
          break;
        }
      }
    }
    else
    {
      // Check NET API AT commands.
      for (i = 0; i < (sizeof(at_net_api_command) / sizeof(at_command_t)); i++)
      {
        found = process_at_cmd(cmd, &at_net_api_command[i], &status, &error);
        if (found)
        {
          break;
        }
      }
    }
  }

  com_error(status, error);
  error = 0;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF
 * FILE****/
