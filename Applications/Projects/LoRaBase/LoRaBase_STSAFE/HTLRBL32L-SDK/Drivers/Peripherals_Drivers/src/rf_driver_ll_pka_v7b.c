/**
  ******************************************************************************
  * @file    rf_driver_ll_pka_v7b.c
  * @author  RF Application Team
  * @brief   PKA LL module driver.
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
#include "rf_driver_ll_pka_v7b.h"
#include "rf_driver_ll_bus.h"

#ifdef  USE_FULL_ASSERT
#include "rf_driver_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined(PKA)

/** @addtogroup PKA_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* 0b0000 00XY. X: PKA_DATA_PCX error Y: PKA_DATA_PCY error */
static uint8_t PKA_SetDataError = 0x00;   

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup PKA_LL_Private_Macros PKA Private Constants
  * @{
  */
#define IS_LL_PKA_CMD(CMD) ( ((CMD) == LL_PKA_DATA_SK) ||  \
                             ((CMD) == LL_PKA_DATA_PCX) || \
                             ((CMD) == LL_PKA_DATA_PCY) )
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
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

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PKA_LL_Exported_Functions
  * @{
  */

/** @addtogroup PKA_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize PKA registers (Registers restored to their default values).
  * @param  PKAx PKA Instance.
  * @retval ErrorStatus
  *          - SUCCESS: PKA registers are de-initialized
  *          - ERROR: PKA registers are not de-initialized
  */
ErrorStatus LL_PKA_DeInit(PKA_TypeDef *PKAx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_PKA_ALL_INSTANCE(PKAx));

  if (PKAx == PKA)
  {
    /* Force PKA reset */
    LL_AHB_ForceReset(LL_AHB_PERIPH_PKA);

    /* Release PKA reset */
    LL_AHB_ReleaseReset(LL_AHB_PERIPH_PKA);
  }
  else
  {
    status = ERROR;
  }

  return (status);
}

/**
  * @brief  Initialize PKA registers according to the specified parameters in PKA_InitStruct.
  * @param  PKAx PKA Instance.
  * @param  PKA_InitStruct pointer to a @ref LL_PKA_InitTypeDef structure
  *         that contains the configuration information for the specified PKA peripheral.
  * @retval ErrorStatus
  *          - SUCCESS: PKA registers are initialized according to PKA_InitStruct content
  *          - ERROR:   Not applicable
  */
ErrorStatus LL_PKA_Init(PKA_TypeDef *PKAx)
{
  assert_param(IS_PKA_ALL_INSTANCE(PKAx));

  LL_PKA_SWReset(PKAx);
  LL_PKA_SWResetRelease(PKAx);

  return (SUCCESS);
}

/**
  * @brief  Wait loop for READY status
  * @param  PKAx PKA Instance.
  * @retval None
  */
void LL_PKA_WaitEndProcess(PKA_TypeDef *PKAx)
{
  assert_param(IS_PKA_ALL_INSTANCE(PKAx));
  
  /* Wait PKA processing end */
  while(!LL_PKA_Ready(PKAx));
}

/**
  * @brief  PKA verification of process command.
  * @param  None
  * @retval ErrorStatus
  */
ErrorStatus LL_PKA_VerifyProcess(void)
{
  uint32_t errorCode;
  
  if(PKA_SetDataError != 0x00) 
    return ERROR;

  errorCode = *(uint32_t *)(PKA_RAM_ECC_ADDR_KP_ERROR);
  
  if (errorCode == 0) {
    return SUCCESS;
  }
  else {
    return ERROR;
  }
}

/**
  * @brief  Write the PKA RAM with the input data.
  * @param  dataType: select the region of PKA RAM to write:
  *         @arg LL_PKA_DATA_SK is the K value
  *         @arg LL_PKA_DATA_PCX is the point X coordinate
  *         @arg LL_PKA_DATA_PCY is the point Y coordinate
  * @param  srcData Source Data
  * @retval ErrorStatus
  */
ErrorStatus LL_PKA_SetData(uint8_t dataType, uint32_t* srcData)
{
  const uint8_t P256_P_LE[32] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xff,0xff,0xff,0xff}; 
  const uint8_t BLE_P256_ABELIAN_ORDER_R_LE[32] = {0x51,0x25,0x63,0xFC,0xC2,0xCA,0xB9,0xF3,0x84,0x9E,0x17,0xA7,0xAD,0xFA,0xE6,0xBC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
  uint32_t StartAddress;
  uint8_t idx;
  
  /* Check the parameters */
  assert_param(IS_LL_PKA_CMD(dataType));
  
  if (dataType == LL_PKA_DATA_SK) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)BLE_P256_ABELIAN_ORDER_R_LE, 32) >= 0) {
      PKA_SetDataError |= 0x04;
      return ERROR;
    }
    else {
      PKA_SetDataError &= ~0x04;
    }
    StartAddress = PKA_RAM_ECC_ADDR_K;
  }
  
  else if (dataType == LL_PKA_DATA_PCX) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)P256_P_LE, 32) >= 0) {
      PKA_SetDataError |= 0x01;
      return ERROR;
    }
    else {
      PKA_SetDataError &= ~0x01;
    }
    StartAddress = PKA_RAM_ECC_ADDR_PX;

  }
  
  else if (dataType == LL_PKA_DATA_PCY) {
    if (rev_memcmp((uint8_t *) srcData, (uint8_t *)P256_P_LE, 32) >= 0) {
      PKA_SetDataError |= 0x02;
      return ERROR;
    }
    else {
      PKA_SetDataError &= ~0x02;
    }
    StartAddress = PKA_RAM_ECC_ADDR_PY;
  }
  else 
    return ERROR;

  /* Write the source data to target PKA RAM address. */
  for (idx = 0; idx<8; idx++)
  {
    *(uint32_t *)(StartAddress + 4*idx) = srcData[idx];
  }
  
  /* A 9th word of zeros must be added */
  *(uint32_t *)(StartAddress + 32UL) = 0x00000000;
  
  return SUCCESS;
}

/**
  * @brief  Get from the PKA RAM the output data.
  * @param  dataType: select the region of PKA RAM to read:
  *         @arg LL_PKA_DATA_SK is the K value
  *         @arg LL_PKA_DATA_PCX is the point X coordinate
  *         @arg LL_PKA_DATA_PCY is the point Y coordinate
  * @param  dataTarget PKA RAM output data
  * @retval ErrorStatus
  */
ErrorStatus LL_PKA_GetData(uint8_t dataType, uint8_t* dataTarget)
{
  uint32_t StartAddress;
  
  /* Check the parameters */
  assert_param(IS_LL_PKA_CMD(dataType));
  
  if (dataType == LL_PKA_DATA_SK)
    StartAddress = PKA_RAM_ECC_ADDR_K;
  else if (dataType == LL_PKA_DATA_PCX)
    StartAddress = PKA_RAM_ECC_ADDR_PX;
  else if (dataType == LL_PKA_DATA_PCY)
    StartAddress = PKA_RAM_ECC_ADDR_PY;
  else return ERROR;
  
  /* Read the data to target PKA RAM address. */
  for(uint8_t i=0;i<32;i++) {
    dataTarget[i] = ((uint8_t *)StartAddress)[i];
  }
  
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

#endif /* defined (PKA) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

