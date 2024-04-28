/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7789.h"
#include "fonts.h"
#include "bitmap.h"

#include "GT911.h"
#include "ee24.h"

//#include "lvgl.h"
//#include "lv_conf.h"
//#include "examples/lv_examples.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
/*
#define DISP_HOR_RES 320
#define DISP_VER_RES 240

static lv_disp_drv_t disp_drv;
static lv_color_t disp_buf1[DISP_HOR_RES * DISP_VER_RES /10];
static lv_color_t disp_buf2[DISP_HOR_RES * DISP_VER_RES /10];

//Descriptor of a input device driver

static volatile uint32_t t_saved = 0;

void monitor_cb(lv_disp_drv_t *d, uint32_t t, uint32_t p){
	t_saved = t;
}

void tft_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p){

    if(area->x2 < 0) return;
    if(area->y2 < 0) return;
    if(area->x1 > DISP_HOR_RES - 1) return;
    if(area->y1 > DISP_VER_RES - 1) return;

    //char Buffer[40];
    //char Buffer1[40];
    //for(int i; i<40; i++)
    //{
    	//Buffer[i] = Buffer1[i];
    //}

    int indx=0;
    for(int32_t y = area->y1; y <= area->y2; y++) {
        for(int32_t x = area->x1; x <= area->x2; x++) {
            //set_pixel(x, y, *color_p);  // Put a pixel to the display
        	ST7789_DrawPixel(x, y, color_p->full);
            color_p++;
            indx++;
        }
        indx =0;
    }

    lv_disp_flush_ready(disp);         // Indicate you are ready with the flushing
}
*/
uint16_t Xread, Yread;

GT911_Config_t sampleConfig = {.X_Resolution = 320, .Y_Resolution = 240, .Number_Of_Touch_Support = 1, .ReverseY = false, .ReverseX = false, .SwithX2Y = true, .SoftwareNoiseReduction = true};
TouchCoordinate_t coordinate[5];
uint8_t number;

/*
void GT911_Read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{

	if (Dev_Now.Touch == 1) {
		//printf("%d  %d\n\n", Dev_Now.X[0], Dev_Now.Y[0]);
		data->state = LV_INDEV_STATE_PRESSED;
		data->point.x = Dev_Now.X[0];
		data->point.y = Dev_Now.Y[0];
	} else {
		data->state = LV_INDEV_STATE_RELEASED;
	}

}
*/
void Display_init(int rotation){

	// Display registration
	//=====================
/*
	static lv_disp_draw_buf_t buf;

	lv_disp_draw_buf_init(&buf, disp_buf1, disp_buf2, DISP_HOR_RES * DISP_VER_RES /10);
	lv_disp_drv_init(&disp_drv);
*/

	ST7789_Init();
	ST7789_rotation( rotation );
	GT911_Init(sampleConfig);
	HAL_Delay(10);
/*
	disp_drv.draw_buf = &buf;
	disp_drv.flush_cb = tft_flush;
	disp_drv.monitor_cb = monitor_cb;
	disp_drv.hor_res = DISP_HOR_RES;
	disp_drv.ver_res = DISP_VER_RES;
	disp_drv.rotated = rotation;
	lv_disp_drv_register(&disp_drv);
*/
/*
	//Touch registration
	//=====================
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type =LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = GT911_Read;
    lv_indev_drv_register(&indev_drv);
    HAL_Delay(10);
*/
}

enum TouchState {
    IDLE,
    PRESS_DETECTED,
};

enum TouchState touchState = IDLE;

struct DataStructure {
	  uint8_t Relay_1, Relay_2, Relay_3, Relay_4;
	  uint8_t main_menu, sett, prev_menu;
	  uint8_t adc_en, scan, save;
};

void ADC_Select_CH1 (void) {

	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
	  Error_Handler();
	}
}

void ADC_Select_CH2 (void) {

	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
	  Error_Handler();
	}
}

void ADC_Select_CH3 (void) {

	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = ADC_CHANNEL_3;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
	  Error_Handler();
	}
}

