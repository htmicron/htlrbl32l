/******************** (C) COPYRIGHT 2018 STMicroelectronics ********************
* File Name          : system_Bluenrg_LP.c
* Author             : AMG - RF Application team
* Version            : V1.0.0
* Date               : 12-December-2018
* Description        : BlueNRG-LP Low Level Init function
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"
#include "system_BlueNRG_LP.h"
#include "rf_driver_ll_rcc.h"
#include "rf_driver_ll_pwr.h"
#include "rf_driver_ll_flash.h"
#include "rf_driver_ll_bus.h"
#include "rf_driver_ll_system.h"
#include "stdio.h"
/* Private constants ---------------------------------------------------------*/

#ifndef CONFIG_NUM_MAX_LINKS
#define CONFIG_NUM_MAX_LINKS 8
#endif 


/* OTA tag used to  tag a  valid application on interrupt vector table*/
#if defined (CONFIG_OTA_SERVICE_MANAGER)
#define OTA_VALID_APP_TAG (0xAABBCCDD) /* OTA Service Manager has a special valid tag */
#else
#define OTA_VALID_APP_TAG (0xAA5555AA) 
#endif

#define SYSCLK_EQUAL_BLECLK          0x28
#define SYSCLK_DOUBLE_BLECLK         0x29
#define SYSCLK_FOURFOLD_BLECLK       0x2A

#define AHB_STALLED   0x08

/* TRIMMING Defines */
#define VALIDITY_TAG 0xFCBCECCC

#define VALIDITY_LOCATION    0x10001EF8
#define TRIMMING_LOCATION    0x10001EE4
#define MR_TRIMMING_LOCATION 0x10001EE8

#define MAIN_REGULATOR_TRIM_Pos (0)
#define MAIN_REGULATOR_TRIM_Msk (0x0F << MAIN_REGULATOR_TRIM_Pos)
#define SMPS_TRIM_Pos           (4)
#define SMPS_TRIM_Msk           (0x07 << SMPS_TRIM_Pos)
#define LSI_LPMU_TRIM_Pos       (8)
#define LSI_LPMU_TRIM_Msk       (0x0F << LSI_LPMU_TRIM_Pos)
#define LSI_BW_TRIM_Pos         (12)
#define LSI_BW_TRIM_Msk         (0x0F << LSI_BW_TRIM_Pos)
#define HSI_TRIM_Pos            (16)
#define HSI_TRIM_Msk            (0x3F << HSI_TRIM_Pos)

#define MR_BLE_IBIAS_TRIM_Pos         (8)
#define MR_BLE_IBIAS_TRIM_Msk         (0x0F << MR_BLE_IBIAS_TRIM_Pos)
#define MR_BLE_IPTAT_TRIM_Pos         (12)
#define MR_BLE_IPTAT_TRIM_Msk         (0x0F << MR_BLE_IPTAT_TRIM_Pos)
#define MR_BLE_VBG_TRIM_Pos           (16)
#define MR_BLE_VBG_TRIM_Msk           (0x0F << MR_BLE_VBG_TRIM_Pos)
#define MR_BLE_RXADC_DELAY_I_TRIM_Pos (20)
#define MR_BLE_RXADC_DELAY_I_TRIM_Msk (0x07 << MR_BLE_RXADC_DELAY_I_TRIM_Pos)
#define MR_BLE_RXADC_DELAY_Q_TRIM_Pos (24)
#define MR_BLE_RXADC_DELAY_Q_TRIM_Msk (0x07 << MR_BLE_RXADC_DELAY_Q_TRIM_Pos)

/* AGC Configuration */
#define AGC_THR0 (0x0A)
#define AGC_THR1 (0x04)
#define AGC_ATT0 (0x00)
#define AGC_ATT1 (0x10)
#define AGC_ATT2 (0x20)
#define AGC_ATT3 (0x30)
#define AGC_ATT4 (0x38)
#define AGC_ATT5 (0x39)
#define AGC_ATT6 (0x3A)
#define AGC_ATT7 (0x3B)
#define AGC_ATT8 (0x3C)
#define AGC_ATT9 (0x3D)
/* AFC Configuration */
#define AFC_DELAY_BEFORE    (0x05)
#define AFC_DELAY_AFTER     (0x05)   
#define CR_GAIN_BEFORE      (0x06)
#define CR_GAIN_AFTER       (0x06)
#define CR_LR_GAIN_BEFORE   (0x05)
#define CR_LR_GAIN_AFTER    (0x05)
#define LR_RSSI_THR         (0x1D)
#define LR_PD_THR           (0x59)
#define LR_AAC_THR          (0x32)


/* Private types -------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
uint32_t SystemCoreClock  = 32000000U; /*CPU: HSI clock after startup (64MHz)*/

/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t SmpsTrimConfig(void);
static uint8_t LSConfig(void);

int __low_level_init(void);
void RESET_HANDLER(void);
void CS_contextRestore(void);

