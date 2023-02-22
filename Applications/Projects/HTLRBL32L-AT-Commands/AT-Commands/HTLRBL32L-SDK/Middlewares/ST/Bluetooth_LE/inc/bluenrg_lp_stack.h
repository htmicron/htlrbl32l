#ifndef BLUENRGLP_STACK_H
#define BLUENRGLP_STACK_H
/**
  ******************************************************************************
 * @file    bluenrg_lp_stack.h
  * @author  AMS - RF Application team
 * @brief   Header file for BlueNRG-LP Bluetooth LE stack
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
#include <stdint.h>
#include "ble_status.h"
#include "bluenrg_lp_api.h"
#include "bluenrg_lp_events.h"

#define MIN(a,b)                        (((a) < (b))? (a) : (b))
#define MAX(a,b)                        (((a) > (b))? (a) : (b))
#define DIV_CEIL(x, y)                  (((x) + (y) - 1) / (y))

/** 
 * BLE_STACK_DEFAULT_ATT_MTU: minimum mtu value that GATT must support.
 * 5.2.1 ATT_MTU, BLUETOOTH SPECIFICATION Version 4.2 [Vol 3, Part G]
 */
#define BLE_STACK_DEFAULT_ATT_MTU                 (23U)

#define BLE_STACK_MEM_BLOCK_SIZE                  (32)


/**
 * @name  BLE_STACK_L2CAP_MPS_OCTETS
 * @brief Minimum and Maximum supported MPS values for L2CAP component.
 * @see   BLE Spec. v.5.2, Vol.3, Part A, Sec.4.1, Table 4.1
 * @{
 */
#define BLE_STACK_L2CAP_MPS_OCTETS_MIN             (23U)
#define BLE_STACK_L2CAP_MPS_OCTETS_MAX             (1024U) /* MPS limited to 1KB */
/**
 * @}
 */


/**
 * BLE_STACK_SM_SECURE_CONN_MTU: mtu size needed for Security Manager Channel Configuration
 * Parameters with LE Secure Connections.
 * 3.2 SECURITY MANAGER CHANNEL OVER L2CAP, BLUETOOTH SPECIFICATION Version 4.2
 * [Vol 3, Part H]
 */
#define BLE_STACK_SM_SECURE_CONN_MTU              (65)

/*
 * BLE_STACK_MAX_ATT_MTU: maximum supported ATT_MTU size.
 */
#define BLE_STACK_MAX_ATT_MTU                     (1024U - 4U)  // (4 bytes for L2CAP header)

/**
 * BLE_STACK_DEFAULT_MAX_ATT_MTU: default max ATT_MTU size.
 */
#define BLE_STACK_DEFAULT_MAX_ATT_MTU             (251 - 4) // (4 bytes for L2CAP header)

/**
 * BLE_STACK_DEFAULT_MAX_ATT_SIZE: maximum attribute size.
 */
#define BLE_STACK_DEFAULT_MAX_ATT_SIZE            (512)

/**
 * BLE_STACK_MEM_BLOCK_X_MTU(mtu, n_links): compute how many memory blocks are needed to
 * support a maximum number (n_links)of simultaneous connections that use ATT
 * packet with ATT_MTU=mtu.
 * 7.2 FRAGMENTATION AND RECOMBINATION, BLUETOOTH SPECIFICATION Version 4.2
 * [Vol 3, Part A]
 */

#define BLE_STACK_MEM_BLOCK_X_TX(mtu)             (DIV_CEIL((mtu) + 4U, BLE_STACK_MEM_BLOCK_SIZE) + 1U)
#define BLE_STACK_MEM_BLOCK_X_RX(mtu, n_link)     ((DIV_CEIL((mtu) + 4U, BLE_STACK_MEM_BLOCK_SIZE) + 2U) * (n_link) + 1)
#define BLE_STACK_MEM_BLOCK_X_MTU(mtu, n_link)    (BLE_STACK_MEM_BLOCK_X_TX(mtu) + BLE_STACK_MEM_BLOCK_X_RX(mtu, (n_link)))

/**
 * Minimum number of blocks required for secure connections
 */
#define BLE_STACK_MBLOCKS_SECURE_CONNECTIONS      (4)

