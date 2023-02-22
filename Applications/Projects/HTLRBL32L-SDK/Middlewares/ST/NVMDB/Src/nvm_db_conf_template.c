/**
 ******************************************************************************
 * @file    nvm_db_conf_template.c
 * @author  AMG RF application team
 * @version V1.0.0
 * @date    April 06, 2018
 * @brief   This file provides the structure of the database.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
 * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
 * IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
 *
 * <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "nvm_db_conf.h"

/** @defgroup NVM_Manager_Conf_Templ  NVM Manager Configuration Template
 * @{
 */

/** @defgroup NVM_Manager_Conf_Templ_TypesDefinitions NVM Configuration Template Private Type Definitions
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_Manager_Private_Defines NVM Configuration Template Private Defines
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_Manager_Conf_Template_Private_Macros NVM Manager Configuration Template Private Macros
 * @{
 */

#define FLASH_NVM_DATASIZE  (5 * PAGE_SIZE)  // Make sure this space is reserved in the linker script.
#define NVM_START_ADDRESS   (_MEMORY_FLASH_END_ - FLASH_NVM_DATASIZE + 1)

#define DB0_SIZE  (PAGE_SIZE / 2)
#define DB1_SIZE  (PAGE_SIZE / 2)
#define DB2_SIZE  (PAGE_SIZE * 2)
#define DB3_SIZE  (PAGE_SIZE * 2 - 8)   // Last 8 bytes in Flash are reserved for the lock/unlock word.

/**
 * @}
 */

/** @defgroup NVM_Manager_Conf_Constants NVM Manager Configuration Constants
 * @{
 */
const NVMDB_SmallDBType dbs[NUM_SMALL_DBS] = { { .id = 0,
                                                 .offset = 0,
#if AUTO_CLEAN
                                                 .clean_threshold = DB0_SIZE / 3
#endif
                                               },
                                               { .id = 1,
                                                 .offset = DB0_SIZE,
#if AUTO_CLEAN
                                                 .clean_threshold = DB1_SIZE / 3
#endif
                                               } };

const NVMDB_SmallDBContainerType NVM_SMALL_DB_STATIC_INFO[NUM_SMALL_DB_PAGES] = { { .page_address = NVM_START_ADDRESS, .num_db = NUM_SMALL_DBS, .dbs = dbs } };
const NVMDB_StaticInfoType NVM_LARGE_DB_STATIC_INFO[NUM_LARGE_DBS] = { {
                                                                         .address = NVM_START_ADDRESS + PAGE_SIZE * NUM_SMALL_DB_PAGES,
                                                                         .size = DB2_SIZE,
                                                                         .id = 2,
#if AUTO_CLEAN
                                                                         .clean_threshold = DB2_SIZE / 4
#endif
                                                                       },
                                                                       {
                                                                         .address = NVM_START_ADDRESS + PAGE_SIZE * NUM_SMALL_DB_PAGES + DB2_SIZE,
                                                                         .size = DB3_SIZE,
                                                                         .id = 3,
#if AUTO_CLEAN
                                                                         .clean_threshold = DB3_SIZE / 4
#endif
                                                                       }, };

/**
 * @}
 */

/**
 * @}
 */
