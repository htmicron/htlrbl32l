/*****************************************************************************
 * @file    bleplat.h
 * @author  MCD Application Team
 * @brief   This file contains the interface of the BLE platform layer
 *          (lower interface of the BLE stack library).
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 *****************************************************************************
 */

#ifndef BLEPLAT_H__
#define BLEPLAT_H__

#include <stdint.h>

#define RSSI_INVALID (127)

/* Enumerated values used for the return of the functions: */

typedef enum
{
  BLEPLAT_OK    =  0,
  BLEPLAT_FULL  = -1,
  BLEPLAT_BUSY  = -2,
  BLEPLAT_EOF   = -3
} bleplat_nvm_status;


/* Enumerated values used for the 'type' of NVM functions: */

typedef enum
{
  BLEPLAT_NVM_TYPE_SEC        =  0,
  BLEPLAT_NVM_TYPE_GATT       =  1,
  BLEPLAT_NVM_TYPE_DEVICE_ID  =  2,
} bleplat_nvm_record_type;


/* Enumerated values used for the 'mode' of NVM functions: */

typedef enum
{
  BLEPLAT_NVM_FIRST    =  0,
  BLEPLAT_NVM_NEXT     =  1,
  BLEPLAT_NVM_CURRENT  =  2,
  BLEPLAT_NVM_ALL      =  3
} bleplat_nvm_record_mode;


/* General functions: */

extern void BLEPLAT_Init( void );


/* Non Volatile Memory (NVM) interface:
 *
 * This interface is only called from BLE stack Tick/Commands context
 */

extern bleplat_nvm_status BLEPLAT_NvmAdd( bleplat_nvm_record_type type,
                           const uint8_t* data,
                           uint16_t size,
                           const uint8_t* extra_data,
                           uint16_t extra_size );

extern bleplat_nvm_status BLEPLAT_NvmGet( bleplat_nvm_record_mode mode,
                           bleplat_nvm_record_type type,
                           uint16_t offset,
                           uint8_t* data,
                           uint16_t size );

extern int BLEPLAT_NvmCompare( uint16_t offset,
                               const uint8_t* data,
                               uint16_t size );

extern void BLEPLAT_NvmDiscard( bleplat_nvm_record_mode mode );


/* Public Key Algorithms (PKA) interface:
 *
 * This interface is only called from BLE stack Tick/Commands context
 */

extern int BLEPLAT_PkaStatus( void );

extern int BLEPLAT_PkaStartP256Key( const uint32_t* local_private_key );

extern void BLEPLAT_PkaReadP256Key( uint32_t* local_public_key );

extern int BLEPLAT_PkaStartDhKey( const uint32_t* local_private_key,
                                  const uint32_t* remote_public_key );

extern int BLEPLAT_PkaReadDhKey( uint32_t* dh_key );


/* Advanced Encryption Standard (AES) interface:
 *
 * This interface is only called from BLE stack Tick/Commands context
 */

extern void BLEPLAT_AesEcbEncrypt( const uint8_t* key,
                                   const uint8_t* input,
                                   uint8_t* output );

extern void BLEPLAT_AesCmacCompute( const uint8_t* key,
                                    const uint8_t* input,
                                    uint32_t input_length,
                                    uint8_t* output_tag );


/* Random Number Generation (RNG) interface:
 *
 * This interface is called from both BLE stack contexts: ISR and Tick/Commands
 */

extern uint16_t BLEPLAT_RngGetVal( void );

/**
  * @brief  Convert TX output power in dBm to the related Power Amplifier level
  * @param  TX_dBm Desired TX output power.  
  * @param  high_power Set to 0 if normal TX power mode is used at this moment.
  *                    Set to 1 if TX power mode has been switched to high (to
  *                    reach maximum power). If this parameter does not reflect
  *                    current power mode, the function does not return the
  *                    correct PA level to give the desired output power.
  *
  * @retval PA level that has to be set in the radio register to have a TX
  *         output power lower than or equal to the desired output power
  */
uint8_t BLEPLAT_DBmToPALevel(int8_t TX_dBm, uint8_t high_power);

/**
  * @brief  Convert TX output power in dBm to the related Power Amplifier level
  * @param  TX_dBm Desired TX output power.  
  * @param  high_power Set to 0 if normal TX power mode is used at this moment.
  *                    Set to 1 if TX power mode has been switched to high (to
  *                    reach maximum power). If this parameter does not reflect
  *                    current power mode, the function does not return the
  *                    correct PA level to give the desired output power.
  *
  * @retval PA level that has to be set in the radio register to have a TX
  *         output power greater than or equal to the desired output power
  */
uint8_t BLEPLAT_DBmToPALevelGe(int8_t TX_dBm, uint8_t high_power);

/**
  * @brief  Convert Power Amplifier level to TX output power in dBm
  * @param  PA_Level Level setting for the Power Amplifier
  * @param  high_power Set to 0 if normal TX power mode is used at this moment.
  *                    Set to 1 if TX power mode has been switched to high (to
  *                    reach maximum power). If this parameter does not reflect
  *                    current power mode, the function does not return the
  *                    correct output power at the given PA level.
  *
  * @retval Output power in dBm, corresponding to the given PA level. If PA
  *         level is invalid, returned value is 127.
  */
int8_t BLEPLAT_PALevelToDBm(uint8_t PA_Level, uint8_t high_power);

/**
  * @brief  Return minimum and maximum supported TX power.
  * @param[in]   high_power Set to 0 if normal TX power mode is used at this moment.
  *                         Set to 1 if TX power mode has been switched to high (to
  *                         reach maximum power). If this parameter does not reflect
  *                         current power mode, the function does not return the
  *                         correct maximum output power.
  * @param[out]  Min_Tx_Power Minimum supported TX power in dBm.
  * @param[out]  Max_Tx_Power Maximum supported TX power in dBm.
  *
  * @retval None
  */
void BLEPLAT_ReadTransmitPower(uint8_t high_power, int8_t *Min_Tx_Power, int8_t *Max_Tx_Power);

/**
  * @brief  Configure the radio in order to increase output power level.
  * @note   This function should be called only by the BLE stack.
  * @param  enable Enable or disable the ability to reach maximum TX power.
  *                Set to 1 to enable high power mode. Set ot 0 to disable.
  * @retval None
  */
void BLEPLAT_SetHighPower(uint8_t enable);

/**
  * @brief      Read the RSSI and AGC HW registers.
  * @param[out] value of the RSSI registers packed on 16 bits.
  * @param[out] value of the AGC register.
  * @retval     None
  */
void BLEPLAT_GetRawRSSIRegs(uint32_t *rssi_reg, uint32_t *agc_reg);

/**
  * @brief  Return the current RSSI measured for the last received packet
            as a signed value in dBm.
  * @retval Current RSSI value
  */
int8_t BLEPLAT_CalculateRSSI(void);

/**
  * @brief  Return the next value of the average of RSSI values
  *         given the current RSSI average value and the next RSSI value.
  *         All values are signed and expressed in dBm.
  *         An Exponential Moving Average algorithm is applied.
  * @param  avg_rssi          Current RSSI average value.
  *                           Set to 127 to return the 'rssi' value.
  * @param  rssi              Next RSSI value
  * @param  rssi_filter_coeff Coefficient used for the filtering of
  *                           the RSSI samples and the calculation of
  *                           the average RSSI.
  * @retval Next RSSI average value
  */
int8_t BLEPLAT_UpdateAvgRSSI(int8_t avg_rssi, int8_t rssi, uint8_t rssi_filter_coeff);

#endif /* ! BLEPLAT_H__ */
