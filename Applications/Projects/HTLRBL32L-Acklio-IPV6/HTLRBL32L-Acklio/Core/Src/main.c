/**
 * Copyright (C) 2018-2022 ACKLIO SAS - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Aydogan Ersoz - aydogan.ersoz@ackl.io
 *
 * Based on ST's AT_Slave example. Check license here: www.st.com/SLA0044.
 *
 */

#include <stdio.h>
#include "sys_app.h"
#include "at.h"
#include "atmgt.h"
#include "fullsdkl2.h"
#include "platform.h"
#include "at.h"
#include "main.h"
#include "fullsdkl2a.h"
#include "atdtg.h"
#ifdef TRACE_ENABLED
#include "fullsdktrace.h"
#endif

void CMD_Init(void);
void CMD_Process(void);

void ModulesTick(void);
void ModulesInit(void);
void ipcore_join_routine(void);
void unjoin(void);

NO_INIT(uint32_t dyn_alloc_a[DYNAMIC_MEMORY_SIZE >> 2]);

bool joining;

volatile uint8_t nwk_joined=0;
volatile uint8_t synced=0;


int main(void)
{

	if (SystemInit(SYSCLK_64M, BLE_SYSCLK_32M) != SUCCESS) {
    /* Error during system clock configuration take appropriate action */
  }
  // Resets all peripherals, initializes the Flash interface and the Systick.
  HAL_Init();

  SystemApp_Init();

  l2_init();

  CMD_Init();

  APP_LOG(TS_OFF, VLEVEL_M, "app> Starting...\n");

  ModulesInit();
  HT_BLE_BleConfig();
  HT_BLE_SetDeviceConnectable();

  while (1)
  {
	ipcore_join_routine();
	ModulesTick();
	HT_PB_app();
	CMD_Process();
	fullsdk_process();

  }
}

void ModulesInit(void) {


	uint8_t ret;
	BLE_STACK_InitTypeDef BLE_STACK_InitParams = BLE_STACK_INIT_PARAMETERS;

	LL_AHB_EnableClock(LL_AHB_PERIPH_PKA|LL_AHB_PERIPH_RNG);

	/* BlueNRG-LP stack init */

	ret = BLE_STACK_Init(&BLE_STACK_InitParams);
	if (ret != BLE_STATUS_SUCCESS) {
		APP_LOG(TS_OFF, VLEVEL_M, "Error in BLE_STACK_Init()\n");
		printf("Error in BLE_STACK_Init() 0x%02x\r\n", ret);
		while(1);
	}
	BLECNTR_InitGlobal();

	HAL_VTIMER_InitType VTIMER_InitStruct = {HS_STARTUP_TIME, INITIAL_CALIBRATION, CALIBRATION_INTERVAL};
	HAL_VTIMER_Init(&VTIMER_InitStruct);

	BLEPLAT_Init();
	if (PKAMGR_Init() == PKAMGR_ERROR)
		while(1);

	if (RNGMGR_Init() != RNGMGR_SUCCESS)
		while(1);

	/* Init the AES block */
	AESMGR_Init();
}

void ModulesTick(void) {
	/* Timer tick */
	HAL_VTIMER_Tick();

	/* Bluetooth stack tick */
	BLE_STACK_Tick();

	/* NVM manager tick */
	NVMDB_Tick();
}

void hci_hardware_error_event(uint8_t Hardware_Code) {
	if (Hardware_Code <= 0x03) {
		printf("Error code: 0x%02X\n", Hardware_Code);
		NVIC_SystemReset();
	}
}

void aci_hal_fw_error_event(uint8_t FW_Error_Type, uint8_t Data_Length, uint8_t Data[]) {
	if (FW_Error_Type <= 0x03) {
		uint16_t connHandle;

		/* Data field is the connection handle where error has occurred */
		connHandle = LE_TO_HOST_16(Data);

		aci_gap_terminate(connHandle, BLE_ERROR_TERMINATED_REMOTE_USER);
	}
}

PowerSaveLevels App_PowerSaveLevel_Check(PowerSaveLevels level) {
	return POWER_SAVE_LEVEL_STOP_NOTIMER;
}

void ipcore_join_routine(void){

static uint8_t joining=0;

	if(!joining){
		joining=1;
		//change configurations
		at_DevEUI_set("xx:xx:xx:xx:xx:xx:xx:xx",NULL);
		at_JoinEUI_set("00:00:00:00:00:00:00:00",NULL);
		at_AppKey_set("xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx:xx",NULL);

		at_Join("C",NULL);

		printf("joining\n");
	}else if (nwk_joined){

		//nwk_joined=0;
		at_DataRate_set("5",NULL);
		//HAL_Delay(1000);
		char param[] = "b1008418960186010101010101818302181c8e880c040102000081410602880d080101000081410002880e140101000081440001234502880f1001010008814200000288100801010000814111028811080101000081414002881218400102000081000288131840010200008101028814184001020000810202881518400102000081030288161001020000810402881710010200008105028818181001010004814200000288181910010100058142000002a4d9";
		uint8_t status = at_set_tpl(param,NULL);
		APP_LOG(TS_OFF, VLEVEL_M, "status %d\n", status);
		at_set_template_params("0,5454000000000000",NULL);
		at_sync("10000,3",NULL);
		nwk_joined=false;
		//unjoin();
		//wait
	}else if(synced){
		synced=false;
		at_set_fullsdk_api("D",NULL);
		at_socket(NULL,NULL);
		at_bind("0,5454:0000:0000:0000:0000:0000:0000:0004,33333",NULL);

	}

}


void unjoin(void){
	nwk_joined= !nwk_joined;
}


