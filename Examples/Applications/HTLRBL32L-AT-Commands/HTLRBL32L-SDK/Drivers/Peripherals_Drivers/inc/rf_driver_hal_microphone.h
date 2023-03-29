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
  * @brief  ADC handle Structure definition
  */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
typedef struct __ADC_HandleTypeDef
#else
typedef struct
#endif
{
  ADC_TypeDef                   *Instance;              /*!< Register base address */
  ADC_InitTypeDef               Init;                   /*!< ADC initialization parameters and regular conversions setting */
  DMA_HandleTypeDef             *DMA_Handle;            /*!< Pointer DMA Handler */
  HAL_LockTypeDef               Lock;                   /*!< ADC locking object */
  __IO uint32_t                 State;                  /*!< ADC communication state (bitmap of ADC states) */
  __IO uint32_t                 ErrorCode;              /*!< ADC Error code */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  void (* ConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);              /*!< ADC conversion complete callback */
  void (* ConvHalfCpltCallback)(struct __ADC_HandleTypeDef *hadc);          /*!< ADC conversion DMA half-transfer callback */
  void (* LevelOutOfWindowCallback)(struct __ADC_HandleTypeDef *hadc);      /*!< ADC analog watchdog 1 callback */
  void (* ErrorCallback)(struct __ADC_HandleTypeDef *hadc);                 /*!< ADC error callback */
  void (* MspInitCallback)(struct __ADC_HandleTypeDef *hadc);               /*!< ADC Msp Init callback */
  void (* MspDeInitCallback)(struct __ADC_HandleTypeDef *hadc);             /*!< ADC Msp DeInit callback */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
}ADC_HandleTypeDef;

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL ADC Callback ID enumeration definition
  */
typedef enum
{
  HAL_ADC_CONVERSION_COMPLETE_CB_ID     = 0x00U,  /*!< ADC conversion complete callback ID */
  HAL_ADC_CONVERSION_HALF_CB_ID         = 0x01U,  /*!< ADC conversion DMA half-transfer callback ID */
  HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID   = 0x02U,  /*!< ADC analog watchdog 1 callback ID */
  HAL_ADC_ERROR_CB_ID                   = 0x03U,  /*!< ADC error callback ID */
  HAL_ADC_MSPINIT_CB_ID                 = 0x09U,  /*!< ADC Msp Init callback ID          */
  HAL_ADC_MSPDEINIT_CB_ID               = 0x0AU   /*!< ADC Msp DeInit callback ID        */
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
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_REG_BUSY) != 0UL) "
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_AWD) != 0UL) "
  */
/* States of ADC global scope */
#define HAL_ADC_STATE_RESET             (0x00000000UL)   /*!< ADC not yet initialized or disabled */
#define HAL_ADC_STATE_READY             (0x00000001UL)   /*!< ADC peripheral ready for use */
#define HAL_ADC_STATE_BUSY_INTERNAL     (0x00000002UL)   /*!< ADC is busy due to an internal process (initialization, calibration) */
#define HAL_ADC_STATE_TIMEOUT           (0x00000004UL)   /*!< TimeOut occurrence */

/* States of ADC errors */
#define HAL_ADC_STATE_ERROR_INTERNAL    (0x00000010UL)   /*!< Internal error occurrence */
#define HAL_ADC_STATE_ERROR_CONFIG      (0x00000020UL)   /*!< Configuration error occurrence */
#define HAL_ADC_STATE_ERROR_DMA         (0x00000040UL)   /*!< DMA error occurrence */

/* States of ADC group */
#define HAL_ADC_STATE_BUSY          (0x00000100UL)   /*!< A conversion on ADC group is ongoing or can occur (either by continuous mode,
                                                          external trigger, low power auto power-on (if feature available), multimode ADC master control (if feature available)) */
#define HAL_ADC_STATE_EOC           (0x00000200UL)   /*!< Conversion data available on group */
#define HAL_ADC_STATE_OVR           (0x00000400UL)   /*!< Overrun occurrence */

/* States of ADC analog watchdog */
#define HAL_ADC_STATE_AWD              (0x00010000UL)   /*!< Out-of-window occurrence of ADC analog watchdog */

/**
  * @}
  */


/** @defgroup ADC_Error_Code ADC Error Code
  * @{
  */

#define HAL_ADC_ERROR_NONE              (0x00U)   /*!< No error                                    */
#define HAL_ADC_ERROR_INTERNAL          (0x01U)   /*!< ADC IP internal error (problem of clocking,
                                                       enable/disable, erroneous state, ...)       */
#define HAL_ADC_ERROR_OVR               (0x02U)   /*!< Overrun error                               */
#define HAL_ADC_ERROR_DMA               (0x04U)   /*!< DMA transfer error                          */
#define HAL_ADC_ERROR_OVF             (0x08U)   /*!< Context queue overflow error       */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define HAL_ADC_ERROR_INVALID_CALLBACK  (0x10U)   /*!< Invalid Callback error */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */



// REMOVE THE DEFINITIONS NOT NECESSARY TO THE API OF THE HAL DRIVER

/** @defgroup ADC_HAL_INPUT_METHOD  ADC input sampling method definitions
  * @brief    It defines the parameters used for the functions LL_ADC_InputSamplingMode() and LL_ADC_GetInputSamplingMode()
  * @{
  */

#define HAL_ADC_SAMPLING_AT_START    (LL_ADC_SAMPLING_AT_START)             /*!< Sampling only at conversion start (default) */
#define HAL_ADC_SAMPLING_AT_END      (LL_ADC_SAMPLING_AT_END)    /*!< Sampling starts at the end of conversion   */

/**
  * @}
  */