/**
 * BLE_STACK_MBLOCKS_CALC(mtu, n_link): minimum number of buffers needed by the stack.
 * This is the minimum racomanded value and depends on:
 *  - mtu: ATT_MTU size
 *  - n_link: maximum number of simultaneous connections
 */
#define BLE_STACK_MBLOCKS_CALC(mtu, n_link)   (MAX(BLE_STACK_MEM_BLOCK_X_MTU(mtu, n_link), (BLE_STACK_MBLOCKS_SECURE_CONNECTIONS)))

/**
 * BLE_STACK_DEFAULT_MBLOCKS_COUNT: default memory blocks count
 */
#define BLE_STACK_DEFAULT_MBLOCKS_COUNT           BLE_STACK_MBLOCKS_CALC(BLE_STACK_DEFAULT_MAX_ATT_MTU, BLE_STACK_NUM_LINKS)

/**
 * BLE_STACK_GATT_ATTRIBUTE_SIZE: memory used for each attribute entry.
 */
#define BLE_STACK_GATT_ATTRIBUTE_SIZE                       (8U)

/**
 * BLE_STACK_NUM_GATT_MANDATORY_ATTRIBUTES: number of attributes used for
 * mandatory profiles (GATT and GAP).
 */
#define BLE_STACK_NUM_GATT_MANDATORY_ATTRIBUTES             (17U)

/**
 * Amount of memory needed by each GATT Client procedure context
 */
#define COEFF_NUM_GATT_CLIENT_PROCS (36)

/**
 * A part of the RAM, is dinamically allocated by initilizing all the pointers
 * defined in a global context variable "mem_alloc_ctx_p".
 * This initialization is made in the Dynamic_allocator functions, which
 * assing a portion of RAM given by the external application to the above
 * mentioned "global pointers".
 *
 * The size of this Dynamic RAM is made of 2 main components:
 * - a part that is parameters-dependent (num of links, GATT buffers, ...),
 *   and which value is explicited by the following macro;
 * - a part, that may be considered "fixed", i.e. independent from the above
 *   mentioned parameters.
*/
#define BLE_STACK_FIXED_BUFFER_SIZE_BYTES ((2238) + ((BLE_STACK_GATT_ATTRIBUTE_SIZE) * (BLE_STACK_NUM_GATT_MANDATORY_ATTRIBUTES)))

/**
 * Amount of memory needed by each radio link
 */
#define COEFF_NUM_OF_LINKS (684)

/**
 * BLE_STACK_PHY_UPD_SIZE: amount of memory needed to support PHY Update feature
 */
#define BLE_STACK_PHY_UPD_SIZE(ENABLED, NUM_OF_LINKS)       (((ENABLED) == 1) ? (40+(NUM_OF_LINKS *16)) : (0))

/**
 * BLE_STACK_CONTROLLER_EXT_ADV_SIZE: amount of memory needed to support extended advertising and scanning feature
 */
#define BLE_STACK_CONTROLLER_EXT_ADV_SIZE(ENABLED, NUM_OF_LINKS, NUM_ADV_SET, NUM_AUX_EVENT) (((ENABLED) == 1) ? ((NUM_OF_LINKS *0)+164+(272*(NUM_ADV_SET-1))+(112*NUM_ADV_SET)+(NUM_AUX_EVENT*(68))) : (0))

/**
 * BLE_STACK_L2C_COCS_SIZE: amount of memory needed to support L2CAP COCs (Connection Oriented Channels)
 */
#define BLE_STACK_L2C_COCS_SIZE(ENABLED, NUM_OF_COCS)       (((ENABLED) == 1) ? (NUM_OF_COCS *76) : (0))

/**
 * BLE_STACK_D_LEN_EXT_SIZE: amount of memory needed to support Data Length Extension
 * feature.
 */
#define BLE_STACK_D_LEN_EXT_SIZE(LEN_EXT_ENABLED, ADV_EXT_ENABLED)                  ((((LEN_EXT_ENABLED) == 1 )|((ADV_EXT_ENABLED) == 1)) ? (552) : (112))

/**
 * BLE_STACK_CONTROLLER_PERIODIC_ADV_SIZE: amount of memory needed to support periodic advertising and synchronizing feature
 */
