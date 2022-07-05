/**
******************************************************************************
* @file    rf_driver_hal_pka_v7b.c
* @author  RF Application Team
* @brief   PKA HAL module driver.
*          This file provides firmware functions to manage the following
*          functionalities of public key accelerator(PKA):
*           + Initialization and de-initialization functions
*           + Start an operation
*           + Retrieve the operation result
*
@verbatim
==============================================================================
##### How to use this driver #####
==============================================================================
[..]
The PKA HAL driver can be used as follows:

(#) Declare a PKA_HandleTypeDef handle structure, for example: PKA_HandleTypeDef  hpka;

(#) Initialize the PKA low level resources by implementing the HAL_PKA_MspInit() API:
(##) Enable the PKA interface clock
(##) NVIC configuration if you need to use interrupt process
(+++) Configure the PKA interrupt priority
(+++) Enable the NVIC PKA IRQ Channel

(#) Initialize the PKA registers by calling the HAL_PKA_Init() API which trig
HAL_PKA_MspInit().

(#) Execute the operation (in polling or interrupt) and check the returned value.

(#) Retrieve the result of the operation by calling the HAL_PKA_GetResult()

(#) Call the function HAL_PKA_DeInit() to restore the default configuration which trig
HAL_PKA_MspDeInit().

*** Polling mode operation ***
===================================
[..]
(+) When an operation is started in polling mode, the function returns when:
(++) A timeout is encounter.
(++) The operation is completed.

*** Interrupt mode operation ***
===================================
[..]
(+) Add HAL_PKA_IRQHandler to the IRQHandler of PKA.
(+) Enable the IRQ using HAL_NVIC_EnableIRQ().
(+) When an operation is started in interrupt mode, the function returns immediatly.
(+) When the operation is completed, the callback HAL_PKA_OperationCpltCallback is called.
(+) When an error is encountered, the callback HAL_PKA_ErrorCallback is called.

*** Utilities ***
===================================
[..]
(+) To get current state, use HAL_PKA_GetState().
(+) To get current error, use HAL_PKA_GetError().

*** Callback registration ***
=============================================
[..]

The compilation flag USE_HAL_PKA_REGISTER_CALLBACKS, when set to 1,
allows the user to configure dynamically the driver callbacks.
Use Functions @ref HAL_PKA_RegisterCallback()
to register an interrupt callback.
[..]

Function @ref HAL_PKA_RegisterCallback() allows to register following callbacks:
(+) OperationCpltCallback : callback for End of operation.
(+) ErrorCallback         : callback for error detection.
(+) MspInitCallback       : callback for Msp Init.
(+) MspDeInitCallback     : callback for Msp DeInit.
This function takes as parameters the HAL peripheral handle, the Callback ID
and a pointer to the user callback function.
[..]

Use function @ref HAL_PKA_UnRegisterCallback to reset a callback to the default
weak function.
[..]

@ref HAL_PKA_UnRegisterCallback takes as parameters the HAL peripheral handle,
and the Callback ID.
This function allows to reset following callbacks:
(+) OperationCpltCallback : callback for End of operation.
(+) ErrorCallback         : callback for error detection.
(+) MspInitCallback       : callback for Msp Init.
(+) MspDeInitCallback     : callback for Msp DeInit.
[..]

By default, after the @ref HAL_PKA_Init() and when the state is @ref HAL_PKA_STATE_RESET
all callbacks are set to the corresponding weak functions:
examples @ref HAL_PKA_OperationCpltCallback(), @ref HAL_PKA_ErrorCallback().
Exception done for MspInit and MspDeInit functions that are
reset to the legacy weak functions in the @ref HAL_PKA_Init()/ @ref HAL_PKA_DeInit() only when
these callbacks are null (not registered beforehand).
[..]

If MspInit or MspDeInit are not null, the @ref HAL_PKA_Init()/ @ref HAL_PKA_DeInit()
keep and use the user MspInit/MspDeInit callbacks (registered beforehand) whatever the state.
[..]

Callbacks can be registered/unregistered in @ref HAL_PKA_STATE_READY state only.
Exception done MspInit/MspDeInit functions that can be registered/unregistered
in @ref HAL_PKA_STATE_READY or @ref HAL_PKA_STATE_RESET state,
thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
[..]

Then, the user first registers the MspInit/MspDeInit user callbacks
using @ref HAL_PKA_RegisterCallback() before calling @ref HAL_PKA_DeInit()
or @ref HAL_PKA_Init() function.
[..]

When the compilation flag USE_HAL_PKA_REGISTER_CALLBACKS is set to 0 or
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

#if defined(PKA) && defined(HAL_PKA_MODULE_ENABLED)

/** @defgroup PKA PKA
* @brief PKA HAL module driver.
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup PKA_Private_Define PKA Private Define
* @{
*/
#define PKA_RAM_SIZE 894U
/**
* @}
*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup PKA_Private_Functions PKA Private Functions
* @{
*/
HAL_StatusTypeDef PKA_PollEndOfOperation(PKA_HandleTypeDef *hpka, uint32_t Timeout, uint32_t Tickstart);
uint32_t PKA_CheckError(PKA_HandleTypeDef *hpka);
static int rev_memcmp(uint8_t *a, const uint8_t *b, uint8_t  bufferSize);
uint32_t PKA_SetData(uint8_t dataType, uint32_t* srcData);
/**
* @}
*/

