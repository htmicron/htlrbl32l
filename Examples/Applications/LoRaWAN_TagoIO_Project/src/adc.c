#ifndef HT_SENSORS

#include "main.h"
//#include "rf_driver_ll_adc.h"
//#include "rf_driver_ll_dma.h"
//#include "adc.h"

#define USER_SAMPLERATE       (LL_ADC_SAMPLE_RATE_28)

#define USER_DATAWIDTH        (LL_ADC_DS_DATA_WIDTH_16_BIT)
#define USER_RATIO            (LL_ADC_DS_RATIO_128)

/* If USE_CALIBRATION is 1 then the internal calibration
   points are used to compensate the ADC acquired sample */
#define USE_CALIBRATION       (1)




/* Private variables ---------------------------------------------------------*/
static uint16_t aDST_Buffer[BUFFER_SIZE];
int8_t offset_vinp2 = 0;
sensor_adc sensor_adc1;

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
void APP_ADC_Init(void)
{

	
  /* Peripheral clock enable */
  LL_APB1_EnableClock(LL_APB1_PERIPH_ADCDIG | LL_APB1_PERIPH_ADCANA);

 // /* This function must not be called on QFN32 package */
  LL_ADC_LDOEnable(ADC);

  /* Enable the ADC */
  LL_ADC_Enable(ADC);

  /* Configure the sample rate */
  LL_ADC_SetSampleRate(ADC, USER_SAMPLERATE);

  /* Configure the Down Sampler data width and ratio */
  LL_ADC_ConfigureDSDataOutput(ADC, USER_DATAWIDTH, USER_RATIO);

  /* Configure the operation mode as ADC mode (static/low frequency signal) */
  LL_ADC_SetADCMode(ADC, LL_ADC_OP_MODE_ADC);

  /* Set the length of the conversion sequence as 2 */
  LL_ADC_SetSequenceLength(ADC, LL_ADC_SEQ_LEN_02);
  
  /* Set the 1st entry of the input sequence as VINP2 */
  LL_ADC_SetChannelSeq0(ADC, LL_ADC_CH_VINP2_TO_SINGLE_POSITIVE_INPUT);
  LL_ADC_SetVoltageRangeSingleVinp2(ADC, LL_ADC_VIN_RANGE_3V6);
#if (USE_CALIBRATION==1)
  if(LL_ADC_GET_CALIB_GAIN_FOR_VINPX_3V6() != 0xFFF) {
    LL_ADC_SetCalibPoint1Gain(ADC, LL_ADC_GET_CALIB_GAIN_FOR_VINPX_3V6() );
  
    offset_vinp2 = LL_ADC_GET_CALIB_OFFSET_FOR_VINPX_3V6();
    if(offset_vinp2 < -64 || offset_vinp2 > 63) {
      LL_ADC_SetCalibPoint1Offset(ADC, 0);
    }
    else {
      LL_ADC_SetCalibPoint1Offset(ADC, offset_vinp2);
      offset_vinp2 = 0;
    }
  }
  else {
    LL_ADC_SetCalibPoint1Gain(ADC, LL_ADC_DEFAULT_RANGE_VALUE_3V6);
  }
#else
  LL_ADC_SetCalibPoint1Gain(ADC, LL_ADC_DEFAULT_RANGE_VALUE_3V6);
#endif
  LL_ADC_SetCalibPointForSinglePos3V6(ADC, LL_ADC_CALIB_POINT_1);
	
	 /* Set the 2th entry of the input sequence as temperature sensor */
  LL_ADC_SetChannelSeq1(ADC, LL_ADC_CH_TEMPERATURE_SENSOR);
  
  /* Enable the temperature sensor */
  LL_PWR_EnableTempSens();
  
#if (USE_CALIBRATION==1)
  if(LL_ADC_GET_CALIB_GAIN_FOR_VINPX_1V2() != 0xFFF) {
    LL_ADC_SetCalibPoint2Gain(ADC, LL_ADC_GET_CALIB_GAIN_FOR_VINPX_1V2() );
  }
  else {
    LL_ADC_SetCalibPoint2Gain(ADC, LL_ADC_DEFAULT_RANGE_VALUE_1V2);
  }
#else
  LL_ADC_SetCalibPoint2Gain(ADC, LL_ADC_DEFAULT_RANGE_VALUE_1V2);
#endif
  LL_ADC_SetCalibPointForSinglePos1V2(ADC, LL_ADC_CALIB_POINT_2);
  
}



/**
  * @brief DMA Initialization Function
  * @param None
  * @retval None
  */
