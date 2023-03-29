#ifndef INC_LORAWANSETUP_H_
#define INC_LORAWANSETUP_H_

#include <stdint.h>
#include "lora.h"
/*!
 * \brief  Initialize basic lorawan software and radio procedures, such as IRQ callback setting and lorawan activation (ABP/OTAA).
 */
void LORAWAN_init(void);
/*!
 * \brief  Function that runs at every iteration of the main "while(1)", responsible for checking flags set by other parts of the system (Timers, tx/rx callbacks) and triggering lorawan processes when necessary.
 */
void LORAWAN_tick(void);
/*!
 * \brief Set certification status
 *
 * \retval status
 *	true/false
 */
void set_certif_running(uint8_t status);

void lorawan_send(lora_AppData_t *appData);



#endif
