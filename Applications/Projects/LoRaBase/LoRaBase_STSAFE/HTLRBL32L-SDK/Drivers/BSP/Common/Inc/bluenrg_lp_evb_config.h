/** 
  ******************************************************************************
  * @file    bluenrg_lp_evb_config.h
  * @author  RF Application Team
  * @brief   This file includes the resources available in a BlueNRG-LP Eval Kit.
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
#ifndef __BLUENRG_LP_EVB_CONFIG_H
#define __BLUENRG_LP_EVB_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup BLUENRGLP_EVB_Private_Defines Private Defines
  * @{
  */ 

/**
  * @brief BLUENRGLP EVB BSP Driver
  */
#define __BLUENRGLP_EVB_BSP_VERSION_MAIN   (0x00U) /*!< [31:24] main version */
#define __BLUENRGLP_EVB_BSP_VERSION_SUB1   (0x00U) /*!< [23:16] sub1 version */
#define __BLUENRGLP_EVB_BSP_VERSION_SUB2   (0x02U) /*!< [15:8]  sub2 version */
#define __BLUENRGLP_EVB_BSP_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */ 
#define __BLUENRGLP_EVB_BSP_VERSION        ((__BLUENRGLP_EVB_BSP_VERSION_MAIN << 24)\
                                             |(__BLUENRGLP_EVB_BSP_VERSION_SUB1 << 16)\
                                             |(__BLUENRGLP_EVB_BSP_VERSION_SUB2 << 8 )\
                                             |(__BLUENRGLP_EVB_BSP_VERSION_RC))   
/**
  * @}
  */ 

/* BlueNRG-LP Development platform: STEVAL-IDB011V1 */
#include "system_BlueNRG_LP.h"

#if defined(STEVAL_IDB010V1)
/* BlueNRG-LP CSP eval kit */
#include "steval_idb010V1_config.h"
#include "bluenrg_lp_evb_led.h" 
#include "bluenrg_lp_evb_button.h"
#include "bluenrg_lp_evb_spi.h"
#include "bluenrg_lp_evb_i2c.h"

#include "lsm6dsox_reg.h"
#include "lps22hh_reg.h"

#else
/* Default configuration is STEVAL_IDB011V1 */
#include "steval_idb011V1_config.h"
#include "bluenrg_lp_evb_led.h" 
#include "bluenrg_lp_evb_button.h"
#include "bluenrg_lp_evb_spi.h"
#include "bluenrg_lp_evb_i2c.h"

#include "lsm6dsox_reg.h"
#include "lps22hh_reg.h"

#endif



/** @defgroup STATIC INLINE functions
  * @{
  */ 

__STATIC_INLINE uint32_t BSP_GetVersion(void){return __BLUENRGLP_EVB_BSP_VERSION;} 

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __BLUENRG_LP_EVB_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
