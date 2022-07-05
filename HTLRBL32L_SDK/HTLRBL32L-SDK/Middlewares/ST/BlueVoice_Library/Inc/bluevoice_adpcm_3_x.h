/**
  **************************************************************************************
  * File Name          : bluevoice_adpcm_3_x
  * Author             : CLAB  & AMS RF Application teams
  * Version            : V1.0.0
  * Date               : 22-September-2020
  * Description        : This file contains definitions for BlueVoice profile: 
  *                      Bluetooth LE stack v3.x (BlueNRG-LP device).
  *
  **************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
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
  **************************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLUEVOICE_3_X_H
#define __BLUEVOICE_3_X_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "ble_const.h" 
#include "bluenrg_lp_api.h"
#include <string.h>

/** @addtogroup MIDDLEWARES
  * @{
  */

/** @defgroup BV_ADPCM_3_x BV_ADPCM_3_x
  * @{
  */

/** @defgroup BV_ADPCM_3_x_Exported_Enums BV_ADPCM_3_x_Exported_Enums
  * @{
  */

/** 
  * @brief Accepted audio in sampling frequencies.
  */
typedef enum
{
  FR_8000 = 8000,                               /*!< Sampling frequency 8000 kHz.*/
  FR_16000 = 16000                              /*!< Sampling frequency 16000 kHz.*/
} Sampling_fr_t;

/** 
* @brief Return states values.
*/
typedef enum 
{
  BV_SUCCESS = 0x00,                        /*!< Success.*/
  BV_ERROR = 0x01,                          /*!< Error.*/
  BV_DISCONNETED = 0x10,                    /*!< BLE Disconnected Error.*/
  BV_NOT_CONFIG = 0x20,                     /*!< BV_ADPCM_3_x library not configured.*/
  BV_RECEIVER_DISABLE = 0x30,               /*!< Receiver mode disabled.*/
  BV_TRANSMITTER_DISABLE = 0x31,            /*!< Transmitter mode disabled.*/
  BV_RX_HANDLE_NOT_AVAILABLE = 0x32,        /*!< The handle isn't recognized.*/
  BV_OUT_BUF_READY = 0x40,                  /*!< The audio out buffer is ready to be sent.*/
  BV_OUT_BUF_NOT_READY = 0x41,              /*!< The audio out buffer is not ready to be sent.*/
  BV_PCM_SAMPLES_ERR = 0x50,                /*!< The number of PCM samples given as audio input is not correct.*/
  BV_NOTIF_DISABLE = 0x60,                  /*!< The notifications are disabled.*/
  BV_TIMEOUT = 0x70,                        /*!< A BLE timeout occurred.*/
  BV_INSUFFICIENT_RESOURCES = 0x80          /*!< GATT TX Buffer full.*/
} BV_3_x_Status;

/** 
* @brief BlueVoice working modalities.
*/
typedef enum
{
  NOT_READY = 0x00,                         /*!< Device not ready.*/
  TRANSMITTER = 0x01,                       /*!< Device in Transmitter mode.*/
  RECEIVER = 0x02,                          /*!< Device in Receiver mode.*/
  HALF_DUPLEX = 0x03                        /*!< Device in HalfDuplex mode.*/
} BV_Mode;

/** 
* @brief BlueVoice profile status.
*/
typedef enum
{
  BLUEVOICE_STATUS_UNITIALIZED = 0x00,      /*!< BlueVoice Profile is not initialized.*/
  BLUEVOICE_STATUS_INITIALIZED = 0x10,      /*!< BlueVoice Profile is initialized.*/
  BLUEVOICE_STATUS_READY = 0x20,            /*!< BlueVoice channel is ready and idle.*/
  BLUEVOICE_STATUS_STREAMING = 0x30,        /*!< BlueVoice device is streaming data.*/
  BLUEVOICE_STATUS_RECEIVING = 0x40         /*!< BlueVoice device is receiving data.*/
} BV_Profile_Status;

/**
  * @}
  */ 

