/**
  ******************************************************************************
  * @file    rf_driver_hal_gpio_ex.h
  * @author  RF Application Team
  * @brief   Header file of GPIO HAL Extended module.
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
#ifndef RF_DRIVER_HAL_GPIO_EX_H
#define RF_DRIVER_HAL_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @brief GPIO Extended HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */

/** @defgroup GPIOEx_Alternate_function_selection GPIOEx Alternate function selection
  * @{
  */


/**
  * @brief   AF 0 selection
  */

#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF0_LCO           ((uint8_t)0x00)  /*!< LCO Alternate Function mapping                 */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /*!< SWCLK Alternate Function mapping               */
#ifdef I2C1 
#define GPIO_AF0_I2C1          ((uint8_t)0x00)  /*!< I2C1 Alternate Function mapping                */
#endif /* I2C1 */
#ifdef I2C2 
#define GPIO_AF0_I2C2          ((uint8_t)0x00)  /*!< I2C2 Alternate Function mapping                */
#endif /* I2C2 */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /*!< LPUART Alternate Function mapping              */
#define GPIO_AF0_RTC           ((uint8_t)0x00)  /*!< RTC Alternate Function mapping                 */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /*!< USART Alternate Function mapping               */
#ifdef SPI1 
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /*!< SPI1 Alternate Function mapping                */
#endif /* SPI1 */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_IR            ((uint8_t)0x01)  /*!< IR Alternate Function mapping                  */
#define GPIO_AF1_LCO           ((uint8_t)0x01)  /*!< LCO Alternate Function mapping                 */
#define GPIO_AF1_SWDIO         ((uint8_t)0x01)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF1_SWCLK         ((uint8_t)0x01)  /*!< SWCLK Alternate Function mapping               */
#ifdef SPI1 
#define GPIO_AF1_SPI1          ((uint8_t)0x01)  /*!< SPI1 Alternate Function mapping                */
#endif /* SPI1 */
#ifdef SPI2 
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /*!< SPI2 Alternate Function mapping                */
#endif /* SPI2 */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /*!< USART Alternate Function mapping               */
#define GPIO_AF1_LPUART1       ((uint8_t)0x01)  /*!< LPUART Alternate Function mapping              */
#define GPIO_AF1_PDM           ((uint8_t)0x01)  /*!< PDM Alternate Function mapping                 */
#ifdef I2C2 
#define GPIO_AF1_I2C2          ((uint8_t)0x01)  /*!< I2C2 Alternate Function mapping                */
#endif /* I2C2 */
#define GPIO_AF1_TX_SEQUENCE   ((uint8_t)0x01)  /*!< TX Sequence Alternate Function mapping         */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_IR            ((uint8_t)0x02)  /*!< IR Alternate Function mapping                  */
#define GPIO_AF2_MCO           ((uint8_t)0x02)  /*!< MCO Alternate Function mapping                 */
#ifdef SPI1  
#define GPIO_AF2_SPI1          ((uint8_t)0x02)  /*!< SPI1 Alternate Function mapping                */
#endif /* SPI1 */
#ifdef SPI2 
#define GPIO_AF2_SPI2          ((uint8_t)0x02)  /*!< SPI2 Alternate Function mapping                */
#endif /* SPI2 */
#ifdef TIM1 
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping                */
#endif /* TIM1 */
#ifdef TIM2 
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping                */
#endif /* TIM2 */
#ifdef TIM16 
#define GPIO_AF2_TIM16         ((uint8_t)0x02)  /*!< TIM16 Alternate Function mapping               */
#endif /* TIM16 */
#ifdef TIM17 
#define GPIO_AF2_TIM17         ((uint8_t)0x02)  /*!< TIM17 Alternate Function mapping               */
#endif /* TIM17 */
#define GPIO_AF2_LPUART        ((uint8_t)0x02)  /*!< LPUART Alternate Function mapping              */
#define GPIO_AF2_USART1        ((uint8_t)0x02)  /*!< USART Alternate Function mapping               */
#define GPIO_AF2_RTC           ((uint8_t)0x02)  /*!< RTC Alternate Function mapping                 */
#ifdef I2C1  
#define GPIO_AF2_I2C1          ((uint8_t)0x02)  /*!< I2C2 Alternate Function mapping                */
#endif /* I2C1 */
#define GPIO_AF2_PDM           ((uint8_t)0x02)  /*!< PDM Alternate Function mapping                 */
#define GPIO_AF2_TX_SEQUENCE   ((uint8_t)0x02)  /*!< TX_SEQUENCE Alternate Function mapping         */
#define GPIO_AF2_RX_SEQUENCE   ((uint8_t)0x02)  /*!< RX_SEQUENCE Alternate Function mapping         */
   
/**
  * @brief   AF 3 selection
  */
#ifdef SPI2
#define GPIO_AF3_SPI2           ((uint8_t)0x03)  /*!< SPI2 Alternate Function mapping               */
#endif /* SPI2 */
#ifdef SPI3 
#define GPIO_AF3_SPI3           ((uint8_t)0x03)  /*!< SPI3 Alternate Function mapping               */
#endif /* SPI3 */  
#ifdef TIM1 
#define GPIO_AF3_TIM1           ((uint8_t)0x03)  /*!< TIM1 Alternate Function mapping               */
#endif /* TIM1 */
#ifdef TIM2 
#define GPIO_AF3_TIM2           ((uint8_t)0x03)  /*!< TIM2 Alternate Function mapping               */
#endif /* TIM2 */
#define GPIO_AF3_PDM            ((uint8_t)0x03)  /*!< PDM Alternate Function mapping                */
#define GPIO_AF3_LPUART1        ((uint8_t)0x03)  /*!< LPUART Alternate Function mapping             */
#define GPIO_AF3_MCO            ((uint8_t)0x03)  /*!< MCO Alternate Function mapping                */

