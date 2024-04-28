/*****************************************************************************
  | File      	:	TFT_Driver.c
  | Author      : admatec team
  | Function    : TFT driver
  | Info        :
  ----------------
  |	This version:   V1.0
  | Date        :   2018-12-18
  | Info        :
  #
  #
******************************************************************************/
#include <SPI.h>
#include "config.h"
#include "TFT_driver.h"
#include "SST25VF.h"

uint8_t tft_xoffset = 0;
uint8_t tft_yoffset = 0;
uint16_t TFT_W = TFT_WIDTH;
uint16_t TFT_H = TFT_HEIGHT;

uint16_t POINT_COLOR = 0;
uint16_t BACK_COLOR = 0xFFFF;


// ===============================================================
// Functions
// ===============================================================

//STM32F103
//inline static void SPI_transfer  ( uint8_t x )
//{ // 0.3uS overhead between bytes when optimized // 3.25 uS unoptimized
//  // SPI.transfer(x);  // send byte
//  SPI1->DR = (x) ;
//  while ( ! (SPI1->SR & SPI_SR_TXE) ) {}; 
//}

//inline void SPI_WaitSPI()
//{
//  while(SPI1->SR & SPI_SR_BSY) {}; 
//}


//inline static void SPI_transfer ( uint8_t x ) __attribute__ ((always_inline))
//{ // 0.3uS overhead between bytes when optimized // 3.25 uS unoptimized
//  // SPI.transfer(x);  // send byte
//  SPI1->DR = (x) ;
//  while ((SPI1->SR &  SPI_SR_BSY ) | (SPI1->SR & (!SPI_SR_TXE)) ) {}; // wait until - Transmit buffer NOT Empty - Busy flag  SET
//}



//inline void SPI_transfer  ( uint8_t x )
//{ // 0.3uS overhead between bytes when optimized // 3.25 uS unoptimized
//  // SPI_transfer(x);  // send byte
//  SPI1->DR = (x) ;
//  while ((SPI1->SR &  SPI_SR_BSY ) | (SPI1->SR & (!SPI_SR_TXE)) ) {}; // wait until - Transmit buffer NOT Empty - Busy flag  SET
//}

// ---------------------------------------------------------------

void TFT_PARTIALPIC( uint32_t start, uint16_t PIC_WIDTH, uint16_t PIC_HEIGHT )
{
  uint16_t OneLine = 2 * PIC_WIDTH;
  uint8_t p_line[ OneLine ];

  digitalWrite( TFT_DC, HIGH );

  for ( uint32_t i=0; i<PIC_HEIGHT; i++ )
  {
    SST25VF_readArray( start + i*OneLine, &p_line[0], OneLine );
    
    digitalWrite( TFT_CS, LOW );
    for ( uint16_t j = 0; j < OneLine; j++ )
    {
      SPI.transfer( p_line[j] );
    }
    digitalWrite( TFT_CS, HIGH );
  }
}


// ---------------------------------------------------------------

void TFT_FULLPIC( uint32_t start )
{
  uint16_t OneLine = 2 * 320;
  uint16_t BUFFERSIZE = 4 * OneLine;
  uint8_t p_line[ BUFFERSIZE ];
  uint32_t i;
  uint16_t j;

  TFT_SetWindow( 0, 0, TFT_W - 1, TFT_H - 1 );
  digitalWrite( TFT_DC, HIGH );

  for ( i=0; i<(240*OneLine)/BUFFERSIZE; i++ )
  {
    SST25VF_readArray( start + i*BUFFERSIZE, &p_line[0], BUFFERSIZE );
    digitalWrite( TFT_CS, LOW );
    for ( j = 0; j < BUFFERSIZE; j++ )
    {
      SPI.transfer( p_line[j] );
    }
    digitalWrite( TFT_CS, HIGH );
  }
}

// ---------------------------------------------------------------

