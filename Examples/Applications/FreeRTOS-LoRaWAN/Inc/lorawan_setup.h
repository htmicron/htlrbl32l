#ifndef INC_LORAWANSETUP_H_
#define INC_LORAWANSETUP_H_

#include <stdint.h>
#include "lora.h"
/*!
 * \brief  Initialize basic lorawan software and radio procedures, such as IRQ callback setting and lorawan activation (ABP/OTAA).
 */
void LORAWAN_init(uint8_t region);
/*!
 * \brief  Function that runs at every iteration of the main "while(1)", responsible for checking flags set by other parts of the system (Timers, tx/rx callbacks) and triggering lorawan processes when necessary.
 */
void LORAWAN_tick(void);
/*!
 * \brief  Set new LoRaWAN region.
 *
 * \param [IN] region
 *	  REGION_AS923 = 0;
 *    REGION_AU915 = 1;
 *    REGION_CN470 = 2;
 *    REGION_CN779 = 3;
 *    REGION_EU433 = 4;
 *    REGION_EU868 = 5;
 *    REGION_KR920 = 6;
 *    REGION_IN865 = 7;
 *    REGION_US915 = 8;
 *    REGION_RU864 = 9;
 */
void setRegion(uint8_t region);

/*!
 * \brief Get current LoRaWAN region
 *
 * \retval region
 *	  REGION_AS923 = 0;
 *    REGION_AU915 = 1;
 *    REGION_CN470 = 2;
 *    REGION_CN779 = 3;
 *    REGION_EU433 = 4;
 *    REGION_EU868 = 5;
 *    REGION_KR920 = 6;
 *    REGION_IN865 = 7;
 *    REGION_US915 = 8;
 *    REGION_RU864 = 9;
 */
uint8_t getRegion(void);

/*!
 * \brief Set certification status
 *
 * \retval status
 *	true/false
 */
void set_certif_running(uint8_t status);

void lorawan_send(lora_AppData_t *appData);



#endif
