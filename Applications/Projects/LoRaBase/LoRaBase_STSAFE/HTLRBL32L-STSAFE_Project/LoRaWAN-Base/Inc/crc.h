
#ifndef __CRC_H__
#define __CRC_H__

#include "main.h"

int32_t MX_CRC_Init(void);
uint32_t CRC_Compute(uint8_t *pData1, uint16_t Length1, uint8_t *pData2, uint16_t Length2);

#endif