/** @defgroup ADC_HAL_DF_OVERRUN_CONFIG ADC overrun configuration definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetOverrunDF(), HAL_ADC_GetOverrunDF(), HAL_ADC_SetOverrunDS(), and HAL_ADC_GetOverrunDS()
  * @{
  */

#define HAL_ADC_NEW_DATA_IS_LOST    (LL_ADC_NEW_DATA_IS_LOST)    /*!< The previous data is lost, the new one is kept */
#define HAL_ADC_NEW_DATA_IS_KEPT    (LL_ADC_NEW_DATA_IS_KEPT)           /*!< The previous data is kept, the new one is lost */

/**
  * @}
  */


/** @defgroup ADC_HAL_SAMPLE_RATE ADC sample rate definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetSampleRate() and HAL_ADC_GetSampleRate()
  * @{
  */

#define HAL_ADC_SAMPLE_RATE_16    (LL_ADC_SAMPLE_RATE_16)                 /*!< ADC conversion rate at System clock / 16 */
#define HAL_ADC_SAMPLE_RATE_20    (LL_ADC_SAMPLE_RATE_20)  /*!< ADC conversion rate at System clock / 20 */
#define HAL_ADC_SAMPLE_RATE_24    (LL_ADC_SAMPLE_RATE_24)  /*!< ADC conversion rate at System clock / 24 */
#define HAL_ADC_SAMPLE_RATE_28    (LL_ADC_SAMPLE_RATE_28)  /*!< ADC conversion rate at System clock / 28 */

/**
  * @}
  */


/** @defgroup ADC_HAL_OP_MODE ADC operation modes definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetADCMode() and HAL_ADC_GetADCMode()
  * @{
  */

#define HAL_ADC_OP_MODE_AUDIO    (LL_ADC_OP_MODE_AUDIO)  /*!< ADC operation mode AUDIO */
#define HAL_ADC_OP_MODE_ADC      (LL_ADC_OP_MODE_ADC)  /*!< ADC operation mode ADC   */
#define HAL_ADC_OP_MODE_FULL     (LL_ADC_OP_MODE_FULL)  /*!< ADC operation Full mode  */

/**
  * @}
  */


/** @defgroup ADC_HAL_SEQUENCE_LEN ADC sequence length definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetSequenceLength() and HAL_ADC_GetSequenceLength()
  * @{
  */

#define HAL_ADC_SEQ_LEN_01    (LL_ADC_SEQ_LEN_01)             /*!< The sequence is of 1 conversion */
#define HAL_ADC_SEQ_LEN_02    (LL_ADC_SEQ_LEN_02)  /*!< The sequence is of 2 conversions */
#define HAL_ADC_SEQ_LEN_03    (LL_ADC_SEQ_LEN_03)  /*!< The sequence is of 3 conversions */
#define HAL_ADC_SEQ_LEN_04    (LL_ADC_SEQ_LEN_04)  /*!< The sequence is of 4 conversions */
#define HAL_ADC_SEQ_LEN_05    (LL_ADC_SEQ_LEN_05)  /*!< The sequence is of 5 conversions */
#define HAL_ADC_SEQ_LEN_06    (LL_ADC_SEQ_LEN_06)  /*!< The sequence is of 6 conversions */
#define HAL_ADC_SEQ_LEN_07    (LL_ADC_SEQ_LEN_07)  /*!< The sequence is of 7 conversions */
#define HAL_ADC_SEQ_LEN_08    (LL_ADC_SEQ_LEN_08)  /*!< The sequence is of 8 conversions */
#define HAL_ADC_SEQ_LEN_09    (LL_ADC_SEQ_LEN_09)  /*!< The sequence is of 9 conversions */
#define HAL_ADC_SEQ_LEN_10    (LL_ADC_SEQ_LEN_10)  /*!< The sequence is of 10 conversions */
#define HAL_ADC_SEQ_LEN_11    (LL_ADC_SEQ_LEN_11) /*!< The sequence is of 11 conversions */
#define HAL_ADC_SEQ_LEN_12    (LL_ADC_SEQ_LEN_12) /*!< The sequence is of 12 conversions */
#define HAL_ADC_SEQ_LEN_13    (LL_ADC_SEQ_LEN_13) /*!< The sequence is of 13 conversions */
#define HAL_ADC_SEQ_LEN_14    (LL_ADC_SEQ_LEN_14) /*!< The sequence is of 14 conversions */
#define HAL_ADC_SEQ_LEN_15    (LL_ADC_SEQ_LEN_15) /*!< The sequence is of 15 conversions */
#define HAL_ADC_SEQ_LEN_16    (LL_ADC_SEQ_LEN_16) /*!< The sequence is of 16 conversions */

/**
  * @}
  */


/** @defgroup ADC_HAL_OCM_SOURCE ADC occasional mode source definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetOccasionalConversionSource() and HAL_ADC_GetOccasionalConversionSource()
  * @{
  */

#define HAL_ADC_OCM_SRC_VBAT    (LL_ADC_OCM_SRC_VBAT)  /*!< ADC occasional mode source VBAT               */
#define HAL_ADC_OCM_SRC_TEMP    (LL_ADC_OCM_SRC_TEMP)  /*!< ADC occasional mode source temperature sensor */

/**
  * @}
  */


/** @defgroup ADC_HAL_PGA_BIAS ADC microphone bias voltage definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetMicrophonePGABias() and HAL_ADC_GetMicrophonePGABias()
  * @{
  */

