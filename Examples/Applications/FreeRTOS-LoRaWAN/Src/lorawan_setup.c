
#include "lorawan_setup.h"
#include "lora.h"
#include "sx126x.h"
#include "sx126x_board.h"
#include "utils.h"
#include "main.h"
static uint8_t AppDataBuff[LORAWAN_APP_DATA_BUFF_SIZE];

static uint8_t global_region;

static char regions[10][6] = {"AS923","AU915","CN470","CN779","EU433","EU868","KR920","IN865","US915","RU864"};
/*!
 * User application data structure
 */
lora_AppData_t AppData={ AppDataBuff,  0 ,0 };

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

 
/* call back when LoRa endNode has received a frame*/
static void LORA_RxData( lora_AppData_t *AppData);

/* call back when LoRa endNode has just joined*/
static void LORA_HasJoined( void );

/* call back when LoRa endNode has just switch the class*/
static void LORA_ConfirmClass ( DeviceClass_t Class );

/* call back when server needs endNode to send a frame*/
static void LORA_TxNeeded ( void );

/* start the tx process*/
static void LoraStartTx(TxEventType_t EventType);

/* tx timer callback function*/
static void OnTxTimerEvent( void* context );

//static void OnTxTesteTimer( void* context );
/* tx timer callback function*/
static void LoraMacProcessNotify( void );

/* Private variables ---------------------------------------------------------*/
/* load Main call backs structure*/
static LoRaMainCallback_t LoRaMainCallbacks = { HW_GetBatteryLevel,
                                                HW_GetTemperatureLevel,
                                                HW_GetUniqueId,
                                                HW_GetRandomSeed,
                                                LORA_RxData,
                                                LORA_HasJoined,
                                                LORA_ConfirmClass,
                                                LORA_TxNeeded,
                                                LoraMacProcessNotify};
LoraFlagStatus LoraMacProcessRequest=LORA_RESET;
LoraFlagStatus AppProcessRequest=LORA_RESET;


static TimerEvent_t TxTimer;
																																												

static  LoRaParam_t LoRaParamInit= {LORAWAN_ADR_STATE,
                                    LORAWAN_DEFAULT_DATA_RATE,
                                    LORAWAN_PUBLIC_NETWORK};

static uint8_t certif_running = false;																	
																		
void LORAWAN_init(uint8_t region){
	//disables GPIO IRQs while initializing radio to avoid fake requests
	HAL_NVIC_DisableIRQ(GPIOB_IRQn);
	//radio reset to avoid undefined behavior
	SX126xReset();
	//sets LoRaWAN region	
	setRegion(region);
	//clears LoRa Radio Interruptions
	SX126xClearIrqStatus( IRQ_RADIO_ALL );
	//Initializes LoRaWAN related variables
	LORA_Init( &LoRaMainCallbacks, &LoRaParamInit);
	//Initializes LoRaWAN join procedure(OTAA/ABP) related code
	LORA_Join();
	//clears LoRa Radio Interruptions
	SX126xClearIrqStatus( IRQ_RADIO_ALL );
	//Starts LoRaWAN periodic TX timer
	LoraStartTx( TX_ON_TIMER);
	//clear pending IRQs
	HAL_NVIC_ClearPendingIRQ(GPIOB_IRQn);
	//re-enable IRQs
	HAL_NVIC_EnableIRQ(GPIOB_IRQn);
}
void LORAWAN_tick(void){

		if (LoraMacProcessRequest==LORA_SET){
		
	        /*reset notification flag*/
			LoraMacProcessRequest=LORA_RESET;
			LoRaMacProcess( );
			
	}
	
}															

