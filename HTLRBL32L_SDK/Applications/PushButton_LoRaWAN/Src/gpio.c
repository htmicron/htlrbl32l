#include "main.h"
#include "gpio.h"
#include "radio.h"
#include "HT_push_button.h"

EXTI_HandleTypeDef HEXTI_InitStructure;
EXTI_HandleTypeDef Button_EXTI_InitStructure;

#if DEEP_SLEEP_MODE == 1
void MX_GPIO_LP_Init(void) {
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO0);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO1);
    LL_PWR_EnablePUA(LL_PWR_PUPD_IO2); //swd
    LL_PWR_EnablePUA(LL_PWR_PUPD_IO3); //swd
    LL_PWR_EnablePUA(LL_PWR_PUPD_IO4);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO5);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO6);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO7);
    LL_PWR_EnablePUA(LL_PWR_PUPD_IO8);
    LL_PWR_EnablePUA(LL_PWR_PUPD_IO9);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO10);
    LL_PWR_EnablePUA(LL_PWR_PUPD_IO11);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO12);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO13);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO14);
    LL_PWR_EnablePDA(LL_PWR_PUPD_IO15);

    LL_PWR_EnablePDB(LL_PWR_PUPD_IO0);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO1);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO2);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO3);
    LL_PWR_EnablePUB(LL_PWR_PUPD_IO4);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO5);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO6);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO7);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO8);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO9);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO10);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO11);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO12);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO13);
    LL_PWR_EnablePDB(LL_PWR_PUPD_IO14);
    LL_PWR_EnablePUB(LL_PWR_PUPD_IO15);
}
#endif

void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, RADIO_NSS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, RADIO_NRST_Pin, GPIO_PIN_SET);

    /*Configure GPIO pins : PAPin PAPin PAPin */
    GPIO_InitStruct.Pin = RADIO_NRST_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(RADIO_NRST_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = RADIO_NSS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(RADIO_NSS_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = RADIO_BUSY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(RADIO_BUSY_Port, &GPIO_InitStruct);

    HAL_NVIC_EnableIRQ(GPIOB_IRQn);

    GPIO_InitStruct.Pin = RADIO_SWITCH_ENABLE_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(RADIO_SWITCH_ENABLE_Port, &GPIO_InitStruct);
}

void IRQHandler_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_ConfigTypeDef EXTI_Config_InitStructure;

    /* Enable GPIOA and GPIOB clock */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure PB.4 pin as input floating */
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    EXTI_Config_InitStructure.Line = EXTI_LINE_PB4;
    EXTI_Config_InitStructure.Trigger = EXTI_TRIGGER_RISING_EDGE;
    EXTI_Config_InitStructure.Type = EXTI_TYPE_EDGE;

    HAL_EXTI_SetConfigLine(&HEXTI_InitStructure, &EXTI_Config_InitStructure);
    HAL_EXTI_RegisterCallback(&HEXTI_InitStructure, HAL_EXTI_COMMON_CB_ID, (void (*)(uint32_t))RadioOnDioIrq);
    HAL_EXTI_Cmd(&HEXTI_InitStructure, ENABLE);

    HAL_EXTI_ClearPending(&HEXTI_InitStructure);
    
    /* Enable and set line 10 Interrupt to the lowest priority */
    HAL_NVIC_SetPriority(GPIOB_IRQn, 2);
    HAL_NVIC_EnableIRQ(GPIOB_IRQn);

    /* Configure PA4 pin as input floating */
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    EXTI_Config_InitStructure.Line = EXTI_LINE_PA4;
    EXTI_Config_InitStructure.Trigger = EXTI_TRIGGER_FALLING_EDGE;
    EXTI_Config_InitStructure.Type = EXTI_TYPE_EDGE;

    HAL_EXTI_SetConfigLine(&Button_EXTI_InitStructure, &EXTI_Config_InitStructure);
#if DEEP_SLEEP_MODE == 0
    HAL_EXTI_RegisterCallback(&Button_EXTI_InitStructure, HAL_EXTI_COMMON_CB_ID, HT_GPIO_UserButtonHandler);
#endif
    HAL_EXTI_Cmd(&Button_EXTI_InitStructure, ENABLE);

    HAL_EXTI_ClearPending(&Button_EXTI_InitStructure);
    
    /* Enable and set line 10 Interrupt to the lowest priority */
    HAL_NVIC_SetPriority(GPIOA_IRQn, 3);
    HAL_NVIC_EnableIRQ(GPIOA_IRQn);
}

void HT_GPIO_EnableButtonIRQN(void) {
    HAL_EXTI_ClearPending(&Button_EXTI_InitStructure);
    
    /* Enable and set line 10 Interrupt to the lowest priority */
    HAL_NVIC_SetPriority(GPIOA_IRQn, 3);
    HAL_NVIC_EnableIRQ(GPIOA_IRQn);
}

#if DEEP_SLEEP_MODE == 0

void HT_GPIO_UserButtonHandler(uint32_t Line) {
    HAL_NVIC_DisableIRQ(GPIOA_IRQn);
    HT_PB_SetState(SM_PUSH_BUTTON_HANDLER);
}

#endif

void HAL_MspInit(void) {
    /* System interrupt init*/
    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0);
    __HAL_RCC_SYSCFG_CLK_ENABLE();
}
