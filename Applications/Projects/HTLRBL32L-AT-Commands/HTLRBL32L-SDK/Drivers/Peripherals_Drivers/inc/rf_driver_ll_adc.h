/**
  ******************************************************************************
  * @file    rf_driver_ll_adc.h
  * @author  RF Application Team
  * @brief   Header file of ADC LL module.
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
#ifndef RF_DRIVER_LL_ADC_H
#define RF_DRIVER_LL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined (ADC)

/** @defgroup ADC_LL ADC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Constants ADC Private Constants
  * @{
  */

/* Uncomment this symbol to use the version with floating point of the conversion functions */
#define BLE_ADC_OUTPUT_FLOAT

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Macros ADC Private Macros
  * @{
  */


/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup ADC_LL_ES_INIT ADC Exported Init structure
  * @{
  */


/**
  * @brief  Structure definition containing the input voltage range
  *         for each type of ADC input channel.
  */
typedef struct
{
  uint8_t InputVinm0_Vinp0Vinm0;             /*!< Set the input voltage range for single VINM0 or differential (VINP0 - VINM0).
                                             This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetVoltageRangeVinX() with X = 1, 2, ...7 */

  uint8_t InputVinm1_Vinp1Vinm1;             /*!< Set the input voltage range for single VINM1 or differential (VINP1 - VINM1).
                                             This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetVoltageRangeVinX() with X = 1, 2, ...7 */

  uint8_t InputVinm2_Vinp2Vinm2;             /*!< Set the input voltage range for single VINM2 or differential (VINP2 - VINM2).
                                             This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetVoltageRangeVinX() with X = 1, 2, ...7 */

  uint8_t InputVinm3_Vinp3Vinm3;             /*!< Set the input voltage range for single VINM3 or differential (VINP3 - VINM3).
                                             This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetVoltageRangeVinX() with X = 1, 2, ...7 */

  uint8_t InputVinp0;                        /*!< Set the input voltage range for single VINP0.
                                             This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetVoltageRangeVinX() with X = 1, 2, ...7 */

  uint8_t InputVinp1;                        /*!< Set the input voltage range for single VINP1.
                                             This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetVoltageRangeVinX() with X = 1, 2, ...7 */

  uint8_t InputVinp2;                        /*!< Set the input voltage range for single VINP2.
                                             This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetVoltageRangeVinX() with X = 1, 2, ...7 */

  uint8_t InputVinp3;                        /*!< Set the input voltage range for single VINP3.
                                             This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetVoltageRangeVinX() with X = 1, 2, ...7 */

} LL_ADC_InitVoltRange;


/**
  * @brief  Structure definition with the input channel entry
  *         for each element of the conversion sequence.
  */
typedef struct
{
  uint8_t ChannelForSeq0;                 /*!< Set the channel number code for the 1st conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq1;                 /*!< Set the channel number code for the 2nd conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq2;                 /*!< Set the channel number code for the 3rd conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq3;                 /*!< Set the channel number code for the 4th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq4;                 /*!< Set the channel number code for the 5th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq5;                 /*!< Set the channel number code for the 6th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq6;                 /*!< Set the channel number code for the 7th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq7;                 /*!< Set the channel number code for the 8th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq8;                 /*!< Set the channel number code for the 9th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq9;                 /*!< Set the channel number code for the 10th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq10;                /*!< Set the channel number code for the 11th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq11;                /*!< Set the channel number code for the 12th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq12;                /*!< Set the channel number code for the 13th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq13;                /*!< Set the channel number code for the 14th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq14;                /*!< Set the channel number code for the 15th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

  uint8_t ChannelForSeq15;                /*!< Set the channel number code for the 16th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CH_NUM_CODE                                             
                                             This feature can be modified afterwards using unitary function @ref LL_ADC_SetChannelSeqX() with X = 0, 1, ...15 */

} LL_ADC_InitChannelsForSeq;


/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/


/** @defgroup ADC_LL_Exported_Constants ADC Exported Constants
  * @{
  */


/** @defgroup ADC_LL_SAMPLING_METHOD  ADC input sampling method definitions
  * @brief    It defines the parameters used for the functions LL_ADC_InputSamplingMode() and LL_ADC_GetInputSamplingMode()
  * @{
  */

#define LL_ADC_SAMPLING_AT_START    (0x00000000UL)             /*!< Sampling only at conversion start (default) */
#define LL_ADC_SAMPLING_AT_END      (ADC_CONF_ADC_CONT_1V2)    /*!< Sampling starts at the end of conversion   */

/**
  * @}
  */


/** @defgroup ADC_LL_OVERRUN_CONFIG ADC overrun configuration definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetOverrunDF(), LL_ADC_GetOverrunDF(), LL_ADC_SetOverrunDS(), and LL_ADC_GetOverrunDS()
  * @{
  */

#define LL_ADC_NEW_DATA_IS_LOST    (ADC_CONF_OVR_DS_CFG)    /*!< The previous data is lost, the new one is kept */
#define LL_ADC_NEW_DATA_IS_KEPT    (0x00000000UL)           /*!< The previous data is kept, the new one is lost */

/**
  * @}
  */


#if defined(ADC_CONF_SAMPLE_RATE_MSB)
/** @defgroup ADC_LL_SAMPLE_RATE ADC sample rate definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetSampleRate() and LL_ADC_GetSampleRate()
  *           The  ADC conversion rate is: System clock / (16 + 16*SAMPLE_RATE_MSB + 4*SAMPLE_RATE)
  * @{
  */

#define LL_ADC_SAMPLE_RATE_MSB_0        (0x00000000UL)
#define LL_ADC_SAMPLE_RATE_MSB_1        (1<<ADC_CONF_SAMPLE_RATE_MSB_Pos)
#define LL_ADC_SAMPLE_RATE_MSB_2        (2<<ADC_CONF_SAMPLE_RATE_MSB_Pos)
#define LL_ADC_SAMPLE_RATE_MSB_3        (3<<ADC_CONF_SAMPLE_RATE_MSB_Pos)
#define LL_ADC_SAMPLE_RATE_MSB_4        (4<<ADC_CONF_SAMPLE_RATE_MSB_Pos)
#define LL_ADC_SAMPLE_RATE_MSB_5        (5<<ADC_CONF_SAMPLE_RATE_MSB_Pos)
#define LL_ADC_SAMPLE_RATE_MSB_6        (6<<ADC_CONF_SAMPLE_RATE_MSB_Pos)
#define LL_ADC_SAMPLE_RATE_MSB_7        (7<<ADC_CONF_SAMPLE_RATE_MSB_Pos)

#define LL_ADC_SAMPLE_RATE_0        (0x00000000UL)
#define LL_ADC_SAMPLE_RATE_1        (1<<ADC_CONF_SAMPLE_RATE_Pos)
#define LL_ADC_SAMPLE_RATE_2        (2<<ADC_CONF_SAMPLE_RATE_Pos)
#define LL_ADC_SAMPLE_RATE_3        (3<<ADC_CONF_SAMPLE_RATE_Pos)

/**
  * @}
  */

#else

/** @defgroup ADC_LL_SAMPLE_RATE ADC sample rate definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetSampleRate() and LL_ADC_GetSampleRate()
  * @{
  */

#define LL_ADC_SAMPLE_RATE_16    (0x00000000UL)                 /*!< ADC conversion rate at System clock / 16 */
#define LL_ADC_SAMPLE_RATE_20    (1<<ADC_CONF_SAMPLE_RATE_Pos)  /*!< ADC conversion rate at System clock / 20 */
#define LL_ADC_SAMPLE_RATE_24    (2<<ADC_CONF_SAMPLE_RATE_Pos)  /*!< ADC conversion rate at System clock / 24 */
#define LL_ADC_SAMPLE_RATE_28    (3<<ADC_CONF_SAMPLE_RATE_Pos)  /*!< ADC conversion rate at System clock / 28 */

/**
  * @}
  */
#endif


/** @defgroup ADC_LL_OP_MODE ADC operation modes definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetADCMode() and LL_ADC_GetADCMode()
  * @{
  */

#if defined(ADC_CONF_OP_MODE)
#define LL_ADC_OP_MODE_AUDIO    (1<<ADC_CONF_OP_MODE_Pos)  /*!< ADC operation mode AUDIO */
#define LL_ADC_OP_MODE_ADC      (2<<ADC_CONF_OP_MODE_Pos)  /*!< ADC operation mode ADC   */
#define LL_ADC_OP_MODE_FULL     (3<<ADC_CONF_OP_MODE_Pos)  /*!< ADC operation Full mode  */
#else
#define LL_ADC_OP_MODE_ADC      (2<<7)  /*!< ADC operation mode ADC   */
#endif
/**
  * @}
  */


/** @defgroup ADC_LL_SEQUENCE_LEN ADC sequence length definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetSequenceLength() and LL_ADC_GetSequenceLength()
  * @{
  */

#define LL_ADC_SEQ_LEN_01    (0x00000000UL)             /*!< The sequence is of 1 conversion */
#define LL_ADC_SEQ_LEN_02    (1<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 2 conversions */
#define LL_ADC_SEQ_LEN_03    (2<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 3 conversions */
#define LL_ADC_SEQ_LEN_04    (3<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 4 conversions */
#define LL_ADC_SEQ_LEN_05    (4<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 5 conversions */
#define LL_ADC_SEQ_LEN_06    (5<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 6 conversions */
#define LL_ADC_SEQ_LEN_07    (6<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 7 conversions */
#define LL_ADC_SEQ_LEN_08    (7<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 8 conversions */
#define LL_ADC_SEQ_LEN_09    (8<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 9 conversions */
#define LL_ADC_SEQ_LEN_10    (9<<ADC_CONF_SEQ_LEN_Pos)  /*!< The sequence is of 10 conversions */
#define LL_ADC_SEQ_LEN_11    (10<<ADC_CONF_SEQ_LEN_Pos) /*!< The sequence is of 11 conversions */
#define LL_ADC_SEQ_LEN_12    (11<<ADC_CONF_SEQ_LEN_Pos) /*!< The sequence is of 12 conversions */
#define LL_ADC_SEQ_LEN_13    (12<<ADC_CONF_SEQ_LEN_Pos) /*!< The sequence is of 13 conversions */
#define LL_ADC_SEQ_LEN_14    (13<<ADC_CONF_SEQ_LEN_Pos) /*!< The sequence is of 14 conversions */
#define LL_ADC_SEQ_LEN_15    (14<<ADC_CONF_SEQ_LEN_Pos) /*!< The sequence is of 15 conversions */
#define LL_ADC_SEQ_LEN_16    (15<<ADC_CONF_SEQ_LEN_Pos) /*!< The sequence is of 16 conversions */

/**
  * @}
  */


/** @defgroup ADC_LL_OCM_SOURCE ADC occasional mode source definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetOccasionalConversionSource() and LL_ADC_GetOccasionalConversionSource()
  * @{
  */

#define LL_ADC_OCM_SRC_VBAT    (0UL)  /*!< ADC occasional mode source VBAT               */
#define LL_ADC_OCM_SRC_TEMP    (1UL)  /*!< ADC occasional mode source temperature sensor */

/**
  * @}
  */


/** @defgroup ADC_LL_PGA_BIAS ADC microphone bias voltage definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetMicrophonePGABias() and LL_ADC_GetMicrophonePGABias()
  * @{
  */

#define LL_ADC_PGA_BIAS_050_BAT   (0x00000000UL)                  /*!< Set the microphone bias voltage at 0.50 V */
#define LL_ADC_PGA_BIAS_055_BAT   (1<<ADC_PGA_CONF_PGA_BIAS_Pos)  /*!< Set the microphone bias voltage at 0.55 V */
#define LL_ADC_PGA_BIAS_060_BAT   (2<<ADC_PGA_CONF_PGA_BIAS_Pos)  /*!< Set the microphone bias voltage at 0.60 V */
#define LL_ADC_PGA_BIAS_065_BAT   (3<<ADC_PGA_CONF_PGA_BIAS_Pos)  /*!< Set the microphone bias voltage at 0.65 V */
#define LL_ADC_PGA_BIAS_070_BAT   (4<<ADC_PGA_CONF_PGA_BIAS_Pos)  /*!< Set the microphone bias voltage at 0.70 V */
#define LL_ADC_PGA_BIAS_075_BAT   (5<<ADC_PGA_CONF_PGA_BIAS_Pos)  /*!< Set the microphone bias voltage at 0.75 V */
#define LL_ADC_PGA_BIAS_080_BAT   (6<<ADC_PGA_CONF_PGA_BIAS_Pos)  /*!< Set the microphone bias voltage at 0.80 V */
#define LL_ADC_PGA_BIAS_090_BAT   (7<<ADC_PGA_CONF_PGA_BIAS_Pos)  /*!< Set the microphone bias voltage at 0.90 V */

/**
  * @}
  */


/** @defgroup ADC_LL_PGA_GAIN ADC microphone gain definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetMicrophonePGAGain() and LL_ADC_GetMicrophonePGAGain()
  * @{
  */

#define LL_ADC_PGA_GAIN_00_DB   (0x00000000UL)  /*!< Set the microphone gain at 0 dB  */
#define LL_ADC_PGA_GAIN_03_DB   (0x00000001UL)  /*!< Set the microphone gain at 3 dB  */
#define LL_ADC_PGA_GAIN_06_DB   (0x00000002UL)  /*!< Set the microphone gain at 6 dB */
#define LL_ADC_PGA_GAIN_09_DB   (0x00000003UL)  /*!< Set the microphone gain at 9 dB */
#define LL_ADC_PGA_GAIN_12_DB   (0x00000004UL)  /*!< Set the microphone gain at 12 dB */
#define LL_ADC_PGA_GAIN_15_DB   (0x00000005UL)  /*!< Set the microphone gain at 15 dB */
#define LL_ADC_PGA_GAIN_18_DB   (0x00000006UL)  /*!< Set the microphone gain at 18 dB */
#define LL_ADC_PGA_GAIN_21_DB   (0x00000007UL)  /*!< Set the microphone gain at 21 dB */
#define LL_ADC_PGA_GAIN_24_DB   (0x00000008UL)  /*!< Set the microphone gain at 24 dB */
#define LL_ADC_PGA_GAIN_27_DB   (0x00000009UL)  /*!< Set the microphone gain at 27 dB */
#define LL_ADC_PGA_GAIN_30_DB   (0x0000000AUL)  /*!< Set the microphone gain at 30 dB */

/**
  * @}
  */


/** @defgroup ADC_LL_INPUT_VOLTAGE_RANGE ADC input voltage range definitions
  * @brief    It defines the parameters used for the functions:
  *           LL_ADC_SetVoltageRangeSingleVinm0(),    LL_ADC_GetVoltageRangeSingleVinm0(),
  *           LL_ADC_SetVoltageRangeDiffVinp0Vinm0(), LL_ADC_GetVoltageRangeDiffVinp0Vinm0(),
  *           LL_ADC_SetVoltageRangeSingleVinm1(),    LL_ADC_GetVoltageRangeSingleVinm1(),
  *           LL_ADC_SetVoltageRangeDiffVinp1Vinm1(), LL_ADC_GetVoltageRangeDiffVinp1Vinm1(),
  *           LL_ADC_SetVoltageRangeSingleVinm2(),    LL_ADC_GetVoltageRangeSingleVinm2(),
  *           LL_ADC_SetVoltageRangeDiffVinp2Vinm2(), LL_ADC_GetVoltageRangeDiffVinp2Vinm2(),
  *           LL_ADC_SetVoltageRangeSingleVinm3(),    LL_ADC_GetVoltageRangeSingleVinm3(),
  *           LL_ADC_SetVoltageRangeDiffVinp3Vinm3(), LL_ADC_GetVoltageRangeDiffVinp3Vinm3(),
  *           LL_ADC_SetVoltageRangeSingleVinp0(),    LL_ADC_GetVoltageRangeSingleVinp0(),
  *           LL_ADC_SetVoltageRangeSingleVinp1(),    LL_ADC_GetVoltageRangeSingleVinp1(),
  *           LL_ADC_SetVoltageRangeSingleVinp2(),    LL_ADC_GetVoltageRangeSingleVinp2(),
  *           LL_ADC_SetVoltageRangeSingleVinp3() and LL_ADC_GetVoltageRangeSingleVinp3()
  * @{
  */

#define LL_ADC_VIN_RANGE_1V2    (0UL)  /*!< ADC input voltage range up to 1.2 V */
#define LL_ADC_VIN_RANGE_2V4    (2UL)  /*!< ADC input voltage range up to 2.4 V */
#define LL_ADC_VIN_RANGE_3V6    (3UL)  /*!< ADC input voltage range up to 3.6 V */

/**
  * @}
  */


/** @defgroup ADC_LL_DEFAULT_RANGE_VALUE ADC default range value definitions
  * @brief    It defines the parameters used as default range value
  * @{
  */

#define LL_ADC_DEFAULT_RANGE_VALUE_1V2    (0xFFF)  /*!< ADC default range value up to 1.2 V */
#define LL_ADC_DEFAULT_RANGE_VALUE_2V4    (0x7FF)  /*!< ADC default range value up to 2.4 V */
#define LL_ADC_DEFAULT_RANGE_VALUE_3V6    (0x555)  /*!< ADC default range value up to 3.6 V */

/**
  * @}
  */


/** @defgroup ADC_LL_DF_DYN_RANGE ADC Decimation Filter dynamic range definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetDFInputDynamic() and LL_ADC_GetDFInputDynamic()
  * @{
  */

#define LL_ADC_DF_DYN_RANGE_FULL    (0x00000000UL)                     /*!< ADC Decimation Filter dynamic full range */
#define LL_ADC_DF_DYN_RANGE_HALF    (1<<ADC_DF_CONF_DF_HALF_D_EN_Pos)  /*!< ADC Decimation Filter dynamic half range */

/**
  * @}
  */


/** @defgroup ADC_LL_MIC_CHANNEL ADC microphone channel definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetMicrophoneChannel() and LL_ADC_GetMicrophoneChannel()
  * @{
  */

#define LL_ADC_DF_MIC_CH_RIGHT    (0x00000000UL)                     /*!< ADC microphone channel right */
#define LL_ADC_DF_MIC_CH_LEFT     (1<<ADC_DF_CONF_DF_MICROL_RN_Pos)  /*!< ADC microphone channel left  */

/**
  * @}
  */


/** @defgroup ADC_LL_PDM_CLK_DIVIDER ADC PDM clock divider definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetPDMRate() and LL_ADC_GetPDMRate()
  * @{
  */

#define LL_ADC_PDM_DIV_10   (0x00000000UL)                    /*!< ADC PDM clock divider 10 */
#define LL_ADC_PDM_DIV_11   ( 1 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 11 */
#define LL_ADC_PDM_DIV_12   ( 2 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 12 */
#define LL_ADC_PDM_DIV_13   ( 3 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 13 */
#define LL_ADC_PDM_DIV_14   ( 4 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 14 */
#define LL_ADC_PDM_DIV_15   ( 5 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 15 */
#define LL_ADC_PDM_DIV_16   ( 6 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 16 */
#define LL_ADC_PDM_DIV_17   ( 7 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 17 */
#define LL_ADC_PDM_DIV_18   ( 8 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 18 */
#define LL_ADC_PDM_DIV_19   ( 9 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 19 */
#define LL_ADC_PDM_DIV_20   (10 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 20 */
#define LL_ADC_PDM_DIV_21   (11 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 21 */
#define LL_ADC_PDM_DIV_22   (12 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 22 */
#define LL_ADC_PDM_DIV_23   (13 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 23 */
#define LL_ADC_PDM_DIV_24   (14 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 24 */
#define LL_ADC_PDM_DIV_25   (15 << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 25 */

/**
  * @}
  */


/** @defgroup ADC_LL_DATA_FORMAT ADC data format definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetDataOutputFormat(), LL_ADC_GetDataOutputFormat(), LL_ADC_SetDataInputFormat() and LL_ADC_GetDataInputFormat()
  * @{
  */

#define LL_ADC_DATA_FRMT_SIGNED    (0UL)  /*!< ADC data format signed   */
#define LL_ADC_DATA_FRMT_UNSIGNED  (1UL)  /*!< ADC data format unsigned */

/**
  * @}
  */


/** @defgroup ADC_LL_CIC_DECIMATOR_FACTOR ADC CIC decimator factor definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetCICDecimatorFactor() and LL_ADC_GetCICDecimatorFactor()
  * @{
  */

#define LL_ADC_CIC_DECIMATOR_FACTOR_HALF     (ADC_DF_CONF_DF_CIC_DHF)  /*!< ADC CIC decimator factor half    */
#define LL_ADC_CIC_DECIMATOR_FACTOR_INTEGER  (0x00000000UL)            /*!< ADC CIC decimator factor integer */

/**
  * @}
  */


/** @defgroup ADC_LL_MICROPHONE_OUT_FREQ ADC microphone output frequency definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetMicrophoneOutputDatarate() and LL_ADC_GetMicrophoneOutputDatarate()
  * @{
  */

#define LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ  (0x0EUL)  /*!< ADC digital microphone output frequency 47.619 kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ  (0x0FUL)  /*!< ADC digital microphone output frequency 44.44  kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ  (0x1EUL)  /*!< ADC digital microphone output frequency 22.22  kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ  (0x2AUL)  /*!< ADC digital microphone output frequency 15.873 kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ   (0x54UL)  /*!< ADC digital microphone output frequency 7.936  kHz */

#define LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ (0x02UL)  /*!< ADC analog microphone output frequency 200.00 kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ  (0x15UL)  /*!< ADC analog microphone output frequency 15.873 kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ   (0x2AUL)  /*!< ADC analog microphone output frequency 7.936  kHz */

/**
  * @}
  */


/** @defgroup ADC_LL_DS_DATA_WIDTH ADC Down Sampler data width definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetDSDataOutputWidth() and LL_ADC_GetDSDataOutputWidth()
  * @{
  */

#define LL_ADC_DS_DATA_WIDTH_12_BIT  (0UL)  /*!< ADC Down Sampler data width 12 bits */
#define LL_ADC_DS_DATA_WIDTH_13_BIT  (1UL)  /*!< ADC Down Sampler data width 13 bits */
#define LL_ADC_DS_DATA_WIDTH_14_BIT  (2UL)  /*!< ADC Down Sampler data width 14 bits */
#define LL_ADC_DS_DATA_WIDTH_15_BIT  (3UL)  /*!< ADC Down Sampler data width 15 bits */
#define LL_ADC_DS_DATA_WIDTH_16_BIT  (4UL)  /*!< ADC Down Sampler data width 16 bits */

/**
  * @}
  */


/** @defgroup ADC_LL_DS_RATIO ADC Down Sampler ratio definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetDSDataOutputRatio() and LL_ADC_GetDSDataOutputRatio()
  * @{
  */

#define LL_ADC_DS_RATIO_01   (0UL)      /*!< ADC Down Sampler ratio 1, no down sampling (default) */
#define LL_ADC_DS_RATIO_02   (1UL)      /*!< ADC Down Sampler ratio 2                             */
#define LL_ADC_DS_RATIO_04   (2UL)      /*!< ADC Down Sampler ratio 4                             */
#define LL_ADC_DS_RATIO_08   (3UL)      /*!< ADC Down Sampler ratio 8                             */
#define LL_ADC_DS_RATIO_16   (4UL)      /*!< ADC Down Sampler ratio 16                            */
#define LL_ADC_DS_RATIO_32   (5UL)      /*!< ADC Down Sampler ratio 32                            */
#define LL_ADC_DS_RATIO_64   (6UL)      /*!< ADC Down Sampler ratio 64                            */
#define LL_ADC_DS_RATIO_128  (7UL)      /*!< ADC Down Sampler ratio 128                           */

/**
  * @}
  */


/** @defgroup ADC_LL_CH_NUM_CODE ADC channel number code for conversion definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetChannelSeqX() and LL_ADC_GetChannelSeqX() with X = 0, 1, ...15
  * @{
  */

#define LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT  (0x00UL)  /*!< ADC channel number code for the conversion is VINM0 to single negative input */
#define LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT  (0x01UL)  /*!< ADC channel number code for the conversion is VINM1 to single negative input */
#define LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT  (0x02UL)  /*!< ADC channel number code for the conversion is VINM2 to single negative input */
#define LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT  (0x03UL)  /*!< ADC channel number code for the conversion is VINM3 to single negative input */
#define LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT  (0x04UL)  /*!< ADC channel number code for the conversion is VINP0 to single positive input */
#define LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT  (0x05UL)  /*!< ADC channel number code for the conversion is VINP1 to single positive input */
#define LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT  (0x06UL)  /*!< ADC channel number code for the conversion is VINP2 to single positive input */
#define LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT  (0x07UL)  /*!< ADC channel number code for the conversion is VINP3 to single positive input */
#define LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT       (0x08UL)  /*!< ADC channel number code for the conversion is VINP0 - VINM0 to differential input */
#define LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT       (0x09UL)  /*!< ADC channel number code for the conversion is VINP1 - VINM1 to differential input */
#define LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT       (0x0AUL)  /*!< ADC channel number code for the conversion is VINP2 - VINM2 to differential input */
#define LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT       (0x0BUL)  /*!< ADC channel number code for the conversion is VINP3 - VINM3 to differential input */
#define LL_ADC_CH_BATTERY_LEVEL_DETECTOR          (0x0CUL)  /*!< ADC channel number code for the conversion is VBAT, battery level detector */
#define LL_ADC_CH_TEMPERATURE_SENSOR              (0x0DUL)  /*!< ADC channel number code for the conversion is temperature sensor */

/**
  * @}
  */


/** @defgroup ADC_LL_CALIB_POINT ADC calibration points definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetCalibPointForDiff3V6(), LL_ADC_GetCalibPointForDiff3V6(),
  *           LL_ADC_SetCalibPointForSinglePos3V6(), LL_ADC_GetCalibPointForSinglePos3V6(), LL_ADC_SetCalibPointForSingleNeg3V6(),
  *           LL_ADC_GetCalibPointForSingleNeg3V6(), LL_ADC_SetCalibPointForDiff2V4(), LL_ADC_GetCalibPointForDiff2V4(),
  *           LL_ADC_SetCalibPointForSinglePos2V4(), LL_ADC_GetCalibPointForSinglePos2V4(), LL_ADC_SetCalibPointForSingleNeg2V4(),
  *           LL_ADC_GetCalibPointForSingleNeg2V4(), LL_ADC_SetCalibPointForDiff1V2(), LL_ADC_GetCalibPointForDiff1V2(),
  *           LL_ADC_SetCalibPointForSinglePos1V2(), LL_ADC_SetCalibPointForSingleNeg1V2() and LL_ADC_GetCalibPointForSingleNeg1V2()
  * @{
  */

#define LL_ADC_CALIB_POINT_1  (0x00UL)  /*!< ADC calibration point 1 */
#define LL_ADC_CALIB_POINT_2  (0x01UL)  /*!< ADC calibration point 2 */
#define LL_ADC_CALIB_POINT_3  (0x02UL)  /*!< ADC calibration point 3 */
#define LL_ADC_CALIB_POINT_4  (0x03UL)  /*!< ADC calibration point 4 */

/**
  * @}
  */

/** @defgroup ADC_LL_WDG_CHANNEL ADC watchdog channel selection for bit mask definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetWDGInputChannels() and LL_ADC_GetWDGInputChannels()
  * @{
  */

#define LL_ADC_WDG_CH_VINM0_TO_NEG     (1<<ADC_WD_CONF_AWD_CHX_0 )  /*!< ADC watchdog channel selection: VINM0 to ADC negative input  */
#define LL_ADC_WDG_CH_VINM1_TO_NEG     (1<<ADC_WD_CONF_AWD_CHX_1 )  /*!< ADC watchdog channel selection: VINM1 to ADC negative input  */
#define LL_ADC_WDG_CH_VINM2_TO_NEG     (1<<ADC_WD_CONF_AWD_CHX_2 )  /*!< ADC watchdog channel selection: VINM2 to ADC negative input  */
#define LL_ADC_WDG_CH_VINM3_TO_NEG     (1<<ADC_WD_CONF_AWD_CHX_3 )  /*!< ADC watchdog channel selection: VINM3 to ADC negative input  */
#define LL_ADC_WDG_CH_MICROM_TO_NEG    (1<<ADC_WD_CONF_AWD_CHX_4 )  /*!< ADC watchdog channel selection: MICROM to ADC negative input */
#define LL_ADC_WDG_CH_VBAT_TO_NEG      (1<<ADC_WD_CONF_AWD_CHX_5 )  /*!< ADC watchdog channel selection: VBAT to ADC negative input   */
#define LL_ADC_WDG_CH_GND_TO_NEG       (1<<ADC_WD_CONF_AWD_CHX_6 )  /*!< ADC watchdog channel selection: GND to ADC negative input    */
#define LL_ADC_WDG_CH_VDDA_TO_NEG      (1<<ADC_WD_CONF_AWD_CHX_7 )  /*!< ADC watchdog channel selection: VDDA to ADC negative input   */
#define LL_ADC_WDG_CH_VINP0_TO_POS     (1<<ADC_WD_CONF_AWD_CHX_8 )  /*!< ADC watchdog channel selection: VINP0 to ADC positive input  */
#define LL_ADC_WDG_CH_VINP1_TO_POS     (1<<ADC_WD_CONF_AWD_CHX_9 )  /*!< ADC watchdog channel selection: VINP1 to ADC positive input  */
#define LL_ADC_WDG_CH_VINP2_TO_POS     (1<<ADC_WD_CONF_AWD_CHX_10)  /*!< ADC watchdog channel selection: VINP2 to ADC positive input  */
#define LL_ADC_WDG_CH_VINP3_TO_POS     (1<<ADC_WD_CONF_AWD_CHX_11)  /*!< ADC watchdog channel selection: VINP3 to ADC positive input  */
#define LL_ADC_WDG_CH_MICROP_TO_POS    (1<<ADC_WD_CONF_AWD_CHX_12)  /*!< ADC watchdog channel selection: MICROP to ADC positive input */
#define LL_ADC_WDG_CH_TEMP_TO_POS      (1<<ADC_WD_CONF_AWD_CHX_13)  /*!< ADC watchdog channel selection: TEMP to ADC positive input   */
#define LL_ADC_WDG_CH_GND_TO_POS       (1<<ADC_WD_CONF_AWD_CHX_14)  /*!< ADC watchdog channel selection: GND to ADC positive input    */
#define LL_ADC_WDG_CH_VDDA_TO_POS      (1<<ADC_WD_CONF_AWD_CHX_15)  /*!< ADC watchdog channel selection: VDDA to ADC positive input   */

/**
  * @}
  */


/** @defgroup ADC_LL_IRQ_STATUS_MASK ADC IRQ_STATUS register mask definitions
  * @brief    It defines the IRQ flags used for the functions LL_ADC_ClearActiveFlags() and LL_ADC_GetActiveFlags().
  * @{
  */

#define LL_ADC_IRQ_FLAG_OVRFL   (ADC_IRQ_STATUS_DF_OVRFL_IRQ) /*!< ADC IRQ flag OVRFL */
#define LL_ADC_IRQ_FLAG_OVRDF   (ADC_IRQ_STATUS_OVR_DF_IRQ) /*!< ADC IRQ flag OVRDF */
#define LL_ADC_IRQ_FLAG_OVRDS   (ADC_IRQ_STATUS_OVR_DS_IRQ) /*!< ADC IRQ flag OVRDS */
#define LL_ADC_IRQ_FLAG_AWD     (ADC_IRQ_STATUS_AWD_IRQ)   /*!< ADC IRQ flag AWD   */
#define LL_ADC_IRQ_FLAG_EOS     (ADC_IRQ_STATUS_EOS_IRQ)   /*!< ADC IRQ flag EOS   */
#define LL_ADC_IRQ_FLAG_EODF    (ADC_IRQ_STATUS_EODF_IRQ)  /*!< ADC IRQ flag EODF  */
#define LL_ADC_IRQ_FLAG_EODS    (ADC_IRQ_STATUS_EODS_IRQ)  /*!< ADC IRQ flag EODS  */

/**
  * @}
  */


/** @defgroup ADC_LL_IRQ_STATUS_MASK ADC IRQ_ENABLE register mask definitions
  * @brief    It defines the mask of the register  IRQ_ENABLE
  * @{
  */

#define LL_ADC_IRQ_FLAGS_MASK      (LL_ADC_IRQ_FLAG_OVRFL | \
                                 LL_ADC_IRQ_FLAG_OVRDF | \
                                 LL_ADC_IRQ_FLAG_OVRDS | \
                                 LL_ADC_IRQ_FLAG_AWD   | \
                                 LL_ADC_IRQ_FLAG_EOS   | \
                                 LL_ADC_IRQ_FLAG_EODF  | \
                                 LL_ADC_IRQ_FLAG_EODS)


/**
  * @}
  */


/** @defgroup ADC_LL_IRQ_ENABLE ADC interrupts enable definitions
  * @brief    It defines the IRQ interrupt enable used for the functions LL_ADC_ClearActiveFlags() and LL_ADC_GetActiveFlags().
  * @{
  */

#define LL_ADC_IRQ_EN_OVRFL   (ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA) /*!< ADC IRQ enable OVRFL */
#define LL_ADC_IRQ_EN_OVRDF   (ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA)   /*!< ADC IRQ enable OVRDF */
#define LL_ADC_IRQ_EN_OVRDS   (ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA)   /*!< ADC IRQ enable OVRDS */
#define LL_ADC_IRQ_EN_AWD     (ADC_IRQ_ENABLE_AWD_IRQ_ENA)      /*!< ADC IRQ enable AWD   */
#define LL_ADC_IRQ_EN_EOS     (ADC_IRQ_ENABLE_EOS_IRQ_ENA)      /*!< ADC IRQ enable EOS   */
#define LL_ADC_IRQ_EN_EODF    (ADC_IRQ_ENABLE_EODF_IRQ_ENA)     /*!< ADC IRQ enable EODF  */
#define LL_ADC_IRQ_EN_EODS    (ADC_IRQ_ENABLE_EODS_IRQ_ENA)     /*!< ADC IRQ enable EODS  */

/**
  * @}
  */



/** @defgroup ADC_LL_CALIB_ADDRESS ADC calibration points location
  * @brief    Defines the memory address of the calibration points.
  * @{
  */
#define ADC_LAYOUT_ID                    (0x10001EFC)
#define ADC_CALIB_ADDRESS_VINPX_3V6      (0x10001E20)
#define ADC_CALIB_ADDRESS_VINMX_3V6      (0x10001E1C)
#define ADC_CALIB_ADDRESS_VINDIFF_3V6    (0x10001E18)
#define ADC_CALIB_ADDRESS_VINPX_2V4      (0x10001E14)
#define ADC_CALIB_ADDRESS_VINMX_2V4      (0x10001E10)
#define ADC_CALIB_ADDRESS_VINDIFF_2V4    (0x10001E0C)
#define ADC_CALIB_ADDRESS_VINPX_1V2      (0x10001E08)
#define ADC_CALIB_ADDRESS_VINMX_1V2      (0x10001E04)
#define ADC_CALIB_ADDRESS_VINDIFF_1V2    (0x10001E00)

/**
  * @}
  */


/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros ADC Exported Macros
  * @{
  */

/** @defgroup ADC_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in ADC register
  * @param  __INSTANCE__ ADC Instance
  * @param  ___ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_ADC_WriteReg(__INSTANCE__, ___, __VALUE__) WRITE_REG(__INSTANCE__->___, (__VALUE__))

/**
  * @brief  Read a value in ADC register
  * @param  __INSTANCE__ ADC Instance
  * @param  ___ Register to be read
  * @retval Register value
  */
#define LL_ADC_ReadReg(__INSTANCE__, ___) READ_REG(__INSTANCE__->___)

/**
  * @}
  */


/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_LL_EF_Configuration_ADC ADC Configuration functions
  * @{
  */

/**
  * @brief  Select the input sampling method.
  *         Sampling only at conversion start (default).
  *         Sampling starts at the end of conversion.
  * @rmtoll CONF     ADC_CONT_1V2       LL_ADC_InputSamplingMode
  * @param  ADCx ADC instance
  * @param  SamplingMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLING_AT_START
  *         @arg @ref LL_ADC_SAMPLING_AT_END
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InputSamplingMode(ADC_TypeDef *ADCx, uint32_t SamplingMode)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_ADC_CONT_1V2, SamplingMode);
}

/**
  * @brief  Get input sampling mode.
  * @rmtoll CONF     ADC_CONT_1V2       LL_ADC_GetInputSamplingMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLING_AT_START
  *         @arg @ref LL_ADC_SAMPLING_AT_END
  */
__STATIC_INLINE uint32_t LL_ADC_GetInputSamplingMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CTRL, ADC_CONF_ADC_CONT_1V2));
}

