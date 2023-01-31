
#ifndef __HT_UART_API_H__
#define __HT_UART_API_H__

#include "uart.h"

#define UART_BUFFER_SIZE 1
#define UART_MAX_SIZE  270

#define END_LINE_CHARACTER_1 '\n'
#define END_LINE_CHARACTER_2 '\r'
#define END_LINE_CHARACTER_3 ' '

typedef enum {
    UART_ERROR_NONE = 0x00,
    UART_ERROR_OVERFLOW = 0x01,
    UART_ERROR_UNDERFLOW = 0x02
} HT_UART_ErrorCode;

typedef enum {
    SM_WAIT_FOR_CHAR = 0,
    SM_CONFIG_UART,
    SM_WAIT_FOR_END,
    SM_RETURN_STRING,
    SM_WAIT_FOR_EXECUTION
} HT_UART_State;

void HT_UART_Fsm(void);

static void HT_UART_WaitForCharState(void);
static void HT_UART_WaitForEndState(void);
static void HT_UART_ReturnStringState(void);
static void HT_UART_WaitForExecutionState(void);

static HT_UART_ErrorCode HT_UART_AppendChar(void);
static uint8_t HT_UART_NullString(char *str);
static uint8_t HT_UART_EndCharacter(char ch);

HT_UART_ErrorCode HT_UART_GetErrorCode(void);
void HT_UART_GetUartBuffer(uint8_t *output);
uint8_t HT_UART_GetCmdLen(void);

#endif /* __HT_UART_API_H__ */