#define HAL_ADC_PGA_BIAS_050_BAT   (LL_ADC_PGA_BIAS_050_BAT)                  /*!< Set the microphone bias voltage at 0.50 V */
#define HAL_ADC_PGA_BIAS_055_BAT   (LL_ADC_PGA_BIAS_055_BAT)  /*!< Set the microphone bias voltage at 0.55 V */
#define HAL_ADC_PGA_BIAS_060_BAT   (LL_ADC_PGA_BIAS_060_BAT)  /*!< Set the microphone bias voltage at 0.60 V */
#define HAL_ADC_PGA_BIAS_065_BAT   (LL_ADC_PGA_BIAS_065_BAT)  /*!< Set the microphone bias voltage at 0.65 V */
#define HAL_ADC_PGA_BIAS_070_BAT   (LL_ADC_PGA_BIAS_070_BAT)  /*!< Set the microphone bias voltage at 0.70 V */
#define HAL_ADC_PGA_BIAS_075_BAT   (LL_ADC_PGA_BIAS_075_BAT)  /*!< Set the microphone bias voltage at 0.75 V */
#define HAL_ADC_PGA_BIAS_080_BAT   (LL_ADC_PGA_BIAS_080_BAT)  /*!< Set the microphone bias voltage at 0.80 V */
#define HAL_ADC_PGA_BIAS_090_BAT   (LL_ADC_PGA_BIAS_090_BAT)  /*!< Set the microphone bias voltage at 0.90 V */

/**
  * @}
  */


/** @defgroup ADC_HAL_PGA_GAIN ADC microphone gain definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetMicrophonePGAGain() and HAL_ADC_GetMicrophonePGAGain()
  * @{
  */

#define HAL_ADC_PGA_GAIN_06_DB   (LL_ADC_PGA_GAIN_06_DB)  /*!< Set the microphone gain at 6 dB  */
#define HAL_ADC_PGA_GAIN_09_DB   (LL_ADC_PGA_GAIN_09_DB)  /*!< Set the microphone gain at 9 dB  */
#define HAL_ADC_PGA_GAIN_12_DB   (LL_ADC_PGA_GAIN_12_DB)  /*!< Set the microphone gain at 12 dB */
#define HAL_ADC_PGA_GAIN_15_DB   (LL_ADC_PGA_GAIN_15_DB)  /*!< Set the microphone gain at 15 dB */
#define HAL_ADC_PGA_GAIN_18_DB   (LL_ADC_PGA_GAIN_18_DB)  /*!< Set the microphone gain at 18 dB */
#define HAL_ADC_PGA_GAIN_21_DB   (LL_ADC_PGA_GAIN_21_DB)  /*!< Set the microphone gain at 21 dB */
#define HAL_ADC_PGA_GAIN_24_DB   (LL_ADC_PGA_GAIN_24_DB)  /*!< Set the microphone gain at 24 dB */
#define HAL_ADC_PGA_GAIN_27_DB   (LL_ADC_PGA_GAIN_27_DB)  /*!< Set the microphone gain at 27 dB */
#define HAL_ADC_PGA_GAIN_30_DB   (LL_ADC_PGA_GAIN_30_DB)  /*!< Set the microphone gain at 30 dB */
#define HAL_ADC_PGA_GAIN_33_DB   (LL_ADC_PGA_GAIN_33_DB)  /*!< Set the microphone gain at 33 dB */

/**
  * @}
  */


/** @defgroup ADC_HAL_INPUT_VOLTAGE_RANGE ADC input voltage range definitions
  * @brief    It defines the parameters used for the functions:
  *           HAL_ADC_SetVoltageRangeSingleVinm0(),    HAL_ADC_GetVoltageRangeSingleVinm0(),
  *           HAL_ADC_SetVoltageRangeDiffVinp0Vinm0(), HAL_ADC_GetVoltageRangeDiffVinp0Vinm0(),
  *           HAL_ADC_SetVoltageRangeSingleVinm1(),    HAL_ADC_GetVoltageRangeSingleVinm1(),
  *           HAL_ADC_SetVoltageRangeDiffVinp1Vinm1(), HAL_ADC_GetVoltageRangeDiffVinp1Vinm1(),
  *           HAL_ADC_SetVoltageRangeSingleVinm2(),    HAL_ADC_GetVoltageRangeSingleVinm2(),
  *           HAL_ADC_SetVoltageRangeDiffVinp2Vinm2(), HAL_ADC_GetVoltageRangeDiffVinp2Vinm2(),
  *           HAL_ADC_SetVoltageRangeSingleVinm3(),    HAL_ADC_GetVoltageRangeSingleVinm3(),
  *           HAL_ADC_SetVoltageRangeDiffVinp3Vinm3(), HAL_ADC_GetVoltageRangeDiffVinp3Vinm3(),
  *           HAL_ADC_SetVoltageRangeSingleVinp0(),    HAL_ADC_GetVoltageRangeSingleVinp0(),
  *           HAL_ADC_SetVoltageRangeSingleVinp1(),    HAL_ADC_GetVoltageRangeSingleVinp1(),
  *           HAL_ADC_SetVoltageRangeSingleVinp2(),    HAL_ADC_GetVoltageRangeSingleVinp2(),
  *           HAL_ADC_SetVoltageRangeSingleVinp3() and HAL_ADC_GetVoltageRangeSingleVinp3()
  * @{
  */

#define HAL_ADC_VIN_RANGE_1V2    (LL_ADC_VIN_RANGE_1V2)  /*!< ADC input voltage range up to 1.2 V */
#define HAL_ADC_VIN_RANGE_2V4    (LL_ADC_VIN_RANGE_2V4)  /*!< ADC input voltage range up to 2.4 V */
#define HAL_ADC_VIN_RANGE_3V6    (LL_ADC_VIN_RANGE_3V6)  /*!< ADC input voltage range up to 3.6 V */

/**
  * @}
  */


/** @defgroup ADC_HAL_DF_DYN_RANGE ADC Decimation Filter dynamic range definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetDFInputDynamic() and HAL_ADC_GetDFInputDynamic()
  * @{
  */

