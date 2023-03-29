/**
 ******************************************************************************
 * @file    at.h
 * @author  MCD Application Team
 * @brief   Header for driver at.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT_H__
#define __AT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "platform.h"

/**
 * @brief AT command status codes
 */
typedef enum
{
  AT_OK = 0,
  AT_ERROR,
  AT_PARAM_ERROR,
  AT_TEST_PARAM_OVERFLOW,
  AT_RX_ERROR,
  AT_L2_ERROR,
  AT_NOT_IMPLEMENTED,
  AT_PLATFORM_ERROR,
  AT_SCHC_MGT_ERROR,
  AT_SCHC_DTG_ERROR,
  AT_SCHC_NET_ERROR,
  AT_MAX
} at_status_t;

extern bool join_flag;
extern bool dtg_api_enabled;
extern bool sdk_init;

#define MAX_PAYLOAD_SIZE 1024

/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* AT printf */
#define AT_PRINTF PRINT_AT

/**
 * @brief  Structure defining an AT Command
 */
typedef struct
{
  const char *string; /*< command string, after the "AT" */
  const int
      size_string; /*< size of the command string, not including the final \0 */
  at_status_t (*get)(
      const char *param,
      uint8_t *error); /*< =? after the string to get the current value*/
  at_status_t (*set)(const char *param, uint8_t *error); /*< = (but not =?\0)
                                            after the string to set a value */
  at_status_t (*run)(
      const char *param,
      uint8_t *error); /*< \0 after the string - run the command */
#if !defined(NO_HELP)
  const char *help_string; /*< to be printed when ? after the string */
#endif
} at_command_t;

/* Exported functions ------------------------------------------------------- */

/**
 * @brief  Return AT_ERROR in all cases
 * @param  Param string of the AT command - unused
 * @retval AT_ERROR
 */
at_status_t at_return_error(const char *param, uint8_t *error);

/**
 * @brief  Return AT_NOT_IMPLEMENTED in all cases
 * @param  Param string of the AT command - unused
 * @retval AT_NOT_IMPLEMENTED
 */
at_status_t at_not_implemented_error(const char *param, uint8_t *error);

/**
 * @brief  Trig a reset of the MCU
 * @param  Param string of the AT command - unused
 * @retval AT_OK
 */
at_status_t at_reset(const char *param, uint8_t *error);

/**
 * @brief  Print Device EUI
 * @param  Param string of the AT command - unused
 * @retval AT_OK
 */
at_status_t at_DevEUI_get(const char *param, uint8_t *error);

/**
 * @brief  Set Device Eui
 * @param  Param string of the AT command
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_DevEUI_set(const char *param, uint8_t *error);

/**
 * @brief  Print Join Eui
 * @param  Param string of the AT command
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_JoinEUI_get(const char *param, uint8_t *error);

/**
 * @brief  Set Join Eui
 * @param  Param string of the AT command
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_JoinEUI_set(const char *param, uint8_t *error);

/**
 * @brief  Print Application Key
 * @param  Param string of the AT command
 * @retval AT_OK
 */
at_status_t at_AppKey_get(const char *param, uint8_t *error);

/**
 * @brief  Set Application Key
 * @param  Param string of the AT command
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_AppKey_set(const char *param, uint8_t *error);

/**
 * @brief  Print Adaptative Data Rate setting
 * @param  String pointing to provided ADR setting
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_ADR_get(const char *param, uint8_t *error);

/**
 * @brief  Set Adaptative Data Rate setting
 * @param  String pointing to provided ADR setting
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_ADR_set(const char *param, uint8_t *error);

/**
 * @brief  Print Data Rate
 * @param  String pointing to provided rate
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_DataRate_get(const char *param, uint8_t *error);

/**
 * @brief  Set Data Rate
 * @param  String pointing to provided rate
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_DataRate_set(const char *param, uint8_t *error);

/**
 * @brief  Print active region
 * @param  String pointing to provided param
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_ActiveRegion_get(const char *param, uint8_t *error);

/**
 * @brief  Set active region
 * @param  String pointing to provided param
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_ActiveRegion_set(const char *param, uint8_t *error);

/**
 * @brief  Join a network
 * @param  String parameter
 * @retval AT_OK if OK, or an appropriate AT_xxx error code
 */
at_status_t at_Join(const char *param, uint8_t *error);

/**
 * @brief  Print the version of the ATModem FW
 * @param  String parameter
 * @retval AT_OK
 */
at_status_t at_version_get(const char *param, uint8_t *error);

#ifdef __cplusplus
}
#endif

#endif /* __AT_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
