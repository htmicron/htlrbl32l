/**
  ******************************************************************************
  * @file    rf_driver_hal_pwr.h
  * @author  RF Application Team
  * @brief   Header file of PWR HAL module.
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
#ifndef RF_DRIVER_HAL_PWR_H
#define RF_DRIVER_HAL_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"

/* Include low level driver */
#include "rf_driver_ll_pwr.h"
#include "rf_driver_ll_exti.h"

/* Include PWR HAL Extended module */
#include "rf_driver_hal_pwr_ex.h"
   
/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */

/**
  * @brief  PWR PVD configuration structure definition
  */
typedef struct
{
  uint32_t PVDLevel;       /*!< PVDLevel: Specifies the PVD detection level.
                                This parameter can be a value of @ref PWR_PVD_detection_level. */

  uint32_t Mode;           /*!< Mode: Specifies the operating mode for the selected pins.
                                This parameter can be a value of @ref PWR_PVD_Mode. */
}PWR_PVDTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_PVD_detection_level  Power Voltage Detector Level selection
  * @note     Refer datasheet for selection voltage value
  * @{
  */
#define PWR_PVDLEVEL_0                  LL_PWR_PVDLEVEL_0   /*!< PVD threshold around 2.05 V */
#define PWR_PVDLEVEL_1                  LL_PWR_PVDLEVEL_1   /*!< PVD threshold around 2.20 V */
#define PWR_PVDLEVEL_2                  LL_PWR_PVDLEVEL_2   /*!< PVD threshold around 2.36 V */
#define PWR_PVDLEVEL_3                  LL_PWR_PVDLEVEL_3   /*!< PVD threshold around 2.52 V */
#define PWR_PVDLEVEL_4                  LL_PWR_PVDLEVEL_4   /*!< PVD threshold around 2.64 V */
#define PWR_PVDLEVEL_5                  LL_PWR_PVDLEVEL_5   /*!< PVD threshold around 2.81 V */
#define PWR_PVDLEVEL_6                  LL_PWR_PVDLEVEL_6   /*!< PVD threshold around 2.91 V */
#define PWR_PVDLEVEL_7                  LL_PWR_PVDLEVEL_7   /*!< External input analog voltage (compared internally to VREFINT for BlueNRG-LP ) */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode  PWR PVD interrupt and event mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL                 (0x00000000U)                  /*!< Basic mode is used */
#define PWR_PVD_MODE_IT                     (SYSCFG_PWRC_IER_PVD_IE)       /*!< Interrupt Mode detection */
/**
  * @}
  */

/**
  * @}
  */

/* Private define ------------------------------------------------------------*/ 
/* Exported macros -----------------------------------------------------------*/
/** @defgroup PWR_Exported_Macros  PWR Exported Macros
  * @{
  */
/**
  * @brief Enable the PVD Line.
  * @retval None
  */
#define __HAL_PWR_PVD_ENABLE_IT()   SET_BIT(SYSCFG->PWRC_IER, SYSCFG_PWRC_IER_PVD_IE)

/**
  * @brief Disable the PVD Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVD_DISABLE_IT()  CLEAR_BIT(SYSCFG->PWRC_IER, SYSCFG_PWRC_IER_PVD_IE)


/**
  * @brief Check whether or not the PVD interrupt flag is set.
  * @retval PVD Line Status.
  */
#define __HAL_PWR_PVD_GET_FLAG()  (READ_BIT(SYSCFG->PWRC_ISCR, SYSCFG_PWRC_ISCR_PVD_ISC) == (SYSCFG_PWRC_ISCR_PVD_ISC)) ? 1UL : 0U

/**
  * @brief Clear the PVD interrupt flag.
  * @retval None
  */
#define __HAL_PWR_PVD_CLEAR_FLAG()  SET_BIT(SYSCFG->PWRC_ISCR, SYSCFG_PWRC_ISCR_PVD_ISC)

/**
  * @}
  */
  

/* Private macros --------------------------------------------------------*/
/** @defgroup PWR_Private_Macros  PWR Private Macros
  * @{
  */

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLEVEL_0) || ((LEVEL) == PWR_PVDLEVEL_1)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_2) || ((LEVEL) == PWR_PVDLEVEL_3)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_4) || ((LEVEL) == PWR_PVDLEVEL_5)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_6) || ((LEVEL) == PWR_PVDLEVEL_7))

                                 
#define IS_PWR_PVD_MODE(MODE)  (((MODE) == PWR_PVD_MODE_NORMAL)              ||\
                                ((MODE) == PWR_PVD_MODE_IT))


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions  PWR Exported Functions
  * @{
  */

/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void              HAL_PWR_EnablePVD(void);
void              HAL_PWR_DisablePVD(void);
void              HAL_PWR_PVDCallback(void);
   
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


#endif /* RF_DRIVER_HAL_PWR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