#define BLE_STACK_CONTROLLER_PERIODIC_ADV_SIZE(ENABLED, NUM_ADV_SET, NUM_AUX_EVENT, NUM_OF_LINKS, ADV_LIST_LIZE) (((ENABLED) == 1) ? (32 + 168*(NUM_ADV_SET) + 184*(NUM_AUX_EVENT) + 56*(NUM_OF_LINKS) + 8*(1<<ADV_LIST_LIZE)): (0))

/**
 * BLE_STACK_CONTROLLER_PRIV: amount of memory needed to support controller privacy feature
 */
#define BLE_STACK_CONTROLLER_PRIV(ENABLED, WHITE_LIST_SIZE_LOG2) (((ENABLED) == 1) ? (((1<<WHITE_LIST_SIZE_LOG2) *80)+8) : (0))

/**
 * BLE_STACK_CTE_SIZE: amount of memory needed to support CTE feature
 */
#define BLE_STACK_CTE_NUM_OF_LINKS(NUM_OF_LINKS)                                     ((NUM_OF_LINKS) * 8U)
#define BLE_STACK_CTE_NUM_OF_ANT_IDS(NUM_OF_LINKS, NUM_OF_ANT_IDS)                   (((NUM_OF_ANT_IDS) > 0U) ? \
                                                                                      (((0U*(NUM_OF_LINKS))+1U)*((((NUM_OF_ANT_IDS)-1U) | 3U)+1U)) : \
                                                                                      0U)
#define BLE_STACK_CTE_NUM_OF_IQ_SAMPLES(NUM_OF_IQSAMPLES)                            ((NUM_OF_IQSAMPLES) * 4U)

#define BLE_STACK_CTE_SIZE(ENABLED, NUM_OF_LINKS, NUM_OF_ANT_IDS, NUM_OF_IQSAMPLES)  (((ENABLED) == 1U) ?                                            \
                                                                                       (BLE_STACK_CTE_NUM_OF_LINKS(NUM_OF_LINKS)                   + \
                                                                                        BLE_STACK_CTE_NUM_OF_ANT_IDS(NUM_OF_LINKS, NUM_OF_ANT_IDS) + \
                                                                                        BLE_STACK_CTE_NUM_OF_IQ_SAMPLES(NUM_OF_IQSAMPLES) + 8U) : 0U) 

/**
 * BLE_STACK_PCL_SIZE: amount of memory needed to support PCL feature
 */
#define BLE_STACK_PCL_NUM_OF_LINKS(NUM_OF_LINKS)  ((NUM_OF_LINKS) * 32U)
#define BLE_STACK_PCL_SIZE(ENABLED, NUM_OF_LINKS) (((ENABLED) == 1U) ? 20 + BLE_STACK_PCL_NUM_OF_LINKS(NUM_OF_LINKS) : 0U)

/**
 *
 * This macro returns the amount of memory, in bytes, needed for the storage of GATT database elements
 * and other data structures whose size depends on the number of supported connections.
 *
 * @param BLE_STACK_NUM_LINKS: Maximum number of simultaneous connections that the device will support. 
 * @param BLE_STACK_NUM_GATT_ATTRIBUTES: Maximum number of Attributes (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services) that can be stored in the GATT database. Note that certain characteristics and relative descriptors are added automatically during device initialization so this parameters should be 9 plus the number of user Attributes
 * @param BLE_STACK_NUM_GATT_CLIENT_PROCS: Maximum number of concurrent GATT Client Procedures.
 * @param BLE_STACK_MBLOCKS_COUNT: Number of memory blocks allocated for packets.
 * @param BLE_STACK_D_LEN_EXT_EN: Enable or disable the Extended Packet length feature. Valid values are 0 or 1.
 * @param BLE_STACK_PHY_UPD_EN: Enable or disable the PHY Update feature. Valid values are 0 or 1.
 * @param BLE_STACK_EXT_ADV_SCAN_EN: Enable or disable the Extended Advertising and Scan feature. Valid values are 0 or 1.
 * @param BLE_STACK_CTRL_PRIV_EN: Enable or disable the Controller privacy feature. Valid values are 0 or 1.
 * @param BLE_STACK_SEC_CONN_EN: Enable or disable the secure connection feature. Valid values are 0 or 1.
 * @param BLE_STACK_MASTER_EN: Enable or disable the Master role feature. Valid values are 0 or 1.
 * @param NUM_ADV_SET: Number of advertising set.
 * @param NUM_AUX_EVENT: Number of auxiliary events.
 * @param WHITE_LIST_SIZE_LOG2: log2 ceiling of white list size.
 * @param BLE_STACK_L2CAP_COS_EN:
 * @param NUM_L2CAP_COCS:
 * @param BLE_STACK_CTE_EN: Enable or disable the CTE feature. Valid values are 0 or 1.
 * @param NUM_CTE_ANT_IDS: Maximum antenna switching pattern length 
 * @param NUM_CTE_IQSAMPLES: Maximum number of IQ-Samples in the buffer
 * @param BLE_STACK_PCL_EN: Enable or disable the Power Control & Path Loss Monitoring feature. Valid values are 0 or 1.
 * @param ISR0_FIFO_SIZE: Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets)
 * @param ISR1_FIFO_SIZE: Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports)
 * @param USER_FIFO_SIZE: Size of the internal FIFO used for controller and host events produced outside the ISR
 */
