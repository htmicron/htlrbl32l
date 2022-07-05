/**
  ******************************************************************************
  * @file    rf_driver_hal_adc_ex.h
  * @author  RF Application Team
  * @brief   Header file of ADC HAL extended module.
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
#ifndef RF_DRIVER_HAL_ADC_EX_H
#define RF_DRIVER_HAL_ADC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Types ADC Extended Exported Types
  * @{
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Constants ADC Extended Exported Constants
  * @{
  */



/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/** @defgroup ADCEx_Private_Macro_internal_HAL_driver ADC Extended Private Macros
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

// MA ALLORA METTILE NEL PUNTO CI... 
/**
  * @brief Verify the ADC channel setting.
  * @param __HANDLE__ ADC handle.
  * @param __CHANNEL__ programmed ADC channel. 
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_CHANNEL(__HANDLE__, __CHANNEL__) ((((__HANDLE__)->Instance) == ADC)  && \
                                                         (((__CHANNEL__) == ADC_CHANNEL_0)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_1)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_2)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_3)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_4)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_5)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_6)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_7)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_8)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_9)           || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_10)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_11)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_12)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_13)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_14)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_15)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_16)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_17)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_18)          || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_VREFINT)     || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR)  || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_VBAT)))

/**
  * @brief Verify the ADC channel setting in differential mode.
  * @param __HANDLE__ ADC handle.
  * @param __CHANNEL__ programmed ADC channel. 
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_DIFF_CHANNEL(__HANDLE__, __CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_1)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_2)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_3)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_4)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_5)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_6)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_7)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_8)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_9)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_10)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_11)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_12)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_13)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_14)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_15)       )

/**
  * @brief Verify the ADC single-ended input or differential mode setting.
  * @param __SING_DIFF__ programmed channel setting. 
  * @retval SET (__SING_DIFF__ is valid) or RESET (__SING_DIFF__ is invalid)
  */
#define IS_ADC_SINGLE_DIFFERENTIAL(__SING_DIFF__) (((__SING_DIFF__) == ADC_SINGLE_ENDED)      || \
                                                   ((__SING_DIFF__) == ADC_DIFFERENTIAL_ENDED)  )


/**
  * @brief Verify the ADC event type.
  * @param __EVENT__ ADC event.
  * @retval SET (__EVENT__ is valid) or RESET (__EVENT__ is invalid)
  */
#define IS_ADC_EVENT_TYPE(__EVENT__) (((__EVENT__) == ADC_EOSMP_EVENT) || \
                                     ((__EVENT__) == ADC_AWD_EVENT)    || \
                                     ((__EVENT__) == ADC_AWD2_EVENT)   || \
                                     ((__EVENT__) == ADC_AWD3_EVENT)   || \
                                     ((__EVENT__) == ADC_OVR_EVENT)    || \
                                     ((__EVENT__) == ADC_JQOVF_EVENT)  ) 

/**
  * @brief Verify the ADC oversampling ratio. 
  * @param __RATIO__ programmed ADC oversampling ratio.
  * @retval SET (__RATIO__ is a valid value) or RESET (__RATIO__ is invalid)
  */
#define IS_ADC_OVERSAMPLING_RATIO(__RATIO__)      (((__RATIO__) == ADC_OVERSAMPLING_RATIO_2   ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_4   ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_8   ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_16  ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_32  ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_64  ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_128 ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_256 ))



/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADCEx_Exported_Functions
  * @{
  */

/** @addtogroup ADCEx_Exported_Functions_Group1
  * @{
  */
/* IO operation functions *****************************************************/

/* ADC calibration */
// HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc, uint32_t SingleDiff);

/* Blocking mode: Polling */

/* Non-blocking mode: Interruption */

/* ADC retrieve conversion value intended to be used with polling or interruption */

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption) */

/* ADC group regular conversions stop */

/**
  * @}
  */

/** @addtogroup ADCEx_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions ***********************************************/

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

#endif /* RF_DRIVER_HAL_ADC_EX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
