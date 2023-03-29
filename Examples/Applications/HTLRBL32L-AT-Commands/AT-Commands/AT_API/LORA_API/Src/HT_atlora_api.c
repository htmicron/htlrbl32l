
#include "HT_atlora_api.h"
#include "sx126x.h"
#include "lorawan_setup.h"
#include "RegionUS915.h"
#include "RegionAU915.h"
#include "RegionEU868.h"
extern uint8_t uart_locked;
lora_at_control at_control = {.dev_eui=DEV_EUI,
										 .abp_keys={DEV_ADDR,APPSKEY,NWKSKEY},
										 .otaa_keys={APP_EUI,APPKEY},
										 .channel_mask=MASK,
										 .join_cfg=JOIN_CFG,
										 .adr=ADR_ON,
										 .nwk_mode=NWK_MODE,
										 .default_dr=DR,
										 .join_delay_rx1=JOIN_DELAY_RX1,
										 .join_delay_rx2=JOIN_DELAY_RX2,
										 .delay_rx1=DELAY_RX1,
										 .delay_rx2=DELAY_RX2,
										 .rx_window_duration=850,
										 .tx_power=TX_POWER,
										 .region=REGION_US915,
										 .joined =0,
										 .restart_required=1,
										 .rx_data={0,0,0},
										 .rx_stats={0,0}
										};

							
HT_AT_ErrorCode HT_AT_set_DEVEUI(uint8_t *ptr) {
	
	HT_AT_ErrorCode error = {0};
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_ValidLength(ptr,8)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error =AT_ERROR_INVALID_HEX_VALUE;
		return error;
	}
	
	HT_AT_ParseCommandData((char*)ptr, 8, at_control.dev_eui );
	
	notify();
	
	return error;
}

HT_AT_ErrorCode HT_AT_get_DEVEUI(void) {
	
	HT_AT_ErrorCode error = {0};
	for(int x=0;x<8;x++)
		printf("%02x", at_control.dev_eui[x]);
	printf("\n");
	return error;
}

HT_AT_ErrorCode HT_AT_set_DEVADDR(uint8_t *ptr){
	
	HT_AT_ErrorCode error = {0};
	char aux[5];
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_ValidLength(ptr,4)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error =AT_ERROR_INVALID_HEX_VALUE;
		return error;
	}

	HT_AT_ParseCommandData((char*)ptr, 4, (uint8_t*)aux );
		
	at_control.abp_keys.dev_add = ((unsigned int)aux[0] << 24) | ((unsigned int)aux[1] << 16) | ((unsigned int)aux[2] << 8) | ((unsigned int)aux[3]);

	notify();
	
return error;	
}

HT_AT_ErrorCode HT_AT_get_DEVADDR(void) {
	
	HT_AT_ErrorCode error = {0};
	printf("%02x\n", at_control.abp_keys.dev_add);

	return error;
}

HT_AT_ErrorCode HT_AT_set_APPSKEY(uint8_t *ptr){
	HT_AT_ErrorCode error = {0};
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_ValidLength(ptr,16)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error =AT_ERROR_INVALID_HEX_VALUE;
		return error;
	}
	
	HT_AT_ParseCommandData((char*)ptr, 16, at_control.abp_keys.appskey );
	
	notify();
	
return error;	
}

HT_AT_ErrorCode HT_AT_get_APPSKEY(void) {
	
	HT_AT_ErrorCode error = {0};
	for(int x=0;x<16;x++){
		printf("%02x", at_control.abp_keys.appskey[x]);
	}
	printf("\n");

	return error;
}

HT_AT_ErrorCode HT_AT_set_NWKSKEY(uint8_t *ptr){
	HT_AT_ErrorCode error = {0};
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_ValidLength(ptr,16)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error =AT_ERROR_INVALID_HEX_VALUE;
		return error;
	}
	
	HT_AT_ParseCommandData((char*)ptr, 16, at_control.abp_keys.nwkskey );
	
	notify();
	
return error;	
}

