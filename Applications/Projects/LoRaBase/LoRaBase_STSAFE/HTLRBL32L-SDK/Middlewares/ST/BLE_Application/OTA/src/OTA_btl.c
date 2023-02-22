/**
  ******************************************************************************
  * @file    OTA_btl.c
  * @author  AMS - RF Application team
  * @version V1.0.0
  * @date    30-April-2019
  * @brief   Bluetooth LE Over The Air (OTA) FW upgrade implementation
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "OTA_btl.h"
#include "bluenrg_lp_stack.h"
#include "ble_const.h"
#include "osal.h"
#include "math.h"
#include "gap_profile.h"
#include "rf_driver_hal_vtimer.h"
#include "bluenrg_lp_evb_config.h"
#include "bluenrg_lp_api.h"
#include <string.h>

#ifdef DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#define NUM_LINKS 1 
    
/* BLE transfer time optimization: No sync with radio activities, no connection interval update */
//#define OTA_DIRECT_WRITE 1 /* not yet supported on BLE stack v3.0 */

/* BLE OTA Server version */ 
#define BLE_OTA_SERVER_VERSION  2 /* L2CAP connection update */


#define OTA_LED BSP_LED3 /* LED turned ON  OTA session is ongoing */


/* OTA with DLE and increased ATT_MTU flags */
#define DLE_DONE     (0x01) //OTA Client has performed DLE 
#define ATT_MTU_DONE (0x02) //OTA Client has performed ATT_MTU exchange
#define DLE_ATT_MTU_DONE (DLE_DONE|ATT_MTU_DONE) //OTA Client has performed bothe DLE and ATT_MTU exchange

/** Define variables for user choice:
 *  For essential amount of status information during OTA bootloader session 
 */
//#define ST_OTA_BTL_MINIMAL_ECHO 

#define NOTIFICATION_WINDOW (8) 
#define NOTIFICATION_INTERVAL(x) (((x) == 1) || ((x) == 3)) ? 1 : (NOTIFICATION_WINDOW) //3: backward compatibility with old OTA client TBR

/* The following defines **MUST NOT** be modified for proper operation of the current OTA BTL release */
#define PAGE_SIZE      (2048)  // Flash page size
#define BYTE_INCREMENT (16)    // It's equal to max flash size we can write: 16 bytes with Flash Burst Write

#define NUM_BURST_WRITE_BYTES     (16)  //bytes on each burst write 
#define BURST_WRITE_BYTES_uS_TIME (107) //us for writing a single data burst  
    
/* Set Default max NUM_BLOCKS_X_PACKET related to the max supported OTA_ATT_MTU_SIZE from OTA Server */
#define MAX_NUM_BLOCKS_X_PACKET  ((OTA_ATT_MTU_SIZE_CONF -3 -4)/(BYTE_INCREMENT)) 
    
/* OTA FW image content MAX size related to the max supported OTA_ATT_MTU_SIZE from OTA Server */
#define IMAGE_CONTENT_SIZE ((BYTE_INCREMENT * MAX_NUM_BLOCKS_X_PACKET) + 4) /* + 4 for (OTA sequence number, check sum needs ack) */ 

/* MAX buffer size to hold only the image file data on received notification/s and to be written on flash:
   It is related to the max supported OTA_ATT_MTU_SIZE from OTA Server */
#define BUF_SIZE (((BYTE_INCREMENT * MAX_NUM_BLOCKS_X_PACKET) +4 ) * NOTIFICATION_WINDOW)  //STATIC value tailored for MAX default value for OTA_ATT_MTU_SIZE 

/**** OTA macros for defining actual OTA FW transfer paramaters related to actual OTA att mtu size agreed with OTA Client *****************/

/* Set actual NUM_BLOCKS_X_PACKET used on OTA FW data transfer: 
   OTA packet actual size = 4 bytes (OTA sequence number, check sum needs ack) + (num_block_x_packets * BYTE_INCREMENT) bytes in a single data packet */
#define NUM_BLOCKS_X_PACKET(ota_att_mtu_size) (((ota_att_mtu_size) -4)/BYTE_INCREMENT)


/* Flash burst write guard time for BYTE_INCREMENT (16) * num_block_x_packets(ota_att_mtu_size)  * NOTIFICATION_WINDOW (8 writes) bytes */
#define OTA_WRITE_GUARD_TIME(ota_att_mtu_size) (((((((((4 + (NUM_BLOCKS_X_PACKET(ota_att_mtu_size) * 16)) * NOTIFICATION_WINDOW)) / NUM_BURST_WRITE_BYTES)) * BURST_WRITE_BYTES_uS_TIME) /(1000))) +1)