/**
  * @brief  Enable the inversion of the ADC data output bits (1's complement)
  *         when a differential input is connected to the ADC
  * @rmtoll CONF     BIT_INVERT_DIFF     LL_ADC_InvertOutputBitDiffModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InvertOutputBitDiffModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_DIFF);
}

/**
  * @brief  Disable the inversion of the ADC data output bits (1's complement)
  *         when a differential input is connected to the ADC
  * @rmtoll CONF     BIT_INVERT_DIFF     LL_ADC_InvertOutputBitDiffModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InvertOutputBitDiffModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_DIFF);
}

/**
  * @brief  Check if the inversion of the ADC data output bits (1's complement)
  *         when a differential input is connected to the ADC is enabled.
  * @rmtoll CONF     BIT_INVERT_DIFF     LL_ADC_IsInvertOutputBitDiffModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: inversion is not enabled, 1: inversion is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsInvertOutputBitDiffModeEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_DIFF) == (ADC_CONF_BIT_INVERT_DIFF)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the inversion of the ADC data output bits (1's complement)
  *         when a single negative input is connected to the ADC
  * @rmtoll CONF     BIT_INVERT_SN     LL_ADC_InvertOutputBitSingleNegModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InvertOutputBitSingleNegModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_SN);
}

/**
  * @brief  Disable the inversion of the ADC data output bits (1's complement)
  *         when a single negative input is connected to the ADC
  * @rmtoll CONF     BIT_INVERT_SN     LL_ADC_InvertOutputBitSingleNegModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InvertOutputBitSingleNegModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_SN);
}

/**
  * @brief  Check if the inversion of the ADC data output bits (1's complement)
  *         when a single negative input is connected to the ADC is enabled.
  * @rmtoll CONF     BIT_INVERT_SN     LL_ADC_IsInvertOutputBitSingleNegModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: inversion is not enabled, 1: inversion is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsInvertOutputBitSingleNegModeEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_SN) == (ADC_CONF_BIT_INVERT_SN)) ? 1UL : 0UL);
}

#if defined(ADC_CONF_OVR_DF_CFG)
/**
  * @brief  Select the overrun configuration for the output data of
  *         the Decimation Filter (DF).
  *         Previous data is kept, the new one is lost.
  *         Previous data is lost, the new one is kept.
  * @rmtoll CONF     OVR_DF_CFG       LL_ADC_SetOverrunDF
  * @param  ADCx ADC instance
  * @param  Overrun This parameter can be one of the following values:
  *         @arg @ref LL_ADC_NEW_DATA_IS_LOST
  *         @arg @ref LL_ADC_NEW_DATA_IS_KEPT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOverrunDF(ADC_TypeDef *ADCx, uint32_t Overrun)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_OVR_DF_CFG, Overrun);
}

/**
  * @brief  Get the overrun configuration for the output data of
  *         the Decimation Filter (DF).
  *         Previous data is kept, the new one is lost.
  *         Previous data is lost, the new one is kept.
  * @rmtoll CONF     OVR_DF_CFG       LL_ADC_GetOverrunDF
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_NEW_DATA_IS_LOST
  *         @arg @ref LL_ADC_NEW_DATA_IS_KEPT
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverrunDF(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_OVR_DF_CFG));
}
#endif


/**
  * @brief  Select the overrun configuration for the output data of
  *         the Down Sampler (DS).
  *         Previous data is kept, the new one is lost.
  *         Previous data is lost, the new one is kept.
  * @rmtoll CONF     OVR_DS_CFG       LL_ADC_SetOverrunDS
  * @param  ADCx ADC instance
  * @param  Overrun This parameter can be one of the following values:
  *         @arg @ref LL_ADC_NEW_DATA_IS_LOST
  *         @arg @ref LL_ADC_NEW_DATA_IS_KEPT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOverrunDS(ADC_TypeDef *ADCx, uint32_t Overrun)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_OVR_DS_CFG, Overrun);
}

/**
  * @brief  Get the overrun configuration for the output data of
  *         the Down Sampler (DS).
  *         Previous data is kept, the new one is lost.
  *         Previous data is lost, the new one is kept.
  * @rmtoll CONF     OVR_DS_CFG       LL_ADC_GetOverrunDS
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_NEW_DATA_IS_LOST
  *         @arg @ref LL_ADC_NEW_DATA_IS_KEPT
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverrunDS(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_OVR_DS_CFG));
}

#if defined(ADC_CONF_DMA_DF_ENA)
/**
  * @brief  Enable the DMA mode for the Decimation Filter (DF) data path.
  * @rmtoll CONF     DMA_DF_ENA     LL_ADC_DMAModeDFEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DMAModeDFEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_DMA_DF_ENA);
}

/**
  * @brief  Disable the DMA mode for the Decimation Filter (DF) data path.
  * @rmtoll CONF     DMA_DF_ENA     LL_ADC_DMAModeDFDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DMAModeDFDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_DMA_DF_ENA);
}


/**
  * @brief  Check if the DMA mode for the Decimation Filter (DF) data path is enabled.
  * @rmtoll CONF     DMA_DF_ENA     LL_ADC_IsDMAModeDFEnabled
  * @param  ADCx ADC instance
  * @retval 0: DMA mode is not enabled, 1: DMA mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDMAModeDFEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_DMA_DF_ENA) == (ADC_CONF_DMA_DF_ENA)) ? 1UL : 0UL);
}
#endif


/**
  * @brief  Enable the DMA mode for the Down Sampler (DS) data path.
  * @rmtoll CONF     DMA_DS_ENA     LL_ADC_DMAModeDSEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DMAModeDSEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_DMA_DS_ENA);
}


/**
  * @brief  Disable the DMA mode for the Down Sampler (DS) data path.
  * @rmtoll CONF     DMA_DS_ENA     LL_ADC_DMAModeDSDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DMAModeDSDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_DMA_DS_ENA);
}


/**
  * @brief  Check if the DMA mode for the Down Sampler (DS) data path is enabled.
  * @rmtoll CONF     DMA_DS_ENA     LL_ADC_IsDMAModeDSEnabled
  * @param  ADCx ADC instance
  * @retval 0: DMA mode is not enabled, 1: DMA mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDMAModeDSEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_DMA_DS_ENA) == (ADC_CONF_DMA_DS_ENA)) ? 1UL : 0UL);
}


#if defined(ADC_CONF_SAMPLE_RATE_MSB)
/**
  * @brief  Select the ADC conversion rate.
  * @rmtoll CONF     SAMPLE_RATE       LL_ADC_SetSampleRate
  * @rmtoll CONF     SAMPLE_RATE_MSB   LL_ADC_SetSampleRate
  * @param  ADCx ADC instance
  * @param  SampleRateMsb This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_0
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_1
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_2
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_3
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_4
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_5
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_6
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_7
  * @param  SampleRate This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLE_RATE_0
  *         @arg @ref LL_ADC_SAMPLE_RATE_1
  *         @arg @ref LL_ADC_SAMPLE_RATE_2
  *         @arg @ref LL_ADC_SAMPLE_RATE_3
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetSampleRate(ADC_TypeDef *ADCx, uint32_t SampleRateMsb, uint32_t SampleRate)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_SAMPLE_RATE_MSB, SampleRateMsb);
  MODIFY_REG(ADCx->CONF, ADC_CONF_SAMPLE_RATE, SampleRate);
}


/**
  * @brief  Get the ADC sample rate .
  * @rmtoll CONF     SAMPLE_RATE       LL_ADC_GetSampleRate
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLE_RATE_0
  *         @arg @ref LL_ADC_SAMPLE_RATE_1
  *         @arg @ref LL_ADC_SAMPLE_RATE_2
  *         @arg @ref LL_ADC_SAMPLE_RATE_3
  */
