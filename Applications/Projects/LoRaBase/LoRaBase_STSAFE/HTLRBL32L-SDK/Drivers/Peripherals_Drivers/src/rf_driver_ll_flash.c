/**
  ******************************************************************************
  * @file    rf_driver_ll_usart.c
  * @author  RF Application Team
  * @brief   FLASH LL module driver.
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
#include "rf_driver_ll_system.h"
#include "rf_driver_ll_flash.h"
#ifdef  USE_FULL_ASSERT
#include "rf_driver_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined (FLASH)

/** @addtogroup FLASH_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup FLASH_LL_Private_Macros
  * @{
  */

#define IS_LL_FLASH_MAIN_MEM_ADDRESS(__VALUE__)          (((__VALUE__) >= LL_FLASH_START_ADDR) && ((__VALUE__) <= LL_FLASH_END_ADDR))

#define IS_LL_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__VALUE__)  (((__VALUE__) >= LL_FLASH_START_ADDR) && ((__VALUE__) <= (LL_FLASH_START_ADDR + LL_FLASH_SIZE - 4UL)) && (((__VALUE__) % 4UL) == 0UL))

#define IS_LL_FLASH_PROGRAM_OTP_ADDRESS(__VALUE__)       (((__VALUE__) >= OTP_AREA_BASE) && ((__VALUE__) <= (OTP_AREA_END_ADDR + 1UL - 4UL)) && (((__VALUE__) % 4UL) == 0UL))

#define IS_LL_FLASH_PROGRAM_ADDRESS(__VALUE__)           ((IS_LL_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__VALUE__)) || (IS_LL_FLASH_PROGRAM_OTP_ADDRESS(__VALUE__)))

#define IS_LL_FLASH_PAGE(__VALUE__)                      ((__VALUE__) <= LL_FLASH_PAGE_NUMBER)

#define IS_LL_ADDR_ALIGNED_32BITS(__VALUE__)             (((__VALUE__) & ~0x3U) == (__VALUE__))

#define IS_LL_FLASH_WAIT_STATES(__VALUE__)               (((__VALUE__) == LL_FLASH_WAIT_STATES_0) || \
                                                          ((__VALUE__) == LL_FLASH_WAIT_STATES_1))

#define IS_LL_FLASH_TYPE_ERASE(__VALUE__)                (((__VALUE__) == LL_FLASH_TYPE_ERASE_PAGES) || \
                                                         ((__VALUE__) == LL_FLASH_TYPE_ERASE_MASSERASE))


