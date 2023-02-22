/**
  ******************************************************************************
  * @file    rf_driver_hal_adc.c
  * @author  RF Application Team
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of the conversions using 
  *                3 possible modes: polling, interruption or DMA.
  *           + Control functions
  *             ++ Channels configuration
  *             ++ Analog Watchdog configuration
  *           + State functions
  *             ++ ADC state machine management
  *             ++ Interrupts and flags management
  *          Other functions (extended functions) are available in file 
  *          "rf_driver_hal_adc_ex.c".
  *
  @verbatim
  ==============================================================================
                     ##### ADC peripheral features #####
  ==============================================================================
  [..]
  (+) Conversion frequency is up to 1 Msps.

  (+) Three input voltage ranges are supported (0 → 1.2V, 0 → 2.4V, 0 → 3.6V).
  
  (+) Up to eight analog single ended channels or four analog differential inputs or a mix of
both.
  
  (+) Temperature sensor conversion.
  
  (+) Battery level conversion up to 3.6V.
  
  (+) Continuous or single acquisition.
  
  (+) ADC Down Sampler for multi-purpose applications to improve analog performance
while off-loading the CPU (ratio adjustable from 1 to 128).
  
  (+) A watchdog feature to inform when data is outside thresholds.
  
  (+) DMA capability.
  
  (+) Interrupt sources with flags.

                     ##### How to use this driver #####
  ==============================================================================
    [..]

     *** Configuration of top level parameters related to ADC ***
     ============================================================
     [..]

    (#) Enable the ADC interface
        (++) As prerequisite, ADC clock must be configured at RCC top level.

        (++) Example:
               Into HAL_ADC_MspInit() (recommended code location) or with
               other device clock parameters configuration:
           (+++) __HAL_RCC_ADC_CLK_ENABLE();                  (mandatory)

    (#) ADC pins configuration
         (++) Enable the clock for the ADC GPIOs
              using macro __HAL_RCC_GPIOx_CLK_ENABLE()
         (++) Configure these ADC pins in analog mode
              using function HAL_GPIO_Init()

    (#) Optionally, in case of usage of ADC with interruptions:
         (++) Configure the NVIC for ADC
              using function HAL_NVIC_EnableIRQ(ADCx_IRQn)
         (++) Insert the ADC interruption handler function HAL_ADC_IRQHandler() 
              into the function of corresponding ADC interruption vector 
              ADC_IRQHandler().

    (#) Optionally, in case of usage of DMA:
         (++) Configure the DMA (DMA channel, mode normal or circular, ...)
              using function HAL_DMA_Init().
         (++) Configure the NVIC for DMA
              using function HAL_NVIC_EnableIRQ(DMAx_Channelx_IRQn)
         (++) Insert the ADC interruption handler function HAL_ADC_IRQHandler() 
              into the function of corresponding DMA interruption vector 
              DMAx_Channelx_IRQHandler().

     *** Configuration of ADC, channels parameters ***
     ================================================================
     [..]

    (#) Configure the ADC parameters using function HAL_ADC_Init().

    (#) Configure the channels using the function HAL_ADC_ConfigChannel().

    (#) Optionally, configure the analog watchdog parameters (channels
        monitored, thresholds, ...)
        using function HAL_ADC_WDGConfig().

     *** Execution of ADC conversions ***
     ====================================
     [..]

    (#) ADC driver can be used among three modes: polling, interruption,
        transfer by DMA.

        (++) ADC conversion by polling:
          (+++) Activate the ADC peripheral and start conversions
                using function HAL_ADC_Start()
          (+++) Wait for ADC conversion completion
                using function HAL_ADC_PollForConversion()
          (+++) Retrieve conversion results 
                using function HAL_ADC_GetValue()
          (+++) Stop conversion and disable the ADC peripheral 
                using function HAL_ADC_Stop()

        (++) ADC conversion by interruption: 
          (+++) Activate the ADC peripheral and start conversions
                using function HAL_ADC_Start_IT()
          (+++) Wait for ADC conversion completion by call of function
                HAL_ADC_ConvCpltCallback()
                (this function must be implemented in user program)
          (+++) Retrieve conversion results 
                using function HAL_ADC_GetValue()
          (+++) Stop conversion and disable the ADC peripheral 
                using function HAL_ADC_Stop_IT()

        (++) ADC conversion with transfer by DMA:
          (+++) Activate the ADC peripheral and start conversions
                using function HAL_ADC_Start_DMA()
          (+++) Wait for ADC conversion completion by call of function
                HAL_ADC_ConvCpltCallback() or HAL_ADC_ConvHalfCpltCallback()
                (these functions must be implemented in user program)
          (+++) Conversion results are automatically transferred by DMA into
                destination variable address.
          (+++) Stop conversion and disable the ADC peripheral 
                using function HAL_ADC_Stop_DMA()

     [..]

    (@) Callback functions must be implemented in user program:
      (+@) HAL_ADC_ErrorCallback()
      (+@) WatchdogAlertCallback() (callback of analog watchdog)
      (+@) HAL_ADC_ConvCpltCallback()
      (+@) HAL_ADC_ConvHalfCpltCallback

     *** Deinitialization of ADC ***
     ============================================================
     [..]

    (#) Disable the ADC interface
      (++) ADC clock can be hard reset and disabled at RCC top level.
        (++) Hard reset of ADC peripherals
             using macro __ADCx_FORCE_RESET(), __ADCx_RELEASE_RESET().
        (++) ADC clock disable
             using the equivalent macro/functions as configuration step.
             (+++) Example:
                   Into HAL_ADC_MspDeInit() (recommended code location).

    (#) ADC pins configuration
         (++) Disable the clock for the ADC GPIOs
              using macro __HAL_RCC_GPIOx_CLK_DISABLE()

    (#) Optionally, in case of usage of ADC with interruptions:
         (++) Disable the NVIC for ADC
              using function HAL_NVIC_EnableIRQ(ADCx_IRQn)

    (#) Optionally, in case of usage of DMA:
         (++) Deinitialize the DMA
              using function HAL_DMA_Init().
         (++) Disable the NVIC for DMA
              using function HAL_NVIC_EnableIRQ(DMAx_Channelx_IRQn)

    [..]
    
    *** Callback registration ***
    =============================================
    [..]

     The compilation flag USE_HAL_ADC_REGISTER_CALLBACKS, when set to 1,
     allows the user to configure dynamically the driver callbacks.
     Use Functions @ref HAL_ADC_RegisterCallback() to register an interrupt callback.
    [..]

     Function @ref HAL_ADC_RegisterCallback() allows to register following callbacks:
       (+) ConvCpltCallback               : ADC conversion complete callback
       (+) ConvHalfCpltCallback           : ADC conversion DMA half-transfer callback
       (+) WatchdogAlertCallback          : ADC analog watchdog callback
       (+) ErrorCallback                  : ADC error callback
       (+) MspInitCallback                : ADC Msp Init callback
       (+) MspDeInitCallback              : ADC Msp DeInit callback
     This function takes as parameters the HAL peripheral handle, the Callback ID
     and a pointer to the user callback function.
    [..]

     Use function @ref HAL_ADC_UnRegisterCallback to reset a callback to the default
     weak function.
    [..]

     @ref HAL_ADC_UnRegisterCallback takes as parameters the HAL peripheral handle,
     and the Callback ID.
     This function allows to reset following callbacks:
       (+) ConvCpltCallback               : ADC conversion complete callback
       (+) ConvHalfCpltCallback           : ADC conversion DMA half-transfer callback
       (+) WatchdogAlertCallback          : ADC analog watchdog callback
       (+) ErrorCallback                  : ADC error callback
       (+) MspInitCallback                : ADC Msp Init callback
       (+) MspDeInitCallback              : ADC Msp DeInit callback
     [..]

     By default, after the @ref HAL_ADC_Init() and when the state is @ref HAL_ADC_STATE_RESET
     all callbacks are set to the corresponding weak functions:
     examples @ref HAL_ADC_ConvCpltCallback(), @ref HAL_ADC_ErrorCallback().
     Exception done for MspInit and MspDeInit functions that are
     reset to the legacy weak functions in the @ref HAL_ADC_Init()/ @ref HAL_ADC_DeInit() only when
     these callbacks are null (not registered beforehand).
    [..]

     If MspInit or MspDeInit are not null, the @ref HAL_ADC_Init()/ @ref HAL_ADC_DeInit()
     keep and use the user MspInit/MspDeInit callbacks (registered beforehand) whatever the state.
     [..]

     Callbacks can be registered/unregistered in @ref HAL_ADC_STATE_READY state only.
     Exception done MspInit/MspDeInit functions that can be registered/unregistered
     in @ref HAL_ADC_STATE_READY or @ref HAL_ADC_STATE_RESET state,
     thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
    [..]

     Then, the user first registers the MspInit/MspDeInit user callbacks
     using @ref HAL_ADC_RegisterCallback() before calling @ref HAL_ADC_DeInit()
     or @ref HAL_ADC_Init() function.
     [..]

     When the compilation flag USE_HAL_ADC_REGISTER_CALLBACKS is set to 0 or
     not defined, the callback registration feature is not available and all callbacks
     are set to the corresponding weak functions.
  
  @endverbatim
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

/** @defgroup ADC ADC
  * @brief ADC HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAError(DMA_HandleTypeDef *hdma);

/* Exported functions --------------------------------------------------------*/

