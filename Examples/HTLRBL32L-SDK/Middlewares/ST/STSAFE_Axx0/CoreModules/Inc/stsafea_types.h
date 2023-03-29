/**
  ******************************************************************************
  * @file    stsafea_types.h
  * @author  SMD/AME application teams
  * @version V3.3.2
  * @brief   Specifies defines, macros, types common to all the STSAFE-A devices
  *          supported by this Middleware library. The file is not device specific.
  *
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
#ifndef STSAFEA_TYPES_H
#define STSAFEA_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

/** MISRA C:2012 deviation rule has been granted for following rules:
  * - Rule-18.7 - Medium: Array field does not have a size.
  */


/** @addtogroup STSAFE_A1XX_DEVICE_DEF_MACRO_TYPES
  * @{
  */


/** @addtogroup DEVICE_STSAFE_A1xx
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup STSAFE_A1xx_Exported_Defines STSAFE-A1xx's exported defines
  * @{
  */


/** @defgroup STSAFEA_Data_Length STSAFE-A1xx's lengths definition
  * @{
  */
#define STSAFEA_HEADER_LENGTH                      0x01U    /*!< Header length */
#define STSAFEA_LENGTH_SIZE                        0x02U    /*!< Length size */
#define STSAFEA_CRC_LENGTH                         0x02U    /*!< CRC length */
#define STSAFEA_MAC_LENGTH                         0x04U    /*!< MAC length */
#define STSAFEA_HASH_LENGTH                        0x04U    /*!< HASH length */
#define STSAFEA_ST_NUMBER_LENGTH                   0x09U    /*!< ST number lenght */
/**
  * @}
  */


/** @defgroup STSAFEA_Buffer_size STSAFE-A1xx's size definition
  * @{
  */
#define STSAFEA_BUFFER_DATA_PACKET_SIZE        507U /*!< 507: Maximum buffer length that can be handled by the device */
#define STSAFEA_BUFFER_DATA_CONTENT_SIZE       (STSAFEA_BUFFER_DATA_PACKET_SIZE - \
                                                STSAFEA_HEADER_LENGTH -           \
                                                STSAFEA_CRC_LENGTH) /*!< Data size in bytes */
#define STSAFEA_BUFFER_DATA_EXTENSION_SIZE     16U /*!< Additional 16 bytes = 2 Bytes CRC + 10 extra bytes used during  RMAC calculation + 4 spare bytes
                                                        used for optimization by the Low Level layer to move bytes inside the same buffer */
#define STSAFEA_BUFFER_MAX_SIZE                (STSAFEA_BUFFER_DATA_PACKET_SIZE + STSAFEA_BUFFER_DATA_EXTENSION_SIZE) /*!< Max extended buffer size in bytes */
#define STSAFEA_ATOMICITY_BUFFER_SIZE          64U /*!< Atomicity buffer size in bytes */
/**
  * @}
  */


/** @defgroup STSAFEA_MAC_Options Bits definition for MAC through command header
  * @{
  */
/******************  Bits definition for command header  *******************/
#define STSAFEA_CMD_HEADER_CMAC_POS             (7U)                                            /*!< C-MAC presence code, if '1' indicates the presence of a C-MAC */
#define STSAFEA_CMD_HEADER_CMAC_MSK             (0x1U << STSAFEA_CMD_HEADER_CMAC_POS)           /*!< 0b10000000  */
#define STSAFEA_CMD_HEADER_CMACEN               STSAFEA_CMD_HEADER_CMAC_MSK                     /*!< C-MAC presence enabled */
#define STSAFEA_CMD_HEADER_RMAC_POS             (6U)                                            /*!< R-MAC request code, if '1' indicates wheter an R-MAC is requested */
#define STSAFEA_CMD_HEADER_RMAC_MSK             (0x1U << STSAFEA_CMD_HEADER_RMAC_POS)           /*!< 0b01000000 */
#define STSAFEA_CMD_HEADER_RMACEN               STSAFEA_CMD_HEADER_RMAC_MSK                      /*!< R-MAC request enabled */
#define STSAFEA_CMD_HEADER_SCHN_POS             (5U)                                            /*!< Secure Channel Type, if '1' indicates C/R-MAC are HOST, if '0' indicates C/R-MAC are defined by current session */
#define STSAFEA_CMD_HEADER_SCHN_MSK             (0x1U << STSAFEA_CMD_HEADER_SCHN_POS)           /*!< 0b00100000 */
#define STSAFEA_CMD_HEADER_SCHN_HOSTEN          (STSAFEA_CMD_HEADER_SCHN_MSK)                   /*!< Secure Channel HOST enabled */
#define STSAFEA_CMD_HEADER_MAC_MSK              (STSAFEA_CMD_HEADER_CMAC_MSK | STSAFEA_CMD_HEADER_RMAC_MSK | STSAFEA_CMD_HEADER_SCHN_MSK)  /*!< MAC bits mask */

