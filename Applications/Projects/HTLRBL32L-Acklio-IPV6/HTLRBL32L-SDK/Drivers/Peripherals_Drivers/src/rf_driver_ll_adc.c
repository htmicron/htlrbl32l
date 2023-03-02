/**
  ******************************************************************************
  * @file    rf_driver_ll_adc.c
  * @author  RF Application Team
  * @brief   ADC LL module driver
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_ll_adc.h"
#include "rf_driver_ll_bus.h"

#ifdef  USE_FULL_ASSERT
  #include "rf_driver_assert.h"
#else
  #define assert_param(expr) ((void)0UL)
#endif

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined (ADC)

/** @addtogroup ADC_LL ADC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup ADC_LL_Private_Constants
  * @{
  */

#define ADC_SWITCH_SE_VIN_ALL                       (ADC_SWITCH_SE_VIN_0 | ADC_SWITCH_SE_VIN_1 | \
                                                     ADC_SWITCH_SE_VIN_2 | ADC_SWITCH_SE_VIN_3 | \
                                                     ADC_SWITCH_SE_VIN_4 | ADC_SWITCH_SE_VIN_5 | \
                                                     ADC_SWITCH_SE_VIN_6 | ADC_SWITCH_SE_VIN_7)

#define ADC_SEQ_1_SEQ_ALL                           (ADC_SEQ_1_SEQ0 | ADC_SEQ_1_SEQ1 | \
                                                     ADC_SEQ_1_SEQ2 | ADC_SEQ_1_SEQ3 | \
                                                     ADC_SEQ_1_SEQ4 | ADC_SEQ_1_SEQ5 | \
                                                     ADC_SEQ_1_SEQ6 | ADC_SEQ_1_SEQ7)

#define ADC_SEQ_2_SEQ_ALL                           (ADC_SEQ_2_SEQ8  | ADC_SEQ_2_SEQ9  | \
                                                     ADC_SEQ_2_SEQ10 | ADC_SEQ_2_SEQ11 | \
                                                     ADC_SEQ_2_SEQ12 | ADC_SEQ_2_SEQ13 | \
                                                     ADC_SEQ_2_SEQ14 | ADC_SEQ_2_SEQ15)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @addtogroup ADC_LL_Private_Macros
  * @{
  */

#define IS_LL_ADC_VOLTRANGE(__VALUE__)      (((__VALUE__) == LL_ADC_VIN_RANGE_1V2)   ||\
                                             ((__VALUE__) == LL_ADC_VIN_RANGE_2V4)   ||\
                                             ((__VALUE__) == LL_ADC_VIN_RANGE_3V6))

#define IS_LL_ADC_CHCODE(__VALUE__)         (((__VALUE__) == LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT)   ||\
                                             ((__VALUE__) == LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT)   ||\
                                             ((__VALUE__) == LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT)   ||\
                                             ((__VALUE__) == LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT)   ||\
                                             ((__VALUE__) == LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT)        ||\
                                             ((__VALUE__) == LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT)        ||\
                                             ((__VALUE__) == LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT)        ||\
                                             ((__VALUE__) == LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT)        ||\
                                             ((__VALUE__) == LL_ADC_CH_BATTERY_LEVEL_DETECTOR)           ||\
                                             ((__VALUE__) == LL_ADC_CH_TEMPERATURE_SENSOR))


