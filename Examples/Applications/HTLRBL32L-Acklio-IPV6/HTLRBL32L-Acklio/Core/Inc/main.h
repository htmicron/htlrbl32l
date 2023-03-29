/**
 * Copyright (C) 2018-2020 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Pascal Bodin - pascal@ackl.io
 */
#ifndef __MAIN_H
#define __MAIN_H
#include <stdio.h>
#include "rf_driver_hal.h"
//BLE INCLUDES

#include "rf_driver_hal.h"
#include "rf_driver_ll_rtc.h"


#include "HT_push_button.h"
#include "rf_driver_hal_power_manager.h"

#include "ble_const.h"
#include "bluenrg_lp_stack.h"
#include "rf_driver_hal_power_manager.h"
#include "rf_driver_hal_vtimer.h"

#include "HT_push_button_cfg.h"
#include "bleplat.h"
#include "nvm_db.h"

#include "ble_controller.h"
#include "pka_manager.h"
#include "rng_manager.h"
#include "aes_manager.h"

#include "HT_ble_api.h"
#include "HT_gatt_db.h"
#include "HT_push_button.h"

//
#define RTC_N_PREDIV_S 10
#define RTC_PREDIV_S ((1<<RTC_N_PREDIV_S)-1)
#define RTC_PREDIV_A ((1<<(15-RTC_N_PREDIV_S))-1)
// UART speed is set to 9600 in order to be compatible with existing Python client.
#define USART_BAUDRATE 9600

/* Pin mapping */

/* Definition for UARTx clock resources */
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define DMAMUX_CLK_ENABLE()              __HAL_RCC_DMAMUX1_CLK_ENABLE()

/* Definition for USARTx's DMA Request */
#define USARTx_TX_DMA_REQUEST             DMA_REQUEST_USART1_TX
/* Definition for USARTx's DMA */

#define USARTx_TX_DMA_CHANNEL             DMA1_Channel7

/* Definition for USARTx's NVIC */
#define DMA1_Channel7_IRQn 					DMA_IRQn
#define USARTx_DMA_TX_IRQn                DMA1_Channel7_IRQn

#define USARTx_DMA_TX_IRQHandler          DMA1_Channel7_IRQHandler

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_Priority 0
#define USARTx_DMA_Priority 0

#define USARTx_RX_Pin GPIO_PIN_8
#define USARTx_RX_GPIO_Port GPIOA
#define USARTx_TX_Pin GPIO_PIN_9
#define USARTx_TX_GPIO_Port GPIOA

#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

//#define USARTx_TX_AF                     GPIO_AF7_USART2
//#define USARTx_RX_AF                     GPIO_AF7_USART2




#endif /* __MAIN_H */