void setRegion(uint8_t region){
//	  REGION_AS923 = 0;
//    REGION_AU915 = 1;
//    REGION_CN470 = 2;
//    REGION_CN779 = 3;
//    REGION_EU433 = 4;
//    REGION_EU868 = 5;
//    REGION_KR920 = 6;
//    REGION_IN865  = 7;
//    REGION_US915 = 8;
//    REGION_RU864 = 9;
	
	if(region<10){
		  printf("Setting Region: %s\n",regions[region]);
			global_region = region;
	}else{
		printf("Invalid region parameter, reverting to region: %d\n",global_region);
	}
}
uint8_t getRegion(void){
	return global_region;
}

void lorawan_send(lora_AppData_t *appData){
	
	printf("\n-LoRaWAN TX-\n");

	if ( LORA_JoinStatus () != LORA_SET)
  {
    /*Not joined, try again later*/
    LORA_Join();
    return;
  }
	appData->BuffSize = strlen((const char*)appData->Buff);

  LORA_send( appData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE);
	

}

void LoraMacProcessNotify(void)
{
  LoraMacProcessRequest=LORA_SET;
}
static void LORA_HasJoined( void )
{
  LORA_RequestClass( LORAWAN_DEFAULT_CLASS );
}

static void LORA_RxData( lora_AppData_t *AppData ){
	
  switch (AppData->Port)
  {
    case 3:
    /*this port switches the class*/
    if( AppData->BuffSize == 1 )
    {
      switch (AppData->Buff[0])
      {
        case 0:
        {
          LORA_RequestClass(CLASS_A);
          break;
        }
        case 1:
        {
          LORA_RequestClass(CLASS_B);
          break;
        }
        case 2:
        {
          LORA_RequestClass(CLASS_C);
          break;
        }
        default:
          break;
      }
    }
    break;
    case LORAWAN_APP_PORT:

    break;
  case LPP_APP_PORT:
  {

    break;
  }
  default:
    break;
 }

}


static void LoraStartTx(TxEventType_t EventType){
	
	if (EventType == TX_ON_TIMER)
	{
	  /* send everytime timer elapses */
			//Sets callback function
	  TimerInit( &TxTimer, OnTxTimerEvent );
			//Sets alarm total time
	  TimerSetValue( &TxTimer,  APP_TX_DUTYCYCLE);
			//Callback call
			
#if( OVER_THE_AIR_ACTIVATION == 0 )
			OnTxTimerEvent( NULL );
#else	
			TimerStart(&TxTimer);
#endif

    }
}

static void OnTxTimerEvent( void* context ){
	//Starts timer
	TimerStart(&TxTimer);

	//Sets send flag = true
	lora_AppData_t appData;

	appData.Buff = (uint8_t*)"test78645";
	appData.BuffSize = strlen((const char*)appData.Buff);
	appData.Port = LORAWAN_APP_PORT;
	
	
	lorawan_send(&appData);

  }

static void LORA_ConfirmClass ( DeviceClass_t Class ){

	printf("switch to class %c done\n\r","ABC"[Class]);
    /*Optionnal*/
    /*informs the server that switch has occurred ASAP*/
    AppData.BuffSize = 0;
    AppData.Port = LORAWAN_APP_PORT;


    LORA_send( &AppData, LORAWAN_UNCONFIRMED_MSG);
}

static void LORA_TxNeeded ( void )
{
		AppData.BuffSize = 0;
    AppData.Port = LORAWAN_APP_PORT;

    LORA_send( &AppData, LORAWAN_UNCONFIRMED_MSG);
}																		

void set_certif_running(uint8_t status){
	if(!status && certif_running){   //if test mode changes to false enable TX regular cycle
			DelayMs(100);
			printf("stopped certification cycle - re-enabling regular cycle\n");
			TimerInit( &TxTimer, OnTxTimerEvent );
	TimerSetValue( &TxTimer,  APP_TX_DUTYCYCLE);
			TimerStart( &TxTimer);

	}else if(status && !certif_running){
			printf("certification cycle started - stopping regular tx timer\n");
			TimerStop(&TxTimer);
	}
	certif_running = status;
	
}