#if defined(CONFIG_SW_OTA_DATA_LENGTH_EXT)
#ifdef OTA_DIRECT_WRITE
#define OTA_EXT_LE_L2CAP_CONN_INTERVAL(ota_att_mtu_size) (8)  
#else
/* Min required Connection interval, with extended packet length enabled, for handling required Flash write operations when no radio activity */
#define OTA_EXT_LE_L2CAP_CONN_INTERVAL(ota_att_mtu_size)  (((OTA_WRITE_GUARD_TIME(ota_att_mtu_size) + 4)*1000)/1250) //Added further margin for BLE communication
#endif
#endif

/* Actual data packet size related to the agreed ota_att_mtu_size */
#define DATA_PACKET_SIZE(ota_att_mtu_size)  (BYTE_INCREMENT * NUM_BLOCKS_X_PACKET(ota_att_mtu_size))

/* Actual bufPointer limit related to the agreed ota_att_mtu_size */
#define BUFPOINTER_LIMIT(ota_att_mtu_size) (DATA_PACKET_SIZE(ota_att_mtu_size) * NOTIFICATION_WINDOW)


/**** End OTA macros ******************************************/



/* OTA bootloades notification error codes */
#define OTA_SUCCESS            0x0000
#define OTA_FLASH_VERIFY_ERROR 0x003C
#define OTA_FLASH_WRITE_ERROR  0x00FF
#define OTA_SEQUENCE_ERROR     0x00F0
#define OTA_CHECKSUM_ERROR     0x000F

   
/* Characteristic handles */
uint16_t btlImageCharHandle, btlNewImageCharHandle, btlNewImageTUContentCharHandle, btlExpectedImageTUSeqNumberCharHandle;

/* OTA service & characteristic UUID 128:

OTA service: 8a97f7c0-8506-11e3-baa7-0800200c9a66
Image Characteristic: 122e8cc0-8508-11e3-baa7-0800200c9a66
New Image Characteristic: 210f99f0-8508-11e3-baa7-0800200c9a66
New Image TU Content Characteristic:2691aa80-8508-11e3-baa7-0800200c9a66
ExpectedImageTUSeqNumber Characteristic: 2bdc5760-8508-11e3-baa7-0800200c9a66
*/
#define OTA_SRVC_UUID          0x66,0x9a,0x0c,0x20,0x00,0x08,0xa7,0xba,0xe3,0x11,0x06,0x85,0xc0,0xf7,0x97,0x8a 
#define IMAGE_CHR_UUID         0x66,0x9a,0x0c,0x20,0x00,0x08,0xa7,0xba,0xe3,0x11,0x08,0x85,0xc0,0x8c,0x2e,0x12
#define NEW_IMAGE_CHR_UUID     0x66,0x9a,0x0c,0x20,0x00,0x08,0xa7,0xba,0xe3,0x11,0x08,0x85,0xf0,0x99,0x0f,0x21
#define IMAGE_CONTENT_CHR_UUID 0x66,0x9a,0x0c,0x20,0x00,0x08,0xa7,0xba,0xe3,0x11,0x08,0x85,0x80,0xaa,0x91,0x26
#define IMAGE_SEQ_NUM_CHR_UUID 0x66,0x9a,0x0c,0x20,0x00,0x08,0xa7,0xba,0xe3,0x11,0x08,0x85,0x60,0x57,0xdc,0x2b

BLE_GATT_SRV_CCCD_DECLARE(sequence_number, NUM_LINKS, BLE_GATT_SRV_CCCD_PERM_DEFAULT,
                     BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG);


/* OTA service, characteristics definition */
static const ble_gatt_chr_def_t ota_chars[] = {
    /* Image char (1ST OTA SERVICE CHARAC ALLOCATION): FREE FLASH RANGE INFOS */
    {
        .properties = BLE_GATT_SRV_CHAR_PROP_READ,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = BLE_GATT_SRV_MAX_ENCRY_KEY_SIZE,
        .uuid = BLE_UUID_INIT_128(IMAGE_CHR_UUID),
    }, 
    /* New Image char (2ND OTA SERVICE CHARAC ALLOCATION): BASE AND SIZE OF NEW IMAGE + NOTIFICATION WINDOW/DLE version */ 
    {
        .properties = BLE_GATT_SRV_CHAR_PROP_READ | BLE_GATT_SRV_CHAR_PROP_WRITE | BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = BLE_GATT_SRV_MAX_ENCRY_KEY_SIZE,
        .uuid = BLE_UUID_INIT_128(NEW_IMAGE_CHR_UUID),
    },   
    /* Image Content char (3RD OTA SERVICE CHARAC ALLOCATION) */
    {
        .properties = BLE_GATT_SRV_CHAR_PROP_READ | BLE_GATT_SRV_CHAR_PROP_WRITE | BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = BLE_GATT_SRV_MAX_ENCRY_KEY_SIZE,
        .uuid = BLE_UUID_INIT_128(IMAGE_CONTENT_CHR_UUID),
    },   
    /* Image sequence number char (4TH OTA SERVICE CHARAC ALLOCATION): IMAGE BLOCK FOR NOTIFICATION, INCLUDES NEXT EXPECTED IMAGE NUMBER AND ERROR CONDITIONS */
    {
        .properties = BLE_GATT_SRV_CHAR_PROP_NOTIFY | BLE_GATT_SRV_CHAR_PROP_READ ,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = BLE_GATT_SRV_MAX_ENCRY_KEY_SIZE,
        .uuid = BLE_UUID_INIT_128(IMAGE_SEQ_NUM_CHR_UUID),
        .descrs = {
            .descrs_p = &BLE_GATT_SRV_CCCD_DEF_NAME(sequence_number),
            .descr_count = 1U,
        },
    },
};