/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_LL_Exported_Functions
  * @{
  */

/** @addtogroup ADC_LL_EF_Init
  * @{
  */


/**
  * @brief  Configure the input voltage range for all the inputs.
  * @param  ADCx ADC instance
  * @param  ADC_InitStructVoltRange pointer to a @ref LL_ADC_InitVoltRange structure
  *         that contains the voltage range for all the inputs.
  * @retval None
  */
ErrorStatus LL_ADC_ConfigureVoltageRange(ADC_TypeDef *ADCx, LL_ADC_InitVoltRange *ADC_InitStructVoltRange)
{
  ErrorStatus status = SUCCESS;
  uint32_t tmpval = 0;

  assert_param(IS_ADC_ALL_INSTANCE(ADCx));
  assert_param(IS_LL_ADC_VOLTRANGE(ADC_InitStructVoltRange->InputVinm0_Vinp0Vinm0));
  assert_param(IS_LL_ADC_VOLTRANGE(ADC_InitStructVoltRange->InputVinm1_Vinp1Vinm1));
  assert_param(IS_LL_ADC_VOLTRANGE(ADC_InitStructVoltRange->InputVinm2_Vinp2Vinm2));
  assert_param(IS_LL_ADC_VOLTRANGE(ADC_InitStructVoltRange->InputVinm3_Vinp3Vinm3));
  assert_param(IS_LL_ADC_VOLTRANGE(ADC_InitStructVoltRange->InputVinp0));
  assert_param(IS_LL_ADC_VOLTRANGE(ADC_InitStructVoltRange->InputVinp1));
  assert_param(IS_LL_ADC_VOLTRANGE(ADC_InitStructVoltRange->InputVinp2));
  assert_param(IS_LL_ADC_VOLTRANGE(ADC_InitStructVoltRange->InputVinp3));

  tmpval |= (ADC_InitStructVoltRange->InputVinm0_Vinp0Vinm0);
  tmpval |= (ADC_InitStructVoltRange->InputVinm1_Vinp1Vinm1)<<ADC_SWITCH_SE_VIN_1_Pos;
  tmpval |= (ADC_InitStructVoltRange->InputVinm2_Vinp2Vinm2)<<ADC_SWITCH_SE_VIN_2_Pos;
  tmpval |= (ADC_InitStructVoltRange->InputVinm3_Vinp3Vinm3)<<ADC_SWITCH_SE_VIN_3_Pos;
  tmpval |= (ADC_InitStructVoltRange->InputVinp0)<<ADC_SWITCH_SE_VIN_4_Pos;
  tmpval |= (ADC_InitStructVoltRange->InputVinp1)<<ADC_SWITCH_SE_VIN_5_Pos;
  tmpval |= (ADC_InitStructVoltRange->InputVinp2)<<ADC_SWITCH_SE_VIN_6_Pos;
  tmpval |= (ADC_InitStructVoltRange->InputVinp3)<<ADC_SWITCH_SE_VIN_7_Pos;

  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_ALL, tmpval);
  
  return (status);
}


/**
  * @brief  Get the input voltage range for all the inputs.
  * @param  ADCx ADC instance
  * @param  ADC_InitStructVoltRange pointer to a @ref LL_ADC_InitVoltRange structure
  *         that contains the voltage range for all the inputs.
  * @retval None
  */
void LL_ADC_GetVoltageRange(ADC_TypeDef *ADCx, LL_ADC_InitVoltRange *ADC_InitStructVoltRange)
{
  uint32_t tmpval = 0;

  assert_param(IS_ADC_ALL_INSTANCE(ADCx));

  tmpval = READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_ALL);

  ADC_InitStructVoltRange->InputVinm0_Vinp0Vinm0 = tmpval & ADC_SWITCH_SE_VIN_0;
  ADC_InitStructVoltRange->InputVinm1_Vinp1Vinm1 = (tmpval >> ADC_SWITCH_SE_VIN_1_Pos) & ADC_SWITCH_SE_VIN_1;
  ADC_InitStructVoltRange->InputVinm2_Vinp2Vinm2 = (tmpval >> ADC_SWITCH_SE_VIN_2_Pos) & ADC_SWITCH_SE_VIN_2;
  ADC_InitStructVoltRange->InputVinm3_Vinp3Vinm3 = (tmpval >> ADC_SWITCH_SE_VIN_3_Pos) & ADC_SWITCH_SE_VIN_3;
  ADC_InitStructVoltRange->InputVinp0 = (tmpval >> ADC_SWITCH_SE_VIN_4_Pos) & ADC_SWITCH_SE_VIN_4;
  ADC_InitStructVoltRange->InputVinp1 = (tmpval >> ADC_SWITCH_SE_VIN_5_Pos) & ADC_SWITCH_SE_VIN_5;
  ADC_InitStructVoltRange->InputVinp2 = (tmpval >> ADC_SWITCH_SE_VIN_6_Pos) & ADC_SWITCH_SE_VIN_6;
  ADC_InitStructVoltRange->InputVinp3 = (tmpval >> ADC_SWITCH_SE_VIN_7_Pos) & ADC_SWITCH_SE_VIN_7;
  
}


/**
  * @brief  Configure the channels for the conversion sequence.
  * @param  ADCx ADC instance
  * @param  ADC_InitChannelsForSeq pointer to a @ref LL_ADC_InitChannelsForSeq structure
  *         that contains the channel codes for the conversion sequence.
  * @retval ErrorStatus
  */