__STATIC_INLINE uint32_t LL_ADC_GetSampleRate(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_SAMPLE_RATE));
}

/**
  * @brief  Get the ADC sample rate MSB.
  * @rmtoll CONF     SAMPLE_RATE_MSB   LL_ADC_GetSampleRate
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_0
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_1
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_2
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_3
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_4
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_5
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_6
  *         @arg @ref LL_ADC_SAMPLE_RATE_MSB_7
  */
__STATIC_INLINE uint32_t LL_ADC_GetSampleRateMsb(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_SAMPLE_RATE_MSB));
}

#else
/**
  * @brief  Select the ADC conversion rate.
  * @rmtoll CONF     SAMPLE_RATE       LL_ADC_SetSampleRate
  * @param  ADCx ADC instance
  * @param  SampleRate This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLE_RATE_16
  *         @arg @ref LL_ADC_SAMPLE_RATE_20
  *         @arg @ref LL_ADC_SAMPLE_RATE_24
  *         @arg @ref LL_ADC_SAMPLE_RATE_28
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetSampleRate(ADC_TypeDef *ADCx, uint32_t SampleRate)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_SAMPLE_RATE, SampleRate);
}


/**
  * @brief  Get the ADC conversion rate.
  * @rmtoll CONF     SAMPLE_RATE       LL_ADC_GetSampleRate
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLE_RATE_16
  *         @arg @ref LL_ADC_SAMPLE_RATE_20
  *         @arg @ref LL_ADC_SAMPLE_RATE_24
  *         @arg @ref LL_ADC_SAMPLE_RATE_28
  */
__STATIC_INLINE uint32_t LL_ADC_GetSampleRate(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_SAMPLE_RATE));
}
#endif


/**
  * @brief  Select the ADC operation mode.
  * @rmtoll CONF     OP_MODE       LL_ADC_SetADCMode
  * @param  ADCx ADC instance
  * @param  OperationMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OP_MODE_AUDIO
  *         @arg @ref LL_ADC_OP_MODE_ADC
  *         @arg @ref LL_ADC_OP_MODE_FULL
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetADCMode(ADC_TypeDef *ADCx, uint32_t OperationMode)
{
#if defined(ADC_CONF_OP_MODE)
  MODIFY_REG(ADCx->CONF, ADC_CONF_OP_MODE, OperationMode);
#endif
}


/**
  * @brief  Get the ADC operation mode.
  * @rmtoll CONF     OP_MODE       LL_ADC_GetADCMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OP_MODE_AUDIO
  *         @arg @ref LL_ADC_OP_MODE_ADC
  *         @arg @ref LL_ADC_OP_MODE_FULL
  */
__STATIC_INLINE uint32_t LL_ADC_GetADCMode(ADC_TypeDef *ADCx)
{
#if defined(ADC_CONF_OP_MODE)
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_OP_MODE));
#else
  return LL_ADC_OP_MODE_ADC;
#endif
}


/**
  * @brief  Enable the synchronization of the ADC start conversion with
  *         a pulse generated by the SMPS.
  * @note   This bitfield must be 0 when the ADC clock is 32 MHz or 
  *         when the SMPS is not used.
  * @rmtoll CONF     SMPS_SYNCHRO_ENA     LL_ADC_SyncADCStartWithSMPSPulseEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SyncADCStartWithSMPSPulseEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_SMPS_SYNCHRO_ENA);
}

/**
  * @brief  Disable the synchronization of the ADC start conversion with
  *         a pulse generated by the SMPS.
  * @note   This bitfield must be 0 when the ADC clock is 32 MHz or 
  *         when the SMPS is not used.
  * @rmtoll CONF     SMPS_SYNCHRO_ENA     LL_ADC_SyncADCStartWithSMPSPulseDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SyncADCStartWithSMPSPulseDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_SMPS_SYNCHRO_ENA);
}


/**
  * @brief  Check if the the synchronization of the ADC start conversion with
  *         a pulse generated by the SMPS is enabled.
  * @note   This bitfield must be 0 when the ADC clock is 32 MHz or 
  *         when the SMPS is not used.
  * @rmtoll CONF     SMPS_SYNCHRO_ENA     LL_ADC_IsSyncADCStartWithSMPSPulseEnabled
  * @param  ADCx ADC instance
  * @retval 0: Synchronization with SMPS is not enabled, 1: Synchronization with SMPS is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsSyncADCStartWithSMPSPulseEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_SMPS_SYNCHRO_ENA) == (ADC_CONF_SMPS_SYNCHRO_ENA)) ? 1UL : 0UL);
}


/**
  * @brief  Set the number of conversion in a sequence starting from SEQ0.
  * @rmtoll CONF     SEQ_LEN       LL_ADC_SetSequenceLength
  * @param  ADCx ADC instance
  * @param  SequenceLength This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SEQ_LEN_01
  *         @arg @ref LL_ADC_SEQ_LEN_02
  *         @arg @ref LL_ADC_SEQ_LEN_03
  *         @arg @ref LL_ADC_SEQ_LEN_04
  *         @arg @ref LL_ADC_SEQ_LEN_05
  *         @arg @ref LL_ADC_SEQ_LEN_06
  *         @arg @ref LL_ADC_SEQ_LEN_07
  *         @arg @ref LL_ADC_SEQ_LEN_08
  *         @arg @ref LL_ADC_SEQ_LEN_09
  *         @arg @ref LL_ADC_SEQ_LEN_10
  *         @arg @ref LL_ADC_SEQ_LEN_11
  *         @arg @ref LL_ADC_SEQ_LEN_12
  *         @arg @ref LL_ADC_SEQ_LEN_13
  *         @arg @ref LL_ADC_SEQ_LEN_14
  *         @arg @ref LL_ADC_SEQ_LEN_15
  *         @arg @ref LL_ADC_SEQ_LEN_16
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetSequenceLength(ADC_TypeDef *ADCx, uint32_t SequenceLength)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_SEQ_LEN, SequenceLength);
}


/**
  * @brief  Get the number of conversion in a sequence starting from SEQ0.
  * @rmtoll CONF     SEQ_LEN       LL_ADC_GetSequenceLength
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SEQ_LEN_01
  *         @arg @ref LL_ADC_SEQ_LEN_02
  *         @arg @ref LL_ADC_SEQ_LEN_03
  *         @arg @ref LL_ADC_SEQ_LEN_04
  *         @arg @ref LL_ADC_SEQ_LEN_05
  *         @arg @ref LL_ADC_SEQ_LEN_06
  *         @arg @ref LL_ADC_SEQ_LEN_07
  *         @arg @ref LL_ADC_SEQ_LEN_08
  *         @arg @ref LL_ADC_SEQ_LEN_09
  *         @arg @ref LL_ADC_SEQ_LEN_10
  *         @arg @ref LL_ADC_SEQ_LEN_11
  *         @arg @ref LL_ADC_SEQ_LEN_12
  *         @arg @ref LL_ADC_SEQ_LEN_13
  *         @arg @ref LL_ADC_SEQ_LEN_14
  *         @arg @ref LL_ADC_SEQ_LEN_15
  *         @arg @ref LL_ADC_SEQ_LEN_16
  */
__STATIC_INLINE uint32_t LL_ADC_GetSequenceLength(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_SEQ_LEN));
}


/**
  * @brief  Enable the ADC conversion in sequence mode.
  * @rmtoll CONF     SEQUENCE     LL_ADC_SequenceModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SequenceModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_SEQUENCE);
}


/**
  * @brief  Disable the ADC conversion in sequence mode.
  * @rmtoll CONF     SEQUENCE     LL_ADC_SequenceModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SequenceModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_SEQUENCE);
}


/**
  * @brief  Check if the ADC conversion in sequence mode is enabled.
  * @rmtoll CONF     SEQUENCE     LL_ADC_IsSequenceModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: Sequence mode is not enabled, 1: Sequence mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsSequenceModeEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_SEQUENCE) == (ADC_CONF_SEQUENCE)) ? 1UL : 0UL);
}


/**
  * @brief  Enable the ADC continuous conversion mode.
  *         When a sequence is over, the conversion starts again.
  * @note   Stop the conversion can be made by sets the STOP_OP_MODE bit.
  *         Call the API @ref LL_ADC_StopConversion().
  * @rmtoll CONF     CONT     LL_ADC_ContinuousModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ContinuousModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_CONT);
}


/**
  * @brief  Disable the ADC continuous conversion mode.
  *         When a sequence is over, the conversion stops (single conversion mode).
  * @rmtoll CONF     CONT     LL_ADC_ContinuousModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ContinuousModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_CONT);
}


/**
  * @brief  Check if the ADC continuous conversion mode is enabled.
  * @rmtoll CONF     CONT     LL_ADC_IsContinuousModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: Continuous mode is not enabled, 1: Continuous mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsContinuousModeEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_CONT) == (ADC_CONF_CONT)) ? 1UL : 0UL);
}

/**
  * @}
  */


/** @defgroup ADC_LL_EF_Control_ADC ADC Control functions
  * @{
  */

