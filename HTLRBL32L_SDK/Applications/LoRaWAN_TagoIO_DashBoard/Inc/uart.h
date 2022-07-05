/*
  _    _ _______   __  __ _____ _____ _____   ____  _   _
 | |  | |__   __| |  \/  |_   _/ ____|  __ \ / __ \| \ | |
 | |__| |  | |    | \  / | | || |    | |__) | |  | |  \| |
 |  __  |  | |    | |\/| | | || |    |  _  /| |  | | . ` |
 | |  | |  | |    | |  | |_| || |____| | \ \| |__| | |\  |
 |_|  |_|  |_|    |_|  |_|_____\_____|_|  \_\\____/|_| \_|
 =================== Advanced R&D ========================

*/

/*!
 * \file uart.h
 * \brief This file contains all the function prototypes for the uart.c file
 * \author HT Micron Advanced R&D
 * \link support_iot@htmicron.com.br
 * \version 1.0
 * \date January 05, 2022
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H__
#define __UART_H__

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
extern UART_HandleTypeDef huart1;

/* Private function prototypes -----------------------------------------------*/
void MX_USART1_UART_Init(void);

#endif /* __UART_H__ */

/************************ HT MICRON SEMICONDUCTORS S.A - uart.h *****END OF FILE****/
