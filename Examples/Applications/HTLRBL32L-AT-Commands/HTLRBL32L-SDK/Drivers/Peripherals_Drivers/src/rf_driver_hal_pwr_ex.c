/**
  ******************************************************************************
  * @file    rf_driver_hal_pwr_ex.c
  * @author  RF Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Extended Peripheral Control functions
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

/** @addtogroup PWREx
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */
  
/****************************************************************************/

/**
  * @brief Enable GPIO pull-up state in DeepStop and Shutdown modes.
  * @note  Set the relevant PUy bits of PWR_PUCRx register to configure the I/O in 
  *        pull-up state in DeepStop and Shutdown modes. 
  * @note  This state is effective in DeepStop and Shutdown modes only if APC bit 
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is lost when exiting the Shutdown mode due to the 
  *        power-on reset, maintained when exiting the  mode. 
  * @note  To avoid any conflict at DeepStop and Shutdown modes exits, the corresponding
  *        PDy bit of PWR_PDCRx register is cleared unless it is reserved. 
  * @note  Even if a PUy bit to set is reserved, the other PUy bits entered as input 
  *        parameter at the same time are set.     
  * @param GPIO Specify the IO port. This parameter can be PWR_GPIO_A, PWR_GPIO_B 
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 or the logical OR 
  *         of several of them to setseveral bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{  
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
       SET_BIT(PWR->PUCRA, GPIONumber);
       CLEAR_BIT(PWR->PDCRA, GPIONumber);
       break;
    case PWR_GPIO_B:
       SET_BIT(PWR->PUCRB, GPIONumber);
       CLEAR_BIT(PWR->PDCRB, GPIONumber);
       break; 
    default:
      status = HAL_ERROR;
      break;
  }
       
  return status;
}

/**
  * @brief Disable GPIO pull-up state in DeepStop mode and Shutdown modes.
  * @note  Reset the relevant PUy bits of PWR_PUCRx register used to configure the I/O
  *        in pull-up state in DeepStop and Shutdown modes.
  * @note  Even if a PUy bit to reset is reserved, the other PUy bits entered as input 
  *        parameter at the same time are reset.
  * @param GPIO Specifies the IO port. This parameter can be PWR_GPIO_A, PWR_GPIO_B 
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 
  *         or the logical OR of several of them to reset 
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */   
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{  
  HAL_StatusTypeDef status = HAL_OK;
  
  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));
  
  switch (GPIO)
  {
    case PWR_GPIO_A:
       CLEAR_BIT(PWR->PUCRA, GPIONumber);
       break;
    case PWR_GPIO_B:
       CLEAR_BIT(PWR->PUCRB, GPIONumber);
       break; 
default:
       status = HAL_ERROR;
       break;
  }
  
  return status;
}



/**
  * @brief Enable GPIO pull-down state in DeepStop and Shutdown modes.
  * @note  Set the relevant PDy bits of PWR_PDCRx register to configure the I/O in 
  *        pull-down state in DeepStop and Shutdown modes. 
  * @note  This state is effective in DeepStop and Shutdown modes only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API. 
  * @note  The configuration is lost when exiting the Shutdown mode due to the 
  *        power-on reset, maintained when exiting the DeepStop mode. 
  * @note  To avoid any conflict at DeepStop and Shutdown modes exits, the corresponding
  *        PUy bit of PWR_PUCRx register is cleared unless it is reserved. 
  * @note  Even if a PDy bit to set is reserved, the other PDy bits entered as input 
  *        parameter at the same time are set.         
  * @param GPIO Specify the IO port. This parameter can be PWR_GPIO_A, PWR_GPIO_B 
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15
  *         or the logical OR of several of them to set 
  *         several bits for a given port in a single API call. 
  * @retval HAL Status
  */   
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));
  
  switch (GPIO)
  { 
    case PWR_GPIO_A:
       SET_BIT(PWR->PDCRA, GPIONumber);
       CLEAR_BIT(PWR->PUCRA, GPIONumber);
       break;
    case PWR_GPIO_B:
       SET_BIT(PWR->PDCRB, GPIONumber);
       CLEAR_BIT(PWR->PUCRB, GPIONumber);
       break; 
    default:
      status = HAL_ERROR;
      break;
  }
       
  return status;
}

