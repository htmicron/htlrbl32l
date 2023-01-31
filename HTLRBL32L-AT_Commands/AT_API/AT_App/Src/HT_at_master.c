//#include "uart.h"
#include "HT_uart_api.h"
#include "HT_at_master.h"
#include "HT_atlora_api.h"
//#include "HT_at_ble_api.h"
//#include "HT_ble_api.h"
//#include "HT_at_stsafe.h"
#include "string.h"


HT_AT_LoRa_ErrorCode lora_error_code = LORA_ERROR_NONE;

extern volatile uint8_t radio_irqn;

static const AT_Command *AT_command_tab[] = {
		"BLETEST",
		"BLECONNECT",
		"LORATX",
		"STSAFETEST",
		"DEEPSLEEP",
		"INITWKPPIN",
		"ECHO",
		"RTCWKP",
	/*LORA*/
		"DEVEUI",
		"DEVEUI?",
		"DEVADDR",
		"DEVADDR?",
		"APPSKEY",
		"APPSKEY?",
		"NWKSKEY",
		"NWKSKEY?",
		"APPEUI",
		"APPEUI?",
		"APPKEY",
		"APPKEY?",
		"REGION",
		"REGION?",
		"JOINCFG",
		"JOINCFG?",
		"ADR",
		"ADR?",
		"DR",
		"DR?",
		"JOINDELAYRX1",
		"JOINDELAYRX1?",
		"JOINDELAYRX2",
		"JOINDELAYRX2?",
		"DELAYRX1",
		"DELAYRX1?",
		"DELAYRX2",
		"DELAYRX2?",
		"RXDURATION",
		"RXDURATION?",
		"POWER",
		"POWER?",
		"CHMASK",
		"CHMASK?",
		"RMVCHMASK",
		"NWKMODE",
		"NWKMODE?",
		"NWKJOIN",
		"NWKJOIN?",
		"SENDSTR",
		"SENDHEX",
		"RCV",
		"STATS?"
	
	
};

uint32_t rtc_timeout = 0;

/* ---------------- Methods -------------------------- */

uint8_t HT_AT_GetCommandStrLen(HT_AT_Commands cmd) {
	return (strlen(AT_command_tab[cmd]));
}

uint8_t HT_AT_CheckErrorCode(HT_AT_ErrorCode code)  {
	return (code.at_cmd_error == AT_ERROR_NONE && code.ble_error == 0x00 && code.lora_error == LORA_ERROR_NONE
			&& code.uart_error == UART_ERROR_NONE) ? 1 : 0;
}

HT_ATCommand_ErrorCode HT_AT_ValidHeaderCommand(uint8_t *str) {
	return (!strncmp((char *)str, HEADER_STR, strlen((char *)HEADER_STR)) ? AT_ERROR_NONE :
			AT_ERROR_UNAVAILABLE_HEADER_CMD);
}

static uint8_t HT_AT_GetCommandLen(uint8_t *cmd) {
	uint8_t len = 0;

	for (uint8_t i = 0; i < strlen((char *)cmd); i++) {
		if((char)cmd[i] == '=' || (char)cmd[i] == '\n' || (char)cmd[i] == '\r')
			break;

		len += 1;
	}

	return len;
}

HT_ATCommand_ErrorCode HT_AT_ValidCommand(uint8_t *cmd, HT_AT_Commands *cmd_id) {
	uint8_t len = HT_AT_GetCommandLen(cmd);

	for (uint16_t i = 0; i < N_CMD(AT_command_tab); i++) {
		if(!strncmp(AT_command_tab[i], (char *)cmd, len)) {
			*cmd_id = (HT_AT_Commands)i;
			return AT_ERROR_NONE;
		}
	}

	return AT_ERROR_UNAVAILABLE_CMD;
}

uint8_t HT_AT_IsHexValue(char value) {
	return (((uint8_t)value >= 0x30 && (uint8_t)value <= 0x39) || ((uint8_t)value >= 0x41 && (uint8_t)value <= 0x46 || ((uint8_t)value >= 0x61 && (uint8_t)value <= 0x66))
			? 1 : 0);
}

uint8_t HT_AT_IsHexPayload(char *payload) {

	for (uint8_t i = 0; i < strlen(payload); i++) {
		if(!HT_AT_IsHexValue(payload[i]))
			return 0;
	}

	return 1;
}