/* Exported functions --------------------------------------------------------*/

/** @defgroup PKA_Exported_Functions PKA Exported Functions
* @{
*/

/** @defgroup PKA_Exported_Functions_Group1 Initialization and de-initialization functions
*  @brief   Initialization and de-initialization functions
*
@verbatim
===============================================================================
##### Initialization and de-initialization functions  #####
===============================================================================
[..]  This subsection provides a set of functions allowing to initialize and
deinitialize the PKAx peripheral:

(+) User must implement HAL_PKA_MspInit() function in which he configures
all related peripherals resources (CLOCK, IT and NVIC ).

(+) Call the function HAL_PKA_Init() to configure the selected device with
the selected configuration:
(++) Security level

(+) Call the function HAL_PKA_DeInit() to restore the default configuration
of the selected PKAx peripheral.

@endverbatim
* @{
*/

/**
* @brief  Initialize the PKA according to the specified
*         parameters in the PKA_InitTypeDef and initialize the associated handle.
* @param  hpka PKA handle
* @retval HAL status
*/
HAL_StatusTypeDef HAL_PKA_Init(PKA_HandleTypeDef *hpka)
{
  HAL_StatusTypeDef err = HAL_OK;
  
  /* Check the PKA handle allocation */
  if (hpka != NULL)
  {
    /* Check the parameters */
    assert_param(IS_PKA_ALL_INSTANCE(hpka->Instance));
    
    if (hpka->State == HAL_PKA_STATE_RESET)
    {
      
#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
      /* Init the PKA Callback settings */
      hpka->OperationCpltCallback = HAL_PKA_OperationCpltCallback; /* Legacy weak OperationCpltCallback */
      hpka->ErrorCallback         = HAL_PKA_ErrorCallback;         /* Legacy weak ErrorCallback         */
      
      if (hpka->MspInitCallback == NULL)
      {
        hpka->MspInitCallback = HAL_PKA_MspInit; /* Legacy weak MspInit  */
      }
      
      /* Init the low level hardware */
      hpka->MspInitCallback(hpka);
#else
      /* Init the low level hardware */
      HAL_PKA_MspInit(hpka);
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */
    }
    
    /* Set the state to busy */
    hpka->State = HAL_PKA_STATE_BUSY;
    
    /* Reset the control register and enable the PKA */
    SET_BIT(hpka->Instance->CSR, PKA_CSR_SFT_RST);
    CLEAR_BIT(hpka->Instance->CSR, PKA_CSR_SFT_RST);
    
    /* Reset any pending flag */
    SET_BIT(hpka->Instance->ISR, PKA_ISR_PROC_END | PKA_ISR_RAM_ERR | PKA_ISR_ADD_ERR);
    CLEAR_BIT(hpka->Instance->ISR, PKA_ISR_PROC_END | PKA_ISR_RAM_ERR | PKA_ISR_ADD_ERR);
    
    /* Initialize the error code */
    hpka->ErrorCode = HAL_PKA_ERROR_NONE;
    
    /* Set the state to ready */
    hpka->State = HAL_PKA_STATE_READY;
  }
  else
  {
    err = HAL_ERROR;
  }
  
  return err;
}