void TFT_bl_on(void)
{
  digitalWrite( TFT_BL, HIGH );
}

void TFT_bl_off(void)
{
  digitalWrite( TFT_BL, LOW );
}

void TFT_WR_CMD( uint8_t data )
{
  digitalWrite( TFT_DC, LOW );
  digitalWrite( TFT_CS, LOW );
  SPI.transfer( data );
  digitalWrite( TFT_CS, HIGH );
}


void TFT_WR_DAT( uint8_t data )
{
  digitalWrite( TFT_DC, HIGH );
  digitalWrite( TFT_CS, LOW );
  SPI.transfer( data );
  digitalWrite( TFT_CS, HIGH );
}

void TFT_WriteReg( uint8_t TFT_Reg, uint8_t TFT_RegValue )
{
  TFT_WR_CMD( TFT_Reg );
  TFT_WR_DAT( TFT_RegValue );
}

void TFT_WriteData_16Bit( uint16_t data )
{
  digitalWrite( TFT_DC, HIGH );
  digitalWrite( TFT_CS, LOW );
  SPI.transfer( highByte( data ) );
  SPI.transfer( lowByte( data ) );
  digitalWrite( TFT_CS, HIGH );
}

void RESET_TFT( void )
{
  digitalWrite( TFT_RESET, LOW );
  delay( 20 );
  digitalWrite( TFT_RESET, HIGH );
  delay( 50 );
}

/*****************************************************************************
   @name       :void TFT_INIT(void)
   @function   :Initialization TFT screen
   @parameters :None
   @retvalue   :None
******************************************************************************/

void TFT_INIT( void )
{
  pinMode( TFT_BL, OUTPUT );
  digitalWrite( TFT_BL, LOW );

  pinMode( TFT_RESET, OUTPUT );
  digitalWrite( TFT_RESET, HIGH );

  pinMode( TFT_DC, OUTPUT );
  digitalWrite( TFT_DC, LOW );

  pinMode( TFT_CS, OUTPUT );
  digitalWrite( TFT_CS, HIGH );

#ifdef MY_DEBUG
  Serial.println( F("TFT: init") );
#endif

  RESET_TFT();

  //************* ST7789V **********//

  TFT_WR_CMD(0x11);                    // Sleep out
  delay(120);                          // delay 120ms
  TFT_WR_CMD(0x3A); TFT_WR_DAT(0x05);  // 0x05( 65K Color)
  TFT_WR_CMD(0x21);                    // display inversion on

  TFT_WR_CMD( 0xB0 );                  //RAM control (color expansion R0 + B0)
  TFT_WR_DAT( 0x00 );
  TFT_WR_DAT( 0xC0 );

  //-------------------------------//
  TFT_WR_CMD(0xB2); TFT_WR_DAT(0x0C); TFT_WR_DAT(0x0C); TFT_WR_DAT(0x00); TFT_WR_DAT(0x33); TFT_WR_DAT(0x33);

  //-------------------------------//
  TFT_WR_CMD(0xB7); TFT_WR_DAT(0x71);  // VGH + VGL
  TFT_WR_CMD(0xBB); TFT_WR_DAT(0x22);  // VCOM
 
  TFT_WR_CMD(0xC3); TFT_WR_DAT(0x0B);  //10
  TFT_WR_CMD(0xC4); TFT_WR_DAT(0x20);
  
  TFT_WR_CMD(0xD0); TFT_WR_DAT(0xA4); TFT_WR_DAT(0xA1);

  //-------------------------------//
  TFT_WR_CMD(0xE0); TFT_WR_DAT(0xD0); TFT_WR_DAT(0x03); TFT_WR_DAT(0x07); TFT_WR_DAT(0x0A); TFT_WR_DAT(0x09); TFT_WR_DAT(0x24); TFT_WR_DAT(0x2B); TFT_WR_DAT(0x32); TFT_WR_DAT(0x42); TFT_WR_DAT(0x37); TFT_WR_DAT(0x13); TFT_WR_DAT(0x15); TFT_WR_DAT(0x27); TFT_WR_DAT(0x2B);
  TFT_WR_CMD(0xE1); TFT_WR_DAT(0xD0); TFT_WR_DAT(0x05); TFT_WR_DAT(0x09); TFT_WR_DAT(0x07); TFT_WR_DAT(0x06); TFT_WR_DAT(0x05); TFT_WR_DAT(0x29); TFT_WR_DAT(0x44); TFT_WR_DAT(0x40); TFT_WR_DAT(0x39); TFT_WR_DAT(0x14); TFT_WR_DAT(0x13); TFT_WR_DAT(0x28); TFT_WR_DAT(0x2D);

  TFT_direction( 1 );

  TFT_WR_CMD(0x29);     //Display on
}


