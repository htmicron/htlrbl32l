/**
  ******************************************************************************
  * @file    rf_driver_hal_pwr_ex.h
  * @author  RF Application Team
  * @brief   Header file of PWR HAL Extended module.
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
#ifndef RF_DRIVER_HAL_PWR_EX_H
#define RF_DRIVER_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief PWR Extended HAL module driver
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants  PWR Extended Exported Constants
  * @{
  */

/** @defgroup PWREx_GPIO_Bit_Number GPIO bit number for puul I/O setting
  * @{
  */
#define PWR_GPIO_BIT_0   PWR_PUCRA_PA0    /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1   PWR_PUCRA_PA1    /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2   PWR_PUCRA_PA2    /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3   PWR_PUCRA_PA3    /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4   PWR_PUCRA_PA4    /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5   PWR_PUCRA_PA5    /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6   PWR_PUCRA_PA6    /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7   PWR_PUCRA_PA7    /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8   PWR_PUCRA_PA8    /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9   PWR_PUCRA_PA9    /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10  PWR_PUCRA_PA10   /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11  PWR_PUCRA_PA11   /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12  PWR_PUCRA_PA12   /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13  PWR_PUCRA_PA13   /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_14  PWR_PUCRA_PA14   /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15  PWR_PUCRA_PA15   /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWREx_GPIO GPIO port
  * @{
  */
#define PWR_GPIO_A   0x00000000U      /*!< GPIO port A */
#define PWR_GPIO_B   0x00000001U      /*!< GPIO port B */
/**
  * @}
  */

/** @defgroup PWREx_SMPS_OPERATING_MODES SMPS step down converter operating modes
  * @{
  */
#define PWR_SMPS_BYPASS                 (PWR_SR2_SMPSBYPR) /*!< SMPS step down in bypass mode  */
#define PWR_SMPS_STEP_DOWN              (PWR_SR2_SMPSENR)  /*!< SMPS step down in step down mode */
/**
  * @}
  */

/** @defgroup PWREx_SMPS_OUTPUT_VOLTAGE_LEVEL SMPS step down converter output voltage scaling voltage level
  * @{
  */
/* Note: SMPS voltage is trimmed during device production to control
         the actual voltage level variation from device to device. */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V20  LL_PWR_SMPS_OUTLVL_1V2     /*!< SMPS step down converter supply output voltage 1.20V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V25  LL_PWR_SMPS_OUTLVL_1V25    /*!< SMPS step down converter supply output voltage 1.25V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V30  LL_PWR_SMPS_OUTLVL_1V3     /*!< SMPS step down converter supply output voltage 1.30V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V35  LL_PWR_SMPS_OUTLVL_1V35    /*!< SMPS step down converter supply output voltage 1.35V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V40  LL_PWR_SMPS_OUTLVL_1V4     /*!< SMPS step down converter supply output voltage 1.40V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V45  LL_PWR_SMPS_OUTLVL_1V45    /*!< SMPS step down converter supply output voltage 1.45V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V50  LL_PWR_SMPS_OUTLVL_1V5     /*!< SMPS step down converter supply output voltage 1.50V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V55  LL_PWR_SMPS_OUTLVL_1V55    /*!< SMPS step down converter supply output voltage 1.55V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V60  LL_PWR_SMPS_OUTLVL_1V6     /*!< SMPS step down converter supply output voltage 1.60V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V65  LL_PWR_SMPS_OUTLVL_1V65    /*!< SMPS step down converter supply output voltage 1.65V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V70  LL_PWR_SMPS_OUTLVL_1V7     /*!< SMPS step down converter supply output voltage 1.70V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V75  LL_PWR_SMPS_OUTLVL_1V75    /*!< SMPS step down converter supply output voltage 1.75V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V80  LL_PWR_SMPS_OUTLVL_1V8     /*!< SMPS step down converter supply output voltage 1.80V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V85  LL_PWR_SMPS_OUTLVL_1V85    /*!< SMPS step down converter supply output voltage 1.85V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V90  LL_PWR_SMPS_OUTLVL_1V9     /*!< SMPS step down converter supply output voltage 1.90V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V95  LL_PWR_SMPS_OUTLVL_1V95    /*!< SMPS step down converter supply output voltage 1.95V */
/**
  * @}
  */

/**
  * @}
  */
/* Private define ------------------------------------------------------------*/ 
/* Exported macros -----------------------------------------------------------*/
/* Private macros --------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#define IS_PWR_GPIO_BIT_NUMBER(BIT_NUMBER) (((BIT_NUMBER) & GPIO_PIN_MASK) != (uint32_t)0x00)
   
#define IS_PWR_GPIO(GPIO) (((GPIO) == PWR_GPIO_A) ||\
                           ((GPIO) == PWR_GPIO_B))

#define IS_PWR_SMPS_MODE(SMPS_MODE) (((SMPS_MODE) == PWR_SMPS_BYPASS)    ||\
                                     ((SMPS_MODE) == PWR_SMPS_STEP_DOWN))

#define IS_PWR_SMPS_OUTPUT_VOLTAGE(SMPS_OUTPUT_VOLTAGE) (((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V20) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V25) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V30) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V35) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V40) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V45) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V50) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V55) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V60) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V65) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V70) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V75) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V80) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V85) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V90) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V95))


/**
  * @}
  */
  

/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */
  
/** @addtogroup PWREx_Exported_Functions_Group1 Extended Peripheral Control functions 
  * @{
  */


/* Peripheral Control functions  **********************************************/
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void              HAL_PWREx_EnablePullUpPullDownConfig(void);
void              HAL_PWREx_DisablePullUpPullDownConfig(void);

HAL_StatusTypeDef HAL_PWREx_ConfigSMPS(uint32_t outputVoltage);
void              HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode);
uint32_t          HAL_PWREx_SMPS_GetMode(void);

void              HAL_PWREx_PVD_IRQHandler(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* RF_DRIVER_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
