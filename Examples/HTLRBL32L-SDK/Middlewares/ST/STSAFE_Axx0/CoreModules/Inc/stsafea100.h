/**
  ******************************************************************************
  * @file    stsafea100.h
  * @author  SMD/AME application teams
  * @version V3.3.1
  * @brief   STSAFE_A100 device specific include file.
  *          Specifies device specific defines, macros, types.
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
  * Under STMicroelectronics’ intellectual property rights, the redistribution,
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
  *     “Open Source Terms” shall mean any open source license which requires as part of
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

#ifndef STSAFEA100_H
#define STSAFEA100_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stsafea_conf.h"
#include "stsafea_types.h"

/** @addtogroup STSAFE_A100_DEVICE_DEF_MACRO_TYPES
  * @{
  */


/** @addtogroup DEVICE_STSAFE_A100
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup STSAFE_A100_Exported_Defines STSAFE-A100's exported defines
  * @{
  */


/** @defgroup STSAFE_A100_Commands STSAFE-A100's commands
  * @brief STSAFE-A100 Commands
  * @{
  */
#define STSAFEA_CMD_ECHO                      (0x00U)      /*!< Echo: Returns as a response the data that it received as command data. */
#define STSAFEA_CMD_RESET                     (0x01U)      /*!< Reset: Interrupts any on-going session. */
#define STSAFEA_CMD_GENERATE_RANDOM           (0x02U)      /*!< Generate Random: Returns the requested number of random bytes.*/
#define STSAFEA_CMD_START_SESSION             (0x03U)      /*!< Start Session: Starts a signature session. It must be used in combination with the Get Signature command. */
#define STSAFEA_CMD_DECREMENT                 (0x04U)      /*!< Decrement: Decrements the one-way counter in a counter zone. When the counter reaches zero, the command is refused.*/
#define STSAFEA_CMD_READ                      (0x05U)      /*!< Read: Used to read data from a data partition zone. This command can also be used to change the read access conditions of the zone to a more stricter value. */
#define STSAFEA_CMD_UPDATE                    (0x06U)      /*!< Update: Used to update data in a zone. This command can also be used to change the update access conditions of the zone to a more stricter value. */
#define STSAFEA_CMD_DELETE_KEY                (0x0CU)      /*!< Delete: Used to delete keys. Only Delete Password feature is supported through the available APIs. */
#define STSAFEA_CMD_HIBERNATE                 (0x0DU)      /*!< Hibernate: Sets the product in very-low-power consumption mode. The device restart is equivalent to a restart after a reset or Power On Reset. */
#define STSAFEA_CMD_WRAP_LOCAL_ENVELOPE       (0x0EU)      /*!< Wrap Local Envelope: This command is used to wrap data (typically working keys that are entirely managed by the local host) with a local key envelope using an AES key wrap algorithm. */
#define STSAFEA_CMD_UNWRAP_LOCAL_ENVELOPE     (0x0FU)      /*!< Unwrap Local Envelope: This command is used to unwrap a local envelope with a local envelope key. */
#define STSAFEA_CMD_PUT_ATTRIBUTE             (0x10U)      /*!< Put Attribute: Used to put attributes in the STSAFE-A chips like Keys, a password, the host’s public key or I2C parameters. */
#define STSAFEA_CMD_GENERATE_KEY              (0x11U)      /*!< Generate Key: This command is used to generate key pairs (asymmetric cryptography) or local envelope keys (symmetric cryptography). */
#define STSAFEA_CMD_QUERY                     (0x14U)      /*!< Query: Used to check how the chip is configured. */
#define STSAFEA_CMD_GET_SIGNATURE             (0x15U)      /*!< Get Signature: This command generates a digital signature over all commands and responses since the start of the signature session. */
#define STSAFEA_CMD_GENERATE_SIGNATURE        (0x16U)      /*!< Generate Signature: This command generates a digital signature over a message digest generated by the host. It is typically used in the IoT device authentication use case. */
#define STSAFEA_CMD_VERIFY_SIGNATURE          (0x17U)      /*!< Verify Signature: This command serves message authentication and entity authentication purposes. */
#define STSAFEA_CMD_ESTABLISH_KEY             (0x18U)      /*!< Establish Key: This command can be used to establish a shared secret between two hosts by using asymmetric cryptography. */
#define STSAFEA_CMD_VERIFY_PASSWORD           (0x1AU)      /*!< Verify Password: This command performs password verification and remembers the outcome for future authorization of Put Attribute commands. */
/**
  * @}
  */