/* Exported function prototypes ---------------------------------------------*/
/* Weak Function declaration for all the Interrupt Handler */
WEAK_FUNCTION(void NMI_IRQHandler(void)) {}
WEAK_FUNCTION(void HardFault_IRQHandler(void)) {}
WEAK_FUNCTION(void SVC_IRQHandler(void)) {}
WEAK_FUNCTION(void PendSV_IRQHandler(void)) {}                         
WEAK_FUNCTION(void SysTick_IRQHandler(void)) {}
WEAK_FUNCTION(void FLASH_IRQHandler(void)) {}
WEAK_FUNCTION(void RCC_IRQHandler(void)) {}
WEAK_FUNCTION(void PVD_IRQHandler(void)) {}
WEAK_FUNCTION(void I2C1_IRQHandler(void)) {}
#if defined(I2C2) 
WEAK_FUNCTION(void I2C2_IRQHandler(void)) {}
#endif
#if defined(SPI1) 
WEAK_FUNCTION(void SPI1_IRQHandler(void)) {}
#endif
#if defined(SPI2) 
WEAK_FUNCTION(void SPI2_IRQHandler(void)) {}
#endif
WEAK_FUNCTION(void SPI3_IRQHandler(void)) {}
WEAK_FUNCTION(void USART1_IRQHandler(void)) {}
WEAK_FUNCTION(void LPUART1_IRQHandler(void)) {}
#if defined(TIM1)
WEAK_FUNCTION(void TIM1_IRQHandler(void)) {}
#endif
#if defined(TIM2)
WEAK_FUNCTION(void TIM2_IRQHandler(void)) {}
#endif
WEAK_FUNCTION(void RTC_IRQHandler(void)) {}
WEAK_FUNCTION(void ADC_IRQHandler(void)) {}
WEAK_FUNCTION(void PKA_IRQHandler(void)) {}
WEAK_FUNCTION(void UPCONV_IRQHandler(void)) {}
WEAK_FUNCTION(void GPIOA_IRQHandler(void)) {}
WEAK_FUNCTION(void GPIOB_IRQHandler(void)) {}
WEAK_FUNCTION(void DMA_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_TX_RX_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_AES_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_ERROR_IRQHandler(void)) {}
WEAK_FUNCTION(void RADIO_CTRL_IRQHandler(void)) {}
WEAK_FUNCTION(void MR_BLE_IRQHandler(void)) {}
WEAK_FUNCTION(void CPU_WKUP_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_WKUP_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_RXTX_SEQ_IRQHandler(void)) {}
#if defined(TIM16)
WEAK_FUNCTION(void TIM16_IRQHandler(void)) {}
#endif
#if defined(TIM17)
WEAK_FUNCTION(void TIM17_IRQHandler(void)) {}
#endif

/* Weak Function declaration for the Context Restore */
WEAK_FUNCTION(void CS_contextRestore(void)) {} 

/* Exported variables ---------------------------------------------------------*/
NO_INIT_SECTION(REQUIRED(RAM_VR_TypeDef RAM_VR), ".ram_vr");

/* BLUE RAM, reserved for radio communication. Not usable from the application */
SECTION(".bss.__blue_RAM")
REQUIRED(uint8_t __blue_RAM[CONFIG_NUM_MAX_LINKS*80+28]) = {0,};


/*************************************************************************************
 **
 ** Should add all the variable to manage the Context restore and OTA procedures!!!!!!!! 
 **
 **************************************************************************************/
/* Exported function prototypes ---------------------------------------------*/
/* Low Level Init function */
int __low_level_init(void) 
{
  /* If the reset reason is a wakeup from DEEPSTOP restore the context */
  if ((RCC->CSR == 0) && ((PWR->SR1 != 0)||(PWR->SR3 != 0))) {
#ifndef NO_SMART_POWER_MANAGEMENT
    RAM_VR.WakeupFromSleepFlag = 1; /* A wakeup from DEEPSTOP occurred */
    CS_contextRestore();            /* Restore the context */
    /* if the context restore worked properly, we should never return here */
    while(1) { 
      NVIC_SystemReset(); 
    }
#else
    return 0;
#endif   
  }
  return 1;
}

#ifdef __CC_ARM
__attribute__((noreturn)) void RESET_HANDLER(void)
{
  if(__low_level_init()==1)
    __main();
  else {
    __set_MSP((uint32_t)_INITIAL_SP);
    main();
  }
  while(1);
}
#else
#ifdef __GNUC__

#include <stdint.h>
#include <errno.h>

extern unsigned long _etext;
extern unsigned long _sidata;       /* start address for the initialization values of the .data section. Defined in linker script */
extern unsigned long _sdata;        /* start address for the .data section. Defined in linker script */
extern unsigned long _edata;        /* end address for the .data section. Defined in linker script */
extern unsigned long _sbss;         /* start address for the .bss section. Defined in linker script */
extern unsigned long _ebss;         /* end address for the .bss section. Defined in linker script */
extern unsigned long _sbssblue;     /* start address for the section reserved for the Blue controller. Defined in linker script */
extern unsigned long _ebssblue;     /* end address for the section reserved for the Blue controller. Defined in linker script */
extern unsigned long _estack;       /* init value for the stack pointer. Defined in linker script */
extern unsigned long _sidata2;      /* start address for the initialization values of the special ram_preamble */
extern unsigned long _sdata2;       /* start address the special ram_preamble defined in linker script */
extern unsigned long _edata2;       /* end address the special ram_preamble defined in linker script */
extern uint8_t _sheap;              /* start address for the .heap section. Defined in linker script */
extern uint8_t _eheap;              /* end address for the .heap section. Defined in linker script */

extern int main(void);

void RESET_HANDLER(void)
{
  if(__low_level_init()==1)	{
    unsigned long *pulSrc, *pulDest;

    // Copy the data segment initializers from flash to SRAM.
    pulSrc = &_sidata;
    for(pulDest = &_sdata; pulDest < &_edata; )
    {
      *(pulDest++) = *(pulSrc++);
    }

    // Zero fill the bss segment.
    for(pulDest = &_sbssblue; pulDest < &_ebssblue; )
    {
      *(pulDest++) = 0;
    }

    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
      *(pulDest++) = 0;
    }
  }
  // Call the application's entry point.
  __set_MSP((uint32_t)_INITIAL_SP);
  main();
}