// ---------------------------------------------------------------

uint16_t TFT_RGB565( uint8_t r, uint8_t g, uint8_t b )
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3) ;
}


void TFT_HLine( uint16_t x, uint16_t y, uint16_t w, uint16_t color )
{
  TFT_SetWindow( x, y, x + w - 1, y );
  digitalWrite( TFT_DC, HIGH );
  digitalWrite( TFT_CS, LOW );
  do  {
    SPI.transfer( highByte( color ) );
    SPI.transfer( lowByte( color ) );
  } while (--w > 0);
  digitalWrite( TFT_CS, HIGH );
}


void TFT_VLine( uint16_t x, uint16_t y, uint16_t h, uint16_t color )
{
  TFT_SetWindow( x, y, x, y + h - 1 );
  digitalWrite( TFT_DC, HIGH );
  digitalWrite( TFT_CS, LOW );
  do  {
    SPI.transfer( highByte( color ) );
    SPI.transfer( lowByte( color ) );
  } while (--h > 0);
  digitalWrite( TFT_CS, HIGH );
}



void TFT_Rectangle( uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color )
{
  TFT_HLine(     x,     y, w + 2, color );
  TFT_HLine(     x, h + 1 + y, w + 2, color );
  TFT_VLine(     x,     y, h + 2, color );
  TFT_VLine( 1 + w + x,     y, h + 2, color );
}


//void TFT_ILI9163C::drawLine(int16_t x0, int16_t y0,int16_t x1, int16_t y1, uint16_t color){
//  if (y0 == y1) {
//    if (x1 > x0) {
//      drawFastHLine(x0, y0, x1 - x0 + 1, color);
//    } else if (x1 < x0) {
//      drawFastHLine(x1, y0, x0 - x1 + 1, color);
//    } else {
//      drawPixel(x0, y0, color);
//    }
//    return;
//  } else if (x0 == x1) {
//    if (y1 > y0) {
//      drawFastVLine(x0, y0, y1 - y0 + 1, color);
//    } else {
//      drawFastVLine(x0, y1, y0 - y1 + 1, color);
//    }
//    return;
//  }
//
//  bool steep = abs(y1 - y0) > abs(x1 - x0);
//  if (steep) {
//    swap(x0, y0);
//    swap(x1, y1);
//  }
//  if (x0 > x1) {
//    swap(x0, x1);
//    swap(y0, y1);
//  }
//
//  int16_t dx, dy;
//  dx = x1 - x0;
//  dy = abs(y1 - y0);
//
//  int16_t err = dx / 2;
//  int16_t ystep;
//
//  if (y0 < y1) {
//    ystep = 1;
//  } else {
//    ystep = -1;
//  }
//
//  SPI.beginTransaction(SPISettings(SPICLOCK, MSBFIRST, SPI_MODE0));
//  int16_t xbegin = x0;
//  if (steep) {
//    for (; x0<=x1; x0++) {
//      err -= dy;
//      if (err < 0) {
//        int16_t len = x0 - xbegin;
//        if (len) {
//          VLine(y0, xbegin, len + 1, color);
//        } else {
//          Pixel(y0, x0, color);
//        }
//        xbegin = x0 + 1;
//        y0 += ystep;
//        err += dx;
//      }
//    }
//    if (x0 > xbegin + 1) {
//      VLine(y0, xbegin, x0 - xbegin, color);
//    }
//
//  } else {
//    for (; x0<=x1; x0++) {
//      err -= dy;
//      if (err < 0) {
//        int16_t len = x0 - xbegin;
//        if (len) {
//          HLine(xbegin, y0, len + 1, color);
//        } else {
//          Pixel(x0, y0, color);
//        }
//        xbegin = x0 + 1;
//        y0 += ystep;
//        err += dx;
//      }
//    }
//    if (x0 > xbegin + 1) {
//      HLine(xbegin, y0, x0 - xbegin, color);
//    }
//  }
//  writecommand_last(CMD_NOP);
//  SPI.endTransaction();
//}



