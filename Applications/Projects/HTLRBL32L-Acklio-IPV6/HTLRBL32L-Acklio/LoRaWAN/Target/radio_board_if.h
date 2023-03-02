/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    radio_board_if.h
  * @author  MCD Application Team
  * @brief   Header for Radio interface configuration
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RADIO_BOARD_IF_H
#define RADIO_BOARD_IF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#ifdef SX1276MB1LAS

#include "sx1276mb1las.h"

#define Sx_Board_IoInit            SX1276MB1LAS_RADIO_IoInit
#define Sx_Board_IoDeInit          SX1276MB1LAS_RADIO_IoDeInit
#define Sx_Board_IoIrqInit         SX1276MB1LAS_RADIO_IoIrqInit
#define Sx_Board_SendRecv          SX1276MB1LAS_RADIO_SendRecv
#define Sx_Board_ChipSelect        SX1276MB1LAS_RADIO_ChipSelect
#define Sx_Board_CheckRfFrequency  SX1276MB1LAS_RADIO_CheckRfFrequency
#define Sx_Board_Reset             SX1276MB1LAS_RADIO_Reset
#define Sx_Board_SetXO             SX1276MB1LAS_RADIO_SetXO
#define Sx_Board_GetWakeUpTime     SX1276MB1LAS_RADIO_GetWakeUpTime
#define Sx_Board_GetPaSelect       SX1276MB1LAS_RADIO_GetPaSelect
#define Sx_Board_SetAntSw          SX1276MB1LAS_RADIO_SetAntSw
#define Sx_Board_Bus_Init          SX1276MB1LAS_RADIO_Bus_Init
#define Sx_Board_Bus_deInit        SX1276MB1LAS_RADIO_Bus_deInit
#define Sx_Board_GetDio1PinState   SX1276MB1LAS_RADIO_GetDio1PinState

#elif SX1276MB1MAS
#include "sx1276mb1mas.h"

#define Sx_Board_IoInit            SX1276MB1MAS_RADIO_IoInit
#define Sx_Board_IoDeInit          SX1276MB1MAS_RADIO_IoDeInit
#define Sx_Board_IoIrqInit         SX1276MB1MAS_RADIO_IoIrqInit
#define Sx_Board_SendRecv          SX1276MB1MAS_RADIO_SendRecv
#define Sx_Board_ChipSelect        SX1276MB1MAS_RADIO_ChipSelect
#define Sx_Board_CheckRfFrequency  SX1276MB1MAS_RADIO_CheckRfFrequency
#define Sx_Board_Reset             SX1276MB1MAS_RADIO_Reset
#define Sx_Board_SetXO             SX1276MB1MAS_RADIO_SetXO
#define Sx_Board_GetWakeUpTime     SX1276MB1MAS_RADIO_GetWakeUpTime
#define Sx_Board_GetPaSelect       SX1276MB1MAS_RADIO_GetPaSelect
#define Sx_Board_SetAntSw          SX1276MB1MAS_RADIO_SetAntSw
#define Sx_Board_Bus_Init          SX1276MB1MAS_RADIO_Bus_Init
#define Sx_Board_Bus_deInit        SX1276MB1MAS_RADIO_Bus_deInit
#define Sx_Board_GetDio1PinState   SX1276MB1MAS_RADIO_GetDio1PinState

#elif CMWX1ZZABZ0XX
#include "cmwx1zzabz_0xx.h"

