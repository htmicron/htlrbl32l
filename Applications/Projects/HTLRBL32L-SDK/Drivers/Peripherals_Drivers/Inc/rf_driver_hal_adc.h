/**
  ******************************************************************************
  * @file    rf_driver_hal_adc.h
  * @author  RF Application Team
  * @brief   Header file of ADC HAL module.
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
#ifndef RF_DRIVER_HAL_ADC_H
#define RF_DRIVER_HAL_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_hal_def.h"

/* Include low level driver */
#include "rf_driver_ll_adc.h"

/** @addtogroup RF_DRIVER_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADC_Exported_Types ADC Exported Types
  * @{
  */

/**
  * @brief  Structure definition for the configuration of the ADC watchdog.
  */
typedef struct
{
  uint32_t LowThreshold;              /*!< Set the lower threshold for the watchdog.
                                           This parameter is a 12-bit value.  */

  uint32_t HighThreshold;             /*!< Set the higher threshold for the watchdog.
                                           This parameter is a 12-bit value.  */

  uint32_t ChannelMask;               /*!< Select the input channels the watchdog has to use.
                                           This parameter can be a value of @ref ADC_WDG_CHANNEL.  */

  uint32_t EventType;                 /*!< Select the event type used for the watchdog.
                                           This parameter can be a value of @ref ADC_WDG_EVENTTYPE.  */

} ADC_ConfigWatchdogTypeDef;



/**
  * @brief  Structure definition for the configuration of the ADC watchdog.
  */
typedef struct
{
  uint8_t ChannelType;                /*!< Specify the channel type the channel number code for the 1st conversion of the sequence.
                                           This parameter can be a value of @ref ADC_HAL_CH_NUM_CODE. */

  uint8_t SequenceNumber;             /*!< Assign a specific sequence number to the channel.
                                           This parameter can be a value of @ref ADC_HAL_SEQUENCE_POSITION. */

  uint8_t VoltRange;                  /*!< Specify the voltage range for the selected channel.
                                           This parameter can be a value of @ref ADC_HAL_INPUT_VOLTAGE_RANGE. */

} ADC_ConfigChannelTypeDef;



// /**
//   * @brief Structure definition with the setting for the Decimation Filter (DF).
//   */
// typedef struct
// {
//   uint32_t    DynamicMode;            /*!< Specify the input dynamic range for the Decimation Filter (DF).
//                                            This parameter can be a value of @ref ADC_HAL_DF_DYN_RANGE. */

//   uint32_t    HighPassFilterEnable;   /*!< Specify the voltage range for the selected channel.
//                                            This parameter can be a value of @ref ADC_HAL_INPUT_VOLTAGE_RANGE. */

//   uint32_t    OutputDataFormatMode;   /*!< Specify the signed/unsigned output data format.
//                                            This parameter can be a value of @ref ADC_HAL_DATA_FORMAT. */

//   uint32_t    InputDataFormatMode;    /*!< Specify the signed/unsigned input data format.
//                                            This parameter can be a value of @ref ADC_HAL_DATA_FORMAT. */

//   uint32_t    FractionalInterpolator; /*!< Specify the voltage range for the selected channel.
//                                            This parameter can be a value of @ref ADC_HAL_INPUT_VOLTAGE_RANGE. */

//   uint32_t    CicFilterFactor;        /*!< Specify the decimator factor of the CIC filter.
//                                            This parameter can be a value of @ref ADC_HAL_CIC_DECIMATOR_FACTOR. */


// } ADC_ConfigDFTypeDef;



// /**
//   * @brief Structure definition with the setting for the Down Sampler (DS).
//   */
// typedef struct
// {
//   uint32_t    DataWidth;              /*!< Specify the width of the output data from the Down Sampler (DS).
//                                            This parameter can be a value of @ref ADC_HAL_DS_DATA_WIDTH. */

//   uint32_t    DataRatio;              /*!< Specify the ratio of the output data from the Down Sampler (DS).
//                                            This parameter can be a value of @ref ADC_HAL_DS_RATIO. */

//   uint32_t    SequenceLength;         /*!< Specify the length of the conversion sequence.
//                                            This parameter can be a value of @ref ADC_HAL_SEQUENCE_LEN. */

// } ADC_ConfigDSTypeDef;



/**
  * @brief Structure definition with common setting for the ADC.
  */
typedef struct
{
  uint32_t    DataRatio;              /*!< Specify the ratio of the output data from the Down Sampler (DS).
                                           This parameter can be a value of @ref ADC_HAL_DS_RATIO. */

  uint32_t    DataWidth;              /*!< Specify the width of the output data from the Down Sampler (DS).
                                           This parameter can be a value of @ref ADC_HAL_DS_DATA_WIDTH. */

  uint32_t    InvertOutputBitMode;    /*!< Specifies the bit to bit inversion (1' complement) for
                                           differential input and/or single negative input.
                                           This parameter can be a value of @ref ADC_HAL_INVERT_OUTIBT.  */

  uint32_t    OverrunMode;            /*!< Specifies the overrung policy applied to the data.
                                           This parameter can be a value of @ref ADC_HAL_OVERRUN_CONFIG. */
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
  uint32_t    SampleRateMsb;          /*!< Specify the ADC sample rate.
                                           This parameter can be a value of @ref ADC_HAL_SAMPLE_RATE_MSB. */
#endif
  uint32_t    SampleRate;             /*!< Specify the ADC sample rate.
                                           This parameter can be a value of @ref ADC_HAL_SAMPLE_RATE. */

  uint32_t    SamplingMode;           /*!< Specifies the input sampling mode.
                                           This parameter can be a value of @ref ADC_HAL_SAMPLING_METHOD. */
  
  uint32_t    SequenceLength;         /*!< Specify the length of the conversion sequence.
                                           This parameter can be a value of @ref ADC_HAL_SEQUENCE_LEN. */

  // uint32_t    ConversionType;      /*!< Specifies the conversion type: through the Down Sampler (DS) or
  //                                          through the Decimation Filter (DF).
  //                                          This parameter can be a value of @ref ADC_HAL_CONVERSION_TYPE. */

} ADC_InitTypeDef;