/** @defgroup ADC_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    ADC Initialization and Configuration functions
  *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the ADC. 
      (+) De-initialize the ADC.
@endverbatim
  * @{
  */

/**
  * @brief  Initialize the ADC peripheral according to  
  *         parameters specified in structure "ADC_InitTypeDef".
  * @note   As prerequisite, ADC clock must be configured at RCC top level
  *         (refer to description of RCC configuration for ADC
  *         in header of this file).
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the ADC MSP (HAL_ADC_MspInit()) only when
  *         coming from ADC state reset. Following calls to this function can
  *         be used to reconfigure some parameters of ADC_InitTypeDef  
  *         structure on the fly, without modifying MSP configuration. If ADC  
  *         MSP has to be modified again, HAL_ADC_DeInit() must be called
  *         before HAL_ADC_Init().
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_InitTypeDef".
  * @param hadc ADC handle
  * @retval HAL status
  */
void HAL_ADC_StructInit(ADC_HandleTypeDef* hadc)
{
  hadc->Instance = ADC;
  hadc->Init.DataRatio = ADC_DS_RATIO_01;
  hadc->Init.DataWidth = ADC_DS_DATA_WIDTH_12_BIT;
  hadc->Init.InvertOutputBitMode = ADC_INVERT_OUTBIT_SING;
  hadc->Init.OverrunMode = ADC_NEW_DATA_IS_KEPT;
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
  hadc->Init.SampleRate = LL_ADC_SAMPLE_RATE_0;
  hadc->Init.SampleRateMsb = LL_ADC_SAMPLE_RATE_MSB_4;
#else
  hadc->Init.SampleRate = ADC_SAMPLE_RATE_16;
#endif
  hadc->Init.SamplingMode = ADC_SAMPLING_AT_START;
  hadc->Init.SequenceLength = ADC_SEQ_LEN_01;
  
}