/** @defgroup STSAFE_A100_Commands_Wait_Time STSAFE-A100's waiting time to get command's response
  * @brief STSAFEA-100 Commands Waiting Time in ms between command and response
  * @{
  */
#define STSAFEA_MS_WAIT_TIME_CMD_ECHO                     (  5U)      /*!< Echo: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_RESET                    ( 30U)      /*!< Reset: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_GENERATE_RANDOM          ( 15U)      /*!< generate Random: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_START_SESSION            ( 25U)      /*!< Start Session: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_DECREMENT                ( 15U)      /*!< Decrement: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_READ                     (  5U)      /*!< Read: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_UPDATE                   ( 10U)      /*!< Update: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_HIBERNATE                ( 50U)      /*!< Hibernate: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_WRAP_LOCAL_ENVELOPE      ( 40U)      /*!< Wrap Local Envelope: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_UNWRAP_LOCAL_ENVELOPE    ( 45U)      /*!< Unwrap Local Envelope: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_PUT_ATTRIBUTE            ( 15U)      /*!< Put Attribute: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_GENERATE_KEY             (110U)      /*!< Generate Key: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_DELETE_KEY               ( 15U)      /*!< Delete Key: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_QUERY                    (  5U)      /*!< Query: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_GET_SIGNATURE            (100U)      /*!< Get Signature: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_GENERATE_SIGNATURE       ( 80U)      /*!< Generate Signature: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_VERIFY_MSG_SIGNATURE     (150U)      /*!< Verify Message Signature: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_VERIFY_ENTITY_SIGNATURE  (150U)      /*!< Verify Entity Signature: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_ESTABLISH_KEY            (170U)      /*!< Establish Key: Minimum delay in ms before response. */
#define STSAFEA_MS_WAIT_TIME_CMD_VERIFY_PASSWORD          ( 15U)      /*!< Verify Password: Minimum delay in ms before response. */
/**
  * @}
  */


/** @defgroup STSAFE_A100_Commands_Tag STSAFE-A100's command tags
  * @brief STSAFEA-100 Commands Tag
  * @{
  */
#define STSAFEA_TAG_ADMIN_BASE_KEY_SLOT                 (0x01U)      /*!< Admin base key slot tag. */
#define STSAFEA_TAG_LOCAL_ENVELOPE_KEY_TABLE            (0x07U)      /*!< Local envelope key table tag . */
#define STSAFEA_TAG_LIFE_CYCLE_STATE                    (0x08U)      /*!< Life cycle state tag. */
#define STSAFEA_TAG_PASSWORD_SLOT                       (0x09U)      /*!< Password slot tag. */
#define STSAFEA_TAG_I2C_PARAMETER                       (0x0AU)      /*!< I2C parameters tag. */
#define STSAFEA_TAG_PUBLIC_KEY_SLOT                     (0x0BU)      /*!< Public key slot tag. */
#define STSAFEA_TAG_PRODUCT_DATA                        (0x11U)      /*!< Product data tag. */
#define STSAFEA_TAG_DATA_PARTITION_CONFIGURATION        (0x12U)      /*!< Data partition configuration tag. */
#define STSAFEA_TAG_PRIVATE_KEY_SLOT                    (0x13U)      /*!< Private key slot tag. */
#define STSAFEA_TAG_PRIVATE_KEY_TABLE                   (0x14U)      /*!< Private key table tag. */
#define STSAFEA_TAG_HOST_KEY_SLOT                       (0x17U)      /*!< Host key slot tag. */
/**
  * @}
  */


/** @defgroup STSAFE_A100_Key_Slot_Number STSAFE-A100's slot number
  * @{
  */
