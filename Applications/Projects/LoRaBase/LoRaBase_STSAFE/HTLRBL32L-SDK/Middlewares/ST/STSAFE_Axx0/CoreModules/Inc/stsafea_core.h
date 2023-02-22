/**
  ******************************************************************************
  * @file    stsafea_core.h
  * @author  SMD/AME application teams
  * @version V3.3.2
  * @brief   Header file of STSAFE-A Middleware Core module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * STSAFE DRIVER SOFTWARE LICENSE AGREEMENT (SLA0088)
  *
  * BY INSTALLING, COPYING, DOWNLOADING, ACCESSING OR OTHERWISE USING THIS SOFTWARE
  * OR ANY PART THEREOF (AND THE RELATED DOCUMENTATION) FROM STMICROELECTRONICS
  * INTERNATIONAL N.V, SWISS BRANCH AND/OR ITS AFFILIATED COMPANIES (STMICROELECTRONICS),
  * THE RECIPIENT, ON BEHALF OF HIMSELF OR HERSELF, OR ON BEHALF OF ANY ENTITY BY WHICH
  * SUCH RECIPIENT IS EMPLOYED AND/OR ENGAGED AGREES TO BE BOUND BY THIS SOFTWARE LICENSE
  * AGREEMENT.
  *
  * Under STMicroelectronicsâ€™ intellectual property rights, the redistribution,
  * reproduction and use in source and binary forms of the software or any part thereof,
  * with or without modification, are permitted provided that the following conditions
  * are met:
  * 1.  Redistribution of source code (modified or not) must retain any copyright notice,
  *     this list of conditions and the disclaimer set forth below as items 10 and 11.
  * 2.  Redistributions in binary form, except as embedded into a microcontroller or
  *     microprocessor device or a software update for such device, must reproduce any
  *     copyright notice provided with the binary code, this list of conditions, and the
  *     disclaimer set forth below as items 10 and 11, in documentation and/or other
  *     materials provided with the distribution.
  * 3.  Neither the name of STMicroelectronics nor the names of other contributors to this
  *     software may be used to endorse or promote products derived from this software or
  *     part thereof without specific written permission.
  * 4.  This software or any part thereof, including modifications and/or derivative works
  *     of this software, must be used and execute solely and exclusively in combination
  *     with a secure microcontroller device from STSAFE family manufactured by or for
  *     STMicroelectronics.
  * 5.  No use, reproduction or redistribution of this software partially or totally may be
  *     done in any manner that would subject this software to any Open Source Terms.
  *     â€œOpen Source Termsâ€� shall mean any open source license which requires as part of
  *     distribution of software that the source code of such software is distributed
  *     therewith or otherwise made available, or open source license that substantially
  *     complies with the Open Source definition specified at www.opensource.org and any
  *     other comparable open source license such as for example GNU General Public
  *     License(GPL), Eclipse Public License (EPL), Apache Software License, BSD license
  *     or MIT license.
  * 6.  STMicroelectronics has no obligation to provide any maintenance, support or
  *     updates for the software.
  * 7.  The software is and will remain the exclusive property of STMicroelectronics and
  *     its licensors. The recipient will not take any action that jeopardizes
  *     STMicroelectronics and its licensors' proprietary rights or acquire any rights
  *     in the software, except the limited rights specified hereunder.
  * 8.  The recipient shall comply with all applicable laws and regulations affecting the
  *     use of the software or any part thereof including any applicable export control
  *     law or regulation.
  * 9.  Redistribution and use of this software or any part thereof other than as  permitted
  *     under this license is void and will automatically terminate your rights under this
  *     license.
  * 10. THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" AND ANY
  *     EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  *     WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
  *     OF THIRD PARTY INTELLECTUAL PROPERTY RIGHTS, WHICH ARE DISCLAIMED TO THE FULLEST
  *     EXTENT PERMITTED BY LAW. IN NO EVENT SHALL STMICROELECTRONICS OR CONTRIBUTORS BE
  *     LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  *     DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  *     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  *     THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  *     NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  *     ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  * 11. EXCEPT AS EXPRESSLY PERMITTED HEREUNDER, NO LICENSE OR OTHER RIGHTS, WHETHER EXPRESS
  *     OR IMPLIED, ARE GRANTED UNDER ANY PATENT OR OTHER INTELLECTUAL PROPERTY RIGHTS OF
  *     STMICROELECTRONICS OR ANY THIRD PARTY.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STSAFEA_CORE_H
#define STSAFEA_CORE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stsafeaxxx.h"

/** @addtogroup STSAFE_A1XX_CORE_MODULES
  * @{
  */


/** @addtogroup CORE
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup CORE_Exported_Types CORE's exported types
  * @{
  */