#if defined (ADC_CTRL_ADC_LDO_ENA)
/**
  * @brief  Enable the LDO associated to the ADC block.
  * @note   This bit must not be set on QFN32 package.
  * @rmtoll CTRL     ADC_LDO_ENA     LL_ADC_LDOEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_LDOEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_ADC_LDO_ENA);
}


/**
  * @brief  Disable the LDO associated to the ADC block.
  * @note   This bit must not be set on QFN32 package.
  * @rmtoll CTRL     ADC_LDO_ENA     LL_ADC_LDODisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_LDODisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CTRL, ADC_CTRL_ADC_LDO_ENA);
}


/**
  * @brief  Check if the LDO associated to the ADC block is enabled.
  * @note   This bit must not be set on QFN32 package.
  * @rmtoll CTRL     ADC_LDO_ENA     LL_ADC_IsLDOEnabled
  * @param  ADCx ADC instance
  * @retval 0: LDO is not enabled, 1: LDO is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsLDOEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_ADC_LDO_ENA) == (ADC_CTRL_ADC_LDO_ENA)) ? 1UL : 0UL);
}
#endif


#if defined (ADC_CTRL_DIG_AUD_MODE)
/**
  * @brief  Enable the digital audio mode.
  * @rmtoll CTRL     DIG_AUD_MODE     LL_ADC_AudioModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_AudioModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_DIG_AUD_MODE);
}


/**
  * @brief  Disable the digital audio mode.
  * @rmtoll CTRL     DIG_AUD_MODE     LL_ADC_AudioModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_AudioModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CTRL, ADC_CTRL_DIG_AUD_MODE);
}

/**
  * @brief  Check if the digital audio mode is enabled.
  * @rmtoll CTRL     DIG_AUD_MODE     LL_ADC_IsAudioModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: audio mode is not enabled, 1: audio mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsAudioModeEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_DIG_AUD_MODE) == (ADC_CTRL_DIG_AUD_MODE)) ? 1UL : 0UL);
}
#endif


/**
  * @brief  Stop the ongoing ADC conversion.
  * @note   This bit is set by software and cleared by hardware.
  * @note   When the STOP_MODE_OP is set, the user has to wait around 10 us before
  *         to start a new ADC conversion (set START_CONV bit).
  * @rmtoll CTRL     STOP_OP_MODE     LL_ADC_StopConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StopConversion(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_STOP_OP_MODE);
}


/**
  * @brief  Check if the stop conversion is ongoing.
  * @rmtoll CTRL     STOP_OP_MODE     LL_ADC_IsStopConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: stop conversion is not ongoing, 1: stop conversion is ongoing.
  */
__STATIC_INLINE uint32_t LL_ADC_IsStopConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_STOP_OP_MODE) == (ADC_CTRL_STOP_OP_MODE)) ? 1UL : 0UL);
}


/**
  * @brief  Start an ADC conversion.
  * @note   This bit is set by software and cleared by hardware.
  * @rmtoll CTRL     START_CONV     LL_ADC_StartConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StartConversion(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_START_CONV);
}


/**
  * @brief  Check if the ADC conversion is ongoing.
  * @rmtoll CTRL     START_CONV     LL_ADC_IsConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: ADC conversion is not ongoing, 1: ADC conversion is ongoing.
  */
__STATIC_INLINE uint32_t LL_ADC_IsConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_START_CONV) == (ADC_CTRL_START_CONV)) ? 1UL : 0UL);
}


/**
  * @brief  Power on the ADC.
  * @rmtoll CTRL     ADC_ON_OFF     LL_ADC_Enable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_ADC_ON_OFF);
}


/**
  * @brief  Power off the ADC.
  * @rmtoll CTRL     ADC_ON_OFF     LL_ADC_Disable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CTRL, ADC_CTRL_ADC_ON_OFF);
}


/**
  * @brief  Check if the ADC is on.
  * @rmtoll CTRL     ADC_ON_OFF     LL_ADC_IsEnabled
  * @param  ADCx ADC instance
  * @retval 0: ADC is off, 1: ADC is on.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_ADC_ON_OFF) == (ADC_CTRL_ADC_ON_OFF)) ? 1UL : 0UL);
}


/**
  * @}
  */


/** @defgroup ADC_LL_EF_Occasional_Mode ADC Occasional Mode Control functions
  * @{
  */

#if defined(ADC_OCM_CTRL_OCM_ENA)
/**
  * @brief  Start an ADC occasional conversion during an analog audio conversion or
  *         during an ADC full mode.
  * @note   This bit is set by software and cleared by hardware.
  * @rmtoll OCM_CTRL     OCM_ENA     LL_ADC_StartOccasionalConversionMode
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StartOccasionalConversionMode(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->OCM_CTRL, ADC_OCM_CTRL_OCM_ENA);
}


/**
  * @brief  Check if the ADC occasional conversion is ongoing.
  * @rmtoll OCM_CTRL     OCM_ENA     LL_ADC_IsOccasionalConversionModeOngoing
  * @param  ADCx ADC instance
  * @retval 0: ADC occasional conversion is not ongoing, 1: ADC occasional conversion is ongoing.
  */
__STATIC_INLINE uint32_t LL_ADC_IsOccasionalConversionModeOngoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->OCM_CTRL, ADC_OCM_CTRL_OCM_ENA) == (ADC_OCM_CTRL_OCM_ENA)) ? 1UL : 0UL);
}
#endif

#if defined(ADC_OCM_CTRL_OCM_SRC)
/**
  * @brief  Set the ADC occasional conversion source.
  *         ADC conversion from internal VBAT.
  *         ADC conversion from temperature sensor.
  * @rmtoll OCM_CTRL     OCM_SRC       LL_ADC_SetOccasionalConversionSource
  * @param  ADCx ADC instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OCM_SRC_VBAT
  *         @arg @ref LL_ADC_OCM_SRC_TEMP
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOccasionalConversionSource(ADC_TypeDef *ADCx, uint32_t Source)
{
  MODIFY_REG(ADCx->OCM_CTRL, ADC_OCM_CTRL_OCM_SRC, Source);
}


/**
  * @brief  Get the ADC occasional conversion source.
  *         ADC conversion from internal VBAT.
  *         ADC conversion from temperature sensor.
  * @rmtoll OCM_CTRL     OCM_SRC       LL_ADC_GetOccasionalConversionSource
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OCM_SRC_VBAT
  *         @arg @ref LL_ADC_OCM_SRC_TEMP
  */
__STATIC_INLINE uint32_t LL_ADC_GetOccasionalConversionSource(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->OCM_CTRL, ADC_OCM_CTRL_OCM_SRC));
}
#endif


/**
  * @}
  */


/** @defgroup ADC_LL_EF_PGA_Configuration ADC PGA Configuration functions
  * @{
  */

#if defined(ADC_PGA_CONF_PGA_BIAS)
/**
  * @brief  Configure the voltage bias and the gain for the PGA used in the ADC microphone mode.
  * @param  ADCx ADC instance
  * @param  Bias This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PGA_BIAS_050_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_055_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_060_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_065_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_070_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_075_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_080_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_090_BAT
  * @param  Gain This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PGA_GAIN_06_DB
  *         @arg @ref LL_ADC_PGA_GAIN_09_DB
  *         @arg @ref LL_ADC_PGA_GAIN_12_DB
  *         @arg @ref LL_ADC_PGA_GAIN_15_DB
  *         @arg @ref LL_ADC_PGA_GAIN_18_DB
  *         @arg @ref LL_ADC_PGA_GAIN_21_DB
  *         @arg @ref LL_ADC_PGA_GAIN_24_DB
  *         @arg @ref LL_ADC_PGA_GAIN_27_DB
  *         @arg @ref LL_ADC_PGA_GAIN_30_DB
  *         @arg @ref LL_ADC_PGA_GAIN_33_DB
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureMicrophonePGA(ADC_TypeDef *ADCx, uint32_t Bias, uint32_t Gain)
{
  MODIFY_REG(ADCx->PGA_CONF, (ADC_PGA_CONF_PGA_BIAS | ADC_PGA_CONF_PGA_GAIN), (Bias | Gain) );
}


/**
  * @brief  Set the voltage bias for the PGA used in the ADC microphone mode.
  * @rmtoll PGA_CONF     PGA_BIAS       LL_ADC_SetMicrophonePGABias
  * @param  ADCx ADC instance
  * @param  Bias This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PGA_BIAS_050_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_055_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_060_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_065_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_070_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_075_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_080_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_090_BAT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMicrophonePGABias(ADC_TypeDef *ADCx, uint32_t Bias)
{
  MODIFY_REG(ADCx->PGA_CONF, ADC_PGA_CONF_PGA_BIAS, Bias);
}


/**
  * @brief  Get the voltage bias for the PGA used in the ADC microphone mode.
  * @rmtoll PGA_CONF     PGA_BIAS       LL_ADC_GetMicrophonePGABias
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_PGA_BIAS_050_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_055_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_060_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_065_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_070_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_075_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_080_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_090_BAT
  */
__STATIC_INLINE uint32_t LL_ADC_GetMicrophonePGABias(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->PGA_CONF, ADC_PGA_CONF_PGA_BIAS));
}
#endif

#if defined(ADC_PGA_CONF_PGA_GAIN)
/**
  * @brief  Set the gain for the PGA used in the ADC microphone mode.
  * @note   PGA gain of 6 dB is equivalent to the 2.4 V ADC full scale.
  * @rmtoll PGA_CONF     PGA_GAIN       LL_ADC_SetMicrophonePGAGain
  * @param  ADCx ADC instance
  * @param  Gain This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PGA_GAIN_06_DB
  *         @arg @ref LL_ADC_PGA_GAIN_09_DB
  *         @arg @ref LL_ADC_PGA_GAIN_12_DB
  *         @arg @ref LL_ADC_PGA_GAIN_15_DB
  *         @arg @ref LL_ADC_PGA_GAIN_18_DB
  *         @arg @ref LL_ADC_PGA_GAIN_21_DB
  *         @arg @ref LL_ADC_PGA_GAIN_24_DB
  *         @arg @ref LL_ADC_PGA_GAIN_27_DB
  *         @arg @ref LL_ADC_PGA_GAIN_30_DB
  *         @arg @ref LL_ADC_PGA_GAIN_33_DB
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMicrophonePGAGain(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->PGA_CONF, ADC_PGA_CONF_PGA_GAIN, Gain);
}


/**
  * @brief  Get the gain for the PGA used in the ADC microphone mode.
  * @note   PGA gain of 6 dB is equivalent to the 2.4 V ADC full scale.
  * @rmtoll PGA_CONF     PGA_GAIN       LL_ADC_GetMicrophonePGAGain
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_PGA_GAIN_06_DB
  *         @arg @ref LL_ADC_PGA_GAIN_09_DB
  *         @arg @ref LL_ADC_PGA_GAIN_12_DB
  *         @arg @ref LL_ADC_PGA_GAIN_15_DB
  *         @arg @ref LL_ADC_PGA_GAIN_18_DB
  *         @arg @ref LL_ADC_PGA_GAIN_21_DB
  *         @arg @ref LL_ADC_PGA_GAIN_24_DB
  *         @arg @ref LL_ADC_PGA_GAIN_27_DB
  *         @arg @ref LL_ADC_PGA_GAIN_30_DB
  *         @arg @ref LL_ADC_PGA_GAIN_33_DB
  */
__STATIC_INLINE uint32_t LL_ADC_GetMicrophonePGAGain(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->PGA_CONF, ADC_PGA_CONF_PGA_GAIN));
}
#endif

/**
  * @}
  */


/** @defgroup ADC_LL_EF_Input_Switch_Selection ADC Input Switch Selection functions
  * @{
  */

/**
  * @brief  Set the input voltage range for the input single VINM0.
  * @rmtoll SWITCH     SE_VIN_0       LL_ADC_SetVoltageRangeSingleVinm0
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeSingleVinm0(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_0, (Range<<ADC_SWITCH_SE_VIN_0_Pos));
}


/**
  * @brief  Get the input voltage range for the input single VINM0.
  * @rmtoll SWITCH     SE_VIN_0       LL_ADC_GetVoltageRangeSingleVinm0
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeSingleVinm0(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_0))>>ADC_SWITCH_SE_VIN_0_Pos);
}


/**
  * @brief  Set the input voltage range for the input differential (VINP0 - VINM0).
  * @rmtoll SWITCH     SE_VIN_0       LL_ADC_SetVoltageRangeDiffVinp0Vinm0
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeDiffVinp0Vinm0(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_0, (Range<<ADC_SWITCH_SE_VIN_0_Pos));
}


/**
  * @brief  Get the input voltage range for the input differential (VINP0 - VINM0).
  * @rmtoll SWITCH     SE_VIN_0       LL_ADC_GetVoltageRangeDiffVinp0Vinm0
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeDiffVinp0Vinm0(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_0))>>ADC_SWITCH_SE_VIN_0_Pos);
}


/**
  * @brief  Set the input voltage range for the input single VINM1
  * @rmtoll SWITCH     SE_VIN_1       LL_ADC_SetVoltageRangeSingleVinm1
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeSingleVinm1(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_1, (Range<<ADC_SWITCH_SE_VIN_1_Pos));
}


/**
  * @brief  Get the input voltage range for the input single VINM1.
  * @rmtoll SWITCH     SE_VIN_1       LL_ADC_GetVoltageRangeSingleVinm1
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeSingleVinm1(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_1))>>ADC_SWITCH_SE_VIN_1_Pos);
}


/**
  * @brief  Set the input voltage range for the input differential (VINP1 - VINM1)
  * @rmtoll SWITCH     SE_VIN_1       LL_ADC_SetVoltageRangeDiffVinp1Vinm1
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeDiffVinp1Vinm1(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_1, (Range<<ADC_SWITCH_SE_VIN_1_Pos));
}


/**
  * @brief  Get the input voltage range for the input differential (VINP1 - VINM1).
  * @rmtoll SWITCH     SE_VIN_1       LL_ADC_GetVoltageRangeDiffVinp1Vinm1
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeDiffVinp1Vinm1(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_1))>>ADC_SWITCH_SE_VIN_1_Pos);
}


/**
  * @brief  Set the input voltage range for the input single VINM2.
  * @rmtoll SWITCH     SE_VIN_2       LL_ADC_SetVoltageRangeSingleVinm2
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeSingleVinm2(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_2, (Range<<ADC_SWITCH_SE_VIN_2_Pos));
}


/**
  * @brief  Get the input voltage range for the input single VINM2.
  * @rmtoll SWITCH     SE_VIN_2       LL_ADC_GetVoltageRangeSingleVinm2
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeSingleVinm2(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_2))>>ADC_SWITCH_SE_VIN_2_Pos);
}


/**
  * @brief  Set the input voltage range for the input differential (VINP2 - VINM2).
  * @rmtoll SWITCH     SE_VIN_2       LL_ADC_SetVoltageRangeDiffVinp2Vinm2
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeDiffVinp2Vinm2(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_2, (Range<<ADC_SWITCH_SE_VIN_2_Pos));
}


/**
  * @brief  Get the input voltage range for the input differential (VINP2 - VINM2).
  * @rmtoll SWITCH     SE_VIN_2       LL_ADC_GetVoltageRangeDiffVinp2Vinm2
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeDiffVinp2Vinm2(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_2))>>ADC_SWITCH_SE_VIN_2_Pos);
}


/**
  * @brief  Set the input voltage range for the input single VINM3.
  * @rmtoll SWITCH     SE_VIN_3       LL_ADC_SetVoltageRangeSingleVinm3
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeSingleVinm3(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_3, (Range<<ADC_SWITCH_SE_VIN_3_Pos));
}


/**
  * @brief  Get the input voltage range for the input single VINM3.
  * @rmtoll SWITCH     SE_VIN_3       LL_ADC_GetVoltageRangeSingleVinm3
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeSingleVinm3(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_3))>>ADC_SWITCH_SE_VIN_3_Pos);
}


/**
  * @brief  Set the input voltage range for the input differential (VINP3 - VINM3).
  * @rmtoll SWITCH     SE_VIN_3       LL_ADC_SetVoltageRangeDiffVinp3Vinm3
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeDiffVinp3Vinm3(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_3, (Range<<ADC_SWITCH_SE_VIN_3_Pos));
}


/**
  * @brief  Get the input voltage range for the input differential (VINP3 - VINM3).
  * @rmtoll SWITCH     SE_VIN_3       LL_ADC_GetVoltageRangeDiffVinp3Vinm3
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeDiffVinp3Vinm3(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_3))>>ADC_SWITCH_SE_VIN_3_Pos);
}


/**
  * @brief  Set the input voltage range for the input single VINP0.
  * @rmtoll SWITCH     SE_VIN_4       LL_ADC_SetVoltageRangeSingleVinp0
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeSingleVinp0(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_4, (Range<<ADC_SWITCH_SE_VIN_4_Pos));
}


/**
  * @brief  Get the input voltage range for the single VINP0.
  * @rmtoll SWITCH     SE_VIN_4       LL_ADC_GetVoltageRangeSingleVinp0
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeSingleVinp0(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_4))>>ADC_SWITCH_SE_VIN_4_Pos);
}


/**
  * @brief  Set the input voltage range for the input single VINP1.
  * @rmtoll SWITCH     SE_VIN_5       LL_ADC_SetVoltageRangeSingleVinp1
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeSingleVinp1(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_5, (Range<<ADC_SWITCH_SE_VIN_5_Pos));
}


/**
  * @brief  Get the input voltage range for the input single VINP1.
  * @rmtoll SWITCH     SE_VIN_5       LL_ADC_GetVoltageRangeSingleVinp1
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeSingleVinp1(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_5))>>ADC_SWITCH_SE_VIN_5_Pos);
}


/**
  * @brief  Set the input voltage range for the input VINP2.
  * @rmtoll SWITCH     SE_VIN_6       LL_ADC_SetVoltageRangeSingleVinp2
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeSingleVinp2(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_6, (Range<<ADC_SWITCH_SE_VIN_6_Pos));
}


/**
  * @brief  Get the input voltage range for the input VINP2.
  * @rmtoll SWITCH     SE_VIN_6       LL_ADC_GetVoltageRangeSingleVinp2
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeSingleVinp2(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_6))>>ADC_SWITCH_SE_VIN_6_Pos);
}


/**
  * @brief  Set the input voltage range for the input VINP3.
  * @rmtoll SWITCH     SE_VIN_7       LL_ADC_SetVoltageRangeSingleVinp3
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVoltageRangeSingleVinp3(ADC_TypeDef *ADCx, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_7, (Range<<ADC_SWITCH_SE_VIN_7_Pos));
}


/**
  * @brief  Get the input voltage range for the input VINP3.
  * @rmtoll SWITCH     SE_VIN_7       LL_ADC_GetVoltageRangeSingleVinp3
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetVoltageRangeSingleVinp3(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_7))>>ADC_SWITCH_SE_VIN_7_Pos);
}


/**
  * @}
  */