/**
  * @brief  Initialize the ADC peripheral according to  
  *         parameters specified in structure "ADC_InitTypeDef".
  * @note   As prerequisite, ADC clock must be configured at RCC top level
  *         (refer to description of RCC configuration for ADC
  *         in header of this file).
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the ADC MSP (HAL_ADC_MspInit()) only when
  *         coming from ADC state reset. Following calls to this function can
  *         be used to reconfigure some parameters of ADC_InitTypeDef  
  *         structure on the fly, without modifying MSP configuration. If ADC  
  *         MSP has to be modified again, HAL_ADC_DeInit() must be called
  *         before HAL_ADC_Init().
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_InitTypeDef".
  * @param hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check ADC handle */
  if(hadc == NULL) {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
      assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
      assert_param(IS_ADC_SAMPLERATE(hadc.Init.SampleRate));
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
      assert_param(IS_ADC_SAMPLERATE_MSB(hadc.Init.SampleRateMsb));
#endif
      assert_param(IS_ADC_SAMPLINGMODE(hadc.Init.SamplingMode));
      assert_param(IS_ADC_OVERRUNMODE(hadc.Init.OverrunMode));
      assert_param(IS_ADC_INVERT_OUTBIT(hadc.Init.InvertOutputBitMode));
      assert_param(IS_ADC_INVERT_OUTBIT(hadc.Init.DataWidth));
      assert_param(IS_ADC_INVERT_OUTBIT(hadc.Init.DataRatio));
      assert_param(IS_ADC_INVERT_OUTBIT(hadc.Init.SequenceLength));
      // assert_param(IS_ADC_CONVERSIONTYPE(hadc->Init.ConversionType));
  
  /* Actions performed only if ADC is coming from state reset:                */
  /* - Initialization of ADC MSP                                              */
  if(hadc->State == HAL_ADC_STATE_RESET)
  {
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
    /* Init the ADC Callback settings */
    hadc->ConvCpltCallback              = HAL_ADC_ConvCpltCallback;                 /* Legacy weak callback */
    hadc->ConvHalfCpltCallback          = HAL_ADC_ConvHalfCpltCallback;             /* Legacy weak callback */
    hadc->WatchdogAlertCallback         = HAL_ADC_WatchdogAlertCallback;         /* Legacy weak callback */
    hadc->ErrorCallback                 = HAL_ADC_ErrorCallback;                    /* Legacy weak callback */
    
    if (hadc->MspInitCallback == NULL) {
      hadc->MspInitCallback = HAL_ADC_MspInit; /* Legacy weak MspInit  */
    }
    
    /* Init the low level hardware */
    hadc->MspInitCallback(hadc);
#else
    /* Init the low level hardware */
    HAL_ADC_MspInit(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
    
    /* Set ADC error code to none */
    ADC_CLEAR_ERRORCODE(hadc);
    
    /* Initialize Lock */
    hadc->Lock = HAL_UNLOCKED;
  }
  
#if defined (ADC_CTRL_ADC_LDO_ENA)
  if(LL_ADC_IsLDOEnabled(hadc->Instance) == 0UL) {
    /* Enable ADC internal voltage regulator */
    LL_ADC_LDOEnable(hadc->Instance);
  }
#endif

  /* Configuration of ADC parameters if there is no conversion on going       */
  /* (ADC may already be enabled at this point if HAL_ADC_Init() is           */
  /* called to update a parameter on the fly).                                */
  if( ((hadc->State & HAL_ADC_STATE_ERROR_INTERNAL) == 0UL) && (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL)) {
    /* Set ADC state */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_BUSY, // HAL_ADC_STATE_BUSY non esiste
                      HAL_ADC_STATE_BUSY_INTERNAL);
    
    /* Configuration of common ADC parameters                                 */
    
    /* Parameters update conditioned to ADC state:                            */
    /* Parameters that can be updated only when ADC is disabled:              */
    // if (LL_ADC_IsEnabled(hadc->Instance) == 0UL) {
    //   /* Enable the ADC */
    //   LL_ADC_Enable(ADC);
    // }
    
    /* Configuration of ADC:                                                  */
    /*  - Sample Rate                              Init.SampleRate            */
    /*  - Sample Rate MSB                          Init.SampleRateMsb         */
    /*  - Sampling Mode                            Init.SamplingMode          */
    /*  - Overrun Mode                             Init.OverrunMode           */
    /*  - Invert Output Bit Mode                   Init.InvertOutputBitMode   */
    /*  - Conversion Type                          Init.ConversionType        */
    
    /* Configure the sample rate */
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
    LL_ADC_SetSampleRate(hadc->Instance, hadc->Init.SampleRateMsb, hadc->Init.SampleRate);
#else
    LL_ADC_SetSampleRate(hadc->Instance, hadc->Init.SampleRate);
#endif

    /* Configure the input sampling mode */
    LL_ADC_InputSamplingMode(hadc->Instance, hadc->Init.SamplingMode);

    /* Configure the overrun mode for the output data */
    // if(hadc->Init.ConversionType == ADC_CONVERSION_WITH_DS) {
    LL_ADC_SetOverrunDS(hadc->Instance, hadc->Init.OverrunMode);
    // }
    // else {
    //   LL_ADC_SetOverrunDF(hadc->Instance, hadc->Init.OverrunMode);
    // }

    /* Configure the bit to bit inversion (1' complement) mode */
    if(hadc->Init.InvertOutputBitMode == ADC_INVERT_OUTBIT_NONE) {
      LL_ADC_InvertOutputBitDiffModeDisable(hadc->Instance);
      LL_ADC_InvertOutputBitSingleNegModeDisable(hadc->Instance);
    }
    else if(hadc->Init.InvertOutputBitMode == ADC_INVERT_OUTBIT_DIFF) {
      LL_ADC_InvertOutputBitDiffModeEnable(hadc->Instance);
      LL_ADC_InvertOutputBitSingleNegModeDisable(hadc->Instance);
    }
    else if(hadc->Init.InvertOutputBitMode == ADC_INVERT_OUTBIT_SING) {
      LL_ADC_InvertOutputBitDiffModeDisable(hadc->Instance);
      LL_ADC_InvertOutputBitSingleNegModeEnable(hadc->Instance);
    }
    else {
      LL_ADC_InvertOutputBitDiffModeEnable(hadc->Instance);
      LL_ADC_InvertOutputBitSingleNegModeEnable(hadc->Instance);
    }

    LL_ADC_ConfigureDSDataOutput(hadc->Instance, hadc->Init.DataWidth, hadc->Init.DataRatio);

    LL_ADC_SetSequenceLength(hadc->Instance, hadc->Init.SequenceLength);

    /* Configure the overrun mode for the output data */
    // if(hadc->Init.ConversionType == ADC_CONVERSION_WITH_DS) {
      /* Configure the operation mode as ADC mode (static/low frequency signal) thourgh the Down Sampler (DS) */
      LL_ADC_SetADCMode(ADC, LL_ADC_OP_MODE_ADC);
    // }
    // else {
      /* Configure the operation mode as Full ADC mode through the Decimation Filter (DF) */
    //   LL_ADC_SetADCMode(ADC, LL_ADC_OP_MODE_FULL);
    // }

    /* Initialize the ADC state */
    /* Clear HAL_ADC_STATE_BUSY_INTERNAL bit, set HAL_ADC_STATE_READY bit */
    ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_BUSY_INTERNAL, HAL_ADC_STATE_READY);
  }
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
    
    tmp_hal_status = HAL_ERROR;
  }
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Deinitialize the ADC peripheral registers to their default reset
  *         values, with deinitialization of the ADC MSP.
  * @param hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  
  /* Check ADC handle */
  if(hadc == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Set ADC state */
  SET_BIT(hadc->State, HAL_ADC_STATE_BUSY_INTERNAL);
  
  /* Stop potential conversion on going */
  tmp_hal_status = ADC_ConversionStop(hadc);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmp_hal_status == HAL_OK) {
    /* Disable the ADC peripheral */
    tmp_hal_status = ADC_Disable(hadc);

    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK) {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }
  
  /* Note: HAL ADC deInit is done independently of ADC conversion stop        */
  /*       and disable return status. In case of status fail, attempt to      */
  /*       perform deinitialization anyway and it is up user code in          */
  /*       in HAL_ADC_MspDeInit() to reset the ADC peripheral using           */
  /*       system RCC hard reset.                                             */
  
  /* ========== Reset ADC registers ========== */
#if defined(ADC_IRQ_EN_MASK)
  /* Reset register IER */
  __HAL_ADC_DISABLE_IT(hadc->Instance, ADC_IRQ_EN_MASK);
#endif
#if defined(ADC_IRQ_FLAGS_MASK)
  /* Reset register ISR */
  __HAL_ADC_CLEAR_FLAG(hadc->Instance, ADC_IRQ_FLAGS_MASK);
#endif
  /* Reset all the registers */
  /* ...                     */

  /* DeInit the low level hardware. 
  
     For example:
    __HAL_RCC_ADC_FORCE_RESET();
    __HAL_RCC_ADC_RELEASE_RESET();
    __HAL_RCC_ADC_CLK_DISABLE();
    
  */

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  if (hadc->MspDeInitCallback == NULL)
  {
    hadc->MspDeInitCallback = HAL_ADC_MspDeInit; /* Legacy weak MspDeInit  */
  }
  
  /* DeInit the low level hardware: RCC clock, NVIC */
  hadc->MspDeInitCallback(hadc);
#else
  /* DeInit the low level hardware: RCC clock, NVIC */
  HAL_ADC_MspDeInit(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
  
  /* Set ADC error code to none */
  ADC_CLEAR_ERRORCODE(hadc);
  
  /* Set ADC state */
  hadc->State = HAL_ADC_STATE_RESET;
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Initialize the ADC MSP.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MspInit must be implemented in the user file.
   */ 
}

/**
  * @brief  DeInitialize the ADC MSP.
  * @param hadc ADC handle
  * @note   All ADC instances use the same core clock at RCC level, disabling
  *         the core clock reset all ADC instances).
  * @retval None
  */
