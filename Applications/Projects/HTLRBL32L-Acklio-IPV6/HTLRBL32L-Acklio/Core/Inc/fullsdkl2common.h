/**
 * Copyright (C) 2018-2021 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Flavien Moullec flavien@ackl.io
 *
 * L2 common structures and functions.
 */

#ifndef FULLSDK_L2_COMMON_H
#define FULLSDK_L2_COMMON_H

typedef enum
{
  L2_SUCCESS = 0,
  L2_ERROR,
  L2_NOT_SUPPORTED_ERR
} l2_status_t;

typedef enum
{
  L2_NETWORK_ACTIVATION_TYPE_NONE = 0,
  L2_NETWORK_ACTIVATION_TYPE_ABP = 1,
  L2_NETWORK_ACTIVATION_TYPE_OTAA = 2,
} l2_network_activation_type_t;

/**
 * Generic type for LoRaMacRegion_t.
 */
typedef uint8_t l2_region_id_t;

typedef struct
{
  char *str;
  l2_region_id_t id;
} l2_region_t;
typedef enum
{
  L2_MSG_TYPE_UNCONFIRMED = 0,
  L2_MSG_TYPE_CONFIRMED = !L2_MSG_TYPE_UNCONFIRMED
} l2_msg_type_t;

typedef struct
{
  l2_msg_type_t type;
  uint8_t port;
  uint8_t size;
  uint8_t *buffer;
} l2_app_data_t;

#endif // FULLSDK_L2_COMMON_H
