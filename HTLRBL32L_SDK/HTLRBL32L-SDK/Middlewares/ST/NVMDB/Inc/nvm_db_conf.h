/**
 ******************************************************************************
 * @file    nvm_db_conf.h
 * @author  AMS - RF Application Team
 * @brief   Header file for NVM manager, that can be customized.
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
#ifndef NVM_DB_CONF_H
#define NVM_DB_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "system_bluenrg_lp.h"
#include "rf_driver_ll_flash.h"

#ifndef AUTO_CLEAN
#define AUTO_CLEAN 1
#endif

/** @addtogroup NVM_Manager_Peripheral  NVM Manager
 * @{
 */

/** @defgroup NVM_Manager_Exported_Types Exported Types
 * @{
 */

typedef struct
{
  uint8_t id;           // Database id.
  uint32_t offset;      // Offset of the database in the page.
#if AUTO_CLEAN
  uint16_t clean_threshold;      // Threshold of free space under which a clean operation is triggered. Set to 0 to disable.
#endif
} NVMDB_SmallDBType;

typedef struct
{
  uint32_t page_address;                    // Start address of the page where the databases are located.
  uint8_t num_db;                           // Number of databases inside the page.
  const NVMDB_SmallDBType *dbs;             // Pointer to an array, where each element is the offset of each database in the page.
} NVMDB_SmallDBContainerType;

typedef struct
{
  uint32_t address;
  uint16_t size;
  uint8_t id;
#if AUTO_CLEAN
  uint16_t clean_threshold;      // Threshold of free space under which a clean operation is triggered. Set to 0 to disable.
#endif
} NVMDB_StaticInfoType;

/**
 * @}
 */

/** @defgroup NVM_Manager_Exported_Constants  Exported Constants
 * @{
 */

#define PAGE_SIZE _MEMORY_BYTES_PER_PAGE_ // It specifies the minimum size that can be erased. It must be multiple of 2.

/* Change the following macros in order to match the desired database set. */

#define SEC_GATT_BD     0
#define DEVICE_ID_DB    1

#define PRESET1 1

#if PRESET1

#define NUM_SMALL_DB_PAGES      0
#define NUM_SMALL_DBS           0
#define NUM_LARGE_DBS           2

#elif PRESET2

#define NUM_SMALL_DB_PAGES     1
#define NUM_SMALL_DBS          2
#define NUM_LARGE_DBS          0

#endif

#define NUM_DB (NUM_SMALL_DBS + NUM_LARGE_DBS)

/**
 * @}
 */

/** @defgroup NVM_Manager_Exported_Macros           Exported Macros
 * @{
 */

#define WORD_WRITE_TIME_US     65                                               // In microsecond units
#define WORD_WRITE_TIME_SYS    ((int)(WORD_WRITE_TIME_US * 256 / 625) + 1)            // In system time units
#define PAGE_ERASE_TIME_US     22000                                            // In microsecond units
#define PAGE_ERASE_TIME_SYS    ((int)(PAGE_ERASE_TIME_US * 256 / 625) + 1)            // In system time units

#define PAGE_WRITE_TIME_MS     ((PAGE_SIZE / 4 * WORD_WRITE_TIME_US) / 1000 + 1)
#define MARGIN_TIME_SYS        10                                               // In system time units

#define NVMDB_FLASH_WRITE(address, word)  LL_FLASH_Program(FLASH, address, word)
#define NVMDB_FLASH_ERASE_PAGE(page_num, num_pages)   LL_FLASH_Erase(FLASH, LL_FLASH_TYPE_ERASE_PAGES, (page_num), (num_pages))


/**
 * @}
 */

/** @defgroup NVM_Manager_Exported_Functions        Exported Functions
 * @{
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

#endif /* NVM_DB_CONF_H */