__weak void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MspDeInit must be implemented in the user file.
   */ 
}

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User ADC Callback
  *         To be used instead of the weak predefined callback
  * @param  hadc Pointer to a ADC_HandleTypeDef structure that contains
  *                the configuration information for the specified ADC.
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_ADC_CONVERSION_COMPLETE_CB_ID      ADC conversion complete callback ID
  *          @arg @ref HAL_ADC_CONVERSION_HALF_CB_ID          ADC conversion complete callback ID
  *          @arg @ref HAL_ADC_WATCHDOG_ALERT_CB_ID           ADC watchdog callback ID
  *          @arg @ref HAL_ADC_ERROR_CB_ID                    ADC error callback ID
  *          @arg @ref HAL_ADC_MSPINIT_CB_ID                  ADC Msp Init callback ID
  *          @arg @ref HAL_ADC_MSPDEINIT_CB_ID                ADC Msp DeInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_RegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID, pADC_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  if (pCallback == NULL) {
    /* Update the error code */
    hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }
  
  if ((hadc->State & HAL_ADC_STATE_READY) != 0UL) {
    switch (CallbackID) {
      case HAL_ADC_CONVERSION_COMPLETE_CB_ID :
        hadc->ConvCpltCallback = pCallback;
        break;
      
      case HAL_ADC_CONVERSION_HALF_CB_ID :
        hadc->ConvHalfCpltCallback = pCallback;
        break;
      
      case HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID :
        hadc->WatchdogAlertCallback = pCallback;
        break;
      
      case HAL_ADC_ERROR_CB_ID :
        hadc->ErrorCallback = pCallback;
        break;
      
      case HAL_ADC_MSPINIT_CB_ID :
        hadc->MspInitCallback = pCallback;
        break;
      
      case HAL_ADC_MSPDEINIT_CB_ID :
        hadc->MspDeInitCallback = pCallback;
        break;
      
      default :
        /* Update the error code */
        hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status = HAL_ERROR;
        break;
    }
  }
  else if (HAL_ADC_STATE_RESET == hadc->State) {
    switch (CallbackID) {
      case HAL_ADC_MSPINIT_CB_ID :
        hadc->MspInitCallback = pCallback;
        break;
      
      case HAL_ADC_MSPDEINIT_CB_ID :
        hadc->MspDeInitCallback = pCallback;
        break;
      
      default :
        /* Update the error code */
        hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;
      
        /* Return error status */
        status = HAL_ERROR;
        break;
    }
  }
  else {
    /* Update the error code */
    hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;
    
    /* Return error status */
    status =  HAL_ERROR;
  }
  
  return status;
}

/**
  * @brief  Unregister a ADC Callback
  *         ADC callback is redirected to the weak predefined callback
  * @param  hadc Pointer to a ADC_HandleTypeDef structure that contains
  *                the configuration information for the specified ADC.
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_ADC_CONVERSION_COMPLETE_CB_ID      ADC conversion complete callback ID
  *          @arg @ref HAL_ADC_CONVERSION_HALF_CB_ID          ADC conversion complete callback ID
  *          @arg @ref HAL_ADC_WATCHDOG_ALERT_CB_ID           ADC watchdog callback ID
  *          @arg @ref HAL_ADC_ERROR_CB_ID                    ADC error callback ID
  *          @arg @ref HAL_ADC_MSPINIT_CB_ID                  ADC Msp Init callback ID
  *          @arg @ref HAL_ADC_MSPDEINIT_CB_ID                ADC Msp DeInit callback ID
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_UnRegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  if ((hadc->State & HAL_ADC_STATE_READY) != 0UL) {
    switch (CallbackID) {
      case HAL_ADC_CONVERSION_COMPLETE_CB_ID :
        hadc->ConvCpltCallback = HAL_ADC_ConvCpltCallback;
        break;
      
      case HAL_ADC_CONVERSION_HALF_CB_ID :
        hadc->ConvHalfCpltCallback = HAL_ADC_ConvHalfCpltCallback;
        break;
      
      case HAL_ADC_WATCHDOG_ALERT_CB_ID :
        hadc->WatchdogAlertCallback = HAL_ADC_WatchdogAlertCallback;
        break;
      
      case HAL_ADC_ERROR_CB_ID :
        hadc->ErrorCallback = HAL_ADC_ErrorCallback;
        break;
      
      case HAL_ADC_MSPINIT_CB_ID :
        hadc->MspInitCallback = HAL_ADC_MspInit; /* Legacy weak MspInit       */
        break;
      
      case HAL_ADC_MSPDEINIT_CB_ID :
        hadc->MspDeInitCallback = HAL_ADC_MspDeInit; /* Legacy weak MspDeInit */
        break;
      
      default :
        /* Update the error code */
        hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;
        
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_ADC_STATE_RESET == hadc->State) {
    switch (CallbackID) {
      case HAL_ADC_MSPINIT_CB_ID :
        hadc->MspInitCallback = HAL_ADC_MspInit;                   /* Legacy weak MspInit              */
        break;
        
      case HAL_ADC_MSPDEINIT_CB_ID :
        hadc->MspDeInitCallback = HAL_ADC_MspDeInit;               /* Legacy weak MspDeInit            */
        break;
        
      default :
        /* Update the error code */
        hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;
        
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else {
    /* Update the error code */
    hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;
    
    /* Return error status */
    status =  HAL_ERROR;
  }
  
  return status;
}

#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group2 ADC Input and Output operation functions
 *  @brief    ADC IO operation functions 
 *
@verbatim   
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) Poll for conversion complete.
      (+) Poll for conversion event.
      (+) Get result of channel conversion.
      (+) Start conversion and enable interruptions.
      (+) Stop conversion and disable interruptions.
      (+) Handle ADC interrupt request
      (+) Start conversion and enable DMA transfer.
      (+) Stop conversion and disable ADC DMA transfer.
