/******************** (C) COPYRIGHT 2020 STMicroelectronics ********************
* File Name          : aes_hw.c
* Author             : AMS - RF Application Team
* Description        : Implementation of AES encryption needed by crypto library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
#include "crypto.h"
#include "aes_manager.h"

/* Implementation of the AES 128 required by the crypto library. */
void AES_128_HW_enc(const uint32_t *P_pInputBuffer,
                    uint32_t *P_pOutputBuffer,
                    const uint8_t *P_pKey)
{
  uint32_t tmp_key_32[4], input_32[4], output_32[4];
  uint8_t *tmp_key = (uint8_t *)tmp_key_32;
  uint8_t *input = (uint8_t *)input_32;
  uint8_t *output = (uint8_t *)output_32;
  int32_t i;
  
  for (i = 0; i < 16; i++)
  {
    tmp_key[15 - i] =  P_pKey[i];
  }
  
  for (i = 0; i < AES_BLOCK_SIZE; i++)
  {
    LEW32_2_BUFFER(input, i * 4, P_pInputBuffer[3 - i]);
  }
  
  AESMGR_Encrypt(input_32, tmp_key_32, output_32, 0);
  
  for (i = 0; i < AES_BLOCK_SIZE; i++)
  {
    P_pOutputBuffer[3 - i] = BUFFER_2_LEW32(output, i * 4);
  }
}

/******************* (C) COPYRIGHT 2019 STMicroelectronics *****END OF FILE****/