uint8_t HT_AT_CheckNumberOfParameter(uint8_t *param, uint8_t nParam) {
	uint8_t cnt = 1;

	for (uint8_t i = 0; i < strlen((char *)param); i++) {
		if((char)param[i] == PARAMETER_DELIMITER[0])
			cnt += 1;
	}

	return ((cnt == nParam) ? 1 : 0);
}

uint8_t HT_AT_ValidParameterFlag(uint8_t param) {
	return (param == 0 || param == 1 ? 1 : 0);
}
uint8_t HT_AT_ValidParameterInterval(uint8_t param,uint8_t min, uint8_t max) {
	return (param >= min && param <=max ? 1 : 0);
}


//static uint8_t HT_AT_ValidEdgePullOption(uint8_t pull) {
//	return ((uint32_t)pull <= GPIO_PULLDOWN) ? 1 : 0;
//}

//static uint8_t HT_AT_ValidExtiPriority(uint8_t priority) {
//	return (priority <= 3) ? 1 : 0;
//}

//static uint8_t HT_AT_ValidExtiType(uint8_t type) {
//	return (type == EXTI_TYPE_EDGE || type == EXTI_TYPE_LEVEL) ? 1 : 0;
//}

//static uint8_t HT_AT_ValidEdgeDetection(uint8_t edge) {
//	return (edge <= LL_EXTI_TRIGGER_HIGH_LEVEL) ? 1 : 0;
//}

//static uint8_t HT_AT_ValidGPIO(char *gpio) {
//	return (gpio[0] == GPIOA_CH || gpio[0] == GPIOB_CH) ? 1 : 0;
//}

//static uint8_t HT_AT_ValidPinNumber(uint8_t pin) {
//	return (pin <= 15) ? 1 : 0;
//}

//static uint8_t HT_AT_ValidRtcTimeout(uint32_t timeout) {
//	return (timeout <= 0xFFFF ? 1 : 0);
//}

uint8_t HT_AT_NullParameter(uint8_t *param) {
	return (strlen((char *)param) == 0 || param[0] == '\0') ? 1 : 0;
}

uint8_t HT_AT_ValidLength(uint8_t *param, uint32_t size) {
	uint8_t len;

	len = !(strlen((char *)param) % 2) ? (strlen((char *)param)/2) : ((strlen((char *)param)+1)/2);

	return (len <= size) ? 1 : 0;
}

static void HT_AT_StrRev(char *x, uint8_t begin, uint8_t end) {
	char c;

	if (begin >= end)
		return;

	c = *(x + begin);
	*(x + begin) = *(x + end);
	*(x + end) = c;

	HT_AT_StrRev(x, ++begin, --end);
}

static void HT_AT_GetInterval(int16_t k, HT_AT_Parameter *ptr, char *str, char delim) {
	int16_t j = 0;

	for (int16_t i = k; i >= 0; i--) {
		if (str[i] != delim) {
			ptr->param[j] = str[i];
			j += 1;
		} else {
			break;
		}
	}

	HT_AT_StrRev(ptr->param, 0, strlen(ptr->param)-1);

}

void HT_AT_SplitCommandData(uint8_t *cmdBuffer, char *delim, HT_AT_Parameter *ptr) {
	int16_t k = 0;
	int16_t count = 0;
	int16_t i;

	for (i = 0; i < strlen((char *)cmdBuffer); i++) {
		if ((char)cmdBuffer[i] == *delim)
			count += 1;
	}
		
	for (i = 0; i < strlen((char *)cmdBuffer); i++){
		if ((char)cmdBuffer[i] == *delim || i == (strlen((char *)cmdBuffer)-1)) {
			HT_AT_GetInterval(i != (strlen((char *)cmdBuffer)-1) ? (i - 1) : i, &ptr[k], (char *)cmdBuffer, *delim);
			if (k < count)
				k += 1;
			else
				break;
		}
	}

}

void HT_AT_ParseCommandData(char *str, uint8_t len, uint8_t *output) {
	char tmp[2];
	uint8_t ind = 0;
	uint8_t i = 0;

	do {
		tmp[0] = str[ind];
		tmp[1] = str[++ind];

		ind++;

		output[i] = (uint8_t)strtol(tmp, NULL, 16);

		i++;
	} while (i < len);
}