/*
if (ee24_isConnected())
{
	  data[0] = datastruc.Relay_1;
	  data[1] = datastruc.Relay_2;
	  data[2] = datastruc.Relay_3;
	  data[3] = datastruc.Relay_4;
	  data[4] = datastruc.main_menu;
	  data[5] = datastruc.sett;
	  data[6] = datastruc.prev_menu;
	  data[7] = datastruc.adc_en;

	  ee24_write(0, data, 8, 1000);
}
*/

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
 struct DataStructure datastruc  = {false, false, false, false, true, false, 1, false, false};
 uint8_t data[8] = {3};
 char s1[11], s3[11], s2[11];

 uint32_t value[3];
 float temp;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
/*
  if (ee24_isConnected())
  {
    ee24_read(0, data, 8, 1000);
    if (data[0] < 2) {
    		datastruc.Relay_1 = data[0];
    		datastruc.Relay_2 = data[1];
    		datastruc.Relay_3 = data[2];
    		datastruc.Relay_4 = data[3];
    		datastruc.main_menu = data[4];
    		datastruc.sett = data[5];
    		datastruc.prev_menu = data[6];
    		datastruc.adc_en = data[7];
    }
  }
*/


/*
  HAL_Delay(100);
  if (HAL_I2C_IsDeviceReady(&hi2c1, 0x5D<<1, 3, 0xFFF) != HAL_OK)
	  printf("NOP\n");
  else
	  printf("GT911 was found\n");

  GT911_init();

  HAL_Delay(1000);

  //Back Light On
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

  ST7789_Init();
  ST7789_rotation( 2 );

  ST7789_FillScreen( RGB565(255, 0, 0) );
  //ST7789_print( 60, 20, RGB565(255, 255, 255) , RGB565(255, 0, 0) , 1, &Font_16x26, 1, "STM32 Display" );
  ST7789_DrawBitmap( 70, 100, logo, 174, 44, RGB565(255, 255, 255) );

  //ST7789_DrawImage( 40, 0, 240, 240, img1 );

  HAL_Delay (4000);
*/
/*
  //Back Light On
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

  lv_init();
  Display_init(2);

  lv_example_get_started_1();
*/

  //Back Light On
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

  Display_init(2);

  //Theme
  ST7789_FillScreen( ST7789_BLACK );
  ST7789_DrawBitmap( 5, 10, logo, 174, 44, RGB565(255, 255, 255) );
  ST7789_DrawBitmap( 270, 10, settings, 44, 44, RGB565(255, 255, 255) );
  ST7789_DrawLine(0, 55, 340, 55, ST7789_MAGENTA);
  ST7789_print( 70, 65, ST7789_WHITE , ST7789_BLACK , 0, &Font_16x26, 1, "MultiSwitch" );

  ST7789_print( 20, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
  ST7789_DrawRectangleFilled(20, 180, 70, 220, ST7789_RED) ;
  ST7789_print( 100, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
  ST7789_DrawRectangleFilled(100, 180, 150, 220, ST7789_RED) ;
  ST7789_print( 180, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
  ST7789_DrawRectangleFilled(180, 180, 230, 220, ST7789_RED) ;
  ST7789_print( 260, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
  ST7789_DrawRectangleFilled(260, 180, 310, 220, ST7789_RED) ;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  GT911_ReadTouch(coordinate, &number);


	  if (datastruc.adc_en == true){

	  ADC_Select_CH1();
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  value[0] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);

	  ADC_Select_CH2();
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  value[1] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);

	  ADC_Select_CH3();
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  value[2] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);

	  printf("ch1 = %f\t ch2 = %f\t ch3 = %f\r\n", ((float)value[0]/4096)*3.3, ((float)value[1]/4096)*3.3, ((float)value[2]/4096)*3.3);

	  if (datastruc.main_menu == true && datastruc.sett == false)  {

			  ST7789_DrawRectangleFilled(20, 120, 300, 135, RGB565(0, 0, 0)) ;

			  ST7789_print( 20, 120, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "1=" );
			  sprintf(s1,"%2.1f", ((float)value[0]/4096)*3.3);
			  ST7789_print( 45, 120, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, s1 );

			  ST7789_print( 100, 120, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "2=" );
			  sprintf(s2,"%2.1f", ((float)value[1]/4096)*3.3);
			  ST7789_print( 125, 120, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, s2 );

			  ST7789_print( 180, 120, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "3=" );
			  sprintf(s3,"%2.1f", ((float)value[2]/4096)*3.3);
			  ST7789_print( 205, 120, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, s3 );

		  }
	  } else {
		  //nothing
	  }


	  if (datastruc.main_menu == true && datastruc.sett == false) {

		  // Handle touch detection logic
		  switch (touchState) {
			  case IDLE:
				  if (number > 0) {
					  // Perform action when press is detected

					  if (coordinate[0].x >= 210 && coordinate[0].x <=235 && coordinate[0].y >= 5 && coordinate[0].y <= 30 && datastruc.main_menu == true && datastruc.sett == false) {
						  printf("labas\n");
						  datastruc.sett = true;
						  datastruc.main_menu = false;
					  }

						  //Relay 1
						  if (coordinate[0].x >= 20 && coordinate[0].x <=40 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.Relay_1 == false) {
							  ST7789_DrawRectangleFilled(20, 160, 55, 175, RGB565(0, 0, 0)) ;
							  ST7789_print( 20, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "On" );
							  ST7789_DrawRectangleFilled(20, 180, 70, 220, ST7789_GREEN);
							  HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_SET);
							  datastruc.Relay_1 = true;
						  } else if (coordinate[0].x >= 20 && coordinate[0].x <=40 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.Relay_1 == true) {
							  ST7789_DrawRectangleFilled(20, 160, 55, 175, RGB565(0, 0, 0));
							  ST7789_print( 20, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
							  ST7789_DrawRectangleFilled(20, 180, 70, 220, ST7789_RED) ;
							  HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_RESET);
							  datastruc.Relay_1 = false;
						  }


						  //Relay 2
						  if (coordinate[0].x >= 55 && coordinate[0].x <=75 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.Relay_2 == false) {
							  ST7789_DrawRectangleFilled(100, 160, 135, 175, RGB565(0, 0, 0)) ;
							  ST7789_print( 100, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "On" );
							  ST7789_DrawRectangleFilled(100, 180, 150, 220, ST7789_GREEN);
							  HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_SET);
							  datastruc.Relay_2 = true;
						  } else if (coordinate[0].x >= 55 && coordinate[0].x <=75 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.Relay_2 == true) {
							  ST7789_DrawRectangleFilled(100, 160, 135, 175, RGB565(0, 0, 0));
							  ST7789_print( 100, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
							  ST7789_DrawRectangleFilled(100, 180, 150, 220, ST7789_RED) ;
							  HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_RESET);
							  datastruc.Relay_2 = false;
						  }

						  //Relay 3
						  if (coordinate[0].x >= 250 && coordinate[0].x <=275 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.Relay_3 == false) {
							  ST7789_DrawRectangleFilled(180, 160, 215, 175, RGB565(0, 0, 0)) ;
							  ST7789_print( 180, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "On" );
							  ST7789_DrawRectangleFilled(180, 180, 230, 220, ST7789_GREEN);
							  HAL_GPIO_WritePin(Relay3_GPIO_Port, Relay3_Pin, GPIO_PIN_SET);
							  datastruc.Relay_3 = true;
						  } else if (coordinate[0].x >= 250 && coordinate[0].x <=275 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.Relay_3 == true) {
							  ST7789_DrawRectangleFilled(180, 160, 215, 175, RGB565(0, 0, 0));
							  ST7789_print( 180, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
							  ST7789_DrawRectangleFilled(180, 180, 230, 220, ST7789_RED) ;
							  HAL_GPIO_WritePin(Relay3_GPIO_Port, Relay3_Pin, GPIO_PIN_RESET);
							  datastruc.Relay_3 = false;
						  }

						  //Relay 4
						  if (coordinate[0].x >= 213 && coordinate[0].x <=230 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.Relay_4 == false) {
							  ST7789_DrawRectangleFilled(260, 160, 295, 175, RGB565(0, 0, 0)) ;
							  ST7789_print( 260, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "On" );
							  ST7789_DrawRectangleFilled(260, 180, 310, 220, ST7789_GREEN);
							  HAL_GPIO_WritePin(Relay4_GPIO_Port, Relay4_Pin, GPIO_PIN_SET);
							  datastruc.Relay_4 = true;
						  } else if (coordinate[0].x >= 213 && coordinate[0].x <=230 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.Relay_4 == true) {
							  ST7789_DrawRectangleFilled(260, 160, 295, 175, RGB565(0, 0, 0));
							  ST7789_print( 260, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
							  ST7789_DrawRectangleFilled(260, 180, 310, 220, ST7789_RED) ;
							  HAL_GPIO_WritePin(Relay4_GPIO_Port, Relay4_Pin, GPIO_PIN_RESET);
							  datastruc.Relay_4 = false;
						  }

					  touchState = PRESS_DETECTED;
				  }
				  break;

			  case PRESS_DETECTED:
				  if (number == 0) {
					  // Reset state when touch is released
					  touchState = IDLE;
				  }
				  break;
		  }


		  if (datastruc.prev_menu != 1) {
			datastruc.prev_menu = 1;
			ST7789_FillScreen( ST7789_BLACK );
			ST7789_DrawBitmap( 5, 10, logo, 174, 44, RGB565(255, 255, 255) );
			ST7789_DrawBitmap( 270, 10, settings, 44, 44, RGB565(255, 255, 255) );
			ST7789_DrawLine(0, 55, 340, 55, ST7789_MAGENTA);
			ST7789_print( 70, 65, ST7789_WHITE , ST7789_BLACK , 0, &Font_16x26, 1, "MultiSwitch" );


			if (datastruc.Relay_1 == false) {
				ST7789_print( 20, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
				ST7789_DrawRectangleFilled(20, 180, 70, 220, ST7789_RED) ;
			} else {
				ST7789_print( 20, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "On" );
				ST7789_DrawRectangleFilled(20, 180, 70, 220, ST7789_GREEN) ;
			}
			if (datastruc.Relay_2 == false) {
				ST7789_print( 100, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
				ST7789_DrawRectangleFilled(100, 180, 150, 220, ST7789_RED) ;
			} else {
				ST7789_print( 100, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "On" );
				ST7789_DrawRectangleFilled(100, 180, 150, 220, ST7789_GREEN) ;
			}
			if (datastruc.Relay_3 == false) {
				ST7789_print( 180, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
				ST7789_DrawRectangleFilled(180, 180, 230, 220, ST7789_RED) ;
			} else {
				ST7789_print( 180, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "On" );
				ST7789_DrawRectangleFilled(180, 180, 230, 220, ST7789_GREEN) ;
			}
			if (datastruc.Relay_4 == false) {
				ST7789_print( 260, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Off" );
				ST7789_DrawRectangleFilled(260, 180, 310, 220, ST7789_RED) ;
			} else {
				ST7789_print( 260, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "On" );
				ST7789_DrawRectangleFilled(260, 180, 310, 220, ST7789_GREEN) ;
			}
		  }
	  }

	  if (datastruc.main_menu == false && datastruc.sett == true) {

		  // Handle touch detection logic
		  switch (touchState) {
			  case IDLE:
				  if (number > 0) {
					  // Perform action when press is detected

				  if (coordinate[0].x >= 210 && coordinate[0].x <=235 && coordinate[0].y >= 5 && coordinate[0].y <= 30 && datastruc.main_menu == false && datastruc.sett == true) {
					  datastruc.sett = false;
					  datastruc.main_menu = true;
				  }

				  if (coordinate[0].x >= 10 && coordinate[0].x <=50 && coordinate[0].y >= 55 && coordinate[0].y <= 90 && datastruc.adc_en == false) {
					  ST7789_DrawRectangleFilled(10, 90, 100, 115, RGB565(0, 0, 0)) ;
					  ST7789_print( 10, 90, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "ADC on" );
					  ST7789_DrawRectangleFilled(10, 110, 50, 150, ST7789_GREEN) ;
					  datastruc.adc_en = true;
				  } else if (coordinate[0].x >= 10 && coordinate[0].x <=50 && coordinate[0].y >= 60 && coordinate[0].y <= 85 && datastruc.adc_en == true) {
					  ST7789_DrawRectangleFilled(10, 90, 100, 115, RGB565(0, 0, 0));
					  ST7789_print( 10, 90, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "ADC Off" );
					  ST7789_DrawRectangleFilled(10, 110, 50, 150, ST7789_RED) ;
					  datastruc.adc_en = false;
				  }


				  if (coordinate[0].x >= 55 && coordinate[0].x <=75 && coordinate[0].y >= 55 && coordinate[0].y <= 90 && datastruc.save == false) {
					  ST7789_DrawRectangleFilled(100, 90, 145, 115, RGB565(0, 0, 0)) ;
					  ST7789_print( 100, 90, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Wait" );
					  ST7789_DrawRectangleFilled(100, 110, 140, 150, ST7789_BLUE) ;
					  datastruc.save = true;
				  } else if (coordinate[0].x >= 55 && coordinate[0].x <=75 && coordinate[0].y >= 60 && coordinate[0].y <= 85 && datastruc.save == true) {
					  ST7789_DrawRectangleFilled(100, 90, 145, 115, RGB565(0, 0, 0));
					  ST7789_print( 100, 90, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Save" );
					  ST7789_DrawRectangleFilled(100, 110, 140, 150, ST7789_RED) ;
					  datastruc.save = false;
				  }



				  if (coordinate[0].x >= 10 && coordinate[0].x <=50 && coordinate[0].y >= 110 && coordinate[0].y <= 140 && datastruc.scan == false) {
					  ST7789_DrawRectangleFilled(100, 160, 110, 175, RGB565(0, 0, 0)) ;
					  ST7789_print( 10, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Scan On" );
					  ST7789_DrawRectangleFilled(10, 180, 50, 220, ST7789_GREEN) ;
					  datastruc.scan = true;
				  } else if (coordinate[0].x >= 10 && coordinate[0].x <=50 && coordinate[0].y >= 110 && coordinate[0].y <= 145 && datastruc.scan == true) {
					  ST7789_DrawRectangleFilled(10, 160, 110, 175, RGB565(0, 0, 0));
					  ST7789_print( 10, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Scan Off" );
					  ST7789_DrawRectangleFilled(10, 180, 50, 220, ST7789_RED) ;
					  datastruc.scan = false;
				  }


				  touchState = PRESS_DETECTED;
			  }
			  break;

		  case PRESS_DETECTED:
			  if (number == 0) {
				  // Reset state when touch is released
				  touchState = IDLE;
			  }
				  break;
		}

		  if (datastruc.prev_menu != 2) {
			  datastruc.prev_menu = 2;
			  ST7789_FillScreen( ST7789_BLACK );
			  ST7789_DrawBitmap( 5, 10, logo, 174, 44, RGB565(255, 255, 255) );
			  ST7789_DrawBitmap( 260, 10, back, 79, 44, RGB565(255, 255, 255) );
			  ST7789_DrawLine(0, 55, 340, 55, ST7789_MAGENTA);

				if (datastruc.adc_en == false) {
					ST7789_print( 10, 90, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "ADC Off" );
					ST7789_DrawRectangleFilled(10, 110, 50, 150, ST7789_RED) ;
				} else {
					ST7789_print( 10, 90, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "ADC On" );
					ST7789_DrawRectangleFilled(10, 110, 50, 150, ST7789_GREEN) ;
				}

				if (datastruc.save == false) {
					ST7789_print( 100, 90, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Save" );
					ST7789_DrawRectangleFilled(100, 110, 140, 150, ST7789_RED) ;
				} else {
					ST7789_print( 100, 90, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Wait" );
					ST7789_DrawRectangleFilled(100, 110, 140, 150, ST7789_BLUE) ;
				}


				if (datastruc.scan == false) {
					ST7789_print( 10, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Scan Off" );
					ST7789_DrawRectangleFilled(10, 180, 50, 220, ST7789_RED) ;
				} else {
					ST7789_print( 10, 160, ST7789_WHITE , ST7789_BLACK , 0, &Font_11x18, 1, "Scan On" );
					ST7789_DrawRectangleFilled(10, 180, 50, 220, ST7789_GREEN) ;
				}
		  }

	  }

	 //printf("%d\n%d\r\n\n", coordinate[0].x, coordinate[0].y);
	 HAL_Delay(100);

	//HAL_Delay(1);
	//lv_task_handler();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GT911_RST_GPIO_Port, GT911_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Relay4_Pin|ST7789_DC_Pin|ST7789_CS_Pin|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ST7789_RST_Pin|Relay3_Pin|Relay2_Pin|Relay1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : GT911_RST_Pin */
  GPIO_InitStruct.Pin = GT911_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GT911_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay4_Pin ST7789_DC_Pin ST7789_CS_Pin PB5 */
  GPIO_InitStruct.Pin = Relay4_Pin|ST7789_DC_Pin|ST7789_CS_Pin|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_RST_Pin Relay3_Pin Relay2_Pin Relay1_Pin */
  GPIO_InitStruct.Pin = ST7789_RST_Pin|Relay3_Pin|Relay2_Pin|Relay1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : GT911_INT_Pin */
  GPIO_InitStruct.Pin = GT911_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GT911_INT_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
