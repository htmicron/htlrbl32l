/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/bluenrg_lp_it.h
  * @author  RF Application Team
  * @brief   This file contains the headers of the interrupt handlers.
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
#ifndef __BLUENRG_LP_IT_H
#define __BLUENRG_LP_IT_H

#include "BlueNRG_LP.h"

#ifdef __cplusplus
 extern "C" {
#endif 

/* Private includes ----------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define DMA_IDLE        0
#define DMA_IN_PROGRESS 1

extern uint8_t command_in_progress;
extern uint8_t dma_state;
/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void NMI_IRQHandler(void);
void HardFault_IRQHandler(void);

void SVC_IRQHandler(void);
void PendSV_IRQHandler(void);
void SysTick_IRQHandler(void);
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BLUENRG_LP_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