/**
  * @brief  ADC handle Structure definition
  */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
typedef struct __ADC_HandleTypeDef
#else
typedef struct
#endif
{
  ADC_TypeDef        *Instance;    /*!< Register base address */
  ADC_InitTypeDef    Init;        /*!< Parameters for ADC initialization */

  DMA_HandleTypeDef  *DMA_Handle;  /*!< Pointer DMA Handler */

  HAL_LockTypeDef    Lock;         /*!< ADC locking object */
  __IO uint32_t      State;        /*!< ADC communication state (bitmap of ADC states) */
  __IO uint32_t      ErrorCode;    /*!< ADC Error code */

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  void (* ConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);        /*!< ADC conversion complete callback */
  void (* ConvHalfCpltCallback)(struct __ADC_HandleTypeDef *hadc);    /*!< ADC conversion DMA half-transfer callback */
  void (* WatchdogAlertCallback)(struct __ADC_HandleTypeDef *hadc);   /*!< ADC analog watchdog 1 callback */
  void (* ErrorCallback)(struct __ADC_HandleTypeDef *hadc);           /*!< ADC error callback */
  void (* MspInitCallback)(struct __ADC_HandleTypeDef *hadc);         /*!< ADC Msp Init callback */
  void (* MspDeInitCallback)(struct __ADC_HandleTypeDef *hadc);       /*!< ADC Msp DeInit callback */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

} ADC_HandleTypeDef;



#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL ADC Callback ID enumeration definition
  */
typedef enum
{
  HAL_ADC_CONVERSION_COMPLETE_CB_ID     = 0x00U,  /*!< ADC conversion complete callback ID          */
  HAL_ADC_CONVERSION_HALF_CB_ID         = 0x01U,  /*!< ADC conversion DMA half-transfer callback ID */
  HAL_ADC_WATCHDOG_ALERT_CB_ID          = 0x02U,  /*!< ADC watchdog callback ID                 */
  HAL_ADC_ERROR_CB_ID                   = 0x03U,  /*!< ADC error callback ID                        */
  HAL_ADC_MSPINIT_CB_ID                 = 0x09U,  /*!< ADC Msp Init callback ID                     */
  HAL_ADC_MSPDEINIT_CB_ID               = 0x0AU   /*!< ADC Msp DeInit callback ID                   */
} HAL_ADC_CallbackIDTypeDef;

/**
  * @brief  HAL ADC Callback pointer definition
  */
typedef  void (*pADC_CallbackTypeDef)(ADC_HandleTypeDef *hadc); /*!< pointer to a ADC callback function */

