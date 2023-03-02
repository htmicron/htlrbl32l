/**
 * Copyright (C) 2018-2020 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Aydogan Ersoz aydogan.ersoz@ackl.io
 */

#ifndef __OS_H
#define __OS_H

#include <stdbool.h>
#include <stdint.h>

#define SDK_TASK_PRIORITY (tskIDLE_PRIORITY + 3UL)
#define SDK_STACK_SIZE 384
#define SDK_TASK_PERIOD 10
#define SDK_TASK_DELAY (SDK_TASK_PERIOD / portTICK_PERIOD_MS)

#define UIP_TASK_PRIORITY (tskIDLE_PRIORITY + 2UL)
#define UIP_STACK_SIZE 240
#define UIP_TASK_PERIOD 10
#define UIP_TASK_DELAY (UIP_TASK_PERIOD / portTICK_PERIOD_MS)

#define APP_TASK_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define APP_STACK_SIZE 192

#define MAX_DATA_LEN                                                           \
  64 // maximum size of the message (use `data_ptr` for larger data)

typedef enum
{
  // MSG_TYPE_<REQ/INF>_<SRC_THREAD>_<DST_THREAD>_<MSG>
  MSG_TYPE_REQ_UIP_SDK_INIT = 0,
  MSG_TYPE_REQ_SDK_SDK_PROCESS,
  MSG_TYPE_REQ_APP_UIP_SEND,
  MSG_TYPE_REQ_UIP_UIP_SEND,
  MSG_TYPE_REQ_UIP_SDK_SEND,
  MSG_TYPE_REQ_APP_APP_SEND,
  MSG_TYPE_REQ_APP_UIP_INIT,
  MSG_TYPE_INF_SDK_SDK_NETWORK_JOINED,
  MSG_TYPE_INF_SDK_SDK_NETWORK_CONFIGURED,
  MSG_TYPE_INF_UIP_APP_READY,
  MSG_TYPE_INF_SDK_UIP_NETWORK_CONFIGURED,
  MSG_TYPE_INF_SDK_UIP_TX_RESULT,
  MSG_TYPE_INF_UIP_APP_TX_RESULT,
  MSG_TYPE_INF_SDK_UIP_DATA_RCVD,
  MSG_TYPE_INF_UIP_APP_DATA_RCVD,
  MSG_TYPE_INF_UIP_APP_CAN_NOT_SEND,
} message_type_e;

typedef struct
{
  message_type_e type;
  uint16_t len;
  struct
  {
    union
    {
      uint8_t data[MAX_DATA_LEN];
      const void *data_ptr;
    };
    bool error;
  } body;
} message_t;

uint32_t get_clock_ms(void);

void platform_delay_ms(uint32_t ms);

void print_mem_hex(const uint8_t *mem, uint16_t mem_size);

void SystemClock_Config(void);

void Error_Handler(void);

#endif /* __OS_H */