#define  STSAFEA_MAC_NONE        (0x0U)                                                                                         /*!< No MAC */
#define  STSAFEA_MAC_CMAC        (STSAFEA_CMD_HEADER_CMACEN)                                                                    /*!< Regular Command MAC  */
#define  STSAFEA_MAC_RMAC        (STSAFEA_CMD_HEADER_RMACEN)                                                                    /*!< Regular Response MAC */
#define  STSAFEA_MAC_CRMAC       (STSAFEA_CMD_HEADER_CMACEN | STSAFEA_CMD_HEADER_RMACEN)                                        /*!< Regular Command & Response MAC */
#define  STSAFEA_MAC_HOST_CMAC   (STSAFEA_CMD_HEADER_CMACEN | STSAFEA_CMD_HEADER_SCHN_HOSTEN)                                   /*!< Host Command MAC */
#define  STSAFEA_MAC_HOST_RMAC   (STSAFEA_CMD_HEADER_RMACEN | STSAFEA_CMD_HEADER_SCHN_HOSTEN )                                  /*!< Host Response MAC */
#define  STSAFEA_MAC_HOST_CRMAC  (STSAFEA_CMD_HEADER_CMACEN | STSAFEA_CMD_HEADER_RMACEN | STSAFEA_CMD_HEADER_SCHN_HOSTEN )      /*!< Host Command & Response MAC */
/**
  * @}
  */


/** @defgroup STSAFEA_Key_Usage_Authentication_Flag Bits definition for Private key mode of operation
  * @{
  */
/******************  Bits definition for Private key mode of operation  *******************/
#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_CMD_RESP_SIGN_POS    (3U)                                                         /*!< Signature generation over command and response sequences */
#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_CMD_RESP_SIGN_MSK    (0x1U << STSAFEA_PRVKEY_MODOPER_AUTHFLAG_CMD_RESP_SIGN_POS)   /*!< 0b1000*/
#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_CMD_RESP_SIGNEN      STSAFEA_PRVKEY_MODOPER_AUTHFLAG_CMD_RESP_SIGN_MSK             /*!< Signature generation over command and response sequences enabled */

#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_MSG_DGST_SIGN_POS    (2U)                                                         /*!< Signature generation over message digest generated by the host */
#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_MSG_DGST_SIGN_MSK    (0x1U << STSAFEA_PRVKEY_MODOPER_AUTHFLAG_MSG_DGST_SIGN_POS)   /*!< 0b0100*/
#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_MSG_DGST_SIGNEN      STSAFEA_PRVKEY_MODOPER_AUTHFLAG_MSG_DGST_SIGN_MSK             /*!< Signature generation over message digest generated by the host enabled */

#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_KEY_ESTABLISH_POS    (0U)                                                         /*!< Key Establishment */
#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_KEY_ESTABLISH_MSK    (0x1U << STSAFEA_PRVKEY_MODOPER_AUTHFLAG_KEY_ESTABLISH_POS)   /*!< 0b0001*/
#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_KEY_ESTABLISHEN      STSAFEA_PRVKEY_MODOPER_AUTHFLAG_KEY_ESTABLISH_MSK             /*!< Key Establishment enabled */

#define STSAFEA_PRVKEY_MODOPER_AUTHFLAG_MAC_MSK              (STSAFEA_PRVKEY_MODOPER_AUTHFLAG_CMD_RESP_SIGN_MSK | STSAFEA_PRVKEY_MODOPER_AUTHFLAG_MSG_DGST_SIGN_MSK | STSAFEA_PRVKEY_MODOPER_AUTHFLAG_KEY_ESTABLISH_MSK)  /*!< bits mask */
/**
  * @}
  */


/** @defgroup STSAFEA_Flag Boolean flag
  * @{
  */
#define STSAFEA_FLAG_FALSE                     (0x0U)   /*!< Specified flag is off / false / 0b */
#define STSAFEA_FLAG_TRUE                      (0x1U)   /*!< Specified flag is on  / true  / 1b */
/**
  * @}
  */


/** @defgroup STSAFEA_AES_Key_Types Key types
  * @{
  */
#define STSAFEA_KEY_TYPE_AES_128               (0x00U) /*!< AES 128-bits key type */
#define STSAFEA_KEY_TYPE_AES_256               (0x01U) /*!< AES 256-bits key type */
/**
  * @}
  */


/** @defgroup STSAFEA_AES_Key_sIZE Key SIZE
  * @{
  */
#define STSAFEA_KEY_SIZE_AES_128               16U /*!< AES 128-bits key size */
#define STSAFEA_KEY_SIZE_AES_256               32U /*!< AES 256-bits key size */
/**
  * @}
  */


/** @defgroup STSAFEA_Access_Conditions Access conditions
  * @{
  */
#define STSAFEA_AC_ALWAYS                     (0x00U)                                         /*!< Access condition: Always */
#define STSAFEA_AC_HOST                       (0x01U)                                         /*!< Access condition: Host. MAC or Auth AC must be fulfilled or the command must have a valid host C-MAC */
#define STSAFEA_AC_AUTH                       (0x02U)                                         /*!< Access condition: Auth. A valid Admin C-MAC must have been received on the command or on some previous command. */
#define STSAFEA_AC_MAC                        (0x03U)                                         /*!< Access condition: MAC. Command must have a valid Admin C-MAC. */
#define STSAFEA_AC_NEVER                      ( (0x04U) | (0x05U) | (0x06U) | (0x07U) )       /*!< Access condition: Never, other values */
#define STSAFEA_AC_MSK                        (0x3U)                                          /*!< 0x00000111 */
/**
  * @}
  */


/** @defgroup STSAFEA_Command_Access_Conditions Commands access condition
    @note STSAFE-A related
  * @{
  */