/******************************************************************************
  function:  Draw a rectangle
  parameter:
    Xstart ：Rectangular  Starting Xpoint point coordinates
    Ystart ：Rectangular  Starting Xpoint point coordinates
    Xend   ：Rectangular  End point Xpoint coordinate
    Yend   ：Rectangular  End point Ypoint coordinate
    Color  ：The color of the Rectangular segment
    Filled : Whether it is filled--- 1 solid 0：empty
******************************************************************************/
void TFT_DrawRectangle( uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd, uint16_t color )
{
  //  TFT_DrawLine( xStar, yStar, Xend, yStar, color );  // TOP LINE
  //  TFT_DrawLine( xStar, yStar, xStar, yEnd, color );  // LEFT LINE
  //  TFT_DrawLine( xEnd, yStar, xEnd, yEnd, color );    // right line
  //  TFT_DrawLine( xEnd, yEnd, xStar, yEnd, color );    // bottom line
}


/*****************************************************************************
   @name       :void TFT_SetWindow(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
   @date       :2018-08-09
   @function   :Setting LCD display window
   @parameters :xStar:the bebinning x coordinate of the LCD display window
                yStar:the bebinning y coordinate of the LCD display window
                xEnd:the endning x coordinate of the LCD display window
                yEnd:the endning y coordinate of the LCD display window
   @retvalue   :None
******************************************************************************/
void TFT_SetWindow( uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd )
{
  digitalWrite( TFT_CS, LOW );
  digitalWrite( TFT_DC, LOW );
  SPI.transfer( 0x2A );
  digitalWrite( TFT_DC, HIGH );
  SPI.transfer( ( xStar + tft_xoffset ) >> 8 ); // .. highbyte
  SPI.transfer( ( xStar + tft_xoffset ) );      // .. lowbyte
  SPI.transfer( ( xEnd + tft_xoffset ) >> 8 );  // .. highbyte
  SPI.transfer( ( xEnd + tft_xoffset ) );       // .. lowbyte

  digitalWrite( TFT_DC, LOW );
  SPI.transfer( 0x2B );
  digitalWrite( TFT_DC, HIGH );
  SPI.transfer( ( yStar + tft_yoffset ) >> 8 ); // .. highbyte
  SPI.transfer( ( yStar + tft_yoffset ) );      // .. lowbyte
  SPI.transfer( ( yEnd + tft_yoffset ) >> 8 );  // .. highbyte
  SPI.transfer( ( yEnd + tft_yoffset ) );       // .. lowbyte
  digitalWrite( TFT_CS, HIGH );

  TFT_WR_CMD( 0x2C );
}