#define Sx_Board_IoInit            CMWX1ZZABZ0XX_RADIO_IoInit
#define Sx_Board_IoDeInit          CMWX1ZZABZ0XX_RADIO_IoDeInit
#define Sx_Board_IoIrqInit         CMWX1ZZABZ0XX_RADIO_IoIrqInit
#define Sx_Board_SendRecv          CMWX1ZZABZ0XX_RADIO_SendRecv
#define Sx_Board_ChipSelect        CMWX1ZZABZ0XX_RADIO_ChipSelect
#define Sx_Board_CheckRfFrequency  CMWX1ZZABZ0XX_RADIO_CheckRfFrequency
#define Sx_Board_Reset             CMWX1ZZABZ0XX_RADIO_Reset
#define Sx_Board_SetXO             CMWX1ZZABZ0XX_RADIO_SetXO
#define Sx_Board_GetWakeUpTime     CMWX1ZZABZ0XX_RADIO_GetWakeUpTime
#define Sx_Board_GetPaSelect       CMWX1ZZABZ0XX_RADIO_GetPaSelect
#define Sx_Board_SetAntSw          CMWX1ZZABZ0XX_RADIO_SetAntSw
#define Sx_Board_Bus_Init          CMWX1ZZABZ0XX_RADIO_Bus_Init
#define Sx_Board_Bus_deInit        CMWX1ZZABZ0XX_RADIO_Bus_deInit
#define Sx_Board_GetDio1PinState   CMWX1ZZABZ0XX_RADIO_GetDio1PinState

#elif SX1272MB2DAS
#include "sx1272mb2das.h"

#define Sx_Board_IoInit            SX1272MB2DAS_RADIO_IoInit
#define Sx_Board_IoDeInit          SX1272MB2DAS_RADIO_IoDeInit
#define Sx_Board_IoIrqInit         SX1272MB2DAS_RADIO_IoIrqInit
#define Sx_Board_SendRecv          SX1272MB2DAS_RADIO_SendRecv
#define Sx_Board_ChipSelect        SX1272MB2DAS_RADIO_ChipSelect
#define Sx_Board_CheckRfFrequency  SX1272MB2DAS_RADIO_CheckRfFrequency
#define Sx_Board_Reset             SX1272MB2DAS_RADIO_Reset
#define Sx_Board_SetXO             SX1272MB2DAS_RADIO_SetXO
#define Sx_Board_GetWakeUpTime     SX1272MB2DAS_RADIO_GetWakeUpTime
#define Sx_Board_GetPaSelect       SX1272MB2DAS_RADIO_GetPaSelect
#define Sx_Board_SetAntSw          SX1272MB2DAS_RADIO_SetAntSw
#define Sx_Board_Bus_Init          SX1272MB2DAS_RADIO_Bus_Init
#define Sx_Board_Bus_deInit        SX1272MB2DAS_RADIO_Bus_deInit
#define Sx_Board_GetDio1PinState   SX1272MB2DAS_RADIO_GetDio1PinState

#elif SX1262DVK1DAS
#include "sx1262dvk1das.h"

#define Sx_Board_IoInit            SX1262DVK1DAS_RADIO_IoInit
#define Sx_Board_IoDeInit          SX1262DVK1DAS_RADIO_IoDeInit
#define Sx_Board_IoIrqInit         SX1262DVK1DAS_RADIO_IoIrqInit
#define Sx_Board_SendRecv          SX1262DVK1DAS_RADIO_SendRecv
#define Sx_Board_ChipSelect        SX1262DVK1DAS_RADIO_ChipSelect
#define Sx_Board_CheckRfFrequency  SX1262DVK1DAS_RADIO_CheckRfFrequency
#define Sx_Board_Reset             SX1262DVK1DAS_RADIO_Reset
#define Sx_Board_SetXO             SX1262DVK1DAS_RADIO_SetXO
#define Sx_Board_GetWakeUpTime     SX1262DVK1DAS_RADIO_GetWakeUpTime
#define Sx_Board_GetPaSelect       SX1262DVK1DAS_RADIO_GetPaSelect
#define Sx_Board_SetAntSw          SX1262DVK1DAS_RADIO_SetAntSw
#define Sx_Board_Bus_Init          SX1262DVK1DAS_RADIO_Bus_Init
#define Sx_Board_Bus_deInit        SX1262DVK1DAS_RADIO_Bus_deInit
#define Sx_Board_WaitOnBusy        SX1262DVK1DAS_RADIO_WaitOnBusy
#define Sx_Board_WakeUp            SX1262DVK1DAS_RADIO_WakeUp
#define Sx_Board_IsTcxo            SX1262DVK1DAS_RADIO_BoardIsTcxo
#define Sx_Board_SetLedRx          SX1262DVK1DAS_RADIO_BoardSetLedRx
#define Sx_Board_SetLedTx          SX1262DVK1DAS_RADIO_BoardSetLedTx