#define BLE_STACK_TOTAL_BUFFER_SIZE_EXT(\
    BLE_STACK_NUM_LINKS,\
    BLE_STACK_NUM_GATT_ATTRIBUTES,\
    BLE_STACK_NUM_GATT_CLIENT_PROCS,\
    BLE_STACK_MBLOCKS_COUNT,\
    BLE_STACK_D_LEN_EXT_EN,\
    BLE_STACK_PHY_UPD_EN,\
    BLE_STACK_EXT_ADV_SCAN_EN,\
    BLE_STACK_CTRL_PRIV_EN,\
    BLE_STACK_SEC_CONN_EN,\
    BLE_STACK_MASTER_EN,\
    NUM_ADV_SET,\
    NUM_AUX_EVENT,\
    WHITE_LIST_SIZE_LOG2,\
    BLE_STACK_L2CAP_COS_EN,\
    NUM_L2CAP_COCS,\
    CONTROLLER_PERIODIC_ADV_ENABLED,\
    NUM_SYNC_SLOTS,\
    BLE_STACK_CTE_EN,\
    NUM_CTE_ANT_IDS,\
    NUM_CTE_IQSAMPLES,\
    BLE_STACK_PCL_EN,\
    ISR0_FIFO_SIZE,\
    ISR1_FIFO_SIZE,\
    USER_FIFO_SIZE)\
(\
  (BLE_STACK_FIXED_BUFFER_SIZE_BYTES)                                                                           + \
  ((COEFF_NUM_OF_LINKS) * (BLE_STACK_NUM_LINKS))                                                                + \
  ((BLE_STACK_GATT_ATTRIBUTE_SIZE) * (BLE_STACK_NUM_GATT_ATTRIBUTES))                                           + \
  ((COEFF_NUM_GATT_CLIENT_PROCS) * (BLE_STACK_NUM_GATT_CLIENT_PROCS))                                           + \
  ((BLE_STACK_MEM_BLOCK_SIZE + 4) * (BLE_STACK_MBLOCKS_COUNT))                                                  + \
  BLE_STACK_D_LEN_EXT_SIZE(BLE_STACK_D_LEN_EXT_EN, BLE_STACK_EXT_ADV_SCAN_EN)                                   + \
  BLE_STACK_PHY_UPD_SIZE(BLE_STACK_PHY_UPD_EN, BLE_STACK_NUM_LINKS)                                             + \
  BLE_STACK_CONTROLLER_EXT_ADV_SIZE(BLE_STACK_EXT_ADV_SCAN_EN, BLE_STACK_NUM_LINKS, NUM_ADV_SET, NUM_AUX_EVENT) + \
  BLE_STACK_CONTROLLER_PRIV(BLE_STACK_CTRL_PRIV_EN, WHITE_LIST_SIZE_LOG2)                                       + \
  (0  * (BLE_STACK_SEC_CONN_EN))                                                                                + \
  (0  * (BLE_STACK_MASTER_EN))                                                                                  + \
  (16 * (1 << (WHITE_LIST_SIZE_LOG2)))                                                                          + \
  BLE_STACK_L2C_COCS_SIZE(BLE_STACK_L2CAP_COS_EN, NUM_L2CAP_COCS)                                               + \
  BLE_STACK_CONTROLLER_PERIODIC_ADV_SIZE(CONTROLLER_PERIODIC_ADV_ENABLED, NUM_ADV_SET,                            \
                                         NUM_SYNC_SLOTS, BLE_STACK_NUM_LINKS, WHITE_LIST_SIZE_LOG2)             + \
  BLE_STACK_CTE_SIZE(BLE_STACK_CTE_EN, BLE_STACK_NUM_LINKS, NUM_CTE_ANT_IDS, NUM_CTE_IQSAMPLES)                 + \
  BLE_STACK_PCL_SIZE(BLE_STACK_PCL_EN, BLE_STACK_NUM_LINKS)                                                     + \
  ((((ISR0_FIFO_SIZE) + 3) >> 2) << 2)                                                                          + \
  ((((ISR1_FIFO_SIZE) + 3) >> 2) << 2)                                                                          + \
  ((((USER_FIFO_SIZE) + 3) >> 2) << 2)                                                                            \
)

