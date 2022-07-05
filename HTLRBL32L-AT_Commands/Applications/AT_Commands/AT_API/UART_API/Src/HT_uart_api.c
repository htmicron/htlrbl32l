
#include "HT_uart_api.h"
#include "HT_at_fsm.h"

static HT_UART_State uart_state = SM_CONFIG_UART;
static HT_UART_State prev_uart_state = SM_RETURN_STRING;

HT_UART_ErrorCode uart_error = UART_ERROR_NONE;

static uint8_t rx_buffer = 0;
static uint8_t uart_buffer[UART_MAX_SIZE];
volatile uint8_t usart_callback = 0;

static uint8_t HT_UART_EndCharacter(char ch) {
    return (ch == END_LINE_CHARACTER_1 || ch == END_LINE_CHARACTER_2) ? 1 : 0;
}

static uint8_t HT_UART_NullString(char *str) {
    return (strlen(str) == 0 || (strlen(str) > 0 && (str[0] == END_LINE_CHARACTER_2 || 
                str[0] == END_LINE_CHARACTER_1 || str[0] == END_LINE_CHARACTER_3))) ? 1 : 0;
}

void HT_UART_GetUartBuffer(uint8_t *output) {
    memcpy(output, uart_buffer, UART_MAX_SIZE);
}

uint8_t HT_UART_GetCmdLen(void) {
    return strlen((char *)uart_buffer);
}

HT_UART_ErrorCode HT_UART_GetErrorCode(void) {
    return uart_error;
}

static HT_UART_ErrorCode HT_UART_AppendChar(void) {
    uint8_t len = 0;
    
    len = strlen((char *)uart_buffer);

    if((len+1) < UART_MAX_SIZE) {
        uart_buffer[len] = rx_buffer;
        uart_error = UART_ERROR_NONE;
    } else {
        uart_error = UART_ERROR_OVERFLOW;
    }

    return uart_error;
}

static void HT_UART_WaitForExecutionState(void) {
    prev_uart_state = SM_WAIT_FOR_EXECUTION;
    HAL_NVIC_DisableIRQ(USART1_IRQn);

    uart_state = !HT_AT_GetReceivedFlag() ? SM_CONFIG_UART : SM_WAIT_FOR_EXECUTION;
}

static void HT_UART_ReturnStringState(void) {

    if(HT_UART_NullString((char *)uart_buffer))  
        uart_error = UART_ERROR_UNDERFLOW;
        
    HT_AT_SetReceivedFlag(1);

    prev_uart_state = SM_RETURN_STRING;
    uart_state = SM_WAIT_FOR_EXECUTION;
}

static void HT_UART_WaitForEndState(void) {

		if(usart_callback) {
        usart_callback = 0;

        if(HT_UART_EndCharacter(rx_buffer)) { 
            uart_state = SM_RETURN_STRING;
        } else if (HT_UART_AppendChar() != UART_ERROR_NONE) { 
            uart_state = SM_RETURN_STRING;
            uart_error = UART_ERROR_OVERFLOW;
        } else {
            uart_state = SM_CONFIG_UART ;
        }
    } else{
        uart_state = SM_WAIT_FOR_END;
    }

    prev_uart_state = SM_WAIT_FOR_END;
}

static void HT_UART_WaitForCharState(void) {

    if(usart_callback) {
        usart_callback = 0;

        HT_UART_AppendChar();
        uart_state = SM_CONFIG_UART;

    } else{
        uart_state = SM_WAIT_FOR_CHAR;
    }

    prev_uart_state = SM_WAIT_FOR_CHAR;
}

static void HT_UART_ConfigUARTState(void) {
    
    rx_buffer = 0;
    HAL_UART_Receive_IT(&huart1, &rx_buffer, UART_BUFFER_SIZE);

    if(prev_uart_state == SM_WAIT_FOR_EXECUTION) {
    
        uart_state = SM_WAIT_FOR_CHAR;
        uart_error = UART_ERROR_NONE;
        usart_callback = 0;

        HAL_NVIC_EnableIRQ(USART1_IRQn);
        rx_buffer = 0;

        memset(uart_buffer, '\0', sizeof(uart_buffer));
    } else{
        uart_state = SM_WAIT_FOR_END;
    }

    prev_uart_state = SM_CONFIG_UART;
}

void HT_UART_Fsm(void) {

    switch (uart_state) {
    case SM_CONFIG_UART:
        HT_UART_ConfigUARTState();
        break;
    case SM_WAIT_FOR_CHAR:
        HT_UART_WaitForCharState();
        break;
    case SM_WAIT_FOR_END:
        HT_UART_WaitForEndState();
        break;
    case SM_RETURN_STRING:
        HT_UART_ReturnStringState();
        break;
    case SM_WAIT_FOR_EXECUTION:
        HT_UART_WaitForExecutionState();
        break;
    }

}
