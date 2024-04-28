/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <stdint.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
extern I2C_HandleTypeDef hi2c1;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GT911_RST_Pin GPIO_PIN_13
#define GT911_RST_GPIO_Port GPIOC
#define Relay4_Pin GPIO_PIN_1
#define Relay4_GPIO_Port GPIOB
#define ST7789_DC_Pin GPIO_PIN_2
#define ST7789_DC_GPIO_Port GPIOB
#define ST7789_RST_Pin GPIO_PIN_8
#define ST7789_RST_GPIO_Port GPIOA
#define Relay3_Pin GPIO_PIN_11
#define Relay3_GPIO_Port GPIOA
#define Relay2_Pin GPIO_PIN_12
#define Relay2_GPIO_Port GPIOA
#define Relay1_Pin GPIO_PIN_15
#define Relay1_GPIO_Port GPIOA
#define GT911_INT_Pin GPIO_PIN_3
#define GT911_INT_GPIO_Port GPIOB
#define GT911_INT_EXTI_IRQn EXTI3_IRQn
#define ST7789_CS_Pin GPIO_PIN_4
#define ST7789_CS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