/* --------------- Commands -------------------------------- */

HT_AT_ErrorCode HT_AT_ExecuteCommand(uint8_t *ptr, HT_AT_Commands cmd) {
	HT_AT_ErrorCode error = {0};

	//printf("cmd: %d\n",cmd);
	switch (cmd) {
		case AT_ECHO:
			error = HT_AT_EchoCmd(ptr);
			break;
		case AT_DEVEUI:
			error = HT_AT_set_DEVEUI(ptr);
			break;
		
		case AT_DEVEUI_REQ:
			error = HT_AT_get_DEVEUI();
			break;
		case AT_DEVADDR:
			error = HT_AT_set_DEVADDR(ptr);
			break;
		case AT_DEVADDR_REQ:
			error = HT_AT_get_DEVADDR();
			break;
		case AT_APPSKEY:
			error = HT_AT_set_APPSKEY(ptr);
			break;
		case AT_APPSKEY_REQ:
			error = HT_AT_get_APPSKEY();
			break;				
		case AT_NWKSKEY:
			error = HT_AT_set_NWKSKEY(ptr);
			break;
		case AT_NWKSKEY_REQ:
			error = HT_AT_get_NWKSKEY();
			break;				
		case AT_APPEUI:
			error = HT_AT_set_APPEUI(ptr);
			break;				
		case AT_APPEUI_REQ:
			error = HT_AT_get_APPEUI();
			break;		
		case AT_APPKEY:
			error = HT_AT_set_APPKEY(ptr);
			break;				
		case AT_APPKEY_REQ:
			error = HT_AT_get_APPKEY();
			break;
		case AT_REGION:
			error = HT_AT_set_REGION(ptr);
			break;				
		case AT_REGION_REQ:
			error = HT_AT_get_REGION();
			break;				
		case AT_JOINCFG:
			error = HT_AT_set_JOINCFG(ptr);
			break;				
		case AT_JOINCFG_REQ:
			error = HT_AT_get_JOINCFG();
			break;					
		case AT_ADR:
			error = HT_AT_set_ADR(ptr);
			break;				
		case AT_ADR_REQ:
			error = HT_AT_get_ADR();
			break;						
		case AT_DR:
			error = HT_AT_set_DR(ptr);
			break;				
		case AT_DR_REQ:
			error = HT_AT_get_DR();
			break;								
		case AT_JOINDELAYRX1:
			error = HT_AT_set_JOINDELAYRX1(ptr);
			break;				
		case AT_JOINDELAYRX1_REQ:
			error = HT_AT_get_JOINDELAYRX1();
			break;							
		case AT_JOINDELAYRX2:
			error = HT_AT_set_JOINDELAYRX2(ptr);
			break;				
		case AT_JOINDELAYRX2_REQ:
			error = HT_AT_get_JOINDELAYRX2();
			break;					
		case AT_DELAYRX1:
			error = HT_AT_set_DELAYRX1(ptr);
			break;				
		case AT_DELAYRX1_REQ:
			error = HT_AT_get_DELAYRX1();
			break;									
		case AT_DELAYRX2:
			error = HT_AT_set_DELAYRX2(ptr);
			break;				
		case AT_DELAYRX2_REQ:
			error = HT_AT_get_DELAYRX2();
			break;
		case AT_RX_WINDOW_DURATION:
			error = HT_AT_set_WINDOW_DURATION(ptr);
			break;
		case AT_RX_WINDOW_DURATION_REQ:
			error = HT_AT_get_WINDOW_DURATION();
			break;
		case AT_POWER:
			error = HT_AT_set_POWER(ptr);
			break;							
		case AT_POWER_REQ:
			error = HT_AT_get_POWER();
			break;
		case AT_CHMASK:
			error = HT_AT_set_CHMASK(ptr);
			break;							
		case AT_CHMASK_REQ:
			error = HT_AT_get_CHMASK();
			break;
		case AT_RMVCHMASK:
			error = HT_AT_rmv_CHMASK(ptr);
			break;							
		case AT_NWKMODE:
			error = HT_AT_set_NWKMODE(ptr);
			break;
		case AT_NWKMODE_REQ:
			error = HT_AT_get_NWKMODE();
			break;
		case AT_JOIN:
			error = HT_AT_JOIN();
			break;
		case AT_JOIN_REQ:
			error = HT_AT_get_JOIN_STATUS();
			break;
		case AT_SEND:
			error = HT_AT_SEND(ptr);
			break;
		case AT_SEND_HEX:
			error = HT_AT_SEND_HEX(ptr);
			break;				
		case AT_RCV:
			error=HT_AT_RCV();
			break;
		case AT_STATS:
			error=HT_AT_STATS();
			break;
			default:


			break;
	}
//	case AT_BLE_TEST_PACKET_CMD:

//		error = HT_AT_BleTestPktCmd(ptr);
//		break;
//	case AT_BLE_CONNECTABLE_CMD:

//		error = HT_AT_BleSetConnectableCmd(ptr);
//		break;
//	case AT_BLUENRG_DEEP_SLEEP_CMD:

//		error = HT_AT_BleDeepSleepCmd(ptr);
//		break;
//	case AT_CFG_WKP_PIN:

//		error = HT_AT_BleCfgWkpPinCmd(ptr);
//		break;

//	case AT_STSAFE_INTERFACE_CMD:

//		error = HT_AT_StsafeTestCmd(ptr);
//		break;

//	case AT_RTC_WKP:

//		error = HT_AT_RtcWkpCmd(ptr);
//		break;
//	default:
//		break;
//	}

	return error;
}