HT_AT_ErrorCode HT_AT_get_NWKSKEY(void) {
	
	HT_AT_ErrorCode error = {0};
	for(int x=0;x<16;x++){
		printf("%02x", at_control.abp_keys.nwkskey[x]);
	}
	printf("\n");

	return error;
}

HT_AT_ErrorCode HT_AT_set_APPEUI(uint8_t *ptr){
	HT_AT_ErrorCode error = {0};
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_ValidLength(ptr,8)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error =AT_ERROR_INVALID_HEX_VALUE;
		return error;
	}
	
	HT_AT_ParseCommandData((char*)ptr, 8, at_control.otaa_keys.app_eui);
		
	notify();
	
return error;	
}

HT_AT_ErrorCode HT_AT_get_APPEUI(void) {
	
	HT_AT_ErrorCode error = {0};
	for(int x=0;x<8;x++){
		printf("%02x", at_control.otaa_keys.app_eui[x]);
	}
	printf("\n");

	return error;
}

HT_AT_ErrorCode HT_AT_set_APPKEY(uint8_t *ptr){
	HT_AT_ErrorCode error = {0};
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_ValidLength(ptr,16)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error =AT_ERROR_INVALID_HEX_VALUE;
		return error;
	}
	
	HT_AT_ParseCommandData((char*)ptr, 16, at_control.otaa_keys.app_key);
	
	notify();
	
return error;	
}

HT_AT_ErrorCode HT_AT_get_APPKEY(void) {
	
	HT_AT_ErrorCode error = {0};
	for(int x=0;x<16;x++){
		printf("%02x", at_control.otaa_keys.app_key[x]);
	}
	printf("\n");

	return error;
}


HT_AT_ErrorCode HT_AT_set_REGION(uint8_t *ptr) {
	uint8_t aux_region;
	HT_AT_ErrorCode error = {0};

	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_ValidLength(ptr,1)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	
	aux_region = atoi((const char*)ptr);
	
	if(valid_region(aux_region)){
		
		at_control.region = aux_region;
		notify();
	}else{
		error.lora_error = LORA_ERROR_INVALID_REGION;
	}
	
	
	return error;
}
HT_AT_ErrorCode HT_AT_get_REGION(void) {
	HT_AT_ErrorCode error = {0};
	
	printf("%u\n",at_control.region);
	
	return error;
	
}

HT_AT_ErrorCode HT_AT_set_JOINCFG(uint8_t *ptr) {
	HT_AT_ErrorCode error = {0};
	uint8_t join_cfg_aux;
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_ValidLength(ptr,1)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	
	if(!HT_AT_IsHexValue(ptr[0])){
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	
	join_cfg_aux=atoi((const char*)ptr);
	
	if(!HT_AT_ValidParameterFlag(join_cfg_aux)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	
	if(HT_AT_ValidParameterFlag(join_cfg_aux)){
		at_control.join_cfg=join_cfg_aux;
		notify();
	}else{
		error.lora_error= AT_ERROR_PARAMETER;
	}
	
	return error;
}
HT_AT_ErrorCode HT_AT_get_JOINCFG(void) {
	HT_AT_ErrorCode error = {0};
	
	printf("%u\n",at_control.join_cfg);
	
	return error;
	
}


HT_AT_ErrorCode HT_AT_set_ADR(uint8_t *ptr) {
		HT_AT_ErrorCode error = {0};
		uint8_t adr_aux;
		if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
			error.at_cmd_error = AT_ERROR_PARAMETER;
			return error;
		}

		if(!HT_AT_ValidLength(ptr,1)){
			error.at_cmd_error =AT_ERROR_OVERFLOW;
			return error;
		}
		if(!HT_AT_IsHexValue(ptr[0])){
			error.at_cmd_error = AT_ERROR_PARAMETER;
			return error;
		}
		
		adr_aux= atoi((const char*)ptr);
		
		if(!HT_AT_ValidParameterFlag(adr_aux)) {
			error.at_cmd_error = AT_ERROR_PARAMETER;
			return error;
		}
		
		if(HT_AT_ValidParameterFlag(adr_aux)){
			at_control.adr=adr_aux;
			notify();
		}else{
			error.lora_error= AT_ERROR_PARAMETER;
		}
		
		return error;
}	
	

HT_AT_ErrorCode HT_AT_get_ADR(void) {
	HT_AT_ErrorCode error = {0};
	
	printf("%u\n",at_control.adr);
	
	return error;
	
}

HT_AT_ErrorCode HT_AT_set_DR(uint8_t *ptr) {
		HT_AT_ErrorCode error = {0};
		uint8_t dr_aux;
		
		if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
			error.at_cmd_error = AT_ERROR_PARAMETER;
			return error;
		}

		if(!HT_AT_IsHexValue(ptr[0])){
			error.at_cmd_error = AT_ERROR_PARAMETER;
			return error;
		}
		if(!HT_AT_ValidLength(ptr,1)){
			error.at_cmd_error =AT_ERROR_OVERFLOW;
			return error;
		}

		dr_aux = atoi((const char*)ptr);
		
		if(HT_AT_ValidParameterInterval(dr_aux,DR_0,DR_7)){
			at_control.default_dr=dr_aux;
			notify();
		}else{
			error.lora_error= AT_ERROR_PARAMETER;
		}
		
		return error;
}		