void * _sbrk(int32_t incr)
{
  static uint8_t *heap_end;
  uint8_t *prev_heap_end;

  if (heap_end == 0)
    heap_end = &_sheap;

  prev_heap_end = heap_end;
  if ((heap_end + incr) > (&_eheap))
  {
//    write(1, "Heap and stack collision\n", 25);
//    abort();
    errno = ENOMEM;
    return (void *) -1;
  }

  heap_end += incr;

  return prev_heap_end;
}

#endif /* __GNUC__ */
#endif /* __CC_ARM */

/* Interrupt Vector Table */
SECTION(".intvec")
REQUIRED(const intvec_elem __vector_table[]) = {
    {.__ptr = _INITIAL_SP},                   /* Stack address                      */
    {RESET_HANDLER},                    /* Reset handler is C initialization. */
    {NMI_IRQHandler},                         /* The NMI handler                    */
    {HardFault_IRQHandler},                   /* The hard fault handler             */
    {(intfunc) OTA_VALID_APP_TAG},            /* OTA Application                    */
    {(intfunc) BLUE_FLAG_TAG},                /* Reserved for blue flag DTM updater */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {SVC_IRQHandler},                         /* SVCall                             */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {PendSV_IRQHandler},                      /* PendSV                             */
    {SysTick_IRQHandler},                     /* SysTick_IRQHandler                 */
    {FLASH_IRQHandler},                       /* IRQ0:  FLASH Controller            */
    {RCC_IRQHandler},                         /* IRQ1:  RCC                         */
    {PVD_IRQHandler},                         /* IRQ2:  PVD                         */
    {I2C1_IRQHandler},                        /* IRQ3:  I2C1                        */
#if defined(I2C2)
    {I2C2_IRQHandler},                        /* IRQ4:  I2C2                        */
#else
    {0x00000000},                             /* IRQ4                               */
#endif
#if defined(SPI1)
    {SPI1_IRQHandler},                        /* IRQ5:  SPI1                        */
#else
    {0x00000000},                             /* IRQ5                               */
#endif
#if defined(SPI2)
    {SPI2_IRQHandler},                        /* IRQ6:  SPI2                        */
#else
    {0x00000000},                             /* IRQ6                               */
#endif
    {SPI3_IRQHandler},                        /* IRQ7:  SPI3                        */
    {USART1_IRQHandler},                      /* IRQ8:  USART1                      */
    {LPUART1_IRQHandler},                     /* IRQ9:  LPUART1                     */
#if defined(TIM1)
    {TIM1_IRQHandler},                        /* IRQ10: TIM1                        */
#endif
#if defined(TIM2)
    {TIM2_IRQHandler},                        /* IRQ10: TIM2                        */
#endif
    {RTC_IRQHandler},                         /* IRQ11: RTC                         */
    {ADC_IRQHandler},                         /* IRQ12: ADC                         */
    {PKA_IRQHandler},                         /* IRQ13: PKA                         */
    {UPCONV_IRQHandler},                      /* IRQ14: AHB_UP_CONVERTER            */
    {GPIOA_IRQHandler},                       /* IRQ15: GPIOA                       */
    {GPIOB_IRQHandler},                       /* IRQ16: GPIOB                       */
    {DMA_IRQHandler},                         /* IRQ17: DMA                         */
    {BLE_TX_RX_IRQHandler},                   /* IRQ18: BLE TX RX                   */
    {BLE_AES_IRQHandler},                     /* IRQ19: BLE AES                     */
    {BLE_ERROR_IRQHandler},                   /* IRQ20: BLE Error                   */
    {RADIO_CTRL_IRQHandler},                  /* IRQ21: Radio Control               */
    {MR_BLE_IRQHandler},                      /* IRQ22: RRM and Radio FSM           */
    {CPU_WKUP_IRQHandler},                    /* IRQ23: CPU Wakeup                  */
    {BLE_WKUP_IRQHandler},                    /* IRQ24: BLE Wakeup                  */
    {BLE_RXTX_SEQ_IRQHandler},                /* IRQ25: BLE RX/TX Sequence          */
#if defined(TIM16)
    {TIM16_IRQHandler},                       /* IRQ26: TIM16                       */
#else
    {0x00000000},                             /* IRQ26                              */
#endif
#if defined(TIM17)
    {TIM17_IRQHandler},                       /* IRQ27: TIM17                       */
#else    
    {0x00000000},                             /* IRQ27                              */
#endif
    {0x00000000},                             /* IRQ28                              */
    {0x00000000},                             /* IRQ29                              */
    {0x00000000},                             /* IRQ30                              */
    {0x00000000}                              /* IRQ31                              */
};

/* Configure all the interrupts priority. 
 * The application can modify the interrupts priority.
 * The BLE_TX_RX_IRQn SHALL maintain the highest priority
 */