/* OTA Service definition */
static const ble_gatt_srv_def_t ota_service = {
   .type = BLE_GATT_SRV_PRIMARY_SRV_TYPE,
   .uuid = BLE_UUID_INIT_128(OTA_SRVC_UUID),
   .chrs = {
       .chrs_p = (ble_gatt_chr_def_t *)ota_chars,
       .chr_count = 4U,
   },
};    

struct
{
    uint16_t  replyCounter;
    uint16_t  errCode;    
} notification;

ALIGN(4) static uint8_t imageBuffer[BUF_SIZE];

uint8_t BTLServiceUUID4Scan[18]= {0x11,0x06,0x8a,0x97,0xf7,0xc0,0x85,0x06,0x11,0xe3,0xba,0xa7,0x08,0x00,0x20,0x0c,0x9a,0x66}; 

/* Let the application know whether we are in the middle of a bootloading session through a global status variable */
//uint8_t bootloadingOngoing = 0;

static uint8_t bootloadingCompleted = 0;
static uint8_t bootloadingCompleted_end = 0; 
static uint8_t ota_allow_jump = 0; 
  
/* UUIDS */
static uint32_t imageBase = 0;  
static volatile uint8_t do_erase_flash=0;  
static volatile uint8_t erase_flash_done=0;

static volatile uint8_t ota_service_is_disconnected=0;
// static uint16_t PageNumber = 0; 
    
static volatile uint8_t detected_error=0;
static volatile uint16_t write_counter=0; 

static volatile uint8_t ota_write_data = 0; 

static uint32_t imageSize = 0; 
static uint16_t bufPointer = 0;
static uint32_t totalBytesWritten = 0;
static uint8_t checksum = 0;
static uint32_t currentWriteAddress = 0;
static uint16_t expectedSeqNum = 0;

static uint8_t notification_range = NOTIFICATION_WINDOW; 
static uint16_t last_written_receivedSequence = 0;
static uint16_t receivedSeqNum;
    
static void OTA_Send_Ack(void);

static void OTA_Write_Data(void); 

static uint16_t conn_handle; 

static uint8_t imageinfo[9] = {BLE_OTA_SERVER_VERSION,0,0,0,0,0,0,0,0}; //BLE OTA DLE server version 
static uint32_t currentImageInfos[2];
static uint8_t imageData[IMAGE_CONTENT_SIZE];

/* Actual OTA mtu size agreed with OTA client: default is OTA_ATT_MTU_SIZE
   if OTA CLient doesn't support extended data lenght */
static uint16_t ota_att_mtu_size =  OTA_ATT_MTU_SIZE_CONF; 

/* Flag for register if OTA Client has performed DLE and ATT_MTU exchange config */
static volatile uint8_t client_DLE_ATT_MTU = 0; 

/**
 * @brief  It jumps to the new upgraded application
 * @param  None
 * @retval None
 *
 * @note The API code could be subject to change in future releases.
 */
void OTA_Jump_To_New_Application()
{
  /* Reset manager will take care of running the new application */
  NVIC_SystemReset(); 
}

/**
 * @brief  It jumps to the OTA Service Manager application
 * @param  None
 * @retval None
 *
 * @note The API code could be subject to change in future releases.
 */
void OTA_Jump_To_Service_Manager_Application()
{
#if defined(CONFIG_OTA_USE_SERVICE_MANAGER)
  extern RAM_VR_TypeDef RAM_VR; 
  RAM_VR.OTAActivation = OTA_APP_SWITCH_OP_CODE_GO_TO_OTA_SERVICE_MANAGER; 
  
  NVIC_SystemReset();
#endif
}
  
/**
 * @brief  It just informs OTA manager of disconnection complete event in order to
 *         jump to new application
 * @param  None
 * @retval None
 *
 * @note The API code could be subject to change in future releases.
 */  
void OTA_terminate_connection(void)
{
  bootloadingCompleted_end = ota_allow_jump; 
}

/**
 * @brief  It returns the OTA upgrade fw status
 * @param  None
 * @retval 1 if OTA upgrade session has been completed; 0 otherwise
 *
 * @note The API code could be subject to change in future releases.
 */