@endverbatim
  * @{
  */

/**
  * @brief  Enable ADC, start conversion.
  * @note   Interruptions enabled in this function: None.
  * @param hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Perform ADC enable and conversion start if no conversion is on going */
  if (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL) {
    /* Process locked */
    __HAL_LOCK(hadc);
    
    /* Enable the ADC peripheral */
    tmp_hal_status = ADC_Enable(hadc);
    
    /* Start conversion if ADC is effectively enabled */
    if (tmp_hal_status == HAL_OK) {
      /* Set ADC state                                                        */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_READY | HAL_ADC_STATE_EOC | HAL_ADC_STATE_OVR,
                        HAL_ADC_STATE_BUSY);
      
      /* Set ADC error code */
      /* Check if a conversion is on going on ADC group injected */
      /* Reset all ADC error code fields */
      ADC_CLEAR_ERRORCODE(hadc); 
    }
    
    /* Clear ADC group regular conversion flag and overrun flag               */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc->Instance, (ADC_IRQ_FLAG_EOS | ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_OVRDS));
    
    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential         */
    /* interruption, to let the process to ADC IRQ Handler.                 */
    __HAL_UNLOCK(hadc);
    
    /* Start ADC conversion */
    LL_ADC_StartConversion(hadc->Instance);
  }
  else {
    tmp_hal_status = HAL_BUSY;
  }
  
  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Stop ADC conversion and disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential conversion.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Stop potential conversion on going, on ADC groups regular and injected */
  tmp_hal_status = ADC_ConversionStop(hadc);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmp_hal_status == HAL_OK) {
    /* Disable the ADC peripheral */
    tmp_hal_status = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK) {
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_READY);
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Wait for a conversion to be completed.
  * @note   ADC conversion flags EOS (end of sequence) and EOC (end of
  *         conversion) are cleared by this function.
  * @note   This function cannot be used in a particular setup: ADC configured 
  *         in DMA mode and polling for end of each conversion.
  *         In this case, DMA resets the flag EOC and polling cannot be
  *         performed on each conversion. Nevertheless, polling can still 
  *         be performed on the complete sequence.
  * @param hadc ADC handle
  * @param Timeout Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Get tick count */
  tickstart = HAL_GetTick();
  
  /* Wait until End of unitary conversion or sequence conversions flag is raised */
  while(__HAL_ADC_GET_FLAG(hadc->Instance, ADC_IRQ_FLAG_EODS) == 0UL) {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY) {
      if(((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0UL)) {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* Update ADC state machine */
  SET_BIT(hadc->State, HAL_ADC_STATE_EOC);
  
  /* Check whether end of sequence is reached */
  if( __HAL_ADC_GET_FLAG(hadc->Instance, ADC_IRQ_FLAG_EOS)) {
    /* Set ADC state */
    CLEAR_BIT(hadc->State, HAL_ADC_STATE_BUSY);
  }
  
  /* Clear polled flag */
  __HAL_ADC_CLEAR_FLAG(hadc->Instance, (ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_EOS));
  
  /* Return function status */
  return HAL_OK;
}

#if 0
/**
  * @brief  Poll for ADC event.
  * @param hadc ADC handle
  * @param EventType the ADC event type.
  *          This parameter can be one of the following values:
  *            @arg @ref ADC_AWD_EVENT   ADC watchdog event
  *            @arg @ref ADC_OVR_EVENT    ADC Overrun event
  * @param Timeout Timeout value in millisecond.
  * @note   The relevant flag is cleared if found to be set, except for ADC_IRQ_FLAG_OVRDS.
  *         Indeed, the latter is reset only if hadc->Init.Overrun field is set  
  *         to ADC_OVR_DATA_OVERWRITTEN. Otherwise, data register may be potentially overwritten 
  *         by a new converted data as soon as OVR is cleared.
  *         To reset OVR flag once the preserved data is retrieved, the user can resort
  *         to macro __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_OVRDS); 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_EVENT_TYPE(EventType));
  
  /* Get tick count */
  tickstart = HAL_GetTick();
  
  /* Check selected event flag */
  while(__HAL_ADC_GET_FLAG(hadc->Instance, EventType) == 0UL) {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY) {
      if(((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0UL)) {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  switch(EventType) {
  
  /* Check analog watchdog flag */
  case ADC_AWD_EVENT:
    /* Set ADC state */
    SET_BIT(hadc->State, HAL_ADC_STATE_AWD);
    
    /* Clear ADC analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc->Instance, ADC_IRQ_FLAG_AWD);
    
    break;
  
  /* Overrun event */
  default: /* Case ADC_OVR_EVENT */
    /* If overrun is set to overwrite previous data, overrun event is not     */
    /* considered as an error.                                                */
    if (hadc->Init.Overrun == ADC_NEW_DATA_IS_KEPT) {
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_OVR);
        
      /* Set ADC error code to overrun */
      SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_OVR);
    }
    else {
      /* Clear ADC Overrun flag only if Overrun is set to ADC_OVR_DATA_OVERWRITTEN
         otherwise, data register is potentially overwritten by new converted data as soon
         as OVR is cleared. */
      __HAL_ADC_CLEAR_FLAG(hadc->Instance, ADC_IRQ_FLAG_OVRDS);
    }
    break;
  }
  
  /* Return function status */
  return HAL_OK;
}
#endif

/**
  * @brief  Enable ADC and start conversion with interruption.
  * @note   Interruptions enabled in this function according to initialization
  *         setting : EOC (end of conversion), EOS (end of sequence), 
  *         OVR overrun.
  *         Each of these interruptions has its dedicated callback function.
  * @note   To guarantee a proper reset of all interruptions once all the needed
  *         conversions are obtained, HAL_ADC_Stop_IT() must be called to ensure 
  *         a correct stop of the IT-based conversions.
  * @param hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Perform ADC enable and conversion start if no conversion is on going */
  if (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL) {
    /* Process locked */
    __HAL_LOCK(hadc);
    
    /* Enable the ADC peripheral */
    tmp_hal_status = ADC_Enable(hadc);
    
    /* Start conversion if ADC is effectively enabled */
    if (tmp_hal_status == HAL_OK) {
      /* Set ADC state                                                        */
      /* - Clear state bitfield related to regular group conversion results   */
      /* - Set state bitfield related to regular operation                    */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_READY | HAL_ADC_STATE_EOC | HAL_ADC_STATE_OVR,
                        HAL_ADC_STATE_BUSY);

      /* Reset all ADC error code fields */
      ADC_CLEAR_ERRORCODE(hadc); 

      /* Clear ADC group regular conversion flag and overrun flag               */
      /* (To ensure of no unknown state from potential previous ADC operations) */
      __HAL_ADC_CLEAR_FLAG(hadc->Instance, (ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_EOS | ADC_IRQ_FLAG_OVRDS));
      
      /* Process unlocked */
      /* Unlock before starting ADC conversions: in case of potential         */
      /* interruption, to let the process to ADC IRQ Handler.                 */
      __HAL_UNLOCK(hadc);
      
      /* Disable all interruptions before enabling the desired ones */
      __HAL_ADC_DISABLE_IT(hadc->Instance, (ADC_IRQ_EN_EODS | ADC_IRQ_EN_EOS | ADC_IRQ_EN_OVRDS));
      
      /* Enable ADC end of conversion interrupt */
      __HAL_ADC_ENABLE_IT(hadc->Instance, ADC_IRQ_EN_EODS);

      /* Enable ADC overrun interrupt */
      /* If hadc->Init.Overrun is set to ADC_OVR_DATA_PRESERVED, only then is
         ADC_IRQ_EN_OVRDS enabled; otherwise data overwrite is considered as normal
         behavior and no CPU time is lost for a non-processed interruption */
      if (hadc->Init.OverrunMode == ADC_NEW_DATA_IS_KEPT) {
        __HAL_ADC_ENABLE_IT(hadc->Instance, ADC_IRQ_EN_OVRDS);  
      }
      
      /* Enable conversion of regular group.                                  */
      /* If software start has been selected, conversion starts immediately.  */
      /* If external trigger has been selected, conversion will start at next */
      /* trigger event.                                                       */
      /* Start ADC group regular conversion */
      LL_ADC_StartConversion(hadc->Instance);
    }
    else {
      /* Process unlocked */
      __HAL_UNLOCK(hadc);
    }
    
  }
  else {
    tmp_hal_status = HAL_BUSY;
  }
  
  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable interrution of 
  *         end-of-conversion, disable ADC peripheral.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion on going, on ADC groups regular and injected */
  tmp_hal_status = ADC_ConversionStop(hadc);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmp_hal_status == HAL_OK) {
    /* Disable ADC end of conversion interrupt for regular group */
    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc->Instance, (ADC_IRQ_EN_EODS | ADC_IRQ_EN_EOS | ADC_IRQ_EN_OVRDS));
    
    /* 2. Disable the ADC peripheral */
    tmp_hal_status = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK) {
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_READY);
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Enable ADC, start conversion and transfer result through DMA.
  * @note   Interruptions enabled in this function:
  *         overrun (if applicable), DMA half transfer, DMA transfer complete. 
  *         Each of these interruptions has its dedicated callback function.
  *         The ADC continuous mode is enabled in this DMA acquisition mode.
  * @param hadc ADC handle
  * @param pData Destination Buffer address.
  * @param Length Number of data to be transferred from ADC peripheral to memory
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
  HAL_StatusTypeDef tmp_hal_status;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Perform ADC enable and conversion start if no conversion is on going */
  if (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL) {
    /* Process locked */
    __HAL_LOCK(hadc);
    
      /* Enable the ADC continuous mode */
      LL_ADC_ContinuousModeEnable(hadc->Instance);
      /* Enable the ADC peripheral */
      tmp_hal_status = ADC_Enable(hadc);
    
      /* Start conversion if ADC is effectively enabled */
      if (tmp_hal_status == HAL_OK) {
        /* Set ADC state                                                        */
        /* - Clear state bitfield related to regular group conversion results   */
        /* - Set state bitfield related to regular operation                    */
        ADC_STATE_CLR_SET(hadc->State,
                          HAL_ADC_STATE_READY | HAL_ADC_STATE_EOC | HAL_ADC_STATE_OVR,
                          HAL_ADC_STATE_BUSY);
        
        /* Reset all ADC error code fields */
        ADC_CLEAR_ERRORCODE(hadc); 
        
        /* Set the DMA transfer complete callback */
        hadc->DMA_Handle->XferCpltCallback = ADC_DMAConvCplt;
        
        /* Set the DMA half transfer complete callback */
        hadc->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;
        
        /* Set the DMA error callback */
        hadc->DMA_Handle->XferErrorCallback = ADC_DMAError;
        
        /* Manage ADC and DMA start: ADC overrun interruption, DMA start,     */
        /* ADC start (in case of SW start):                                   */
        
        /* Clear conversion flag and overrun flag                             */
        /* (To ensure of no unknown state from potential previous ADC         */
        /* operations)                                                        */
        __HAL_ADC_CLEAR_FLAG(hadc->Instance, (ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_EOS | ADC_IRQ_FLAG_OVRDS));
        
        /* Process unlocked */
        /* Unlock before starting ADC conversions: in case of potential         */
        /* interruption, to let the process to ADC IRQ Handler.                 */
        __HAL_UNLOCK(hadc);
        
        /* With DMA, overrun event is always considered as an error even if 
           hadc->Init. Overrun is set to ADC_OVR_DATA_OVERWRITTEN. Therefore,  
           ADC_IRQ_EN_OVRDS is enabled. */
        __HAL_ADC_ENABLE_IT(hadc->Instance, ADC_IRQ_EN_OVRDS);
        
        /* Enable ADC DMA mode */
        LL_ADC_DMAModeDSEnable(hadc->Instance);
        
        /* Start the DMA channel */
        if (HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DS_DATAOUT, (uint32_t)pData, Length) != HAL_OK) {
          /* Set error code to DMA */
          hadc->ErrorCode = HAL_ADC_ERROR_DMA;

          /* Process Unlocked */
          __HAL_UNLOCK(hadc);
          
          return HAL_ERROR;
        }
        /* Enable conversion of regular group.                                  */
        /* If software start has been selected, conversion starts immediately.  */
        /* If external trigger has been selected, conversion will start at next */
        /* trigger event.                                                       */
        /* Start ADC group regular conversion */
        LL_ADC_StartConversion(hadc->Instance);
      }
      else {
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
      }
  }
  else {
    tmp_hal_status = HAL_BUSY;
  }
  
  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential
  *         conversion on ADC group injected. If ADC group injected is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential ADC group regular conversion on going */
  LL_ADC_ContinuousModeDisable(hadc->Instance);
  tmp_hal_status = ADC_ConversionStop(hadc);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmp_hal_status == HAL_OK) {
    
    /* Abort the ADC DMA channel */
    if (hadc->DMA_Handle != NULL)
    {
      /* Disable ADC DMA (ADC DMA configuration of continous requests is kept) */
      LL_ADC_DMAModeDSDisable(hadc->Instance);
      
      if (HAL_DMA_Abort_IT(hadc->DMA_Handle) != HAL_OK)
      {
        if (HAL_DMA_GetError(hadc->DMA_Handle) == HAL_DMA_ERROR_TIMEOUT)
        {
          /* Set error code to DMA */
          hadc->ErrorCode = HAL_ADC_ERROR_DMA;
          
          /* Process Unlocked */
          __HAL_UNLOCK(hadc);
          
          return HAL_TIMEOUT;
        }
      }
    }
    
    /* Disable the DMA channel (in case of DMA in circular mode or stop       */
    /* while DMA transfer is on going)                                        */
    if(hadc->DMA_Handle->State == HAL_DMA_STATE_BUSY) {
      //      tmp_hal_status = HAL_DMA_Abort(hadc->DMA_Handle);
      
      /* Check if DMA channel effectively disabled */
      if (tmp_hal_status != HAL_OK) {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_DMA);
      }
    }
    
    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc->Instance, ADC_IRQ_EN_OVRDS);
    
    /* 2. Disable the ADC peripheral */
    /* Update "tmp_hal_status" only if DMA channel disabling passed,          */
    /* to keep in memory a potential failing status.                          */
    if (tmp_hal_status == HAL_OK) {
      tmp_hal_status = ADC_Disable(hadc);
    }
    else {
      (void)ADC_Disable(hadc);
    }
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK) {
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_READY);
    }
    
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Get ADC conversion result (raw value).
  * @note   Occurrence of flag EOS rising:
  *          - If sequencer is composed of 1 rank, flag EOS is equivalent
  *            to flag EOC.
  *          - If sequencer is composed of several ranks, during the scan
  *            sequence flag EOC only is raised, at the end of the scan sequence
  *            both flags EOC and EOS are raised.
  *         To clear this flag, either use function:
  *         in programming model IT: @ref HAL_ADC_IRQHandler(), in programming
  *         model polling: @ref HAL_ADC_PollForConversion()
  *         or @ref __HAL_ADC_CLEAR_FLAG(&hadc, ADC_IRQ_FLAG_EOS).
  * @param hadc ADC handle
  * @retval ADC group regular conversion data
  */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Return ADC converted value */ 
  return LL_ADC_DSGetOutputData(hadc->Instance);
}