#elif SX1262DVK1CAS
#include "sx1262dvk1cas.h"

#define Sx_Board_IoInit            SX1262DVK1CAS_RADIO_IoInit
#define Sx_Board_IoDeInit          SX1262DVK1CAS_RADIO_IoDeInit
#define Sx_Board_IoIrqInit         SX1262DVK1CAS_RADIO_IoIrqInit
#define Sx_Board_SendRecv          SX1262DVK1CAS_RADIO_SendRecv
#define Sx_Board_ChipSelect        SX1262DVK1CAS_RADIO_ChipSelect
#define Sx_Board_CheckRfFrequency  SX1262DVK1CAS_RADIO_CheckRfFrequency
#define Sx_Board_Reset             SX1262DVK1CAS_RADIO_Reset
#define Sx_Board_SetXO             SX1262DVK1CAS_RADIO_SetXO
#define Sx_Board_GetWakeUpTime     SX1262DVK1CAS_RADIO_GetWakeUpTime
#define Sx_Board_GetPaSelect       SX1262DVK1CAS_RADIO_GetPaSelect
#define Sx_Board_SetAntSw          SX1262DVK1CAS_RADIO_SetAntSw
#define Sx_Board_Bus_Init          SX1262DVK1CAS_RADIO_Bus_Init
#define Sx_Board_Bus_deInit        SX1262DVK1CAS_RADIO_Bus_deInit
#define Sx_Board_WaitOnBusy        SX1262DVK1CAS_RADIO_WaitOnBusy
#define Sx_Board_WakeUp            SX1262DVK1CAS_RADIO_WakeUp
#define Sx_Board_IsTcxo            SX1262DVK1CAS_RADIO_BoardIsTcxo
#define Sx_Board_SetLedRx          SX1262DVK1CAS_RADIO_BoardSetLedRx
#define Sx_Board_SetLedTx          SX1262DVK1CAS_RADIO_BoardSetLedTx

#elif SX1261DVK1BAS
#include "sx1261dvk1bas.h"

#define Sx_Board_IoInit            SX1261DVK1BAS_RADIO_IoInit
#define Sx_Board_IoDeInit          SX1261DVK1BAS_RADIO_IoDeInit
#define Sx_Board_IoIrqInit         SX1261DVK1BAS_RADIO_IoIrqInit
#define Sx_Board_SendRecv          SX1261DVK1BAS_RADIO_SendRecv
#define Sx_Board_ChipSelect        SX1261DVK1BAS_RADIO_ChipSelect
#define Sx_Board_CheckRfFrequency  SX1261DVK1BAS_RADIO_CheckRfFrequency
#define Sx_Board_Reset             SX1261DVK1BAS_RADIO_Reset
#define Sx_Board_SetXO             SX1261DVK1BAS_RADIO_SetXO
#define Sx_Board_GetWakeUpTime     SX1261DVK1BAS_RADIO_GetWakeUpTime
#define Sx_Board_GetPaSelect       SX1261DVK1BAS_RADIO_GetPaSelect
#define Sx_Board_SetAntSw          SX1261DVK1BAS_RADIO_SetAntSw
#define Sx_Board_Bus_Init          SX1261DVK1BAS_RADIO_Bus_Init
#define Sx_Board_Bus_deInit        SX1261DVK1BAS_RADIO_Bus_deInit
#define Sx_Board_WaitOnBusy        SX1261DVK1BAS_RADIO_WaitOnBusy
#define Sx_Board_WakeUp            SX1261DVK1BAS_RADIO_WakeUp
#define Sx_Board_IsTcxo            SX1261DVK1BAS_RADIO_BoardIsTcxo
#define Sx_Board_SetLedRx          SX1261DVK1BAS_RADIO_BoardSetLedRx
#define Sx_Board_SetLedTx          SX1261DVK1BAS_RADIO_BoardSetLedTx

#else
#error "include your board here"
#endif

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions ------------------------------------------------------- */

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* RADIO_BOARD_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