/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup CORE_Exported_Defines CORE's exported defines
  * @{
  */


/** @defgroup STSAFEA_VERSION CORE's version
  * @{
  */
#define STSAFEA_VERSION_MAIN   (0x03U) /*!< [31:24] main version */
#define STSAFEA_VERSION_SUB1   (0x03U) /*!< [23:16] sub1 version */
#define STSAFEA_VERSION_SUB2   (0x01U) /*!< [15:8]  sub2 version */
#define STSAFEA_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
/**
  * @}
  */


/** @defgroup STSAFEA_DATA_LENGTH Length definition
  * @{
  */
#define STSAFEA_LENGTH_CMD_RESP_GET_SIGNATURE_SHA_256       ( 2U * (STSAFEA_LENGTH_SIZE + STSAFEA_XYRS_ECDSA_SHA256_LENGTH) ) /*!< ECDSA_SHA256 GenerateSignature CMD Response len (equal to 68)*/
#define STSAFEA_LENGTH_CMD_RESP_GET_SIGNATURE_SHA_384       ( 2U * (STSAFEA_LENGTH_SIZE + STSAFEA_XYRS_ECDSA_SHA384_LENGTH) ) /*!< ECDSA_SHA384 GenerateSignature CMD Response len (equal to 100)*/
#define STSAFEA_LENGTH_CMD_RESP_GENERATE_SIGNATURE_SHA_256  ( 2U * (STSAFEA_LENGTH_SIZE + STSAFEA_XYRS_ECDSA_SHA256_LENGTH) ) /*!< ECDSA_SHA256 GenerateSignature CMD Response len (equal to  68)*/
#define STSAFEA_LENGTH_CMD_RESP_GENERATE_SIGNATURE_SHA_384  ( 2U * (STSAFEA_LENGTH_SIZE + STSAFEA_XYRS_ECDSA_SHA384_LENGTH) ) /*!< ECDSA_SHA384 GenerateSignature CMD Response len (equal to 100)*/
/**
  * @}
  */


/** @defgroup STSAFEA_DECREMENT_CMD Bits definition for DECREMENT command
  * @{
  */
/******************  Bits definition for DECREMENT command *******************/
#define STSAFEA_CMD_DECREMENT_HEADER_CHAC_POS             (4U)                                                       /*!< Change AC indicator, if '1' means change access request, if '0' no change. */
#define STSAFEA_CMD_DECREMENT_HEADER_CHAC_MSK             (0x1UL << STSAFEA_CMD_DECREMENT_HEADER_CHAC_POS)           /*!< 0x00010000 */
#define STSAFEA_CMD_DECREMENT_HEADER_CHACEN               STSAFEA_CMD_DECREMENT_HEADER_CHAC_MSK                      /*!< Change access request enabled */

#define STSAFEA_CMD_DECREMENT_HEADER_NEWUPDRIGHT_POS      (3U)  /* Zero based */                                     /*!< New value of update AC change right. Must be equal to '0' if change AC indicator is '0'.*/
#define STSAFEA_CMD_DECREMENT_HEADER_NEWUPDRIGHT_MSK      (0x1UL << STSAFEA_CMD_DECREMENT_HEADER_NEWUPDRIGHT_POS)    /*!< 0x00001000 */
#define STSAFEA_CMD_DECREMENT_HEADER_NEWUPDRIGHT_ON       STSAFEA_CMD_DECREMENT_HEADER_NEWUPDRIGHT_MSK               /*!< Update right enabled */
#define STSAFEA_CMD_DECREMENT_HEADER_NEWUPDRIGHT_OFF      (0x0UL & STSAFEA_CMD_DECREMENT_HEADER_NEWUPDRIGHT_MSK)     /*!< Update right disabled */

#define STSAFEA_CMD_DECREMENT_HEADER_NEWUPDAC_POS         (0U) /* Zero based */                                      /*!< New value of update AC. Must be stricter than current and equal to '000' if change AC indicator is '0'.*/
#define STSAFEA_CMD_DECREMENT_HEADER_NEWUPDAC_MSK         (0x7UL << STSAFEA_CMD_DECREMENT_HEADER_NEWUPDAC_POS)       /*!< 0x00000111 */
/**
  * @}
  */


/** @defgroup STSAFEA_UPDATE_CMD Bits definition for UPDATE command
  * @{
  */
/******************  Bits definition for UPDATE command ***********************/
#define STSAFEA_CMD_UPDATE_HEADER_ATOM_POS             (7U)                                                 /*!< Atomicity mode, if '1' means the processing has to be atomic, if '0' it has not. Zero based */
#define STSAFEA_CMD_UPDATE_HEADER_ATOM_MSK             (0x1UL << STSAFEA_CMD_UPDATE_HEADER_ATOM_POS)        /*!< 0x10000000 */
#define STSAFEA_CMD_UPDATE_HEADER_ATOMEN               STSAFEA_CMD_UPDATE_HEADER_ATOM_MSK                   /*!< Atomicity mode enabled */

#define STSAFEA_CMD_UPDATE_HEADER_CHAC_POS             (4U)                                                 /*!< Change AC indicator, if '1' means a change access request, if '0' no change. Zero based */
#define STSAFEA_CMD_UPDATE_HEADER_CHAC_MSK             (0x1UL << STSAFEA_CMD_UPDATE_HEADER_CHAC_POS)        /*!< 0x00010000 */
#define STSAFEA_CMD_UPDATE_HEADER_CHACEN               STSAFEA_CMD_UPDATE_HEADER_CHAC_MSK                   /*!< Change access request enabled */

#define STSAFEA_CMD_UPDATE_HEADER_NEWUPDRIGHT_POS      (3U)                                                 /*!< New value of update AC change right. Must be equal to '0' if change AC indicator is '0'. Zero based */
#define STSAFEA_CMD_UPDATE_HEADER_NEWUPDRIGHT_MSK      (0x1UL << STSAFEA_CMD_UPDATE_HEADER_NEWUPDRIGHT_POS) /*!< 0x00001000 */
#define STSAFEA_CMD_UPDATE_HEADER_NEWUPDRIGHT_ON       STSAFEA_CMD_UPDATE_HEADER_NEWUPDRIGHT_MSK            /*!< Change access request enabled */
#define STSAFEA_CMD_UPDATE_HEADER_NEWUPDRIGHT_OFF      (0x0UL & STSAFEA_CMD_UPDATE_HEADER_NEWUPDRIGHT_MSK)  /*!< Change access request enabled */

#define STSAFEA_CMD_UPDATE_HEADER_NEWUPDAC_POS         (0U)                                                 /*!< New value of update AC. Must be stricter than current and equal to '000' if change AC indicator is '0'. Zero based */
#define STSAFEA_CMD_UPDATE_HEADER_NEWUPDAC_MSK         (0x7UL << STSAFEA_CMD_UPDATE_HEADER_NEWUPDAC_POS)    /*!< 0x00000111 */
/**
  * @}
  */


/** @defgroup STSAFEA_I2C_QUERY_CMD Bits definition for I2C parameters
  * @{
  */
/*******************  Bits definition for I2C parameters  *********************/
#define STSAFEA_I2C_MSK                       (0xFFFFU)                                        /*!< I2C param mask */
#define STSAFEA_I2C_ADDRESS_POS               (1U)                                             /*!< Address */
#define STSAFEA_I2C_ADDRESS_MSK               (0xFEU << STSAFEA_I2C_LPMODE_POS)                /*!< 0b1111111000000000 */

#define STSAFEA_I2C_LPMODE_POS                (1U)                                             /*!< Low-power mode */
#define STSAFEA_I2C_LPMODE_MSK                (0x3U << STSAFEA_I2C_LPMODE_POS)                 /*!< 0b0000000000000110 */

#define STSAFEA_I2C_LOCK_POS                  (0U)                                             /*!< Lock */
#define STSAFEA_I2C_LOCK_MSK                  (0x1U << STSAFEA_I2C_LOCK_POS)                   /*!< 0b0000000000000001 */
#define STSAFEA_I2C_LOCKEN                    STSAFEA_I2C_LOCK_MSK                             /*!< I2C Lock enabled */

#define STSAFEA_I2C_LPMODE_NONE               (0x0U << STSAFEA_I2C_LPMODE_POS)                 /*!< Low-power mode: none, 0b00000000 */
#define STSAFEA_I2C_LPMODE_STDBY              (0x2U << STSAFEA_I2C_LPMODE_POS)                 /*!< Low-power mode: standby, 0b00000100 */
#define STSAFEA_I2C_LPMODE_NOTAUTH            ((~((STSAFEA_I2C_LPMODE_NONE) | (STSAFEA_I2C_LPMODE_STDBY))) & STSAFEA_I2C_LPMODE_MSK)  /*!< Low-power mode: not authorized, 0b00000010 | 0b00000011  */

/**
  * @}
  */


/**
  * @}
  */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup CORE_Exported_Macros CORE's exported macros
  * @{
  */
#define STSAFEA_GET_ECC_CURVE_OID(CURVE_ID)     (((CURVE_ID) == STSAFEA_NIST_P_256) ? STSAFEA_ECC_CURVE_OID_NIST_P_256 :                \
                                                 ((CURVE_ID) == STSAFEA_NIST_P_384) ? STSAFEA_ECC_CURVE_OID_NIST_P_384 :                \
                                                 ((CURVE_ID) == STSAFEA_BRAINPOOL_P_256) ? STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256 :      \
                                                 ((CURVE_ID) == STSAFEA_BRAINPOOL_P_384) ? STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384 : STSAFEA_ECC_CURVE_OID_NULL)

#define STSAFEA_GET_ECC_CURVE_OID_LEN(CURVE_ID) (((CURVE_ID) == STSAFEA_NIST_P_256) ? STSAFEA_ECC_CURVE_OID_NIST_P_256_LEN :             \
                                                 ((CURVE_ID) == STSAFEA_NIST_P_384) ? STSAFEA_ECC_CURVE_OID_NIST_P_384_LEN :             \
                                                 ((CURVE_ID) == STSAFEA_BRAINPOOL_P_256) ? STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256_LEN :   \
                                                 ((CURVE_ID) == STSAFEA_BRAINPOOL_P_384) ? STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384_LEN : 0U)

