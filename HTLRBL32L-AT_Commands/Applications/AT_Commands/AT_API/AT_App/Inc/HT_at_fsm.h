
#ifndef __HT_AT_FSM_H__
#define __HT_AT_FSM_H__

#include "main.h"

#define AT_CMD_ERROR_NONE   (uint16_t)0x0000

typedef enum {
    SM_WAIT_FOR_CMD = 0,
    SM_DECODE_CMD,
    SM_EXECUTE_CMD,
    SM_RETURN_RESULT
} HT_AT_State;

void HT_AT_Fsm(void);

static void HT_AT_WaitForCmdState(void);
static void HT_AT_DecodeCmdState(void);
static void HT_AT_ExecuteCmdState(void);
static void HT_AT_ReturnResultState(void);

extern void HT_AT_SetReceivedFlag(uint8_t val);
extern uint8_t HT_AT_GetReceivedFlag(void);

#endif /* __HT_AT_FSM_H__ */