ErrorStatus LL_ADC_ConfigureChannelsForSequence(ADC_TypeDef *ADCx, LL_ADC_InitChannelsForSeq *ADC_InitChannelsForSeq)
{
  ErrorStatus status = SUCCESS;
  uint32_t tmpval = 0;

  assert_param(IS_ADC_ALL_INSTANCE(ADCx));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq0));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq1));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq2));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq3));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq4));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq5));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq6));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq7));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq8));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq9));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq10));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq11));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq12));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq13));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq14));
  assert_param(IS_LL_ADC_CHCODE(ADC_InitChannelsForSeq->ChannelForSeq15));

  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq0);
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq1)<<ADC_SEQ_1_SEQ1_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq2)<<ADC_SEQ_1_SEQ2_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq3)<<ADC_SEQ_1_SEQ3_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq4)<<ADC_SEQ_1_SEQ4_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq5)<<ADC_SEQ_1_SEQ5_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq6)<<ADC_SEQ_1_SEQ6_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq7)<<ADC_SEQ_1_SEQ7_Pos;

  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ_ALL, tmpval);
  
  tmpval = 0;

  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq8 );
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq9 )<<ADC_SEQ_2_SEQ9_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq10)<<ADC_SEQ_2_SEQ10_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq11)<<ADC_SEQ_2_SEQ11_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq12)<<ADC_SEQ_2_SEQ12_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq13)<<ADC_SEQ_2_SEQ13_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq14)<<ADC_SEQ_2_SEQ14_Pos;
  tmpval |= (ADC_InitChannelsForSeq->ChannelForSeq15)<<ADC_SEQ_2_SEQ15_Pos;

  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ_ALL, tmpval);

  return (status);
}


/**
  * @brief  Get the channels for the conversion sequence.
  * @param  ADCx ADC instance
  * @param  ADC_InitChannelsForSeq pointer to a @ref LL_ADC_InitChannelsForSeq structure
  *         that contains the channel codes for the conversion sequence.
  * @retval None
  */
void LL_ADC_GetChannelsForSequence(ADC_TypeDef *ADCx, LL_ADC_InitChannelsForSeq *ADC_InitChannelsForSeq)
{
  uint32_t tmpval = 0;

  assert_param(IS_ADC_ALL_INSTANCE(ADCx));

  tmpval = READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ_ALL);

  ADC_InitChannelsForSeq->ChannelForSeq0 = tmpval & ADC_SEQ_1_SEQ0;
  ADC_InitChannelsForSeq->ChannelForSeq1 = (tmpval >> ADC_SEQ_1_SEQ1_Pos) & ADC_SEQ_1_SEQ1;
  ADC_InitChannelsForSeq->ChannelForSeq2 = (tmpval >> ADC_SEQ_1_SEQ2_Pos) & ADC_SEQ_1_SEQ2;
  ADC_InitChannelsForSeq->ChannelForSeq3 = (tmpval >> ADC_SEQ_1_SEQ3_Pos) & ADC_SEQ_1_SEQ3;
  ADC_InitChannelsForSeq->ChannelForSeq4 = (tmpval >> ADC_SEQ_1_SEQ4_Pos) & ADC_SEQ_1_SEQ4;
  ADC_InitChannelsForSeq->ChannelForSeq5 = (tmpval >> ADC_SEQ_1_SEQ5_Pos) & ADC_SEQ_1_SEQ5;
  ADC_InitChannelsForSeq->ChannelForSeq6 = (tmpval >> ADC_SEQ_1_SEQ6_Pos) & ADC_SEQ_1_SEQ6;
  ADC_InitChannelsForSeq->ChannelForSeq7 = (tmpval >> ADC_SEQ_1_SEQ7_Pos) & ADC_SEQ_1_SEQ7;
  
  tmpval = READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ_ALL);

  ADC_InitChannelsForSeq->ChannelForSeq8  = tmpval & ADC_SEQ_2_SEQ8;
  ADC_InitChannelsForSeq->ChannelForSeq9  = (tmpval >> ADC_SEQ_2_SEQ9_Pos) & ADC_SEQ_2_SEQ9;
  ADC_InitChannelsForSeq->ChannelForSeq10 = (tmpval >> ADC_SEQ_2_SEQ10_Pos) & ADC_SEQ_2_SEQ10;
  ADC_InitChannelsForSeq->ChannelForSeq11 = (tmpval >> ADC_SEQ_2_SEQ11_Pos) & ADC_SEQ_2_SEQ11;
  ADC_InitChannelsForSeq->ChannelForSeq12 = (tmpval >> ADC_SEQ_2_SEQ12_Pos) & ADC_SEQ_2_SEQ12;
  ADC_InitChannelsForSeq->ChannelForSeq13 = (tmpval >> ADC_SEQ_2_SEQ13_Pos) & ADC_SEQ_2_SEQ13;
  ADC_InitChannelsForSeq->ChannelForSeq14 = (tmpval >> ADC_SEQ_2_SEQ14_Pos) & ADC_SEQ_2_SEQ14;
  ADC_InitChannelsForSeq->ChannelForSeq15 = (tmpval >> ADC_SEQ_2_SEQ15_Pos) & ADC_SEQ_2_SEQ15;

}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* ADC */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
