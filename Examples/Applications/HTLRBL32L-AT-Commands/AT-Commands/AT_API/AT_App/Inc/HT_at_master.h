
#ifndef __HT_AT_MASTER_H__
#define __HT_AT_MASTER_H__

#include "main.h"
#include "HT_uart_api.h"

/* ------------------------- Defines --------------------------- */

#define LORA_MAX_PAYLOAD_SIZE   242
#define MAX_PARAMETER_SIZE       UART_MAX_SIZE
#define MAX_ECHO_STR_SIZE       20

#define HEADER_DELIMITER        "+"
#define COMMAND_DELIMITER       "="
#define PARAMETER_DELIMITER     ":"

#define HEADER_STR              "AT+"

#define GPIOA_CH                'A'
#define GPIOB_CH                'B'

/* ------------------------- Macros --------------------------- */

#define N_CMD(tab) ((int32_t)(sizeof(tab)/sizeof(tab)[0]))

/* ------------------------------------------------------------------ */

/* ------------------------- Typedefs ------------------------------- */

typedef char AT_Command;

typedef enum {
    AT_ERROR_NONE                       = 0x00,
    AT_ERROR_UNAVAILABLE_CMD            = 0x01,
    AT_ERROR_PARAMETER                  = 0x02,
    AT_ERROR_OVERFLOW                   = 0x03,
    AT_ERROR_UNAVAILABLE_HEADER_CMD     = 0x04,
    AT_ERROR_INVALID_HEX_VALUE          = 0x05,
    AT_ERROR_INVALID_WKP_SRC            = 0x06,
    AT_ERROR_INVALID_PIN_NUMBER         = 0x07,
    AT_ERROR_INVALID_GPIO               = 0x08,
    AT_ERROR_INVALID_EDGE_DETECTION     = 0x10,
    AT_ERROR_INVALID_PULL_OPTION        = 0x11,
    AT_ERROR_INVALID_EXTI_TYPE          = 0x12,
    AT_ERROR_INVALID_EXTI_PRIORITY      = 0x13,
	AT_ERROR_STSAFE_ERROR				= 0x14,
	AT_ERROR_INVALID_TIMEOUT			= 0x15,
} HT_ATCommand_ErrorCode;

typedef enum {
    AT_BLE_TEST_PACKET_CMD = 0,
    AT_BLE_CONNECTABLE_CMD=1,
    AT_LORA_TX_CMD=2,
    AT_STSAFE_INTERFACE_CMD=3,
    AT_BLUENRG_DEEP_SLEEP_CMD=4,
    AT_CFG_WKP_PIN=5,
    AT_ECHO=6,
	AT_RTC_WKP=7,
	/*LORA*/
	AT_DEVEUI=8,
	AT_DEVEUI_REQ=9,
	AT_DEVADDR=10,
	AT_DEVADDR_REQ=11,
	AT_APPSKEY=12,
	AT_APPSKEY_REQ=13,
	AT_NWKSKEY=14,
	AT_NWKSKEY_REQ=15,
	AT_APPEUI=16,
	AT_APPEUI_REQ=17,
	AT_APPKEY=18,
	AT_APPKEY_REQ=19,
	AT_REGION=20,
	AT_REGION_REQ=21,
	AT_JOINCFG=22,
	AT_JOINCFG_REQ=23,
	AT_ADR=24,
	AT_ADR_REQ=25,
	AT_DR=26,
	AT_DR_REQ=27,
	AT_JOINDELAYRX1=28,
	AT_JOINDELAYRX1_REQ=29,
	AT_JOINDELAYRX2=30,
	AT_JOINDELAYRX2_REQ=31,
	AT_DELAYRX1=32,
	AT_DELAYRX1_REQ=33,
	AT_DELAYRX2=34,
	AT_DELAYRX2_REQ=35,
	AT_RX_WINDOW_DURATION=36,
	AT_RX_WINDOW_DURATION_REQ=37,
	AT_POWER=38,
	AT_POWER_REQ=39,
	AT_CHMASK=40,
	AT_CHMASK_REQ=41,
	AT_RMVCHMASK=42,
	AT_NWKMODE=43,
	AT_NWKMODE_REQ=44,
	AT_JOIN=45,
	AT_JOIN_REQ=46,
	AT_SEND=47,
	AT_SEND_HEX=48,
	AT_RCV=49,
	AT_STATS=50
} HT_AT_Commands;

typedef struct {
    uint8_t at_cmd_error;
    uint8_t uart_error;
    uint8_t lora_error;
    uint8_t ble_error;
} __attribute__((packed)) HT_AT_ErrorCode;

//typedef struct {
//    char* param;
//} HT_AT_Parameter;
typedef struct {
    char param[10];
} HT_AT_Parameter;
/* ------------------------- Functions --------------------------- */

void HT_AT_SplitCommandData(uint8_t *cmdBuffer, char *delim, HT_AT_Parameter *ptr);
void HT_AT_SplitCommandStr(uint8_t *input, char *delim, uint8_t *output);

void HT_AT_ParseCommandData(char *str, uint8_t len, uint8_t *output);
HT_ATCommand_ErrorCode HT_AT_ValidHeaderCommand(uint8_t *str);
HT_ATCommand_ErrorCode HT_AT_ValidCommand(uint8_t *cmd, HT_AT_Commands *cmd_id);
HT_AT_ErrorCode HT_AT_ExecuteCommand(uint8_t *ptr, HT_AT_Commands cmd);
uint8_t HT_AT_CheckErrorCode(HT_AT_ErrorCode code);
uint8_t HT_AT_GetCommandStrLen(HT_AT_Commands cmd);

uint8_t HT_AT_ValidParameterFlag(uint8_t param);
uint8_t HT_AT_CheckNumberOfParameter(uint8_t *param, uint8_t nParam);
uint8_t HT_AT_NullParameter(uint8_t *param);
uint8_t HT_AT_ValidLength(uint8_t *param, uint32_t size);
uint8_t HT_AT_ValidParameterInterval(uint8_t param,uint8_t min, uint8_t max);

uint8_t HT_AT_IsHexValue(char value);

uint8_t HT_AT_IsHexPayload(char *payload);

static HT_AT_ErrorCode HT_AT_BleTestPktCmd(uint8_t *ptr);
static HT_AT_ErrorCode HT_AT_LoraTxCmd(uint8_t *ptr);
static HT_AT_ErrorCode HT_AT_BleSetConnectableCmd(uint8_t *ptr);
static HT_AT_ErrorCode HT_AT_BleDeepSleepCmd(uint8_t *ptr);
static HT_AT_ErrorCode HT_AT_BleCfgWkpPinCmd(uint8_t *ptr);
static HT_AT_ErrorCode HT_AT_EchoCmd(uint8_t *ptr);
static HT_AT_ErrorCode HT_AT_StsafeTestCmd(uint8_t *ptr);
static HT_AT_ErrorCode HT_AT_RtcWkpCmd(uint8_t *ptr);
void HT_AT_SendInitString(void);

#endif /* __HT_AT_MASTER_H__ */
