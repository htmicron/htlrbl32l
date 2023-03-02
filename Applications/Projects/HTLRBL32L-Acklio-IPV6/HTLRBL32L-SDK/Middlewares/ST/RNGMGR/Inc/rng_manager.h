/**
 ******************************************************************************
 * @file    rng_manager.h
 * @author  AMS - RF Application Team
 * @brief   This file contains all the functions prototypes for the RNG MANAGER.
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
#ifndef RNGMGR_H
#define RNGMGR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
  
/** @addtogroup RNGMGR_Peripheral  RNG MANAGER
 * @{
 */

/** @defgroup RNGMGR_Exported_Types Exported Types
 * @{
 */
	
/* Enumerated values used to report the RNG result status after a process */
typedef enum
{
  RNGMGR_SUCCESS     =  0,
  RNGMGR_ERROR,
  RNGMGR_ERROR_TIMEOUT
} RNGMGR_ResultStatus;

/**
 * @}
 */

/** @defgroup RNGMGR_Exported_Constants  Exported Constants
 * @{
 */
/**
 * @}
 */

/** @defgroup RNGMGR_Exported_Macros           Exported Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup RNGMGR_Exported_Functions        Exported Functions
 * @{
 */
RNGMGR_ResultStatus RNGMGR_Init(void);

RNGMGR_ResultStatus RNGMGR_Deinit(void);

RNGMGR_ResultStatus RNGMGR_NewSecretKey(uint32_t* buffer);

RNGMGR_ResultStatus RNGMGR_GetRandom16(uint32_t* buffer, uint8_t isr);


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

#endif /* RNGMGR_H */