#define HAL_ADC_DF_DYN_RANGE_FULL    (LL_ADC_DF_DYN_RANGE_FULL)                     /*!< ADC Decimation Filter dynamic full range */
#define HAL_ADC_DF_DYN_RANGE_HALF    (LL_ADC_DF_DYN_RANGE_HALF)  /*!< ADC Decimation Filter dynamic half range */

/**
  * @}
  */


/** @defgroup ADC_HAL_MIC_CHANNEL ADC microphone channel definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetMicrophoneChannel() and HAL_ADC_GetMicrophoneChannel()
  * @{
  */

#define HAL_ADC_DF_MIC_CH_RIGHT    (LL_ADC_DF_MIC_CH_RIGHT)                     /*!< ADC microphone channel right */
#define HAL_ADC_DF_MIC_CH_LEFT     (LL_ADC_DF_MIC_CH_LEFT)  /*!< ADC microphone channel left  */

/**
  * @}
  */


/** @defgroup ADC_HAL_PDM_CLK_DIVIDER ADC PDM clock divider definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetPDMRate() and HAL_ADC_GetPDMRate()
  * @{
  */

#define HAL_ADC_PDM_DIV_10   (LL_ADC_PDM_DIV_10)                    /*!< ADC PDM clock divider 10 */
#define HAL_ADC_PDM_DIV_11   (LL_ADC_PDM_DIV_11)  /*!< ADC PDM clock divider 11 */
#define HAL_ADC_PDM_DIV_12   (LL_ADC_PDM_DIV_12)  /*!< ADC PDM clock divider 12 */
#define HAL_ADC_PDM_DIV_13   (LL_ADC_PDM_DIV_13)  /*!< ADC PDM clock divider 13 */
#define HAL_ADC_PDM_DIV_14   (LL_ADC_PDM_DIV_14)  /*!< ADC PDM clock divider 14 */
#define HAL_ADC_PDM_DIV_15   (LL_ADC_PDM_DIV_15)  /*!< ADC PDM clock divider 15 */
#define HAL_ADC_PDM_DIV_16   (LL_ADC_PDM_DIV_16)  /*!< ADC PDM clock divider 16 */
#define HAL_ADC_PDM_DIV_17   (LL_ADC_PDM_DIV_17)  /*!< ADC PDM clock divider 17 */
#define HAL_ADC_PDM_DIV_18   (LL_ADC_PDM_DIV_18)  /*!< ADC PDM clock divider 18 */
#define HAL_ADC_PDM_DIV_19   (LL_ADC_PDM_DIV_19)  /*!< ADC PDM clock divider 19 */
#define HAL_ADC_PDM_DIV_20   (LL_ADC_PDM_DIV_20)  /*!< ADC PDM clock divider 20 */
#define HAL_ADC_PDM_DIV_21   (LL_ADC_PDM_DIV_21)  /*!< ADC PDM clock divider 21 */
#define HAL_ADC_PDM_DIV_22   (LL_ADC_PDM_DIV_22)  /*!< ADC PDM clock divider 22 */
#define HAL_ADC_PDM_DIV_23   (LL_ADC_PDM_DIV_23)  /*!< ADC PDM clock divider 23 */
#define HAL_ADC_PDM_DIV_24   (LL_ADC_PDM_DIV_24)  /*!< ADC PDM clock divider 24 */
#define HAL_ADC_PDM_DIV_25   (LL_ADC_PDM_DIV_25)  /*!< ADC PDM clock divider 25 */

/**
  * @}
  */


/** @defgroup ADC_HAL_DATA_FORMAT ADC data format definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetDataOutputFormat(), HAL_ADC_GetDataOutputFormat(), HAL_ADC_SetDataInputFormat() and HAL_ADC_GetDataInputFormat()
  * @{
  */

#define HAL_ADC_DATA_FRMT_SIGNED    (LL_ADC_DATA_FRMT_SIGNED)  /*!< ADC data format signed   */
#define HAL_ADC_DATA_FRMT_UNSIGNED  (LL_ADC_DATA_FRMT_UNSIGNED)  /*!< ADC data format unsigned */

/**
  * @}
  */


/** @defgroup ADC_HAL_CIC_DECIMATOR_FACTOR ADC CIC decimator factor definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetCICDecimatorFactor() and HAL_ADC_GetCICDecimatorFactor()
  * @{
  */

#define HAL_ADC_CIC_DECIMATOR_FACTOR_HALF     (LL_ADC_CIC_DECIMATOR_FACTOR_HALF)  /*!< ADC CIC decimator factor half    */
#define HAL_ADC_CIC_DECIMATOR_FACTOR_INTEGER  (LL_ADC_CIC_DECIMATOR_FACTOR_INTEGER)            /*!< ADC CIC decimator factor integer */

/**
  * @}
  */


/** @defgroup ADC_HAL_MICROPHONE_OUT_FREQ ADC microphone output frequency definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetMicrophoneOutputDatarate() and HAL_ADC_GetMicrophoneOutputDatarate()
  * @{
  */

#define HAL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ)  /*!< ADC digital microphone output frequency 47.619 kHz */
#define HAL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ)  /*!< ADC digital microphone output frequency 44.44  kHz */
#define HAL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ)  /*!< ADC digital microphone output frequency 22.22  kHz */
#define HAL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ)  /*!< ADC digital microphone output frequency 15.873 kHz */
#define HAL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ   (LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ)  /*!< ADC digital microphone output frequency 7.936  kHz */

#define HAL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ (LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ)  /*!< ADC analog microphone output frequency 200.00 kHz */
#define HAL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ  (LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ)  /*!< ADC analog microphone output frequency 15.873 kHz */
#define HAL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ   (LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ)  /*!< ADC analog microphone output frequency 7.936  kHz */

