/**
  ******************************************************************************
  * @file           : i2c.h
  * @brief          : Header for i2c.cpp file.
  *                   This file contains the common defines of the application.
  * @version		: 0.1
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Raimondas Pomarnacki.
  * All rights reserved.</center></h2>
  *
  * This software component is not licensed,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *
  *
  ******************************************************************************
  */

#ifndef __i2c_H
#define __i2c_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stdbool.h"
#include "print.h"

void I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c,  uint16_t DevAddress, uint32_t TestCount, uint32_t timeout);
void I2C_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *data, uint16_t Size, uint32_t Timeout);
void I2C_receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t startreg, uint8_t *data, uint16_t Size, uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