#define STSAFEA_GET_XYRS_LEN_FROM_CURVE(CURVE_ID) (((CURVE_ID) == STSAFEA_NIST_P_256) ? STSAFEA_XYRS_ECDSA_SHA256_LENGTH :                 \
                                                   ((CURVE_ID) == STSAFEA_NIST_P_384) ? STSAFEA_XYRS_ECDSA_SHA384_LENGTH :                 \
                                                   ((CURVE_ID) == STSAFEA_BRAINPOOL_P_256) ? STSAFEA_XYRS_ECDSA_SHA256_LENGTH :            \
                                                   ((CURVE_ID) == STSAFEA_BRAINPOOL_P_384) ? STSAFEA_XYRS_ECDSA_SHA384_LENGTH : 0U)

#define STSAFEA_GET_SIGN_LEN_FROM_CURVE(CURVE_ID) (((CURVE_ID) == STSAFEA_NIST_P_256) ? STSAFEA_SIGN_ECDSA_SHA256_LENGTH :                 \
                                                   ((CURVE_ID) == STSAFEA_NIST_P_384) ? STSAFEA_SIGN_ECDSA_SHA384_LENGTH :                 \
                                                   ((CURVE_ID) == STSAFEA_BRAINPOOL_P_256) ? STSAFEA_SIGN_ECDSA_SHA256_LENGTH :            \
                                                   ((CURVE_ID) == STSAFEA_BRAINPOOL_P_384) ? STSAFEA_SIGN_ECDSA_SHA384_LENGTH : 0U)
/* Note: Consider to rework the following code in the next release.
   It generates a not-clear and not-readable return in the middle of functions that should be avoided */
#define STSAFEA_CHECK_SIZE(mac, index, size)                                        \
  {                                                                                  \
    if (mac == STSAFEA_MAC_NONE)                                                     \
    {                                                                                \
      if ((size + index ) > STSAFEA_BUFFER_DATA_CONTENT_SIZE)                        \
      {                                                                              \
        return STSAFEA_BUFFER_LENGTH_EXCEEDED;                                       \
      }                                                                              \
    }                                                                                \
    else                                                                             \
    {                                                                                \
      if ((size + index ) > (STSAFEA_BUFFER_DATA_CONTENT_SIZE - STSAFEA_MAC_LENGTH)) \
      {                                                                              \
        return STSAFEA_BUFFER_LENGTH_EXCEEDED;                                       \
      }                                                                              \
    }                                                                                \
  }

/**
  * @brief STSAFEA Middleware version number
  */
#define STSAFEA_VERSION        ((STSAFEA_VERSION_MAIN << 24U) | \
                                (STSAFEA_VERSION_SUB1 << 16U) | \
                                (STSAFEA_VERSION_SUB2 <<  8U) | \
                                (STSAFEA_VERSION_RC))

#define STSAFEA_CRC_SUPPORT                                             ((uint8_t)1)            /*!< Crc support flag */
#define STSAFEA_PRIVATE_KEY_MODE_OF_OPERATION_CHANGE_RIGHT_MASK         ((uint16_t)0x8000)      /*!< Mask */
#define STSAFEA_PRIVATE_KEY_MODE_OF_OPERATION_AUTHORIZATION_FLAGS_MASK  ((uint16_t)0x000D)      /*!< Mask */
#define STSAFEA_PASSWORD_SIZE                                           ((uint16_t)16)          /*!< Password size */
#define STSAFEA_ONE_WAY_COUNTER_PRESENCE                                ((uint8_t)1)            /*!< One way counter presence */
#define STSAFEA_HOST_CMAC_INVALID_COUNTER                               ((uint32_t)0x00FFFFFF)  /*!< Invalid counter */

#define STSAFEA_RANDOM_ENTITY_AUTH_RESPONSE_LENGTH                      ((uint16_t)16)      /*!< Response length to random command for entity authentication */
#define STSAFEA_DECREMENT_RESPONSE_LENGTH                               ((uint16_t)4)       /*!< Response length to decrement command */
#define STSAFEA_VERIFY_MSG_SIGNATURE_RESPONSE_LENGTH                    ((uint16_t)1)       /*!< Response length to verify message authentication command */
#define STSAFEA_VERIFY_ENTITY_SIGNATURE_RESPONSE_LENGTH                 ((uint16_t)1)       /*!< Response length to verify entity authentication command */
#define STSAFEA_PRODUCT_DATA_QUERY_RESPONSE_LENGTH                      ((uint16_t)39)      /*!< Response length to product data query */
#define STSAFEA_DATA_PARTITION_QUERY_MIN_RESPONSE_LENGTH                ((uint16_t)1)       /*!< Minimum response length to data partition query */
#define STSAFEA_I2C_PARAMETERS_QUERY_RESPONSE_LENGTH                    ((uint16_t)2)       /*!< Response length to I2C parameters query */
#define STSAFEA_LIFE_CYCLE_STATE_QUERY_RESPONSE_LENGTH                  ((uint16_t)1)       /*!< Response length to life cycle state query */
#define STSAFEA_PUBLIC_KEY_SLOT_QUERY_MIN_RESPONSE_LENGTH               ((uint16_t)1)       /*!< Minimum response length to public key slot query */
#define STSAFEA_HOST_KEY_SLOT_QUERY_RESPONSE_LENGTH                     ((uint16_t)4)       /*!< Response length to host key slot query */
#define STSAFEA_LOCAL_ENVELOPE_QUERY_MIN_RESPONSE_LENGTH                ((uint16_t)7)       /*!< Minimum response length to local envelope key slot query */
#define STSAFEA_CMD_AUTH_CONFIG_QUERY_MIN_RESPONSE_LENGTH               ((uint16_t)2)       /*!< Minimum response length to command authorization configuration query */
#define STSAFEA_WRAP_UNWRAP_ENVELOPE_ADDITIONAL_RESPONSE_LENGTH         ((uint16_t)8)       /*!< Additional 8-bytes to consider for Wrap/Unwrap commands */
#define STSAFEA_VERIFY_PASSWORD_RESPONSE_LENGTH                         ((uint16_t)2)       /*!< Response length to I2C parameters query */


#define WORKAROUND_GENERATE_SIGNATURE /* STSAFE-A1x0 hangs when hash containing only NULL bytes */

/**
  * @}
  */


