#ifndef INC_PERIPHERALINIT_H_
#define INC_PERIPHERALINIT_H_


#define BOARD_TCXO_WAKEUP_TIME  0 // no TCXO

#define USE_SX126X_DVK

#define RADIO_NRST_Port														GPIOB
#define RADIO_NRST_Pin                            GPIO_PIN_8

#define RADIO_NSS_Port                           GPIOA
#define RADIO_NSS_Pin                            GPIO_PIN_11

#define RADIO_BUSY_Port                         GPIOB
#define RADIO_BUSY_Pin                          GPIO_PIN_15

#define RADIO_DIO1_Port												  GPIOB
#define RADIO_DIO1_Pin							              GPIO_PIN_4

#define RADIO_DEV_SEL_Port                   GPIOB
#define RADIO_DEV_SEL_Pin                    GPIO_PIN_3

#define RADIO_SWITCH_ENABLE_Port			 GPIOB
#define RADIO_SWITCH_ENABLE_Pin        GPIO_PIN_0
	

void IRQHandler_Config(void);

void MX_GPIO_Init(void);

void SystemClock_Config(void);
#endif
