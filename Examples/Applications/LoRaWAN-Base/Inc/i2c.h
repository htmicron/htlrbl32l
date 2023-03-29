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
 * \file i2c.h
 * \brief I2C configuration.
 * \author HT Micron Advanced R&D
 * \link support_iot@htmicron.com.br
 * \version 1.0
 * \date October 07, 2021
 */

#ifndef __I2C_H__
#define __I2C_H__

#include "main.h"

#define BSP_ERROR_NONE                        0
#define BSP_ERROR_NO_INIT                    -1
#define BSP_ERROR_WRONG_PARAM                -2
#define BSP_ERROR_BUSY                       -3
#define BSP_ERROR_PERIPH_FAILURE             -4
#define BSP_ERROR_COMPONENT_FAILURE          -5
#define BSP_ERROR_UNKNOWN_FAILURE            -6
#define BSP_ERROR_UNKNOWN_COMPONENT          -7
#define BSP_ERROR_BUS_FAILURE                -8
#define BSP_ERROR_CLOCK_FAILURE              -9
#define BSP_ERROR_MSP_FAILURE                -10
#define BSP_ERROR_FEATURE_NOT_SUPPORTED      -11

/* BSP BUS error codes */

#define BSP_ERROR_BUS_TRANSACTION_FAILURE    -100
#define BSP_ERROR_BUS_ARBITRATION_LOSS       -101
#define BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE    -102
#define BSP_ERROR_BUS_PROTOCOL_FAILURE       -103

#define BSP_ERROR_BUS_MODE_FAULT             -104
#define BSP_ERROR_BUS_FRAME_ERROR            -105
#define BSP_ERROR_BUS_CRC_ERROR              -106
#define BSP_ERROR_BUS_DMA_FAILURE            -107

#define BUS_I2C2_POLL_TIMEOUT                10000

extern I2C_HandleTypeDef hi2c;

int32_t MX_I2C2_Init(void);
int32_t BSP_I2C_MspDeInit(void);

#endif /* __I2C_H__ */

/************************ HT Micron Semiconductors S.A i2c.h *****END OF FILE*****************************/
