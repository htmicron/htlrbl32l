/**
 * Copyright (C) 2018-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Authors: Aydogan Ersoz aydogan.ersoz@ackl.io
 *          Pascal Bodin pascal@ackl.io
 *
 * Semtech L2 configuration layer. Used by ATModem application.
 */

#include "fullsdkl2.h"
#include "utilities.h"
#include "LmHandler.h"
#include "LoRaMac.h"
#include "se-identity.h"

static uint8_t default_datarate = 3;

uint8_t dev_eui[] = LORAWAN_DEVICE_EUI;
uint8_t join_eui[] = LORAWAN_JOIN_EUI;
uint8_t app_key[] = FORMAT_KEY(LORAWAN_APP_KEY);
// Must be set to a value that is not a valid class. This is
// used by fullsdkl2a.c for ATModem application.
DeviceClass_t device_class = 0;

// L2 initialization function defined in fullsdkl2a.c.
void l2a_l2_init(void);
// L2 connection function defined in fullsdkl2a.c.

/*!
 * Available regions
 */
l2_region_t regions[L2_MAX_SUPPORTED_REGION] = {
    {.str = "AS923", .id = LORAMAC_REGION_AS923},
    {.str = "AU915", .id = LORAMAC_REGION_AU915},
    {.str = "CN470", .id = LORAMAC_REGION_CN470},
    {.str = "CN779", .id = LORAMAC_REGION_CN779},
    {.str = "EU433", .id = LORAMAC_REGION_EU433},
    {.str = "EU868", .id = LORAMAC_REGION_EU868},
    {.str = "KR920", .id = LORAMAC_REGION_KR920},
    {.str = "IN865", .id = LORAMAC_REGION_IN865},
    {.str = "US915", .id = LORAMAC_REGION_US915},
    {.str = "RU864", .id = LORAMAC_REGION_RU864}};

const char *l2_get_version(void)
{
  return "ST2.1.0";
}

l2_status_t l2_init(void)
{
  return L2_SUCCESS;
}

uint8_t l2_get_default_datarate(void)
{
  return default_datarate;
}

void l2_set_default_datarate(uint8_t datarate)
{
  default_datarate = datarate;
}

l2_status_t l2_get_active_region(l2_region_id_t *region)
{
  LmHandlerErrorStatus_t rs = LmHandlerGetActiveRegion((LoRaMacRegion_t *)region);
  if (rs != LORAMAC_HANDLER_SUCCESS)
  {
    return L2_ERROR;
  }

  return L2_SUCCESS;
}

l2_status_t l2_set_active_region(l2_region_id_t region)
{
  LmHandlerErrorStatus_t rs = LmHandlerSetActiveRegion((LoRaMacRegion_t)region);
  if (rs != LORAMAC_HANDLER_SUCCESS)
  {
    return L2_ERROR;
  }

  return L2_SUCCESS;
}

l2_status_t l2_get_class(char *class)
{
  switch (device_class)
  {
  case CLASS_A:
    *class = 'A';
    break;
  case CLASS_B:
    *class = 'B';
    break;
  case CLASS_C:
    *class='C';
    break;
  default:
    return L2_ERROR;
  }
  return L2_SUCCESS;
}

l2_status_t l2_set_class(char class)
{
   switch (class)
   {
   case 'A':
     device_class = CLASS_A;
     break;
   case 'C':
     device_class = CLASS_C;
     break;
   case 'B':
     device_class = CLASS_B;
     break;
   default:
     return L2_ERROR;
   }

  return L2_SUCCESS;
}

uint8_t *l2_get_dev_eui(void)
{
  // dev_eui is initialized to LORAWAN_DEV_EUI. In ST stack, device EUI
  // is stored in SeNvm->DevEui (soft-se.c).
  return dev_eui;
}

l2_status_t l2_set_dev_eui(uint8_t *value)
{
  // According to a comment in utilities.h, STM32 memcpy only
  // works with aligned pointers.
  memcpy1(dev_eui, value, 8);

  return L2_SUCCESS;
}

uint8_t *l2_get_join_eui(void)
{
  // join_eui is initialized to LORAWAN_JOIN_EUI. In ST stack, join EUI
  // is stored in SeNvm->JoinEui (soft-se.c).
  return join_eui;
}

l2_status_t l2_set_join_eui(uint8_t *value)
{
  // According to a comment in utilities.h, STM32 memcpy only
  // works with aligned pointers.
  memcpy1(join_eui, value, 8);

  return L2_SUCCESS;
}

uint8_t *l2_get_app_key(void)
{
  // app_key is initialized to LORAWAN_APP_KEY. In ST stack, App Key
  // is stored in SeNvm (soft-se.c).
  return app_key;
}

l2_status_t l2_set_app_key(uint8_t *value)
{
  // LmHandlerSetNwkKey must not be called before LoRaMAC initialization.
  // Consequently, we save value to app_key here. And LmHandlerSetNwkKey
  // will be called in fullsdkl2a.c, when join is requested.

  // According to a comment in utilities.h, STM32 memcpy only
  // works with aligned pointers.
  memcpy1(app_key, value, 16);

  return L2_SUCCESS;
}

l2_status_t l2_get_dr(uint8_t *dr)
{
  LmHandlerErrorStatus_t status = LmHandlerGetTxDatarate((int8_t *)dr);
  if (status != LORAMAC_HANDLER_SUCCESS)
  {
    return L2_ERROR;
  }
  return L2_SUCCESS;
}

l2_status_t l2_set_dr(uint8_t dr)
{
  LmHandlerErrorStatus_t status = LmHandlerSetTxDatarate(dr);
  if (status != LORAMAC_HANDLER_SUCCESS)
  {
    return L2_ERROR;
  }
  return L2_SUCCESS;
}

l2_status_t l2_get_adr(bool *adr)
{
  LmHandlerErrorStatus_t status = LmHandlerGetAdrEnable(adr);
  if (status != LORAMAC_HANDLER_SUCCESS)
  {
    return L2_ERROR;
  }
  return L2_SUCCESS;
}

l2_status_t l2_set_adr(bool adr)
{
  LmHandlerErrorStatus_t status = LmHandlerSetAdrEnable(adr);
  if (status != LORAMAC_HANDLER_SUCCESS)
  {
    return L2_ERROR;
  }
  return L2_SUCCESS;
}
