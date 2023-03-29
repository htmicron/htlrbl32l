/**
 * Copyright (C) 2018-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Aydogan Ersoz aydogan.ersoz@ackl.io
 *
 * Semtech L2 configuration layer.
 */

#ifndef FULLSDK_L2_H_
#define FULLSDK_L2_H_

#include <stdint.h>
#include <string.h>

//#include "LoRaMac.h"
#include "fullsdkl2a.h"
#include "fullsdkl2common.h"

#define SEMTECH_L2

#define L2_MAX_SUPPORTED_REGION (10)

//typedef LoRaMacStatus_t l2_op_status_t;

l2_status_t l2_init(void);
const char *l2_get_version(void);
uint8_t l2_get_default_datarate(void);
void l2_set_default_datarate(uint8_t datarate);
l2_status_t l2_get_active_region(l2_region_id_t *region);
l2_status_t l2_set_active_region(l2_region_id_t region);
l2_status_t l2_get_class(char *class);
l2_status_t l2_set_class(char class);
uint8_t *l2_get_dev_eui(void);
l2_status_t l2_set_dev_eui(uint8_t *value);
uint8_t *l2_get_join_eui(void);
l2_status_t l2_set_join_eui(uint8_t *value);
uint8_t *l2_get_app_key(void);
l2_status_t l2_set_app_key(uint8_t *value);
l2_status_t l2_get_dr(uint8_t *dr);
l2_status_t l2_set_dr(uint8_t dr);
l2_status_t l2_set_adr(bool adr);
l2_status_t l2_get_adr(bool *adr);

// This global variable must be defined in fullsdkl2.c
extern l2_region_t regions[L2_MAX_SUPPORTED_REGION];



#endif // FULLSDK_L2_H_