/**
 *
 * This macro acts like the BLE_STACK_TOTAL_BUFFER_SIZE_EXT macro while makes use of the
 * modularity parameters defined in the bluenrgx_user_cfg.h file
 *
 * @param BLE_STACK_NUM_LINKS: Maximum number of simultaneous radio tasks that the device will support (Radio controller supports up to 128 simultaneous radio tasks, but actual usable max value depends 
on the available device RAM)
 * @param BLE_STACK_NUM_GATT_ATTRIBUTES: Maximum number of Attributes (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services) that can be stored in the GATT database. Note that certain characteristics and relative descriptors are added automatically during device initialization so this parameters should be 9 plus the number of user Attributes
 * @param BLE_STACK_NUM_GATT_CLIENT_PROCS: Maximum number of concurrent GATT Client Procedures.
 * @param BLE_STACK_MBLOCKS_COUNT: Number of memory blocks allocated for packets.
 * @param BLE_STACK_NUM_ADV_SET: Number of advertising set.
 * @param BLE_STACK_NUM_AUX_EVENT: Number of auxiliary scan slots.
 * @param BLE_STACK_WHITE_LIST_SIZE_LOG2: log2 ceiling of white list size.
 * @param BLE_STACK_NUM_L2CAP_COCS: number of L2CAP Connection Oriented Channels supported.
 * @param BLE_STACK_NUM_CTE_ANT_IDS: Maximum antenna switching pattern length . 
 * @param BLE_STACK_NUM_IQSAMPLES: Maximum number of IQ-Samples in the buffer.
 * @param ISR0_FIFO_SIZE: Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets).
 * @param ISR1_FIFO_SIZE: Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports).
 * @param USER_FIFO_SIZE: Size of the internal FIFO used for controller and host events produced outside the ISR.
 */
#define BLE_STACK_TOTAL_BUFFER_SIZE(\
    BLE_STACK_NUM_LINKS,\
    BLE_STACK_NUM_GATT_ATTRIBUTES,\
    BLE_STACK_NUM_GATT_CLIENT_PROCS,\
    BLE_STACK_MBLOCKS_COUNT,\
    BLE_STACK_NUM_ADV_SET,\
    BLE_STACK_NUM_AUX_EVENT,\
    BLE_STACK_WHITE_LIST_SIZE_LOG2,\
    BLE_STACK_NUM_L2CAP_COCS,\
    NUM_SYNC_SLOTS,\
    BLE_STACK_NUM_CTE_ANT_IDS,\
    BLE_STACK_NUM_IQSAMPLES,\
    ISR0_FIFO_SIZE,\
    ISR1_FIFO_SIZE,\
    USER_FIFO_SIZE)\
(\
    BLE_STACK_TOTAL_BUFFER_SIZE_EXT(\
        BLE_STACK_NUM_LINKS,\
        BLE_STACK_NUM_GATT_ATTRIBUTES,\
        BLE_STACK_NUM_GATT_CLIENT_PROCS,\
        BLE_STACK_MBLOCKS_COUNT,\
        CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED,\
        CONTROLLER_2M_CODED_PHY_ENABLED,\
        CONTROLLER_EXT_ADV_SCAN_ENABLED,\
        CONTROLLER_PRIVACY_ENABLED,\
        SECURE_CONNECTIONS_ENABLED,\
        CONTROLLER_MASTER_ENABLED,\
        BLE_STACK_NUM_ADV_SET,\
        BLE_STACK_NUM_AUX_EVENT,\
        BLE_STACK_WHITE_LIST_SIZE_LOG2,\
        L2CAP_COS_ENABLED,\
        BLE_STACK_NUM_L2CAP_COCS,\
        CONTROLLER_PERIODIC_ADV_ENABLED,\
        NUM_SYNC_SLOTS,\
        CONTROLLER_CTE_ENABLED,\
        BLE_STACK_NUM_CTE_ANT_IDS,\
        BLE_STACK_NUM_IQSAMPLES,\
        CONTROLLER_POWER_CONTROL_ENABLED,\
        ISR0_FIFO_SIZE,\
        ISR1_FIFO_SIZE,\
        USER_FIFO_SIZE\
))

