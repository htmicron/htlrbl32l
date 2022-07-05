/** 
  ******************************************************************************
  * @file    bluenrg_lp_evb_com.h
  * @author  RF Application Team
  * @brief   This file contains definitions to manage the UART communication.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLUENRG_LP_EVB_COM_H
#define __BLUENRG_LP_EVB_COM_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup BSP
  * @{
  */

/** @addtogroup BSP_BLUENRGLP_COM BSP BlueNRG-LP COM
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lp_evb_config.h"
#include <stdio.h>
   

/** @defgroup BSP_BLUENRGLP_COM_Exported_Types
 * @{
 */

/**
 * @brief  BSP_COM_RxDataCb_t User callback type 
 */
typedef void (* BSP_COM_RxDataCb_t) (uint8_t * pRxDataBuff, uint16_t nDataSize);


/**
 * @}
 */


/** @addtogroup BSP_BLUENRGLP_COM_Exported_Functions
  * @{
  */

void BSP_COM_Init(BSP_COM_RxDataCb_t pRxDataCb);
void BSP_COM_DeInit(void);
void BSP_COM_Write(uint8_t *pBuff, uint8_t nBuffSize);
uint8_t BSP_COM_Read(uint8_t *pData);
void BSP_COM_IRQHandler(void);

void BSP_COM_RxDataUserCb(uint8_t * pRxDataBuff, uint16_t nDataSize);
uint8_t BSP_COM_TxFifoNotEmpty(void);
uint8_t BSP_COM_UARTBusy(void);

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

#endif /* __BLUENRG_LP_EVB_COM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

