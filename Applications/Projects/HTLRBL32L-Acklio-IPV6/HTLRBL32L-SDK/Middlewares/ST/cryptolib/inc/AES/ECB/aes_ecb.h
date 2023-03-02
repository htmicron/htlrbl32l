/**
  ******************************************************************************
  * @file    aes_ecb.h
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    05-June-2015
  * @brief   AES in ECB Mode
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Image SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRL_AES_ECB_H__
#define __CRL_AES_ECB_H__

#ifdef __cplusplus
extern "C"
{
#endif

  /** @ingroup AESECB
    * @{
    */

  /* Exported types ------------------------------------------------------------*/
  /** ECB context = CBC context. AESECBctx_stt is equal to AESCBCctx_stt */
  typedef AESCBCctx_stt AESECBctx_stt;

  /* Exported functions --------------------------------------------------------*/
#ifdef INCLUDE_ENCRYPTION
/**
  * @brief Initialization for AES Encryption in ECB Mode
  * @param[in,out]    *P_pAESECBctx  AES ECB context
  * @param[in]        *P_pKey        Buffer with the Key
  * @param[in]        *P_pIv         Buffer with the IV (Can be NULL since no IV is required in ECB)
  * @retval    AES_SUCCESS Operation Successfull
  * @retval    AES_ERR_BAD_PARAMETER At least one of the parameters is a NULL pointer
  * @retval    AES_ERR_BAD_CONTEXT   Context was not initialized with valid values, see the note below.
  * @note \c P_pAESECBctx.mKeySize (see \ref AESECBctx_stt) must be set with the size of the key prior to calling this function.
  *           Instead of the size of the key, you can also use the following predefined values:
  *         - \ref CRL_AES128_KEY
  *         - \ref CRL_AES192_KEY
  *         - \ref CRL_AES256_KEY
  * @note \c P_pAESECBctx.mFlags must be set prior to calling this function. Default value is E_SK_DEFAULT.
  *          See \ref SKflags_et for details.
  * @remark In ECB the IV is not used, so the value of \c P_pIv is not checked or used
  */
  int32_t AES_ECB_Encrypt_Init   (AESECBctx_stt *P_pAESECBctx, \
                                  const uint8_t *P_pKey,      \
                                  const uint8_t *P_pIv);

/**
  * @brief AES Encryption in ECB Mode
  * @param[in]    *P_pAESECBctx     AES ECB, already initialized, context
  * @param[in]    *P_pInputBuffer   Input buffer
  * @param[in]     P_inputSize      Size of input data, expressed in bytes
  * @param[out]   *P_pOutputBuffer  Output buffer
  * @param[out]   *P_pOutputSize    Pointer to integer that will contain the size of written output data, expressed in bytes
  * @retval    AES_SUCCESS Operation Successfull
  * @retval    AES_ERR_BAD_PARAMETER   At least one of the parameters is a NULL pointer
  * @retval    AES_ERR_BAD_INPUT_SIZE  The size of the input is not a multiple of CRL_AES_BLOCK
  * @retval    AES_ERR_BAD_OPERATION   Append not allowed
  * @remark This function can be called multiple times, provided that \c P_inputSize is a multiple of 16
  */
  int32_t AES_ECB_Encrypt_Append (AESECBctx_stt *P_pAESECBctx,   \
                                  const uint8_t *P_pInputBuffer, \
                                  int32_t        P_inputSize,    \
                                  uint8_t       *P_pOutputBuffer, \
                                  int32_t       *P_pOutputSize);

/**
  * @brief AES Encryption Finalization of ECB Mode
  * @param[in,out]    *P_pAESECBctx     AES ECB, already initialized, context
  * @param[out]   *P_pOutputBuffer  Output buffer
  * @param[out]   *P_pOutputSize    Pointer to integer that will contain the size of written output data, expressed in bytes
  * @retval    AES_SUCCESS Operation Successfull
  * @retval    AES_ERR_BAD_PARAMETER At least one of the parameters is a NULL pointer
  * @remark    This function won't write output data, thus it can be skipped. \n It is kept for API compatibility.
  */
  int32_t AES_ECB_Encrypt_Finish (AESECBctx_stt *P_pAESECBctx,   \
                                  uint8_t       *P_pOutputBuffer, \
                                  int32_t       *P_pOutputSize);