/*****************************************************************************
   @name       :void TFT_direction(uint8_t direction)
   @date       :2018-08-09
   @function   :Setting the display direction of LCD screen
   @parameters :direction:0-0 degree
                          1-90 degree
                          2-180 degree
                          3-270 degree
   @retvalue   :None
******************************************************************************/
void TFT_direction( uint8_t direction )
{
  switch ( direction )
  {
    case 0: TFT_W = TFT_WIDTH;
      TFT_H = TFT_HEIGHT;
      tft_xoffset = 0;
      tft_yoffset = 0;
      TFT_WriteReg( 0x36, 0 );                 //BGR==0,MY==0,MX==0,MV==0
      break;
    case 1: TFT_W = TFT_HEIGHT;
      TFT_H = TFT_WIDTH;
      tft_xoffset = 0;
      tft_yoffset = 0;
      TFT_WriteReg(0x36, (1 << 6) | (1 << 5)); //BGR==0,MY==1,MX==0,MV==1
      break;
    case 2: TFT_W = TFT_WIDTH;
      TFT_H = TFT_HEIGHT;
      tft_xoffset = 0;
      tft_yoffset = 0;
      TFT_WriteReg(0x36, (1 << 6) | (1 << 7)); //BGR==0,MY==0,MX==0,MV==0
      break;
    case 3: TFT_W = TFT_HEIGHT;
      TFT_H = TFT_WIDTH;
      tft_xoffset = 0;
      tft_yoffset = 0;
      TFT_WriteReg(0x36, (1 << 7) | (1 << 5)); //BGR==0,MY==1,MX==0,MV==1
      break;
    default:  break;
  }

  TFT_SetWindow( 0, 0, TFT_W - 1, TFT_H - 1 );
}



// fill a rectangle
void TFT_fillRect( uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color )
{
  uint32_t pixel;

  pixel = w * h;
  TFT_SetWindow( x, y, x + w - 1, y + h - 1 );

  digitalWrite( TFT_DC, HIGH );
  digitalWrite( TFT_CS, LOW );
  while ( pixel-- )
  {
    SPI.transfer( color >> 8 );
    SPI.transfer( color );
  }
  digitalWrite( TFT_CS, HIGH );
}


// ---------------------------------------------------------------

void TFT_fillScreen( uint16_t color )
{
  TFT_fillRect( 0, 0, TFT_W, TFT_H, color );
}


// ---------------------------------------------------------------

void TFT_DrawImage( uint8_t* mem_image, uint16_t num_bytes )
{
  uint16_t i;
  uint8_t data;

  digitalWrite( TFT_CS, LOW );
  digitalWrite( TFT_DC, HIGH );
  for ( i = 0; i < num_bytes; i++ )
  {
    data = pgm_read_byte( &mem_image[i] );
    SPI.transfer( data );
  }
  digitalWrite( TFT_CS, HIGH );
}



/*****************************************************************************
   @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
   @date       :2018-08-09
   @function   :Set coordinate value
   @parameters :Xpos:the  x coordinate of the pixel
                Ypos:the  y coordinate of the pixel
   @retvalue   :None
******************************************************************************/
void TFT_SetCursor( uint16_t Xpos, uint16_t Ypos)
{
  TFT_SetWindow( Xpos, Ypos, Xpos, Ypos );
}


// ---------------------------------------------------------------
/*****************************************************************************
   @name       :void TFT_DrawPoint(u16 x,u16 y)
   @date       :2018-08-09
   @function   :Write a pixel data at a specified location
   @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
   @retvalue   :None
******************************************************************************/

void TFT_DrawPoint( uint16_t x, uint16_t y, uint16_t color )
{
  TFT_SetCursor( x, y );
  TFT_WriteData_16Bit( color );
}
// ---------------------------------------------------------------

