/**
  ******************************************************************************
  * @file    bluenrg_lp_evb_io.c
  * @author  RF Application Team
  * @brief   his file provides set of firmware functions to initialize IOs 
  *          for power save modes settings
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lp_evb_io.h"
#include "rf_driver_ll_pwr.h"

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup BSP_BLUENRGLP_IO BSP BlueNRG-LP IOS
  * @{
  */ 


/** @defgroup BSP_BLUENRGLP_IO_Exported_Functions Exported Functions
  * @{
  */ 


/**
  * @brief  Configures the device IOS for power save modes 
  * @param  None
  * @retval None
  */
void BSP_IO_Init(void)
{
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO0);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO1);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO2);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO3);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO4);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO5);
  LL_PWR_EnablePUA(LL_PWR_PUPD_IO6);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO7);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO8);
  LL_PWR_EnablePUA(LL_PWR_PUPD_IO9);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO10);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO11); 
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO12);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO13); 
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO14);
  LL_PWR_EnablePDA(LL_PWR_PUPD_IO15);
  
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO0);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO1);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO2);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO3);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO4);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO5);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO6);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO7);
  LL_PWR_EnablePUB(LL_PWR_PUPD_IO8);
  LL_PWR_EnablePUB(LL_PWR_PUPD_IO9);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO10);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO11);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO14);
  LL_PWR_EnablePDB(LL_PWR_PUPD_IO15);

}


/**
  * @}
  */ 


/**
  * @}
  */  
    
/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