/**
* @brief  DeInitialize the PKA peripheral.
* @param  hpka PKA handle
* @retval HAL status
*/
HAL_StatusTypeDef HAL_PKA_DeInit(PKA_HandleTypeDef *hpka)
{
  HAL_StatusTypeDef err = HAL_OK;
  
  /* Check the PKA handle allocation */
  if (hpka != NULL)
  {
    /* Check the parameters */
    assert_param(IS_PKA_ALL_INSTANCE(hpka->Instance));
    
    /* Set the state to busy */
    hpka->State = HAL_PKA_STATE_BUSY;
    
    /* Reset the control register and enable the PKA */
    SET_BIT(hpka->Instance->CSR, PKA_CSR_SFT_RST);
    CLEAR_BIT(hpka->Instance->CSR, PKA_CSR_SFT_RST);
    
    /* Reset any pending flag */
    SET_BIT(hpka->Instance->ISR, PKA_ISR_PROC_END | PKA_ISR_RAM_ERR | PKA_ISR_ADD_ERR);
    CLEAR_BIT(hpka->Instance->ISR, PKA_ISR_PROC_END | PKA_ISR_RAM_ERR | PKA_ISR_ADD_ERR);
    
#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
    if (hpka->MspDeInitCallback == NULL)
    {
      hpka->MspDeInitCallback = HAL_PKA_MspDeInit; /* Legacy weak MspDeInit  */
    }
    
    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    hpka->MspDeInitCallback(hpka);
#else
    /* DeInit the low level hardware: CLOCK, NVIC */
    HAL_PKA_MspDeInit(hpka);
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */
    
    /* Reset the error code */
    hpka->ErrorCode = HAL_PKA_ERROR_NONE;
    
    /* Reset the state */
    hpka->State = HAL_PKA_STATE_RESET;
  }
  else
  {
    err = HAL_ERROR;
  }
  
  return err;
}

/**
* @brief  Initialize the PKA MSP.
* @param  hpka PKA handle
* @retval None
*/
WEAK_FUNCTION(void HAL_PKA_MspInit(PKA_HandleTypeDef *hpka))
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpka);
  
  /* NOTE : This function should not be modified, when the callback is needed,
  the HAL_PKA_MspInit can be implemented in the user file
  */
}

/**
* @brief  DeInitialize the PKA MSP.
* @param  hpka PKA handle
* @retval None
*/
WEAK_FUNCTION(void HAL_PKA_MspDeInit(PKA_HandleTypeDef *hpka))
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpka);
  
  /* NOTE : This function should not be modified, when the callback is needed,
  the HAL_PKA_MspDeInit can be implemented in the user file
  */
}