/**
  * @brief  Handle ADC interrupt request.
  * @param hadc ADC handle
  * @retval None
  */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc)
{
  uint32_t overrun_error = 0UL; /* flag set if overrun occurrence has to be considered as an error */
  uint32_t tmp_ier = LL_ADC_GetActiveFlags(hadc->Instance);
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* ====== Check ADC end of unitary conversion sequence conversions ===== */
  if( ( LL_ADC_IsEnabledIT(hadc->Instance, ADC_IRQ_FLAG_EODS) && ((tmp_ier & ADC_IRQ_EN_EODS) == ADC_IRQ_EN_EODS)) ||
      ( LL_ADC_IsEnabledIT(hadc->Instance, ADC_IRQ_FLAG_EOS) && ((tmp_ier & ADC_IRQ_EN_EOS) == ADC_IRQ_EN_EOS)) ) {
    /* Update state machine on conversion status if not in error state */
    if ((hadc->State & HAL_ADC_STATE_ERROR_INTERNAL) == 0UL) {
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_EOC);
    }
    
      /* Carry on if continuous mode is disabled */
      if (LL_ADC_IsContinuousModeEnabled(hadc->Instance)) {
        /* If End of Sequence is reached, disable interrupts */
        if( __HAL_ADC_GET_FLAG(hadc->Instance, ADC_IRQ_FLAG_EOS) ) {
          /* Allowed to modify bits ADC_IRQ_EN_EODS/ADC_IRQ_EN_EOS only if bit         */
          if (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL) {
            /* Disable ADC end of sequence conversion interrupt */
            /* Note: Overrun interrupt was enabled with EOC interrupt in      */
            /* HAL_Start_IT(), but is not disabled here because can be used   */
            /* by overrun IRQ process below.                                  */
            __HAL_ADC_DISABLE_IT(hadc->Instance, ADC_IRQ_EN_EODS | ADC_IRQ_EN_EOS);
            
            /* Set ADC state */
            CLEAR_BIT(hadc->State, HAL_ADC_STATE_BUSY);
          }
          else {
            /* Change ADC state to error state */
            SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
            
            /* Set ADC error code to ADC IP internal error */
            SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
          }
        }
      }
    
    /* Conversion complete callback */
    /* Note: Into callback function "HAL_ADC_ConvCpltCallback()",             */
    /*       to determine if conversion has been triggered from EOC or EOS,   */
    /*       possibility to use:                                              */
    /*        " if( __HAL_ADC_GET_FLAG(&hadc, ADC_IRQ_FLAG_EOS)) "                */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
    hadc->ConvCpltCallback(hadc);
#else
    HAL_ADC_ConvCpltCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
    
    /* Clear regular group conversion flag */
    /* Note: in case of overrun set to ADC_OVR_DATA_PRESERVED, end of         */
    /*       conversion flags clear induces the release of the preserved data.*/
    /*       Therefore, if the preserved data value is needed, it must be     */
    /*       read preliminarily into HAL_ADC_ConvCpltCallback().              */
    __HAL_ADC_CLEAR_FLAG(hadc->Instance, (ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_EOS) );
  }
  
  /* ========== Check Analog watchdog 1 flag ========== */
  if ( LL_ADC_IsEnabledIT(hadc->Instance, ADC_IRQ_FLAG_AWD) && ((tmp_ier & ADC_IRQ_FLAG_AWD) == ADC_IRQ_FLAG_AWD)) {
    /* Set ADC state */
    SET_BIT(hadc->State, HAL_ADC_STATE_AWD);
    
    /* Level out of window 1 callback */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
    hadc->WatchdogAlertCallback(hadc);
#else
    HAL_ADC_WatchdogAlertCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
    
    /* Clear ADC analog watchdog flag */ 
    __HAL_ADC_CLEAR_FLAG(hadc->Instance, ADC_IRQ_FLAG_AWD);
  }
  
  /* ========== Check Overrun flag ========== */
  if ( LL_ADC_IsEnabledIT(hadc->Instance, ADC_IRQ_FLAG_OVRDS) && ((tmp_ier & ADC_IRQ_EN_OVRDS) == ADC_IRQ_EN_OVRDS)) {
    /* If overrun is set to overwrite previous data (default setting),        */
    /* overrun event is not considered as an error.                           */
    /* Exception for usage with DMA overrun event always considered as an     */
    /* error.                                                                 */
    if (hadc->Init.OverrunMode == ADC_NEW_DATA_IS_KEPT) {
      overrun_error = 1UL;
    }
    else {
      /* Check DMA configuration */
      if (LL_ADC_IsDMAModeDSEnabled(hadc->Instance)) {
        overrun_error = 1UL;
      }
    }

    if (overrun_error == 1UL) {
      /* Change ADC state to error state */
      SET_BIT(hadc->State, HAL_ADC_STATE_OVR);
      
      /* Set ADC error code to overrun */
      SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_OVR);
      
      /* Error callback */
      /* Note: In case of overrun, ADC conversion data is preserved until     */
      /*       flag OVR is reset.                                             */
      /*       Therefore, old ADC conversion data can be retrieved in         */
      /*       function "HAL_ADC_ErrorCallback()".                            */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
      hadc->ErrorCallback(hadc);
#else
      HAL_ADC_ErrorCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
    }
    
    /* Clear ADC overrun flag */
    __HAL_ADC_CLEAR_FLAG(hadc->Instance, ADC_IRQ_FLAG_OVRDS);
  }
  
}


