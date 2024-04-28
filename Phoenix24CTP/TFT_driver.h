/*****************************************************************************
* | File      	:	 TFT_driver.h
* | Author      :  admatec team
* | Function    :  TFT driver
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2018-12-18
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _TFT_DRIVER_H
  #define _TFT_DRIVER_H

  #include "freefont.c"
  
  #define TFT_WIDTH  240                     // TFT width
  #define TFT_HEIGHT 320                     // TFT height 
  #define MAX_PIXEL (TFT_WIDTH * TFT_HEIGHT)


  // some colors
  #define RGB565_BLACK       0x0000      /*   0,   0,   0 */
  #define RGB565_NAVY        0x000F      /*   0,   0, 128 */
  #define RGB565_DARKGREEN   0x03E0      /*   0, 128,   0 */
  #define RGB565_DARKCYAN    0x03EF      /*   0, 128, 128 */
  #define RGB565_MAROON      0x7800      /* 128,   0,   0 */
  #define RGB565_PURPLE      0x780F      /* 128,   0, 128 */
  #define RGB565_OLIVE       0x7BE0      /* 128, 128,   0 */
  #define RGB565_LIGHTGREY   0xC618      /* 192, 192, 192 */
  #define RGB565_DARKGREY    0x7BEF      /* 128, 128, 128 */
  #define RGB565_BLUE        0x001F      /*   0,   0, 255 */
  #define RGB565_GREEN       0x07E0      /*   0, 255,   0 */
  #define RGB565_CYAN        0x07FF      /*   0, 255, 255 */
  #define RGB565_RED         0xF800      /* 255,   0,   0 */
  #define RGB565_MAGENTA     0xF81F      /* 255,   0, 255 */
  #define RGB565_YELLOW      0xFFE0      /* 255, 255,   0 */
  #define RGB565_WHITE       0xFFFF      /* 255, 255, 255 */
  #define RGB565_ORANGE      0xFD20      /* 255, 165,   0 */
  #define RGB565_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
  #define RGB565_PINK        0xFC36      /* 255, 134, 181 */

  #define RGB565_Phoenix     TFT_RGB565( 142, 192, 63 )


  void RESET_TFT( void );
  void TFT_WR_CMD( uint8_t data );
  void TFT_WR_DAT( uint8_t data );  
  void TFT_WriteReg( uint8_t TFT_Reg, uint8_t TFT_RegValue );
  void TFT_WriteData_16Bit( uint16_t data );
  void TFT_INIT( void );

  void TFT_bl_on( void );
  void TFT_bl_off( void );

  void TFT_FULLPIC( uint32_t start_address );
  void TFT_PARTIALPIC( uint32_t start_address, uint16_t PIC_WIDTH, uint16_t PIC_HEIGHT );

  uint16_t TFT_RGB565( uint8_t r, uint8_t g, uint8_t b );

  void TFT_SetWindow( uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd );
  void TFT_direction( uint8_t direction );

  void TFT_DrawPoint( uint16_t x, uint16_t y, uint16_t color );
  
  void TFT_fillScreen( uint16_t color );
  void TFT_fillRect( uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color );

  void TFT_HLine( uint16_t x, uint16_t y, uint16_t w, uint16_t color );
  void TFT_VLine( uint16_t x, uint16_t y, uint16_t h, uint16_t color );
  void TFT_Rectangle( uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color );
  void TFT_drawChar( uint16_t x, uint16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);

  void TFT_ShowString( uint16_t x, uint16_t y, char *p, uint16_t fc, uint16_t bg_c, uint8_t size );
  

//  void Pixel( int16_t x, int16_t y, uint16_t color ) __attribute__((always_inline))
//  {
//    TFT_SetWindow(x, y, x, y);
//    TFT_WriteData_16Bit(color);
//  }


#endif // _TFT_DRIVER_H