/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup USART_LL_Exported_Functions
  * @{
  */

/**
  * @brief  Program a word at a specified address.
  * @param  FLASHx FLASH Instance
  * @param  Address Specifies the address to be programmed.
  * @param  Data Specifies the data to be programmed.
  *
  * @retval none
  */
void LL_FLASH_Program(FLASH_TypeDef *FLASHx, uint32_t Address, uint32_t Data)
{
  /* Check the parameters */
  assert_param(IS_LL_ADDR_ALIGNED_32BITS(Address));
  assert_param(IS_LL_FLASH_PROGRAM_ADDRESS(Address));

  /* Clear All Flags */
  LL_FLASH_ClearFlag(FLASHx, LL_FLASH_FLAG_CMDDONE|LL_FLASH_FLAG_CMDSTART|LL_FLASH_FLAG_CMDERR|LL_FLASH_FLAG_ILLCMD);

  /* Load the word address */
  FLASHx->ADDRESS = ((Address>>2) & 0xFFFF);
  
  /* Load the data to program */
  FLASHx->DATA0 = Data;
  
  /* Load the WRITE command */
  FLASHx->COMMAND = LL_FLASH_CMD_WRITE;
  
  /* Wait for last operation to be completed */
  while(LL_FLASH_GetFlag(FLASHx, LL_FLASH_FLAG_CMDDONE) != SET);
}

/**
  * @brief  Program 4 words starting from the specified address.
  * @param  FLASHx FLASH Instance
  * @param  Address Specifies the starting address to be programmed.
  * @param  Data Specifies the 4 words data to be programmed.
  *
  * @retval none
  */
void LL_FLASH_ProgramBurst(FLASH_TypeDef *FLASHx, uint32_t Address, uint32_t *Data)
{
  /* Check the parameters */
  assert_param(IS_LL_ADDR_ALIGNED_32BITS(Address));
  assert_param(IS_LL_FLASH_PROGRAM_ADDRESS(Address));

  /* Clear All Flags */
  LL_FLASH_ClearFlag(FLASHx, LL_FLASH_FLAG_CMDDONE|LL_FLASH_FLAG_CMDSTART|LL_FLASH_FLAG_CMDERR|LL_FLASH_FLAG_ILLCMD);

  /* Load the word address */
  FLASHx->ADDRESS = ((Address>>2) & 0xFFFF);
  
  /* Load the data to program */
  FLASHx->DATA0 = Data[0];
  FLASHx->DATA1 = Data[1];
  FLASHx->DATA2 = Data[2];
  FLASHx->DATA3 = Data[3];
        
  /* Load the BURST WRITE command */
  FLASHx->COMMAND = LL_FLASH_CMD_BURSTWRITE;
  
  /* Wait for last operation to be completed */
  while(LL_FLASH_GetFlag(FLASHx, LL_FLASH_FLAG_CMDDONE) != SET);
}

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages.
  * @param  FLASHx FLASH Instance
  * @param  TypeErase This parameter can be a value of:
  *           @ref LL_FLASH_TYPE_ERASE_PAGES
  *           @ref LL_FLASH_TYPE_ERASE_MASSERASE
  * @param  Page Initial Flash page to erase when page erase is enabled.
  *              This parameter must be a value between 0 and (max number of pages - 1)
  * @param  NbPages Number of pages to be erased
  *
  * @retval none
  */
void LL_FLASH_Erase(FLASH_TypeDef *FLASHx, uint32_t TypeErase, uint32_t Page, uint32_t NbPages)
{
  uint32_t index;

  /* Check the parameters */
  assert_param(IS_LL_FLASH_TYPE_ERASE(TypeErase));

  /* Verify that next operation can be proceed */
  if (TypeErase == LL_FLASH_TYPE_ERASE_MASSERASE)
  {
      /* Clear All Flags */
    LL_FLASH_ClearFlag(FLASHx, LL_FLASH_FLAG_CMDDONE|LL_FLASH_FLAG_CMDSTART|LL_FLASH_FLAG_CMDERR|LL_FLASH_FLAG_ILLCMD);

    /* MASSERASE command */
    FLASHx->COMMAND = LL_FLASH_CMD_MASSERASE;

    /* Wait for last operation to be completed */
    while(LL_FLASH_GetFlag(FLASHx, LL_FLASH_FLAG_CMDDONE) != SET);
  }
  else
  {
    for(index = Page; index < (Page + NbPages); index++)
    {
        /* Clear All Flags */
      LL_FLASH_ClearFlag(FLASHx, LL_FLASH_FLAG_CMDDONE|LL_FLASH_FLAG_CMDSTART|LL_FLASH_FLAG_CMDERR|LL_FLASH_FLAG_ILLCMD);

      /* Write the page address */
      FLASHx->ADDRESS = (((index * LL_FLASH_PAGE_SIZE)>>2) & 0xFFFF);
  
      /* Write the ERASE command */
      FLASHx->COMMAND = LL_FLASH_CMD_ERASE_PAGES;

      /* Wait for last operation to be completed */
      while(LL_FLASH_GetFlag(FLASHx, LL_FLASH_FLAG_CMDDONE) != SET);
    }
  }
}

/**
  * @brief  Program a word at a specified OTP address.
  * @param  FLASHx FLASH Instance
  * @param  Address Specifies the address to be programmed.
  * @param  Data Specifies the data to be programmed.
  *
  * @retval none
  */
void LL_FLASH_OTPWrite(FLASH_TypeDef *FLASHx, uint32_t Address, uint32_t Data)
{
  uint16_t otp_address, addr_offset;
  
  /* Check the parameters */
  assert_param(IS_LL_ADDR_ALIGNED_32BITS(Address));
  assert_param(IS_LL_FLASH_PROGRAM_OTP_ADDRESS(Address));

  /* Clear All Flags */
  LL_FLASH_ClearFlag(FLASHx, LL_FLASH_FLAG_CMDDONE|LL_FLASH_FLAG_CMDSTART|LL_FLASH_FLAG_CMDERR|LL_FLASH_FLAG_ILLCMD);

  addr_offset = Address - OTP_AREA_BASE;
  otp_address = (((addr_offset & 0x300)>>2)| ((addr_offset & 0xFF)>>2));
  
  /* Load the word address */
  FLASHx->ADDRESS = otp_address;
  
  /* Load the data to program */
  FLASHx->DATA0 = Data;
  
  /* Load the OTP WRITE command */
  FLASHx->COMMAND = LL_FLASH_CMD_OTPWRITE;
  
  /* Wait for last operation to be completed */
  while(LL_FLASH_GetFlag(FLASHx, LL_FLASH_FLAG_CMDDONE) != SET);
}

/**
  * @brief  Page Protection function. It allows protecting from write and page erase 
  *         by group of 8 pages
  * @param  FLASHx FLASH Instance
  * @param  pageProt_0 It is a Bitfield built as follows:
  *                               - bit[6:0] = SIZE: number of 2 kB pages to protect including the starting page@ref pageProt_0 param
  *                                                 (provided in the offset bits)
  *                               - bit[7]: reserved
  *                               - bit[14:8] = OFFSET: page number to start the write protection 
  *                                                    (value between 0 and 0x7F)
  *                               - bit[15]: reserved
  *                               - bit[22:16] = SIZE: same meaning of bit[6:0]
  *                               - bit[23]: reserved
  *                               - bit[30:24] = OFFSET: same meaning of bit[22:16]
  *                               - bit[31]: reserved
  * @param  pageProt_1 Same meaning of @ref pageProt_0 param
  * @param  state this parameter can be: ENABLE DISABLE 
  * @retval none
  */
void LL_FLASH_PageProtection(FLASH_TypeDef *FLASHx, uint32_t pageProt_0, uint32_t pageProt_1, FunctionalState state)
{
  /* Check the parameters */
  assert_param(IS_LL_FUNCTIONAL_STATE(state));

  if (state == ENABLE)
  {
    FLASHx->PAGEPROT0 |= pageProt_0;
    if (pageProt_1 != 0)
    {
      FLASHx->PAGEPROT1 |= pageProt_1;
    }
  }
  else
  {
    FLASHx->PAGEPROT0 &= ~pageProt_0;
    if (pageProt_1 != 0)
    {
      FLASHx->PAGEPROT1 &= ~pageProt_1;
    }
  }
}

/**
  * @}
  */


/**
  * @}
  */

#endif /* FLASH */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