/**
*
* This structure contains memory and low level hardware configuration data for the device
*/
typedef struct {
  uint8_t* BLEStartRamAddress;  /**< Start address of the RAM buffer for GATT database allocated according to BLE_STACK_TOTAL_BUFFER_SIZE (32bit aligned RAM area) */
  uint32_t TotalBufferSize;     /**< BLE_STACK_TOTAL_BUFFER_SIZE return value, used to check the MACRO correctness*/
  uint16_t NumAttrRecords;      /**< Maximum number of Attributes that can be stored in the GATT database. */
  uint8_t MaxNumOfClientProcs;  /**< Maximum number of concurrent Client's Procedures. This value shall be less or equal to NumOfLinks. */
  uint8_t NumOfLinks;           /**< Maximum number of simultaneous radio tasks. Radio controller supports up to 128 simultaneous radio tasks, but actual usable max value depends on the available device RAM (NUM_LINKS used in the calculation of BLE_STACK_TOTAL_BUFFER_SIZE). */
  uint16_t NumBlockCount;       /**< Number of allocated memory blocks */
  uint16_t ATT_MTU;             /**< Maximum supported ATT_MTU size [23-1020]*/
  uint32_t MaxConnEventLength;  /**< Maximum duration of the connection event when the device is in Slave mode in units of 625/256 us (~2.44 us) */
  uint16_t SleepClockAccuracy;  /**< Sleep clock accuracy (ppm value)*/
  uint8_t NumOfAdvDataSet;      /**< Maximum number of Advertising Data Set, valid only when Advertising Extension Feature is enabled  */
  uint8_t NumOfAuxScanSlots;    /**< Maximum number of slots for scanning on the secondary advertising channel, valid only when Advertising Extension Feature is enabled  */
  uint8_t NumOfSyncSlots;       /**< Maximum number of slots for synchronizing, valid only when Periodic Advertising and Synchronizing Feature is enabled  */
  uint8_t WhiteListSizeLog2;    /**< Two's logarithm of white, resolving and advertiser list size. */
  uint16_t L2CAP_MPS;           /**< The maximum size of payload data in octets that the L2CAP layer entity is capable of accepting [0-1024].*/
  uint8_t L2CAP_NumChannels;    /**< Maximum number of channels in LE Credit Based Flow Control mode [0-255].*/
  uint8_t CTE_MaxNumAntennaIDs; /**< Maximum number of Antenna IDs in the antenna pattern used in CTE connection oriented mode. */
  uint8_t CTE_MaxNumIQSamples;  /**< Maximum number of IQ samples in the buffer used in CTE connection oriented mode. */
  uint16_t isr0_fifo_size;      /**< Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets)*/
  uint16_t isr1_fifo_size;      /**< Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports)*/
  uint16_t user_fifo_size;      /**< Size of the internal FIFO used for controller and host events produced outside the ISR */
} BLE_STACK_InitTypeDef;


/**
 * @brief This function executes the processing of all Host Stack layers.
 *
 * The BLE Stack Tick function has to be executed regularly to process incoming Link Layer packets and to process Host Layers procedures. All
 * stack callbacks are called by this function.
 *
 * If Low Speed Ring Oscillator is used instead of the LS Crystal oscillator this function performs also the LS RO calibration and hence must
 * be called at least once at every system wake-up in order to keep the 500 ppm accuracy (at least 500 ppm accuracy is mandatory if acting as a master).
 *
 * No BLE stack function must be called while the BLE_STACK_Tick is running. For example, if a BLE stack function may be called inside an
 * interrupt routine, that interrupt must be disabled during the execution of BLE_STACK_Tick(). Example (if a stack function may be called inside
 * UART ISR):
 * @code
 * NVIC_DisableIRQ(UART_IRQn);
 * BLE_STACK_Tick();
 * NVIC_EnableIRQ(UART_IRQn);
 * @endcode

 * @note The API name and parameters are subject to change in future releases.
 * @return None
 */
