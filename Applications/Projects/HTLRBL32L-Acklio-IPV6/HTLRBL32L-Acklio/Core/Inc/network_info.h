/**
 * Copyright (C) 2018-2020 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Aydogan Ersoz aydogan.ersoz@ackl.io
 */

#ifndef __NETWORK_INFO_H
#define __NETWORK_INFO_H

#include <stdint.h>

#define MAX_NETWORK_PARAM_LEN 20
#define NETWORK_PARAM_CNT 6 // IPv6/UDP template ID 1

// Network parameter structure
typedef struct
{
  uint8_t value[MAX_NETWORK_PARAM_LEN];
  uint16_t len;
} network_params_t;

// Network info structure
typedef struct
{
  network_params_t param[NETWORK_PARAM_CNT];
} network_info_t;

#endif /* __NETWORK_INFO_H */