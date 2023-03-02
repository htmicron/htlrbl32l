/**
  ******************************************************************************
  * @file    rf_driver_ll_exti.c
  * @author  RF Application Team
  * @brief   EXTI LL module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics. 
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
#include "rf_driver_ll_exti.h"
#ifdef  USE_FULL_ASSERT
#include "rf_driver_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */


/** @defgroup EXTI_LL EXTI
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup EXTI_LL_Private_Macros
  * @{
  */

#define IS_LL_EXTI_LINE(__VALUE__)              (((__VALUE__) & ~LL_EXTI_LINE_ALL) == 0x00000000U)

#define IS_LL_EXTI_TYPE(__VALUE__)                   (((__VALUE__) == LL_EXTI_TYPE_EDGE)  \
                                                   || ((__VALUE__) == LL_EXTI_TYPE_LEVEL))


#define IS_LL_EXTI_TRIGGER(__VALUE__)                (((__VALUE__) == LL_EXTI_TRIGGER_RISING_EDGE)       \
                                                   || ((__VALUE__) == LL_EXTI_TRIGGER_FALLING_EDGE)     \
                                                   || ((__VALUE__) == LL_EXTI_TRIGGER_BOTH_EDGE)    \
                                                   || ((__VALUE__) == LL_EXTI_TRIGGER_LOW_LEVEL)    \
                                                   || ((__VALUE__) == LL_EXTI_TRIGGER_HIGH_LEVEL))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup EXTI_LL_Exported_Functions
  * @{
  */

/** @addtogroup EXTI_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the EXTI registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_EXTI_DeInit(void)
{
  /* I/O Interrupt detection type register set to default reset values */
  LL_EXTI_WriteReg(IO_DTR,  0x00000000U);
  
  /* I/O Interrupt Edge register set to default reset values */
  LL_EXTI_WriteReg(IO_IBER,  0x00000000U);
  
  /* I/O Interrupt polarity event register set to default reset values */
  LL_EXTI_WriteReg(IO_IEVR, 0x00000000U);
  
  /* I/O Interrupt Enable register set to default reset values */
  LL_EXTI_WriteReg(IO_IER, 0x00000000U);

  /* Clear all the I/O Interrupt */
  LL_EXTI_WriteReg(IO_ISCR, LL_EXTI_LINE_ALL);
  
  return SUCCESS;
}

/**
  * @brief  Initialize the EXTI registers according to the specified parameters in EXTI_InitStruct.
  * @param  EXTI_InitStruct pointer to a @ref LL_EXTI_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_EXTI_Init(LL_EXTI_InitTypeDef *EXTI_InitStruct)
{
  ErrorStatus status = SUCCESS;
  /* Check the parameters */
  assert_param(IS_LL_EXTI_LINE(EXTI_InitStruct->Line));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->LineCommand));
  assert_param(IS_LL_EXTI_TYPE(EXTI_InitStruct->Type));

  /* ENABLE LineCommand */
  if (EXTI_InitStruct->LineCommand != DISABLE)
  {
    assert_param(IS_LL_EXTI_TRIGGER(EXTI_InitStruct->Trigger));

    /* Configure EXTI Lines in range from PA0 to PB15 */
    if (EXTI_InitStruct->Line != LL_EXTI_LINE_NONE)
    {
      /* Set the IT Type on provided Lines */
      LL_EXTI_SetType(EXTI_InitStruct->Type, EXTI_InitStruct->Line);

      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        /* Set the IT Trigger on provided Lines */
        LL_EXTI_SetTrigger(EXTI_InitStruct->Trigger, EXTI_InitStruct->Line);
      }
      LL_EXTI_EnableIT(EXTI_InitStruct->Line);
      LL_EXTI_ClearInterrupt(EXTI_InitStruct->Line);
    }
  }
  /* DISABLE LineCommand */
  else
  {
    LL_EXTI_DisableIT(EXTI_InitStruct->Line);
  }
  return status;
}

/**
  * @brief  Set each @ref LL_EXTI_InitTypeDef field to default value.
  * @param  EXTI_InitStruct Pointer to a @ref LL_EXTI_InitTypeDef structure.
  * @retval None
  */
void LL_EXTI_StructInit(LL_EXTI_InitTypeDef *EXTI_InitStruct)
{
  EXTI_InitStruct->Line           = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->LineCommand    = DISABLE;
  EXTI_InitStruct->Type           = LL_EXTI_TYPE_EDGE;
  EXTI_InitStruct->Trigger        = LL_EXTI_TRIGGER_NONE;
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


/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