/**
  * @}
  */


/** @defgroup ADC_HAL_DS_DATA_WIDTH ADC Down Sampler data width definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetDSDataOutputWidth() and HAL_ADC_GetDSDataOutputWidth()
  * @{
  */

#define HAL_ADC_DS_DATA_WIDTH_12_BIT  (LL_ADC_DS_DATA_WIDTH_12_BIT)                 /*!< ADC Down Sampler data width 12 bits */
#define HAL_ADC_DS_DATA_WIDTH_13_BIT  (LL_ADC_DS_DATA_WIDTH_13_BIT)  /*!< ADC Down Sampler data width 13 bits */
#define HAL_ADC_DS_DATA_WIDTH_14_BIT  (LL_ADC_DS_DATA_WIDTH_14_BIT)  /*!< ADC Down Sampler data width 14 bits */
#define HAL_ADC_DS_DATA_WIDTH_15_BIT  (LL_ADC_DS_DATA_WIDTH_15_BIT)  /*!< ADC Down Sampler data width 15 bits */
#define HAL_ADC_DS_DATA_WIDTH_16_BIT  (LL_ADC_DS_DATA_WIDTH_16_BIT)  /*!< ADC Down Sampler data width 16 bits */

/**
  * @}
  */


/** @defgroup ADC_HAL_DS_RATIO ADC Down Sampler ratio definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetDSDataOutputRatio() and HAL_ADC_GetDSDataOutputRatio()
  * @{
  */

#define HAL_ADC_DS_RATIO_01   (LL_ADC_DS_RATIO_01)      /*!< ADC Down Sampler ratio 1, no down sampling (default) */
#define HAL_ADC_DS_RATIO_02   (LL_ADC_DS_RATIO_02)      /*!< ADC Down Sampler ratio 2                             */
#define HAL_ADC_DS_RATIO_04   (LL_ADC_DS_RATIO_04)      /*!< ADC Down Sampler ratio 4                             */
#define HAL_ADC_DS_RATIO_08   (LL_ADC_DS_RATIO_08)      /*!< ADC Down Sampler ratio 8                             */
#define HAL_ADC_DS_RATIO_16   (LL_ADC_DS_RATIO_16)      /*!< ADC Down Sampler ratio 16                            */
#define HAL_ADC_DS_RATIO_32   (LL_ADC_DS_RATIO_32)      /*!< ADC Down Sampler ratio 32                            */
#define HAL_ADC_DS_RATIO_64   (LL_ADC_DS_RATIO_64)      /*!< ADC Down Sampler ratio 64                            */
#define HAL_ADC_DS_RATIO_128  (LL_ADC_DS_RATIO_128)      /*!< ADC Down Sampler ratio 128                           */

/**
  * @}
  */


/** @defgroup ADC_HAL_CH_NUM_CODE ADC channel number code for conversion definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetChannelSeqX() and HAL_ADC_GetChannelSeqX() with X = 0, 1, ...15
  * @{
  */

#define HAL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT  (LL_ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT)  /*!< ADC channel number code for the conversion is VINM0 to single negative input */
#define HAL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT  (LL_ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT)  /*!< ADC channel number code for the conversion is VINM1 to single negative input */
#define HAL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT  (LL_ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT)  /*!< ADC channel number code for the conversion is VINM2 to single negative input */
#define HAL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT  (LL_ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT)  /*!< ADC channel number code for the conversion is VINM3 to single negative input */
#define HAL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT  (LL_ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT)  /*!< ADC channel number code for the conversion is VINP0 to single positive input */
#define HAL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT  (LL_ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT)  /*!< ADC channel number code for the conversion is VINP1 to single positive input */
#define HAL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT  (LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT)  /*!< ADC channel number code for the conversion is VINP2 to single positive input */
#define HAL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT  (LL_ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT)  /*!< ADC channel number code for the conversion is VINP3 to single positive input */
#define HAL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT       (LL_ADC_CH_VINP0_VINM0_TO_DIFF_INPUT)  /*!< ADC channel number code for the conversion is VINP0 - VINM0 to differential input */
#define HAL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT       (LL_ADC_CH_VINP1_VINM1_TO_DIFF_INPUT)  /*!< ADC channel number code for the conversion is VINP1 - VINM1 to differential input */
#define HAL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT       (LL_ADC_CH_VINP2_VINM2_TO_DIFF_INPUT)  /*!< ADC channel number code for the conversion is VINP2 - VINM2 to differential input */
#define HAL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT       (LL_ADC_CH_VINP3_VINM3_TO_DIFF_INPUT)  /*!< ADC channel number code for the conversion is VINP3 - VINM3 to differential input */
#define HAL_ADC_CH_BATTERY_LEVEL_DETECTOR          (LL_ADC_CH_BATTERY_LEVEL_DETECTOR)  /*!< ADC channel number code for the conversion is VBAT, battery level detector */
#define HAL_ADC_CH_TEMPERATURE_SENSOR              (LL_ADC_CH_TEMPERATURE_SENSOR)  /*!< ADC channel number code for the conversion is temperature sensor */

/**
  * @}
  */


/** @defgroup ADC_HAL_CALIB_POINT ADC calibration points definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetCalibPointForDiff3V6(), HAL_ADC_GetCalibPointForDiff3V6(),
  *           HAL_ADC_SetCalibPointForSinglePos3V6(), HAL_ADC_GetCalibPointForSinglePos3V6(), HAL_ADC_SetCalibPointForSingleNeg3V6(),
  *           HAL_ADC_GetCalibPointForSingleNeg3V6(), HAL_ADC_SetCalibPointForDiff2V4(), HAL_ADC_GetCalibPointForDiff2V4(),
  *           HAL_ADC_SetCalibPointForSinglePos2V4(), HAL_ADC_GetCalibPointForSinglePos2V4(), HAL_ADC_SetCalibPointForSingleNeg2V4(),
  *           HAL_ADC_GetCalibPointForSingleNeg2V4(), HAL_ADC_SetCalibPointForDiff1V2(), HAL_ADC_GetCalibPointForDiff1V2(),
  *           HAL_ADC_SetCalibPointForSinglePos1V2(), HAL_ADC_SetCalibPointForSingleNeg1V2() and HAL_ADC_GetCalibPointForSingleNeg1V2()
  * @{
  */

