


#ifndef HT_CRYPTO_H
#define HT_CRYPTO_H

#include "stsafea_types.h"
#include "LoRaMacTypes.h"
#include "../Crypto/cmac.h"
#include "aes.h"
#include "secure-element.h"

typedef enum keytypes{
	HT_DEVADDR   = 0,
	ABP_APPSKEY  = 1,
	ABP_NWKSKEY  = 2,
	OTAA_APPKEY  = 3,
	OTAA_APPSKEY = 4,
	OTAA_NWKSKEY = 5
}ht_key_types;


StSafeA_ResponseCode_t ht_crypto_init(void);

SecureElementStatus_t ht_aes_encrypt( uint8_t* buffer, uint16_t size, KeyIdentifier_t keyID, uint8_t* encBuffer,uint8_t activation_mode );
SecureElementStatus_t ht_compute_cmac( uint8_t *micBxBuffer, uint8_t *buffer, uint16_t size, KeyIdentifier_t keyID, uint32_t* cmac,uint8_t activation_mode );
SecureElementStatus_t ht_verify_cmac( uint8_t* buffer, uint16_t size, uint32_t expectedCmac, KeyIdentifier_t keyID, uint8_t activation_mode );
ht_key_types keyIDTranslation(KeyIdentifier_t keyID,uint8_t activation_mode);
SecureElementStatus_t ht_key_set( KeyIdentifier_t keyID, uint8_t* key,uint8_t activation_mode );
SecureElementStatus_t ht_crypto_hibernate(void);

uint8_t get_dev_addr(uint32_t *key);
uint8_t get_dev_eui(uint8_t *key);
uint8_t get_join_eui(uint8_t *key);
uint8_t keys_provisioned(void);
#endif /* HT_CRYPTO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