#define STSAFEA_CMD_AC_NOT_AUTHORIZED          (0x00U)      /*!< Not authorized command access condition */
#define STSAFEA_CMD_AC_FREE                    (0x01U)      /*!< Free command access condition */
#define STSAFEA_CMD_AC_ADMIN_CMAC              (0x02U)      /*!< Admin MAC command access condition */
#define STSAFEA_CMD_AC_HOST_CMAC               (0x03U)      /*!< Host MAC command access condition */
#define STSAFEA_CMD_AC_ADMIN_CMAC_OR_PASSWORD  (0x04U)      /*!< Admin MAC or Password command access condition */
#define STSAFEA_CMD_AC_ADMIN_CMAC_OR_HOST_CMAC (0x05U)      /*!< Admin or Host MAC command access condition */
/**
  * @}
  */


/** @defgroup STSAFEA_Host_Encryption_Flag Host encryption flags
  * @{
  */
#define STSAFEA_ENCRYPTION_NONE                    (0x00U)   /*!< No encryption */
#define STSAFEA_ENCRYPTION_RESPONSE                (0x01U)   /*!< Response encryption only */
#define STSAFEA_ENCRYPTION_COMMAND                 (0x02U)   /*!< Command encryption only */
#define STSAFEA_ENCRYPTION_COMMAND_RESPONSE        (STSAFEA_ENCRYPTION_COMMAND | STSAFEA_ENCRYPTION_RESPONSE) /*!< Both Command / Response encryption */
/**
  * @}
  */


/** @defgroup STSAFEA_Host_Encryption_Access_Condition Host encryption access conditions
  * @{
  */
#define STSAFEA_ENCRYPTION_AC_ALWAYS                    (0x00U)
#define STSAFEA_ENCRYPTION_AC_ONCE                      (0x01U)
#define STSAFEA_ENCRYPTION_AC_NEVER                     (0x04U)
/**
  * @}
  */


/** @defgroup STSAFEA_Command_Change_Right Command's change rights
  * @{
  */
#define STSAFEA_CHANGE_RIGHT_NONE                                 (0x00U)
#define STSAFEA_CHANGE_RIGHT_HOST_ENCRYPTION                      (0x01U)
#define STSAFEA_CHANGE_RIGHT_ACCESS_CONDITION                     (0x02U)
#define STSAFEA_CHANGE_RIGHT_HOST_ENCRYPTION_AND_ACCESS_CONDITION (STSAFEA_CHANGE_RIGHT_HOST_ENCRYPTION \
                                                                   | STSAFEA_CHANGE_RIGHT_ACCESS_CONDITION)
/**
  * @}
  */


/** @defgroup STSAFEA_Wakeup_Modes Wakeup modes
  * @{
  */
#define STSAFEA_WAKEUP_FROM_I2C_START_OR_RESET          (( uint8_t ) 0x01 )
#define STSAFEA_WAKEUP_FROM_RESET                       (( uint8_t ) 0x02 )
/**
  * @}
  */


/** @defgroup STSAFEA_Lifecycle_State Life cycle state
  * @{
  */
#define STSTAFEA_LIFECYCLE_STATE_BORN                     (( uint8_t ) 0x01 )
#define STSTAFEA_LIFECYCLE_STATE_OPERATIONAL              (( uint8_t ) 0x03 )
#define STSTAFEA_LIFECYCLE_STATE_TERMINATED               (( uint8_t ) 0x04 )
#define STSTAFEA_LIFECYCLE_STATE_BORN_AND_LOCKED          (( uint8_t ) 0x81 )
#define STSTAFEA_LIFECYCLE_STATE_OPERATIONAL_AND_LOCKED   (( uint8_t ) 0x83 )
/**
  * @}
  */


/** @defgroup STSAFEA_Sessions Session types
  * @{
  */
#define STSAFEA_SESSION_ENVELOPE        (( uint8_t ) 0x03 )
#define STSAFEA_SESSION_SIGNATURE       (( uint8_t ) 0x08 )
/**
  * @}
  */


/** @defgroup STSAFEA_Key_Sha_Sign_Length Crypto length
  * @{
  */
#define STSAFEA_SHA_256_LENGTH                                          32U                                   /*ECDSA_SHA256 Hash Len */
#define STSAFEA_XYRS_ECDSA_SHA256_LENGTH                                STSAFEA_SHA_256_LENGTH                /*ECDSA_SHA256 R,S, X,and Y Len */
#define STSAFEA_SIGN_ECDSA_SHA256_LENGTH                                (2*STSAFEA_XYRS_ECDSA_SHA256_LENGTH)  /*ECDSA_SHA256 Signature Len */
#define STSAFEA_SHA_384_LENGTH                                          48U                                   /*ECDSA_SHA384 Hash Len */
#define STSAFEA_XYRS_ECDSA_SHA384_LENGTH                                STSAFEA_SHA_384_LENGTH                /*ECDSA_SHA384 R,S, X,and Y Len */
#define STSAFEA_SIGN_ECDSA_SHA384_LENGTH                                (2*STSAFEA_XYRS_ECDSA_SHA384_LENGTH)  /*ECDSA_SHA384 Signature Len */
/**
  * @}
  */


/** @defgroup STSAFEA_ECC_Curve_OID ECC curve informations
  * @{
  */
