
#include "HT_otp_api.h"

void HT_OTP_Write(uint8_t *ptr, uint8_t size, uint32_t addr) {
	uint32_t k = 0;
	int8_t j = 0;
	uint32_t tmp = 0;

	for (uint8_t i = 0; i < (size+1); i++) {

		if(j > 24) {
#ifdef USE_OTP
			LL_FLASH_OTPWrite(FLASH, OTP_ADDR+k, tmp);
#else
			HAL_FLASH_Program(addr+k, tmp);
#endif
			k += 4;
			j = 0;
			tmp = 0;
		}

		if(j <= 24 && i != size)  {
			tmp = tmp | (ptr[i] << j);
			j += 8;
		}
	}
}

void HT_OTP_Read(uint8_t *output, uint8_t size, uint32_t addr) {
	uint32_t tmp;
	uint32_t k = 0;
	uint32_t mask;
	uint32_t aux = 0;
	uint8_t cnt;

	for (uint8_t i = 0; i < size; i+=4) {
		tmp = *(uint32_t *)(addr+k);
		k += 4;
		mask = 0x000000FF;
		cnt = 0;

		for (uint8_t j = 0; j < 4; j++) {
			aux = tmp & mask;
			output[i+j] = (uint8_t)(aux >> cnt);
			cnt += 8;
			mask <<= 8;
		}
	}
}
