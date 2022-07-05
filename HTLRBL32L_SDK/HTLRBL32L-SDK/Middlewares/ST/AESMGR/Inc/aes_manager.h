/**
 ******************************************************************************
 * @file    aes_manager.h
 * @author  AMS - RF Application Team
 * @brief   This file contains all the functions prototypes for the AES MANAGER.
 *
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
#ifndef AESMGR_H
#define AESMGR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
  
/** @addtogroup AESMGR_Peripheral  AES MANAGER
 * @{
 */

/** @defgroup AESMGR_Exported_Types Exported Types
 * @{
 */
	
/* Enumerated values used to report the AES result status after a process */
typedef enum
{
  AESMGR_SUCCESS     =  0,
  AESMGR_ERROR
} AESMGR_ResultStatus;

/**
 * @}
 */

/** @defgroup AESMGR_Exported_Constants  Exported Constants
 * @{
 */
/**
 * @}
 */

/** @defgroup AESMGR_Exported_Macros           Exported Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup AESMGR_Exported_Functions        Exported Functions
 * @{
 */
AESMGR_ResultStatus AESMGR_Init(void);

AESMGR_ResultStatus AESMGR_Deinit(void);

AESMGR_ResultStatus AESMGR_Encrypt(const uint32_t *plainTextData, const uint32_t *key, uint32_t *encryptedData, uint8_t isr);

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

#endif /* AESMGR_H */