/**
  * @brief   AF 4 selection
  */
#ifdef TIM1 
#define GPIO_AF4_TIM1           ((uint8_t)0x04)  /*!< TIM1 Alternate Function mapping               */
#endif /* TIM1 */
#ifdef TIM2 
#define GPIO_AF4_TIM2           ((uint8_t)0x04)  /*!< TIM2 Alternate Function mapping               */
#endif /* TIM2 */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_ADC           ((uint8_t)0x05)  /*!< ADC Alternate Function mapping                 */
#define GPIO_AF5_SWDIO         ((uint8_t)0x05)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF5_SWCLK         ((uint8_t)0x05)  /*!< SWCLK Alternate Function mapping               */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_ANT           ((uint8_t)0x06)  /*!< ANT Alternate Function mapping                 */
#define GPIO_AF6_RXACTIVITY    ((uint8_t)0x06)  /*!< RXACTIVITY Alternate Function mapping          */
#ifdef TIM16 
#define GPIO_AF6_TIM16         ((uint8_t)0x06)  /*!< TIM16 Alternate Function mapping               */
#endif /* TIM16 */  
#ifdef TIM17 
#define GPIO_AF6_TIM17         ((uint8_t)0x06)  /*!< TIM17 Alternate Function mapping               */
#endif /* TIM17 */    
#define GPIO_AF6_USART         ((uint8_t)0x06)  /*!< USART Alternate Function mapping                 */  

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_RF_DTB        ((uint8_t)0x07)  /*!< RF DTB Alternate Function mapping              */
#define GPIO_AF7_SWDIO         ((uint8_t)0x07)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF7_SWCLK         ((uint8_t)0x07)  /*!< SWCLK Alternate Function mapping               */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /*!< USART Alternate Function mapping               */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

   
   
#ifdef STEVAL_S38681V1

#define GPIO_AF0_I2C1          ((uint8_t)0x00)  /*!< I2C1 Alternate Function mapping        */
#define GPIO_AF0_I2C2          ((uint8_t)0x00)  /*!< I2C2 Alternate Function mapping        */
#define GPIO_AF0_LCO           ((uint8_t)0x00)  /*!< LCO Alternate Function mapping         */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping         */
#define GPIO_AF0_RTC           ((uint8_t)0x00)  /*!< RTC Alternate Function mapping         */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /*!< USART Alternate Function mapping       */
#define GPIO_AF1_LPUART        ((uint8_t)0x01)  /*!< LPUART Alternate Function mapping      */
#define GPIO_AF1_LPUART1       ((uint8_t)0x01)  /*!< LPUART1 Alternate Function mapping     */
#define GPIO_AF1_USART         ((uint8_t)0x01)  /*!< USART Alternate Function mapping       */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /*!< USART1 Alternate Function mapping      */
#define GPIO_AF2_USART1        ((uint8_t)0x02)  /*!< USART1 Alternate Function mapping      */
#define GPIO_AF2_COMP1         ((uint8_t)0x02)  /*!< COMP1 Alternate Function mapping       */
#define GPIO_AF2_RF            ((uint8_t)0x02)  /*!< RF Alternate Function mapping          */
#define GPIO_AF2_RTC           ((uint8_t)0x02)  /*!< RTC Alternate Function mapping         */
#define GPIO_AF2_RX            ((uint8_t)0x02)  /*!< RX Alternate Function mapping          */
#define GPIO_AF2_TIM16         ((uint8_t)0x02)  /*!< TIM16 Alternate Function mapping       */
#define GPIO_AF2_LCO           ((uint8_t)0x02)  /*!< LCO Alternate Function mapping         */
#define GPIO_AF2_TX            ((uint8_t)0x02)  /*!< TX Alternate Function mapping          */
#define GPIO_AF3_MCO           ((uint8_t)0x03)  /*!< MCO Alternate Function mapping         */
#define GPIO_AF3_SPI1          ((uint8_t)0x03)  /*!< SPI1 Alternate Function mapping        */
#define GPIO_AF3_SPI3          ((uint8_t)0x03)  /*!< SPI3 Alternate Function mapping        */
#define GPIO_AF4_ADC           ((uint8_t)0x04)  /*!< ADC Alternate Function mapping         */
#define GPIO_AF4_ANTENNA       ((uint8_t)0x04)  /*!< ANTENNA Alternate Function mapping     */
#define GPIO_AF4_SUBG          ((uint8_t)0x04)  /*!< SUBG Alternate Function mapping        */
#define GPIO_AF4_TIM2          ((uint8_t)0x04)  /*!< TIM2 Alternate Function mapping        */
#define GPIO_AF5_ADC           ((uint8_t)0x05)  /*!< ADC Alternate Function mapping         */
#define GPIO_AF5_LCD           ((uint8_t)0x05)  /*!< LCD Alternate Function mapping         */
#define GPIO_AF6_LCD           ((uint8_t)0x06)  /*!< LCD Alternate Function mapping         */
#define GPIO_AF6_RF            ((uint8_t)0x06)  /*!< RF Alternate Function mapping          */
#define GPIO_AF7_RF            ((uint8_t)0x07)  /*!< RF Alternate Function mapping          */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

#endif /* STEVAL_S38681V1 */
   

/**
  * @}
  */ 

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Macros GPIOEx Exported Macros
  * @{
  */

/** @defgroup GPIOEx_Get_Port_Index GPIOEx Get Port Index
* @{
  */

#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL : 1uL)

 /**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/ 
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
