
/* Includes ------------------------------------------------------------------*/
//#include "main.h"
#include <stdbool.h>
/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	float vpin;       /*!< latitude converted to binary */
	float temp;
	bool validation; // modified	
} sensor_adc;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define PRINT_INT(x)    ((int)(x))
#define PRINT_FLOAT(x)  (x>0)? ((int) (((x) - PRINT_INT(x)) * 1000)) : (-1*(((int) (((x) - PRINT_INT(x)) * 1000))))
#define BUFFER_SIZE           (2)

/* Exported functions prototypes ---------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void APP_ADC_Init(void);
void APP_DMA_Init(void);
/* Private defines -----------------------------------------------------------*/
void sensor_ADC(sensor_adc *sensor_adc1);