/* Exported variables --------------------------------------------------------*/
/** @defgroup CORE_Exported_Variables  CORE's exported variables
  * @{
  */
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup CORE_Exported_Functions CORE's exported functions
  * @{
  */

/** @addgroup CORE_Exported_Functions_Group1 Initialization / Configuration Commands APIs
  *  @brief    STSAFE-A Core APIs related to Initialization and configuration commands
  *
@verbatim
 ===============================================================================
              ##### Initialization / Configuration Commands #####
 ===============================================================================
[..]
    (+) Init
@endverbatim
  * @{
  */

/**
  * @brief   StSafeA_Init
  *          Create, initialize and assign the STSAFE-A1xx device handle.
  * @note    No other APIs can be called/used if this one has never been called
  *
  * @param   pStSafeA : Handle pointer for STSAFE-A1xx interface to be properly initialized
  * @param   pAllocatedRxTxBufferData : Rx/Tx Buffer used to transmit/receive data to/from STSAFEA.
  *          Memory for Rx/Tx buffer must be allocated before being passed to this function
  * @retval  STSAFEA_OK if success, an error code otherwise
  */
StSafeA_ResponseCode_t StSafeA_Init(
  StSafeA_Handle_t *pStSafeA,
  uint8_t *pAllocatedRxTxBufferData);
/**
  * @}
  */


/** @addgroup CORE_Exported_Functions_Group2 General Purpose Commands APIs
  *  @brief    STSAFE-A APIs related to general purpose commands
  *
@verbatim
 ===============================================================================
              ##### General Purpose Commands #####
 ===============================================================================
[..]
    (+) Get Version
    (+) Echo
    (+) Reset
    (+) Generate Random
    (+) Hibernate
@endverbatim
  * @{
  */

/**
  * @brief   StSafeA_GetVersion
  *          Returns the STSAFE-A1xx Middleware revision
  *
  * @param   None
  * @retval  int32_t version in the format 0xXYZR (8bits for each XYZ decimal, R for release candidate)\n
  *                          [31:24] main version \n
  *                          [23:16] sub1 version \n
  *                          [15:8]  sub2 version \n
  *                          [7:0]  release candidate
  */
int32_t StSafeA_GetVersion(void);

/**
  * @brief   StSafeA_Echo
  *          Executes the echo command expecting to receive back from STSAFEA the
  *          same data passed in the command.
  *
  * @param   pStSafeA       : STSAFE-A1xx object pointer.
  * @param   pInEchoData    : Pointer to bytes array.
  * @param   InRespDataLen  : Expected data length in bytes of 'echoed' data (pOutLVResponse->Data).\n
  *                           Used if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0.
  * @param   pOutLVResponse : LV structure pointer to be filled with the response data.\n
  *                           If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                           If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   InMAC          : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_Echo(
  StSafeA_Handle_t *pStSafeA,
  uint8_t *pInEchoData,
  uint16_t InRespDataLen,
  StSafeA_LVBuffer_t *pOutLVResponse,
  uint8_t InMAC);

/**
  * @brief   StSafeA_Reset
  *          Reset command executed to reset the volatile attributes to their initial value.
  *
  * @param   pStSafeA      : STSAFE-A1xx object pointer.
  * @param   InMAC         : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_Reset(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InMAC);

/**
  * @brief   StSafeA_GenerateRandom
  *          Generates a number of random bytes
  *
  * @param   pStSafeA       : STSAFE-A1xx object pointer.
  * @param   InRndSubject   : Random bytes type (STSAFEA_EPHEMERAL or STSAFEA_ENTITY_AUTHENTICATION).\n
  *                           Only used for STSAFE-A100.
  * @param   InRespDataLen  : Expected data length in bytes of generated random (pOutLVResponse->Data).\n
  *                           Used if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0.
  * @param   pOutLVResponse : LV structure pointer to be filled with the response data.\n
  *                           If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                           If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   InMAC          : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_GenerateRandom(
  StSafeA_Handle_t *pStSafeA,
  StSafeA_RndSubject_t InRndSubject,
  uint8_t InRespDataLen,
  StSafeA_LVBuffer_t *pOutLVResponse,
  uint8_t InMAC);

/**
  * @brief   StSafeA_Hibernate
  *          This function is executed to put the STSAFE-A1xx device in hibernation.
  *
  * @param   pStSafeA      : STSAFE-A1xx object pointer.
  * @param   InWakeUpMode  : Wake up mode conditions.\n
  *                          Can be one of the following values:\n
  *                          @arg STSAFEA_WAKEUP_FROM_I2C_START_OR_RESET: Wake up from hibernate after I2C start condition or after reset.\n
  *                          @arg STSAFEA_WAKEUP_FROM_RESET: Wake up from hibernate after reset only.
  * @param   InMAC         : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_Hibernate(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InWakeUpMode,
  uint8_t InMAC);
/**
  * @}
  */

/**
  * @brief   StSafeA_Process_Update
  *          This command updates data through zone partition without counter:
  *          - It may start by changing the update access conditions before updating the data in a zone with no one-way counter.\n
  *          - It carries out both operations in a single atomic operation.
  * @note    Note that changing the update AC change right is irreversible and that, if allowed, the update access conditions may only be changed to a stricter value.
  *
  * @param   pStSafeA            : STSAFE-A1xx object pointer.
  * @param   InAtomicity         : STSAFEA_FLAG_TRUE (1) if update will be done in atomic way, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InChangeACIndicator : STSAFEA_FLAG_TRUE (1) if change, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewUpdateACRight  : STSAFEA_FLAG_TRUE (1) to change update access condition right, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewUpdateAC       : Must be stricter than current and equal to 000b if InChangeACIndicator is 0. Can be one of the following values:
  *                                @arg STSAFEA_AC_ALWAYS (0) Access Condition always allowed. Also use this value if InChangeACIndicator is 0
  *                                @arg STSAFEA_AC_HOST   MAC or Auth AC must be fulfilled
  *                                @arg STSAFEA_AC_AUTH   A valid C-MAC must have been received on the command or on some previous command
  *                                @arg STSAFEA_AC_MAC    Command must have a valid C-MAC
  * @param   InZoneIndex         : Specify the Zone Index to apply the command to.
  * @param   InOffset            : offset in data segment, from where data are written.
  * @param   pInLVData           : LV structure pointer containing the data to be written.
  * @param   InMAC               : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_Process_Update(StSafeA_Handle_t *pStSafeA, uint8_t InAtomicity,
                                              uint8_t InChangeACIndicator, uint8_t InNewUpdateACRight,
                                              uint8_t InNewUpdateAC, uint8_t InZoneIndex,
                                              uint16_t InOffset, StSafeA_LVBuffer_t *pInLVData, uint8_t InMAC);


/** @addgroup CORE_Exported_Functions_Group3 Data Partition Commands APIs
  *  @brief    STSAFE-A APIs related to data partition commands
  *
@verbatim
 ===============================================================================
              ##### Data Partition Commands #####
 ===============================================================================
[..]
    (+) Data Partition Query
    (+) Decrement
    (+) Read
    (+) Update
@endverbatim
  * @{
  */

/**
  * @brief   StSafeA_DataPartitionQuery
  *          Query command to retrieve data partition configuration.
  *
  * @param   pStSafeA          : STSAFE-A1xx object pointer.
  * @param   InZoneMaxNum      : Expected number of zones.\n
  *                              Must correspond to the num of zones allocated for pOutDataPartition->pZoneInfoRecord, if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0.\n
  *                              If unknown it's possible to specify 0 (zero). In this case the num of zones will be returned in pOutDataPartition->NumberOfZones and\n
  *                              the function can then be called once again with the right InZoneMaxNum value.\n
  *                              Specify 0xFF if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1.
  * @param   pOutDataPartition : StSafeA_DataPartitionBuffer_t structure pointer to be filled with the response data partition.\n
  *                              If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the internal StSafeA_ZoneInformationRecordBuffer_t structure array must have been properly allocated.\n
  *                              If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned to pOutDataPartition->pZoneInfoRecord.
  * @param   InMAC             : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_DataPartitionQuery(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InZoneMaxNum,
  StSafeA_DataPartitionBuffer_t *pOutDataPartition,
  uint8_t InMAC);

/**
  * @brief   StSafeA_Decrement
  *          This command is applied to a counter zone and performs the following processing:\n
  *          - It changes the update access conditions and the update AC change right.\n
  *          - It decrements the one way counter with the amount given as parameter.\n
  *          - It updates data in its data segment with data buffer pointed.
  * @note    The change in "update AC change right" is irreversible and the \n
  *          "update access conditions" may only be changed to a stricter value
  *
  * @param   pStSafeA              : STSAFE-A1xx object pointer.
  * @param   InChangeACIndicator   : STSAFEA_FLAG_TRUE (1) if change, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewDecrementACRight : STSAFEA_FLAG_TRUE (1) to change decrement access condition right, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewDecrementAC      : Must be more strict than current and equal to 000b if InChangeACIndicator is 0.\n
  *                                  Can be one of the following values:\n
  *                                  @arg STSAFEA_AC_ALWAYS (0) Access Condition always allowed. Also use this value if InChangeACIndicator is 0.\n
  *                                  @arg STSAFEA_AC_HOST   MAC or Auth AC must be fulfilled.\n
  *                                  @arg STSAFEA_AC_AUTH   A valid C-MAC must have been received on the command or on some previous command.\n
  *                                  @arg STSAFEA_AC_MAC    Command must have a valid C-MAC.
  * @param   InZoneIndex           : Specify the Zone Index to apply the command to.
  * @param   InOffset              : Offset in data segment where data, if any, are written.
  * @param   InAmount              : Must be strictly larger than 0.
  * @param   pInData               : LV structure pointer with input data.
  * @param   pOutDecrement         : StSafeA_DecrementBuffer_t structure pointer to be filled with the response data.\n
  *                                  Pointer must have been properly allocated.
  * @param   InMAC                 : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_Decrement(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InChangeACIndicator,
  uint8_t InNewDecrementACRight,
  uint8_t InNewDecrementAC,
  uint8_t InZoneIndex,
  uint16_t InOffset,
  uint32_t InAmount,
  StSafeA_LVBuffer_t *pInData,
  StSafeA_DecrementBuffer_t *pOutDecrement,
  uint8_t InMAC);

/**
  * @brief   StSafeA_Read
  *          This command read data from a data partition zone:
  *          - It may change the read access conditions before reading the data.\n
  *          - It checks the access conditions and only returns the data starting from the specified offset up to the zone boundary.\n
  * @note    Note that change in read AC change right is irreversible and that, if allowed, the read access conditions may only be changed to a stricter value.
  *
  * @param   pStSafeA            : STSAFE-A1xx object pointer.
  * @param   InChangeACIndicator : STSAFEA_FLAG_TRUE (1) if change, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewReadACRight    : STSAFEA_FLAG_TRUE (1) to change read access condition right, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewReadAC         : Must be stricter than current and equal to 000b if InChangeACIndicator is 0.\n
  *                                Can be one of the following values:\n
  *                                @arg STSAFEA_AC_ALWAYS (0) Access Condition always allowed. Also use this value if InChangeACIndicator is 0.\n
  *                                @arg STSAFEA_AC_HOST   MAC or Auth AC must be fulfilled for the command.\n
  *                                @arg STSAFEA_AC_AUTH   A valid C-MAC must have been received on the command or on some previous command.\n
  *                                @arg STSAFEA_AC_MAC    Command must have a valid C-MAC.
  * @param   InZoneIndex         : Specify the Zone Index to apply the command to.
  * @param   InOffset            : Range supported is from 0 up to the length of the data segment.
  * @param   InAmount            : Must be strictly larger than 0.
  * @param   InRespDataLen       : Expected data length in bytes of read data (pOutLVResponse->Data). Take care to include the length of the counter if any.\n
  *                                Used if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0.
  * @param   pOutLVResponse      : LV structure pointer to be filled with the response data.\n
  *                                If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                                If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   InMAC               : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_Read(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InChangeACIndicator,
  uint8_t InNewReadACRight,
  uint8_t InNewReadAC,
  uint8_t InZoneIndex,
  uint16_t InOffset,
  uint16_t InAmount,
  uint16_t InRespDataLen,
  StSafeA_LVBuffer_t *pOutLVResponse,
  uint8_t InMAC);

/**
  * @brief   StSafeA_Update
  *          This command updates data through zone partition without counter:
  *          - It may start by changing the update access conditions before updating the data in a zone with no one-way counter.\n
  *          - It carries out both operations in a single atomic operation.
  * @note    Note that changing the update AC change right is irreversible and that, if allowed, the update access conditions may only be changed to a stricter value.
  *
  * @param   pStSafeA            : STSAFE-A1xx object pointer.
  * @param   InAtomicity         : STSAFEA_FLAG_TRUE (1) if update will be done in atomic way, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InChangeACIndicator : STSAFEA_FLAG_TRUE (1) if change, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewUpdateACRight  : STSAFEA_FLAG_TRUE (1) to change update access condition right, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewUpdateAC       : Must be stricter than current and equal to 000b if InChangeACIndicator is 0.\n
  *                                Can be one of the following values:\n
  *                                @arg STSAFEA_AC_ALWAYS (0) Access Condition always allowed. Also use this value if InChangeACIndicator is 0.\n
  *                                @arg STSAFEA_AC_HOST   MAC or Auth AC must be fulfilled.\n
  *                                @arg STSAFEA_AC_AUTH   A valid C-MAC must have been received on the command or on some previous command.\n
  *                                @arg STSAFEA_AC_MAC    Command must have a valid C-MAC.
  * @param   InZoneIndex         : Specify the Zone Index to apply the command to.
  * @param   InOffset            : offset in data segment, from where data are written.
  * @param   pInLVData           : LV structure pointer containing the data to be written.
  * @param   InMAC               : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_Update(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InAtomicity,
  uint8_t InChangeACIndicator,
  uint8_t InNewUpdateACRight,
  uint8_t InNewUpdateAC,
  uint8_t InZoneIndex,
  uint16_t InOffset,
  StSafeA_LVBuffer_t *pInLVData,
  uint8_t InMAC);
/**
  * @}
  */


/** @addgroup CORE_Exported_Functions_Group4 Private and Public Key Commands APIs
  *  @brief    STSAFE-A APIs related to private and public key commands
  *
@verbatim
 ===============================================================================
              ##### Private and Public Key Commands  #####
 ===============================================================================
[..]
    (+) Generate Key Pair
    (+) Generate Signature
    (+) Verify Message Signature
    (+) Establish Key
@endverbatim
  * @{
  */

/**
  * @brief   StSafeA_GenerateKeyPair
  *          This command instructs the STSAFE-A1xx to generate a key-pair in a private key slot.
  * @note    If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the pOutPubX & pOutPubY LV structure pointers must have been properly allocated. \n
  *          If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1, pointers inside pStSafeA->InOutBuffer will be assigned.
  *
  * @param   pStSafeA                  : STSAFE-A1xx object pointer.
  * @param   InKeySlotNum              : Slot number in the private key table.\n
  *                                      Can be one of the following values:\n
  *                                      @arg STSAFEA_KEY_SLOT_0: Slot 0 in private key table.\n
  *                                      @arg STSAFEA_KEY_SLOT_1: Slot 1 in private key table.
  * @param   InUseLimit                : Maximum number of times the key can be used (0xFFFF : no limit).
  * @param   InChangeACIndicator       : STSAFEA_FLAG_TRUE (1) if change, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InNewDecrementACRight     : STSAFEA_FLAG_TRUE (1) to change decrement access condition right, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InChangeAuthFlagsRight    : STSAFEA_FLAG_TRUE (1) to allow changing authorization right, STSAFEA_FLAG_FALSE (0) if not.
  * @param   InAuthorizationFlags      : A combination of the following values:\n
  *                                      @arg STSAFEA_PRVKEY_MODOPER_AUTHFLAG_CMD_RESP_SIGNEN.\n
  *                                      @arg STSAFEA_PRVKEY_MODOPER_AUTHFLAG_MSG_DGST_SIGNEN.\n
  *                                      @arg STSAFEA_PRVKEY_MODOPER_AUTHFLAG_KEY_ESTABLISHEN.
  * @param   InCurveId                  : Curve identifier.
  * @param   InPubXYLen                 : Expected data length in bytes of public key X & Y coordinates (pOutPubX->Data & pOutPubY->Data).\n
  *                                       Used if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0.
  * @param   pOutPointReprensentationId : byte pointer to be filled with point representation identifier and must have been properly allocated.
  * @param   pOutPubX                   : LV structure pointer to be filled with public key X coordinate.
  *                                       If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                                       If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   pOutPubY                   : LV structure pointer to be filled with public key Y coordinate.
  *                                       If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                                       If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   InMAC                      : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_GenerateKeyPair(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InKeySlotNum,
  uint16_t InUseLimit,
  uint8_t InChangeAuthFlagsRight,
  uint8_t InAuthorizationFlags,
  StSafeA_CurveId_t InCurveId,
  uint16_t InPubXYLen,
  uint8_t *pOutPointReprensentationId,
  StSafeA_LVBuffer_t *pOutPubX,
  StSafeA_LVBuffer_t *pOutPubY,
  uint8_t InMAC);

/**
  * @brief   StSafeA_GenerateSignature
  *          This command returns the ECDSA signature over a message digest.
  * @note    If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the pOutSignR & pOutSignS LV structure pointers must have been properly allocated. \n
  *          If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1, pointers inside pStSafeA->InOutBuffer will be assigned.
  *
  * @param   pStSafeA         : STSAFE-A1xx object pointer.
  * @param   InKeySlotNum     : Slot number in the private key table.\n
  *                             Can be one of the following values:\n
  *                             @arg STSAFEA_KEY_SLOT_0: Slot 0 in private key table.\n
 *                             @arg STSAFEA_KEY_SLOT_1: Slot 1 in private key table.
  * @param   pInDigest        : Pointer to message digest bytes array.
  * @param   InDigestType     : Digest type.
  * @param   InSignRSLen      : Expected data length in bytes of ECDSA signature's part X & Y (pOutSignR->Data & pOutSignS->Data).\n
  *                             Can be one of the following values:\n
  *                             @arg STSAFEA_XYRS_ECDSA_SHA256_LENGTH.\n
  *                             @arg STSAFEA_XYRS_ECDSA_SHA384_LENGTH.\n
  *                             Used if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0.
  * @param   pOutSignR        : LV structure pointer to be filled with the ECDSA signature R.\n
  *                             If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                             If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   pOutSignR        : LV structure pointer to be filled with the ECDSA signature S.\n
  *                             If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                             If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   InMAC            : MAC authenticating command/response
  * @param   InHostEncryption : Encryption type.\n
  *                             Can be one of the following values:\n
  *                             @arg STSAFEA_ENCRYPTION_NONE: No encryption needed.\n
  *                             @arg STSAFEA_ENCRYPTION_RESPONSE: Response will be generated encrypted.\n
  *                             @arg STSAFEA_ENCRYPTION_COMMAND: Command is encrypted before sending.\n
  *                             @arg STSAFEA_ENCRYPTION_COMMAND_RESPONSE: Both command and response are encrypted.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_GenerateSignature(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InKeySlotNum,
  const uint8_t *pInDigest,
  StSafeA_HashTypes_t InDigestType,
  uint16_t InSignRSLen,
  StSafeA_LVBuffer_t *pOutSignR,
  StSafeA_LVBuffer_t *pOutSignS,
  uint8_t InMAC,
  uint8_t InHostEncryption);

/**
  * @brief   StSafeA_VerifyMessageSignature
  *          This command is executed for Message authentication.
  * @note    Note that this command doesn't require a signature session to be ongoing.
  *
  * @param   pStSafeA      : STSAFE-A1xx object pointer.
  * @param   InCurveId     : Curve identifier.
  * @param   pInPubX       : LV structure pointer defining public key X coordinate.
  * @param   pInPubY       : LV structure pointer defining public key X coordinate.
  * @param   pInRSignature : LV structure pointer defining R of ECDSA signature.
  * @param   pInSSignature : LV structure pointer defining S of ECDSA signature.
  * @param   pInDigest     : Pointer to message digest bytes array.
  * @param   pOutRespVerifySignature : StSafeA_VerifySignatureBuffer_t structure pointer to be filled with\n
  *                                    the signature validity response.\n
  *                                    Pointer must have been properly allocated.
  * @param   InMAC         : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_VerifyMessageSignature(
  StSafeA_Handle_t *pStSafeA,
  const StSafeA_CurveId_t InCurveId,
  const StSafeA_LVBuffer_t *pInPubX,
  const StSafeA_LVBuffer_t *pInPubY,
  const StSafeA_LVBuffer_t *pInSignR,
  const StSafeA_LVBuffer_t *pInSignS,
  const StSafeA_LVBuffer_t *pInDigest,
  StSafeA_VerifySignatureBuffer_t *pOutRespVerifySignature,
  uint8_t InMAC);

/**
  * @brief   StSafeA_EstablishKey
  *          This command establish shared secret between 2 hosts by using asymmetric cryptography.
  * @note    Note that this command doesn't require an asymmetric crypto session to be ongoing.
  *
  * @param   pStSafeA             : STSAFE-A1xx object pointer.
  * @param   InKeySlotNum         : Slot number in the private key table.\n
  *                                 Can be one of the following values:\n
  *                                 @arg STSAFEA_KEY_SLOT_0: Slot 0 in private key table.\n
  *                                 @arg STSAFEA_KEY_SLOT_1: Slot 1 in private key table.
  * @param   pInPubX              : LV structure pointer defining public key X coordinate.
  * @param   pInPubY              : LV structure pointer defining public key X coordinate.
  * @param   InSharedSecretLength : Expected data length in bytes of computed shared secret (pOutSharedSecret->SharedKey.Data).\n
  *                                 Can be one of the following values:\n
  *                                 @arg STSAFEA_XYRS_ECDSA_SHA256_LENGTH.\n
  *                                 @arg STSAFEA_XYRS_ECDSA_SHA384_LENGTH.\n
  *                                 Used if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0.
  * @param   pOutSharedSecret     : StSafeA_SharedSecretBuffer_t structure pointer to be filled with the response data, coded as length and key.\n
  *                                 If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the StSafeA_SharedSecretBuffer_t SharedKey structure must have been properly allocated.\n
  *                                 If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned for the SharedKey.
  * @param   InMAC                : MAC authenticating command/response.
  * @param   InHostEncryption     : Encryption type.\n
  *                                 Can be one of the following values:\n
  *                                 @arg STSAFEA_ENCRYPTION_NONE: No encryption needed.\n
  *                                 @arg STSAFEA_ENCRYPTION_RESPONSE: Response will be generated encrypted.\n
  *                                 @arg STSAFEA_ENCRYPTION_COMMAND: Command is encrypted before sending.\n
  *                                 @arg STSAFEA_ENCRYPTION_COMMAND_RESPONSE: Both command and response are encrypted.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_EstablishKey(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InKeySlotNum,
  const StSafeA_LVBuffer_t *pInPubX,
  const StSafeA_LVBuffer_t *pInPubY,
  uint16_t InSharedSecretLength,
  StSafeA_SharedSecretBuffer_t *pOutSharedSecret,
  uint8_t InMAC,
  uint8_t InHostEncryption);
/**
  * @}
  */


/** @addgroup CORE_Exported_Functions_Group5 Administrative Commands APIs
  *  @brief    STSAFE-A APIs related to administrative commands
  *
@verbatim
 ===============================================================================
              ##### Administrative Commands  #####
 ===============================================================================
[..]
    (+) Product Data Query
    (+) I2C Parameter Query
    (+) Life Cycle State Query
    (+) Host Key Slot Query
    (+) Put Attribute
    (+) Delete Password
    (+) Verify Password
    (+) RawCommand
@endverbatim
  * @{
  */

/**
  * @brief   StSafeA_ProductDataQuery
  *          Query command to retrieve product data.
  *
  * @param   pStSafeA          : STSAFE-A1xx object pointer.
  * @param   pOutProductData   : StSafeA_ProductDataBuffer_t structure pointer to be filled with the response product data.\n
  *                              The pointer must have been properly allocated.
  * @param   InMAC             : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_ProductDataQuery(
  StSafeA_Handle_t *pStSafeA,
  StSafeA_ProductDataBuffer_t *pOutProductData,
  uint8_t InMAC);

/**
  * @brief   StSafeA_I2cParameterQuery
  *          Query command to retrieve I2C address and low power mode configuration.
  *
  * @param   pStSafeA         : STSAFE-A1xx object pointer
  * @param   pOutI2CParamData : StSafeA_I2cParameterBuffer_t structure pointer to be filled with the response data.\n
  *                             The pointer must have been properly allocated.
  * @param   InMAC            : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_I2cParameterQuery(
  StSafeA_Handle_t *pStSafeA,
  StSafeA_I2cParameterBuffer_t *pOutI2CParamData,
  uint8_t InMAC);


/**
  * @brief   StSafeA_LifeCycleStateQuery
  *          Query command to retrieve the life cycle state product status.
  *
  * @param   pStSafeA           : STSAFE-A1xx object pointer.
  * @param   pOutLifeCycleState : StSafeA_LifeCycleStateBuffer_t structure pointer to be filled with the response data.\n
  *                               The pointer must have been properly allocated.
  * @param   InMAC              : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_LifeCycleStateQuery(
  StSafeA_Handle_t *pStSafeA,
  StSafeA_LifeCycleStateBuffer_t *pOutLifeCycleState,
  uint8_t InMAC);


/**
  * @brief   StSafeA_HostKeySlotQuery
  *          Query command to retrieve the host key information (presence & host C-MAC counter).
  *
  * @param   pStSafeA          : STSAFE-A1xx object pointer
  * @param   pOutHostKeySlot   : StSafeA_HostKeySlotBuffer_t structure pointer to be filled with the response data.\n
  *                              The pointer must have been properly allocated.
  * @param   InMAC             : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_HostKeySlotQuery(
  StSafeA_Handle_t *pStSafeA,
  StSafeA_HostKeySlotBuffer_t *pOutHostKeySlot,
  uint8_t InMAC);


/**
  * @brief   StSafeA_PutAttribute
  *          This command is executed to put attributes in the STSAFE-A1xx device like
  *          keys, password, I2C parameters according to the attribute TAG.
  *
  * @param   pStSafeA       : STSAFE-A1xx object pointer.
  * @param   InAttributeTag : Attribute tag.
  * @param   pInData        : pointer to attribute value (bytes array).
  * @param   InDataSize     : attribute value size in bytes.
  * @param   InMAC          : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_PutAttribute(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InAttributeTag,
  const uint8_t *pInData,
  uint16_t InDataSize,
  uint8_t InMAC);


/**
  * @brief   StSafeA_DeletePassword
  *          This command instructs the STSAFE-A1xx to delete the password form its slot.
  *
  * @param   pStSafeA    : STSAFE-A1xx object pointer.
  * @param   InMAC       : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_DeletePassword(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InMAC);


/**
  * @brief   StSafeA_VerifyPassword
  *          This command performs password verification
  *          and remembers the outcome of the verification for future command authorization.
  *
  * @param   pStSafeA            : STSAFE-A1xx object pointer.
  * @param   pInPassword         : Pointer to password bytes array (16 bytes length).
  * @param   pOutVerifyPassword  : StSafeA_VerifyPasswordBuffer_t structure pointer to be filled with response data.\n
  *                                The pointer must have been properly allocated.
  * @param   InMAC               : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_VerifyPassword(
  StSafeA_Handle_t *pStSafeA,
  const uint8_t *pInPassword,
  StSafeA_VerifyPasswordBuffer_t *pOutVerifyPassword,
  uint8_t InMAC);


/**
  * @brief   StSafeA_RawCommand
  *          This functions is used to execute a raw command and receive the related response.
  *
  * @param   pStSafeA       : STSAFE-A1xx object pointer.
  * @param   pInRawCommand  : Pointer to the TLV structure containing the command to send to STSAFE-A device.
  * @param   InRespDataLen  : Expected response length. Specify 0xFF if STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1.
  * @param   pOutLVResponse : LV structure pointer to be filled with the response data.\n
  *                           If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                           If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   DelayMs        : Waiting time in ms after the command has been sent, before checking for the received response.
  * @param   InMAC          : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_RawCommand(
  StSafeA_Handle_t *pStSafeA,
  const StSafeA_TLVBuffer_t *pInRawCommand,
  uint16_t InRespDataLen,
  StSafeA_TLVBuffer_t *pOutTLVResponse,
  uint32_t DelayMs,
  uint8_t InMAC);
/**
  * @}
  */


/** @addgroup CORE_Exported_Functions_Group6 Local Envelope Commands APIs
  *  @brief    STSAFE-A APIs related to local envelope commands APIs
  *
@verbatim
 ===============================================================================
              ##### Local Envelope Commands  #####
 ===============================================================================
[..]
    (+) Local Envelope Key Slot Query
    (+) Generate Local Envelope Key
    (+) Wrap Local Envelope
    (+) Unwrap Local Envelope
@endverbatim
  * @{
  */

/**
  * @brief   StSafeA_LocalEnvelopeKeySlotQuery
  *          Query command to retrieve local envevelope keys information (slot number, presence & key length) for the available key slots.
  *
  * @param   pStSafeA                                    : STSAFE-A1xx object pointer
  * @param   pOutLocalEnvelopeKeyTable                   : StSafeA_LocalEnvelopeKeyTableBuffer_t structure pointer to be filled with response data.\n
  *                                                        The pointer must have been properly allocated.
  * @param   pOutLlocalEnvelopeKeySlot0InformationRecord : StSafeA_LocalEnvelopeKeyInformationRecordBuffer_t structure pointer to be filled with local envelope key slot 0 information.
  *                                                        The pointer must have been properly allocated.
  * @param   pOutLlocalEnvelopeKeySlot1InformationRecord : StSafeA_LocalEnvelopeKeyInformationRecordBuffer_t structure pointer to be filled with local envelope key slot 1 information.
  *                                                        The pointer must have been properly allocated.
  * @param   InMAC         : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_LocalEnvelopeKeySlotQuery(
  StSafeA_Handle_t *pStSafeA,
  StSafeA_LocalEnvelopeKeyTableBuffer_t *pOutLocalEnvelopeKeyTable,
  StSafeA_LocalEnvelopeKeyInformationRecordBuffer_t *pOutLlocalEnvelopeKeySlot0InformationRecord,
  StSafeA_LocalEnvelopeKeyInformationRecordBuffer_t *pOutLlocalEnvelopeKeySlot1InformationRecord,
  uint8_t InMAC);


/**
  * @brief   StSafeA_GenerateLocalEnvelopeKey
  *          This command instructs the STSAFE-A1xx to generate a key in a local envelope key slot.
  *
  * @param   pStSafeA      : STSAFE-A1xx object pointer.
  * @param   InKeySlotNum  : Slot number in the KSK table.\n
  *                          Can be one of the following values:\n
  *                          @arg STSAFEA_KEY_SLOT_0: Slot 0 in the KSK table.\n
  *                          @arg STSAFEA_KEY_SLOT_1: Slot 1 in the KSK table.
  * @param   InKeyType     : AES Key type.\n
  *                          Can be one of the following values:\n
  *                          @arg STSAFEA_KEY_TYPE_AES_128: AES-128 bits key.\n
  *                          @arg STSAFEA_KEY_TYPE_AES_256: AES-256 bits key.
  * @param   pInSeed       : Seed pointer. It's optional and can be empty.
  * @param   InSeedSize    : Seed size in bytes. Should be 0 is seed is empty.
  * @param   InMAC         : MAC authenticating command/response.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_GenerateLocalEnvelopeKey(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InKeySlotNum,
  uint8_t InKeyType,
  uint8_t *pInSeed,
  uint16_t InSeedSize,
  uint8_t InMAC);


/**
  * @brief   StSafeA_WrapLocalEnvelope
  *          This command is used to wrap data and typically working keys that are entirely
  *          managed by the host, with a local envelope key and the [AES key wrap] algorithm.
  *
  * @param   pStSafeA         : STSAFE-A1xx object pointer.
  * @param   InKeySlotNum     : Local envelope key slot number.\n
  *                             Can be one of the following values:\n
  *                             @arg STSAFEA_KEY_SLOT_0: Slot 0 in local envelope key table.\n
  *                             @arg STSAFEA_KEY_SLOT_1: Slot 1 in local envelope key table.
  * @param   pInData          : Pointer to data bytes array to wrap.
  * @param   InDataSize       : Data size (non-zero, multiple of 8 bytes and maximum 480 bytes).
  * @param   pOutLVResponse   : LV structure pointer to be filled with the wrapped local envelope response data.\n
  *                             If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                             If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   InMAC            : MAC authenticating command/response.
  * @param   InHostEncryption : Encryption type.
  *                             Can be one of the following values:\n
  *                             @arg STSAFEA_ENCRYPTION_NONE: No encryption needed.\n
  *                             @arg STSAFEA_ENCRYPTION_RESPONSE: Response will be generated encrypted.\n
  *                             @arg STSAFEA_ENCRYPTION_COMMAND: Command is encrypted before sending.\n
  *                             @arg STSAFEA_ENCRYPTION_COMMAND_RESPONSE: Both command and response are encrypted.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_WrapLocalEnvelope(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InKeySlotNum,
  uint8_t *pInData,
  uint16_t InDataSize,
  StSafeA_LVBuffer_t *pOutLVResponse,
  uint8_t InMAC,
  uint8_t InHostEncryption);


/**
  * @brief   StSafeA_UnwrapLocalEnvelope
  *          This command is used to unwrap a local envelope with a local envelope key.
  *          The result can be a working key that is further used by the host.
  *
  * @param   pStSafeA            : STSAFE-A1xx object pointer.
  * @param   InKeySlotNum        : Local envelope key slot number.\n
  *                                Can be one of the following values:\n
  *                                @arg STSAFEA_KEY_SLOT_0: Slot 0 in local envelope key table.\n
  *                                @arg STSAFEA_KEY_SLOT_1: Slot 1 in local envelope key table.
  * @param   pInLocalEnvelope    : Pointer to data bytes array to wrap.
  * @param   InLocalEnvelopeSize : Data size (multiple of 8 bytes between 16 and 488 bytes inclusive).
  * @param   pOutLVResponse      : LV structure pointer to be filled with the working key response data.\n
  *                                If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 0, the LV structure must have been properly allocated.\n
  *                                If STSAFEA_USE_OPTIMIZATION_SHARED_RAM = 1 a pointer inside pStSafeA->InOutBuffer will be assigned.
  * @param   InMAC               : MAC authenticating command/response.
  * @param   InHostEncryption    : Encryption type.
  *                                Can be one of the following values:\n
  *                                @arg STSAFEA_ENCRYPTION_NONE: No encryption needed.\n
  *                                @arg STSAFEA_ENCRYPTION_RESPONSE: Response will be generated encrypted.\n
  *                                @arg STSAFEA_ENCRYPTION_COMMAND: Command is encrypted before sending.\n
  *                                @arg STSAFEA_ENCRYPTION_COMMAND_RESPONSE: Both command and response are encrypted.
  * @retval  STSAFEA_OK if success, an error code otherwise.
  */
StSafeA_ResponseCode_t StSafeA_UnwrapLocalEnvelope(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InKeySlotNum,
  uint8_t *pInLocalEnvelope,
  uint16_t InLocalEnvelopeSize,
  StSafeA_LVBuffer_t *pOutLVResponse,
  uint8_t InMAC,
  uint8_t InHostEncryption);

StSafeA_ResponseCode_t StSafeA_Write(StSafeA_Handle_t* handle, uint8_t *ptr, uint16_t len);
StSafeA_ResponseCode_t StSafeA_ReadZone(StSafeA_Handle_t* handle, uint8_t *output, uint16_t len);
/**
  * @}
  */


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
#endif /* __cplusplus */

#endif /* STSAFEA_CORE_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