HT_AT_ErrorCode HT_AT_get_DR() {
	HT_AT_ErrorCode error = {0};
	
	printf("%u\n",at_control.default_dr);
	
	return error;
}


HT_AT_ErrorCode HT_AT_set_JOINDELAYRX1(uint8_t *ptr) {
		HT_AT_ErrorCode error = {0};
		
		if(!HT_AT_IsHexPayload((char*)ptr)){
			error.at_cmd_error = AT_ERROR_PARAMETER;
			return error;
		}
		if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
			error.at_cmd_error = AT_ERROR_PARAMETER;
			return error;
		}

		if(!HT_AT_ValidLength(ptr,6)){
			error.at_cmd_error =AT_ERROR_OVERFLOW;
			return error;
		}

	at_control.join_delay_rx1 = (uint32_t)atoi((const char*)ptr);
	
	notify();

return error;
}			
	

HT_AT_ErrorCode HT_AT_get_JOINDELAYRX1(void) {
	HT_AT_ErrorCode error = {0};

	printf("%u\n",at_control.join_delay_rx1);
return error;
}

HT_AT_ErrorCode HT_AT_set_JOINDELAYRX2(uint8_t *ptr) {
	HT_AT_ErrorCode error = {0};
	
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	if(!HT_AT_ValidLength(ptr,6)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
		}
		
	at_control.join_delay_rx2 = (uint32_t)atoi((const char*)ptr);
	
	notify();
		
return error;
}			
	

HT_AT_ErrorCode HT_AT_get_JOINDELAYRX2(void) {
	HT_AT_ErrorCode error = {0};

	printf("%u\n",at_control.join_delay_rx2);
return error;
}

HT_AT_ErrorCode HT_AT_set_DELAYRX1(uint8_t *ptr) {
	HT_AT_ErrorCode error = {0};


	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
		}

	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	if(!HT_AT_ValidLength(ptr,6)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
				

	at_control.delay_rx1 = (uint32_t)atoi((const char*)ptr);
	
	notify();
	
return error;

}
HT_AT_ErrorCode HT_AT_get_DELAYRX1() {
	HT_AT_ErrorCode error = {0};

	printf("%u\n",at_control.delay_rx1);
return error;
}
HT_AT_ErrorCode HT_AT_set_DELAYRX2(uint8_t *ptr) {
	HT_AT_ErrorCode error = {0};

	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}	
	if(!HT_AT_ValidLength(ptr,6)){
		error.at_cmd_error = AT_ERROR_OVERFLOW;
		return error;
	}
		
	at_control.delay_rx2 = (uint32_t)atoi((const char*)ptr);
	
	notify();
	
return error;

}
HT_AT_ErrorCode HT_AT_get_DELAYRX2() {
	HT_AT_ErrorCode error = {0};

	printf("%u\n",at_control.delay_rx2);
return error;
}	



