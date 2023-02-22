
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rf_driver_hal_i2c_ex.h"

/* Private includes ----------------------------------------------------------*/

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

/* Exported types ------------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c;
 /* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
int32_t MX_I2C2_Init(void);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle);

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __I2C_H */