#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
/**
* @brief  Register a User PKA Callback
*         To be used instead of the weak predefined callback
* @param  hpka Pointer to a PKA_HandleTypeDef structure that contains
*                the configuration information for the specified PKA.
* @param  CallbackID ID of the callback to be registered
*         This parameter can be one of the following values:
*          @arg @ref HAL_PKA_OPERATION_COMPLETE_CB_ID End of operation callback ID
*          @arg @ref HAL_PKA_ERROR_CB_ID Error callback ID
*          @arg @ref HAL_PKA_MSPINIT_CB_ID MspInit callback ID
*          @arg @ref HAL_PKA_MSPDEINIT_CB_ID MspDeInit callback ID
* @param  pCallback pointer to the Callback function
* @retval HAL status
*/
HAL_StatusTypeDef HAL_PKA_RegisterCallback(PKA_HandleTypeDef *hpka, HAL_PKA_CallbackIDTypeDef CallbackID, pPKA_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  if (pCallback == NULL)
  {
    /* Update the error code */
    hpka->ErrorCode |= HAL_PKA_ERROR_INVALID_CALLBACK;
    
    return HAL_ERROR;
  }
  
  if (HAL_PKA_STATE_READY == hpka->State)
  {
    switch (CallbackID)
    {
    case HAL_PKA_OPERATION_COMPLETE_CB_ID :
      hpka->OperationCpltCallback = pCallback;
      break;
      
    case HAL_PKA_ERROR_CB_ID :
      hpka->ErrorCallback = pCallback;
      break;
      
    case HAL_PKA_MSPINIT_CB_ID :
      hpka->MspInitCallback = pCallback;
      break;
      
    case HAL_PKA_MSPDEINIT_CB_ID :
      hpka->MspDeInitCallback = pCallback;
      break;
      
    default :
      /* Update the error code */
      hpka->ErrorCode |= HAL_PKA_ERROR_INVALID_CALLBACK;
      
      /* Return error status */
      status = HAL_ERROR;
      break;
    }
  }
  else if (HAL_PKA_STATE_RESET == hpka->State)
  {
    switch (CallbackID)
    {
    case HAL_PKA_MSPINIT_CB_ID :
      hpka->MspInitCallback = pCallback;
      break;
      
    case HAL_PKA_MSPDEINIT_CB_ID :
      hpka->MspDeInitCallback = pCallback;
      break;
      
    default :
      /* Update the error code */
      hpka->ErrorCode |= HAL_PKA_ERROR_INVALID_CALLBACK;
      
      /* Return error status */
      status = HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Update the error code */
    hpka->ErrorCode |= HAL_PKA_ERROR_INVALID_CALLBACK;
    
    /* Return error status */
    status =  HAL_ERROR;
  }
  
  return status;
}

/**
* @brief  Unregister a PKA Callback
*         PKA callback is redirected to the weak predefined callback
* @param  hpka Pointer to a PKA_HandleTypeDef structure that contains
*                the configuration information for the specified PKA.
* @param  CallbackID ID of the callback to be unregistered
*         This parameter can be one of the following values:
*          @arg @ref HAL_PKA_OPERATION_COMPLETE_CB_ID End of operation callback ID
*          @arg @ref HAL_PKA_ERROR_CB_ID Error callback ID
*          @arg @ref HAL_PKA_MSPINIT_CB_ID MspInit callback ID
*          @arg @ref HAL_PKA_MSPDEINIT_CB_ID MspDeInit callback ID
* @retval HAL status
*/
HAL_StatusTypeDef HAL_PKA_UnRegisterCallback(PKA_HandleTypeDef *hpka, HAL_PKA_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  if (HAL_PKA_STATE_READY == hpka->State)
  {
    switch (CallbackID)
    {
    case HAL_PKA_OPERATION_COMPLETE_CB_ID :
      hpka->OperationCpltCallback = HAL_PKA_OperationCpltCallback; /* Legacy weak OperationCpltCallback */
      break;
      
    case HAL_PKA_ERROR_CB_ID :
      hpka->ErrorCallback = HAL_PKA_ErrorCallback;                 /* Legacy weak ErrorCallback        */
      break;
      
    case HAL_PKA_MSPINIT_CB_ID :
      hpka->MspInitCallback = HAL_PKA_MspInit;                     /* Legacy weak MspInit              */
      break;
      
    case HAL_PKA_MSPDEINIT_CB_ID :
      hpka->MspDeInitCallback = HAL_PKA_MspDeInit;                 /* Legacy weak MspDeInit            */
      break;
      
    default :
      /* Update the error code */
      hpka->ErrorCode |= HAL_PKA_ERROR_INVALID_CALLBACK;
      
      /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if (HAL_PKA_STATE_RESET == hpka->State)
  {
    switch (CallbackID)
    {
    case HAL_PKA_MSPINIT_CB_ID :
      hpka->MspInitCallback = HAL_PKA_MspInit;                   /* Legacy weak MspInit              */
      break;
      
    case HAL_PKA_MSPDEINIT_CB_ID :
      hpka->MspDeInitCallback = HAL_PKA_MspDeInit;               /* Legacy weak MspDeInit            */
      break;
      
    default :
      /* Update the error code */
      hpka->ErrorCode |= HAL_PKA_ERROR_INVALID_CALLBACK;
      
      /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Update the error code */
    hpka->ErrorCode |= HAL_PKA_ERROR_INVALID_CALLBACK;
    
    /* Return error status */
    status =  HAL_ERROR;
  }
  
  return status;
}

#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */

/**
* @}
*/

/** @defgroup PKA_Exported_Functions_Group2 IO operation functions
*  @brief   IO operation functions
*
@verbatim
===============================================================================
##### IO operation functions #####
===============================================================================
[..]
This subsection provides a set of functions allowing to manage the PKA operations.

(#) There are two modes of operation:

(++) Blocking mode : The operation is performed in the polling mode.
These functions return when data operation is completed.
(++) No-Blocking mode : The operation is performed using Interrupts.
These functions return immediatly.
The end of the operation is indicated by HAL_PKA_ErrorCallback in case of error.
The end of the operation is indicated by HAL_PKA_OperationCpltCallback in case of success.
To stop any operation in interrupt mode, use HAL_PKA_Abort().

(#) Blocking mode functions are :

(++) HAL_PKA_StartProc()

(#) No-Blocking mode functions with Interrupt are :

(++) HAL_PKA_StartProc_IT();
(++) HAL_PKA_Abort();

@endverbatim
* @{
*/

/**
* @brief  Start Process Data in blocking mode.
* @param  hpka PKA handle
* @param  randomK 16 word random for point 
* @param  Timeout Timeout duration
* @param  PKAStartPoint Parametric PKA Start Point, if NULL it will be equal to the internal PKAStartPoint
* @retval HAL status
*/
HAL_StatusTypeDef HAL_PKA_StartProc(PKA_HandleTypeDef *hpka, uint32_t *randomK, uint32_t Timeout, uint32_t *PKAStartPoint)
{
  HAL_StatusTypeDef err = HAL_OK;
  uint32_t tickstart;
  uint32_t PKAInternalStartPoint[16] = {
    INITIAL_START_POINT_X_W1, INITIAL_START_POINT_X_W2, INITIAL_START_POINT_X_W3, INITIAL_START_POINT_X_W4,
    INITIAL_START_POINT_X_W5, INITIAL_START_POINT_X_W6, INITIAL_START_POINT_X_W7, INITIAL_START_POINT_X_W8,
    INITIAL_START_POINT_Y_W1, INITIAL_START_POINT_Y_W2, INITIAL_START_POINT_Y_W3, INITIAL_START_POINT_Y_W4,
    INITIAL_START_POINT_Y_W5, INITIAL_START_POINT_Y_W6, INITIAL_START_POINT_Y_W7, INITIAL_START_POINT_Y_W8};
  
  if(PKAStartPoint == NULL){
    PKAStartPoint = PKAInternalStartPoint;
  }
  
  if (hpka->State == HAL_PKA_STATE_READY)
  {
    /* Set the state to busy */
    hpka->State = HAL_PKA_STATE_BUSY;
    
    /* Clear any pending error */
    hpka->ErrorCode = HAL_PKA_ERROR_NONE;
    
    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();
    
    /* Deactivate the interrupts */
    CLEAR_BIT(hpka->Instance->IEN, PKA_IEN_READY_EN | PKA_IEN_RAMERR_EN | PKA_IEN_ADDERR_EN);
    
    /* Insert the random K for point */
    hpka->ErrorCode |= PKA_SetData(PKA_DATA_SK, randomK);
    
    /* Insert the initial starting point coordinates */
    hpka->ErrorCode |= PKA_SetData(PKA_DATA_PCX, (uint32_t *)&PKAStartPoint[0]);
    hpka->ErrorCode |= PKA_SetData(PKA_DATA_PCY, (uint32_t *)&PKAStartPoint[8]);
    
    /* Start the computation */
    SET_BIT(hpka->Instance->CSR, PKA_CSR_GO);
    CLEAR_BIT(hpka->Instance->CSR, PKA_CSR_GO);
    
    /* Wait for the end of operation or timeout */
    if (PKA_PollEndOfOperation(hpka, Timeout, tickstart) != HAL_OK)
    {
      hpka->ErrorCode |= HAL_PKA_ERROR_TIMEOUT;
    }
    
    /* Check error */
    hpka->ErrorCode |= PKA_CheckError(hpka);
    
    /* Clear all flags */
    SET_BIT(hpka->Instance->ISR, PKA_ISR_PROC_END | PKA_ISR_RAM_ERR | PKA_ISR_ADD_ERR);
    CLEAR_BIT(hpka->Instance->ISR, PKA_ISR_PROC_END | PKA_ISR_RAM_ERR | PKA_ISR_ADD_ERR);
    
    /* Set the state to ready */
    hpka->State = HAL_PKA_STATE_READY;
    
    /* Manage the result based on encountered errors */
    if (hpka->ErrorCode != HAL_PKA_ERROR_NONE)
    {
      err = HAL_ERROR;
    }
  }
  else
  {
    err = HAL_ERROR;
  }
  return err;
}


/**
* @brief  Start Process Data in non-blocking mode with Interrupt.
* @param  hpka PKA handle
* @param  randomK 16 word random for point 
* @param  Timeout Timeout duration
* @param  PKAStartPoint Parametric PKA Start Point, if NULL it will be equal to the internal PKAStartPoint
* @retval HAL status
*/
HAL_StatusTypeDef HAL_PKA_StartProc_IT(PKA_HandleTypeDef *hpka, uint32_t *randomK, uint32_t Timeout, uint32_t *PKAStartPoint)
{
  HAL_StatusTypeDef err = HAL_OK;
  uint32_t PKAInternalStartPoint[16] = {
    INITIAL_START_POINT_X_W1, INITIAL_START_POINT_X_W2, INITIAL_START_POINT_X_W3, INITIAL_START_POINT_X_W4,
    INITIAL_START_POINT_X_W5, INITIAL_START_POINT_X_W6, INITIAL_START_POINT_X_W7, INITIAL_START_POINT_X_W8,
    INITIAL_START_POINT_Y_W1, INITIAL_START_POINT_Y_W2, INITIAL_START_POINT_Y_W3, INITIAL_START_POINT_Y_W4,
    INITIAL_START_POINT_Y_W5, INITIAL_START_POINT_Y_W6, INITIAL_START_POINT_Y_W7, INITIAL_START_POINT_Y_W8};
  
  if(PKAStartPoint == NULL){
    PKAStartPoint = PKAInternalStartPoint;
  }
  
  if (hpka->State == HAL_PKA_STATE_READY)
  {
    /* Set the state to busy */
    hpka->State = HAL_PKA_STATE_BUSY;
    
    /* Clear any pending error */
    hpka->ErrorCode = HAL_PKA_ERROR_NONE;
    
    /* Activate interrupts */
    SET_BIT(hpka->Instance->IEN, PKA_IEN_READY_EN | PKA_IEN_RAMERR_EN | PKA_IEN_ADDERR_EN);
    
    /* Insert the random K for point */
    hpka->ErrorCode |= PKA_SetData(PKA_DATA_SK, randomK);
    
    /* Insert the initial starting point coordinates */
    hpka->ErrorCode |= PKA_SetData(PKA_DATA_PCX, (uint32_t *)&PKAStartPoint[0]);
    hpka->ErrorCode |= PKA_SetData(PKA_DATA_PCY, (uint32_t *)&PKAStartPoint[8]);
    
    /* Start the computation */
    SET_BIT(hpka->Instance->CSR, PKA_CSR_GO);
    CLEAR_BIT(hpka->Instance->CSR, PKA_CSR_GO);
  }
  else
  {
    err = HAL_ERROR;
  }
  return err;
  
}



/**
* @brief  Retrieve operation result.
* @param  hpka PKA handle
* @param  dataType: select the region of PKA RAM to read:
*         @arg PKA_DATA_SK is the K value
*         @arg PKA_DATA_PCX is the point X coordinate
*         @arg PKA_DATA_PCY is the point Y coordinate 
* @param  pRes Output buffer
* @retval HAL status
*/
void HAL_PKA_GetResult(PKA_HandleTypeDef *hpka, uint8_t dataType, uint8_t *pRes)
{
  uint32_t StartAddress;
  
  if (dataType == PKA_DATA_SK)
    StartAddress = PKA_RAM_ECC_ADDR_K;
  else if (dataType == PKA_DATA_PCX)
    StartAddress = PKA_RAM_ECC_ADDR_PX;
  else if (dataType == PKA_DATA_PCY)
    StartAddress = PKA_RAM_ECC_ADDR_PY;
  else  hpka->ErrorCode |= HAL_PKA_ERROR_OPERATION;
  
  /* Read the data to target PKA RAM address. */
  for(uint8_t i=0;i<32;i++) {
    pRes[i] = ((uint8_t *)StartAddress)[i];
  }
}

/**
* @brief  Abort any ongoing operation.
* @param  hpka PKA handle
* @retval HAL status
*/
HAL_StatusTypeDef HAL_PKA_Abort(PKA_HandleTypeDef *hpka)
{
  HAL_StatusTypeDef err = HAL_OK;
  
  /* This abort any operation in progress (PKA RAM content is not guaranted in this case) */
  SET_BIT(hpka->Instance->CSR, PKA_CSR_SFT_RST);
  CLEAR_BIT(hpka->Instance->CSR, PKA_CSR_SFT_RST);
  
  /* Reset any pending flag */
  SET_BIT(hpka->Instance->ISR, PKA_ISR_PROC_END | PKA_ISR_RAM_ERR | PKA_ISR_ADD_ERR);
  CLEAR_BIT(hpka->Instance->ISR, PKA_ISR_PROC_END | PKA_ISR_RAM_ERR | PKA_ISR_ADD_ERR);
  
  /* Reset the error code */
  hpka->ErrorCode = HAL_PKA_ERROR_NONE;
  
  /* Reset the state */
  hpka->State = HAL_PKA_STATE_READY;
  
  return err;
}

/**
* @brief  Reset the PKA RAM.
* @param  hpka PKA handle
* @retval None
*/
void HAL_PKA_RAMReset(PKA_HandleTypeDef *hpka)
{
  uint8_t i;
  
  for(i=0; i<32; i++)
  {
    ((uint8_t *)PKA_RAM_ECC_ADDR_K)[i] = 0;
    ((uint8_t *)PKA_RAM_ECC_ADDR_PX)[i] = 0;
    ((uint8_t *)PKA_RAM_ECC_ADDR_PY)[i] = 0;
  }
}

/**
* @brief  This function handles PKA event interrupt request.
* @param  hpka PKA handle
* @retval None
*/
void HAL_PKA_IRQHandler(PKA_HandleTypeDef *hpka)
{
  FlagStatus addErrFlag = __HAL_PKA_GET_FLAG(hpka, PKA_FLAG_ADDRERR);
  FlagStatus ramErrFlag = __HAL_PKA_GET_FLAG(hpka, PKA_FLAG_RAMERR);
  FlagStatus procEndFlag = __HAL_PKA_GET_FLAG(hpka, PKA_FLAG_PROCEND);
  
  /* Address error interrupt occurred */
  if ((__HAL_PKA_GET_IT_SOURCE(hpka, PKA_IT_ADDRERR) == SET) && (addErrFlag == SET))
  {
    hpka->ErrorCode |= HAL_PKA_ERROR_ADDRERR;
    
    /* Clear ADDRERR flag */
    __HAL_PKA_CLEAR_FLAG(hpka, PKA_FLAG_ADDRERR);
  }
  
  /* RAM access error interrupt occurred */
  if ((__HAL_PKA_GET_IT_SOURCE(hpka, PKA_IT_RAMERR) == SET) && (ramErrFlag == SET))
  {
    hpka->ErrorCode |= HAL_PKA_ERROR_RAMERR;
    
    /* Clear RAMERR flag */
    __HAL_PKA_CLEAR_FLAG(hpka, PKA_FLAG_RAMERR);
  }
  
  /* Trigger the error callback if an error is present */
  if (hpka->ErrorCode != HAL_PKA_ERROR_NONE)
  {
#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
    hpka->ErrorCallback(hpka);
#else
    HAL_PKA_ErrorCallback(hpka);
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */
  }
  
  /* End Of Operation interrupt occurred */
  if ((__HAL_PKA_GET_IT_SOURCE(hpka, PKA_IT_PROCEND) == SET) && (procEndFlag == SET))
  {
    /* Clear PROCEND flag */
    __HAL_PKA_CLEAR_FLAG(hpka, PKA_FLAG_PROCEND);
    
    /* Set the state to ready */
    hpka->State = HAL_PKA_STATE_READY;
    
#if (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
    hpka->OperationCpltCallback(hpka);
#else
    HAL_PKA_OperationCpltCallback(hpka);
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */
  }
}

/**
* @brief  Process completed callback.
* @param  hpka PKA handle
* @retval None
*/
WEAK_FUNCTION(void HAL_PKA_OperationCpltCallback(PKA_HandleTypeDef *hpka))
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpka);
  
  /* NOTE : This function should not be modified, when the callback is needed,
  the HAL_PKA_OperationCpltCallback could be implemented in the user file
  */
}

/**
* @brief  Error callback.
* @param  hpka PKA handle
* @retval None
*/
WEAK_FUNCTION(void HAL_PKA_ErrorCallback(PKA_HandleTypeDef *hpka))
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpka);
  
  /* NOTE : This function should not be modified, when the callback is needed,
  the HAL_PKA_ErrorCallback could be implemented in the user file
  */
}