#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_States ADC States
  * @{
  */

/**
  * @brief  HAL ADC state machine: ADC states definition (bitfields)
  * @note   ADC state machine is managed by bitfields, state must be compared
  *         with bit by bit.
  *         For example:                                                         
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATEBUSY) != 0UL) "
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_AWD) != 0UL) "
  */
/* States of ADC global scope */
#define HAL_ADC_STATE_RESET           (0x00000000UL)   /*!< ADC not yet initialized or disabled */
#define HAL_ADC_STATE_READY           (0x00000001UL)   /*!< ADC peripheral ready to use         */
#define HAL_ADC_STATE_BUSY_INTERNAL   (0x00000002UL)   /*!< ADC is busy due to an internal process (initialization, calibration) */
#define HAL_ADC_STATE_TIMEOUT         (0x00000004UL)   /*!< TimeOut occurrence                  */

/* States of ADC errors */
#define HAL_ADC_STATE_ERROR_INTERNAL  (0x00000010UL)   /*!< Internal error occurrence      */
#define HAL_ADC_STATE_ERROR_CONFIG    (0x00000020UL)   /*!< Configuration error occurrence */
#define HAL_ADC_STATE_ERROR_DMA       (0x00000040UL)   /*!< DMA error occurrence           */

/* States of ADC conversion */
#define HAL_ADC_STATE_BUSY            (0x00000100UL)   /*!< A conversion is ongoing or can occur */
#define HAL_ADC_STATE_EOC             (0x00000200UL)   /*!< Converted data available             */
#define HAL_ADC_STATE_OVR             (0x00000400UL)   /*!< Overrun occurrence                   */

/* States of ADC analog watchdog */
#define HAL_ADC_STATE_AWD             (0x00010000UL)   /*!< Out-of-window occurrence of ADC analog watchdog */

/**
  * @}
  */


/** @defgroup ADC_Error_Code ADC Error Code
  * @{
  */

#define HAL_ADC_ERROR_NONE            (0x00U)   /*!< No error               */
#define HAL_ADC_ERROR_INTERNAL        (0x01U)   /*!< Internal error         */
#define HAL_ADC_ERROR_OVR             (0x02U)   /*!< Data overrun error     */
#define HAL_ADC_ERROR_DMA             (0x04U)   /*!< DMA transfer error     */

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define HAL_ADC_ERROR_INVALID_CALLBACK  (0x10U) /*!< Invalid Callback error */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */


/** @defgroup ADC_HAL_CH_NUM_CODE ADC channel number code for conversion definitions
  * @{
  */

#define ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT  (LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT)  /*!< ADC channel number code for the conversion is VINM0 to single negative input */
#define ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT  (LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT)  /*!< ADC channel number code for the conversion is VINM1 to single negative input */
#define ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT  (LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT)  /*!< ADC channel number code for the conversion is VINM2 to single negative input */
#define ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT  (LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT)  /*!< ADC channel number code for the conversion is VINM3 to single negative input */
#define ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT  (LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT)  /*!< ADC channel number code for the conversion is VINP0 to single positive input */
#define ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT  (LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT)  /*!< ADC channel number code for the conversion is VINP1 to single positive input */
#define ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT  (LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT)  /*!< ADC channel number code for the conversion is VINP2 to single positive input */
#define ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT  (LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT)  /*!< ADC channel number code for the conversion is VINP3 to single positive input */
#define ADC_CH_VINP0_VINM0_TO_DIFF_INPUT       (LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT)       /*!< ADC channel number code for the conversion is VINP0 - VINM0 to differential input */
#define ADC_CH_VINP1_VINM1_TO_DIFF_INPUT       (LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT)       /*!< ADC channel number code for the conversion is VINP1 - VINM1 to differential input */
#define ADC_CH_VINP2_VINM2_TO_DIFF_INPUT       (LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT)       /*!< ADC channel number code for the conversion is VINP2 - VINM2 to differential input */
#define ADC_CH_VINP3_VINM3_TO_DIFF_INPUT       (LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT)       /*!< ADC channel number code for the conversion is VINP3 - VINM3 to differential input */
#define ADC_CH_BATTERY_LEVEL_DETECTOR          (LL_ADC_CH_BATTERY_LEVEL_DETECTOR)          /*!< ADC channel number code for the conversion is VBAT, battery level detector        */
#define ADC_CH_TEMPERATURE_SENSOR              (LL_ADC_CH_TEMPERATURE_SENSOR)              /*!< ADC channel number code for the conversion is temperature sensor                  */

/**
  * @}
  */



// REMOVE THE DEFINITIONS NOT NECESSARY TO THE API OF THE HAL DRIVER

/** @defgroup ADC_HAL_SAMPLING_METHOD  ADC input sampling method definitions
  * @{
  */

#define ADC_SAMPLING_AT_START    (LL_ADC_SAMPLING_AT_START)  /*!< Sampling only at conversion start (default) */
#define ADC_SAMPLING_AT_END      (LL_ADC_SAMPLING_AT_END)    /*!< Sampling starts at the end of conversion   */

/**
  * @}
  */


/** @defgroup ADC_HAL_OVERRUN_CONFIG ADC overrun configuration definitions
  * @{
  */

#define ADC_NEW_DATA_IS_LOST    (LL_ADC_NEW_DATA_IS_LOST)    /*!< The previous data is lost, the new one is kept */
#define ADC_NEW_DATA_IS_KEPT    (LL_ADC_NEW_DATA_IS_KEPT)    /*!< The previous data is kept, the new one is lost */

/**
  * @}
  */


/** @defgroup ADC_HAL_INVERT_OUTIBT ADC invert bit to bit data output for differential or
  *           single negative input (1' complement) definitions
  * @{
  */

#define ADC_INVERT_OUTBIT_NONE  (0x00U)    /*!< No inversion                             */
#define ADC_INVERT_OUTBIT_DIFF  (0x01U)    /*!< Inversion only for differential input    */
#define ADC_INVERT_OUTBIT_SING  (0x02U)    /*!< Inversion only for single negative input */
#define ADC_INVERT_OUTBIT_BOTH  (0x03U)    /*!< Inversion for both input type            */

/**
  * @}
  */


/** @defgroup ADC_HAL_CONVERSION_TYPE ADC conversion type definitions
  * @{
  */

#define ADC_CONVERSION_WITH_DS  (0x00U)    /*!< ADC convesion through the Down Sampler (DS)      */
#define ADC_CONVERSION_WITH_DF  (0x01U)    /*!< ADC convesion through the Decimation Filter (DF) */

/**
  * @}
  */


/** @defgroup ADC_HAL_SAMPLE_RATE ADC sample rate definitions
  * @{
  */

#define ADC_SAMPLE_RATE_16    (LL_ADC_SAMPLE_RATE_16)  /*!< ADC conversion rate at System clock / 16 */
#define ADC_SAMPLE_RATE_20    (LL_ADC_SAMPLE_RATE_20)  /*!< ADC conversion rate at System clock / 20 */
#define ADC_SAMPLE_RATE_24    (LL_ADC_SAMPLE_RATE_24)  /*!< ADC conversion rate at System clock / 24 */
#define ADC_SAMPLE_RATE_28    (LL_ADC_SAMPLE_RATE_28)  /*!< ADC conversion rate at System clock / 28 */

/**
  * @}
  */


// /** @defgroup ADC_HAL_OP_MODE ADC operation modes definitions
//   * @{
//   */

// #define ADC_OP_MODE_AUDIO    (LL_ADC_OP_MODE_AUDIO)  /*!< ADC operation mode AUDIO */
// #define ADC_OP_MODE_ADC      (LL_ADC_OP_MODE_ADC)  /*!< ADC operation mode ADC   */
// #define ADC_OP_MODE_FULL     (LL_ADC_OP_MODE_FULL)  /*!< ADC operation Full mode  */

// /**
//   * @}
//   */


/** @defgroup ADC_HAL_SEQUENCE_LEN ADC sequence length definitions
  * @{
  */

#define ADC_SEQ_LEN_01    (LL_ADC_SEQ_LEN_01)  /*!< The sequence is of 1 conversion */
#define ADC_SEQ_LEN_02    (LL_ADC_SEQ_LEN_02)  /*!< The sequence is of 2 conversions */
#define ADC_SEQ_LEN_03    (LL_ADC_SEQ_LEN_03)  /*!< The sequence is of 3 conversions */
#define ADC_SEQ_LEN_04    (LL_ADC_SEQ_LEN_04)  /*!< The sequence is of 4 conversions */
#define ADC_SEQ_LEN_05    (LL_ADC_SEQ_LEN_05)  /*!< The sequence is of 5 conversions */
#define ADC_SEQ_LEN_06    (LL_ADC_SEQ_LEN_06)  /*!< The sequence is of 6 conversions */
#define ADC_SEQ_LEN_07    (LL_ADC_SEQ_LEN_07)  /*!< The sequence is of 7 conversions */
#define ADC_SEQ_LEN_08    (LL_ADC_SEQ_LEN_08)  /*!< The sequence is of 8 conversions */
#define ADC_SEQ_LEN_09    (LL_ADC_SEQ_LEN_09)  /*!< The sequence is of 9 conversions */
#define ADC_SEQ_LEN_10    (LL_ADC_SEQ_LEN_10)  /*!< The sequence is of 10 conversions */
#define ADC_SEQ_LEN_11    (LL_ADC_SEQ_LEN_11)  /*!< The sequence is of 11 conversions */
#define ADC_SEQ_LEN_12    (LL_ADC_SEQ_LEN_12)  /*!< The sequence is of 12 conversions */
#define ADC_SEQ_LEN_13    (LL_ADC_SEQ_LEN_13)  /*!< The sequence is of 13 conversions */
#define ADC_SEQ_LEN_14    (LL_ADC_SEQ_LEN_14)  /*!< The sequence is of 14 conversions */
#define ADC_SEQ_LEN_15    (LL_ADC_SEQ_LEN_15)  /*!< The sequence is of 15 conversions */
#define ADC_SEQ_LEN_16    (LL_ADC_SEQ_LEN_16)  /*!< The sequence is of 16 conversions */

/**
  * @}
  */


/** @defgroup ADC_HAL_SEQUENCE_POSITION ADC sequence position definitions
  * @{
  */

#define ADC_SEQ_POS_01    (0x01U)  /*!< The sequence position 1 */
#define ADC_SEQ_POS_02    (0x02U)  /*!< The sequence position 2 */
#define ADC_SEQ_POS_03    (0x03U)  /*!< The sequence position 3 */
#define ADC_SEQ_POS_04    (0x04U)  /*!< The sequence position 4 */
#define ADC_SEQ_POS_05    (0x05U)  /*!< The sequence position 5 */
#define ADC_SEQ_POS_06    (0x06U)  /*!< The sequence position 6 */
#define ADC_SEQ_POS_07    (0x07U)  /*!< The sequence position 7 */
#define ADC_SEQ_POS_08    (0x08U)  /*!< The sequence position 8 */
#define ADC_SEQ_POS_09    (0x09U)  /*!< The sequence position 9 */
#define ADC_SEQ_POS_10    (0x10U)  /*!< The sequence position 10 */
#define ADC_SEQ_POS_11    (0x11U)  /*!< The sequence position 11 */
#define ADC_SEQ_POS_12    (0x12U)  /*!< The sequence position 12 */
#define ADC_SEQ_POS_13    (0x13U)  /*!< The sequence position 13 */
#define ADC_SEQ_POS_14    (0x14U)  /*!< The sequence position 14 */
#define ADC_SEQ_POS_15    (0x15U)  /*!< The sequence position 15 */
#define ADC_SEQ_POS_16    (0x16U)  /*!< The sequence position 16 */

/**
  * @}
  */


// /** @defgroup ADC_HAL_OCM_SOURCE ADC occasional mode source definitions
//   * @{
//   */

// #define ADC_OCM_SRC_VBAT    (LL_ADC_OCM_SRC_VBAT)  !< ADC occasional mode source VBAT               
// #define ADC_OCM_SRC_TEMP    (LL_ADC_OCM_SRC_TEMP)  /*!< ADC occasional mode source temperature sensor */

// /**
//   * @}
//   */


// /** @defgroup ADC_HAL_PGA_BIAS ADC microphone bias voltage definitions
//   * @{
//   */

// #define ADC_PGA_BIAS_050_BAT   (LL_ADC_PGA_BIAS_050_BAT)                  /*!< Set the microphone bias voltage at 0.50 V */
// #define ADC_PGA_BIAS_055_BAT   (LL_ADC_PGA_BIAS_055_BAT)  /*!< Set the microphone bias voltage at 0.55 V */
// #define ADC_PGA_BIAS_060_BAT   (LL_ADC_PGA_BIAS_060_BAT)  /*!< Set the microphone bias voltage at 0.60 V */
// #define ADC_PGA_BIAS_065_BAT   (LL_ADC_PGA_BIAS_065_BAT)  !< Set the microphone bias voltage at 0.65 V 
// #define ADC_PGA_BIAS_070_BAT   (LL_ADC_PGA_BIAS_070_BAT)  /*!< Set the microphone bias voltage at 0.70 V */
// #define ADC_PGA_BIAS_075_BAT   (LL_ADC_PGA_BIAS_075_BAT)  /*!< Set the microphone bias voltage at 0.75 V */
// #define ADC_PGA_BIAS_080_BAT   (LL_ADC_PGA_BIAS_080_BAT)  /*!< Set the microphone bias voltage at 0.80 V */
// #define ADC_PGA_BIAS_090_BAT   (LL_ADC_PGA_BIAS_090_BAT)  /*!< Set the microphone bias voltage at 0.90 V */

// /**
//   * @}
//   */


// /** @defgroup ADC_HAL_PGA_GAIN ADC microphone gain definitions
//   * @{
//   */

// #define ADC_PGA_GAIN_06_DB   (LL_ADC_PGA_GAIN_06_DB)  /*!< Set the microphone gain at 6 dB  */
// #define ADC_PGA_GAIN_09_DB   (LL_ADC_PGA_GAIN_09_DB)  /*!< Set the microphone gain at 9 dB  */
// #define ADC_PGA_GAIN_12_DB   (LL_ADC_PGA_GAIN_12_DB)  /*!< Set the microphone gain at 12 dB */
// #define ADC_PGA_GAIN_15_DB   (LL_ADC_PGA_GAIN_15_DB)  /*!< Set the microphone gain at 15 dB */
// #define ADC_PGA_GAIN_18_DB   (LL_ADC_PGA_GAIN_18_DB)  !< Set the microphone gain at 18 dB 
// #define ADC_PGA_GAIN_21_DB   (LL_ADC_PGA_GAIN_21_DB)  /*!< Set the microphone gain at 21 dB */
// #define ADC_PGA_GAIN_24_DB   (LL_ADC_PGA_GAIN_24_DB)  /*!< Set the microphone gain at 24 dB */
// #define ADC_PGA_GAIN_27_DB   (LL_ADC_PGA_GAIN_27_DB)  /*!< Set the microphone gain at 27 dB */
// #define ADC_PGA_GAIN_30_DB   (LL_ADC_PGA_GAIN_30_DB)  /*!< Set the microphone gain at 30 dB */
// #define ADC_PGA_GAIN_33_DB   (LL_ADC_PGA_GAIN_33_DB)  /*!< Set the microphone gain at 33 dB */

// /**
//   * @}
//   */


/** @defgroup ADC_HAL_INPUT_VOLTAGE_RANGE ADC input voltage range definitions
  * @{
  */

#define ADC_VIN_RANGE_1V2    (LL_ADC_VIN_RANGE_1V2)  /*!< ADC input voltage range up to 1.2 V */
#define ADC_VIN_RANGE_2V4    (LL_ADC_VIN_RANGE_2V4)  /*!< ADC input voltage range up to 2.4 V */
#define ADC_VIN_RANGE_3V6    (LL_ADC_VIN_RANGE_3V6)  /*!< ADC input voltage range up to 3.6 V */

/**
  * @}
  */


/** @defgroup ADC_HAL_DF_DYN_RANGE ADC Decimation Filter dynamic range definitions
  * @{
  */

#define ADC_DF_DYN_RANGE_FULL    (LL_ADC_DF_DYN_RANGE_FULL)  /*!< ADC Decimation Filter dynamic full range */
#define ADC_DF_DYN_RANGE_HALF    (LL_ADC_DF_DYN_RANGE_HALF)  /*!< ADC Decimation Filter dynamic half range */

/**
  * @}
  */


// /** @defgroup ADC_HAL_MIC_CHANNEL ADC microphone channel definitions
//   * @{
//   */

// #define ADC_DF_MIC_CH_RIGHT    (LL_ADC_DF_MIC_CH_RIGHT)                     /*!< ADC microphone channel right */
// #define ADC_DF_MIC_CH_LEFT     (LL_ADC_DF_MIC_CH_LEFT)  /*!< ADC microphone channel left  */

// /**
//   * @}
//   */


// /** @defgroup ADC_HAL_PDM_CLK_DIVIDER ADC PDM clock divider definitions
//   * @{
//   */

// #define ADC_PDM_DIV_10   (LL_ADC_PDM_DIV_10)                    /*!< ADC PDM clock divider 10 */
// #define ADC_PDM_DIV_11   (LL_ADC_PDM_DIV_11)  /*!< ADC PDM clock divider 11 */
// #define ADC_PDM_DIV_12   (LL_ADC_PDM_DIV_12)  /*!< ADC PDM clock divider 12 */
// #define ADC_PDM_DIV_13   (LL_ADC_PDM_DIV_13)  /*!< ADC PDM clock divider 13 */
// #define ADC_PDM_DIV_14   (LL_ADC_PDM_DIV_14)  /*!< ADC PDM clock divider 14 */
// #define ADC_PDM_DIV_15   (LL_ADC_PDM_DIV_15)  /*!< ADC PDM clock divider 15 */
// #define ADC_PDM_DIV_16   (LL_ADC_PDM_DIV_16)  /*!< ADC PDM clock divider 16 */
// #define ADC_PDM_DIV_17   (LL_ADC_PDM_DIV_17)  /*!< ADC PDM clock divider 17 */
// #define ADC_PDM_DIV_18   (LL_ADC_PDM_DIV_18)  /*!< ADC PDM clock divider 18 */
// #define ADC_PDM_DIV_19   (LL_ADC_PDM_DIV_19)  /*!< ADC PDM clock divider 19 */
// #define ADC_PDM_DIV_20   (LL_ADC_PDM_DIV_20)  /*!< ADC PDM clock divider 20 */
// #define ADC_PDM_DIV_21   (LL_ADC_PDM_DIV_21)  /*!< ADC PDM clock divider 21 */
// #define ADC_PDM_DIV_22   (LL_ADC_PDM_DIV_22)  /*!< ADC PDM clock divider 22 */
// #define ADC_PDM_DIV_23   (LL_ADC_PDM_DIV_23)  /*!< ADC PDM clock divider 23 */
// #define ADC_PDM_DIV_24   (LL_ADC_PDM_DIV_24)  /*!< ADC PDM clock divider 24 */
// #define ADC_PDM_DIV_25   (LL_ADC_PDM_DIV_25)  /*!< ADC PDM clock divider 25 */

// /**
//   * @}
//   */


/** @defgroup ADC_HAL_DATA_FORMAT ADC data format definitions
  * @{
  */

#define ADC_DATA_FRMT_SIGNED    (LL_ADC_DATA_FRMT_SIGNED)    /*!< ADC data format signed   */
#define ADC_DATA_FRMT_UNSIGNED  (LL_ADC_DATA_FRMT_UNSIGNED)  /*!< ADC data format unsigned */

/**
  * @}
  */


/** @defgroup ADC_HAL_CIC_DECIMATOR_FACTOR ADC CIC decimator factor definitions
  * @{
  */

#define ADC_CIC_DECIMATOR_FACTOR_HALF     (LL_ADC_CIC_DECIMATOR_FACTOR_HALF)      /*!< ADC CIC decimator factor half    */
#define ADC_CIC_DECIMATOR_FACTOR_INTEGER  (LL_ADC_CIC_DECIMATOR_FACTOR_INTEGER)   /*!< ADC CIC decimator factor integer */

/**
  * @}
  */


/** @defgroup ADC_HAL_MICROPHONE_OUT_FREQ ADC microphone output frequency definitions
  * @{
  */
//#warning "not sure, ask for confirmation"
#define ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ)  /*!< ADC digital microphone output frequency 47.619 kHz */
#define ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ)  /*!< ADC digital microphone output frequency 44.44  kHz */
#define ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ)  /*!< ADC digital microphone output frequency 22.22  kHz */
#define ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ)  /*!< ADC digital microphone output frequency 15.873 kHz */
#define ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ   (LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ)   /*!< ADC digital microphone output frequency 7.936  kHz */

#define ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ (LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ)  /*!< ADC analog microphone output frequency 200.00 kHz */
#define ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ  (LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ)   /*!< ADC analog microphone output frequency 15.873 kHz */
#define ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ   (LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ)    /*!< ADC analog microphone output frequency 7.936  kHz */

/**
  * @}
  */


/** @defgroup ADC_HAL_DS_DATA_WIDTH ADC Down Sampler data width definitions
  * @{
  */

#define ADC_DS_DATA_WIDTH_12_BIT  (LL_ADC_DS_DATA_WIDTH_12_BIT)  /*!< ADC Down Sampler data width 12 bits */
#define ADC_DS_DATA_WIDTH_13_BIT  (LL_ADC_DS_DATA_WIDTH_13_BIT)  /*!< ADC Down Sampler data width 13 bits */
#define ADC_DS_DATA_WIDTH_14_BIT  (LL_ADC_DS_DATA_WIDTH_14_BIT)  /*!< ADC Down Sampler data width 14 bits */
#define ADC_DS_DATA_WIDTH_15_BIT  (LL_ADC_DS_DATA_WIDTH_15_BIT)  /*!< ADC Down Sampler data width 15 bits */
#define ADC_DS_DATA_WIDTH_16_BIT  (LL_ADC_DS_DATA_WIDTH_16_BIT)  /*!< ADC Down Sampler data width 16 bits */

/**
  * @}
  */


/** @defgroup ADC_HAL_DS_RATIO ADC Down Sampler ratio definitions
  * @{
  */

#define ADC_DS_RATIO_01   (LL_ADC_DS_RATIO_01)      /*!< ADC Down Sampler ratio 1, no down sampling (default) */
#define ADC_DS_RATIO_02   (LL_ADC_DS_RATIO_02)      /*!< ADC Down Sampler ratio 2                             */
#define ADC_DS_RATIO_04   (LL_ADC_DS_RATIO_04)      /*!< ADC Down Sampler ratio 4                             */
#define ADC_DS_RATIO_08   (LL_ADC_DS_RATIO_08)      /*!< ADC Down Sampler ratio 8                             */
#define ADC_DS_RATIO_16   (LL_ADC_DS_RATIO_16)      /*!< ADC Down Sampler ratio 16                            */
#define ADC_DS_RATIO_32   (LL_ADC_DS_RATIO_32)      /*!< ADC Down Sampler ratio 32                            */
#define ADC_DS_RATIO_64   (LL_ADC_DS_RATIO_64)      /*!< ADC Down Sampler ratio 64                            */
#define ADC_DS_RATIO_128  (LL_ADC_DS_RATIO_128)     /*!< ADC Down Sampler ratio 128                           */

/**
  * @}
  */


// /** @defgroup ADC_HAL_CALIB_POINT ADC calibration points definitions
//   * @{
//   */

// #define ADC_CALIB_POINT_1  (LL_ADC_CALIB_POINT_1)  /*!< ADC calibration point 1 */
// #define ADC_CALIB_POINT_2  (LL_ADC_CALIB_POINT_2)  /*!< ADC calibration point 2 */
// #define ADC_CALIB_POINT_3  (LL_ADC_CALIB_POINT_3)  /*!< ADC calibration point 3 */
// #define ADC_CALIB_POINT_4  (LL_ADC_CALIB_POINT_4)  /*!< ADC calibration point 4 */

// /**
//   * @}
//   */


/** @defgroup ADC_WDG_CHANNEL ADC watchdog channel selection for bit mask definitions
  * @brief    It defines the parameters used for the functions LL_ADC_SetWDGInputChannels() and LL_ADC_GetWDGInputChannels()
  * @{
  */

#define ADC_WDG_CH_VINM0_TO_NEG     (LL_ADC_WDG_CH_VINM0_TO_NEG)  /*!< ADC watchdog channel selection: VINM0 to ADC negative input  */
#define ADC_WDG_CH_VINM1_TO_NEG     (LL_ADC_WDG_CH_VINM1_TO_NEG)  /*!< ADC watchdog channel selection: VINM1 to ADC negative input  */
#define ADC_WDG_CH_VINM2_TO_NEG     (LL_ADC_WDG_CH_VINM2_TO_NEG)  /*!< ADC watchdog channel selection: VINM2 to ADC negative input  */
#define ADC_WDG_CH_VINM3_TO_NEG     (LL_ADC_WDG_CH_VINM3_TO_NEG)  /*!< ADC watchdog channel selection: VINM3 to ADC negative input  */
#define ADC_WDG_CH_MICROM_TO_NEG    (LL_ADC_WDG_CH_MICROM_TO_NEG) /*!< ADC watchdog channel selection: MICROM to ADC negative input */
#define ADC_WDG_CH_VBAT_TO_NEG      (LL_ADC_WDG_CH_VBAT_TO_NEG)   /*!< ADC watchdog channel selection: VBAT to ADC negative input   */
#define ADC_WDG_CH_GND_TO_NEG       (LL_ADC_WDG_CH_GND_TO_NEG)    /*!< ADC watchdog channel selection: GND to ADC negative input    */
#define ADC_WDG_CH_VDDA_TO_NEG      (LL_ADC_WDG_CH_VDDA_TO_NEG)   /*!< ADC watchdog channel selection: VDDA to ADC negative input   */
#define ADC_WDG_CH_VINP0_TO_POS     (LL_ADC_WDG_CH_VINP0_TO_POS)  /*!< ADC watchdog channel selection: VINP0 to ADC positive input  */
#define ADC_WDG_CH_VINP1_TO_POS     (LL_ADC_WDG_CH_VINP1_TO_POS)  /*!< ADC watchdog channel selection: VINP1 to ADC positive input  */
#define ADC_WDG_CH_VINP2_TO_POS     (LL_ADC_WDG_CH_VINP2_TO_POS)  /*!< ADC watchdog channel selection: VINP2 to ADC positive input  */
#define ADC_WDG_CH_VINP3_TO_POS     (LL_ADC_WDG_CH_VINP3_TO_POS)  /*!< ADC watchdog channel selection: VINP3 to ADC positive input  */
#define ADC_WDG_CH_MICROP_TO_POS    (LL_ADC_WDG_CH_MICROP_TO_POS) /*!< ADC watchdog channel selection: MICROP to ADC positive input */
#define ADC_WDG_CH_TEMP_TO_POS      (LL_ADC_WDG_CH_TEMP_TO_POS)   /*!< ADC watchdog channel selection: TEMP to ADC positive input   */
#define ADC_WDG_CH_GND_TO_POS       (LL_ADC_WDG_CH_GND_TO_POS)    /*!< ADC watchdog channel selection: GND to ADC positive input    */
#define ADC_WDG_CH_VDDA_TO_POS      (LL_ADC_WDG_CH_VDDA_TO_POS)   /*!< ADC watchdog channel selection: VDDA to ADC positive input   */

/**
  * @}
  */

/** @defgroup ADC_WDG_EVENTTYPE ADC watchdog event type definitions
  * @{
  */

#define ADC_WDG_EVENT_POLLING       (0x00U)  /*!< ADC watchdog event type polling   */
#define ADC_WDG_EVENT_INTERRUPT     (0x01U)  /*!< ADC watchdog event type interrupt */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_STATUS_MASK ADC IRQ_STATUS register mask definitions
  * @{
  */

#define ADC_IRQ_FLAG_OVRFL   (LL_ADC_IRQ_FLAG_OVRFL) /*!< ADC IRQ flag OVRFL */
#define ADC_IRQ_FLAG_OVRDF   (LL_ADC_IRQ_FLAG_OVRDF) /*!< ADC IRQ flag OVRDF */
#define ADC_IRQ_FLAG_OVRDS   (LL_ADC_IRQ_FLAG_OVRDS) /*!< ADC IRQ flag OVRDS */
#define ADC_IRQ_FLAG_AWD     (LL_ADC_IRQ_FLAG_AWD)   /*!< ADC IRQ flag AWD   */
#define ADC_IRQ_FLAG_EOS     (LL_ADC_IRQ_FLAG_EOS)   /*!< ADC IRQ flag EOS   */
#define ADC_IRQ_FLAG_EODF    (LL_ADC_IRQ_FLAG_EODF)  /*!< ADC IRQ flag EODF  */
#define ADC_IRQ_FLAG_EODS    (LL_ADC_IRQ_FLAG_EODS)  /*!< ADC IRQ flag EODS  */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_STATUS_MASK ADC IRQ_STATUS register mask definitions
  * @{
  */
#define ADC_IRQ_FLAGS_MASK      (ADC_IRQ_FLAG_OVRFL | \
                                 ADC_IRQ_FLAG_OVRDF | \
                                 ADC_IRQ_FLAG_OVRDS | \
                                 ADC_IRQ_FLAG_AWD   | \
                                 ADC_IRQ_FLAG_EOS   | \
                                 ADC_IRQ_FLAG_EODF  | \
                                 ADC_IRQ_FLAG_EODS)


/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_ENABLE ADC interrupts enable definitions
  * @{
  */

#define ADC_IRQ_EN_OVRFL   (LL_ADC_IRQ_EN_OVRFL)    /*!< ADC IRQ enable OVRFL */
#define ADC_IRQ_EN_OVRDF   (LL_ADC_IRQ_EN_OVRDF)    /*!< ADC IRQ enable OVRDF */
#define ADC_IRQ_EN_OVRDS   (LL_ADC_IRQ_EN_OVRDS)    /*!< ADC IRQ enable OVRDS */
#define ADC_IRQ_EN_AWD     (LL_ADC_IRQ_EN_AWD)      /*!< ADC IRQ enable AWD   */
#define ADC_IRQ_EN_EOS     (LL_ADC_IRQ_EN_EOS)      /*!< ADC IRQ enable EOS   */
#define ADC_IRQ_EN_EODF    (LL_ADC_IRQ_EN_EODF)     /*!< ADC IRQ enable EODF  */
#define ADC_IRQ_EN_EODS    (LL_ADC_IRQ_EN_EODS)     /*!< ADC IRQ enable EODS  */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_ENABLE_MASK ADC IRQ_ENABLE register mask definitions
  * @{
  */
#define ADC_IRQ_EN_MASK      (ADC_IRQ_EN_OVRFL | \
                              ADC_IRQ_EN_OVRDF | \
                              ADC_IRQ_EN_OVRDS | \
                              ADC_IRQ_EN_AWD   | \
                              ADC_IRQ_EN_EOS   | \
                              ADC_IRQ_EN_EODF  | \
                              ADC_IRQ_EN_EODS)

/**
  * @}
  */


/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/

/** @defgroup ADC_Private_Macros ADC Private Macros
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */


/**
  * @brief Clear ADC error code (set it to no error code "HAL_ADC_ERROR_NONE").
  * @param __HANDLE__ ADC handle
  * @retval None
  */
#define ADC_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE) 

/**
  * @brief Simultaneously clear and set specific bits of the handle State.
  * @note  ADC_STATE_CLR_SET() macro is merely aliased to generic macro MODIFY_REG(),
  *        the first parameter is the ADC handle State, the second parameter is the
  *        bit field to clear, the third and last parameter is the bit field to set.
  * @retval None
  */
#define ADC_STATE_CLR_SET MODIFY_REG



/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/

/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup ADC_Exported_Macros ADC Exported Macros
  * @{
  */

/** @defgroup ADC_HAL_EM_HANDLE_IT_FLAG HAL ADC macro to manage HAL ADC handle, IT and flags.
  * @{
  */

/** @brief  Reset ADC handle state.
  * @param __HANDLE__ ADC handle
  * @retval None
  */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)      \
  do{                                                 \
     (__HANDLE__)->State = HAL_ADC_STATE_RESET;       \
     (__HANDLE__)->MspInitCallback = NULL;            \
     (__HANDLE__)->MspDeInitCallback = NULL;          \
    } while(0)
#else
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)      \
  ((__HANDLE__)->State = HAL_ADC_STATE_RESET)
#endif


/**
  * @brief Enable ADC interrupt.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC Interrupt
  *        This parameter can be a combination of the following values:
  *            @arg @ref ADC_IRQ_EN_OVRFL  ADC Decimation Filter saturared interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_EN_AWD    ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_EN_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_EN_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_EN_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)     LL_ADC_EnableIT(__HANDLE__, __INTERRUPT__)


/**
  * @brief Disable ADC interrupt.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC Interrupt
  *        This parameter can be a combination of the following values:
  *            @arg @ref ADC_IRQ_EN_OVRFL  ADC Decimation Filter saturared interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_EN_AWD    ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_EN_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_EN_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_EN_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)    LL_ADC_DisableIT(__HANDLE__, __INTERRUPT__)


/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC interrupt source to check
  *          This parameter can be one of the following values:
  *            @arg @ref ADC_IRQ_EN_OVRFL  ADC Decimation Filter saturared interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_EN_AWD    ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_EN_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_EN_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_EN_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)    LL_ADC_IsEnabledIT(__HANDLE__, __INTERRUPT__)


/**
  * @brief Check whether the specified ADC flag is set or not.
  * @param __HANDLE__ ADC handle
  * @param __FLAG__ ADC flag
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_IRQ_FLAG_OVRFL  ADC Decimation Filter saturared interrupt source
  *            @arg @ref ADC_IRQ_FLAG_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_FLAG_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_FLAG_AWD    ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval State of flag (TRUE or FALSE).
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__)    LL_ADC_IsActiveFlag(__HANDLE__, __FLAG__)


/**
  * @brief Clear the specified ADC flag.
  * @param __HANDLE__ ADC handle
  * @param __FLAG__ ADC flag
  *        This parameter can be a combination of the following values:
  *            @arg @ref ADC_IRQ_FLAG_OVRFL  ADC Decimation Filter saturared interrupt source
  *            @arg @ref ADC_IRQ_FLAG_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_FLAG_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_FLAG_AWD    ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval None
  */
/* Note: bit cleared bit by writing 1 (writing 0 has no effect on any bit of register ISR) */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__)    LL_ADC_ClearActiveFlags(__HANDLE__, __FLAG__)


/**
  * @}
  */


/**
  * @}
  */


/* Include ADC HAL Extended module */
//#include "rf_driver_hal_adc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions
  * @{
  */

/** @addtogroup ADC_Exported_Functions_Group1
  * @brief    Initialization and Configuration functions
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
void                    HAL_ADC_StructInit(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_ADC_RegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID, pADC_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_ADC_UnRegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group2
  * @brief    IO operation functions
  * @{
  */

/* IO operation functions  *****************************************************/

/* Blocking mode: Polling */
  HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef* hadc); // start adc conversion ... ok after HAL_ADC_Init
  HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef* hadc);  // stop adc conversion .. ok after HAL_ADC_Start
  HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout); // Poll ECO o EOS
  HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout); // Poll 1 specific event 