void setInterruptPriority(void)
{
  NVIC_SetPriority(FLASH_IRQn,       IRQ_LOW_PRIORITY);
  NVIC_SetPriority(RCC_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(PVD_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(I2C1_IRQn,        IRQ_LOW_PRIORITY);
#if defined(I2C2) 
  NVIC_SetPriority(I2C2_IRQn,        IRQ_LOW_PRIORITY);
#endif
#if defined(SPI1) 
  NVIC_SetPriority(SPI1_IRQn,        IRQ_LOW_PRIORITY);
#endif
#if defined(SPI2) 
  NVIC_SetPriority(SPI2_IRQn,        IRQ_LOW_PRIORITY);
#endif
  NVIC_SetPriority(SPI3_IRQn,        IRQ_LOW_PRIORITY);
  NVIC_SetPriority(USART1_IRQn,      IRQ_LOW_PRIORITY);
  NVIC_SetPriority(LPUART1_IRQn,     IRQ_LOW_PRIORITY);
#if defined(TIM1)
  NVIC_SetPriority(TIM1_IRQn,        IRQ_LOW_PRIORITY);
#endif
#if defined(TIM2)
  NVIC_SetPriority(TIM2_IRQn,        IRQ_LOW_PRIORITY);
#endif
  NVIC_SetPriority(RTC_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(ADC_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(PKA_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(UPCONV_IRQn,      IRQ_LOW_PRIORITY);
  NVIC_SetPriority(GPIOA_IRQn,       IRQ_LOW_PRIORITY);
  NVIC_SetPriority(GPIOB_IRQn,       IRQ_LOW_PRIORITY);
  NVIC_SetPriority(DMA_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(BLE_TX_RX_IRQn,   IRQ_CRITICAL_PRIORITY);
  NVIC_SetPriority(BLE_AES_IRQn,     IRQ_LOW_PRIORITY);
  NVIC_SetPriority(BLE_ERROR_IRQn,   IRQ_LOW_PRIORITY);
  NVIC_SetPriority(RADIO_CTRL_IRQn,  IRQ_LOW_PRIORITY);
  NVIC_SetPriority(MR_BLE_IRQn,      IRQ_LOW_PRIORITY);
  NVIC_SetPriority(CPU_WKUP_IRQn,    IRQ_HIGH_PRIORITY);
  NVIC_SetPriority(BLE_WKUP_IRQn,    IRQ_CRITICAL_PRIORITY);
  NVIC_SetPriority(BLE_SEQ_IRQn,     IRQ_LOW_PRIORITY);
#if defined(TIM16)
  NVIC_SetPriority(TIM16_IRQn,       IRQ_LOW_PRIORITY);
#endif
#if defined(TIM17)
  NVIC_SetPriority(TIM17_IRQn,       IRQ_LOW_PRIORITY);
#endif
}

/**
  * @brief System Timer timeout configuration
  * @param system_clock System Clock Frequency
  * @param timeout Timeout expressed in ms (max (2**24)/(system_clock/1000))
  * @param enable TRUE enables the System Timer, FALSE disable the System Timer
  * @retval None
  */
void SystemTimer_TimeoutConfig(uint32_t system_clock_freq, uint32_t timeout, uint8_t enable)
{
  if (enable) {
  SysTick->LOAD  = (uint32_t)(((system_clock_freq/1000) - 1UL)*timeout);                         /* set reload register */
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  } else {
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;    
  }
}

/**
  * @brief System Timer Timeout Expired information
  * @retval True if the timout configured with the SystemTimer_TimeoutConfig() 
  *         is epired, FALSE otherwise
  */                               
uint8_t SystemTimer_TimeoutExpired(void)
{
  if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
    return TRUE;
  
  return FALSE;
}

/**
  * @brief  SMPS and Trimming value Configuration 
  */
static uint8_t SmpsTrimConfig(void)
{
  uint8_t ret_val=SUCCESS;
  uint32_t main_regulator, smps_out_voltage, lsi_bw, hsi_calib;
  uint8_t eng_lsi_bw_flag;
  uint32_t lsi_lpmu;

  /* After reset wait until SMPS is ready */
  SystemTimer_TimeoutConfig(16000000, 200, TRUE);
  while(LL_PWR_IsSMPSReady() == 0)
  {
    if (SystemTimer_TimeoutExpired()) 
    {
      ret_val = SYSTEM_CONFIG_SMPS_READY_ERROR;
      break;
    }
  }
  /* Disable the System Timer */
  SystemTimer_TimeoutConfig(0, 0, FALSE);
  if (ret_val != SUCCESS) 
  {
    return ret_val;
  }
  
  /* Configure SMPS BOM */
#ifdef CONFIG_HW_SMPS_10uH
  LL_PWR_SetSMPSBOM(LL_PWR_SMPS_BOM3);
  /* SMPS clock 4 MHz configuration */
  LL_RCC_SetSMPSPrescaler(LL_RCC_SMPS_DIV_4);
#else
#ifdef CONFIG_HW_SMPS_2_2uH
  LL_PWR_SetSMPSBOM(LL_PWR_SMPS_BOM2);
  /* SMPS clock 8 MHz configuration  */
  LL_RCC_SetSMPSPrescaler(LL_RCC_SMPS_DIV_2);
#else
#ifdef CONFIG_HW_SMPS_1_5uH
  LL_PWR_SetSMPSBOM(LL_PWR_SMPS_BOM1);
    /* SMPS clock 8 MHz configuration  */
  LL_RCC_SetSMPSPrescaler(LL_RCC_SMPS_DIV_2);
#else
#ifdef CONFIG_HW_SMPS_NONE
  /* SMPS NONE configuration will be done after the trimming configuration values */
#else
#warning "No SMPS Configuration!!!"
#endif
#endif
#endif
#endif

  /* Retrieve Trimming values from engineering flash locations */
  if (*(volatile uint32_t*)VALIDITY_LOCATION == VALIDITY_TAG) {
    main_regulator    = ((*(volatile uint32_t*)TRIMMING_LOCATION) & MAIN_REGULATOR_TRIM_Msk) >> MAIN_REGULATOR_TRIM_Pos;
    smps_out_voltage  = ((*(volatile uint32_t*)TRIMMING_LOCATION) & SMPS_TRIM_Msk) >> SMPS_TRIM_Pos;
    lsi_lpmu          = ((*(volatile uint32_t*)TRIMMING_LOCATION) & LSI_LPMU_TRIM_Msk) >> LSI_LPMU_TRIM_Pos;
    lsi_bw            = ((*(volatile uint32_t*)TRIMMING_LOCATION) & LSI_BW_TRIM_Msk) >> LSI_BW_TRIM_Pos;
    hsi_calib         = ((*(volatile uint32_t*)TRIMMING_LOCATION) & HSI_TRIM_Msk) >> HSI_TRIM_Pos;
    eng_lsi_bw_flag   = TRUE;
  } else {
    main_regulator    = 0x08;
    lsi_lpmu          = 0x08;
    hsi_calib         = 0x1E;
    eng_lsi_bw_flag   = FALSE;
    smps_out_voltage  = 0x03;
  }
  
  /* Set HSI Calibration Trimming value */
  LL_RCC_HSI_SetCalibTrimming(hsi_calib);

  /* Low speed internal RC trimming value set by software */
  if (eng_lsi_bw_flag)
    LL_RCC_LSI_SetTrimming(lsi_bw);
  
  /* Set LSI LPMU Trimming value */
  LL_PWR_SetLSILPMUTrim(lsi_lpmu);
	
  /* Set Main Regulator voltage Trimming value */ 
  LL_PWR_SetMRTrim(main_regulator);

  /* Set SMPS output voltage Trimming value */
  LL_PWR_SetSMPSTrim(smps_out_voltage);
  
  /* Set SMPS in LP Open */
  LL_PWR_SetSMPSOpenMode(LL_PWR_SMPS_LPOPEN);

  
#ifdef CONFIG_HW_SMPS_NONE
  /* No SMPS configuration */
  LL_PWR_SetSMPSMode(LL_PWR_NO_SMPS);
#endif

  return SUCCESS;
}

/**
  * @brief  Low Speed Configuration
  */
static uint8_t LSConfig(void)
{
  uint8_t ret_val=SUCCESS;
  
  SystemTimer_TimeoutConfig(16000000, 300, TRUE);
  /* Low speed crystal configuration */
#ifdef CONFIG_HW_LS_XTAL
  LL_PWR_SetNoPullB(LL_PWR_PUPD_IO12|LL_PWR_PUPD_IO13);
  LL_RCC_LSCO_SetSource(LL_RCC_LSCO_CLKSOURCE_LSE);
  
   /* Set LSE oscillator drive capability */
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_HIGH);
  
  LL_RCC_LSE_Enable();
  while (LL_RCC_LSE_IsReady() == 0U)
  {
    if (SystemTimer_TimeoutExpired()) 
    {
      ret_val = SYSTEM_CONFIG_LSE_READY_ERROR;
      break;
    }
  }    
#else
#ifdef CONFIG_HW_LS_RO
  LL_RCC_LSCO_SetSource(LL_RCC_LSCO_CLKSOURCE_LSI);
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() == 0U)
  {
    if (SystemTimer_TimeoutExpired())
    {
      ret_val = SYSTEM_CONFIG_LSI_READY_ERROR;
      break;
    }
  }        
#else
#warning "No Low Speed Crystal definition!!!"
#endif
#endif  
  /* Disable the System Timer */
  SystemTimer_TimeoutConfig(0, 0, FALSE);
  
  return ret_val;
}

/**
  * @brief  MR_BLE BIAS current Trimming value Configuration 
  */
void MrBleBiasTrimConfig(uint8_t coldStart)
{  
  uint32_t mr_ble_ibias, mr_ble_iptat, mr_ble_vbg, mr_ble_rxadc_delay_i, mr_ble_rxadc_delay_q;
  uint8_t mr_ble_rxadc_delay_flag;
  
  if (coldStart) {
    /* Change system's clock frequency from 16MHz to 32MHz */
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_2);
    
    /* Set MR_BLE frequency to 32MHz (HSI/2) */
    LL_RCC_SetRFClockSource(LL_RCC_RF_RC64MPLL_DIV2);

    /* Peripheral reset */
    LL_APB2_ForceReset(LL_APB2_PERIPH_MRBLE);
    LL_APB2_ReleaseReset(LL_APB2_PERIPH_MRBLE);
    
    /* Enable MR_BLE's clock */
    LL_APB2_EnableClock(LL_APB2_PERIPH_MRBLE);    
  }
  
  
  /* Retrieve Trimming values from engineering flash locations */
  if (*(volatile uint32_t*)VALIDITY_LOCATION == VALIDITY_TAG) {
    mr_ble_ibias            = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_IBIAS_TRIM_Msk) >> MR_BLE_IBIAS_TRIM_Pos;
    mr_ble_iptat            = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_IPTAT_TRIM_Msk) >> MR_BLE_IPTAT_TRIM_Pos;
    mr_ble_vbg              = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_VBG_TRIM_Msk) >> MR_BLE_VBG_TRIM_Pos;
    mr_ble_rxadc_delay_i    = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_RXADC_DELAY_I_TRIM_Msk) >> MR_BLE_RXADC_DELAY_I_TRIM_Pos;
    mr_ble_rxadc_delay_q    = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_RXADC_DELAY_Q_TRIM_Msk) >> MR_BLE_RXADC_DELAY_Q_TRIM_Pos;
    mr_ble_rxadc_delay_flag = TRUE;
  } else {
    mr_ble_ibias = 0x08;
    mr_ble_iptat = 0x07;
    mr_ble_vbg   = 0x08;
    mr_ble_rxadc_delay_flag = FALSE;
  }

  /* Write MR_BLE Trimming values in the registers: Cbias' VBG, Cbias' IPTAT, Cbias' IBIAS, RxAnaUsr Delay Trim I & Q */
  MODIFY_REG_FIELD(RRM->CBIAS1_ANA_ENG, RRM_CBIAS1_ANA_ENG_RFD_CBIAS_VBG_TRIM, mr_ble_vbg);
  MODIFY_REG_FIELD(RRM->CBIAS0_ANA_ENG, RRM_CBIAS0_ANA_ENG_RFD_CBIAS_IPTAT_TRIM, mr_ble_iptat);
  MODIFY_REG_FIELD(RRM->CBIAS0_ANA_ENG, RRM_CBIAS0_ANA_ENG_RFD_CBIAS_IBIAS_TRIM, mr_ble_ibias);
  if (mr_ble_rxadc_delay_flag) {
    MODIFY_REG_FIELD(RRM->RXADC_ANA_USR, RRM_RXADC_ANA_USR_RFD_RXADC_DELAYTRIM_I, mr_ble_rxadc_delay_i);
    MODIFY_REG_FIELD(RRM->RXADC_ANA_USR, RRM_RXADC_ANA_USR_RFD_RXADC_DELAYTRIM_Q, mr_ble_rxadc_delay_q);
  }

  /* AGC configuration */
  MODIFY_REG_FIELD(RRM->AGC0_DIG_ENG, RRM_AGC0_DIG_ENG_AGC_THR_HIGH, AGC_THR0);
  SET_BIT(RRM->AGC0_DIG_ENG, RRM_AGC0_DIG_ENG_AGC_ENABLE);
  MODIFY_REG_FIELD(RRM->AGC1_DIG_ENG, RRM_AGC1_DIG_ENG_AGC_THR_LOW_6, AGC_THR1);
  SET_BIT(RRM->AGC1_DIG_ENG, RRM_AGC1_DIG_ENG_AGC_LOCK_SYNC);
  CLEAR_BIT(RRM->AGC1_DIG_ENG, RRM_AGC1_DIG_ENG_AGC_AUTOLOCK);
  MODIFY_REG_FIELD(RRM->AGC10_DIG_ENG, RRM_AGC10_DIG_ENG_ATT_0, AGC_ATT0);
  MODIFY_REG_FIELD(RRM->AGC11_DIG_ENG, RRM_AGC11_DIG_ENG_ATT_1, AGC_ATT1);
  MODIFY_REG_FIELD(RRM->AGC12_DIG_ENG, RRM_AGC12_DIG_ENG_ATT_2, AGC_ATT2);
  MODIFY_REG_FIELD(RRM->AGC13_DIG_ENG, RRM_AGC13_DIG_ENG_ATT_3, AGC_ATT3);
  MODIFY_REG_FIELD(RRM->AGC14_DIG_ENG, RRM_AGC14_DIG_ENG_ATT_4, AGC_ATT4);
  MODIFY_REG_FIELD(RRM->AGC15_DIG_ENG, RRM_AGC15_DIG_ENG_ATT_5, AGC_ATT5);
  MODIFY_REG_FIELD(RRM->AGC16_DIG_ENG, RRM_AGC16_DIG_ENG_ATT_6, AGC_ATT6);
  MODIFY_REG_FIELD(RRM->AGC17_DIG_ENG, RRM_AGC17_DIG_ENG_ATT_7, AGC_ATT7);
  MODIFY_REG_FIELD(RRM->AGC18_DIG_ENG, RRM_AGC18_DIG_ENG_ATT_8, AGC_ATT8);
  MODIFY_REG_FIELD(RRM->AGC19_DIG_ENG, RRM_AGC19_DIG_ENG_ATT_9, AGC_ATT9);
  
  /* AFC configuration */
  MODIFY_REG(RRM->AFC1_DIG_ENG, RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER|RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE,
             ((AFC_DELAY_BEFORE << RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE_Pos) & RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE_Msk) |
               ((AFC_DELAY_AFTER << RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER_Pos) & RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER_Msk));
  MODIFY_REG(RRM->CR0_DIG_ENG, RRM_CR0_DIG_ENG_CR_GAIN_BEFORE|RRM_CR0_DIG_ENG_CR_GAIN_AFTER,
             ((CR_GAIN_BEFORE << RRM_CR0_DIG_ENG_CR_GAIN_BEFORE_Pos) & RRM_CR0_DIG_ENG_CR_GAIN_BEFORE_Msk) |
               ((CR_GAIN_AFTER << RRM_CR0_DIG_ENG_CR_GAIN_AFTER_Pos) & RRM_CR0_DIG_ENG_CR_GAIN_AFTER_Msk));
  MODIFY_REG(RRM->CR0_LR, RRM_CR0_LR_CR_LR_GAIN_BEFORE|RRM_CR0_LR_CR_LR_GAIN_AFTER,
             ((CR_LR_GAIN_BEFORE << RRM_CR0_LR_CR_LR_GAIN_BEFORE_Pos) & RRM_CR0_LR_CR_LR_GAIN_BEFORE_Msk) |
               ((CR_LR_GAIN_AFTER << RRM_CR0_LR_CR_LR_GAIN_AFTER_Pos) & RRM_CR0_LR_CR_LR_GAIN_AFTER_Msk));
  
  MODIFY_REG_FIELD(RRM->LR_RSSI_THR_DIG_ENG, RRM_LR_RSSI_THR_DIG_ENG_LR_RSSI_THR, LR_RSSI_THR);
  MODIFY_REG_FIELD(RRM->LR_PD_THR_DIG_ENG, RRM_LR_PD_THR_DIG_ENG_LR_PD_THR, LR_PD_THR);
  MODIFY_REG_FIELD(RRM->LR_AAC_THR_DIG_ENG, RRM_LR_AAC_THR_DIG_ENG_LR_AAC_THR, LR_AAC_THR);
  
  /* Enable Viterbi */
  SET_BIT(RRM->VIT_CONF_DIG_ENG, RRM_VIT_CONF_DIG_ENG_VIT_CONF_0);
}