#define STSAFEA_ECC_CURVE_OID_NIST_P_256              ((int8_t*) "\x2A\x86\x48\xCE\x3D\x03\x01\x07")               /*!< ASN.1 X9.62 Curve Object Identifier : NIST-P256 OID */
#define STSAFEA_ECC_CURVE_OID_NIST_P_256_LEN          0x08U                                                        /*!< Length of ASN.1 X9.62 Curve Object Identifier: NIST-P256 OID */
#define STSAFEA_ECC_CURVE_OID_NIST_P_256_DER          ((int8_t*) "\x06\x08\x2A\x86\x48\xCE\x3D\x03\x01\x07")       /*!< DER encoded ASN.1 X9.62 Curve Object Identifier: 0x06 |Len| NIST-P256 OID */
#define STSAFEA_ECC_CURVE_OID_NIST_P_256_DER_LEN      ( 2U + STSAFEA_ECC_CURVE_OID_NIST_P_256_LEN )                /*!< Length of DER encoded ASN.1 X9.62 Curve Object Identifier: 0x06 |Len| NIST-P256 OID */

#define STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256         ((int8_t*) "\x2B\x24\x03\x03\x02\x08\x01\x01\x07")           /*!< ASN.1 X9.62 Curve Object Identifier : BRAINPOOL-P256 OID */
#define STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256_LEN     0x09U                                                        /*!< Length of ASN.1 X9.62 Curve Object Identifier: BRAINPOOL-P256 OID */
#define STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256_DER     ((int8_t*) "\x06\x09\x2B\x24\x03\x03\x02\x08\x01\x01\x07")   /*!< DER encoded ASN.1 X9.62 Curve Object Identifier: 0x06 |Len| BRAINPOOL-P256 OID */
#define STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256_DER_LEN ( 2U + STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256_LEN )           /*!< Length of DER encoded ASN.1 X9.62 Curve Object Identifier: 0x06 |Len| BRAINPOOL-P256 OID */

#define STSAFEA_ECC_CURVE_OID_NIST_P_384              ((int8_t*) "\x2B\x81\x04\x00\x22")                           /*!< ASN.1 X9.62 Curve Object Identifier : NIST-P384 OID */
#define STSAFEA_ECC_CURVE_OID_NIST_P_384_LEN          0x05U                                                        /*!< Length of ASN.1 X9.62 Curve Object Identifier: NIST-P384 OID */
#define STSAFEA_ECC_CURVE_OID_NIST_P_384_DER          ((int8_t*) "\x06\x05\x2B\x81\x04\x00\x22")                   /*!< DER encoded ASN.1 X9.62 Curve Object Identifier: 0x06 |Len| NIST-P384 OID */
#define STSAFEA_ECC_CURVE_OID_NIST_P_384_DER_LEN      ( 2U + STSAFEA_ECC_CURVE_OID_NIST_P_384_LEN )                /*!< Length of DER encoded ASN.1 X9.62 Curve Object Identifier: 0x06 |Len| NIST-P384 OID */

#define STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384         ((int8_t*) "\x2B\x24\x03\x03\x02\x08\x01\x01\x0B")           /*!< ASN.1 X9.62 Curve Object Identifier : BRAINPOOL-P384 OID */
#define STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384_LEN     0x09U                                                        /*!< Length of ASN.1 X9.62 Curve Object Identifier: BRAINPOOL-P384 OID */
#define STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384_DER     ((int8_t*) "\x06\x09\x2B\x24\x03\x03\x02\x08\x01\x01\x0B")   /*!< DER encoded ASN.1 X9.62 Curve Object Identifier: 0x06 |Len| BRAINPOOL-P384 OID */
#define STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384_DER_LEN ( 2U + STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384_LEN )           /*!< Length of DER encoded ASN.1 X9.62 Curve Object Identifier: 0x06 |Len| BRAINPOOL-P384 OID */

#define STSAFEA_ECC_CURVE_OID_NULL                    ((int8_t*) "\x00")                                           /*!< Null value */

#define STSAFEA_ECC_CURVE_OID_LEN                     0x02U                                                        /*!< Length of LEN field */
/**
  * @}
  */


/** @defgroup STSAFEA_Miscellaneous Miscellaneous
  * @{
  */
#define STSAFEA_MASK_ID                      0x03U   /*!< Mask Id */
#define STSAFEA_POINT_REPRESENTATION_ID      0x04U   /*!< Point of representation ID */
#define STSAFEA_POINT_REPRESENTATION_ID_LEN  0x01U   /*!< Point of representation ID's length */
/**
  * @}
  */


/**
  * @}
  */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup STSAFE_A1xx_Exported_Macros  STSAFE-A1xx's exported macros
  * @{
  */
#define STSAFEA_AES_KEY_BITSIZE(x)          128U*((x)+1U)  /*!< Aes key size in number of bits */
#define STSAFEA_R_MAC_LENGTH(mac)           ((uint16_t)((( ( mac ) \
                                                           & STSAFEA_CMD_HEADER_RMACEN) == STSAFEA_CMD_HEADER_RMACEN) ? STSAFEA_MAC_LENGTH : 0x00U))
#define STSAFEA_GET_HASH_SIZE(x)            (16U*((x)+2U))      /*!< Hash size */
#define STSAFEA_UNUSED_VAR(X)               (void)X             /* To prevent gcc/g++ warnings for unused param */
#define STSAFEA_UNUSED_PTR(X)               *(&(X)) = *(&(X))   /* To prevent gcc/g++ warnings for unused param and MISRA-C2012-Rule-8.13 violation with unused pointer params */
#define STSAFEA_UNMODIFIED_PTR(X)           *(&(X)) = *(&(X))   /* To prevent gcc/g++ warnings for not-const and not-modified unused param */
#define STSAFEA_MIN(a,b)                    (((a)<(b))?(a):(b)) /* To give the minimum */