/**
  * @brief Disable GPIO pull-down state in DeepStop and Shutdown modes.
  * @note  Reset the relevant PDy bits of PWR_PDCRx register used to configure the I/O
  *        in pull-down state in DeepStop and Shutdown modes. 
  * @note  Even if a PDy bit to reset is reserved, the other PDy bits entered as input 
  *        parameter at the same time are reset.
  * @param GPIO Specifies the IO port. This parameter can be PWR_GPIO_A, PWR_GPIO_B 
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 
  *         or the logical OR of several of them to reset
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */   
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));
   
  switch (GPIO)
  {
    case PWR_GPIO_A:
       CLEAR_BIT(PWR->PDCRA, GPIONumber);
       break;
    case PWR_GPIO_B:
       CLEAR_BIT(PWR->PDCRB, GPIONumber);
       break; 
    default:
      status = HAL_ERROR;
      break;
  }
  
  return status;
}

/**
  * @brief Enable pull-up and pull-down configuration.
  * @note  When APC bit is set, the I/O pull-up and pull-down configurations defined in 
  *        PWR_PUCRx and PWR_PDCRx registers are applied in DeepStop and Shutdown modes.    
  * @note  Pull-up set by PUy bit of PWR_PUCRx register is not activated if the corresponding
  *        PDy bit of PWR_PDCRx register is also set (pull-down configuration priority is higher). 
  *        HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() API's ensure there 
  *        is no conflict when setting PUy or PDy bit.
  * @retval None
  */
void HAL_PWREx_EnablePullUpPullDownConfig(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief Disable pull-up and pull-down configuration.
  * @note  When APC bit is cleared, the I/O pull-up and pull-down configurations defined in 
  *        PWR_PUCRx and PWR_PDCRx registers are not applied in DeepStop and Shutdown modes.     
  * @retval None
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_APC);
}

/****************************************************************************/

/**
  * @brief Configure the SMPS step down converter.
  * @param outputVoltage SMPS output voltage configuration.
  *         This parameter can be one of the following values:
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V20
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V25
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V30
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V35
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V40
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V45
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V50
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V55
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V60
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V65
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V70
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V75
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V80
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V85
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V90
  *         - PWR_SMPS_OUTPUT_VOLTAGE_1V95
  *         
  * @note  To set and enable SMPS operating mode, refer to function
  *        "HAL_PWREx_SMPS_SetMode()".
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSMPS(uint32_t outputVoltage)
{
  /* Check the parameter */
  assert_param(IS_PWR_SMPS_OUTPUT_VOLTAGE(outputVoltage));
  
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLVL, outputVoltage);
  
  return HAL_OK;
}

/**
  * @brief Set SMPS operating mode.
  * @param  OperatingMode This parameter can be one of the following values:
  *         @arg @ref PWR_SMPS_BYPASS
  *         @arg @ref PWR_SMPS_STEP_DOWN
  *
  * @retval None
  */
void HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode)
{
   /* Check the parameter */
  assert_param(IS_PWR_SMPS_MODE(OperatingMode));

  if (OperatingMode == PWR_SMPS_BYPASS)
  {
    SET_BIT(PWR->CR5, PWR_CR5_NOSMPS);
    SET_BIT(PWR->CR5, PWR_CR5_SMPSFBYP);
  }
  else
  {
    CLEAR_BIT(PWR->CR5, PWR_CR5_SMPSFBYP);    
    CLEAR_BIT(PWR->CR5, PWR_CR5_NOSMPS);
  }
}

/**
  * @brief  Get SMPS operating mode
  * @retval Returned value can be one of the following values:
  *         @arg @ref PWR_SMPS_BYPASS
  *         @arg @ref PWR_SMPS_STEP_DOWN
  */
uint32_t HAL_PWREx_SMPS_GetMode(void)
{  
  return (uint32_t)(READ_BIT(PWR->SR2, (PWR_SR2_SMPSENR | PWR_SR2_SMPSBYPR)));
}

/****************************************************************************/

void HAL_PWREx_PVD_IRQHandler(void)
{
  /* Check PWR flag */
  if(__HAL_PWR_PVD_GET_FLAG() != 0U)
  {
    /* PWR PVD interrupt user callback */
    HAL_PWR_PVDCallback();

    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_CLEAR_FLAG();
  }
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