/*****************************************************************************
   @name       :void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
   @date       :2018-08-09
   @function   :Display a single English character
   @parameters :x:the bebinning x coordinate of the Character display position
                y:the bebinning y coordinate of the Character display position
                fc:the color value of display character
                bc:the background color of display character
                num:the ascii code of display character(0~94)
                size:the size of display character
                mode:0-no overlying,1-overlying
   @retvalue   :None
******************************************************************************/
/***************************************************************************************
** Function name:           drawChar
** Description:             draw a single character in the Adafruit GLCD font
***************************************************************************************/
void TFT_drawChar( uint16_t x, uint16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)
{
  if (size == 1) // default size
  {
    for (int8_t i = 0; i < 5; i++ )
    {
      uint8_t line = pgm_read_byte(font + c * 5 + i);
      if (line & 0x1)  TFT_DrawPoint(x + i, y, color);
      if (line & 0x2)  TFT_DrawPoint(x + i, y + 1, color);
      if (line & 0x4)  TFT_DrawPoint(x + i, y + 2, color);
      if (line & 0x8)  TFT_DrawPoint(x + i, y + 3, color);
      if (line & 0x10) TFT_DrawPoint(x + i, y + 4, color);
      if (line & 0x20) TFT_DrawPoint(x + i, y + 5, color);
      if (line & 0x40) TFT_DrawPoint(x + i, y + 6, color);
      if (line & 0x80) TFT_DrawPoint(x + i, y + 7, color);
    }
  }
  else
  {
    for (int8_t i = 0; i < 5; i++ )
    {
      uint8_t line = pgm_read_byte(font + c * 5 + i);
      for (int8_t j = 0; j < 8; j++)
      {
        if (line & 0x1)
          TFT_fillRect(x + (i * size), y + (j * size), size, size, color);
        else
          if (color != bg )
            TFT_fillRect(x + i * size, y + j * size, size, size, bg);
          
        line >>= 1;
      }
    }
  }
}
 

// ---------------------------------------------------------------
/*****************************************************************************
   @name       :u32 mypow(u8 m,u8 n)
   @date       :2018-08-09
   @function   :get the nth power of m (internal call)
   @parameters :m:the multiplier
                n:the power
   @retvalue   :the nth power of m
******************************************************************************/
uint32_t TFT_mypow( uint8_t m, uint8_t n)
{
  uint32_t result = 1;
  while (n--)result *= m;
  return result;
}

// ---------------------------------------------------------------

/*****************************************************************************
   @name       :void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
   @date       :2018-08-09
   @function   :Display number
   @parameters :x:the bebinning x coordinate of the number
                y:the bebinning y coordinate of the number
                num:the number(0~4294967295)
                len:the length of the display number
                size:the size of display number
   @retvalue   :None
******************************************************************************/
void TFT_ShowNum( uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size)
{
  uint8_t t, temp;
  uint8_t enshow = 0;
  for (t = 0; t < len; t++)
  {
    temp = (num / TFT_mypow(10, len - t - 1)) % 10;
    if (enshow == 0 && t < (len - 1))
    {
      if (temp == 0)
      {
        //TFT_ShowChar(x + (size / 2)*t, y, POINT_COLOR, BACK_COLOR, ' ', size, 0);
        continue;
      } else enshow = 1;

    }
    //    TFT_ShowChar(x + (size / 2)*t, y, POINT_COLOR, BACK_COLOR, temp + '0', size, 0);
  }
}
// ---------------------------------------------------------------

/*****************************************************************************
   @name       :void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode)
   @date       :2018-08-09
   @function   :Display English string
   @parameters :x:the bebinning x coordinate of the English string
                y:the bebinning y coordinate of the English string
                p:the start address of the English string
                size:the size of display character
                mode:0-no overlying,1-overlying
   @retvalue   :None
******************************************************************************/
void TFT_ShowString( uint16_t x, uint16_t y, char *p, uint16_t fc, uint16_t bc, uint8_t size )
{
  while ((*p <= '~') && (*p >= ' '))
  {
    if (x > (TFT_W - 1) || y > (TFT_H - 1))
      return;
    TFT_drawChar( x, y, *p, fc, bc, size );
    x += size*6;
    p++;
  }
}
