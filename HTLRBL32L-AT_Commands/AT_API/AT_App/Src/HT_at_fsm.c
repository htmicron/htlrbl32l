
#include "HT_at_fsm.h"
#include "HT_at_master.h"


HT_AT_State at_state = SM_WAIT_FOR_CMD;

uint8_t uart_locked = 0;

volatile uint8_t cmd_received = 0;
static HT_AT_ErrorCode ret;

static HT_AT_Commands command;
static uint8_t cmd_param[MAX_PARAMETER_SIZE];

static void HT_AT_ResetCtrlFlags(void) {
    cmd_received = 0;
    memset((uint8_t *)&ret, 0, sizeof(HT_AT_ErrorCode));
}

void HT_AT_SetReceivedFlag(uint8_t val) {
    cmd_received = val;
}

uint8_t HT_AT_GetReceivedFlag(void) {
    return cmd_received;
}

static void HT_AT_WaitForCmdState(void) {

//	if(uart_locked){
//		printf("%u\n",uart_locked);
//	}
    if(!cmd_received || uart_locked) {
        HT_UART_Fsm();
        at_state = SM_WAIT_FOR_CMD;
    } else  {
        at_state = SM_DECODE_CMD;
    }
}

static void HT_AT_DecodeCmdState(void) {
    uint8_t cmd_str[UART_MAX_SIZE];

    memset(cmd_str, 0, UART_MAX_SIZE);
    HT_UART_GetUartBuffer(cmd_str);

    ret.uart_error = HT_UART_GetErrorCode();
    
    if(ret.uart_error == UART_ERROR_NONE) {                               //check command string
        ret.at_cmd_error = HT_AT_ValidHeaderCommand(cmd_str);        
        if(ret.at_cmd_error == AT_ERROR_NONE) {                               //check command header
            ret.at_cmd_error = HT_AT_ValidCommand(&cmd_str[3], &command);     
            if(ret.at_cmd_error == AT_ERROR_NONE) {                           //check command parameter
                memset(cmd_param, 0, MAX_PARAMETER_SIZE);
                strcpy((char *)cmd_param, &cmd_str[HT_AT_GetCommandStrLen(command)+4]); //get parameter: AT+<CMD_STRING>=
            }
        } 
    } 

    at_state = HT_AT_CheckErrorCode(ret) ? SM_EXECUTE_CMD : SM_RETURN_RESULT;
}

static void HT_AT_ExecuteCmdState(void) {

    ret = HT_AT_ExecuteCommand(cmd_param, command);
    at_state = SM_RETURN_RESULT;
}

static void HT_AT_ReturnResultState(void) {

    HAL_UART_Transmit(&huart1, (uint8_t *)&ret, sizeof(HT_AT_ErrorCode), 0xFFFF);
	printf("\n");

    HT_AT_ResetCtrlFlags();
    at_state = SM_WAIT_FOR_CMD;
}

void HT_AT_Fsm(void) {

    switch (at_state) {
    case SM_WAIT_FOR_CMD:
        HT_AT_WaitForCmdState();
        break;
    case SM_DECODE_CMD:
        HT_AT_DecodeCmdState();
        break;
    case SM_EXECUTE_CMD:
        HT_AT_ExecuteCmdState();
        break;
    case SM_RETURN_RESULT:
        HT_AT_ReturnResultState();
        break;
    default:
        break;
    }
}
