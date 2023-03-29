/**
  ******************************************************************************
  * @file    rf_driver_ll_pwr.c
  * @author  RF Application Team
  * @brief   PWR LL module driver.
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
#include "rf_driver_ll_pwr.h"
#include "rf_driver_ll_bus.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */
/* Definitions of PWR registers reset value */
#define PWR_CR1_RESET_VALUE     (0x00000010)
#define PWR_CR2_RESET_VALUE     (0x00000100)
#define PWR_CR3_RESET_VALUE     (0x00000000)
#define PWR_CR4_RESET_VALUE     (0x00000000)
#define PWR_CR5_RESET_VALUE     (0x00000014)
#define PWR_PUCRA_RESET_VALUE   (0x0000FFFF)
#define PWR_PDCRA_RESET_VALUE   (0x00000000)
#define PWR_PUCRB_RESET_VALUE   (0x0000FFFF)
#define PWR_PDCRB_RESET_VALUE   (0x00000000)
#define PWR_IOxCFG_RESET_VALUE  (0x00000000)
#define PWR_ENGTRIM_RESET_VALUE (0x00000000)
#define PWR_EWUA_RESET_VALUE    (0x00000000)
#define PWR_EWUB_RESET_VALUE    (0x00000000)
#define PWR_IEWU_RESET_VALUE    (0x00000000)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWR_LL_Exported_Functions
  * @{
  */

/** @addtogroup PWR_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the PWR registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PWR registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_PWR_DeInit(void)
{
  /* Apply reset values to all PWR registers */
  LL_PWR_WriteReg(CR1, PWR_CR1_RESET_VALUE);
  LL_PWR_WriteReg(CR2, PWR_CR2_RESET_VALUE);
  LL_PWR_WriteReg(CR3, PWR_CR3_RESET_VALUE);
  LL_PWR_WriteReg(CR4, PWR_CR4_RESET_VALUE);
  LL_PWR_WriteReg(CR5, PWR_CR5_RESET_VALUE);
  LL_PWR_WriteReg(PUCRA, PWR_PUCRA_RESET_VALUE);
  LL_PWR_WriteReg(PDCRA, PWR_PDCRA_RESET_VALUE);
  LL_PWR_WriteReg(PUCRB, PWR_PUCRB_RESET_VALUE);
  LL_PWR_WriteReg(PDCRB, PWR_PDCRB_RESET_VALUE);
  LL_PWR_WriteReg(IOxCFG, PWR_IOxCFG_RESET_VALUE);
  LL_PWR_WriteReg(ENGTRIM, PWR_ENGTRIM_RESET_VALUE);
  
  /* Clear all flags */
  LL_PWR_WriteReg(SR1,
                    LL_PWR_EWS_INT
                  | LL_PWR_EWS_BLEHOST 
                  | LL_PWR_EWS_BLE     
                  | LL_PWE_EWS_EW11    
                  | LL_PWE_EWS_EW10    
                  | LL_PWE_EWS_EW9     
                  | LL_PWE_EWS_EW8     
                  | LL_PWE_EWS_EW7     
                  | LL_PWE_EWS_EW6     
                  | LL_PWE_EWS_EW5     
                  | LL_PWE_EWS_EW4     
                  | LL_PWE_EWS_EW3     
                  | LL_PWE_EWS_EW2     
                  | LL_PWE_EWS_EW1     
                  | LL_PWE_EWS_EW0
                 );

  
  return SUCCESS;
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
#endif /* defined(PWR) */
/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