void BLE_STACK_Tick(void);

/**
 * @brief The BLE Stack initialization routine
 *
 * @note The API name and parameters are subject to change in future releases.
 *
 * @param[in]  BLE_STACK_InitStruct      pointer to the const structure containing memory and low level
 *                                              hardware configuration data for the device
 *
 * @return Value indicating success or error code.
 *
 */
tBleStatus BLE_STACK_Init(const BLE_STACK_InitTypeDef *BLE_STACK_InitStruct);


/**
 * @brief Returns the BLE Stack matching sleep mode
 *
 * @note The API name and parameters are subject to change in future releases.
 *
 * @return
 *  SLEEPMODE_RUNNING       = 0,
 *  SLEEPMODE_NOTIMER       = 3,
 */
uint8_t BLE_STACK_SleepCheck(void);

/**
 *
 * @brief Radio ISR routine.
 *
 * This is the base function called for any radio ISR.
 *
 * @param[in]  BlueInterrupt    value of the radio interrupt register
 *
 * @return None
 */
void BLE_STACK_RadioHandler(uint32_t BlueInterrupt);

/**
  * @brief 'This function provide information when a new radio activity will be performed.
Information provided includes type of radio activity and absolute time in system ticks when a new radio activity is schedule, if any.
  * @param NextStateSysTime 32bit absolute current time expressed in internal time units.
  * @retval Value indicating the next state:
  - 0x00: Idle
  - 0x01: Advertising
  - 0x02: Connection event slave
  - 0x03: Scanning
  - 0x04: Connection request
  - 0x05: Connection event master
  - 0x06: TX test mode
  - 0x07: RX test mode
  */
uint8_t BLE_STACK_ReadNextRadioActivity(uint32_t *NextStateSysTime);

/*
** [PA:] req_swe1 #522259: the following prototypes/defines shall be moved
** to bluenrg_lp_api_h (please see #followup_2319645 for more details)
*/

/* Statistic per link */
typedef struct LLC_per_count_s {

    uint16_t num_pkts;
    uint16_t num_crc_err;
    uint16_t num_evts;
    uint16_t num_miss_evts;

} LLC_per_statistic_st;

/**
 * @brief     LLC function to collect statistics per link:
 *             - statistics are stored in a buffer allocated by the application
 *             - counters are reset every time the function is called
 *             - counters are stopped when the function is called with a pointer to NULL
 *
 * @param[in] Connection_Handle - connection handle that identifies the connection
 * @param[in] ptr - pointer to the buffer
 * @return    BLE_ERROR_UNKNOWN_CONNECTION_ID in case of invalid Connection_Handle
 *            BLE_STATUS_SUCCESS otherwise
 */
tBleStatus LLC_per_statistic(uint16_t Connection_Handle,
                             LLC_per_statistic_st *ptr);


/* Statistic per link and per channel */
#define LLC_MAX_NUM_DATA_CHAN 37U

typedef struct LLC_per_statistic_by_channel_s {

    uint16_t num_pkts[LLC_MAX_NUM_DATA_CHAN];
    uint16_t num_crc_err[LLC_MAX_NUM_DATA_CHAN];
    uint16_t num_miss_evts[LLC_MAX_NUM_DATA_CHAN];
    
} LLC_per_statistic_by_channel_st;

/**
 * @brief     LLC function to collect statistics per link and per channel:
 *             - statistics are stored in a buffer allocated by the application
 *             - counters are reset every time the function is called
 *             - counters are stopped when the function is called with a pointer to NULL
 *
 * @param[in] Connection_Handle - connection handle that identifies the connection
 * @param[in] ptr - pointer to the buffer
 * @return    BLE_ERROR_UNKNOWN_CONNECTION_ID in case of invalid Connection_Handle
 *            BLE_STATUS_SUCCESS otherwise
 */
tBleStatus LLC_per_statistic_by_channel(uint16_t Connection_Handle,
                                        LLC_per_statistic_by_channel_st *ptr);


#endif /* BLUENRGLP_STACK_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