uint8_t OTA_Tick()
{
  if (bootloadingCompleted) 
  { 
    bootloadingCompleted = 0; 
    PRINTF("** Over The Air BLE  FW upgrade completed with success! *****************\r\n");
    PRINTF("** Application is JUMPING to new base address: 0x%08X *********************\r\n",(unsigned int)imageBase);
    /*  Turn off radio activity mask */
    aci_hal_set_radio_activity_mask(0x0000);
    /* Terminate connection with option to performs pending operations on stack queue */
    aci_gap_terminate(conn_handle, 0x93);
  }
  
  return (bootloadingCompleted_end);
}

static void OTA_Set_Application_Tag_Value(uint32_t address,uint32_t Data)
{
  LL_FLASH_Program(FLASH, address + OTA_TAG_VECTOR_TABLE_ENTRY_OFFSET, Data);
}

/**
 * @brief  It sets the related OTA application
 *         validity tags for handling the proper jumping to the valid application. 
 * @param  None
 * @retval None
 *
 * @note The API code could be subject to change in future releases.
 */
static void OTA_Set_Validity_Tags(void) 
{
  /* Based on the application type, the application validity tag is set */
  if (OTA_OP_CODE == OTA_APP_SWITCH_OP_CODE_GO_TO_LOWER_APP) // Lower Application OTA done with success  
  {
    /* Set valid tag x lower application (the new application just successfully upgraded through OTA) */
    OTA_Set_Application_Tag_Value(APP_LOWER_ADDRESS, OTA_VALID_TAG);
    
    /* Set invalid/old tag for old higher application */
    OTA_Set_Application_Tag_Value(APP_HIGHER_ADDRESS, OTA_INVALID_OLD_TAG); 
  }
  else if (OTA_OP_CODE == OTA_APP_SWITCH_OP_CODE_GO_TO_HIGHER_APP) // Higher Application OTA done with success  
  {
    /* Set valid tag x higher application (the new application just successfully upgraded through OTA) */
    OTA_Set_Application_Tag_Value(APP_HIGHER_ADDRESS, OTA_VALID_TAG);
    
    /* Set invalid/old tag for old lower application */
    OTA_Set_Application_Tag_Value(APP_LOWER_ADDRESS, OTA_INVALID_OLD_TAG); 
  }
  else if (OTA_OP_CODE == OTA_APP_SWITCH_OP_CODE_GO_TO_NEW_APP) // OTA Service Manager has upgraded a new application with success  
  {
    /* Set valid tag x the new application just successfully upgraded through OTA */
    OTA_Set_Application_Tag_Value(APP_WITH_OTA_SERVICE_ADDRESS, OTA_VALID_TAG);
  }
  
}


/**
 * @brief  Verifies flash content.
 * @param  currentWriteAddress: beginning of written address
 *         pbuffer: target buffer address
 *         size: buffer size
 * @retval Status.
 *
 * @note The API code could be subject to change in future releases.
 */
static ErrorStatus FLASH_Verify(uint32_t currentWriteAddress,uint32_t * pbuffer,uint8_t size)
{
  uint8_t * psource = (uint8_t*) (currentWriteAddress);
  uint8_t * pdest   = (uint8_t*) pbuffer;
  
  for(;(size>0) && (*(psource++) == *(pdest++)) ;size--);
  
  if (size>0)
  {
    return (ErrorStatus) (ERROR);
  }
  else
  {
    return (ErrorStatus) (SUCCESS);
  }
}

/**
 * @brief  Init OTA
 * @param  None.
 * @retval Value indicating success or error code.
 *
 * @note The API code could be subject to change in future releases.
 */
static void OTA_Init(void)
{
  BSP_LED_Init(OTA_LED); //bootloader is ongoing led
}

/**
 * @brief  Add the 'OTABootloader' service.
 * @param  None.
 * @retval Value indicating success or error code.
 *
 * @note The API code could be subject to change in future releases.
 */
tBleStatus OTA_Add_Btl_Service(void)
{
    tBleStatus ret;
    
    OTA_Init();
    /* Define OTA service */
    ret = aci_gatt_srv_add_service((ble_gatt_srv_def_t *)&ota_service);
    if (ret != BLE_STATUS_SUCCESS)
    {
        goto fail;
    }
    
    /* Add btlImageCharHandle */
    btlImageCharHandle = aci_gatt_srv_get_char_decl_handle((ble_gatt_chr_def_t *)&ota_chars[0]);

    /* Add btlNewImageCharHandle */
    btlNewImageCharHandle = aci_gatt_srv_get_char_decl_handle((ble_gatt_chr_def_t *)&ota_chars[1]);

    /* Add btlNewImageTUContentCharHandle */	
    btlNewImageTUContentCharHandle = aci_gatt_srv_get_char_decl_handle((ble_gatt_chr_def_t *)&ota_chars[2]);
    
    /* Add btlExpectedImageTUSeqNumberCharHandle */	
    btlExpectedImageTUSeqNumberCharHandle = aci_gatt_srv_get_char_decl_handle((ble_gatt_chr_def_t *)&ota_chars[3]);
#ifdef ST_OTA_BTL_ECHO  
    PRINTF("Service OTA added. Image Charac handle: 0x%04X, New Image Charac handle: 0x%04X, Image Content Charac handle: 0x%04X, Image Seq Number Charac handle: 0x%04X\n",
            btlImageCharHandle, btlNewImageCharHandle,btlNewImageTUContentCharHandle,btlExpectedImageTUSeqNumberCharHandle);
#endif 

  return BLE_STATUS_SUCCESS; 

 fail:
  PRINTF("Error while adding OTA service.\n");
  return BLE_STATUS_ERROR ;
} /* end OTA_Add_Btl_Service() */


