/**
  ******************************************************************************
  * @file    miscutil.h
  * @author  AMS - RF Application team
  * @version V1.0.0
  * @date    3-April-2019
  * @brief   Header file for radio HW miscellaneous utilities.
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
  * <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#ifndef __MISCUTIL_H__
#define __MISCUTIL_H__

#include <stdint.h>


/**
 * @brief Get Device ID, Version and Revision numbers
 * 
 * This function returns the device ID, version and revision numbers.
 * To be called by the BLE Stack for ensuring platform independence.
 * 
 * @param[out] device_id Device ID (3 = BlueNRG-LP)
 * @param[out] major_cut Device cut version/major number
 * @param[out] minor_cut Device cut revision/minor number
 *
 * @retval None
 */
void BLEPLAT_get_part_info(uint8_t *device_id, uint8_t *major_cut, uint8_t *minor_cut);

/**
 * @brief Set the vector table offset address. 
 *        On reset, the Cortex-M0+ vector table is fixed at address 0x00000000. 
 *        The software may relocate the vector table address to a different 
 *        memory location, in a range 0x00000000 to 0xFFFFFF80 in multiples 
 *        of 256 bytes through the Vector Table Offset Register (VTOR)
 *        located in the Cortex-M0+ registers area
 * @param offset Table offset address
 * @Note Remember to modify the linker file according the new offset.
 *       i.e. if the offset is 0x600, place the vector table in the linker file
 *       at address 0x10040600
 */
void NVIC_SetVectorTableOffset(uint32_t offset);

#endif /* __MISCUTIL_H__ */