/** @defgroup ADC_LL_EF_DF_Configuration ADC Decimation Filter Configuration functions
  * @{
  */

#if defined(ADC_DF_CONF_DF_HALF_D_EN)
/**
  * @brief  Set the input dynamic range for Decimation Filter (DF).
  *         It can be full dynamic or half dynamic.
  * @rmtoll DF_CONF     DF_HALF_D_EN       LL_ADC_SetDFInputDynamic
  * @param  ADCx ADC instance
  * @param  Dynamic This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DF_DYN_RANGE_FULL
  *         @arg @ref LL_ADC_DF_DYN_RANGE_HALF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDFInputDynamic(ADC_TypeDef *ADCx, uint32_t Dynamic)
{
  SET_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HALF_D_EN);
}


/**
  * @brief  Get the input dynamic ragne for Decimation Filter (DF).
  *         It can be full dynamic or half dynamic.
  * @rmtoll DF_CONF     DF_HALF_D_EN       LL_ADC_GetDFInputDynamic
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DF_DYN_RANGE_FULL
  *         @arg @ref LL_ADC_DF_DYN_RANGE_HALF
  */
__STATIC_INLINE uint32_t LL_ADC_GetDFInputDynamic(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HALF_D_EN));
}
#endif

#if defined(ADC_DF_CONF_DF_HPF_EN)
/**
  * @brief  Enable the High Pass Filter (HPF) of the Decimation Filter (DF).
  *         The HPF cut off frequency is 40 Hz.
  * @rmtoll DF_CONF     DF_HPF_EN     LL_ADC_DFHighPassFilterEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DFHighPassFilterEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HPF_EN);
}


/**
  * @brief  Disable the High Pass Filter (HPF) of the Decimation Filter (DF).
  *         The HPF cut off frequency is 40 Hz.
  * @rmtoll DF_CONF     DF_HPF_EN     LL_ADC_DFHighPassFilterDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DFHighPassFilterDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HPF_EN);
}


/**
  * @brief  Check if the High Pass Filter (HPF) of the Decimation Filter (DF) is enabled.
  * @rmtoll DF_CONF     DF_HPF_EN     LL_ADC_IsDFHighPassFilterEnabled
  * @param  ADCx ADC instance
  * @retval 0: HPF is not enabled, 1: HPF is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDFHighPassFilterEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HPF_EN) == (ADC_DF_CONF_DF_HPF_EN)) ? 1UL : 0UL);
}
#endif

#if defined(ADC_DF_CONF_DF_MICROL_RN)
/**
  * @brief  Select the left/right channel on digital microphone mode.
  * @rmtoll DF_CONF     DF_MICROL_RN       LL_ADC_SetMicrophoneChannel
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DF_MIC_CH_LEFT
  *         @arg @ref LL_ADC_DF_MIC_CH_RIGHT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMicrophoneChannel(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_MICROL_RN, Channel);
}


/**
  * @brief  Get the left/right channel on digital microphone mode.
  * @rmtoll DF_CONF     DF_MICROL_RN       LL_ADC_GetMicrophoneChannel
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DF_MIC_CH_LEFT
  *         @arg @ref LL_ADC_DF_MIC_CH_RIGHT
  */
__STATIC_INLINE uint32_t LL_ADC_GetMicrophoneChannel(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_MICROL_RN));
}
#endif

#if defined(ADC_DF_CONF_PDM_RATE)
/**
  * @brief  Set the PDM clock rate.
  *         The PDM clock rate is : SYSTEM_CLOCK / (Divider).
  * @note   With a SYSTEM_CLOCK of 32 MHz, the PDM clock rate is:
  *         3.2  MHz with Divider = 10.
  *         1.28 MHz with Divider = 25.
  * @rmtoll DF_CONF     PDM_RATE       LL_ADC_SetPDMRate
  * @param  ADCx ADC instance
  * @param  Divider This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PDM_DIV_10
  *         @arg @ref LL_ADC_PDM_DIV_11
  *         @arg @ref LL_ADC_PDM_DIV_12
  *         @arg @ref LL_ADC_PDM_DIV_13
  *         @arg @ref LL_ADC_PDM_DIV_14
  *         @arg @ref LL_ADC_PDM_DIV_15
  *         @arg @ref LL_ADC_PDM_DIV_16
  *         @arg @ref LL_ADC_PDM_DIV_17
  *         @arg @ref LL_ADC_PDM_DIV_18
  *         @arg @ref LL_ADC_PDM_DIV_19
  *         @arg @ref LL_ADC_PDM_DIV_20
  *         @arg @ref LL_ADC_PDM_DIV_21
  *         @arg @ref LL_ADC_PDM_DIV_22
  *         @arg @ref LL_ADC_PDM_DIV_23
  *         @arg @ref LL_ADC_PDM_DIV_24
  *         @arg @ref LL_ADC_PDM_DIV_25
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetPDMRate(ADC_TypeDef *ADCx, uint32_t Divider)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_PDM_RATE, Divider);
}


/**
  * @brief  Get the PDM clock rate.
  *         The PDM clock rate is : SYSTEM_CLOCK / (Divider).
  * @note   With a SYSTEM_CLOCK of 32 MHz, the PDM clock rate is:
  *         3.2  MHz with Divider = 10.
  *         1.28 MHz with Divider = 25.
  * @rmtoll DF_CONF     PDM_RATE       LL_ADC_GetPDMRate
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_PDM_DIV_10
  *         @arg @ref LL_ADC_PDM_DIV_11
  *         @arg @ref LL_ADC_PDM_DIV_12
  *         @arg @ref LL_ADC_PDM_DIV_13
  *         @arg @ref LL_ADC_PDM_DIV_14
  *         @arg @ref LL_ADC_PDM_DIV_15
  *         @arg @ref LL_ADC_PDM_DIV_16
  *         @arg @ref LL_ADC_PDM_DIV_17
  *         @arg @ref LL_ADC_PDM_DIV_18
  *         @arg @ref LL_ADC_PDM_DIV_19
  *         @arg @ref LL_ADC_PDM_DIV_20
  *         @arg @ref LL_ADC_PDM_DIV_21
  *         @arg @ref LL_ADC_PDM_DIV_22
  *         @arg @ref LL_ADC_PDM_DIV_23
  *         @arg @ref LL_ADC_PDM_DIV_24
  *         @arg @ref LL_ADC_PDM_DIV_25
  */
__STATIC_INLINE uint32_t LL_ADC_GetPDMRate(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_PDM_RATE) + 10);
}
#endif

#if defined(ADC_DF_CONF_DF_O_S2U)
/**
  * @brief  Set the signed/unsigned output data format.
  * @rmtoll DF_CONF     DF_O_S2U       LL_ADC_SetDataOutputFormat
  * @param  ADCx ADC instance
  * @param  Format This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DATA_FRMT_SIGNED
  *         @arg @ref LL_ADC_DATA_FRMT_UNSIGNED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDataOutputFormat(ADC_TypeDef *ADCx, uint32_t Format)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_O_S2U, (Format << ADC_DF_CONF_DF_O_S2U_Pos));
}


/**
  * @brief  Get the signed/unsigned output data format.
  * @rmtoll DF_CONF     DF_O_S2U       LL_ADC_GetDataOutputFormat
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DATA_FRMT_SIGNED
  *         @arg @ref LL_ADC_DATA_FRMT_UNSIGNED
  */
__STATIC_INLINE uint32_t LL_ADC_GetDataOutputFormat(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_O_S2U)) >> ADC_DF_CONF_DF_O_S2U_Pos);
}
#endif

#if defined(ADC_DF_CONF_DF_I_U2S)
/**
  * @brief  Set the signed/unsigned input data format.
  * @rmtoll DF_CONF     DF_I_S2U       LL_ADC_SetDataInputFormat
  * @param  ADCx ADC instance
  * @param  Format This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DATA_FRMT_SIGNED
  *         @arg @ref LL_ADC_DATA_FRMT_UNSIGNED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDataInputFormat(ADC_TypeDef *ADCx, uint32_t Format)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_I_U2S, (Format << ADC_DF_CONF_DF_I_U2S_Pos));
}


/**
  * @brief  Get the signed/unsigned input data format.
  * @rmtoll DF_CONF     DF_I_S2U       LL_ADC_GetDataInputFormat
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DATA_FRMT_SIGNED
  *         @arg @ref LL_ADC_DATA_FRMT_UNSIGNED
  */
__STATIC_INLINE uint32_t LL_ADC_GetDataInputFormat(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_I_U2S)) >> ADC_DF_CONF_DF_I_U2S_Pos);
}
#endif

#if defined(ADC_DF_CONF_DF_ITP1P2)
/**
  * @brief  Enable the fractional interpolator.
  * @note   This bit must be set only for the generation of a data rate
  *         at 200 kps from ADC data at 1 MHz.
  * @rmtoll DF_CONF     DF_ITP1P2     LL_ADC_FractionalInterpolatorEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_FractionalInterpolatorEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_ITP1P2);
}


/**
  * @brief  Disable the fractional interpolator.
  * @note   This bit must be set only for the generation of a data rate
  *         at 200 kps from ADC data at 1 MHz.
  * @rmtoll DF_CONF     DF_ITP1P2     LL_ADC_FractionalInterpolatorDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_FractionalInterpolatorDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_ITP1P2);
}

/**
  * @brief  Check if the fractional interpolator is enabled.
  * @rmtoll DF_CONF     DF_ITP1P2     LL_ADC_IsFractionalInterpolatorEnabled
  * @param  ADCx ADC instance
  * @retval 0: Interpolator is not enabled, 1: Interpolator is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsFractionalInterpolatorEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_ITP1P2) == (ADC_DF_CONF_DF_ITP1P2)) ? 1UL : 0UL);
}
#endif

#if defined(ADC_DF_CONF_DF_CIC_DHF)
/**
  * @brief  Set the decimator factor of the CIC filter.
  * @note   This bit must be set (LL_ADC_CIC_DECIMATOR_FACTOR_HALF) 
  *         only for the generation of a data rate
  *         at 44.1 kps from ADC data at 1 MHz.
  * @rmtoll DF_CONF     DF_CIC_DHF       LL_ADC_SetCICDecimatorFactor
  * @param  ADCx ADC instance
  * @param  Factor This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CIC_DECIMATOR_FACTOR_HALF
  *         @arg @ref LL_ADC_CIC_DECIMATOR_FACTOR_INTEGER
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCICDecimatorFactor(ADC_TypeDef *ADCx, uint32_t Factor)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_CIC_DHF, Factor);
}


/**
  * @brief  Get the decimator factor of the CIC filter.
  * @rmtoll DF_CONF     DF_CIC_DHF       LL_ADC_GetCICDecimatorFactor
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CIC_DECIMATOR_FACTOR_HALF
  *         @arg @ref LL_ADC_CIC_DECIMATOR_FACTOR_INTEGER
  */
__STATIC_INLINE uint32_t LL_ADC_GetCICDecimatorFactor(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_CIC_DHF)));
}
#endif

#if defined(ADC_DF_CONF_DF_CIC_DEC_FACTOR)
/**
  * @brief  Set the output frequency for the microphone mode.
  * @rmtoll DF_CONF     DF_CIC_DEC_FACTOR       LL_ADC_SetMicrophoneOutputDatarate
  * @note   Different parameters for digital microphone and analog microphone.
  * @param  ADCx ADC instance
  * @param  Frequency This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ
  *
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMicrophoneOutputDatarate(ADC_TypeDef *ADCx, uint32_t Frequency)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_CIC_DEC_FACTOR, Frequency);
}


/**
  * @brief  Get the output frequency for the microphone mode.
  * @rmtoll DF_CONF     DF_CIC_DEC_FACTOR       LL_ADC_GetMicrophoneOutputDatarate
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ
  *
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ
  */
__STATIC_INLINE uint32_t LL_ADC_GetMicrophoneOutputDatarate(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_CIC_DEC_FACTOR));
}
#endif

/**
  * @}
  */


/** @defgroup ADC_LL_EF_DS_Configuration ADC Down Sampler Configuration functions
  * @{
  */

/**
  * @brief  Configure the width (in bit) and the ratio of the output data from the Down Sampler.
  * @param  ADCx ADC instance
  * @param  Width This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT (default)
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @param  Ratio This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_RATIO_01 (no down sampling, default)
  *         @arg @ref LL_ADC_DS_RATIO_02
  *         @arg @ref LL_ADC_DS_RATIO_04
  *         @arg @ref LL_ADC_DS_RATIO_08
  *         @arg @ref LL_ADC_DS_RATIO_16
  *         @arg @ref LL_ADC_DS_RATIO_32
  *         @arg @ref LL_ADC_DS_RATIO_64
  *         @arg @ref LL_ADC_DS_RATIO_128
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureDSDataOutput(ADC_TypeDef *ADCx, uint32_t Width, uint32_t Ratio)
{
  MODIFY_REG(ADCx->DS_CONF, (ADC_DS_CONF_DS_WIDTH | ADC_DS_CONF_DS_RATIO), ((Width<<ADC_DS_CONF_DS_WIDTH_Pos) | Ratio));
}

/**
  * @brief  Set the width (in bit) of the output data from the Down Sampler.
  * @rmtoll DS_CONF     DS_WIDTH       LL_ADC_SetDSDataOutputWidth
  * @param  ADCx ADC instance
  * @param  Width This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT (default)
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDSDataOutputWidth(ADC_TypeDef *ADCx, uint32_t Width)
{
  MODIFY_REG(ADCx->DS_CONF, ADC_DS_CONF_DS_WIDTH, (Width<<ADC_DS_CONF_DS_WIDTH_Pos));
}


/**
  * @brief  Get the width (in bit) of the output data from the Down Sampler (DS).
  * @rmtoll DS_CONF     DS_WIDTH       LL_ADC_GetDSDataOutputWidth
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT (default)
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  */
__STATIC_INLINE uint32_t LL_ADC_GetDSDataOutputWidth(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DS_CONF, ADC_DS_CONF_DS_WIDTH) >> ADC_DS_CONF_DS_WIDTH_Pos);
}


/**
  * @brief  Set the ratio of the Down Sampler (DS).
  * @rmtoll DS_CONF     DS_RATIO       LL_ADC_SetDSDataOutputRatio
  * @param  ADCx ADC instance
  * @param  Ratio This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_RATIO_01 (no down sampling, default)
  *         @arg @ref LL_ADC_DS_RATIO_02
  *         @arg @ref LL_ADC_DS_RATIO_04
  *         @arg @ref LL_ADC_DS_RATIO_08
  *         @arg @ref LL_ADC_DS_RATIO_16
  *         @arg @ref LL_ADC_DS_RATIO_32
  *         @arg @ref LL_ADC_DS_RATIO_64
  *         @arg @ref LL_ADC_DS_RATIO_128
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDSDataOutputRatio(ADC_TypeDef *ADCx, uint32_t Ratio)
{
  MODIFY_REG(ADCx->DS_CONF, ADC_DS_CONF_DS_RATIO, Ratio);
}


/**
  * @brief  Get the ratio of the Down Sampler (DS).
  * @rmtoll DS_CONF     DS_RATIO       LL_ADC_GetDSDataOutputRatio
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DS_RATIO_01 (no down sampling, default)
  *         @arg @ref LL_ADC_DS_RATIO_02
  *         @arg @ref LL_ADC_DS_RATIO_04
  *         @arg @ref LL_ADC_DS_RATIO_08
  *         @arg @ref LL_ADC_DS_RATIO_16
  *         @arg @ref LL_ADC_DS_RATIO_32
  *         @arg @ref LL_ADC_DS_RATIO_64
  *         @arg @ref LL_ADC_DS_RATIO_128
  */
__STATIC_INLINE uint32_t LL_ADC_GetDSDataOutputRatio(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DS_CONF, ADC_DS_CONF_DS_RATIO));
}


/**
  * @}
  */



/** @defgroup ADC_LL_EF_Sequence_Configuration ADC Sequence Configuration functions
  * @{
  */