static void OTA_Check_Update_Error_Condition(uint8_t notification_range)
{
  tBleStatus ret;
  
  /* Check if the notification reporting the error condition can be sent  
     (notification are sent inline with the expected notification window) */
  if (((write_counter+1) % notification_range) == 0) 
  {              
     //ret = aci_gatt_update_char_value_ext(conn_handle, btlExpectedImageTUSeqNumberCharHandle, 1,4, 0, 4,(uint8_t*)&notification);
     ret = aci_gatt_srv_notify(conn_handle, btlExpectedImageTUSeqNumberCharHandle + 1, 0, 4, (uint8_t *)&notification); 
     if (ret != BLE_STATUS_SUCCESS)
       PRINTF("Error while updating  characteristic.\n");
    
     detected_error = 0;
     write_counter = 0; 
  } 
}

static void OTA_Set_Error_Flags(uint8_t error_condition, uint16_t expectedSeqNum)
{
  /* Set error flag */
   detected_error = 1;
   
   /* Set checksum error with expected sequence number */
   notification.errCode = error_condition;
   notification.replyCounter = expectedSeqNum;
}

/* it sends the ack to OTA client */ 
void OTA_Send_Ack(void)
{
   tBleStatus ret;
   
  /* Depending on outcome of code section above send notification related to: 
  * next sequence number *OR* flash write failure *OR* verify failure 
  */
  ret = aci_gatt_srv_notify(conn_handle, btlExpectedImageTUSeqNumberCharHandle + 1, 0, 4, (uint8_t *)&notification);  
  
  if (ret != BLE_STATUS_SUCCESS)
  {
    PRINTF("Error while updating btlExpectedImageTUSeqNumberCharHandle characteristic.\n");
  }

  if (totalBytesWritten >= imageSize)
  { 

   /* light down led on the BlueNRG-LP platform to advertise beginning of OTA bootloading session */
   BSP_LED_Off(OTA_LED);

   /* Set the validity tags for the new app and old one */
   OTA_Set_Validity_Tags();
   /* set flag for ota fw upgrade process completed */
   bootloadingCompleted = 1;
   /* jump to new application is allowed */
   ota_allow_jump = 1; 
  }
}/* end OTA_Send_Ack() */


/* It writes the received data into OTA slave flash */
void OTA_Write_Data(void)
{
  uint8_t verifyStatus;
 
  uint16_t k;
   
  ota_write_data = 0; 
  
  /* store the potential last sequence number successfully written (if no flash write errors are detected) */
  last_written_receivedSequence = receivedSeqNum; 

  /* drop buffer into flash if it's the right time */
  currentWriteAddress = imageBase + totalBytesWritten;
  k=0;

  verifyStatus = SUCCESS;
  while (k<bufPointer)
  {
    /* don't change the OTA validity tag value during OTA upgrade session: it stays to 0xFFFFFFFF */
    if (currentWriteAddress != (imageBase + OTA_TAG_VECTOR_TABLE_ENTRY_OFFSET))
    {
       uint8_t  byteIncrement = BYTE_INCREMENT; /* Flash Burst Write: 4 words (16 bytes) */
        
       if ((bufPointer - k) >= BYTE_INCREMENT)
       {
          LL_FLASH_ProgramBurst(FLASH, currentWriteAddress, (uint32_t *)(&imageBuffer[k]));
          verifyStatus = FLASH_Verify(currentWriteAddress,(uint32_t *)(&imageBuffer[k]),BYTE_INCREMENT);
       } 
       else 
       {
         uint8_t  byteIncrement = 4; /* Flash Write: 1 word (4 bytes) */
         
         LL_FLASH_Program(FLASH, currentWriteAddress, (((uint32_t)imageBuffer[k+3]<< 24) + ((uint32_t)imageBuffer[k+2]<< 16) + ((uint32_t)imageBuffer[k+1]<< 8) + (uint32_t)imageBuffer[k]));
         verifyStatus = FLASH_Verify(currentWriteAddress,(uint32_t *)(&imageBuffer[k]),byteIncrement);
       }
       
       if (verifyStatus == SUCCESS)
       {  
          k+=byteIncrement;
          currentWriteAddress += byteIncrement;
       } 
       else
          break;
    }
    else
    {
      uint8_t  byteIncrement = 4; /* Flash Write: 1 word (4 bytes) */
      
      currentWriteAddress += byteIncrement;
      for (uint8_t index=k+4; index<k+BYTE_INCREMENT; index+=4) 
      {
        LL_FLASH_Program(FLASH, currentWriteAddress, (((uint32_t)imageBuffer[index+3]<< 24) + ((uint32_t)imageBuffer[index+2]<< 16) + ((uint32_t)imageBuffer[index+1]<< 8) + (uint32_t)imageBuffer[index]));
        verifyStatus = FLASH_Verify(currentWriteAddress,(uint32_t *)(&imageBuffer[index]),byteIncrement);
        if (verifyStatus == SUCCESS)
        {
          currentWriteAddress += byteIncrement;
        }
      }
      k+= BYTE_INCREMENT; /* skip bytes write related to OTA validity tag */  
    }
  }/* end while */
  /* prepare notification data for next expected block if for both success or notify write/verify failure */
  if (verifyStatus == SUCCESS) 
  {
    totalBytesWritten+=bufPointer;
    notification.errCode = OTA_SUCCESS;
    /* reser buffer pointer, everything was successfully written on flash */
    bufPointer = 0; 
  } 
  else 
  {
  #ifdef ST_OTA_BTL_MINIMAL_ECHO
    PRINTF("Flash verify failure \r\n");
  #endif
    notification.errCode = OTA_FLASH_VERIFY_ERROR;                
  }
 
  OTA_Send_Ack();
  
}/* end OTA_Write_Data() */


