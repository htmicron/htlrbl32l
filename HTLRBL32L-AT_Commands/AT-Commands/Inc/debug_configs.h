#ifndef __DEBUG_CONFIGS_H
#define __DEBUG_CONFIGS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUG

/*#####################################################################################

TX and RX Frequency valid values:
	9 digits. ex: 926900000

Spreading Factor valid values:
	7 to 12

Bandwidth valid values:
	0 : 125
	1 : 250
	2 : 500

Coderate valid values:
	1 : 4/5
	2 : 4/6
	3 : 4/7
	4 : 4/8
	
	TX power valid values: 	
	-9 to 22
	
	ATTENTION: leave unused defines commented
	
#####################################################################################*/

//Time between TX messages (Minimum 3000)
#define APP_TX_DUTYCYCLE 10000

#define TX_FREQUENCY 902700000

#define TX_SPREADING_FACTOR 7

#define TX_BANDWIDTH 0

#define TX_CODERATE 1

#define TX_POWER 20

#define RX_FREQUENCY 902700000

#define RX_SPREADING_FACTOR 7

#define RX_BANDWIDTH 0

#define RX_CODERATE 1

#endif
#endif