//static HT_AT_ErrorCode HT_AT_RtcWkpCmd(uint8_t *ptr) {
//	HT_AT_ErrorCode error = {0};
//	HT_AT_Parameter argp;
//	char argp0[6]; //(2^16)-1

//	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
//		error.at_cmd_error = AT_ERROR_PARAMETER;
//		return error;
//	}

//	memset(argp0, 0, sizeof(argp0));
//	argp.param = argp0;

//	HT_AT_SplitCommandData(ptr, (char *)PARAMETER_DELIMITER, &argp);

//	rtc_timeout = (uint32_t)atoi(argp.param);
//	if(!HT_AT_ValidRtcTimeout(rtc_timeout)) {
//		error.at_cmd_error = AT_ERROR_INVALID_TIMEOUT;
//		return error;
//	}

//	return error;
//}

//static HT_AT_ErrorCode HT_AT_StsafeTestCmd(uint8_t *ptr) {
//	HT_AT_ErrorCode error = {0};

//	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
//		error.at_cmd_error = AT_ERROR_PARAMETER;
//		return error;
//	}

//	error.at_cmd_error = HT_STSAFE_EchoCmd(ptr);

//	return error;
//}

static HT_AT_ErrorCode HT_AT_EchoCmd(uint8_t *ptr) {
	HT_AT_ErrorCode error = {0};

	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	HAL_UART_Transmit(&huart1, ptr, strlen((char *)ptr), 0xFFFF);
	printf("\n");
	return error;
}

//static HT_AT_ErrorCode HT_AT_BleCfgWkpPinCmd(uint8_t *ptr) {
//	HT_AT_ErrorCode error = {0};
//	HT_AT_Parameter argp[6];
//	char argp0[2], argp1[2], argp2[2], argp3[2], argp4[2], argp5[2];
//	uint8_t pin, edge_detection, pull, exti_type, priority;

//	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 6)) {
//		error.at_cmd_error = AT_ERROR_PARAMETER;
//		return error;
//	}

//	memset(argp0, 0, sizeof(argp0));
//	memset(argp1, 0, sizeof(argp1));
//	memset(argp2, 0, sizeof(argp2));
//	memset(argp3, 0, sizeof(argp3));
//	memset(argp4, 0, sizeof(argp4));
//	memset(argp5, 0, sizeof(argp5));

//	argp[0].param = argp0;
//	argp[1].param = argp1;
//	argp[2].param = argp2;
//	argp[3].param = argp3;
//	argp[4].param = argp4;
//	argp[5].param = argp5;

//	HT_AT_SplitCommandData(ptr, (char *)PARAMETER_DELIMITER, argp);

//	HT_AT_ParseCommandData(argp[0].param, strlen(argp[0].param), &pin);
//	if(!HT_AT_ValidPinNumber(pin)) {
//		error.at_cmd_error = AT_ERROR_INVALID_PIN_NUMBER;
//		return error;
//	}