/** 
 * @brief This function handles the OTA bootloader updgrade. 
 * It is called on the aci_gatt_srv_attribute_modified_event() callback context for handling the
 * the specific characteristic write coming from the OTA Client.
 * 
 * @param Connection_Handle Handle of the connection.
 * @param attr_handle Handle of the OTA attribute that was modified.
 * @param data_length Length of att_data in octets
 * @param att_data    The modified value
 *
 * @retval None
 *
 * @note The API code could be subject to change in future releases.
 */
void OTA_Write_Request_CB(uint16_t connection_handle, 
                          uint16_t attr_handle,
                          uint8_t data_length,
                          uint8_t *att_data)
{
    tBleStatus ret;
    uint16_t k;
    
    conn_handle = connection_handle;
    
    if (attr_handle == (btlNewImageCharHandle + 1)){
      
      erase_flash_done = 0;
      ota_service_is_disconnected=0;
      
      /* Incoming write characteristic to allow master to specify the base address and size
       * of the firmware image it intends to send. 
       * Get base_address and image size + notification range requested from client.
       */
      imageSize = (uint32_t)(att_data[4] << 24) + (uint32_t)(att_data[3] << 16) + (uint32_t)(att_data[2] << 8) + att_data[1];
      imageBase = (uint32_t)(att_data[8] << 24) + (uint32_t)(att_data[7] << 16) + (uint32_t)(att_data[6] << 8) + att_data[5];
      memcpy(&imageinfo[0], &att_data[0], 9); 
      
      notification_range = NOTIFICATION_INTERVAL(att_data[0]); 

      currentWriteAddress = imageBase;
      bufPointer = 0;
      totalBytesWritten = 0;
      expectedSeqNum = 0;
#ifdef ST_OTA_BTL_MINIMAL_ECHO
      PRINTF("Free Image base = 0x%08X ; Image size = 0x%08X, numPages = %d\r\n",(unsigned int)imageBase,(unsigned int)imageSize,imageSize/PAGE_SIZE+1);
#endif  
      
      
#ifndef OTA_DIRECT_WRITE 
      /*  0x0004: "Connection event slave" */
      ret = aci_hal_set_radio_activity_mask(0x0004);
      if(ret != BLE_STATUS_SUCCESS) {
        PRINTF("aci_hal_set_radio_activity_mask()failed: 0x%02x\r\n", ret);
      }
#endif 
      
    } else  if (attr_handle == (btlExpectedImageTUSeqNumberCharHandle + 2)){

     /* Here we are handling write characteristic descriptor, switch on notifications.
      * At this point it performs required pages erase according to the previously provided image 
      * size and provide notification
      */
      expectedSeqNum = 0;

      notification.replyCounter = 0;
      notification.errCode = 0; 
      ret = aci_gatt_srv_notify(conn_handle, btlExpectedImageTUSeqNumberCharHandle + 1, 0, 4, (uint8_t *)&notification);
      if (ret != BLE_STATUS_SUCCESS) 
      {
        PRINTF("Error while updating btlExpectedImageTUSeqNumberCharHandle characteristic.\n");
      } 
      else 
      {  
        /* light up led on the BlueNRG platform to advertise beginning of OTA bootloading session */
        BSP_LED_On(OTA_LED);
        
        /* warn beginning of bootloading session through gloabal variable */
        //bootloadingOngoing = 1;
      }
      
      if (client_DLE_ATT_MTU != DLE_ATT_MTU_DONE) 
      {
        /* OTA Client doesn't perform both DLE and ATT_MTU: use DEFAULT_ATT_MTU for OTA transfer */
        ota_att_mtu_size = BLE_STACK_DEFAULT_ATT_MTU; 
      }
      
   }
    else if (attr_handle == (btlNewImageTUContentCharHandle + 1))
    {
       /* Check if a checksum or sequence number error has been detected */
       if (detected_error) 
       {
         /* An error has been detected: just count the coming next write until the end of current
            notification window: all the writes on this window must be repeated */
         write_counter += 1; 
         /* When the next expected notification from OTA client must be sent sent (inline with notification window),
            the detected error code is notified with the sequence number to be used for retrying again all the writes of this block */
         OTA_Check_Update_Error_Condition(notification_range);
       }
       /* Here we read updated characteristic content filled by "write with no response command' coming from the master */
       else if (bufPointer < BUFPOINTER_LIMIT(ota_att_mtu_size)){
         //else if (bufPointer < bufPointer_limit){
          /* Data will be received by the OTA slave 16 byte wise (due to characteristic image content = 16 bytes image + 4 of headers)
           * Drop new image data into buffer
           */
          memcpy(&imageData[0], &att_data[0], IMAGE_CONTENT_SIZE);
          for(k=bufPointer; k<(bufPointer + data_length - 4); k++){ // Store 16 bytes of received notification on imageBuffer 
             if (k<imageSize)
               imageBuffer[k] = att_data[(k - bufPointer) + 1];
             else
               /* zero pad unutilized residual*/
               imageBuffer[k] = 0;
 
             checksum ^= imageBuffer[k];
          }
          /* include header data into checksum processing as well */
          checksum ^= (att_data[data_length - 3] ^ att_data[data_length - 2] ^ att_data[data_length - 1]);          
          bufPointer = k;
          /* In the section of code below: notify for received packet integrity (cheksum), sequence number correctness
           * and eventually write flash (which will get notified as well)
          */
          
          /* check checksum */ 
          if (checksum == att_data[0]){
             /* checksum ok */      
             /* sequence number check */
             receivedSeqNum = ((att_data[DATA_PACKET_SIZE(ota_att_mtu_size) +3]<<8) + att_data[DATA_PACKET_SIZE(ota_att_mtu_size) +2]);
            
             if (expectedSeqNum == receivedSeqNum) 
             { 
               /* sequence number check ok, increment expected sequence number and prepare for next block notification */
               expectedSeqNum++;
              
               if ((att_data[DATA_PACKET_SIZE(ota_att_mtu_size) +1] == 1) || (((receivedSeqNum+1)*DATA_PACKET_SIZE(ota_att_mtu_size)) >= imageSize)) //TBR ((receivedSeqNum+1) % notification_range) or (att_data[NEEDS_ACK_INDEX] == 1)
               { 
                 /* Here is where we manage notifications related to correct sequence number and write/verify
                  * results if conditions get us through the next nested 'if' section (FLASH write section)
                  */
                 /* replyCounter defaults to expectedSeqNum unless flash write fails */
                 notification.replyCounter = expectedSeqNum;
                 notification.errCode = 0x0000;
                
                 if (((bufPointer % BUFPOINTER_LIMIT(ota_att_mtu_size)) == 0) || (((imageSize - totalBytesWritten) < BUFPOINTER_LIMIT(ota_att_mtu_size))&& (bufPointer >= (imageSize - totalBytesWritten))))
                 {
                    ota_write_data = 1;  
                    
#ifdef OTA_DIRECT_WRITE 
                   /* Perform Flash write */
                   OTA_Write_Data();            
#endif 
                 }/* end of BUF write management section*/              

               } /* end of notification window section */
             } 
             else 
             { 
                /* notify sequence number failure */
                write_counter = expectedSeqNum;
                
                /* set new expected sequence number */
                expectedSeqNum = (last_written_receivedSequence == 0) ? last_written_receivedSequence: (last_written_receivedSequence+1); 
                 
                /* Set error flags for sequence number error */
                OTA_Set_Error_Flags(OTA_SEQUENCE_ERROR,expectedSeqNum); 
                 
                /* null packet due to seq failure: remove from internal buffer through buffer pointer shift */
                bufPointer = 0;
#ifdef ST_OTA_BTL_MINIMAL_ECHO
                PRINTF("Sequence number check failed, expected frame # 0x%02X but 0x%02X was received \r\n", expectedSeqNum,receivedSeqNum);      
#endif
                /* An error has been detected just on last write of current notification window: the detected error code can be notified now
                   since OTA client is ready to get the expected notification.
                   Notification is done with the sequence number to be used for retrying again all the writes of this block */
                OTA_Check_Update_Error_Condition(notification_range);
             }            
          } /* if check sum */
          else 
          { 
             /* notify checksum failure */
             write_counter = expectedSeqNum;
            
             /* set new expected sequence number */
             expectedSeqNum = (last_written_receivedSequence == 0) ? last_written_receivedSequence: (last_written_receivedSequence+1); 
             
             /* Set error flags for checksum error*/
             OTA_Set_Error_Flags(OTA_CHECKSUM_ERROR,expectedSeqNum); 

             /* null packet due to seq failure: remove from internal buffer through buffer pointer shift */
             bufPointer = 0; 
            
#ifdef ST_OTA_BTL_MINIMAL_ECHO
             PRINTF("CheckSum error on expected frame # 0x%02X\r\n", expectedSeqNum);            
#endif
             /* An error has been detected just on last write of current notification window: the detected error code can be notified now
                since OTA client is ready to get the expected notification.
                Notification is done with the sequence number to be used for retrying again all the writes of this block */
             OTA_Check_Update_Error_Condition(notification_range);
          }
          checksum = 0;
       }
    }
}/* end OTA_Write_Request_CB() */


