/**
  ******************************************************************************
  * @file    rf_driver_hal_pwr.c
  * @author  RF Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Power Voltage Detector functions
  *
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

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/ 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup PWR_Private_Defines
  * @{
  */

 /**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions  PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group  Peripheral Control functions
  *  @brief Low Power modes configuration functions
  *
@verbatim

 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================

    [..]
     *** PVD configuration ***
    =========================
    [..]
      (+) The PVD is used to monitor the VDD power supply by comparing it to a
          threshold selected by the PVD Level (PVDLS[2:0] bits in PWR_CR2 register).
      (+) PVDO flag is available to indicate if VDD/VDDA is higher or lower
          than the PVD threshold. This event can generate an interrupt if enabled. 
          This is done through  __HAL_PVD_ENABLE_IT() macro.
      (+) The PVD is stopped in Shutdown mode.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector (PVD).
  * @param  sConfigPVD pointer to a PWR_PVDTypeDef structure that contains the PVD 
  *         configuration information.
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage thresholds corresponding to each
  *         detection level.
  * @retval None
  */
HAL_StatusTypeDef HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Set PVDLS bits according to PVDLevel value */
  MODIFY_REG(PWR->CR2, PWR_CR2_PVDLS, sConfigPVD->PVDLevel);
  
  /* Clear any previous config. Keep it clear if IT mode is selected */
  __HAL_PWR_PVD_DISABLE_IT();
    
  /* Configure interrupt mode */
  if((sConfigPVD->Mode & PWR_PVD_MODE_IT) == PWR_PVD_MODE_IT)
  {
    __HAL_PWR_PVD_ENABLE_IT();
  }
  
  return HAL_OK;
}

/**
  * @brief Enables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_EnablePVD(void)
{
  /* Enable the power voltage detector */
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief Disables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_DisablePVD(void)
{
  /* Disable the power voltage detector */
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}


/**
  * @brief  PWR PVD interrupt callback
  * @retval None
  */
WEAK_FUNCTION(void HAL_PWR_PVDCallback(void))
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVDCallback can be implemented in the user file
  */
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_PWR_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