#define STSAFEA_KEY_SLOT_0                     (0x00U) /*!< Key Slot number 0 */
#define STSAFEA_KEY_SLOT_1                     (0x01U) /*!< Key Slot number 1 */
/**
  * @}
  */


/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup STSAFE_A100_Exported_Types STSAFE-A100's exported types
  * @{
  */
/*!
 * \enum StSafeA_RndSubject_t
 * \brief Random subject enumeration
 * \details Specifies if the random number must or mustn't be used in the entity authentication protocol
 */
typedef enum
{
  STSAFEA_EPHEMERAL_RND             = 0x0U,
  STSAFEA_ENTITY_AUTHENTICATION_RND = 0x1U
} StSafeA_RndSubject_t;

/*!
 * \struct StSafeA_ProductDataBuffer_t
 * \brief Product data structure type definition
 * \details Response format of the product data query.
 */
typedef struct
{
  uint16_t Length;                                                              /*!< The whole length in number of octet */
  uint8_t  MaskIdentificationTag;                                               /*!< The tag for the Mask Identification (0x01) */
  uint8_t  MaskIdentificationLength;                                            /*!< The length in number of octet for the Mask Identification */
  uint8_t  MaskIdentification[STSAFEA_MASK_ID];                                 /*!< The data for the Mask Identification */
  uint8_t  STNumberTag;                                                         /*!< The tag for the ST Number (0x02) */
  uint8_t  STNumberLength;                                                      /*!< The length in number of octet for the ST Number */
  uint8_t  STNumber[STSAFEA_ST_NUMBER_LENGTH];                                  /*!< The data for the ST Number */
  uint8_t  InputOutputBufferSizeTag;                                            /*!< The tag for the InputOutputBuffer Size (0x03) */
  uint8_t  InputOutputBufferSizeLength;                                         /*!< The length in number of octet for the InputOutputBuffer Size */
  uint16_t InputOutputBufferSize;                                               /*!< The data for the InputOutputBuffer Size */
  uint8_t  AtomicityBufferSizeTag;                                              /*!< The tag for the Atomicity Buffer Size (0x04) */
  uint8_t  AtomicityBufferSizeLength;                                           /*!< The length in number of octet for the Atomicity Buffer Size */
  uint16_t AtomicityBufferSize;                                                 /*!< The data for the Atomicity Buffer Size */
  uint8_t  NonVolatileMemorySizeTag;                                            /*!< The tag for the Non Volatile Memory Size (0x05) */
  uint8_t  NonVolatileMemorySizeLength;                                         /*!< The length in number of octet for the Non Volatile Memory Size */
  uint16_t NonVolatileMemorySize;                                               /*!< The data for the Non Volatile Memory Size */
  uint8_t  TestDateTag;                                                         /*!< The tag for the Test Date (0x06) */
  uint8_t  TestDateLength;                                                      /*!< The length in number of octet for the Test Date */
  uint16_t TestDateSize;                                                        /*!< The data for the Test Date Size */
  uint8_t  InternalProductVersionTag;                                           /*!< The tag for the Internal Product Version (0x07) */
  uint8_t  InternalProductVersionLength;                                        /*!< The length in number of octet for the Internal Product Version */
  uint8_t  InternalProductVersionSize;                                          /*!< The data for the Internal Product Version */
  uint8_t  ModuleDateTag;                                                       /*!< The tag for the Module Date (0x08) */
  uint8_t  ModuleDateLength;                                                    /*!< The length in number of octet for the Module Date */
  uint16_t ModuleDateSize;                                                      /*!< The data for the Module Date */
}StSafeA_ProductDataBuffer_t;
/**
  * @}
  */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup STSAFE_A100_Exported_Macros STSAFE-A100's exported macros
  * @{
  */
/******************************** IS STSAFE TAG *******************************/
#define IS_STSAFEA_TAG(TAG) (((TAG) == STSAFEA_TAG_ADMIN_BASE_KEY_SLOT)                 || \
                             ((TAG) == STSAFEA_TAG_SERVICE_BASE_KEY_SLOT)               || \
                             ((TAG) == STSAFEA_TAG_LOCAL_ENVELOPE_KEY_TABLE)            || \
                             ((TAG) == STSAFEA_TAG_LIFE_CYCLE_STATE)                    || \
                             ((TAG) == STSAFEA_TAG_PASSWORD_SLOT)                       || \
                             ((TAG) == STSAFEA_TAG_I2C_PARAMETER)                       || \
                             ((TAG) == STSAFEA_TAG_PUBLIC_KEY_SLOT)                     || \
                             ((TAG) == STSAFEA_TAG_LTC_PARAM)                           || \
                             ((TAG) == STSAFEA_TAG_PRODUCT_DATA)                        || \
                             ((TAG) == STSAFEA_TAG_DATA_PARTITION_CONFIGURATION)        || \
                             ((TAG) == STSAFEA_TAG_PRIVATE_KEY_SLOT)                    || \
                             ((TAG) == STSAFEA_TAG_PRIVATE_KEY_TABLE)                   || \
                             ((TAG) == STSAFEA_TAG_HOST_KEY_SLOT))

/******************************* STSAFE KEY SLOTS *****************************/
#define IS_STSAFEA_KEY_SLOT(SLOT_NUM) (((SLOT_NUM) == STSAFEA_KEY_SLOT_0) || \
                                       ((SLOT_NUM) == STSAFEA_KEY_SLOT_1))
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup STSAFE_A100_CORE_Exported_Functions
  * @{
  */
/** @addgroup STSAFE_A100_CORE_Exported_Functions_Group1 Signature Session Commands APIs
  *  @brief    STSAFE-A100 APIs related to signature session commands
  *
@verbatim
 ===============================================================================
              ##### Signature Session Commands  #####
 ===============================================================================
[..]
    (+) Start Signature Session
    (+) Get Signature
@endverbatim
  * @{
  */
StSafeA_ResponseCode_t StSafeA_StartSignatureSession(
  StSafeA_Handle_t *pStSafeA,
  uint8_t InKeySlotNum,
  uint8_t InMAC);

StSafeA_ResponseCode_t StSafeA_GetSignature(
  StSafeA_Handle_t *pStSafeA,
  const uint8_t *pInChallenge,
  uint16_t InChallengeSize,
  uint16_t InSignRSLen,
  StSafeA_LVBuffer_t *pOutSignR,
  StSafeA_LVBuffer_t *pOutSignS,
  uint8_t InMAC);
/**
  * @}
  */


/** @addtogroup STSAFE_A100_CORE_Exported_Functions_Group2 Entity Authentication Commands APIs
  *  @brief    STSAFE-A APIs related to entity authentication commands
  *
@verbatim
 ===============================================================================
              ##### Entity authentication Commands  #####
 ===============================================================================
[..]
    (+) Public Key Slot Query
    (+) Put Public Key Slot
    (+) Verify Entity Signature
@endverbatim
  * @{
  */
StSafeA_ResponseCode_t StSafeA_PublicKeySlotQuery(
  StSafeA_Handle_t *pStSafeA,
  StSafeA_PublicKeySlotBuffer_t *pOutPubKeySlot,
  uint16_t InPubXYLen,
  uint16_t InCurveIdLen,
  StSafeA_LVBuffer_t *pOutPubX,
  StSafeA_LVBuffer_t *pOutPubY,
  StSafeA_LVBuffer_t *pOutCurveId,
  uint8_t InMAC);

StSafeA_ResponseCode_t StSafeA_PutPublicKeySlot(
  StSafeA_Handle_t *pStSafeA,
  const StSafeA_CurveId_t InCurveId,
  const StSafeA_LVBuffer_t *pInPubX,
  const StSafeA_LVBuffer_t *pInPubY,
  uint8_t InMAC);

StSafeA_ResponseCode_t StSafeA_VerifyEntitySignature(
  StSafeA_Handle_t *pStSafeA,
  const StSafeA_LVBuffer_t *pInRSignature,
  const StSafeA_LVBuffer_t *pInSSignature,
  StSafeA_VerifySignatureBuffer_t *pOutRespVerifySignature,
  uint8_t InMAC);
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

#endif /* STSAFEA100_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
