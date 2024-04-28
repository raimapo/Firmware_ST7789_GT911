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
#include "stdio.h"
#include "st7789.h"
#include "fonts.h"
#include "bitmap.h"

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

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */


  if (HAL_I2C_IsDeviceReady(&hi2c1, 0x5D<<1, 3, 0xFF) != HAL_OK)
	  printf("NOP\n");
  else
	  printf("GT911 was found\n");
  HAL_Delay(1000);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);



	ST7789_Init();
	ST7789_rotation( 2 );

	ST7789_FillScreen( RGB565(255, 0, 0) );
	//ST7789_print( 60, 20, RGB565(255, 255, 255) , RGB565(255, 0, 0) , 1, &Font_16x26, 1, "STM32 Display" );
	ST7789_DrawBitmap( 70, 100, logo, 174, 44, RGB565(255, 255, 255) );

	//ST7789_DrawImage( 40, 0, 240, 240, img1 );

	HAL_Delay (4000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
/*
	  // закрашиваем весь экран указаным цветом
	  ST7789_FillScreen( RGB565(255, 0, 0) );
	  HAL_Delay (2000);
	  // закрашиваем весь экран указаным цветом
	  ST7789_FillScreen( RGB565(0, 255, 0) );
	  HAL_Delay (2000);
	  // закрашиваем весь экран указаным цветом
	  ST7789_FillScreen( RGB565(0, 0, 255) );
	  HAL_Delay (2000);

	  // прямоугольник закрашеный ( координата X и Y ( начиная с 0 ) ширина и высота в пикселях )
	  ST7789_DrawRectangleFilled(0, 0, 320, 240, RGB565(255, 255, 255)) ;
	  HAL_Delay (1000);

	  for( uint8_t i = 0; i< 240; i+=3){
		  // прямоугольник закрашеный ( координата X и Y ( начиная с 0 ) ширина и высота в пикселях )
		  ST7789_DrawRectangleFilled(i, i, 320-i, 240-i, RGB565(i/2, 255-i, 0+i)) ;
	  }

	  for( uint8_t i = 0; i< 120; i+=3){
		  // прямоугольник пустотелый ( координата X и Y ( начиная с 0 ) ширина и высота в пикселях )
		  ST7789_DrawRectangle(i, i, 320-i, 240-i, RGB565(255, 0, 0)) ;
	  }
	  HAL_Delay (2000);


	  // рисуем цветную иконку. параметры координаты х и у ( начиная с 0 ), размер иконки шир и выс, имя иконки ( массив )
	  //ST7789_DrawImage( 0, 0, 240, 240, img1 );
	  //HAL_Delay (2000);

	  // рисуем цветную иконку. параметры координаты х и у ( начиная с 0 ), размер иконки шир и выс, имя иконки ( массив )
	  //ST7789_DrawImage( 0, 0, 240, 240, img2 );
	  //HAL_Delay (2000);

	  // рисуем цветную иконку. параметры координаты х и у ( начиная с 0 ), размер иконки шир и выс, имя иконки ( массив )
	  //ST7789_DrawImage( 0, 0, 240, 240, img3 );
	  //HAL_Delay (2000);


	  // закрашиваем весь экран указаным цветом
	  ST7789_FillScreen( RGB565(0, 10, 100) );
	  HAL_Delay (2000);

	  // печатаем символ ( один ) параметры: х,  у, ( начиная с 0 ),  цвет символа, цвет фона, вкл/выкл фон, размер шрифта, множитель шрифта (увеличивает в х раз шрифт ), сам символ ( поддерживает кириллицу )
	  ST7789_DrawChar( 20, 20, RGB565( 255, 255, 255 ) , RGB565( 0, 10, 10 ) , 0, &Font_16x26, 3, 'F' );
	  HAL_Delay (2000);

	  // печатаем строку параметры: х,  у, ( начиная с 0 ), цвет строки, цвет фона, вкл/выкл фон, размер шрифта, множитель шрифта (увеличивает в х раз шрифт ), сама строка ( поддерживает кириллицу )
	  ST7789_print( 50, 20, RGB565(255, 255, 255) , RGB565(0, 10, 100) , 1, &Font_16x26, 1, "STM32 TFT" );
	  HAL_Delay (2000);

	  // печатаем строку параметры: х,  у, ( начиная с 0 ),  цвет строки, цвет фона, вкл/выкл фон, размер шрифта, множитель шрифта (увеличивает в х раз шрифт ), сама строка ( поддерживает кириллицу )
	  ST7789_print( 10, 160, RGB565(255, 0, 0) , RGB565(0, 10, 100) , 1, &Font_11x18, 1, "Классный дисплей !!!" );
	  HAL_Delay (2000);

	  // печатаем строку параметры: х,  у, ( начиная с 0 ),  цвет строки, цвет фона, вкл/выкл фон, размер шрифта, множитель шрифта (увеличивает в х раз шрифт ), сама строка ( поддерживает кириллицу )
	  ST7789_print( 8, 200, RGB565(0, 255, 0) , RGB565(0, 10, 100) , 1, &Font_7x9, 2, "ST7789 : 240x320" );
	  HAL_Delay (2000);

	  // рисуем цветную иконку. параметры координаты х и у ( начиная с 0 ), размер иконки шир и выс, имя иконки ( массив )
	  //ST7789_DrawImage( 80, 65, 85, 80, logoRGB );
	  //HAL_Delay (2000);

	  // очистка экрана - закрашивает экран цветом черный
	  ST7789_Clear();
	  HAL_Delay (2000);

	  // рисуем монохромную иконку. параметры координаты х и у ( начиная с 0 ), имя иконки ( массив ), размер иконки шир и выс, цвет отображения
	  ST7789_DrawBitmap( 60, 200, logo, 174, 44, RGB565(255, 0, 0) );
	  HAL_Delay (2000);

	  // очистка экрана - закрашивает экран цветом черный
	  ST7789_Clear();
	  HAL_Delay (2000);

	  // круг пустотелый
	  ST7789_DrawCircle(50, 100, 50, RGB565(255, 0, 255));
	  HAL_Delay (2000);

	  // круг закрашеный
	  ST7789_DrawCircleFilled(50, 290, 20, RGB565(255, 40, 255)) ;
	  HAL_Delay (2000);

	  // линия
	  ST7789_DrawLine(1, 319, 239, 319, RGB565(255, 255, 0));
	  HAL_Delay (2000);

	  // прямоугольник закрашеный
	  ST7789_DrawRectangleFilled(90, 265, 140, 310, RGB565(0, 255, 0)) ;
	  HAL_Delay (2000);

	  // прямоугольник пустотелый
	  ST7789_DrawRectangle(160, 265, 220, 309, RGB565(255, 255, 255)) ;
	  HAL_Delay (2000);

	  // рисуем треугольник пустотелый
	  ST7789_DrawTriangle(60, 40, 150, 100, 200, 200, RGB565(100, 255, 150) );
	  HAL_Delay (2000);

	  // рисуем треугольник закрашеный
	  ST7789_DrawFilledTriangle(20, 40, 150, 100, 200, 200, RGB565(100, 255, 150) );
	  HAL_Delay (2000);

	  // рисуем прямоугольник с закругленными краями ( закрашенный )
	  ST7789_DrawFillRoundRect(10, 10, 50, 50, 10, RGB565(100, 255, 150));
	  HAL_Delay (2000);

	  // рисуем прямоугольник с закругленными краями ( пустотелый )
	  ST7789_DrawRoundRect(10, 10, 50, 50, 10, RGB565(100, 255, 150));
	  HAL_Delay (2000);

	  // рисуем полукруг ( правое или левое полушарие (параметр 1 или 2) ) закрашенный
	  ST7789_DrawFillCircleHelper(30, 30, 20 , 1, 0, RGB565(100, 255, 150));
	  HAL_Delay (2000);

	  // рисуем дугу ( четверть круга (параметр 1, 2, 4, 8) ) шириной 1 пиксель
	  ST7789_DrawCircleHelper(30, 30, 20 , 1, RGB565(100, 255, 150));
	  HAL_Delay (2000);

	  // переход в спящий режим
	  ST7789_SleepModeEnter();
	  HAL_Delay (2000);

	  // выход их спящего режима
	  ST7789_SleepModeExit();
	  HAL_Delay (2000);

	  // вкл/выкл дисплея 0-выкл 1- вкл
	  ST7789_DisplayPower( 1 );
	  HAL_Delay (2000);

	  // инверсия цветов 0-вкл  1-выкл
	  ST7789_InversionMode(1);
	  HAL_Delay (2000);
*/
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
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
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
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
  hspi2.Init.CRCPolynomial = 10;
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GT911_RST_GPIO_Port, GT911_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_CS_Pin|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7789_RST_GPIO_Port, ST7789_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : GT911_RST_Pin */
  GPIO_InitStruct.Pin = GT911_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GT911_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_CS_Pin PB5 */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_CS_Pin|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ST7789_RST_Pin */
  GPIO_InitStruct.Pin = ST7789_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_RST_GPIO_Port, &GPIO_InitStruct);

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