//	if(!HT_AT_ValidGPIO(argp[1].param)) {
//		error.at_cmd_error = AT_ERROR_INVALID_GPIO;
//		return error;
//	}

//	HT_AT_ParseCommandData(argp[2].param, strlen(argp[2].param), &edge_detection);
//	if(!HT_AT_ValidEdgeDetection(edge_detection)) {
//		error.at_cmd_error = AT_ERROR_INVALID_EDGE_DETECTION;
//		return error;
//	}

//	HT_AT_ParseCommandData(argp[3].param, strlen(argp[3].param), &pull);
//	if(!HT_AT_ValidEdgePullOption(pull)) {
//		error.at_cmd_error = AT_ERROR_INVALID_PULL_OPTION;
//		return error;
//	}

//	HT_AT_ParseCommandData(argp[4].param, strlen(argp[4].param), &exti_type);
//	if(!HT_AT_ValidExtiType(exti_type)) {
//		error.at_cmd_error = AT_ERROR_INVALID_EXTI_TYPE;
//		return error;
//	}

//	HT_AT_ParseCommandData(argp[5].param, strlen(argp[5].param), &priority);
//	if(!HT_AT_ValidExtiPriority(priority)) {
//		error.at_cmd_error = AT_ERROR_INVALID_EXTI_PRIORITY;
//		return error;
//	}

//	HT_BLE_InitWkpPin(pin, argp[1].param[0], edge_detection, pull, exti_type, priority);

//	return error;
//}

//static HT_AT_ErrorCode HT_AT_BleDeepSleepCmd(uint8_t *ptr) {
//	HT_AT_ErrorCode error = {0};
//	HT_AT_Parameter argp[4];
//	char argp0[2], argp1[2], argp2[5], argp3[5];
//	uint8_t output_flag[2]; //0 = rtc, 1 = lpu
//	uint32_t pin[2]; // 0 = low polarity, 1 high polarity

//	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 4)) {
//		error.at_cmd_error = AT_ERROR_PARAMETER;
//		return error;
//	}

//	memset(argp0, 0, sizeof(argp0));
//	memset(argp1, 0, sizeof(argp1));
//	memset(argp2, 0, sizeof(argp2));
//	memset(argp3, 0, sizeof(argp3));

//	argp[0].param = argp0;
//	argp[1].param = argp1;
//	argp[2].param = argp2;
//	argp[3].param = argp3;

//	HT_AT_SplitCommandData(ptr, (char *)PARAMETER_DELIMITER, argp);

//	for (uint8_t i = 0; i < 2; i++) {
//		HT_AT_ParseCommandData(argp[i].param, strlen(argp[i].param), &output_flag[i]);
//		if(!HT_AT_ValidParameterFlag(output_flag[i])) {
//			error.at_cmd_error = AT_ERROR_PARAMETER;
//			return error;
//		}
//	}

//	for (uint8_t i = 2; i < 4; i++) {

//		error.at_cmd_error = HT_BLE_GetWkpPins(argp[i].param, &pin[i-2]);
//		if(error.at_cmd_error != AT_ERROR_NONE)
//			return error;
//	}

//	HT_BLE_SetWakeupSrc(output_flag[0], output_flag[1], pin[0], pin[1]);
//	HT_BLE_DeepSleep();

//	return error;
//}

//static HT_AT_ErrorCode HT_AT_BleSetConnectableCmd(uint8_t *ptr) {
//	HT_AT_ErrorCode error = {0};
//	uint8_t param;
//	uint8_t len;

//	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
//		error.at_cmd_error = AT_ERROR_PARAMETER;
//		return error;
//	}

//	len = strlen((char *)ptr);
//	HT_AT_ParseCommandData((char *)ptr, len, &param);

//	if(!HT_AT_ValidParameterFlag(param)) {
//		error.at_cmd_error = AT_ERROR_PARAMETER;
//		return error;
//	}

//	error.ble_error = HT_BLE_SetDeviceConnectable(param);

//	return error;
//}

//static HT_AT_ErrorCode HT_AT_BleTestPktCmd(uint8_t *ptr) {
//	HT_AT_ErrorCode error = {0};

//	if(!HT_AT_NullParameter(ptr)) {
//		error.at_cmd_error = AT_ERROR_PARAMETER;
//		return error;
//	}

//	error.ble_error = HT_BLE_TransmitTestPacket();

//	return error;
//}