/**
  * @brief  Set the channel code for the conversion of the sequence number 0.
  * @rmtoll SEQ_1     SEQ0       LL_ADC_SetChannelSeq0
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHL_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CHL_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CHL_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CHL_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CHL_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CHL_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CHL_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CHL_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CHL_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CHL_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CHL_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CHL_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CHL_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CHL_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq0(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ0, (Channel<<ADC_SEQ_1_SEQ0_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 0.
  * @rmtoll SEQ_1     SEQ0       LL_ADC_GetChannelSeq0
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq0(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ0)) >> ADC_SEQ_1_SEQ0_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 1.
  * @rmtoll SEQ_1     SEQ1       LL_ADC_SetChannelSeq1
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq1(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ1, (Channel<<ADC_SEQ_1_SEQ1_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 1.
  * @rmtoll SEQ_1     SEQ1       LL_ADC_GetChannelSeq1
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq1(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ1)) >> ADC_SEQ_1_SEQ1_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 2.
  * @rmtoll SEQ_1     SEQ2       LL_ADC_SetChannelSeq2
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq2(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ2, (Channel<<ADC_SEQ_1_SEQ2_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 2.
  * @rmtoll SEQ_1     SEQ2       LL_ADC_GetChannelSeq2
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq2(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ2)) >> ADC_SEQ_1_SEQ2_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 3.
  * @rmtoll SEQ_1     SEQ3       LL_ADC_SetChannelSeq3
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq3(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ3, (Channel<<ADC_SEQ_1_SEQ3_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 3.
  * @rmtoll SEQ_1     SEQ3       LL_ADC_GetChannelSeq3
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq3(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ3)) >> ADC_SEQ_1_SEQ3_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 4.
  * @rmtoll SEQ_1     SEQ4       LL_ADC_SetChannelSeq4
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq4(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ4, (Channel<<ADC_SEQ_1_SEQ4_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 4.
  * @rmtoll SEQ_1     SEQ4       LL_ADC_GetChannelSeq4
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq4(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ4)) >> ADC_SEQ_1_SEQ4_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 5.
  * @rmtoll SEQ_1     SEQ5       LL_ADC_SetChannelSeq5
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq5(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ5, (Channel<<ADC_SEQ_1_SEQ5_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 5.
  * @rmtoll SEQ_1     SEQ5       LL_ADC_GetChannelSeq5
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq5(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ5)) >> ADC_SEQ_1_SEQ5_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 6.
  * @rmtoll SEQ_1     SEQ6       LL_ADC_SetChannelSeq6
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq6(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ6, (Channel<<ADC_SEQ_1_SEQ6_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 6.
  * @rmtoll SEQ_1     SEQ6       LL_ADC_GetChannelSeq6
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq6(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ6)) >> ADC_SEQ_1_SEQ6_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 7.
  * @rmtoll SEQ_1     SEQ7       LL_ADC_SetChannelSeq7
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq7(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ7, (Channel<<ADC_SEQ_1_SEQ7_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 7.
  * @rmtoll SEQ_1     SEQ7       LL_ADC_GetChannelSeq7
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq7(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_1, ADC_SEQ_1_SEQ7)) >> ADC_SEQ_1_SEQ7_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 8.
  * @rmtoll SEQ_2     SEQ8       LL_ADC_SetChannelSeq8
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq8(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ8, (Channel<<ADC_SEQ_2_SEQ8_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 8.
  * @rmtoll SEQ_2     SEQ8       LL_ADC_GetChannelSeq8
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq8(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ8)) >> ADC_SEQ_2_SEQ8_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 9.
  * @rmtoll SEQ_2     SEQ9       LL_ADC_SetChannelSeq9
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq9(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ9, (Channel<<ADC_SEQ_2_SEQ9_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 9.
  * @rmtoll SEQ_2     SEQ9       LL_ADC_GetChannelSeq9
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq9(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ9)) >> ADC_SEQ_2_SEQ9_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 10.
  * @rmtoll SEQ_2     SEQ10       LL_ADC_SetChannelSeq10
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq10(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ10, (Channel<<ADC_SEQ_2_SEQ10_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 10.
  * @rmtoll SEQ_2     SEQ10       LL_ADC_GetChannelSeq10
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq10(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ10)) >> ADC_SEQ_2_SEQ10_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 11.
  * @rmtoll SEQ_2     SEQ11       LL_ADC_SetChannelSeq11
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq11(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ11, (Channel<<ADC_SEQ_2_SEQ11_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 11.
  * @rmtoll SEQ_2     SEQ11       LL_ADC_GetChannelSeq11
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq11(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ11)) >> ADC_SEQ_2_SEQ11_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 12.
  * @rmtoll SEQ_2     SEQ12       LL_ADC_SetChannelSeq12
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq12(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ12, (Channel<<ADC_SEQ_2_SEQ12_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 12.
  * @rmtoll SEQ_2     SEQ12       LL_ADC_GetChannelSeq12
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq12(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ12)) >> ADC_SEQ_2_SEQ12_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 13.
  * @rmtoll SEQ_2     SEQ13       LL_ADC_SetChannelSeq13
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq13(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ13, (Channel<<ADC_SEQ_2_SEQ13_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 13.
  * @rmtoll SEQ_2     SEQ13       LL_ADC_GetChannelSeq13
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq13(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ13)) >> ADC_SEQ_2_SEQ13_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 14.
  * @rmtoll SEQ_2     SEQ14       LL_ADC_SetChannelSeq14
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq14(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ14, (Channel<<ADC_SEQ_2_SEQ14_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 14.
  * @rmtoll SEQ_2     SEQ14       LL_ADC_GetChannelSeq14
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq14(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ14)) >> ADC_SEQ_2_SEQ14_Pos);
}


/**
  * @brief  Set the channel code for the conversion of the sequence number 15.
  * @rmtoll SEQ_2     SEQ15       LL_ADC_SetChannelSeq15
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSeq15(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ15, (Channel<<ADC_SEQ_2_SEQ15_Pos) );  
}


/**
  * @brief  Get the channel code for the conversion of the sequence number 15.
  * @rmtoll SEQ_2     SEQ15       LL_ADC_GetChannelSeq15
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT
  *         @arg @ref LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT
  *         @arg @ref LL_ADC_CH_BATTERY_LEVEL_DETECTOR
  *         @arg @ref LL_ADC_CH_TEMPERATURE_SENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSeq15(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->SEQ_2, ADC_SEQ_2_SEQ15)) >> ADC_SEQ_2_SEQ15_Pos);
}


/**
  * @}
  */


/** @defgroup ADC_LL_EF_Calibration_Points_Configuration ADC Calibration Points Configuration functions
  * @{
  */

/**
  * @brief  Configure the gain and the offset of the calibration point 1.
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @param  Offset the signed offset of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureCalibPoint1(ADC_TypeDef *ADCx, uint16_t Gain, uint8_t Offset)
{
  MODIFY_REG(ADCx->COMP_1, (ADC_COMP_1_GAIN1 | ADC_COMP_1_OFFSET1), (Gain | (Offset<<ADC_COMP_1_OFFSET1_Pos)) );
}

/**
  * @brief  Write the calibration point 1.
  * @param  ADCx ADC instance
  * @param  Calib Calibration point 1.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_WriteCalibPoint1(ADC_TypeDef *ADCx, uint32_t Calib)
{
  WRITE_REG(ADCx->COMP_1, Calib);
}

/**
  * @brief  Set the gain of the calibration point 1.
  * @rmtoll COMP_1     GAIN1       LL_ADC_SetCalibPoint1Gain
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPoint1Gain(ADC_TypeDef *ADCx, uint16_t Gain)
{
  MODIFY_REG(ADCx->COMP_1, ADC_COMP_1_GAIN1, Gain);
}


/**
  * @brief  Get the gain of the calibration point 1.
  * @rmtoll COMP_1     GAIN1       LL_ADC_GetCalibPoint1Gain
  * @param  ADCx ADC instance
  * @retval Return the gain of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPoint1Gain(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->COMP_1, ADC_COMP_1_GAIN1));
}


/**
  * @brief  Set the offset of the calibration point 1.
  * @rmtoll COMP_1     OFFSET1       LL_ADC_SetCalibPoint1Offset
  * @param  ADCx ADC instance
  * @param  Offset the signed offset of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPoint1Offset(ADC_TypeDef *ADCx, uint8_t Offset)
{
  MODIFY_REG(ADCx->COMP_1, ADC_COMP_1_OFFSET1, (Offset<<ADC_COMP_1_OFFSET1_Pos) );
}


/**
  * @brief  Get the offset of the calibration point 1.
  * @rmtoll COMP_1     OFFSET1       LL_ADC_GetCalibPoint1Offset
  * @param  ADCx ADC instance
  * @retval Return the signed offset of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPoint1Offset(ADC_TypeDef *ADCx)
{
  return (uint32_t)( READ_BIT(ADCx->COMP_1, ADC_COMP_1_OFFSET1) >> ADC_COMP_1_OFFSET1_Pos);
}


/**
  * @brief  Configure the gain and the offset of the calibration point 2.
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @param  Offset the signed offset of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureCalibPoint2(ADC_TypeDef *ADCx, uint16_t Gain, uint8_t Offset)
{
  MODIFY_REG(ADCx->COMP_2, (ADC_COMP_2_GAIN2 | ADC_COMP_2_OFFSET2), (Gain | (Offset<<ADC_COMP_2_OFFSET2_Pos)) );
}


/**
  * @brief  Configure the calibration point 2.
  * @param  ADCx ADC instance
  * @param  Calib Calibration point 2.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_WriteCalibPoint2(ADC_TypeDef *ADCx, uint32_t Calib)
{
  WRITE_REG(ADCx->COMP_2, Calib);
}

/**
  * @brief  Set the gain of the calibration point 2.
  * @rmtoll COMP_2     GAIN2       LL_ADC_SetCalibPoint2Gain
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPoint2Gain(ADC_TypeDef *ADCx, uint16_t Gain)
{
  MODIFY_REG(ADCx->COMP_2, ADC_COMP_2_GAIN2, Gain);
}


/**
  * @brief  Get the gain of the calibration point 2.
  * @rmtoll COMP_2     GAIN2       LL_ADC_GetCalibPoint1Gain
  * @param  ADCx ADC instance
  * @retval Return the gain of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPoint2Gain(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->COMP_2, ADC_COMP_2_GAIN2));
}


/**
  * @brief  Set the offset of the calibration point 2.
  * @rmtoll COMP_2     OFFSET2       LL_ADC_SetCalibPoint2Offset
  * @param  ADCx ADC instance
  * @param  Offset the signed offset of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPoint2Offset(ADC_TypeDef *ADCx, uint8_t Offset)
{
  MODIFY_REG(ADCx->COMP_2, ADC_COMP_2_OFFSET2, (Offset<<ADC_COMP_2_OFFSET2_Pos));
}


/**
  * @brief  Get the offset of the calibration point 2.
  * @rmtoll COMP_2     OFFSET2       LL_ADC_GetCalibPoint2Offset
  * @param  ADCx ADC instance
  * @retval Return the signed offset of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPoint2Offset(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->COMP_2, ADC_COMP_2_OFFSET2));
}


/**
  * @brief  Configure the gain and the offset of the calibration point 3.
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @param  Offset the signed offset of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureCalibPoint3(ADC_TypeDef *ADCx, uint16_t Gain, uint8_t Offset)
{
  MODIFY_REG(ADCx->COMP_3, (ADC_COMP_3_GAIN3 | ADC_COMP_3_OFFSET3), (Gain | (Offset<<ADC_COMP_3_OFFSET3_Pos)) );
}


/**
  * @brief  Write the calibration point 3.
  * @param  ADCx ADC instance
  * @param  Calib Calibration point 3.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_WriteCalibPoint3(ADC_TypeDef *ADCx, uint32_t Calib)
{
  WRITE_REG(ADCx->COMP_3, Calib);
}


/**
  * @brief  Set the gain of the calibration point 3.
  * @rmtoll COMP_3     GAIN3       LL_ADC_SetCalibPoint3Gain
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPoint3Gain(ADC_TypeDef *ADCx, uint16_t Gain)
{
  MODIFY_REG(ADCx->COMP_3, ADC_COMP_3_GAIN3, Gain);
}


/**
  * @brief  Get the gain of the calibration point 3.
  * @rmtoll COMP_3     GAIN3       LL_ADC_GetCalibPoint3Gain
  * @param  ADCx ADC instance
  * @retval Return the gain of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPoint3Gain(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->COMP_3, ADC_COMP_3_GAIN3));
}


/**
  * @brief  Set the offset of the calibration point 3.
  * @rmtoll COMP_3     OFFSET3       LL_ADC_SetCalibPoint3Offset
  * @param  ADCx ADC instance
  * @param  Offset the signed offset of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPoint3Offset(ADC_TypeDef *ADCx, uint8_t Offset)
{
  MODIFY_REG(ADCx->COMP_3, ADC_COMP_3_OFFSET3, (Offset<<ADC_COMP_3_OFFSET3_Pos));
}


/**
  * @brief  Get the offset of the calibration point 3.
  * @rmtoll COMP_3     OFFSET3       LL_ADC_GetCalibPoint1Offset
  * @param  ADCx ADC instance
  * @retval Return the signed offset of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPoint3Offset(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->COMP_3, ADC_COMP_3_OFFSET3));
}


/**
  * @brief  Configure the gain and the offset of the calibration point 4.
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @param  Offset the signed offset of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureCalibPoint4(ADC_TypeDef *ADCx, uint16_t Gain, uint8_t Offset)
{
  MODIFY_REG(ADCx->COMP_4, (ADC_COMP_4_GAIN4 | ADC_COMP_4_OFFSET4), (Gain | (Offset<<ADC_COMP_4_OFFSET4_Pos)) );
}


/**
  * @brief  Write the calibration point 4.
  * @param  ADCx ADC instance
  * @param  Calib Calibration point 4.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_WriteCalibPoint4(ADC_TypeDef *ADCx, uint32_t Calib)
{
  WRITE_REG(ADCx->COMP_4, Calib);
}


/**
  * @brief  Set the gain of the calibration point 4.
  * @rmtoll COMP_4     GAIN4       LL_ADC_SetCalibPoint4Gain
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPoint4Gain(ADC_TypeDef *ADCx, uint16_t Gain)
{
  MODIFY_REG(ADCx->COMP_4, ADC_COMP_4_GAIN4, Gain);
}


/**
  * @brief  Get the gain of the calibration point 4.
  * @rmtoll COMP_4     GAIN4       LL_ADC_GetCalibPoint4Gain
  * @param  ADCx ADC instance
  * @retval Return the gain of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPoint4Gain(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->COMP_4, ADC_COMP_4_GAIN4));
}


/**
  * @brief  Set the offset of the calibration point 4.
  * @rmtoll COMP_4     OFFSET4       LL_ADC_SetCalibPoint4Offset
  * @param  ADCx ADC instance
  * @param  Offset the signed offset of the first calibration point.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPoint4Offset(ADC_TypeDef *ADCx, uint8_t Offset)
{
  MODIFY_REG(ADCx->COMP_4, ADC_COMP_4_OFFSET4, (Offset<<ADC_COMP_4_OFFSET4_Pos));
}


/**
  * @brief  Get the offset of the calibration point 4.
  * @rmtoll COMP_4     OFFSET4       LL_ADC_GetCalibPoint4Offset
  * @param  ADCx ADC instance
  * @retval Return the signed offset of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPoint4Offset(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->COMP_4, ADC_COMP_4_OFFSET4));
}


/**
  * @brief  Set the use of a specific calibration point for
  *         ADC differential mode with Vinput range = 3.6 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN8       LL_ADC_SetCalibPointForDiff3V6
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForDiff3V6(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN8, (Point << ADC_COMP_SEL_OFFSET_GAIN8_Pos) ); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC differential mode with Vinput range = 3.6 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN8       LL_ADC_GetCalibPointForDiff3V6
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForDiff3V6(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN8) >> ADC_COMP_SEL_OFFSET_GAIN8_Pos ));
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC single positive mode with Vinput range = 3.6 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN7       LL_ADC_SetCalibPointForSinglePos3V6
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForSinglePos3V6(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN7, (Point << ADC_COMP_SEL_OFFSET_GAIN7_Pos)); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC single positive mode with Vinput range = 3.6 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN7       LL_ADC_GetCalibPointForSinglePos3V6
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForSinglePos3V6(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN7) >>ADC_COMP_SEL_OFFSET_GAIN7_Pos ));
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC single negative mode with Vinput range = 3.6 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN6       LL_ADC_SetCalibPointForSingleNeg3V6
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForSingleNeg3V6(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN6, (Point << ADC_COMP_SEL_OFFSET_GAIN6_Pos)); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC single negative mode with Vinput range = 3.6 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN6       LL_ADC_GetCalibPointForSingleNeg3V6
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForSingleNeg3V6(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN6) >> ADC_COMP_SEL_OFFSET_GAIN6_Pos));
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC differential mode with Vinput range = 2.4 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN5       LL_ADC_SetCalibPointForDiff2V4
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForDiff2V4(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN5, (Point << ADC_COMP_SEL_OFFSET_GAIN5_Pos)); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC differential mode with Vinput range = 2.4 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN5       LL_ADC_GetCalibPointForDiff2V4
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForDiff2V4(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN5) >> ADC_COMP_SEL_OFFSET_GAIN5_Pos));
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC single positive mode with Vinput range = 2.4 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN4       LL_ADC_SetCalibPointForSinglePos2V4
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForSinglePos2V4(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN4, (Point << ADC_COMP_SEL_OFFSET_GAIN4_Pos)); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC single positive mode with Vinput range = 2.4 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN4       LL_ADC_GetCalibPointForSinglePos2V4
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForSinglePos2V4(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN4) >> ADC_COMP_SEL_OFFSET_GAIN4_Pos));
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC single negative mode with Vinput range = 2.4 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN3       LL_ADC_SetCalibPointForSingleNeg2V4
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForSingleNeg2V4(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN3, (Point << ADC_COMP_SEL_OFFSET_GAIN3_Pos)); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC single negative mode with Vinput range = 2.4 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN3       LL_ADC_GetCalibPointForSingleNeg2V4
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForSingleNeg2V4(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN3) >> ADC_COMP_SEL_OFFSET_GAIN3_Pos));
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC differential mode with Vinput range = 1.2 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN2       LL_ADC_SetCalibPointForDiff1V2
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForDiff1V2(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN2, (Point << ADC_COMP_SEL_OFFSET_GAIN2_Pos)); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC differential mode with Vinput range = 1.2 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN2       LL_ADC_GetCalibPointForDiff1V2
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForDiff1V2(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN2) >> ADC_COMP_SEL_OFFSET_GAIN2_Pos));
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC single positive mode with Vinput range = 1.2 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN1       LL_ADC_SetCalibPointForSinglePos1V2
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForSinglePos1V2(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN1, (Point << ADC_COMP_SEL_OFFSET_GAIN1_Pos)); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC single positive mode with Vinput range = 1.2 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN1       LL_ADC_GetCalibPointForSinglePos1V2
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForSinglePos1V2(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN1) >> ADC_COMP_SEL_OFFSET_GAIN1_Pos));
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC single negative mode with Vinput range = 1.2 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN0       LL_ADC_SetCalibPointForSingleNeg1V2
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForSingleNeg1V2(ADC_TypeDef *ADCx, uint32_t Point)
{
  MODIFY_REG(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN0, (Point << ADC_COMP_SEL_OFFSET_GAIN0_Pos)); 
}


/**
  * @brief  Get what calibration point is used for
  *         ADC single negative mode with Vinput range = 1.2 V.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN0       LL_ADC_GetCalibPointForSingleNeg1V2
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForSingleNeg1V2(ADC_TypeDef *ADCx, uint32_t InputMode)
{
  return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN0) >> ADC_COMP_SEL_OFFSET_GAIN0_Pos));
}



/**
  * @}
  */


/** @defgroup ADC_LL_EF_WDG_TH_Configuration ADC Watchdog Thresholds Configuration functions
  * @{
  */


