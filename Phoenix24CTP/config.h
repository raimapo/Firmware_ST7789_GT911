#ifndef _CONFIG_H
#define _CONFIG_H

  #define MY_DEBUG 4

  #include <Arduino.h>
  #include "blob.h"
  
  // TFT pins
  #define TFT_CS     PB3  
  #define TFT_RESET  PB4
  #define TFT_DC     PB5
  #define TFT_BL    PA11
  //#define TFT_SCK1   PA5
  //#define TFT_MOSI1  PA7
  
  // CTP pins
  //#define CTP_SCL1  PB6
  //#define CTP_SDA1  PB7
  #define CTP_IRQ   PB8  
  #define CTP_RESET PB9


// LED pins
  #define LED_R PB1 // PB13
  #define LED_B PB11 //PB14
  #define LED_G PB10 // PB15

// FLASH pins
  #define FLASH_CS PA3
  #define FLASH_WP PA2
  #define FLASH_HOLD PA1

// KEYPAD pins
   #define KEY PB0

  #define LED_OFF HIGH
  #define LED_ON LOW

  #define GREEN_FEEDBACK 32
  #define RED_FEEDBACK   32

  #define fade_in_step_time  1
  #define fade_out_step_time 1

  #define SPEED_I2C   400000
  #define SPEED_SPI 35000000

  inline void volatile nop1(void) { asm __volatile__ ("nop"); }
  //STM32F103
  inline void volatile SPI_WaitSPI(void) { while(SPI1->SR & SPI_SR_BSY); } 
  inline void volatile SPI_transfer( uint8_t x ) { while ( !(SPI1->SR & SPI_SR_TXE)) {}; *(volatile uint8_t *)&SPI1->DR = (x);  } 


  inline void volatile SPI_Transmission( uint8_t *data, int size)
  {
    uint8_t clear;
    //check flag TxE //
    int i=0;
    while (i<size)
    {
        while (!((SPI1->SR)&(SPI_SR_TXE))){};  // buffer is empty
        *(volatile uint8_t *)&SPI1->DR = data[i];
        i++;
    }
    while (!((SPI1->SR)&(SPI_SR_TXE))){};  // buffer is empty
    while (((SPI1->SR)&(SPI_SR_BSY))){}; // buffer not communicating  
    clear= SPI1->DR; // empty Overrun flag
    clear= SPI1->SR;
}

  


//  uint32_t flash_start[25][2] = {
//                        {      0, 153600 },
//                        { 153600, 153600 },
//                        { 307200,   2242 },
//                        { 309442,   2242 },
//                        { 311684,   2242 },
//                        { 313926,   2242 },
//                        { 316168,   2242 },
//                        { 318410,   1188 },
//                        { 319598, 153600 },
//                        { 473198,   4428 },
//                        { 477626,   4428 },
//                        { 482054,   4428 },
//                        { 486482,   4428 },
//                        { 490910,   4428 },
//                        { 495338,   4428 },
//                        { 499766,   4428 },
//                        { 504194,   4428 },
//                        { 508622,   4428 },
//                        { 513050,   4428 },
//                        { 517478,   4428 },
//                        { 521906,   4428 },
//                        { 526334, 153600 },
//                        { 679934, 153600 },
//                        { 833534, 153600 },
//                        { 987134, 153600 },
//                       };

#endif