HT_AT_ErrorCode HT_AT_set_WINDOW_DURATION(uint8_t *ptr) {
	
	HT_AT_ErrorCode error = {0};

	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
		}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}	
	at_control.rx_window_duration = (uint16_t)atoi((const char*)ptr);
	
	notify();
	
	return error;
		
}

HT_AT_ErrorCode HT_AT_get_WINDOW_DURATION() {
	HT_AT_ErrorCode error = {0};

	printf("%u\n",at_control.rx_window_duration);
return error;
}

HT_AT_ErrorCode HT_AT_set_POWER(uint8_t *ptr) {
	HT_AT_ErrorCode error = {0};
	uint8_t aux_power;
	
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
		}

	if(!HT_AT_ValidLength(ptr,1)){
		error.at_cmd_error = AT_ERROR_OVERFLOW;
		return error;
	}
	if(!HT_AT_IsHexValue(ptr[0])){
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	aux_power =(15- (uint8_t)atoi((const char*)ptr)); //15- to invert value
	
	if(HT_AT_ValidParameterInterval(aux_power,TX_POWER_0,TX_POWER_15)){
		at_control.tx_power=aux_power;
		notify();
	}else{
		error.lora_error= AT_ERROR_PARAMETER;
	}
		
return error;
}		

HT_AT_ErrorCode HT_AT_get_POWER() {
	HT_AT_ErrorCode error = {0};
	
	printf("%u\n",at_control.tx_power);
	
	return error;
}