/**
  * @brief  Configure the WatchDoG threshold low and high.
  * @param  ADCx ADC instance
  * @param  LowThreshold This parameter is a 12-bit value.
  * @param  HighThreshold This parameter is a 12-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureWDGThresholds(ADC_TypeDef *ADCx, uint32_t LowThreshold, uint32_t HighThreshold)
{
  MODIFY_REG(ADCx->WD_TH, (ADC_WD_TH_WD_LT | ADC_WD_TH_WD_HT), (LowThreshold | (HighThreshold<<ADC_WD_TH_WD_HT_Pos)) );
}


/**
  * @brief  Set the WatchDoG threshold low.
  * @rmtoll WD_TH     ADC_WD_TH_WD_LT     LL_ADC_SetWDGThresholdLow
  * @param  ADCx ADC instance
  * @param  Threshold This parameter is a 12-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetWDGThresholdLow(ADC_TypeDef *ADCx, uint32_t Threshold)
{
  MODIFY_REG(ADCx->WD_TH, ADC_WD_TH_WD_LT, Threshold);
}


/**
  * @brief  Get the WatchDoG threshold low.
  * @rmtoll WD_TH     ADC_WD_TH_WD_LT     LL_ADC_GetWDGThresholdLow
  * @param  ADCx ADC instance
  * @retval Returned value of the low threshold.
  */
__STATIC_INLINE uint32_t LL_ADC_GetWDGThresholdLow(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->WD_TH, ADC_WD_TH_WD_LT)));
}

/**
  * @brief  Set the WatchDoG threshold high.
  * @rmtoll WD_TH     ADC_WD_TH_WD_HT     LL_ADC_SetWDGThresholdHigh
  * @param  ADCx ADC instance
  * @param  Threshold This parameter is a 12-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetWDGThresholdHigh(ADC_TypeDef *ADCx, uint32_t Threshold)
{
  MODIFY_REG(ADCx->WD_TH, ADC_WD_TH_WD_HT, (Threshold<<ADC_WD_TH_WD_HT_Pos) );
}


/**
  * @brief  Get the WatchDoG threshold high.
  * @rmtoll WD_TH     ADC_WD_TH_WD_HT     LL_ADC_GetWDGThresholdHigh
  * @param  ADCx ADC instance
  * @retval Returned value of the high threshold.
  */
__STATIC_INLINE uint32_t LL_ADC_GetWDGThresholdHigh(ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->WD_TH, ADC_WD_TH_WD_HT) >> ADC_WD_TH_WD_HT_Pos));
}


/**
  * @brief  Set the input channels the watchdog must check.
  * @note   ChannelMask can be an OR of the listed parameters.
  * @rmtoll WD_CONF     AWD_CHX       LL_ADC_SetWDGInputChannels
  * @param  ADCx ADC instance
  * @param  ChannelMask This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_WDG_CH_VINM0_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VINM1_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VINM2_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VINM3_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_MICROM_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VBAT_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_GND_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VDDA_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VINP0_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_VINP1_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_VINP2_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_VINP3_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_MICROP_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_TEMP_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_GND_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_VDDA_TO_POS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetWDGInputChannels(ADC_TypeDef *ADCx, uint32_t ChannelMask)
{
  MODIFY_REG(ADCx->WD_CONF, ADC_WD_CONF_AWD_CHX, ChannelMask);
}


/**
  * @brief  Get the input channels the watchdog must check.
  * @note   The returned value can be an OR of the listed parameters.
  * @rmtoll WD_CONF     AWD_CHX       LL_ADC_GetWDGInputChannels
  * @param  ADCx ADC instance
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_ADC_WDG_CH_VINM0_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VINM1_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VINM2_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VINM3_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_MICROM_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VBAT_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_GND_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VDDA_TO_NEG
  *         @arg @ref LL_ADC_WDG_CH_VINP0_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_VINP1_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_VINP2_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_VINP3_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_MICROP_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_TEMP_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_GND_TO_POS
  *         @arg @ref LL_ADC_WDG_CH_VDDA_TO_POS
  */
__STATIC_INLINE uint32_t LL_ADC_GetWDGInputChannels(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->WD_CONF, ADC_WD_CONF_AWD_CHX));
}


/**
  * @}
  */


/** @defgroup ADC_LL_EF_Output_Data ADC Output Data functions
  * @{
  */


/**
  * @brief  Get the 16-bit output data from the Down Sampler (DS).
  * @rmtoll DS_DATAOUT       DS_DATA          LL_ADC_DSGetOutputData
  * @param  ADCx ADC instance
  * @retval The output data from DS.
  */
__STATIC_INLINE uint32_t LL_ADC_DSGetOutputData(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DS_DATAOUT, ADC_DS_DATAOUT_DS_DATA));
}

#if defined(DF_DATAOUT)
/**
  * @brief  Get the 16-bit output data from the Decimation Filter (DF).
  * @rmtoll DF_DATAOUT       DF_DATA          LL_ADC_DFGetOutputData
  * @param  ADCx ADC instance
  * @retval The output data from DF.
  */
__STATIC_INLINE uint32_t LL_ADC_DFGetOutputData(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_DATAOUT, ADC_DF_DATAOUT_DF_DATA));
}
#endif

/**
  * @brief  Get the address of the register DS_DATAOUT to be used for setting the DMA channel.
  *         The output data register from Down Sampler.
  * @rmtoll DS_DATAOUT       DS_DATA         LL_ADC_GetOutputDataRegDS
  * @param  ADCx ADC instance
  * @retval The address of the register DS_DATAOUT.
  */
__STATIC_INLINE uint32_t LL_ADC_GetOutputDataRegDS(ADC_TypeDef *ADCx)
{  
  return (uint32_t)&(ADCx->DS_DATAOUT);
}

#if defined(ADC_DF_DATAOUT_DF_DATA)
/**
  * @brief  Get the address of the register DF_DATAOUT to be used for setting the DMA channel.
  *         The output data register from Decimation Filter.
  * @rmtoll DF_DATAOUT       DF_DATA         LL_ADC_GetOutputDataRegDF
  * @param  ADCx ADC instance
  * @retval The address of the register DF_DATAOUT.
  */
__STATIC_INLINE uint32_t LL_ADC_GetOutputDataRegDF(ADC_TypeDef *ADCx)
{  
  return (uint32_t)&(ADCx->DF_DATAOUT);
}
#endif

/**
  * @}
  */


/** @defgroup ADC_LL_EF_FLAG_Management ADC flag management
  * @{
  */


/**
  * @brief  Get all the flags status.
  * @param  ADCx ADC instance
  * @retval All the status flags of the register IRQ_STATUS. 
  *         The value is a combination of the following values:
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRFL
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDF
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDS
  *         @arg @ref LL_ADC_IRQ_FLAG_AWD
  *         @arg @ref LL_ADC_IRQ_FLAG_EOS
  *         @arg @ref LL_ADC_IRQ_FLAG_EODF
  *         @arg @ref LL_ADC_IRQ_FLAG_EODS
  */
__STATIC_INLINE uint32_t LL_ADC_GetActiveFlags(ADC_TypeDef *ADCx)
{
#ifdef LL_ADC_IRQ_FLAGS_MASK
  return (uint32_t)(READ_BIT(ADCx->IRQ_STATUS, LL_ADC_IRQ_FLAGS_MASK));
#else
  return 0;
#endif
}


/**
  * @brief  Clear all the flags status.
  * @param  ADCx ADC instance
  * @param  FlagsMask This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRFL
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDF
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDS
  *         @arg @ref LL_ADC_IRQ_FLAG_AWD
  *         @arg @ref LL_ADC_IRQ_FLAG_EOS
  *         @arg @ref LL_ADC_IRQ_FLAG_EODF
  *         @arg @ref LL_ADC_IRQ_FLAG_EODS
  * @retval None.
  */
__STATIC_INLINE void LL_ADC_ClearActiveFlags(ADC_TypeDef *ADCx, uint32_t FlagsMask)
{
  SET_BIT(ADCx->IRQ_STATUS, FlagsMask);
}


/**
  * @brief  Get if the flags status is set.
  * @param  ADCx ADC instance
  * @param  FlagsMask This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRFL
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDF
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDS
  *         @arg @ref LL_ADC_IRQ_FLAG_AWD
  *         @arg @ref LL_ADC_IRQ_FLAG_EOS
  *         @arg @ref LL_ADC_IRQ_FLAG_EODF
  *         @arg @ref LL_ADC_IRQ_FLAG_EODS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag(ADC_TypeDef *ADCx, uint32_t Flag)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, Flag) == (Flag)) ? 1UL : 0UL);
}

#if defined(ADC_IRQ_STATUS_DF_OVRFL_IRQ)
/**
  * @brief  Get the status of the flag DF_OVRFL.
  *         The flag indicates, if set, the Decimation Filter output is saturated.
  * @rmtoll IRQ_STATUS      DF_OVRFL_IRQ     LL_ADC_IsActiveFlag_DFOVRFL
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_DFOVRFL(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_DF_OVRFL_IRQ) == (ADC_IRQ_STATUS_DF_OVRFL_IRQ)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flag DF_OVRFL.
  * @rmtoll IRQ_STATUS      DF_OVRFL_IRQ     LL_ADC_ClearFlag_DFOVRFL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_DFOVRFL(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_DF_OVRFL_IRQ);
}
#endif

#if defined(ADC_IRQ_STATUS_OVR_DF_IRQ)
/**
  * @brief  Get the status of the flag OVR_DF.
  *         The flag indicates, if set, the Decimation Filter output is overran (at least one data is lost).
  * @rmtoll IRQ_STATUS      OVR_DF_IRQ     LL_ADC_IsActiveFlag_OVRDF
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVRDF(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_OVR_DF_IRQ) == (ADC_IRQ_STATUS_OVR_DF_IRQ)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the flag OVR_DF.
  * @rmtoll IRQ_STATUS      OVR_DF_IRQ     LL_ADC_ClearFlag_OVRDF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVRDF(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_OVR_DF_IRQ);
}
#endif

/**
  * @brief  Get the status of the flag OVR_DS.
  *         The flag indicates, if set, the Down Sampler output is overran (at least one data is lost).
  * @rmtoll IRQ_STATUS      OVR_DS_IRQ     LL_ADC_IsActiveFlag_OVRDS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVRDS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_OVR_DS_IRQ) == (ADC_IRQ_STATUS_OVR_DS_IRQ)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the flag OVR_DS.
  * @rmtoll IRQ_STATUS      OVR_DS_IRQ     LL_ADC_ClearFlag_OVRDS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVRDS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_OVR_DS_IRQ);
}


/**
  * @brief  Get the status of the flag AWD.
  *         The flag indicates, if set, an event of the watchdog has occured.
  * @rmtoll IRQ_STATUS      AWD_IRQ     LL_ADC_IsActiveFlag_AWD
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_AWD_IRQ) == (ADC_IRQ_STATUS_AWD_IRQ)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the flag AWD.
  * @rmtoll IRQ_STATUS      AWD_IRQ     LL_ADC_ClearFlag_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_AWD_IRQ);
}


/**
  * @brief  Get the status of the flag EOS.
  *         The flag indicates, if set, the End Of a Sequence of conversion.
  * @rmtoll IRQ_STATUS      EOS_IRQ     LL_ADC_IsActiveFlag_EOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EOS_IRQ) == (ADC_IRQ_STATUS_EOS_IRQ)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the flag EOS.
  * @rmtoll IRQ_STATUS      EOS_IRQ     LL_ADC_ClearFlag_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EOS_IRQ);
}

#if defined(ADC_IRQ_STATUS_EODF_IRQ)
/**
  * @brief  Get the status of the flag EODF.
  *         The flag indicates, if set, the End Of a Decimation Filter conversion.
  * @rmtoll IRQ_STATUS      EODF_IRQ     LL_ADC_IsActiveFlag_EODF
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EODF(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EODF_IRQ) == (ADC_IRQ_STATUS_EODF_IRQ)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the flag EODF.
  * @rmtoll IRQ_STATUS      EODF_IRQ     LL_ADC_ClearFlag_EODF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EODF(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EODF_IRQ);
}
#endif

/**
  * @brief  Get the status of the flag EODS.
  *         The flag indicates, if set, the End Of a Down Sampler conversion.
  * @rmtoll IRQ_STATUS      EODS_IRQ     LL_ADC_IsActiveFlag_EODS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EODS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EODS_IRQ) == (ADC_IRQ_STATUS_EODS_IRQ)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the flag EODS.
  * @rmtoll IRQ_STATUS      EODS_IRQ     LL_ADC_ClearFlag_EODS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EODS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EODS_IRQ);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_IT_Management ADC IT management
  * @{
  */

/**
  * @brief  Enable the interrupts according to the interrupt mask passed as parameter.
  * @param  ADCx ADC instance
  * @param  IrqMask This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IRQ_EN_OVRFL
  *         @arg @ref LL_ADC_IRQ_EN_OVRDS
  *         @arg @ref LL_ADC_IRQ_EN_AWD
  *         @arg @ref LL_ADC_IRQ_EN_EOS
  *         @arg @ref LL_ADC_IRQ_EN_EODF
  *         @arg @ref LL_ADC_IRQ_EN_EODS
  * @retval None.
  */
__STATIC_INLINE void LL_ADC_EnableIT(ADC_TypeDef *ADCx, uint32_t IrqMask)
{
  SET_BIT(ADCx->IRQ_ENABLE, IrqMask);
}


/**
  * @brief  Disable the interrupts according to the interrupt mask passed as parameter.
  * @param  ADCx ADC instance
  * @param  IrqMask This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IRQ_EN_OVRFL
  *         @arg @ref LL_ADC_IRQ_EN_OVRDS
  *         @arg @ref LL_ADC_IRQ_EN_AWD
  *         @arg @ref LL_ADC_IRQ_EN_EOS
  *         @arg @ref LL_ADC_IRQ_EN_EODF
  *         @arg @ref LL_ADC_IRQ_EN_EODS
  * @retval None.
  */
__STATIC_INLINE void LL_ADC_DisableIT(ADC_TypeDef *ADCx, uint32_t IrqMask)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, IrqMask);
}


/**
  * @brief  Get if the specific flag is enabled or not.
  * @param  ADCx ADC instance
  * @param  FlagsMask This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRFL
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDF
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDS
  *         @arg @ref LL_ADC_IRQ_FLAG_AWD
  *         @arg @ref LL_ADC_IRQ_FLAG_EOS
  *         @arg @ref LL_ADC_IRQ_FLAG_EODF
  *         @arg @ref LL_ADC_IRQ_FLAG_EODS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT(ADC_TypeDef *ADCx, uint32_t Flag)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, Flag) == (Flag)) ? 1UL : 0UL);
}

#if defined(ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA)
/**
  * @brief  Enable the Decimation Filter saturated interrupt.
  * @rmtoll IRQ_ENABLE     DF_OVRFL_IRQ_ENA     LL_ADC_EnableIT_DFOVRFL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_DFOVRFL(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA);
}


/**
  * @brief  Disable the Decimation Filter saturated interrupt.
  * @rmtoll IRQ_ENABLE     DF_OVRFL_IRQ_ENA     LL_ADC_DisableIT_DFOVRFL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_DFOVRFL(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA);
}

/**
  * @brief  Check if the Decimation Filter saturated interrupt is enabled.
  * @rmtoll IRQ_ENABLE     DF_OVRFL_IRQ_ENA     LL_ADC_IsEnabledIT_DFOVRFL
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_DFOVRFL(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA) == (ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA)) ? 1UL : 0UL);
}
#endif

#if defined(ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA)
/**
  * @brief  Enable the Decimation Filter overrun interrupt.
  * @rmtoll IRQ_ENABLE     OVR_DF_IRQ_ENA     LL_ADC_EnableIT_DFOVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_DFOVR(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA);
}


/**
  * @brief  Disable the Decimation Filter overrun interrupt.
  * @rmtoll IRQ_ENABLE     OVR_DF_IRQ_ENA     LL_ADC_DisableIT_DFOVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_DFOVR(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA);
}


/**
  * @brief  Check if the Decimation Filter overrun interrupt is enabled.
  * @rmtoll IRQ_ENABLE     OVR_DF_IRQ_ENA     LL_ADC_IsEnabledIT_DFOVR
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_DFOVR(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA) == (ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA)) ? 1UL : 0UL);
}
#endif

/**
  * @brief  Enable the Down Sampler overrun interrupt.
  * @rmtoll IRQ_ENABLE     OVR_DS_IRQ_ENA     LL_ADC_EnableIT_DSOVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_DSOVR(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA);
}


/**
  * @brief  Disable the Down Sampler overrun interrupt.
  * @rmtoll IRQ_ENABLE     OVR_DS_IRQ_ENA     LL_ADC_DisableIT_DSOVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_DSOVR(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA);
}


/**
  * @brief  Check if the Down Sampler overrun interrupt is enabled.
  * @rmtoll IRQ_ENABLE     OVR_DS_IRQ_ENA     LL_ADC_IsEnabledIT_DSOVR
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_DSOVR(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA) == (ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA)) ? 1UL : 0UL);
}


/**
  * @brief  Enable the watchdog event interrupt.
  * @rmtoll IRQ_ENABLE     AWD_IRQ_ENA     LL_ADC_EnableIT_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_AWD_IRQ_ENA);
}


/**
  * @brief  Disable the watchdog event interrupt.
  * @rmtoll IRQ_ENABLE     AWD_IRQ_ENA     LL_ADC_DisableIT_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_AWD_IRQ_ENA);
}


/**
  * @brief  Check if the watchdog event interrupt is enabled.
  * @rmtoll IRQ_ENABLE     AWD_IRQ_ENA     LL_ADC_IsEnabledIT_AWD
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_AWD_IRQ_ENA) == (ADC_IRQ_ENABLE_AWD_IRQ_ENA)) ? 1UL : 0UL);
}


/**
  * @brief  Enable the End Of a Sequence of conversion interrupt.
  * @rmtoll IRQ_ENABLE     EOS_IRQ_ENA     LL_ADC_EnableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOS_IRQ_ENA);
}


/**
  * @brief  Disable the End Of a Sequence of conversion interrupt.
  * @rmtoll IRQ_ENABLE     EOS_IRQ_ENA     LL_ADC_DisableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOS_IRQ_ENA);
}


/**
  * @brief  Check if the End Of a Sequence of conversion interrupt is enabled.
  * @rmtoll IRQ_ENABLE     EOS_IRQ_ENA     LL_ADC_IsEnabledIT_EOS
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOS_IRQ_ENA) == (ADC_IRQ_ENABLE_EOS_IRQ_ENA)) ? 1UL : 0UL);
}

#if defined(ADC_IRQ_ENABLE_EODF_IRQ_ENA)
/**
  * @brief  Enable the End Of a Decimation Filter conversion interrupt.
  * @rmtoll IRQ_ENABLE     EODF_IRQ_ENA     LL_ADC_EnableIT_EODF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EODF(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODF_IRQ_ENA);
}


/**
  * @brief  Disable the End Of a Decimation Filter conversion interrupt.
  * @rmtoll IRQ_ENABLE     EODF_IRQ_ENA     LL_ADC_DisableIT_EODF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EODF(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODF_IRQ_ENA);
}


/**
  * @brief  Check if the End Of a Decimation Filter conversion interrupt is enabled.
  * @rmtoll IRQ_ENABLE     EODF_IRQ_ENA     LL_ADC_IsEnabledIT_EODF
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EODF(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODF_IRQ_ENA) == (ADC_IRQ_ENABLE_EODF_IRQ_ENA)) ? 1UL : 0UL);
}
#endif

/**
  * @brief  Enable the End Of a Down Sampler conversion interrupt.
  * @rmtoll IRQ_ENABLE     EODS_IRQ_ENA     LL_ADC_EnableIT_EODS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EODS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODS_IRQ_ENA);
}


/**
  * @brief  Disable the End Of a Down Sampler conversion interrupt.
  * @rmtoll IRQ_ENABLE     EODS_IRQ_ENA     LL_ADC_DisableIT_EODS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EODS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODS_IRQ_ENA);
}


/**
  * @brief  Check if the End Of a Down Sampler conversion interrupt is enabled.
  * @rmtoll IRQ_ENABLE     EODS_IRQ_ENA     LL_ADC_IsEnabledIT_EODS
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EODS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODS_IRQ_ENA) == (ADC_IRQ_ENABLE_EODS_IRQ_ENA)) ? 1UL : 0UL);
}


/**
  * @}
  */