/* Non-blocking mode: Interruption */
  HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc); // start adc conversion and enable EOC/EOS
  HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);

/* Non-blocking mode: DMA */
HAL_StatusTypeDef       HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length); // start adc conversion and fill a buffer with the data
HAL_StatusTypeDef       HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc); // stop conversion with dma

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);  // just get the output register value

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_WatchdogAlertCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);

/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions 
 * @{
 */

/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef       HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ConfigChannelTypeDef* ConfigChannel);  // Config the channel, see for the right struct
// HAL_StatusTypeDef       HAL_ADC_DSConfig(ADC_HandleTypeDef* hadc, ADC_ConfigDSTypeDef* ConfigDS); // config the DS
// HAL_StatusTypeDef       HAL_ADC_DFConfig(ADC_HandleTypeDef* hadc, ADC_ConfigDFTypeDef* ConfigDF); // config the DF
HAL_StatusTypeDef       HAL_ADC_WDGConfig(ADC_HandleTypeDef* hadc, ADC_ConfigWatchdogTypeDef* ConfigWatchdog); // config the WDG

/**
  * @}
  */

/* Peripheral State functions *************************************************/
/** @addtogroup ADC_Exported_Functions_Group4
  * @{
  */

uint32_t                HAL_ADC_GetState(ADC_HandleTypeDef* hadc);
uint32_t                HAL_ADC_GetError(ADC_HandleTypeDef *hadc);

/**
  * @}
  */

/**
  * @}
  */

/* Private functions -----------------------------------------------------------*/
/** @addtogroup ADC_Private_Functions ADC Private Functions
  * @{
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


#endif /* RF_DRIVER_HAL_ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