/**
  * @brief  System Clock Configuration for System Core, low speed
  *         BLE RF and AHB bus
  * @param  SysClk system clock divided factor from HSI64MPLL
  *         This parameter can be one of the following values:
  *         SYSCLK_64M
  *         SYSCLK_32M
  *         SYSCLK_16M
  *         SYSCLK_8M
  *         SYSCLK_4M
  *         SYSCLK_2M
  *         SYSCLK_1M
  *         SYSCLK_DIRECT_HSE
  * @retval SUCCESS or error code
  */
uint8_t SystemClockConfig(uint8_t SysClk)
{ 
  uint8_t ret_val=SUCCESS;
    
  /* High speed crystal configuration: BlueNRG-LP supports only HSE 32 MHz */
  SystemTimer_TimeoutConfig(32000000, 1000, TRUE);
  LL_RCC_HSE_Enable();
  while (LL_RCC_HSE_IsReady() == 0U) 
  {
    if (SystemTimer_TimeoutExpired()) {
      ret_val = SYSTEM_CONFIG_HSE_READY_ERROR;
      break;
    }
  }
  /* Disable the System Timer */
  SystemTimer_TimeoutConfig(0, 0, FALSE);
  if (ret_val != SUCCESS)
  {
    return ret_val;
  }
  
  /* BlueNRG_LP cut 1.0 not support DIRECT HSE configuration */
  if ((SysClk == SYSCLK_DIRECT_HSE) && (((LL_SYSCFG_GetDeviceVersion()<<4)|LL_SYSCFG_GetDeviceRevision()) == LL_BLUENRG_LP_CUT_10)) {
    return SYSTEM_CONFIG_DIRECT_HSE_NOT_SUPPORTED;
  }
  
  if (SysClk != SYSCLK_DIRECT_HSE) {
    /* System PLL Clock configuration */
  switch(SysClk)
  {
  case SYSCLK_64M:
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_1);
    SystemCoreClock = 64000000;
    break;
  case SYSCLK_32M:
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_2);
    SystemCoreClock = 32000000;
    break;
  case SYSCLK_16M:
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_4);
    SystemCoreClock = 16000000;
    break;
  case SYSCLK_8M:
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_8);
    SystemCoreClock = 8000000;
    break;
  case SYSCLK_4M:
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_16);
    SystemCoreClock = 4000000;
    break;
  case SYSCLK_2M:
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_32);
    SystemCoreClock = 2000000;
    break;
  case SYSCLK_1M:
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_64);
    SystemCoreClock = 1000000;
    break;
  default:
    /* Error, wrong choice */
    while(1);
  }
  SystemTimer_TimeoutConfig(SystemCoreClock, 1000, TRUE);
  LL_RCC_RC64MPLL_Enable();
  while(LL_RCC_RC64MPLL_IsReady() == 0U)
  {
    if (SystemTimer_TimeoutExpired()) {
      ret_val = SYSTEM_CONFIG_PLL_READY_ERROR;
      break;
    }
  }  
  /* Disable the System Timer */
  SystemTimer_TimeoutConfig(0, 0, FALSE);
  if (ret_val != SUCCESS)
  {
    return ret_val;
  }
  
  /* FLASH Wait State configuration */
  if (SystemCoreClock == 64000000) 
  {
    LL_FLASH_SetWaitStates(FLASH, LL_FLASH_WAIT_STATES_1);
  } else {
    LL_FLASH_SetWaitStates(FLASH, LL_FLASH_WAIT_STATES_0);
  }
  } else { // DIRECT HSE configuration
    LL_RCC_DIRECT_HSE_Enable();
  }
  
	
  return SUCCESS;
}

