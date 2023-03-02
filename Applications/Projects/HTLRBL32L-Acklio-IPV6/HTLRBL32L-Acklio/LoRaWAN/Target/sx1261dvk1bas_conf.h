/**
  ******************************************************************************
  * @file              : sx1261dvk1bas_conf.h
  * @brief             : This file provides code for the configuration
  *                      of the shield instances (pin mapping).
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SX1261DVK1BAS_CONF_H__
#define __SX1261DVK1BAS_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "platform.h"

/* Daughter board Pin mapping --------------------------------------------*/

/*  SPI MACRO redefinition */
#define RADIO_SPI_Init                            BSP_SPI1_Init
#define RADIO_SPI_DeInit                          BSP_SPI1_DeInit
#define RADIO_SPI_SendRecv                        BSP_SPI1_SendRecv

#define RADIO_SPI_CLK_ENABLE()                    __HAL_RCC_SPI1_CLK_ENABLE()

/* SPIx Bus Pin mapping */
#define RADIO_SPI_SCK_GPIO_PIN           BUS_SPI1_SCK_GPIO_PIN
#define RADIO_SPI_MISO_GPIO_PIN          BUS_SPI1_MISO_GPIO_PIN
#define RADIO_SPI_MOSI_GPIO_PIN          BUS_SPI1_MOSI_GPIO_PIN
#define RADIO_SPI_SCK_GPIO_PORT          BUS_SPI1_SCK_GPIO_PORT
#define RADIO_SPI_MISO_GPIO_PORT         BUS_SPI1_MISO_GPIO_PORT
#define RADIO_SPI_MOSI_GPIO_PORT         BUS_SPI1_MOSI_GPIO_PORT
#define RADIO_SPI_SCK_GPIO_AF            BUS_SPI1_SCK_GPIO_AF
#define RADIO_SPI_MOSI_GPIO_AF           BUS_SPI1_MOSI_GPIO_AF
#define RADIO_SPI_MISO_GPIO_AF           BUS_SPI1_MISO_GPIO_AF
#define RADIO_SPI_SCK_GPIO_CLK_ENABLE()  BUS_SPI1_SCK_GPIO_CLK_ENABLE()
#define RADIO_SPI_MOSI_GPIO_CLK_ENABLE() BUS_SPI1_MOSI_GPIO_CLK_ENABLE()
#define RADIO_SPI_MISO_GPIO_CLK_ENABLE() BUS_SPI1_MISO_GPIO_CLK_ENABLE()

#if defined (USE_STM32L0XX_NUCLEO) || defined (USE_B_L072Z_LRWAN1)
#define RADIO_SPI_AF                              GPIO_AF0_SPI1
#elif defined (USE_STM32L1XX_NUCLEO) || defined (USE_STM32L4XX_NUCLEO)
#define RADIO_SPI_AF                              GPIO_AF5_SPI1
#endif

#define RADIO_NSS_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define RADIO_NSS_PORT              GPIOA
#define RADIO_NSS_PIN               GPIO_PIN_11
/*  Radio Pins */

#define RADIO_RESET_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define RADIO_RESET_PORT            GPIOB
#define RADIO_RESET_PIN             GPIO_PIN_8

#define RADIO_BUSY_CLK_ENABLE()                  __HAL_RCC_GPIOB_CLK_ENABLE()
#define RADIO_BUSY_PORT                           GPIOB
#define RADIO_BUSY_PIN                            GPIO_PIN_15

#define RADIO_DIOn                               1U

#define RADIO_DIO_1_IT_PRIO                        0
#define RADIO_DIO_1_PORT                  GPIOB
#define RADIO_DIO_1_PIN                   GPIO_PIN_4
#define RADIO_DIO_1_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define RADIO_DIO_1_EXTI_LINE             EXTI_LINE_PB4
#define RADIO_DIO_1_IRQn                  GPIOB_IRQn
#define H_EXTI_4        hRADIO_DIO_exti[0]

#define RADIO_ANT_SWITCH_POWER_PORT               GPIOB
#define RADIO_ANT_SWITCH_POWER_PIN                GPIO_PIN_0
#define RADIO_ANT_SWITCH_POWER_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define RADIO_LEDTX_PORT                                GPIOC
#define RADIO_LEDTX_PIN                                 GPIO_PIN_1
#define RADIO_LEDRX_PORT                                GPIOC
#define RADIO_LEDRX_PIN                                 GPIO_PIN_0

#define DEVICE_SEL_PORT                           GPIOB
#define DEVICE_SEL_PIN                            GPIO_PIN_3
#define RADIO_DEV_SEL_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#ifdef __cplusplus
}
#endif

#endif /* __SX1261DVK1BAS_CONF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