#endif /* ECB Encryption */

#ifdef INCLUDE_DECRYPTION
/**
  * @brief Initialization for AES Decryption in ECB Mode
  * @param[in,out]    *P_pAESECBctx  AES ECB context
  * @param[in]        *P_pKey        Buffer with the Key
  * @param[in]        *P_pIv         Buffer with the IV
  * @retval    AES_SUCCESS Operation Successfull
  * @retval    AES_ERR_BAD_PARAMETER At least one of the parameters is a NULL pointer
  * @retval    AES_ERR_BAD_CONTEXT   Context was not initialized with valid values, see the note below.
  * @note \c P_pAESECBctx.mKeySize (see \ref AESECBctx_stt) must be set with the size of the key prior to calling this function.
  *           Instead of the size of the key, you can also use the following predefined values:
  *         - \ref CRL_AES128_KEY
  *         - \ref CRL_AES192_KEY
  *         - \ref CRL_AES256_KEY
  * @note \c P_pAESECBctx.mFlags must be set prior to calling this function. Default value is E_SK_DEFAULT.
  *          See \ref SKflags_et for details.
  * @remark In ECB the IV is not used, so the value of \c P_pIv is not checked or used
  */
  int32_t AES_ECB_Decrypt_Init   (AESECBctx_stt *P_pAESECBctx, \
                                  const uint8_t *P_pKey,      \
                                  const uint8_t *P_pIv);

/**
  * @brief AES Decryption in ECB Mode
  * @param[in]    *P_pAESECBctx     AES ECB, already initialized, context
  * @param[in]    *P_pInputBuffer   Input buffer
  * @param[in]     P_inputSize      Size of input data, expressed in bytes
  * @param[out]   *P_pOutputBuffer  Output buffer
  * @param[out]   *P_pOutputSize    Pointer to integer that will contain the size of written output data, expressed in bytes
  * @retval    AES_SUCCESS Operation Successfull
  * @retval    AES_ERR_BAD_PARAMETER At least one of the parameters is a NULL pointer
  * @retval    AES_ERR_BAD_INPUT_SIZE  The size of the input is not a multiple of CRL_AES_BLOCK
  * @retval    AES_ERR_BAD_OPERATION   Append not allowed
  * @remark This function can be called multiple times, provided that \c P_inputSize is a multiple of 16
  */
  int32_t AES_ECB_Decrypt_Append (AESECBctx_stt *P_pAESECBctx,   \
                                  const uint8_t *P_pInputBuffer, \
                                  int32_t        P_inputSize,    \
                                  uint8_t       *P_pOutputBuffer, \
                                  int32_t       *P_pOutputSize);

/**
  * @brief AES Decryption Finalization of ECB Mode
  * @param[in,out]    *P_pAESECBctx     AES ECB, already initialized, context
  * @param[out]   *P_pOutputBuffer  Output buffer
  * @param[out]   *P_pOutputSize    Pointer to integer that will contain the size of written output data, expressed in bytes
  * @retval    AES_SUCCESS Operation Successfull
  * @retval    AES_ERR_BAD_PARAMETER At least one of the parameters is a NULL pointer
  * @remark    This function won't write output data, thus it can be skipped. \n It is kept for API compatibility.
  */
  int32_t AES_ECB_Decrypt_Finish (AESECBctx_stt *P_pAESECBctx,   \
                                  uint8_t       *P_pOutputBuffer, \
                                  int32_t       *P_pOutputSize);
#endif /* ECB Decryption */

  /** @} */

#ifdef __cplusplus
}
#endif

#endif  /*__CRL_AES_ECB_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
