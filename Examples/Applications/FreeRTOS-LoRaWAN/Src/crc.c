
#include "crc.h"
#include "stsafea_conf.h"

CRC_HandleTypeDef hcrc;

static __IO uint32_t CRC_CR; /*!< CRC Control register */

int32_t MX_CRC_Init(void) {
	hcrc.Instance = CRC;
	hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_DISABLE;
	hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_DISABLE;
	hcrc.Init.GeneratingPolynomial = 0x00001021;
	hcrc.Init.CRCLength = CRC_POLYLENGTH_16B;
	hcrc.Init.InitValue = 0xFFFFFFFF;
	hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_BYTE;
	hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_ENABLE;
	hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;

	if (HAL_CRC_Init(&hcrc) != HAL_OK)
		while (1);

	CRC_CR = READ_REG(hcrc.Instance->CR);

	return 0;
}

void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc) {
	if(hcrc->Instance==CRC) {
		/* Peripheral clock enable */
		__HAL_RCC_CRC_CLK_ENABLE();
	}
}

void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc) {
	if(hcrc->Instance==CRC) {
		/* Peripheral clock disable */
		__HAL_RCC_CRC_CLK_DISABLE();
	}
}

uint32_t CRC_Compute(uint8_t *pData1, uint16_t Length1, uint8_t *pData2, uint16_t Length2) {
	uint32_t crc = 0;

	WRITE_REG(hcrc.Instance->CR, CRC_CR);

	if (pData1 != NULL)
		crc = HAL_CRC_Calculate(&hcrc, (uint32_t *)pData1, (uint32_t)Length1);

	if (pData2 != NULL)
		crc = ~HAL_CRC_Accumulate(&hcrc, (uint32_t *)pData2, (uint32_t)Length2);

	crc = SWAP2BYTES(crc);

	return crc;
}