/**
  * @brief  Radio Clock Configuration
  * @param  BleSysClk BLE System Clock 
  *         This parameter can be one of the following values:
  *         BLE_SYSCLK_32M
  *         BLE_SYSCLK_16M
  * @param  SysClk system clock divided factor from HSI64MPLL
  *         This parameter can be one of the following values:
  *         SYSCLK_64M
  *         SYSCLK_32M
  *         SYSCLK_16M
  *         SYSCLK_8M
  *         SYSCLK_4M
  *         SYSCLK_2M
  *         SYSCLK_1M
  *         SYSCLK_DIRECT_HSE
  * @retval None
  */
uint8_t RadioClockConfig(uint8_t BleSysClk, uint8_t SysClk)
{
    /* No radio configuration required */
  if (BleSysClk == BLE_SYSCLK_NONE) {
    return SUCCESS;
  }

  /* The system clock shall be greater than 8 MHz with the radio enabled */
  if ((SysClk == SYSCLK_8M) || (SysClk == SYSCLK_4M) ||
      (SysClk == SYSCLK_2M) || (SysClk == SYSCLK_1M)) {
    return ERROR;
  }

  /* The System clock shall be greater than or equal to the BLE Radio Clock */
  if ((SysClk == SYSCLK_16M) && (BleSysClk == BLE_SYSCLK_32M)) {
    return ERROR;
  }
  
  /* RF clock source configuration according System Clock Frequency*/
  if ((BleSysClk == BLE_SYSCLK_16M) || (SysClk == SYSCLK_16M))
  {
    LL_RCC_SetRFClockSource(LL_RCC_RF_RC64MPLL_DIV4);
    BleSysClk = BLE_SYSCLK_16M;
  }
  else
  {
    LL_RCC_SetRFClockSource(LL_RCC_RF_RC64MPLL_DIV2);
  }

#if defined(AHBUPCONV)
  /* AHBUPCONV management is allowed only for BlueNRG-LP cut 1.0 */ 
  if (((LL_SYSCFG_GetDeviceVersion()<<4)|LL_SYSCFG_GetDeviceRevision()) == LL_BLUENRG_LP_CUT_10)
  {
    /* Configure AHBUPCONV */
    /* Configuration with System Clock four time faster than the MR_BLE clock */
    if ((SysClk == SYSCLK_64M) && (BleSysClk == BLE_SYSCLK_16M))
    {
      AHBUPCONV->COMMAND = SYSCLK_FOURFOLD_BLECLK;
    }
    /* Configuration with System Clock two time faster than the MR_BLE clock */
    else if (((SysClk == SYSCLK_64M) && (BleSysClk == BLE_SYSCLK_32M)) ||
	     ((SysClk == SYSCLK_32M) && (BleSysClk == BLE_SYSCLK_16M)))
    {
      AHBUPCONV->COMMAND = SYSCLK_DOUBLE_BLECLK;
    }
    /* Configuration with System Clock is the same of the MR_BLE clock */
    else
    {
      AHBUPCONV->COMMAND = SYSCLK_EQUAL_BLECLK;
    }
    while(AHBUPCONV->STATUS & AHB_STALLED);
  }
#endif /* defined(AHBUPCONV) */

  return SUCCESS;
}