/**
* @}
*/

/** @defgroup PKA_Exported_Functions_Group3 Peripheral State and Error functions
*  @brief   Peripheral State and Error functions
*
@verbatim
===============================================================================
##### Peripheral State and Error functions #####
===============================================================================
[..]
This subsection permit to get in run-time the status of the peripheral.

@endverbatim
* @{
*/

/**
* @brief  Return the PKA handle state.
* @param  hpka PKA handle
* @retval HAL status
*/
HAL_PKA_StateTypeDef HAL_PKA_GetState(PKA_HandleTypeDef *hpka)
{
  /* Return PKA handle state */
  return hpka->State;
}

/**
* @brief  Return the PKA error code.
* @param  hpka PKA handle
* @retval PKA error code
*/
uint32_t HAL_PKA_GetError(PKA_HandleTypeDef *hpka)
{
  return hpka->ErrorCode;
}

/**
* @}
*/

/**
* @}
*/

/** @addtogroup PKA_Private_Functions
* @{
*/

/**
* @brief  Wait for operation completion or timeout.
* @param  hpka PKA handle
* @param  Timeout Timeout duration in millisecond.
* @param  Tickstart Tick start value
* @retval HAL status
*/
HAL_StatusTypeDef PKA_PollEndOfOperation(PKA_HandleTypeDef *hpka, uint32_t Timeout, uint32_t Tickstart)
{
  /* Wait for the end of operation or timeout */
  while ((hpka->Instance->CSR & PKA_CSR_READY) != PKA_CSR_READY)
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0UL))
      {
        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}