/**
 * @brief  It tracks the timing for next radio activity slot when connected as slave
 * @param  Next_State_SysTime time of next radio activity slot 
 * @retval None
 *
 * @note The API code could be subject to change in future releases.
 */
void OTA_Radio_Activity(uint32_t Next_State_SysTime)
{
  /* Check if data for flash write are ready: do write only if there is enough time before next radio activity */
  if (ota_write_data) 
  {
    /* Data buffer are available for Flash write */
    if (HAL_VTIMER_DiffSysTimeMs(Next_State_SysTime, HAL_VTIMER_GetCurrentSysTime()) > OTA_WRITE_GUARD_TIME(ota_att_mtu_size)) 
    {
        ota_write_data = 0; 
        OTA_Write_Data(); 
    }
  }
  
}

#if defined(CONFIG_SW_OTA_DATA_LENGTH_EXT)
void aci_att_exchange_mtu_resp_event(uint16_t Connection_Handle,
                                     uint16_t Att_MTU)
{
  //printf("ATT mtu exchanged with value = 0x%04X\n", Att_MTU);
  
  /* If OTA CLient performs an ATT_MTU exchange in order to increase ATT_MTU: 
     set actual ota_att_mtu_size used for OTA transfer and register this event */
  ota_att_mtu_size = Att_MTU -3; 
  
  client_DLE_ATT_MTU |= ATT_MTU_DONE;
}