/**
  * @brief  Conversion complete callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Conversion DMA half-transfer callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvHalfCpltCallback must be implemented in the user file.
  */
}


/**
  * @brief  Analog watchdog callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_WatchdogAlertCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_WatchdogAlertCallback must be implemented in the user file.
  */
}


/**
  * @brief  ADC error callback in non-blocking mode
  *         (ADC conversion with interruption or transfer by DMA).
  * @note   In case of error due to overrun when using ADC with DMA transfer 
  *         (HAL ADC handle parameter "ErrorCode" to state "HAL_ADC_ERROR_OVR"):
  *         - Reinitialize the DMA using function "HAL_ADC_Stop_DMA()".
  *         - If needed, restart a new ADC conversion using function
  *           "HAL_ADC_Start_DMA()"
  *           (this function is also clearing overrun flag)
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ErrorCallback must be implemented in the user file.
  */
}


/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions 
 *
@verbatim   
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels on a conversion sequence
      (+) Configure the analog watchdog
      
@endverbatim
  * @{
  */

/**
  * @brief Configure a channel to be assigned to ADC conversion sequence.
  * @param hadc ADC handle
  * @param sConfigChannel Structure of ADC channel assigned to ADC conversion sequence.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ConfigChannelTypeDef* sConfigChannel)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  __IO uint32_t wait_loop_index = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SEQUENCE_NUM(sConfigChannel->SequenceNumber));
  assert_param(IS_ADC_VOLTAGE_RANGE(sConfigChannel->VoltRange));
  assert_param(IS_ADC_CHANNEL_TYPE(sConfigChannel->ChannelType));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  if (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL) {

    switch(sConfigChannel->SequenceNumber) {
        case ADC_SEQ_POS_01:
          LL_ADC_SetChannelSeq0(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_02:
          LL_ADC_SetChannelSeq1(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_03:
          LL_ADC_SetChannelSeq2(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_04:
          LL_ADC_SetChannelSeq3(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_05:
          LL_ADC_SetChannelSeq4(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_06:
          LL_ADC_SetChannelSeq5(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_07:
          LL_ADC_SetChannelSeq6(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_08:
          LL_ADC_SetChannelSeq7(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_09:
          LL_ADC_SetChannelSeq8(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_10:
          LL_ADC_SetChannelSeq9(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_11:
          LL_ADC_SetChannelSeq10(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_12:
          LL_ADC_SetChannelSeq11(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_13:
          LL_ADC_SetChannelSeq12(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_14:
          LL_ADC_SetChannelSeq13(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_15:
          LL_ADC_SetChannelSeq14(hadc->Instance, sConfigChannel->ChannelType);
          break;
        
        case ADC_SEQ_POS_16:
          LL_ADC_SetChannelSeq15(hadc->Instance, sConfigChannel->ChannelType);
          break;
    }

    switch(sConfigChannel->ChannelType) {
        case ADC_CH_VINM0_TO_SINGLE_NEGATIVE_INPUT:
          LL_ADC_SetVoltageRangeSingleVinm0(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINM1_TO_SINGLE_NEGATIVE_INPUT:
          LL_ADC_SetVoltageRangeSingleVinm1(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINM2_TO_SINGLE_NEGATIVE_INPUT:
          LL_ADC_SetVoltageRangeSingleVinm2(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINM3_TO_SINGLE_NEGATIVE_INPUT:
          LL_ADC_SetVoltageRangeSingleVinm3(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT:
          LL_ADC_SetVoltageRangeSingleVinp0(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINP1_TO_SINGLE_POSITIVE_INPUT:
          LL_ADC_SetVoltageRangeSingleVinp1(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT:
          LL_ADC_SetVoltageRangeSingleVinp2(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINP3_TO_SINGLE_POSITIVE_INPUT:
          LL_ADC_SetVoltageRangeSingleVinp3(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINP0_VINM0_TO_DIFF_INPUT:
          LL_ADC_SetVoltageRangeDiffVinp0Vinm0(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINP1_VINM1_TO_DIFF_INPUT:
          LL_ADC_SetVoltageRangeDiffVinp1Vinm1(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINP2_VINM2_TO_DIFF_INPUT:
          LL_ADC_SetVoltageRangeDiffVinp2Vinm2(hadc->Instance, sConfigChannel->VoltRange);
          break;
        
        case ADC_CH_VINP3_VINM3_TO_DIFF_INPUT:
          LL_ADC_SetVoltageRangeDiffVinp3Vinm3(hadc->Instance, sConfigChannel->VoltRange);
          break;
    }
    if(sConfigChannel->ChannelType == ADC_CH_TEMPERATURE_SENSOR) {
      /* Enable the internal temperature sensor */
      LL_PWR_EnableTempSens();
    }
  }
  /* If a conversion is on going on regular group, no update on regular       */
  /* channel could be done on neither of the channel configuration structure  */
  /* parameters.                                                              */
  else {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);
    
    tmp_hal_status = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Configure the watchdog.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the watchdog, successive  
  *         calls to this function can be used to reconfigure some parameters 
  *         of structure "ADC_ConfigWatchdogTypeDef" on the fly, without resetting 
  *         the ADC.
  *         The setting of these parameters is conditioned to ADC state.
  * @param hadc ADC handle
  * @param ConfigWatchdog Structure of ADC watchdog configuration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_WDGConfig(ADC_HandleTypeDef* hadc, ADC_ConfigWatchdogTypeDef* ConfigWatchdog)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_WDG_CHANNEL_MASK(ConfigWatchdog->ChannelMask));
  assert_param(IS_ADC_WDG_EVENT_TYPE(ConfigWatchdog->EventType));

  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Check if there is a conversion on going */
  if(LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL) {

    /* Configure the thresholds */
    LL_ADC_ConfigureWDGThresholds(hadc->Instance, ConfigWatchdog->LowThreshold, ConfigWatchdog->HighThreshold);

    /* Set the channels mask */
    LL_ADC_SetWDGInputChannels(hadc->Instance, ConfigWatchdog->ChannelMask);

    /* Update state, clear previous result related to watchdog */
    CLEAR_BIT(hadc->State, HAL_ADC_STATE_AWD);
      
    /* Clear flag ADC analog watchdog */
    /* Note: Flag cleared Clear the ADC Analog watchdog flag to be ready  */
    /* to use for HAL_ADC_IRQHandler() or HAL_ADC_PollForEvent()          */
    /* (in case left enabled by previous ADC operations).                 */
    LL_ADC_ClearFlag_AWD(hadc->Instance);

//#warning "evaluate if it is necessary add it in the event, because if no IT, then how get the flag status?"
    
    /* Configure ADC analog watchdog interrupt */
    if(ConfigWatchdog->EventType == ADC_WDG_EVENT_INTERRUPT) {
      LL_ADC_EnableIT_AWD(hadc->Instance);
    }
    else {
      LL_ADC_DisableIT_AWD(hadc->Instance);
    }
  }
  /* If a conversion is on going , no update could be done */
  else {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);
    
    tmp_hal_status = HAL_ERROR;
  }
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}