/** @defgroup BV_ADPCM_3_x_Exported_Types BV_ADPCM_3_x_Exported_Types
  * @{
 */

/** 
* @brief BlueVoice profile configuration parameters.
*/
typedef struct
{   
  Sampling_fr_t sampling_frequency;     /*!< Specifies the sampling frequency in kHz - can be 16 kHz or 8 kHz.*/
  
  uint8_t channel_tot;                  /*!< Number of channels contained in the buffer given as Audio Input.*/
  
  uint8_t channel_in;                   /*!< The chosen channel among the available in the input buffer.*/

} BV_ADPCM_3_x_Config_t;

/** 
* @brief BlueVoice profile handle deinition.
*/
typedef struct
{
  uint16_t ServiceHandle;               /*!< Service handle.*/
 
  uint16_t CharAudioHandle;             /*!< Audio characteristic handle.*/
  
  uint16_t CharAudioSyncHandle;         /*!< Audio Sync characteristic handle.*/

} BV_ADPCM_3_x_ProfileHandle_t;

/**
 * @}
 */ 

/** @defgroup BV_ADPCM_3_x_Exported_Constants BV_ADPCM_3_x_Exported_Constants
 * @{
 */ 

#define BV_ADPCM_3_x_TIMEOUT_STATUS                 ((uint16_t)500)           /*!< status timeout (in ms), the function "BlueVoice_IncTick" must be 
                                                                                called every 1 ms. If timeout expires, the device goes from receiving/streaming 
                                                                                to ready mode.*/
                                                                            
/**
  * @}
  */

/** @defgroup BV_ADPCM_3_x_Exported_Functions BV_ADPCM_3_x_Exported_Functions
  * @{
  */

/**
  * @brief  This function is called to initialize the bluevoice library.
  * @param  None.
  * @retval None.
  */
void BluevoiceADPCM_3_x_Initialize(void);
    
/**
  * @brief  This function is called to set the configuration parameters 
  * @param  BV_ADPCM_3_x_Config: It contains the configuration parameters.
  * @retval BV_3_x_Status: BV_SUCCESS if the configuration is ok, BV_ERROR otherwise.
  */
BV_3_x_Status BluevoiceADPCM_3_x_SetConfig(BV_ADPCM_3_x_Config_t *BV_ADPCM_3_x_Config);

/**
  * @brief  This function returns if the BlueVoice Profile is configured.
  * @param  None.
  * @retval uint8_t: 1 if the profile is configured 0 otherwise.
  */
uint8_t BluevoiceADPCM_3_x_IsProfileConfigured(void);
  
/**
  * @brief  This function is called to add BlueVoice Service.
  * @param  service_handle: Pointer to a variable in which the service handle will be saved.
  * @retval BV_3_x_Status: Value indicating success or error code.
  */
BV_3_x_Status BluevoiceADPCM_3_x_AddService(uint16_t *service_handle);

/**
  * @brief  This function is called to add BlueVoice characteristics.
  * @param  uuid: It contains the uuid values of the Audio and audioSync characteristics.
  * @param  service_handle: Handle of the service to which the characteristic must be added.
  * @param  handle: Pointer to a BV_ADPCM_3_x_ProfileHandle_t struct in which the handles will be saved.
  * @retval BV_3_x_Status: BV_SUCCESS in case of success, BV_ERROR otherwise.
  */
BV_3_x_Status BluevoiceADPCM_3_x_AddChar(uint16_t service_handle, BV_ADPCM_3_x_ProfileHandle_t *handle);

/**
  * @brief  This function is called to set the handles if the BlueVoice characteristics are added out of the library.
  * @param  tx_handle: Pointer to a BV_ADPCM_3_x_ProfileHandle_t struct in which the handles are stored.
  * @retval None.
  */
void BluevoiceADPCM_3_x_SetTxHandle(BV_ADPCM_3_x_ProfileHandle_t *tx_handle);  
  