void hci_le_data_length_change_event(uint16_t Connection_Handle,
                                     uint16_t MaxTxOctets,
                                     uint16_t MaxTxTime,
                                     uint16_t MaxRxOctets,
                                     uint16_t MaxRxTime)
{
   /* If OTA Client supports extended data length, this event is raised: set associated flag and increase connection interval
      for allowing OTA transfer with data length extension */
   
    client_DLE_ATT_MTU |= DLE_DONE; 
    /* Increase connection interval for handling BUF_SIZE Flash write operations */
    aci_l2cap_connection_parameter_update_req(Connection_Handle, (uint16_t) OTA_EXT_LE_L2CAP_CONN_INTERVAL(ota_att_mtu_size), (uint16_t) OTA_EXT_LE_L2CAP_CONN_INTERVAL(ota_att_mtu_size), 0, 100); 
}
#endif 
    

void OTA_Read_Char(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint16_t Data_Offset) 
{
    uint8_t att_err = BLE_ATT_ERR_NONE;

    if(Attribute_Handle == btlNewImageCharHandle + 1) //Read and write 
    { 
        aci_gatt_srv_resp(Connection_Handle, Attribute_Handle, att_err, sizeof(imageinfo), (uint8_t *)(&imageinfo[0]));
    }
    else if(Attribute_Handle == btlImageCharHandle + 1) //ONLY Read 
    {
        currentImageInfos[0] = OTA_FREE_SPACE_RANGE_START;
        currentImageInfos[1] = OTA_FREE_SPACE_RANGE_END;
        aci_gatt_srv_resp(Connection_Handle, Attribute_Handle, att_err, sizeof(currentImageInfos), (uint8_t *)(&currentImageInfos[0]));
    }
    else if(Attribute_Handle == btlNewImageTUContentCharHandle + 1) //Read and write 
    { 
        aci_gatt_srv_resp(Connection_Handle, Attribute_Handle, att_err, IMAGE_CONTENT_SIZE, (uint8_t *)(&imageData[0]));
    }
    else if(Attribute_Handle == btlExpectedImageTUSeqNumberCharHandle + 1) //Read and notify 
    { 
        aci_gatt_srv_resp(Connection_Handle, Attribute_Handle, att_err, 4, (uint8_t *)&notification);
    }

} /* OTA_Read_Char() */

/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