/**
  * @brief  System Init
  * @param  SysClk system clock divided factor from HSI64MPLL
  *         This parameter can be one of the following values:
  *         SYSCLK_64M
  *         SYSCLK_32M
  *         SYSCLK_16M
  *         SYSCLK_8M
  *         SYSCLK_4M
  *         SYSCLK_2M
  *         SYSCLK_1M
  *         SYSCLK_DIRECT_HSE
  * @param  BleSysClk BLE System Clock 
  *         This parameter can be one of the following values:
  *         BLE_SYSCLK_NONE
  *         BLE_SYSCLK_32M
  *         BLE_SYSCLK_16M
  * @Note   The radio not works if the SYSCLK is lower than 16 MHz 
  * @retval SUCCESS or Error code
  */
uint8_t SystemInit(uint8_t SysClk, uint8_t BleSysClk)
{
  uint8_t ret_val;
  
  /* Vector Table Offset Register */
  SCB->VTOR = (uint32_t) (__vector_table);

  /* Store in RAM the AppBase information */
  RAM_VR.AppBase = (uint32_t) (__vector_table);
	
  /* Enable all the RAM banks in retention during DEEPSTOP */
  LL_PWR_EnableRAMBankRet(LL_PWR_RAMRET_1);
#if defined(LL_PWR_RAMRET_2)
  LL_PWR_EnableRAMBankRet(LL_PWR_RAMRET_2);
#endif
#if defined(LL_PWR_RAMRET_3)
  LL_PWR_EnableRAMBankRet(LL_PWR_RAMRET_3);
#endif
  
#if defined(PWR_CR2_GPIORET)
      /* Disable the GPIO retention in DEEPSTOP configuration */
      LL_PWR_DisableGPIORET();
#endif
	
  /* HW SMPS and HW Trimming value Configuration */
  ret_val = SmpsTrimConfig();
  if (ret_val!= SUCCESS)
    return ret_val;

  /* Low Speed Crystal Configuration */
  ret_val = LSConfig();
  if (ret_val!= SUCCESS)
      return ret_val;
  
  /* MR_BLE BIAS current Trimming Configuration */
  if (BleSysClk != BLE_SYSCLK_NONE) {
    MrBleBiasTrimConfig(TRUE);
  }

  /* Set current and capacitors for High Speed Crystal Oscillator */
#ifdef CONFIG_HW_HSE_TUNE
  LL_RCC_HSE_SetCapacitorTuning(CONFIG_HW_HSE_TUNE);
#else
#warning "No HSE Tune configuration!!!"
#endif
  LL_RCC_HSE_SetCurrentControl(LL_RCC_HSE_CURRENTMAX_3);

  /* System Clock Configuration */
  ret_val = SystemClockConfig(SysClk);
  if (ret_val!= SUCCESS)
    return ret_val;

  /* Radio Clock Configuration */
  ret_val = RadioClockConfig(BleSysClk, SysClk);
  if (ret_val!= SUCCESS)
    return ret_val;
    
  /* Set all the IRQ priority with a default value */
  setInterruptPriority();

  __enable_irq();
  
  return SUCCESS;
}


/******************* (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