/**
* @brief  Return a hal error code based on PKA error flags.
* @param  hpka PKA handle
* @retval error code
*/
uint32_t PKA_CheckError(PKA_HandleTypeDef *hpka)
{
  uint32_t err = HAL_PKA_ERROR_NONE;
  
  /* Check RAMERR error */
  if (__HAL_PKA_GET_FLAG(hpka, PKA_FLAG_RAMERR) == SET)
  {
    err |= HAL_PKA_ERROR_RAMERR;
  }
  
  /* Check ADDRERR error */
  if (__HAL_PKA_GET_FLAG(hpka, PKA_FLAG_ADDRERR) == SET)
  {
    err |= HAL_PKA_ERROR_ADDRERR;
  }
  
  /* If error output result is different from 0, operation need to be repeated */
  if (*(uint32_t *)(PKA_RAM_ECC_ADDR_KP_ERROR) != 0UL)
  {
    err |= HAL_PKA_ERROR_OPERATION;
  }
  
  return err;
}

/**
* @brief  Internal Utility for PKA key range check
* @param  a: pka key
*         b: reference key
*         bufferSize: key size
* @retval check result 
*/
static int rev_memcmp(uint8_t *a, const uint8_t *b, uint8_t  bufferSize)
{
  uint_fast8_t i = bufferSize;
  int retval = 0;
  
  do
  {
    i--;
    retval = (int)a[i] - (int)b[i];
    if (retval !=0)
    {
      break;
    }
  } while (i != 0U);
  
  return retval;
}


