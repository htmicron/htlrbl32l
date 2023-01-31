
#ifndef __HT_ATLORA_API__
#define __HT_ATLORA_API__

#include "main.h"
#include "HT_at_master.h"

#define MAX_CHANNELS_AT_ONCE 8

#define DEV_ADDR   				(uint32_t)0xDEADBEEF
#define APPSKEY					{ 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 }
#define NWKSKEY					{ 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 }
#define APP_EUI					{ 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 }
#define APPKEY					{ 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 }
#define MASK					{ 0xFF00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }
#define DEV_EUI					{ 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0xEF, 0xDE, 0xAD }
#define JOIN_CFG				ABP
#define ADR_ON					0
#define NWK_MODE				1
#define DR						0
#define JOIN_DELAY_RX1			5000
#define JOIN_DELAY_RX2			6000
#define DELAY_RX1				1000
#define DELAY_RX2				2000
#define TX_POWER				14

typedef enum{
	
	REGION_AS923 = 0,
	REGION_AU915 = 1,
    REGION_CN470 = 2,
    REGION_CN779 = 3,
    REGION_EU433 = 4,
    REGION_EU868 = 5,
    REGION_KR920 = 6,
    REGION_IN865 = 7,
    REGION_US915 = 8,
    REGION_RU864 = 9
	
}region;

typedef enum{
	OTAA = 1,
	ABP  = 0
}join_cfg;

typedef struct ABP_keys{
	uint32_t dev_add;
	uint8_t appskey[16];
	uint8_t nwkskey[16];
	
}ABP_keys;

typedef struct OTAA_keys{
	uint8_t app_eui[8];
	uint8_t app_key[16];
	
}OTAA_keys;

typedef struct rx_data{
	uint8_t* last_payload;
	uint8_t size;
	uint8_t new_data_flag;
	
}rx_data;

typedef struct rx_stats_struct{
	int8_t rssi;
	uint8_t snr;
}rx_stats;



typedef struct lora_at{
	uint8_t dev_eui[8];
	OTAA_keys otaa_keys;
	ABP_keys abp_keys;
	uint16_t channel_mask[6];
	
	uint8_t join_cfg;
	uint8_t adr;
	uint8_t nwk_mode;
	uint8_t default_dr;
	
	uint32_t join_delay_rx1;
	uint32_t join_delay_rx2;
	uint32_t delay_rx1;
	uint32_t delay_rx2;
	uint16_t rx_window_duration;
	
	uint8_t tx_power;
	uint8_t region;
	uint8_t joined;
	
	
	uint8_t restart_required;
	
	rx_data rx_data;
	rx_stats rx_stats;
}lora_at_control;


typedef enum {
    LORA_ERROR_NONE                  = 0x00,                    
    LORA_ERROR_INVALID_REGION     = 0x01,
    LORA_ERROR_RX_CONFIG              = 0x02,
	LORA_ERROR_ALREADY_JOINED= 0x03,
	LORA_ERROR_INVALID_PAYLOAD_SIZE = 0x04,
	LORA_ERROR_INVALID_FOPTS_PAYLOAD_SIZE = 0x05,
	LORA_NO_NEW_DATA = 0x06,
	LORA_ERROR_BUSY=0x07,
	LORA_ERROR_TX_TIMEOUT=0x08
} HT_AT_LoRa_ErrorCode;


HT_AT_ErrorCode HT_AT_set_DEVEUI(uint8_t *ptr); 
HT_AT_ErrorCode HT_AT_get_DEVEUI(void);
	
HT_AT_ErrorCode HT_AT_set_DEVADDR(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_DEVADDR(void);

HT_AT_ErrorCode HT_AT_set_APPSKEY(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_APPSKEY(void);

HT_AT_ErrorCode HT_AT_set_NWKSKEY(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_NWKSKEY(void);

HT_AT_ErrorCode HT_AT_set_APPEUI(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_APPEUI(void);

HT_AT_ErrorCode HT_AT_set_APPKEY(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_APPKEY(void);
	
HT_AT_ErrorCode HT_AT_set_REGION(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_REGION(void);


HT_AT_ErrorCode HT_AT_set_JOINCFG(uint8_t *ptr); 
HT_AT_ErrorCode HT_AT_get_JOINCFG(void);

HT_AT_ErrorCode HT_AT_set_ADR(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_ADR(void);

HT_AT_ErrorCode HT_AT_set_DR(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_DR(void);


HT_AT_ErrorCode HT_AT_set_JOINDELAYRX1(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_JOINDELAYRX1(void);

HT_AT_ErrorCode HT_AT_set_JOINDELAYRX2(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_JOINDELAYRX2(void);


HT_AT_ErrorCode HT_AT_set_DELAYRX1(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_DELAYRX1(void);


HT_AT_ErrorCode HT_AT_set_DELAYRX2(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_DELAYRX2(void);

HT_AT_ErrorCode HT_AT_set_WINDOW_DURATION(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_WINDOW_DURATION(void);

HT_AT_ErrorCode HT_AT_set_POWER(uint8_t *ptr);
HT_AT_ErrorCode HT_AT_get_POWER(void);

HT_AT_ErrorCode HT_AT_set_CHMASK(uint8_t *ptr); 
HT_AT_ErrorCode HT_AT_get_CHMASK(void);
HT_AT_ErrorCode HT_AT_rmv_CHMASK(uint8_t *ptr); 

HT_AT_ErrorCode HT_AT_set_NWKMODE(uint8_t *ptr); 
HT_AT_ErrorCode HT_AT_get_NWKMODE(void);

HT_AT_ErrorCode HT_AT_JOIN(void);
HT_AT_ErrorCode HT_AT_get_JOIN_STATUS(void);

HT_AT_ErrorCode HT_AT_SEND(uint8_t *ptr);

HT_AT_ErrorCode HT_AT_SEND_HEX(uint8_t *ptr);

HT_AT_ErrorCode HT_AT_RCV(void);

HT_AT_ErrorCode HT_AT_STATS(void);

void notify(void);

void restart_check(void);

uint8_t valid_region(uint8_t region);

void add_channel(uint8_t channel);

void remove_channel(uint8_t channel);

void default_mask(void);

uint8_t get_max_payload_size(void);

void report_lora_execution_error(HT_AT_LoRa_ErrorCode error_code);

uint8_t rx_config_validation(uint32_t delay_rx1, uint32_t delay_rx2,uint16_t rx_duration);

#endif /* __HT_ATLORA_API__ */