/** @defgroup ADC_LL_EF_Delay_Setting ADC Dealy Setting
  * @{
  */

#if defined(ADC_TIMER_CONF_VBIAS_PRECH_DELAY)
/**
  * @brief  Set the duration of a waiting time starting at rising edge of
  *         PGA_EN signal and corresponding to the VBIAS precharge duration.
  *         The time unit is 4 us. Max delay is 1.02 ms, default value is 128 us.
  * @note   The minimum recommended value for this bitfield is 0.96 to have 600 us.
  * @rmtoll TIMER_CONF     VBIAS_PRECH_DELAY       LL_ADC_SetVbiasPrechargeDelay
  * @param  ADCx ADC instance
  * @param  Delay This parameter is a 8-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVbiasPrechargeDelay(ADC_TypeDef *ADCx, uint32_t Delay)
{
  MODIFY_REG(ADCx->TIMER_CONF, ADC_TIMER_CONF_VBIAS_PRECH_DELAY, Delay);
}


/**
  * @brief  Get the duration of a waiting time starting at rising edge of
  *         PGA_EN signal and corresponding to the VBIAS precharge duration.
  *         The time unit is 4 us. Max delay is 1.02 ms, default value is 128 us.
  * @note   The minimum recommended value for this bitfield is 0.96 to have 600 us.
  * @rmtoll TIMER_CONF     VBIAS_PRECH_DELAY       LL_ADC_GetVbiasPrechargeDelay
  * @param  ADCx ADC instance
  * @retval Returned value is a 8-bit value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetVbiasPrechargeDelay(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->TIMER_CONF, ADC_TIMER_CONF_VBIAS_PRECH_DELAY));
}
#endif

#if defined (ADC_TIMER_CONF_ADC_LDO_DELAY)
/**
  * @brief  Set the duration of the waiting time between the ADC_LDO enable and
  *         the ADC_ON, to let time to the LDO to stabilize itself before
  *         starting a conversion
  *         The time unit is 4 us. Max delay is 1.02 ms, default value is 160 us.
  * @rmtoll TIMER_CONF     ADC_LDO_DELAY       LL_ADC_SetADCLDODelay
  * @param  ADCx ADC instance
  * @param  Delay This parameter is a 8-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetADCLDODelay(ADC_TypeDef *ADCx, uint32_t Delay)
{
  MODIFY_REG(ADCx->TIMER_CONF, ADC_TIMER_CONF_ADC_LDO_DELAY, Delay);
}


/**
  * @brief  Get the duration of the waiting time between the ADC_LDO enable and
  *         the ADC_ON, to let time to the LDO to stabilize itself before
  *         starting a conversion
  *         The time unit is 4 us. Max delay is 1.02 ms, default value is 160 us.
  * @rmtoll TIMER_CONF     ADC_LDO_DELAY       LL_ADC_GetADCLDODelay
  * @param  ADCx ADC instance
  * @retval Returned value is a 8-bit value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetADCLDODelay(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->TIMER_CONF, ADC_TIMER_CONF_ADC_LDO_DELAY));
}
#endif


/**
  * @}
  */



/** @defgroup ADC_LL_CALIB_CONVERSION ADC Calibration and Conversion functions
  * @{
  */


/**
  * @brief  Return the calibration value for the gain of
  *         single ended positive input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINPX_3V6(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINPX_3V6) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         single ended positive input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINPX_3V6(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINPX_3V6) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (int8_t)(calibration_offset | 0x80);
    }
  }
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (int8_t)(calibration_offset | 0x100);
    }
  }
  return calibration_offset; /* Positive number */
}

/**
  * @brief  Return the calibration value for the gain of
  *         single ended positive input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINPX_2V4(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINPX_2V4) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         single ended positive input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINPX_2V4(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINPX_2V4) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (int8_t)(calibration_offset | 0x80);
}
  }
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (int8_t)(calibration_offset | 0x100);
    }
  }
  return calibration_offset; /* Positive number */
}


/**
  * @brief  Return the calibration value for the gain of
  *         single ended positive input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINPX_1V2(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINPX_1V2) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         single ended positive input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINPX_1V2(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINPX_1V2) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (int8_t)(calibration_offset | 0x80);
    }
  }
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (int8_t)(calibration_offset | 0x100);
    }
  }
  return calibration_offset; /* Positive number */
}




/**
  * @brief  Return the calibration value for the gain of
  *         single ended negative input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINMX_3V6(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINMX_3V6) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         single ended negative input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINMX_3V6(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINMX_3V6) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (1 - (int8_t)(calibration_offset | 0x80));
}
  }
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (1 - (int8_t)(calibration_offset | 0x100));
    }
  }
  return (1 - calibration_offset);
}

/**
  * @brief  Return the calibration value for the gain of
  *         single ended negative input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINMX_2V4(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINMX_2V4) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         single ended negative input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINMX_2V4(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINMX_2V4) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (1 - (int8_t)(calibration_offset | 0x80));
    }
  }
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (1 - (int8_t)(calibration_offset | 0x100));
    }
  }
  return (1 - calibration_offset);
}


/**
  * @brief  Return the calibration value for the gain of
  *         single ended negative input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINMX_1V2(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINMX_1V2) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         single ended negative input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINMX_1V2(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINMX_1V2) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (1 - (int8_t)(calibration_offset | 0x80));
    }
  }
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (1 - (int8_t)(calibration_offset | 0x100));
    }
  }
  return (1 - calibration_offset);
}



/**
  * @brief  Return the calibration value for the gain of
  *         differential input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINDIFF_3V6(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINDIFF_3V6) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         differential input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINDIFF_3V6(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINDIFF_3V6) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (int8_t)(calibration_offset | 0x80);
    }
  }
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (int8_t)(calibration_offset | 0x100);
    }
  }
  return calibration_offset; /* Positive number */
}

/**
  * @brief  Return the calibration value for the gain of
  *         differential input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINDIFF_2V4(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINDIFF_2V4) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         differential input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINDIFF_2V4(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINDIFF_2V4) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (int8_t)(calibration_offset | 0x80);
    }
  }
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (int8_t)(calibration_offset | 0x100);
    }
  }
  return calibration_offset; /* Positive number */
}


/**
  * @brief  Return the calibration value for the gain of
  *         differential input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINDIFF_1V2(void)
{
  return (uint16_t)((*(uint32_t*)ADC_CALIB_ADDRESS_VINDIFF_1V2) & 0xFFF);
}


/**
  * @brief  Return the calibration value for the offset of 
  *         differential input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINDIFF_1V2(void)
{
  int8_t calibration_offset = ( (*(uint32_t*)ADC_CALIB_ADDRESS_VINDIFF_1V2) >> 12);
  if( *(uint32_t*)ADC_LAYOUT_ID == 0) { /* Memory version 1 */
    if((calibration_offset & 0x40) == 0x40) { /* Negative number */
      return (int8_t)(calibration_offset | 0x80);
    }
  }  
  else { /* Memory version 2 */
    if((calibration_offset & 0x80) == 0x80) { /* Negative number */
      return (int8_t)(calibration_offset | 0x100);
    }
  }
  return calibration_offset; /* Positive number */
}


/**
  * @brief  Apply the conversion formula for single ended converted data.
  *         (Preliminary formula to be confirmed).
  * @param  ADCx ADC instance
  * @param  RawValue Output value from register DATAOUT
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @param  Width This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval Returned value is an unsigned 32-bit value.
  */
#ifndef BLE_ADC_OUTPUT_FLOAT
__STATIC_INLINE uint32_t LL_ADC_GetADCConvertedValueSingle(ADC_TypeDef *ADCx, uint16_t RawValue, uint32_t Range, uint32_t Width, int8_t offset)
{
  if(Range == LL_ADC_VIN_RANGE_1V2) {
//    return ((( ((uint32_t)RawValue) * 1250) / (4096 * (1<<Width) - 1)) + (offset * 1250) / 4096);
    return ((((((uint32_t)RawValue) * 1250) + (4096 * (1<<Width) - 1)/2) /(4096 * (1<<Width) - 1))  + ((offset * 1250) + 2048) / 4096);
  }
  else {
//    return ((( ((uint32_t)RawValue) * 1200 * Range) / (4096 * (1<<Width) - 1)) + (offset * 1200 * Range) / 4096);
    return ((((((uint32_t)RawValue) * 1200 * Range) + (4096 * (1<<Width) - 1)/2) /(4096 * (1<<Width) - 1))  + ((offset * 1200 * Range) + 2048) / 4096);
  }
}
#else
__STATIC_INLINE float LL_ADC_GetADCConvertedValueSingle(ADC_TypeDef *ADCx, uint16_t RawValue, uint32_t Range, uint32_t Width, int8_t offset)
{
  if(Range == LL_ADC_VIN_RANGE_1V2) {
    return ((( ((float)RawValue) * 1250) / (4096.0 * (1<<Width) - 1) ) + (((float)offset * 1250 ) / 4096.0) );
  }
  else {
    return ((( ((float)RawValue) * 1200 * Range) / (4096.0 * (1<<Width) - 1) ) + (((float)offset * 1200 * Range) / 4096.0) );
  }
}
#endif

/**
  * @brief  Apply the conversion formula for differential converted data.
  *         (Preliminary formula to be confirmed).
  * @param  ADCx ADC instance
  * @param  RawValue Output value from register DATAOUT
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @param  Width This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval Returned value is a signed 32-bit value.
  */
#ifndef BLE_ADC_OUTPUT_FLOAT
__STATIC_INLINE int32_t LL_ADC_GetADCConvertedValueDiff(ADC_TypeDef *ADCx, uint16_t RawValue, uint32_t Range, uint32_t Width, int8_t offset)
{
  if(Range == LL_ADC_VIN_RANGE_1V2) {
//    return (int32_t)((    ((int32_t)RawValue * 4096 / (4096 * (1<<Width) - 1))     +offset - 2048) * 1250) / 2048;
    return (int32_t)((((((((int32_t)RawValue * 4096) + (4096 * (1<<Width) - 1)/2) / (4096 * (1<<Width) - 1)) + offset - 2048) * 1250) + 1024) / 2048);
  }
  else {
//    return (int32_t)(( ((int32_t)RawValue * 4096 / (4096 * (1<<Width) - 1))  +offset - 2048) * 1200 * Range) / 2048;
    return (int32_t)((((((((int32_t)RawValue * 4096) + (4096 * (1<<Width) - 1)/2) / (4096 * (1<<Width) - 1)) + offset - 2048) * 1200 * Range) + 1024) / 2048);
  }
}
#else
__STATIC_INLINE float LL_ADC_GetADCConvertedValueDiff(ADC_TypeDef *ADCx, uint16_t RawValue, uint32_t Range, uint32_t Width, int8_t offset)
{
  if(Range == LL_ADC_VIN_RANGE_1V2) {
    return (float)((( ( ( ((float)RawValue) * 4096 / (4096.0 * (1<<Width) - 1) ) - 2048) +  offset )  * 1250) / 2048.0);
  }
  else {
    return (float)((( ( ( ((float)RawValue) * 4096 / (4096.0 * (1<<Width) - 1) ) - 2048) +  offset )  * 1200 * Range) / 2048.0);
  }
}
#endif


/**
  * @brief  Apply the conversion formula for ADC raw value.
  *         (Preliminary formula to be confirmed).
  * @param  ADCx ADC instance
  * @param  RawValue Output value from register DATAOUT
  * @param  Width This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval Returned value is an unsigned 32-bit value.
  */
#ifndef BLE_ADC_OUTPUT_FLOAT
__STATIC_INLINE uint32_t LL_ADC_GetADCConvertedValueBatt(ADC_TypeDef *ADCx, uint16_t RawValue, uint32_t Width, int8_t offset)
{
//  return ((((uint32_t)RawValue * 3600) / (4096 * (1<<Width) - 1)) + (offset * 3600) / 4096);
  return (((((uint32_t)RawValue * 3600) + (4096 * (1<<Width) - 1)/2) / (4096 * (1<<Width) - 1) ) + ((offset * 3600) + 2048)/ 4096);
}
#else
__STATIC_INLINE float LL_ADC_GetADCConvertedValueBatt(ADC_TypeDef *ADCx, uint16_t RawValue, uint32_t Width, int8_t offset)
{
  return ((( ((float)RawValue) * 3600) / (4096.0 * (1<<Width) - 1)) + (offset * 3600) / 4096.0 );
}
#endif

/**
  * @brief  Apply the conversion formula for temperature raw value.
  *         (Preliminary formula to be confirmed).
  * @param  ADCx ADC instance
  * @param  RawValue Output value from register DATAOUT
  * @param  Width This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval Returned value is a signed 32-bit value representing the temperaure value in Celsius degree.
  */
#ifndef BLE_ADC_OUTPUT_FLOAT

__STATIC_INLINE int32_t LL_ADC_GetADCConvertedValueTemp(ADC_TypeDef *ADCx, uint16_t RawValue, uint32_t Width)
{
  int32_t c30_value = *(uint32_t*)0x10001E60;
  int32_t c85_value = *(uint32_t*)0x10001E68;
  
    if( !((c30_value == 0xFFFFFFFF) || (c85_value == 0xFFFFFFFF)) ) {
//    return (int32_t)( (55 * ((int32_t)RawValue * 4096 / (4096 * (1<<Width) - 1) - c30_value) * 100) /(c85_value-c30_value) + 3000);
      return (int32_t)( ((55 * ( (((int32_t)RawValue * 4096) + (4096 * (1<<Width) - 1)/2) / (4096 * (1<<Width) - 1) - c30_value) * 100) +(c85_value-c30_value)/2) / (c85_value-c30_value) + 3000);
  }
  
//  return ((((( ((1200 * (int32_t)RawValue)/(4096 * (1<<Width) - 1))- 686)* 10000) ) /256) ); /* Obsolete */
  return ((((( (  ((1200 * (int32_t)RawValue)+(4096 * (1<<Width) - 1)/2) / (4096 * (1<<Width) - 1)  )- 686)* 10000) ) /128)/256 ); /* Obsolete */
}
  

#else /* BLE_ADC_OUTPUT_FLOAT defined */

__STATIC_INLINE float LL_ADC_GetADCConvertedValueTemp(ADC_TypeDef *ADCx, uint16_t RawValue, uint32_t Width)
{
  int32_t c30_value = *(uint32_t*)0x10001E60;
  int32_t c85_value = *(uint32_t*)0x10001E68;
  
   if( !((c30_value == 0xFFFFFFFF) || (c85_value == 0xFFFFFFFF)) ) {
      c30_value = c30_value;
      c85_value = c85_value;
    return (float)( (55 * ( ((float)RawValue * 4096 / (4096.0 * (1<<Width) - 1)) - c30_value) * 100) /(c85_value-c30_value) + 3000);
  }
  
  return ((((( ((1200 * (float)RawValue)/ (4096.0 * (1<<Width) - 1) )- 686)* 10000) ) /256) ); /* Obsolete */
}

#endif

/**
  * @}
  */


#if defined(USE_FULL_LL_DRIVER)
/** @defgroup ADC_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

/* De-initialization of ADC instance, ADC group regular and ADC group injected */
/* (availability of ADC group injected depends on BlueNRG_LP families) */
ErrorStatus LL_ADC_DeInit(ADC_TypeDef *ADCx);

/* Initialization of some features of ADC instance */
ErrorStatus LL_ADC_ConfigureVoltageRange(ADC_TypeDef *ADCx, LL_ADC_InitVoltRange *ADC_InitStructVoltRange);
void LL_ADC_GetVoltageRange(ADC_TypeDef *ADCx, LL_ADC_InitVoltRange *ADC_InitStructVoltRange);

ErrorStatus LL_ADC_ConfigureChannelsForSequence(ADC_TypeDef *ADCx, LL_ADC_InitChannelsForSeq *ADC_InitChannelsForSeq);
void LL_ADC_GetChannelsForSequence(ADC_TypeDef *ADCx, LL_ADC_InitChannelsForSeq *ADC_InitChannelsForSeq);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

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

#ifdef __cplusplus
}
#endif

#endif /* RF_DRIVER_LL_ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