#define HAL_ADC_CALIB_POINT_1  (LL_ADC_CALIB_POINT_1)  /*!< ADC calibration point 1 */
#define HAL_ADC_CALIB_POINT_2  (LL_ADC_CALIB_POINT_2)  /*!< ADC calibration point 2 */
#define HAL_ADC_CALIB_POINT_3  (LL_ADC_CALIB_POINT_3)  /*!< ADC calibration point 3 */
#define HAL_ADC_CALIB_POINT_4  (LL_ADC_CALIB_POINT_4)  /*!< ADC calibration point 4 */

/**
  * @}
  */

/** @defgroup ADC_HAL_CALIB_POINT ADC calibration points definitions
  * @brief    It defines the parameters used for the functions HAL_ADC_SetWDGInputChannels() and HAL_ADC_GetWDGInputChannels()
  * @{
  */

#define HAL_ADC_VINM0_TO_NEG     (LL_ADC_VINM0_TO_NEG )  /*!< ADC watchdog channel selection: VINM0 to ADC negative input  */
#define HAL_ADC_VINM1_TO_NEG     (LL_ADC_VINM1_TO_NEG )  /*!< ADC watchdog channel selection: VINM1 to ADC negative input  */
#define HAL_ADC_VINM2_TO_NEG     (LL_ADC_VINM2_TO_NEG )  /*!< ADC watchdog channel selection: VINM2 to ADC negative input  */
#define HAL_ADC_VINM3_TO_NEG     (LL_ADC_VINM3_TO_NEG )  /*!< ADC watchdog channel selection: VINM3 to ADC negative input  */
#define HAL_ADC_MICROM_TO_NEG    (LL_ADC_MICROM_TO_NEG )  /*!< ADC watchdog channel selection: MICROM to ADC negative input */
#define HAL_ADC_VBAT_TO_NEG      (LL_ADC_VBAT_TO_NEG )  /*!< ADC watchdog channel selection: VBAT to ADC negative input   */
#define HAL_ADC_GND_TO_NEG       (LL_ADC_GND_TO_NEG )  /*!< ADC watchdog channel selection: GND to ADC negative input    */
#define HAL_ADC_VDDA_TO_NEG      (LL_ADC_VDDA_TO_NEG )  /*!< ADC watchdog channel selection: VDDA to ADC negative input   */
#define HAL_ADC_VINP0_TO_POS     (LL_ADC_VINP0_TO_POS )  /*!< ADC watchdog channel selection: VINP0 to ADC positive input  */
#define HAL_ADC_VINP1_TO_POS     (LL_ADC_VINP1_TO_POS )  /*!< ADC watchdog channel selection: VINP1 to ADC positive input  */
#define HAL_ADC_VINP2_TO_POS     (LL_ADC_VINP2_TO_POS)  /*!< ADC watchdog channel selection: VINP2 to ADC positive input  */
#define HAL_ADC_VINP3_TO_POS     (LL_ADC_VINP3_TO_POS)  /*!< ADC watchdog channel selection: VINP3 to ADC positive input  */
#define HAL_ADC_MICROP_TO_POS    (LL_ADC_MICROP_TO_POS)  /*!< ADC watchdog channel selection: MICROP to ADC positive input */
#define HAL_ADC_TEMP_TO_POS      (LL_ADC_TEMP_TO_POS)  /*!< ADC watchdog channel selection: TEMP to ADC positive input   */
#define HAL_ADC_GND_TO_POS       (LL_ADC_GND_TO_POS)  /*!< ADC watchdog channel selection: GND to ADC positive input    */
#define HAL_ADC_VDDA_TO_POS      (LL_ADC_VDDA_TO_POS)  /*!< ADC watchdog channel selection: VDDA to ADC positive input   */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_STATUS ADC flags definitions
  * @brief    It defines the IRQ status flags used for the functions HAL_ADC_SetWDGInputChannels() and HAL_ADC_GetWDGInputChannels()
  * @{
  */

#define HAL_ADC_VINM0_TO_NEG     (LL_ADC_VINM0_TO_NEG )  /*!< ADC watchdog channel selection: VINM0 to ADC negative input  */
#define HAL_ADC_VINM1_TO_NEG     (LL_ADC_VINM1_TO_NEG )  /*!< ADC watchdog channel selection: VINM1 to ADC negative input  */
#define HAL_ADC_VINM2_TO_NEG     (LL_ADC_VINM2_TO_NEG )  /*!< ADC watchdog channel selection: VINM2 to ADC negative input  */
#define HAL_ADC_VINM3_TO_NEG     (LL_ADC_VINM3_TO_NEG )  /*!< ADC watchdog channel selection: VINM3 to ADC negative input  */
#define HAL_ADC_MICROM_TO_NEG    (LL_ADC_MICROM_TO_NEG )  /*!< ADC watchdog channel selection: MICROM to ADC negative input */
#define HAL_ADC_VBAT_TO_NEG      (LL_ADC_VBAT_TO_NEG )  /*!< ADC watchdog channel selection: VBAT to ADC negative input   */
#define HAL_ADC_GND_TO_NEG       (LL_ADC_GND_TO_NEG )  /*!< ADC watchdog channel selection: GND to ADC negative input    */
#define HAL_ADC_VDDA_TO_NEG      (LL_ADC_VDDA_TO_NEG )  /*!< ADC watchdog channel selection: VDDA to ADC negative input   */
#define HAL_ADC_VINP0_TO_POS     (LL_ADC_VINP0_TO_POS )  /*!< ADC watchdog channel selection: VINP0 to ADC positive input  */
#define HAL_ADC_VINP1_TO_POS     (LL_ADC_VINP1_TO_POS )  /*!< ADC watchdog channel selection: VINP1 to ADC positive input  */
#define HAL_ADC_VINP2_TO_POS     (LL_ADC_VINP2_TO_POS)  /*!< ADC watchdog channel selection: VINP2 to ADC positive input  */
#define HAL_ADC_VINP3_TO_POS     (LL_ADC_VINP3_TO_POS)  /*!< ADC watchdog channel selection: VINP3 to ADC positive input  */
#define HAL_ADC_MICROP_TO_POS    (LL_ADC_MICROP_TO_POS)  /*!< ADC watchdog channel selection: MICROP to ADC positive input */
#define HAL_ADC_TEMP_TO_POS      (LL_ADC_TEMP_TO_POS)  /*!< ADC watchdog channel selection: TEMP to ADC positive input   */
#define HAL_ADC_GND_TO_POS       (LL_ADC_GND_TO_POS)  /*!< ADC watchdog channel selection: GND to ADC positive input    */
#define HAL_ADC_VDDA_TO_POS      (LL_ADC_VDDA_TO_POS)  /*!< ADC watchdog channel selection: VDDA to ADC positive input   */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_STATUS_MASK ADC IRQ_STATUS register mask definitions
  * @brief    It defines the IRQ flags used for the functions HAL_ADC_ClearActiveFlags() and HAL_ADC_GetActiveFlags().
  * @{
  */

#define HAL_ADC_IRQ_FLAG_OVRFL   (LL_ADC_IRQ_FLAG_OVRFL) /*!< ADC IRQ flag OVRFL */
#define HAL_ADC_IRQ_FLAG_OVRDF   (LL_ADC_IRQ_FLAG_OVRDF) /*!< ADC IRQ flag OVRDF */
#define HAL_ADC_IRQ_FLAG_OVRDS   (LL_ADC_IRQ_FLAG_OVRDS) /*!< ADC IRQ flag OVRDS */
#define HAL_ADC_IRQ_FLAG_AWD     (LL_ADC_IRQ_FLAG_AWD)   /*!< ADC IRQ flag AWD   */
#define HAL_ADC_IRQ_FLAG_EOS     (LL_ADC_IRQ_FLAG_EOS)   /*!< ADC IRQ flag EOS   */
#define HAL_ADC_IRQ_FLAG_EODF    (LL_ADC_IRQ_FLAG_EODF)  /*!< ADC IRQ flag EODF  */
#define HAL_ADC_IRQ_FLAG_EODS    (LL_ADC_IRQ_FLAG_EODS)  /*!< ADC IRQ flag EODS  */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_ENABLE_MASK ADC IRQ_ENABLE register mask definitions
  * @brief    It defines the mask of the register  IRQ_ENABLE
  * @{
  */

#define ADC_IRQ_FLAGS_MASK      (LL_ADC_IRQ_FLAG_OVRFL | \
                                 HAL_ADC_IRQ_FLAG_OVRDF | \
                                 HAL_ADC_IRQ_FLAG_OVRDS | \
                                 HAL_ADC_IRQ_FLAG_AWD   | \
                                 HAL_ADC_IRQ_FLAG_EOS   | \
                                 HAL_ADC_IRQ_FLAG_EODF  | \
                                 HAL_ADC_IRQ_FLAG_EODS)

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_ENABLE ADC interrupts enable definitions
  * @brief    It defines the IRQ interrupt enable used for the functions HAL_ADC_ClearActiveFlags() and HAL_ADC_GetActiveFlags().
  * @{
  */

#define HAL_ADC_IRQ_EN_OVRFL   (LL_ADC_IRQ_EN_OVRFL) /*!< ADC IRQ enable OVRFL */
#define HAL_ADC_IRQ_EN_OVRDF   (LL_ADC_IRQ_EN_OVRDF)   /*!< ADC IRQ enable OVRDF */
#define HAL_ADC_IRQ_EN_OVRDS   (LL_ADC_IRQ_EN_OVRDS)   /*!< ADC IRQ enable OVRDS */
#define HAL_ADC_IRQ_EN_AWD     (LL_ADC_IRQ_EN_AWD)      /*!< ADC IRQ enable AWD   */
#define HAL_ADC_IRQ_EN_EOS     (LL_ADC_IRQ_EN_EOS)      /*!< ADC IRQ enable EOS   */
#define HAL_ADC_IRQ_EN_EODF    (LL_ADC_IRQ_EN_EODF)     /*!< ADC IRQ enable EODF  */
#define HAL_ADC_IRQ_EN_EODS    (LL_ADC_IRQ_EN_EODS)     /*!< ADC IRQ enable EODS  */

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
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)                               \
  do{                                                                          \
     (__HANDLE__)->State = HAL_ADC_STATE_RESET;                               \
     (__HANDLE__)->MspInitCallback = NULL;                                     \
     (__HANDLE__)->MspDeInitCallback = NULL;                                   \
    } while(0)
#else
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)                               \
  ((__HANDLE__)->State = HAL_ADC_STATE_RESET)
#endif

/**
  * @brief Enable ADC interrupt.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC Interrupt
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_IT_RDY    ADC Ready interrupt source
  *            @arg @ref ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg @ref ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg @ref ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_OVR    ADC overrun interrupt source
  *            @arg @ref ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg @ref ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_AWD1   ADC Analog watchdog 1 interrupt source (main analog watchdog)
  *            @arg @ref ADC_IT_AWD2   ADC Analog watchdog 2 interrupt source (additional analog watchdog)
  *            @arg @ref ADC_IT_AWD3   ADC Analog watchdog 3 interrupt source (additional analog watchdog)
  *            @arg @ref ADC_IT_JQOVF  ADC Injected Context Queue Overflow interrupt source. 
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)                         \
  (((__HANDLE__)->Instance->IER) |= (__INTERRUPT__))

/**
  * @brief Disable ADC interrupt.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC Interrupt
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_IT_RDY    ADC Ready interrupt source
  *            @arg @ref ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg @ref ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg @ref ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_OVR    ADC overrun interrupt source
  *            @arg @ref ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg @ref ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_AWD1   ADC Analog watchdog 1 interrupt source (main analog watchdog)
  *            @arg @ref ADC_IT_AWD2   ADC Analog watchdog 2 interrupt source (additional analog watchdog)
  *            @arg @ref ADC_IT_AWD3   ADC Analog watchdog 3 interrupt source (additional analog watchdog)
  *            @arg @ref ADC_IT_JQOVF  ADC Injected Context Queue Overflow interrupt source. 
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)                        \
  (((__HANDLE__)->Instance->IER) &= ~(__INTERRUPT__))

/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC interrupt source to check
  *          This parameter can be one of the following values:
  *            @arg @ref ADC_IT_RDY    ADC Ready interrupt source
  *            @arg @ref ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg @ref ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg @ref ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_OVR    ADC overrun interrupt source
  *            @arg @ref ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg @ref ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg @ref ADC_IT_AWD1   ADC Analog watchdog 1 interrupt source (main analog watchdog)
  *            @arg @ref ADC_IT_AWD2   ADC Analog watchdog 2 interrupt source (additional analog watchdog)
  *            @arg @ref ADC_IT_AWD3   ADC Analog watchdog 3 interrupt source (additional analog watchdog)
  *            @arg @ref ADC_IT_JQOVF  ADC Injected Context Queue Overflow interrupt source.  
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                     \
  (((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__))
    
/**
  * @brief Check whether the specified ADC flag is set or not.
  * @param __HANDLE__ ADC handle
  * @param __FLAG__ ADC flag
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_FLAG_RDY     ADC Ready flag                              
  *            @arg @ref ADC_FLAG_EOSMP   ADC End of Sampling flag                            
  *            @arg @ref ADC_FLAG_EOC     ADC End of Regular Conversion flag                  
  *            @arg @ref ADC_FLAG_EOS     ADC End of Regular sequence of Conversions flag     
  *            @arg @ref ADC_FLAG_OVR     ADC overrun flag        
  *            @arg @ref ADC_FLAG_JEOC    ADC End of Injected Conversion flag                 
  *            @arg @ref ADC_FLAG_JEOS    ADC End of Injected sequence of Conversions flag    
  *            @arg @ref ADC_FLAG_AWD1    ADC Analog watchdog 1 flag (main analog watchdog)
  *            @arg @ref ADC_FLAG_AWD2    ADC Analog watchdog 2 flag (additional analog watchdog)
  *            @arg @ref ADC_FLAG_AWD3    ADC Analog watchdog 3 flag (additional analog watchdog)
  *            @arg @ref ADC_FLAG_JQOVF   ADC Injected Context Queue Overflow flag.            
  * @retval State of flag (TRUE or FALSE).
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__)                               \
  ((((__HANDLE__)->Instance->ISR) & (__FLAG__)) == (__FLAG__))

/**
  * @brief Clear the specified ADC flag.
  * @param __HANDLE__ ADC handle
  * @param __FLAG__ ADC flag
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_FLAG_RDY     ADC Ready flag                              
  *            @arg @ref ADC_FLAG_EOSMP   ADC End of Sampling flag                            
  *            @arg @ref ADC_FLAG_EOC     ADC End of Regular Conversion flag                  
  *            @arg @ref ADC_FLAG_EOS     ADC End of Regular sequence of Conversions flag     
  *            @arg @ref ADC_FLAG_OVR     ADC overrun flag        
  *            @arg @ref ADC_FLAG_JEOC    ADC End of Injected Conversion flag                 
  *            @arg @ref ADC_FLAG_JEOS    ADC End of Injected sequence of Conversions flag    
  *            @arg @ref ADC_FLAG_AWD1    ADC Analog watchdog 1 flag (main analog watchdog)
  *            @arg @ref ADC_FLAG_AWD2    ADC Analog watchdog 2 flag (additional analog watchdog)
  *            @arg @ref ADC_FLAG_AWD3    ADC Analog watchdog 3 flag (additional analog watchdog)
  *            @arg @ref ADC_FLAG_JQOVF   ADC Injected Context Queue Overflow flag.   
  * @retval None
  */
/* Note: bit cleared bit by writing 1 (writing 0 has no effect on any bit of register ISR) */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__)                             \
  (((__HANDLE__)->Instance->ISR) = (__FLAG__))

/**
  * @}
  */


/**
  * @}
  */

/* Include ADC HAL Extended module */
#include "rf_driver_hal_adc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions
  * @{
  */

/** @addtogroup ADC_Exported_Functions_Group1
  * @brief    Initialization and Configuration functions
  * @{
  */
/* Initialization and de-initialization functions  ****************************/
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
HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);
HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);

/* Non-blocking mode: DMA */
HAL_StatusTypeDef       HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions 
 * @{
 */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef       HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);
HAL_StatusTypeDef       HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);

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
HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc, uint32_t ConversionGroup);
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc);
void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAError(DMA_HandleTypeDef *hdma);

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