#define STSAFEA_HOST_KEY_LENGTH             STSAFEA_KEY_SIZE_AES_128    /*!< Host mac key length */

/******************************* STSAFE FLAG **********************************/
#define IS_STSAFEA_FLAG(FLAG) (((FLAG) == STSAFEA_FLAG_TRUE) || ((FLAG) == STSAFEA_FLAG_FALSE))

/******************************* STSAFE KEY TYPES *****************************/
#define IS_STSAFEA_KEY_TYPE(KEY_TYPE) (((KEY_TYPE) == STSAFEA_KEY_TYPE_AES_128)|| \
                                       ((KEY_TYPE) == STSAFEA_KEY_TYPE_AES_256))

/******************************* STSAFE MAC MODES *****************************/
#define IS_STSAFEA_MAC(MAC) (((MAC) == STSAFEA_MAC_NONE)        || \
                             ((MAC) == STSAFEA_MAC_ADMIN_CMAC)  || \
                             ((MAC) == STSAFEA_MAC_ADMIN_RMAC)  || \
                             ((MAC) == STSAFEA_MAC_ADMIN_CRMAC) || \
                             ((MAC) == STSAFEA_MAC_HOST_CMAC)   || \
                             ((MAC) == STSAFEA_MAC_HOST_RMAC)   || \
                             ((MAC) == STSAFEA_MAC_HOST_CRMAC))

/********************* STSAFE HOST ENCRYPTION MODES ***************************/
#define IS_STSAFEA_ENCRYPT(ENCRYPT) (((ENCRYPT) == STSAFEA_ENCRYPTION_NONE)     || \
                                     ((ENCRYPT) == STSAFEA_ENCRYPTION_RESPONSE) || \
                                     ((ENCRYPT) == STSAFEA_ENCRYPTION_COMMAND)  || \
                                     ((ENCRYPT) == STSAFEA_ENCRYPTION_COMMAND_RESPONSE))

/****************** STSAFE HOST ENCRYPTION ACCESS CONDITIONS ******************/
#define IS_STSAFEA_ENCRYPT_AC(ENCRYPT_AC) (((ENCRYPT_AC) == STSAFEA_ENCRYPTION_AC_ALWAYS)  || \
                                           ((ENCRYPT_AC) == STSAFEA_ENCRYPTION_AC_ONCE)    || \
                                           ((ENCRYPT_AC) == STSAFEA_ENCRYPTION_AC_NEVER))

/************************* STSAFE ACCESS CONDITIONS ***************************/
#define IS_STSAFEA_AC(AC) (((AC) == STSAFEA_AC_ALWAYS) || \
                           ((AC) == STSAFEA_AC_HOST)   || \
                           ((AC) == STSAFEA_AC_AUTH)   || \
                           ((AC) == STSAFEA_AC_MAC)    || \
                           ((AC) == STSAFEA_AC_NEVER))

/************************* STSAFE CMD CHANGE RIGHT ****************************/
#define IS_STSAFEA_CHANGE_RIGHT(CR) (((CR) == STSAFEA_CHANGE_RIGHT_NONE)             || \
                                     ((CR) == STSAFEA_CHANGE_RIGHT_HOST_ENCRYPTION)  || \
                                     ((CR) == STSAFEA_CHANGE_RIGHT_ACCESS_CONDITION) || \
                                     ((CR) == STSAFEA_CHANGE_RIGHT_HOST_ENCRYPTION_AND_ACCESS_CONDITION))

/***************************** STSAFE SESSION ********************************/
#define IS_STSAFEA_SESSION(SESSION)      (((SESSION) == STSAFEA_SESSION_ENVELOPE)    || \
                                          ((SESSION) == STSAFEA_SESSION_SIGNATURE))

/************************* STSAFE WAKEUP MODES ********************************/
#define IS_STSAFEA_WAKEUP_MODE(MODE)     (((MODE) == STSAFEA_WAKEUP_FROM_I2C_START_OR_RESET) || \
                                          ((MODE) == STSAFEA_WAKEUP_FROM_RESET))

/************************* STSAFE LIFECYCLE STATES ****************************/
#define IS_STSAFEA_LIFECYCLE_STATE(STATE)(((STATE) == STSTAFEA_LIFECYCLE_STATE_BORN)                || \
                                          ((STATE) == STSTAFEA_LIFECYCLE_STATE_OPERATIONAL)         || \
                                          ((STATE) == STSTAFEA_LIFECYCLE_STATE_TERMINATED)          || \
                                          ((STATE) == STSTAFEA_LIFECYCLE_STATE_BORN_AND_LOCKED)     || \
                                          ((STATE) == STSTAFEA_LIFECYCLE_STATE_OPERATIONAL_AND_LOCKED))

/******************************* STSAFE HANDLER *******************************/
#define IS_STSAFEA_HANDLER_VALID_PTR(HANDLER) (((HANDLER) != NULL) && ((HANDLER)->InOutBuffer.LV.Data != NULL))

/******************************* STSAFE LV BUFFER *******************************/
#define IS_STSAFEA_LVBUFFER_VALID_PTR(LVBUFFER) (((LVBUFFER) != NULL) && ((LVBUFFER)->Data != NULL))