void APP_DMA_Init(void)
{
  /* Init with LL driver */
  /* DMA controller clock enable */
  LL_AHB_EnableClock(LL_AHB_PERIPH_DMA);

  /* Configure DMA request MEMTOMEM_DMA1_Channel1 */

  /* Set the DMA channel 1 with the ADC Down Sampler output */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_ADC_DS);

  /* Set transfer direction from ADC DS peripheral to RAM memory */
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  /* Set priority level */
  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);

  /* Set DMA mode */
  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);

  /* Set peripheral increment mode to no increment */
  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

  /* Set memory increment mode to increment */
  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

  /* Set peripheral data width to 16-bit */
  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);

  /* Set memory data width to 16-bit */
  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);
	
	 /* Set DMA transfer addresses of source and destination */
  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1,
                         LL_ADC_GetOutputDataRegDS(ADC),
                         (uint32_t)&aDST_Buffer,
                         LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  /* Set DMA transfer size */
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, BUFFER_SIZE);

//  /* Enable DMA transfer complete/error interrupts */
//  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);

  /* Start the DMA transfer */
  LL_ADC_DMAModeDSEnable(ADC);
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
  
  /* Start ADC conversion */
  LL_ADC_StartConversion(ADC);
}

void sensor_ADC(sensor_adc *sensor_adc1){
	
 /* Reset validation of measures */
	sensor_adc1->validation = false;
	
/* Check the ADC flag End Of Sequence of conversion */
    if( LL_ADC_IsActiveFlag_EOS(ADC) == 1) {
      /* Clear the ADC flag End Of Sequence of conversion */
      LL_ADC_ClearFlag_EOS(ADC);
    }
    
    /* Check the DMA flag Transfer Complete on channel 1 */
    if( LL_DMA_IsActiveFlag_TC1(DMA1) == 1) {
      LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
      
      /* Printout the output value */
			sensor_adc1->vpin=0;
      sensor_adc1->vpin = (float)LL_ADC_GetADCConvertedValueSingle(ADC, aDST_Buffer[0], LL_ADC_VIN_RANGE_3V6, USER_DATAWIDTH, offset_vinp2);
		
			// modified convert to %
			if(sensor_adc1->vpin > 3300) sensor_adc1->vpin = 3300;
			sensor_adc1->vpin = (100*sensor_adc1->vpin)/3300;
      //printf("ADC pin 1 %d.%03d mV\r\n", PRINT_INT(sensor_adc1->vpin),PRINT_FLOAT(sensor_adc1->vpin));
			sensor_adc1->temp =0;
      sensor_adc1->temp = LL_ADC_GetADCConvertedValueTemp(ADC, aDST_Buffer[1], USER_DATAWIDTH)/100.0;
     // printf("Temperature %d.%02d %cC\r\n\n", PRINT_INT(sensor_adc1->temp),PRINT_FLOAT(sensor_adc1->temp), 248);
			
			/* Sensor validation */
			if(sensor_adc1->temp != 0 && sensor_adc1->vpin != 0) sensor_adc1->validation = true;
			else sensor_adc1->validation = false;

      /* Clear the DMA flag Transfer Complete on channel 1 */
      LL_DMA_ClearFlag_TC1(DMA1);
      
      /* Toggle the conversion/activity LED */
      //BSP_LED_Toggle(BSP_LED1);
      
      /* Add 100 ms of delay between each sequence of measurement */
      //LL_mDelay(200);
      
      /* Restart DMA channel */
      LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&aDST_Buffer);
      LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, BUFFER_SIZE);
      LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
      
      /* Restart ADC conversion */
      LL_ADC_StartConversion(ADC);
    }
   
    /* Check the ADC flag overrun of Down Sampler */
    if( LL_ADC_IsActiveFlag_OVRDS(ADC) == 1) {
      
      /* Clear the ADC flag overrun of Down Sampler */
      LL_ADC_ClearFlag_OVRDS(ADC);

      /* Turn on the LED2 if overrun occurs */
      //BSP_LED_On(BSP_LED2);
    }

    /* Check the DMA flag Transfer Error on channel 1 */
    if( LL_DMA_IsActiveFlag_TE1(DMA1) == 1) {
      
      /* Clear the DMA flag Transfer Error on channel 1 */
      LL_ADC_ClearFlag_OVRDS(ADC);

      /* Turn on the LED2 if transfer error occurs */
     // BSP_LED_On(BSP_LED2);
    }
				
//		/* Stop ADC conversion */
//			LL_ADC_StopConversion(ADC);
//		
//		/* Disable the temperature sensor */
//			LL_PWR_DisableTempSens();
//		for(int w=0; w<10000; w++); //Necessario para que eventualmente não de erro na leitura do ADC
		

		
}

#endif