HT_AT_ErrorCode HT_AT_set_CHMASK(uint8_t *ptr) {
	
	uint8_t channel;
	HT_AT_ErrorCode error = {0};
	HT_AT_Parameter argp[MAX_CHANNELS_AT_ONCE]={0};

	if(!HT_AT_IsHexValue(ptr[0])){
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	HT_AT_SplitCommandData(ptr, (char *)PARAMETER_DELIMITER, argp);
	
	for (uint8_t i = 0; i <= MAX_CHANNELS_AT_ONCE; i++) {
		if(strlen(argp[i].param)){
			channel= atoi(argp[i].param);
			if(HT_AT_ValidParameterInterval(channel,0,72)){		
				if(channel>0){
					
					add_channel(channel);
					notify();
				}
			}else{
				error.at_cmd_error = AT_ERROR_PARAMETER;
			}
		}
	}
	return error;
}

HT_AT_ErrorCode HT_AT_get_CHMASK() {
	HT_AT_ErrorCode error = {0};
	
	for(int array_size=0;array_size<6;array_size++){
		for(int element=0;element<16;element++){
			if(at_control.channel_mask[array_size] & (1<<element)){
				printf("%d ",((element+1)+(array_size*16)));
			}
		}
	}
	printf("\n");	
	return error;
}
HT_AT_ErrorCode HT_AT_rmv_CHMASK(uint8_t *ptr) {
	uint8_t channel;
	HT_AT_ErrorCode error = {0};
	HT_AT_Parameter argp[MAX_CHANNELS_AT_ONCE]={0};

	if(!HT_AT_IsHexValue(ptr[0])){
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	
	HT_AT_SplitCommandData(ptr, (char *)PARAMETER_DELIMITER, argp);

	for (uint8_t i = 0; i <= MAX_CHANNELS_AT_ONCE; i++) {
		if(strlen(argp[i].param)){
			channel= atoi(argp[i].param);
			if(HT_AT_ValidParameterInterval(channel,0,72)){		
				if(channel==0){
					default_mask();
					notify();
				}else{
					remove_channel(channel);
					notify();
				}
			}else{
				error.at_cmd_error = AT_ERROR_PARAMETER;
			}
		}
	}
	return error;
}

HT_AT_ErrorCode HT_AT_set_NWKMODE(uint8_t *ptr){
	
	HT_AT_ErrorCode error = {0};
	uint8_t nwkmode_aux;
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}
	if(!HT_AT_ValidLength(ptr,1)){
		error.at_cmd_error =AT_ERROR_OVERFLOW;
		return error;
	}
	HT_AT_ParseCommandData((char*)ptr, 1, &nwkmode_aux);
	
	if(HT_AT_ValidParameterFlag(nwkmode_aux)){
		at_control.nwk_mode=nwkmode_aux;
		notify();
	}else{
		error.lora_error= AT_ERROR_PARAMETER;
	}
		
return error;

}
HT_AT_ErrorCode HT_AT_get_NWKMODE(void) {
	HT_AT_ErrorCode error = {0};
	
	printf("%u\n",at_control.nwk_mode);
	
	return error;
}

HT_AT_ErrorCode HT_AT_JOIN(void) {
	HT_AT_ErrorCode error = {0};
	
	restart_check();
	
	if(!rx_config_validation(at_control.join_delay_rx1,at_control.join_delay_rx2,at_control.rx_window_duration)){
		error.lora_error=LORA_ERROR_RX_CONFIG;
		return error;
	}
	
	if(at_control.joined==1){
		error.lora_error=LORA_ERROR_ALREADY_JOINED;
	}else{
		uart_locked = 1;
		LORA_Join();
	}
	return error;
}
HT_AT_ErrorCode HT_AT_get_JOIN_STATUS(void) {
	HT_AT_ErrorCode error = {0};
	
	printf("%u\n",at_control.joined);
	
	return error;
}


HT_AT_ErrorCode HT_AT_SEND(uint8_t *ptr) {
	HT_AT_ErrorCode error = {0};
	lora_AppData_t appData;
	
//initializes lorawan
	
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if (!HT_AT_ValidLength(ptr, LORA_MAX_PAYLOAD_SIZE)) {
		error.at_cmd_error = AT_ERROR_OVERFLOW;
		return error;
	}

	restart_check();
	
	if(at_control.join_cfg==ABP && at_control.joined==0){ //if activation is ABP it is done automatically
		LORA_Join();
		at_control.joined = 1;
	}
	
	if(!rx_config_validation(at_control.delay_rx1,at_control.delay_rx2,at_control.rx_window_duration)){
		error.lora_error=LORA_ERROR_RX_CONFIG;
		return error;
	}
	
	
	appData.BuffSize  = strlen((const char*)ptr);
	//printf("%s\n",ptr);
	
	appData.Buff=ptr;
	appData.Port=LORAWAN_APP_PORT;
	
//	for(int x=0;x<appData.BuffSize;x++){
//		printf("%02x",appData.Buff[x]);
//	}

//	printf("\n");
	if(at_control.adr==0){
		if(appData.BuffSize>get_max_payload_size()){
			error.lora_error=LORA_ERROR_INVALID_PAYLOAD_SIZE;
			return error;
		}
	}
	uart_locked = 1;
	LORA_send( &appData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE);
	

	return error;
}

HT_AT_ErrorCode HT_AT_SEND_HEX(uint8_t *ptr) {
	HT_AT_ErrorCode error = {0};
	lora_AppData_t appData;
	
//initializes lorawan
	
	if(HT_AT_NullParameter(ptr) || !HT_AT_CheckNumberOfParameter(ptr, 1)) {
		error.at_cmd_error = AT_ERROR_PARAMETER;
		return error;
	}

	if (!HT_AT_ValidLength(ptr, (LORA_MAX_PAYLOAD_SIZE*2))) {
		error.at_cmd_error = AT_ERROR_OVERFLOW;
		return error;
	}
	if(!HT_AT_IsHexPayload((char*)ptr)){
		error.at_cmd_error =AT_ERROR_INVALID_HEX_VALUE;
		return error;
	}

	restart_check();
	
	if(at_control.join_cfg==ABP && at_control.joined==0){ //if activation is ABP it is done automatically
		LORA_Join();
		at_control.joined = 1;
	}
	
	if(!rx_config_validation(at_control.delay_rx1,at_control.delay_rx2,at_control.rx_window_duration)){
		error.lora_error=LORA_ERROR_RX_CONFIG;
		return error;
	}
	
	
	appData.BuffSize  = strlen((const char*)ptr);
	//printf("%s\n",ptr);
	
	//appData.Buff=ptr;

    unsigned int bytearray[255];
	uint8_t  buff[255];	
	appData.BuffSize=appData.BuffSize/2; //reduced number of elements by half (converted char to hex)
    for (int i = 0; i < (appData.BuffSize); i++) {
        sscanf(ptr + 2*i, "%02x", &bytearray[i]);
		buff[i]=bytearray[i];
    }
   appData.Buff=buff;

	
	appData.Port=LORAWAN_APP_PORT;
	

	if(at_control.adr==0){
		if(appData.BuffSize>get_max_payload_size()){
			error.lora_error=LORA_ERROR_INVALID_PAYLOAD_SIZE;
			return error;
		}
	}
	uart_locked = 1;
	LORA_send( &appData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE);
	

	return error;
}

HT_AT_ErrorCode HT_AT_RCV(void) {
	HT_AT_ErrorCode error={0};

	if(at_control.rx_data.new_data_flag){
			for(int x=0;x<at_control.rx_data.size;x++){
				printf("%02x",at_control.rx_data.last_payload[x]);
			}
			printf("\n");	
	at_control.rx_data.new_data_flag=0;
	}else{
			error.lora_error=LORA_NO_NEW_DATA;
	}	
	return error;
}

HT_AT_ErrorCode HT_AT_STATS(void){
	HT_AT_ErrorCode error={0};

	printf("%d %u\n",at_control.rx_stats.rssi,at_control.rx_stats.snr);
	
	return error;

}

void notify(void){
	at_control.restart_required = 1;
}

void restart_check(void){
	if(at_control.restart_required){
		LORAWAN_init();
		at_control.restart_required=0;
		at_control.joined=0;
	}
}
void remove_channel(uint8_t channel){
	uint8_t index = ((channel-1)/16);
	
	at_control.channel_mask[index] &= ~(1 << ((channel-(index*16)-1)));
	
}

void add_channel(uint8_t channel){
	
	uint8_t index = ((channel-1)/16);
	
	at_control.channel_mask[index] |= (1 << ((channel-(index*16)-1)));
	
}
void default_mask(void){
	
	memcpy(at_control.channel_mask, (uint16_t[])MASK, 6) ;

}

uint8_t valid_region(uint8_t region){
	if((region==REGION_AU915) || (region==REGION_US915) || (region==REGION_EU868)){
		return 1;
	}
	return 0;
}
uint8_t get_max_payload_size(void){
	uint8_t max_payload; //max payload without considering fopts size
	
	switch(at_control.region){
		case(REGION_AS923):
			break;
		case(REGION_AU915):
			max_payload = MaxPayloadOfDatarateDwell0AU915[at_control.default_dr];
			break;		
		case(REGION_CN470):
			break;
		case(REGION_CN779):
			break;
		case(REGION_EU433):
			break;
		case(REGION_EU868):
			max_payload = MaxPayloadOfDatarateEU868[at_control.default_dr];
			break;
		case(REGION_KR920):
			break;
		case(REGION_IN865):
			break;
		case(REGION_US915):
			max_payload = MaxPayloadOfDatarateUS915[at_control.default_dr];
			break;
		case(REGION_RU864):
			break;
		
		default:
			break;
	}
	return max_payload;
	
}

void report_lora_execution_error(HT_AT_LoRa_ErrorCode error_code){
	
	HT_AT_ErrorCode error = {0};
	error.lora_error= error_code;
	HAL_UART_Transmit(&huart1, (uint8_t *)&error, sizeof(HT_AT_ErrorCode), 0xFFFF);
	printf("\n");
}

uint8_t rx_config_validation(uint32_t delay_rx1, uint32_t delay_rx2,uint16_t rx_duration){
	rx_duration+=100; //time difference to ensure that there wont be window overlap
	if((delay_rx2 - delay_rx1) > rx_duration){
		return true;
	}
	return false;
	
}