/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group4 Peripheral State functions
 *  @brief    ADC Peripheral State functions
 *
@verbatim
 ===============================================================================
            ##### Peripheral state and errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions to get in run-time the status of the  
    peripheral.
      (+) Check the ADC state
      (+) Check the ADC error code

@endverbatim
  * @{
  */

/**
  * @brief  Return the ADC handle state.
  * @note   ADC state machine is managed by bitfields, ADC status must be 
  *         compared with states bits.
  *         For example:                                                         
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_BUSY) != 0UL) "
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_AWD1) != 0UL) "
  * @param hadc ADC handle
  * @retval ADC handle state (bitfield on 32 bits)
  */
uint32_t HAL_ADC_GetState(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Return ADC handle state */
  return hadc->State;
}

/**
  * @brief  Return the ADC error code.
  * @param hadc ADC handle
  * @retval ADC error code (bitfield on 32 bits)
  */
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  return hadc->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */

/**
  * @brief Stop ADC conversion.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc)
{
  uint32_t is_conversion_on;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Verification if ADC is not already stopped (on regular and injected      */
  /* groups) to bypass this function if not needed.                           */
  is_conversion_on = LL_ADC_IsConversionOngoing(hadc->Instance);
  if (is_conversion_on != 0UL) {
          /* Stop ADC group injected conversion */
          LL_ADC_StopConversion(hadc->Instance);
  }
  
  /* Return HAL status */
  return HAL_OK;
}


/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  /* ADC enable  */
  if (LL_ADC_IsEnabled(hadc->Instance) == 0UL) {
    /* Enable the ADC peripheral */
    LL_ADC_Enable(hadc->Instance);
  }
   
  /* Return HAL status */
  return HAL_OK;
}


/**
  * @brief  Disable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc)
{
  /* Verification if ADC is not already disabled: */
  if( (LL_ADC_IsEnabled(hadc->Instance) != 0UL)) {
    
//      LL_ADC_SetSequenceLength(hadc->Instance, LL_ADC_SEQ_LEN_01);

      /* Disable the ADC peripheral */
      LL_ADC_Disable(hadc->Instance);
      /* Disable the internal temperature sensor */
      LL_PWR_DisableTempSens();
  }

  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  DMA transfer complete callback. 
  * @param hdma pointer to DMA handle.
  * @retval None
  */
void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma)
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  /* Update state machine on conversion status if not in error state */
  if((hadc->State & (HAL_ADC_STATE_ERROR_INTERNAL | HAL_ADC_STATE_ERROR_DMA)) == 0UL) {
    /* Set ADC state */
    SET_BIT(hadc->State, HAL_ADC_STATE_EOC);
    
    /* Is it the end of the sequence ? */
    if ((hadc->Instance->IRQ_STATUS & ADC_IRQ_FLAG_EOS) != 0UL) {
      /* Is it in continuous mode */
      if(LL_ADC_IsContinuousModeEnabled(hadc->Instance) == 0UL) {
        
        /* It is not  bit is not set, no more conversions expected */
        CLEAR_BIT(hadc->State, HAL_ADC_STATE_BUSY);
      }
    }
    else {
      /* DMA End of Transfer interrupt was triggered but conversions sequence
         is not over. If DMACFG is set to 0, conversions are stopped. */
      // if(READ_BIT(hadc->Instance->CFGR, ADC_CFGR_DMACFG) == 0UL)
      // {
      //   /* DMACFG bit is not set, conversions are stopped. */
      //   CLEAR_BIT(hadc->State, HAL_ADC_STATE_BUSY);
      //   if((hadc->State & HAL_ADC_STATE_INJ_BUSY) == 0UL)
      //   { 
      //     SET_BIT(hadc->State, HAL_ADC_STATE_READY);
      //   }
      // }
    }
    
    /* Conversion complete callback */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
    hadc->ConvCpltCallback(hadc);
#else
    HAL_ADC_ConvCpltCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
  }
  else /* DMA and-or internal error occurred */
  {
    if ((hadc->State & HAL_ADC_STATE_ERROR_INTERNAL) != 0UL) {
      /* Call HAL ADC Error Callback function */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
      hadc->ErrorCallback(hadc);
#else
      HAL_ADC_ErrorCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
    }
    else {
      /* Call ADC DMA error callback */
      hadc->DMA_Handle->XferErrorCallback(hdma);
    }
  }
}


/**
  * @brief  DMA half transfer complete callback. 
  * @param hdma pointer to DMA handle.
  * @retval None
  */
void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma)
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  /* Half conversion callback */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  hadc->ConvHalfCpltCallback(hadc);
#else
  HAL_ADC_ConvHalfCpltCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
}


/**
  * @brief  DMA error callback.
  * @param hdma pointer to DMA handle.
  * @retval None
  */
void ADC_DMAError(DMA_HandleTypeDef *hdma)
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  /* Set ADC state */
  SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_DMA);
  
  /* Set ADC error code to DMA error */
  SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_DMA);
  
  /* Error callback */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  hadc->ErrorCallback(hadc);
#else
  HAL_ADC_ErrorCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
}


/**
  * @}
  */

#endif /* HAL_ADC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
