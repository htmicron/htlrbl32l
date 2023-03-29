/**
 ******************************************************************************
 * @file    nvm_db_conf.c
 * @author  AMS - RF Application Team
 * @brief   This file provides the structure of the database.
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
#include "nvm_db_conf.h"
#include <stdlib.h>

/** @defgroup NVM_Manager  NVM Manager
 * @{
 */

/** @defgroup NVM_Manager_TypesDefinitions Private Type Definitions
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_Manager_Private_Defines Private Defines
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_Manager_Conf_Private_Macros NVM Manager Configuration Private Macros
 * @{
 */

#if PRESET1

#define FLASH_NVM_DATASIZE  (2 * PAGE_SIZE)  // Make sure this space is reserved in the linker script.
#define NVM_START_ADDRESS   (_MEMORY_FLASH_END_ - FLASH_NVM_DATASIZE + 1)

#define DB0_SIZE  (PAGE_SIZE)
#define DB1_SIZE  (PAGE_SIZE - 8) // Last 8 bytes in Flash are reserved for the lock/unlock word.

#elif PRESET2

#define FLASH_NVM_DATASIZE  (1 * PAGE_SIZE)  // Make sure this space is reserved in the linker script.
#define NVM_START_ADDRESS   (_MEMORY_FLASH_END_ - FLASH_NVM_DATASIZE + 1)

#define DB0_SIZE  (PAGE_SIZE - 8 - 64) // Last 8 bytes in Flash are reserved for the lock/unlock word.
#define DB1_SIZE  (64)

#endif

/**
 * @}
 */

/** @defgroup NVM_Manager_Conf_Constants NVM Manager Configuration Constants
 * @{
 */

#if PRESET1

const NVMDB_SmallDBContainerType *NVM_SMALL_DB_STATIC_INFO = NULL;
const NVMDB_StaticInfoType NVM_LARGE_DB_STATIC_INFO[NUM_LARGE_DBS] =
{
  {
    .address = NVM_START_ADDRESS,
    .size = DB0_SIZE,
    .id = 0,
#if AUTO_CLEAN
    .clean_threshold = DB0_SIZE / 3
#endif
  },
  {
    .address = NVM_START_ADDRESS + DB0_SIZE,
    .size = DB1_SIZE,
    .id = 1,
#if AUTO_CLEAN
    .clean_threshold = 0
#endif
  },
};

#elif PRESET2

const NVMDB_SmallDBType dbs[NUM_SMALL_DBS] =
{
  {
    .id = 0,
    .offset = 0,
#if AUTO_CLEAN
    .clean_threshold = DB0_SIZE / 3
#endif
  },
  {
    .id = 1,
    .offset = DB0_SIZE,
#if AUTO_CLEAN
    .clean_threshold = 0
#endif
  }
};

const NVMDB_SmallDBContainerType NVM_SMALL_DB_STATIC_INFO[NUM_SMALL_DB_PAGES] = { { .page_address = NVM_START_ADDRESS, .num_db = NUM_SMALL_DBS, .dbs = dbs } };
const NVMDB_StaticInfoType *NVM_LARGE_DB_STATIC_INFO = NULL;

#endif /* PRESET2 */

/**
 * @}
 */

/**
 * @}
 */