/*************************** POINTER CHECK UNDER SHARED RAM OPTIM CONDITION *******************************/
#if (STSAFEA_USE_OPTIMIZATION_SHARED_RAM)
#define IS_STSAFEA_CONDITIONAL_VALID_PTR(PTR) (0x1U != 0x0U)
#define IS_STSAFEA_CONDITIONAL_LVBUFFER_VALID_PTR(PTR) (0x1U != 0x0U)
#else
#define IS_STSAFEA_CONDITIONAL_VALID_PTR(PTR) ((PTR) != NULL)
#define IS_STSAFEA_CONDITIONAL_LVBUFFER_VALID_PTR(PTR) IS_STSAFEA_LVBUFFER_VALID_PTR(PTR)
#endif

/*************************** STSAFE DATA LEN *******************************/
#define IS_STSAFEA_LEN(LEN) (((LEN)>0U))
/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup STSAFE_A1xx_Exported_Types  STSAFE-A1xx's exported types
  * @{
  */

/*!
 * \enum StSafeA_Bool_t
 * \brief boolean enumeration
 * \details True or False.
 */
typedef enum
{
  STSAFEA_FALSE = 0x0U,
  STSAFEA_TRUE  = !STSAFEA_FALSE
} StSafeA_Bool_t;

/*!
 * \enum StSafeA_HashTypes_t
 * \brief Hash types enumeration
 * \details Specifies the type of the hash.
 */
typedef enum
{
  STSAFEA_SHA_256 = 0x0U,
  STSAFEA_SHA_384 = 0x1U
} StSafeA_HashTypes_t;

/*!
 * \enum StSafeA_MacShaProcess_t
 * \brief MAC and SHA process enumeration
 * \details Specifies Pre-Process before Cmd Transmit or Post-Process after Resp Receive
 */
typedef enum
{
  STSAFEA_MAC_SHA_PRE_PROCESS         = 0x0U,
  STSAFEA_MAC_SHA_POST_PROCESS        = 0x1U
} StSafeA_MacShaProcess_t;

/*!
 * \enum StSafeA_CurveId_t
 * \brief Curve identifier enumeration
 * \details Specifies the elliptic curve type.
 */
typedef enum
{
  STSAFEA_NIST_P_256      = 0x0U,
  STSAFEA_NIST_P_384      = 0x1U,
  STSAFEA_BRAINPOOL_P_256 = 0x2U,
  STSAFEA_BRAINPOOL_P_384 = 0x3U
} StSafeA_CurveId_t;

/*!
 * \enum StSafeA_ResponseCode_t
 * \brief STSAFEA response codes enumeration
 * \details Specifies success or the specific returned error.
 */
typedef enum
{
  STSAFEA_OK                           = 0x00U,
  STSAFEA_COMMUNICATION_ERROR          = 0x01U,
  STSAFEA_INCONSISTENT_COMMAND_DATA    = 0x02U,
  STSAFEA_VALUE_OUT_OF_RANGE           = 0x03U,
  STSAFEA_UNSUPPORTED_COMMAND_CODE     = 0x04U,
  STSAFEA_UNEXPECTED_ERROR             = 0x05U,
  STSAFEA_BUFFER_LENGTH_EXCEEDED       = 0x06U,
  STSAFEA_WRONG_SESSION                = 0x07U,
  STSAFEA_TOO_MANY_MESSAGE_LOST        = 0x08U,
  STSAFEA_CMAC_COUNTER_LIMIT_REACHED   = 0x09U,
  STSAFEA_KEY_NOT_FOUND                = 0x0AU,
  STSAFEA_KEY_BLOCKED                  = 0x0BU,
  STSAFEA_WRONG_KEY_TYPE               = 0x0CU,
  STSAFEA_COUNTER_OUT_OF_RANGE         = 0x0DU,
  STSAFEA_DEPTH_OUT_OF_RANGE           = 0x0EU,
  STSAFEA_INVALID_LIFE_CYCLE_STATE     = 0x0FU,
  STSAFEA_ENTRY_NOT_FOUND              = 0x10U,
  STSAFEA_UNSATISFIED_ACCESS_CONDITION = 0x11U,
  STSAFEA_INCORRECT_ZONE_TYPE          = 0x12U,
  STSAFEA_COUNTER_LIMIT_EXCEEDED       = 0x13U,
  STSAFEA_BOUNDARY_EXCEEDED            = 0x14U,
  STSAFEA_INVALID_PRIVATE_KEY          = 0x15U,
  STSAFEA_INVALID_CMAC                 = 0x16U,
  STSAFEA_CHALLENGE_MISSING            = 0x17U,
  STSAFEA_COMMAND_DECRYPTION_ERROR     = 0x18U,
  STSAFEA_INVALID_PUBLIC_KEY           = 0x19U,
  STSAFEA_PASSWORD_BLOCKED             = 0x1AU,
  STSAFEA_WRONG_KEY_USAGE              = 0x1BU,
  STSAFEA_WRONG_MODE_OF_OPERATION      = 0x1CU,
  STSAFEA_WRONG_MAC_LENGTH             = 0x1DU,
  STSAFEA_UNAUTHORIZED_COMMAND         = 0x1EU,
  STSAFEA_OLD_MESSAGE                  = 0x1FU,
  STSAFEA_CRYPTO_LIB_ISSUE             = 0x20U,
  STSAFEA_INVALID_RMAC                 = 0x21U,
  STSAFEA_INVALID_CRC                  = 0x22U,
  STSAFEA_INVALID_PARAMETER            = 0x30U,
  STSAFEA_INVALID_RESP_LENGTH          = 0x31U,
  STSAFEA_COMMUNICATION_NACK           = 0x32U
} StSafeA_ResponseCode_t;

/*!
 * \struct StSafeA_LVBuffer_t
 * \brief LV structure type definition
 * \details Specifies the Length - Value data format
 */
typedef struct
{
  uint16_t Length;                     /*!< The whole length in number of octet */
  uint8_t  *Data;                      /*!< Buffer data pointer */
} StSafeA_LVBuffer_t;

/*!
 * \struct StSafeA_TLVBuffer_t
 * \brief TLV structure type definition
 * \details Specifies the Tag - Length - Value data format.
 */
typedef struct
{
  uint8_t            Header;    /*!< The header for tag */
  StSafeA_LVBuffer_t LV;        /*!< The LV part */
} StSafeA_TLVBuffer_t;

/*!
 * \struct StSafeA_VerifySignatureBuffer_t
 * \brief Verify signature structure type definition
 * \details Response format of the verify signature command.
 */
typedef struct
{
  uint16_t Length;                /*!< The whole length in number of octet */
  uint8_t  SignatureValidity;     /*!< The data for the Signature Validity */
} StSafeA_VerifySignatureBuffer_t;

/*!
 * \struct StSafeA_ZoneInformationRecordBuffer_t
 * \brief Zone information record structure type definition
 * \details Provides zone information record.
 */
#pragma pack(push, 1)
typedef struct
{
  uint8_t  Index;
  uint8_t  ZoneType;                /*!< Zone type. 0 by default and 1 for zone with one way counter*/
  uint8_t  ReadAcChangeRight;      /*!< Read AC change right */
  uint8_t  ReadAccessCondition;    /*!< Read access conditions. See STSAFEA_Access_Conditions @group */
  uint8_t  UpdateAcChangeRight;    /*!< Update AC change right */
  uint8_t  UpdateAccessCondition;  /*!< Update access conditions. See STSAFEA_Access_Conditions @group */
  uint16_t DataSegmentLength;      /*!< Length of zone */
  uint32_t OneWayCounter;          /*!< One way counter value (significant for ZoneType = 1) */
} StSafeA_ZoneInformationRecordBuffer_t;
#pragma pack(pop)

/*!
 * \struct StSafeA_DataPartitionBuffer_t
 * \brief Data partition configuration structure type definition
 * \details Response format of the data partition configuration query.
 */
typedef struct
{
  uint16_t Length;           /*!< The whole length in number of octet */
  uint8_t  NumberOfZones;    /*!< Number of zone information records */
  StSafeA_ZoneInformationRecordBuffer_t *pZoneInfoRecord;
} StSafeA_DataPartitionBuffer_t;

/*!
 * \struct StSafeA_I2cParameterBuffer_t
 * \brief I2C parameter structure type definition
 * \details Response format of the I2C parameter query.
 */
typedef struct
{
  uint16_t Length;                            /*!< The whole length in number of octet */
  uint8_t  I2cAddress;                        /*!< The I2c Address of the STSAFE_A peripheral device. */
  uint8_t  LowPowerModeConfig;                /*!< I2C Low-power mode configuration. */
  uint8_t  LockConfig;                        /*!< I2C lock configuration. */
} StSafeA_I2cParameterBuffer_t;

/*!
 * \struct StSafeA_LifeCycleStateBuffer_t
 * \brief Life cycle state structure type definition
 * \details Response format of the life cycle state query.
 */
typedef struct
{
  uint16_t    Length;              /*!< The whole length in number of octet */
  uint8_t     LifeCycleStatus;     /*!< Life cycle state. See STSAFEA_Lifecycle_State @group */
} StSafeA_LifeCycleStateBuffer_t;

/*!
 * \struct StSafeA_DecrementBuffer_t
 * \brief Decrement structure type definition
 * \details Response format of the decrement command.
 */
typedef struct
{
  uint16_t Length;
  uint32_t OneWayCounter;
} StSafeA_DecrementBuffer_t;

/*!
 * \struct StSafeA_SharedSecretBuffer_t
 * \brief Shared secret structure type definition
 * \details Response format of the Establish Key command.
 */
typedef struct
{
  uint16_t         Length;                    /*!< The whole length in number of octet */
  StSafeA_LVBuffer_t SharedKey;               /*!< The key being computed by STSAFE_A */
} StSafeA_SharedSecretBuffer_t;

/*!
 * \struct StSafeA_PublicKeySlotBuffer_t
 * \brief Public key coding structure type definition
 * \details ECC public key slot structure format.
 */
typedef struct
{
  uint16_t Length;                    /*!< The whole length in number of octet */
  uint8_t  PresenceFlag;
  uint8_t  PointRepresentationId;
} StSafeA_PublicKeySlotBuffer_t;

/*!
 * \struct StSafeA_VerifyPasswordBuffer_t
 * \brief Verify password structure type definition
 * \details Response format of the verify password command.
 */
typedef struct
{
  uint16_t Length;                    /*!< The whole length in number of octet */
  uint8_t  VerificationStatus;
  uint8_t  RemainingTries;
} StSafeA_VerifyPasswordBuffer_t;

/*!
 * \struct StSafeA_HostKeySlotBuffer_t
 * \brief Host key slot structure type definition
 * \details Response format of the host key slot query.
 */
typedef struct
{
  uint16_t Length;                    /*!< The whole length in number of octet */
  uint8_t  HostKeyPresenceFlag;
  uint32_t HostCMacSequenceCounter;
} StSafeA_HostKeySlotBuffer_t;

/*!
 * \struct StSafeA_LocalEnvelopeKeyTableBuffer_t
 * \brief Local envelope key table structure type definition
 * \details Response format of the local envelope key table query.
 */
typedef struct
{
  uint16_t Length;                    /*!< The whole length in number of octet */
  uint8_t  NumberOfSlots;
} StSafeA_LocalEnvelopeKeyTableBuffer_t;

/*!
 * \struct StSafeA_LocalEnvelopeKeyInformationRecordBuffer_t
 * \brief Local envelope key information structure type definition
 * \details Contains the local envelope key information record.
 */
typedef struct
{
  uint8_t  SlotNumber;
  uint8_t  PresenceFlag;
  uint8_t  KeyLength;
} StSafeA_LocalEnvelopeKeyInformationRecordBuffer_t;

/*!
 * \struct StSafeA_CommandAuthorizationRecordBuffer_t
 * \brief Command authorization record structure type definition
 * \details Contains command authorization record.
 */
typedef struct
{
  uint8_t    CommandCode;          /*!< Code related to commands with update capability */
  uint8_t    CommandAC;            /*!< Command Access Condition. See STSAFEA_Command_Access_Conditions @group */
  uint8_t    HostEncryptionFlags;  /*!< Encryption flag. See STSAFEA_Host_Encryption_Flag @group */
} StSafeA_CommandAuthorizationRecordBuffer_t;

/*!
 * \struct StSafeA_CommandAuthorizationConfigurationBuffer_t
 * \brief Command authorization configuration structure type definition
 * \details Contains all commands' authorization configuration.
 */
typedef struct
{
  uint16_t Length;
  uint8_t  ChangeRight;
  uint8_t  CommandAuthorizationRecordNumber;
  StSafeA_CommandAuthorizationRecordBuffer_t  *pCommandAuthorizationRecord;
} StSafeA_CommandAuthorizationConfigurationBuffer_t;

/*!
 * \struct StSafeA_CommandAccessConditionRecordBuffer_t
 * \brief Command access record structure type definition
 * \details Contains command access record.
 */
typedef struct
{
  uint8_t    CommandCode;   /* Code related to commands with update capability */
  uint8_t    CommandAC;     /* Command Access Condition. See STSAFEA_Command_Access_Conditions @group */
} StSafeA_CommandAccessConditionRecordBuffer_t;

/*!
 * \struct StSafeA_CommandAccessConfigurationBuffer_t.
 * \brief Command access configuration structure type definition
 * \details Contains all commands access record.
 */
typedef struct
{
  uint16_t Length;
  uint8_t  CommandAccessRecordNumber;
  StSafeA_CommandAccessConditionRecordBuffer_t *pCommandACRecord;
} StSafeA_CommandAccessConfigurationBuffer_t;

/*!
 * \struct StSafeA_HostEncryptionRecordBuffer_t
 * \brief Command host encryption record structure type definition
 * \details Contains command host encryption record.
 */
typedef struct
{
  uint8_t    CommandCode;         /* Code related to commands with update capability */
  uint8_t    HostEncryptionFlags; /* Encryption flag. See STSAFEA_Host_Encryption_Flag @group */
} StSafeA_HostEncryptionRecordBuffer_t;

/*!
 * \struct StSafeA_HostEncryptionConfigurationBuffer_t
 * \brief Command host encryption configuration structure type definition
 * \details Contains all commands' host encryption record.
 */
typedef struct
{
  uint16_t Length;
  uint8_t                                HostEncryptionRecordNumber;
  StSafeA_HostEncryptionRecordBuffer_t   *pHostEncryptionRecord;
} StSafeA_HostEncryptionConfigurationBuffer_t;

/**
  * @brief   StSafeA_HashFunction_t
  *          SHA Function Pointer type definition
  *
  * @details  Used for the ShaUpdate callback defined at user space.
  */
typedef void (* StSafeA_HashFunction_t)(StSafeA_HashTypes_t in_hash_type, void *in_sha_ctx, uint8_t *in_input_message, uint32_t in_input_message_length);

/*!
 * \struct StSafeA_Hash_t
 * \brief Hash structure type definition
 * \details Contains STSAFEA Hash related field.
 */
typedef struct
{
  StSafeA_HashTypes_t     HashType;                                         /*!< STSAFE_A's type of hash */
  StSafeA_HashFunction_t  HashFuncPtr;                                      /*!< STSAFE_A's Hash Update function used to prepare commands */
  void                    *HashCtx;                                         /*!< STSAFE_A's hash context */
  uint8_t                 HashRes[STSAFEA_SHA_384_LENGTH];                  /*!< STSAFE_A's hash result sized at the max possible length */
} StSafeA_Hash_t;

/*!
 * \struct StSafeA_Handle_t
 * \brief STSAFEA handler structure type definition
 * \details Contains all data needed to manage the STSAFEA device including the transmit/receive buffer.
 */
typedef struct
{
  StSafeA_TLVBuffer_t  InOutBuffer;                               /*!< STSAFE_A's input output buffer pointer */
  uint8_t              CrcSupport;                                /*!< STSAFE_A's COM CRC feature support */
  uint8_t              MacCounter;                                /*!< MAC counter for peripheral MACs */
  uint32_t             HostMacSequenceCounter;                    /*!< Host-MAC counter */
  StSafeA_Hash_t       HashObj;
} StSafeA_Handle_t;

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

#endif /* STSAFEA_TYPES_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
