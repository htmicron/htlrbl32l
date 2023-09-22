/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/UART_Printf_main.h
  * @author  RF Application Team
  * @brief   Header for UART_Printf_main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal.h"
#include "rf_driver_ll_rtc.h"
#include "utils.h"
#include "uart.h"
#include "spi.h"
#include "rtc.h"
#include "sx126x.h"
#include "sx126x_board.h"
#include "radio.h"
#include "lorawan_setup.h"
#include "lora-test.h"
#include "LoRaMac.h"
#include "hal_wrappers.h"
#include "HT_push_button.h"
#include "rf_driver_hal_power_manager.h"

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>

#include "rf_driver_hal_dma.h"
#include "rf_driver_hal_i2c.h"
#include "rf_driver_hal_spi.h"
#include "rf_driver_hal_uart.h"
#include "rf_driver_hal_gpio.h"
//#include "stsafea_types.h"

#define FLASH_USER_START_ADDR   (FLASH_END_ADDR - FLASH_PAGE_SIZE - 0xF)        /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     (FLASH_END_ADDR - 0xF)                          /* End @ of user Flash area */




//extern StSafeA_Handle_t stsafea_handle;
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

void MX_GPIO_LP_Init(void);
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void HSM_Init(void);

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
