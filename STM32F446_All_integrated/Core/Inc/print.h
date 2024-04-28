/**
  ******************************************************************************
  * @file           : LSM9DS1.h
  * @brief          : Header for lsm9ds1.cpp file.
  *                   This file contains the common defines of the application.
  * @version		: 0.1
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 Raimondas Pomarnacki.
  * All rights reserved.</center></h2>
  *
  * This software component is not licensed,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *
  *
  ******************************************************************************
  */

#ifndef __print_H
#define __print_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "stdarg.h"
#include <string.h>
#include <stdbool.h>

	
extern UART_HandleTypeDef huart3;
	
void print_usart3(char const *format, ...);
	
bool DEBUG_Init(void);
void DEBUG_Printf(const char *fmt, ...);
	
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
