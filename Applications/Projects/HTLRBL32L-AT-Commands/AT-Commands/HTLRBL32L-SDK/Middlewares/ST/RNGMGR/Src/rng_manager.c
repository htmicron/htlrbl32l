/**
******************************************************************************
* @file    rng_manager.c
* @author  AMS - RF Application Team
* @brief   This file provides weak functions for RNG Manager
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

/* Includes ------------------------------------------------------------------*/
#include "rng_manager.h"
#include "rf_driver_ll_rng.h"
#include "rf_driver_ll_bus.h"


/** @defgroup RNG_Manager  RNG MANAGER
* @{
*/

/** @defgroup RNGMGR_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup RNGMGR_Private_Defines Private Defines
* @{
*/
/**
* @}
*/

/** @defgroup RNGMGR_Private_Macros Private Macros
* @{
*/
/**
* @}
*/

/** @defgroup RNGMGR_Private_Variables Private Variables
* @{
*/  
/**
* @}
*/

/** @defgroup RNGMGR_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup RNGMGR_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
/**
* @}
*/

/** @defgroup RNGMGR_Public_Functions Public Functions
* @{
*/
WEAK_FUNCTION(RNGMGR_ResultStatus RNGMGR_Init(void))
{
  return RNGMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(RNGMGR_ResultStatus RNGMGR_Deinit(void))
{
  return RNGMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(RNGMGR_ResultStatus RNGMGR_NewSecretKey(uint32_t* buffer))
{
  return RNGMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(RNGMGR_ResultStatus  RNGMGR_GetRandom16(uint32_t* buffer, uint8_t isr))
{
  return RNGMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}


/**
* @}
*/