/**
* @brief  Write the PKA RAM with the input data.
* @param  dataType: select the region of PKA RAM to write:
*         @arg PKA_DATA_SK is the K value
*         @arg PKA_DATA_PCX is the point X coordinate
*         @arg PKA_DATA_PCY is the point Y coordinate
* @retval Status
*/
uint32_t PKA_SetData(uint8_t dataType, uint32_t* srcData)
{
  const uint8_t P256_P_LE[32] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xff,0xff,0xff,0xff}; 
  const uint8_t BLE_P256_ABELIAN_ORDER_R_LE[32] = {0x51,0x25,0x63,0xFC,0xC2,0xCA,0xB9,0xF3,0x84,0x9E,0x17,0xA7,0xAD,0xFA,0xE6,0xBC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
  uint32_t StartAddress;
  uint8_t idx;
  uint32_t err = HAL_PKA_ERROR_NONE;
  
  if (dataType == PKA_DATA_SK) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)BLE_P256_ABELIAN_ORDER_R_LE, 32) >= 0) {
      err |= HAL_PKA_ERROR_DATA_SK;
    }
    StartAddress = PKA_RAM_ECC_ADDR_K;
  }
  
  else if (dataType == PKA_DATA_PCX) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)P256_P_LE, 32) >= 0) {
      err |= HAL_PKA_ERROR_DATA_PCX;
    }
    StartAddress = PKA_RAM_ECC_ADDR_PX;
  }
  
  else if (dataType == PKA_DATA_PCY) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)P256_P_LE, 32) >= 0) {
      err |= HAL_PKA_ERROR_DATA_PCY;
    }
    StartAddress = PKA_RAM_ECC_ADDR_PY;
  }
  else 
    err |= HAL_PKA_ERROR_OPERATION;
  
  /* Write the source data to target PKA RAM address. */
  for (idx = 0; idx<8; idx++)
  {
    *(uint32_t *)(StartAddress + 4*idx) = srcData[idx];
  }
  
  /* A 9th word of zeros must be added */
  *(uint32_t *)(StartAddress + 32UL) = 0x00000000;
  
  return err;
}

/**
* @}
*/

/**
* @}
*/

#endif /* defined(PKA) && defined(HAL_PKA_MODULE_ENABLED) */

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
