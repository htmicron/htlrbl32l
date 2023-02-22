#ifndef __HT_OTP_API_H__
#define __HT_OTP_API_H__

#include "main.h"

#define OTP_ADDR 0x10001800
#define OTP_LOCK_ADDR 0x10001BFF

void HT_OTP_Write(uint8_t *ptr, uint8_t size, uint32_t addr);
void HT_OTP_Read(uint8_t *output, uint8_t size, uint32_t addr);

#endif /* __HT_OTP_API_H__ */