/**
  * @brief  This function is called to set the handles discovered, if an other BlueVoice module is available.
  * @param  rx_handle: Pointer to a BV_ADPCM_3_x_ProfileHandle_t struct in which the handles are stored.
  * @retval None.
  */
void BluevoiceADPCM_3_x_SetRxHandle(BV_ADPCM_3_x_ProfileHandle_t *rx_handle);

/**
  * @brief  This function returns the BlueVoice Profile State Machine status.
  * @param  None.
  * @retval BV_Profile_Status: BlueVoice Profile Status.
  */
BV_Profile_Status BluevoiceADPCM_3_x_GetStatus(void);

/**
  * @brief  This function returns the current modality.
  * @param  None.
  * @retval BV_Mode: Current working modality: NOT_READY, RECEIVER, TRANSMITTER or HALF_DUPLEX.
  */
BV_Mode BluevoiceADPCM_3_x_GetMode(void);
   
/**
  * @brief  This function increases the the internal counter, used to switch from Receiving/Streaming to Ready status.
  * @param  None.
  * @retval BV_3_x_Status: Value indicating success or error code.
  */
BV_3_x_Status BluevoiceADPCM_3_x_IncTick(void);
  
/**
  * @brief  This function is called to enable Audio notification.
  * @param  None.
  * @retval BV_3_x_Status: Value indicating success or error code.
  */
BV_3_x_Status BluevoiceADPCM_3_x_EnableAudioNotification(void);
  
/**
  * @brief  This function is called to enable Sync notifications.
  * @param  None.
  * @retval BV_3_x_Status: Value indicating success or error code.
  */
BV_3_x_Status BluevoiceADPCM_3_x_EnableSyncNotification(void);

/**
  * @brief  This function is called to fill audio buffer.
  * @param  buffer: Audio in PCM buffer.
  * @param  Nsamples: Number of PCM 16 bit audio samples.
  * @retval BV_3_x_Status: Value indicating success or error code.
  */
BV_3_x_Status BluevoiceADPCM_3_x_AudioIn(uint16_t* buffer, uint8_t Nsamples);
  
/**
 * @brief  This function is called to send data.
 * @param  None
 * @retval BV_3_x_Status: Value indicating success or error code.
 */
BV_3_x_Status BluevoiceADPCM_3_x_SendData(void);
   
/**
  * @brief  This function is called to parse received data.
  * @param  buffer_in: 8-bit packed ADPCM samples source buffer.
  * @param  Len: Dimension in Bytes.
  * @param  attr_handle: Handle of the updated characteristic.
  * @param  buffer_out: 16-bit PCM samples destination buffer.
  * @param  samples: Number of 16-bit PCM samples in the destination buffer.
  * @retval BV_3_x_Status: Value indicating success or error code.
  */
BV_3_x_Status BluevoiceADPCM_3_x_ParseData(uint8_t* buffer_in, uint32_t Len, uint16_t attr_handle, uint8_t* buffer_out, uint8_t *samples);

/**
  * @}
  */ 
  
/** @defgroup BV_ADPCM_3_x_Exported_Callbacks BV_ADPCM_3_x_Exported_Callbacks
* @{
*/
  
/**
  * @brief  This function must be called when there is a LE Connection Complete event.
  * @param  handle: Connection handle.
  * @retval None.
  */
void BluevoiceADPCM_3_x_ConnectionComplete_CB(uint16_t handle);

/**
  * @brief  This function must be called when there is a LE disconnection Complete event. 
  * @param  None.
  * @retval None.
  */
void BluevoiceADPCM_3_x_DisconnectionComplete_CB(void);

/**
  * @brief  This function must be called when there is a LE attribut modified event. 
  * @param  attr_handle: Attribute handle.
  * @param  attr_len: Attribute length.
  * @param  attr_value: Attribute value.
  * @retval None.
  */
void BluevoiceADPCM_3_x_AttributeModified_CB(uint16_t attr_handle, uint8_t attr_len, uint8_t *attr_value);

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

#endif /* __BLUEVOICE_3_X_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
