// ===============================================================
// INCLUDES
// ===============================================================
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>
#include "config.h"
#include "SST25VF.h"
#include "TFT_driver.h"
#include "CTP_driver.h"
#include <EEPROM.h>


//colors
const uint16_t color_background = TFT_RGB565( 3, 10, 56 );

uint8_t pic_nr=1;

// touch
struct FINGER
{
  uint8_t valid;
  uint16_t x;
  uint16_t y;
};

struct FINGER finger;

uint16_t x, y;
uint8_t counter;
uint8_t draw = 0;


// -------------------------------------------------------LED_init

void LED_KEY_init()
{
  pinMode( LED_R, OUTPUT );
  digitalWrite( LED_R, LED_OFF );
  pinMode( LED_G, OUTPUT );
  digitalWrite( LED_G, LED_OFF );
  pinMode( LED_B, OUTPUT );
  digitalWrite( LED_B, LED_OFF );
  pinMode( LED_BUILTIN, OUTPUT );
  digitalWrite( LED_BUILTIN, LED_OFF );

  pinMode( KEY,INPUT_PULLUP );
}

// --------------------------------------------------------LED_RGB

void LED_RGB( uint8_t r, uint8_t g, uint8_t b)
{
  analogWrite( LED_R, 255 - r );
  analogWrite( LED_G, 255 - g );
  analogWrite( LED_B, 255 - b );
}

// -------------------------------------------------------fade_out

void fade_out()
{
  for ( uint8_t i = 250; i > 50; i -= 2 )
  {
    analogWrite( TFT_BL, i );
    delay( fade_out_step_time );
  }
  analogWrite( TFT_BL, 0 );
}

// --------------------------------------------------------fade_in
// ---------------------------------------------------------------
void fade_in()
{
  for ( uint8_t i = 50; i < 250; i += 2 )
  {
    analogWrite( TFT_BL, i );
    delay( fade_in_step_time );
  }
  analogWrite( TFT_BL, 255 );
}

// -------------------------------------------------WAIT_INPUT

void WAIT_INPUT()
{
  uint8_t buf[6], i, f1=0, f2=0;

  finger.valid = 0;

  while ( finger.valid == 0 )
  {
    CTP_READ( GOODIX_READ_COOR_ADDR, 6, &buf[0] );
    switch ( buf[0] )
    {
      case 0x81 : if (++f1 > 3)
                  {
                    finger.x = (uint16_t)((buf[3] << 8) + buf[2]);
                    finger.y = (uint16_t)((buf[5] << 8) + buf[4]);
                    finger.valid = 1;
                  }
                  break;
      case 0x82 : if (++f2 > 20)
                  {
                    finger.valid = 2;
                  }
                  break;
      default :   f1 = 0;
                  f2 = 0;
                  break;
    }
    CTP_restart();
    
    if (digitalRead( KEY ) == LOW)
    {
      finger.valid = 2;
      while (digitalRead( KEY ) == LOW) {}; 
    }
    delay( 20 );
  }
}

// -----------------------------------------------------------sub1

void sub1( unsigned long time_out )
{
  uint8_t buf[6], exit_loop;
  uint8_t y, u_counter, d_counter;
  char my_name[20];

  uint8_t yl[] = {0, 73, 100, 126, 146, 161 };
  uint32_t start[] = { 0, pic_sub1_1, pic_sub1_2, pic_sub1_3, pic_sub1_4, pic_sub1_5, pic_sub1_s };
  unsigned int y_old;

  uint8_t demo_done=0;
  unsigned long t;

  TFT_FULLPIC( 153600 );
  fade_in();

  y = 3;
  y_old = 3;
  exit_loop = 0;
  u_counter = 0;
  d_counter = 0;

  t = millis() + time_out;

  while ( (demo_done==0) && (exit_loop < 5) )
  {
    if (millis()>t) demo_done=1;
    
    CTP_READ( GOODIX_READ_COOR_ADDR, 6, &buf[0] );
    if ( buf[0] == 0x81 )
    {
      t = millis() + time_out;
      finger.x = (uint16_t)((buf[3] << 8) + buf[2]);
      finger.y = (uint16_t)((buf[5] << 8) + buf[4]);

      //check EXIT
      if ( (finger.x < 40) && (finger.y < 40) )
      {
        exit_loop++;
      }
      else
      {
        exit_loop = 0;
      }

      //check UP
      if ( (finger.x > 201) && (finger.x < 201 + 86) && (finger.y > 18) && ((finger.y < 18 + 86)) )
      {
        if ( u_counter++ > 9 )
        {
          u_counter = 0;
          if (y > 1) y--;
          TFT_SetWindow( 13, 112, 13 + 59 - 1, 112 + 19 - 1 );
          TFT_PARTIALPIC( start[y], 59, 19 );
          delay( 100 );
        }
      }
      else
      {
        u_counter = 0;
      }

      // check DOWN
      if ( (finger.x > 201) && (finger.x < 201 + 86) && (finger.y > 137) && ((finger.y < 137 + 86)) )
      {
        if ( d_counter++ > 9 )
        {
          d_counter = 0;
          if (y < 5) y++;
          sprintf( my_name, "sub1_%d.bin", y );
          TFT_SetWindow( 13, 112, 13 + 59 - 1, 112 + 19 - 1 );
          TFT_PARTIALPIC( start[y], 59, 19 );
          delay( 100 );
        }
      }
      else
      {
        d_counter = 0;
      }

      // check if move requiered
      if (y != y_old )
      {
        if (y > y_old)
        {
          for (uint8_t i = yl[y_old]; i < yl[y]; i++ )
          {
            TFT_SetWindow( 89, i, 89 + 66 - 1, i + 9 - 1 );
            TFT_PARTIALPIC( start[6], 66, 9 );
          }
        }
        else
        {
          for (uint8_t i = yl[y_old]; i > yl[y]; i-- )
          {
            TFT_SetWindow( 89, i, 89 + 66 - 1, i + 9  - 1 );
            TFT_PARTIALPIC( start[6], 66, 9);
          }
        }
        y_old = y;
      }

    }
    else
    {
      exit_loop = 0;
    }
    CTP_restart();
    delay( 20 );
  }
}

// -----------------------------------------------------------sub2

void sub2( unsigned long time_out )
{
  uint8_t buf[6], exit_loop;
  uint8_t y, u_counter, d_counter;
  uint8_t demo_done=0;
  unsigned long t;

  uint32_t start[] = { 0, pic_sub2_01, pic_sub2_02, pic_sub2_03, pic_sub2_04, pic_sub2_05, pic_sub2_06, pic_sub2_07, pic_sub2_08, pic_sub2_09, pic_sub2_10, pic_sub2_11, pic_sub2_12 };
  
  TFT_FULLPIC( pic_sub2 );
  fade_in();

  u_counter = 0;
  d_counter = 0;
  exit_loop = 0;
  y=8;
  t = millis() + time_out;

  while ( (demo_done==0) && (exit_loop < 5) )
  {
    if (millis()>t)demo_done=1;
    
    CTP_READ( GOODIX_READ_COOR_ADDR, 6, &buf[0] );
    if ( buf[0] == 0x81 )
    {
      t = millis() + time_out;
      finger.x = (uint16_t)((buf[3] << 8) + buf[2]);
      finger.y = (uint16_t)((buf[5] << 8) + buf[4]);
      if ( (finger.x < 40) && (finger.y < 40) )
      {
        exit_loop++;
      }
      else
      {
        exit_loop = 0;
      }
     //check UP
      if ( (finger.x > 201) && (finger.x < 201 + 86) && (finger.y > 18) && ((finger.y < 18 + 86)) )
      {
        if ( u_counter++ > 9 )
        {
          u_counter = 0;       
          if (y < 12) 
          {
            y++;
            TFT_SetWindow( 23, 59, 23 + 82 - 1, 59 + 27 - 1 );
            TFT_PARTIALPIC( start[y], 82, 27 );
            delay( 100 );
          }
        }
      }
      else
      {
        u_counter = 0;
      }

      // check DOWN
      if ( (finger.x > 201) && (finger.x < 201 + 86) && (finger.y > 137) && ((finger.y < 137 + 86)) )
      {
        if ( d_counter++ > 9 )
        {
          d_counter = 0;
          if (y > 1)
          {
            y--;          
            TFT_SetWindow( 23, 59, 23 + 82 - 1, 59 + 27 - 1 );
            TFT_PARTIALPIC( start[y], 82, 27 );
            delay( 100 );            
          }
        }
      }
      else
      {
        d_counter = 0;
      }      
    }
    else
    {
      exit_loop = 0;
    }
    CTP_restart();
    delay( 20 );
  }
}

// -----------------------------------------------------------sub3

void sub3( unsigned long time_out )
{
  const uint16_t slider = TFT_RGB565( 188, 190, 202);
  uint8_t buf[6], exit_loop;
  uint8_t r=142/2, g=192/2, b=63/2;
  uint16_t rpos=171, gpos=222, bpos=91;
  
  uint8_t demo_done=0;
  unsigned long t;

  TFT_FULLPIC( pic_sub3 );
  fade_in();
  LED_RGB( r, g, b );
  
  CTP_ClearBuffer();
  
  exit_loop = 0;
  t = millis() + time_out;

  while ( (demo_done==0) && (exit_loop < 5) )
  {
    LED_RGB( r, g, b );
    if (millis()>t) demo_done=1;
    
    CTP_READ( GOODIX_READ_COOR_ADDR, 6, &buf[0] );
    if ( buf[0] == 0x81 )
    {
      t = millis() + time_out;
      finger.x = (uint16_t)((buf[3] << 8) + buf[2]);
      finger.y = (uint16_t)((buf[5] << 8) + buf[4]);
      if ( (finger.x < 40) && (finger.y < 40) )
      {
        exit_loop++;
      }
      else
      {
        exit_loop = 0;
      }

      //check red slider
      if ((finger.x>29)&& (finger.x<284) && (finger.y>81) && (finger.y<102))
      {
       TFT_fillRect( rpos, 82-3, 6, 3, color_background );
       TFT_fillRect( rpos, 82, 6, 20, RGB565_RED );
       TFT_fillRect( rpos, 82+20, 6, 3, color_background );
       r=(finger.x-30)/2;
       rpos=finger.x;
       TFT_fillRect( rpos, 82-3, 6, 26, slider );
      }

      //check green slider
      if ((finger.x>29)&& (finger.x<284) && (finger.y>133) && (finger.y<154))
      {
       TFT_fillRect( gpos, 134-3, 6, 3, color_background );
       TFT_fillRect( gpos, 134, 6, 20, RGB565_GREEN );
       TFT_fillRect( gpos, 134+20, 6, 3, color_background );
       g=(finger.x-30)/2;
       gpos=finger.x;
       TFT_fillRect( gpos, 134-3, 6, 26, slider );
      }

      //check blue slider
      if ((finger.x>29)&& (finger.x<284) && (finger.y>185) && (finger.y<206))
      {
       TFT_fillRect( bpos, 186-3, 6, 3, color_background );
       TFT_fillRect( bpos, 186, 6, 20, RGB565_BLUE );
       TFT_fillRect( bpos, 186+20, 6, 3, color_background );
       b=(finger.x-30)/2;
       bpos=finger.x;
       TFT_fillRect( bpos, 186-3, 6, 26, slider );
      }
            
    }
    else
    {
      exit_loop = 0;
    }
    CTP_restart();
    delay( 10 );
  }
  LED_RGB( 0, 0, 0 );
}

// -----------------------------------------------------------sub4

void sub4( unsigned long time_out )
{
  uint8_t buf[6], exit_loop;
  uint8_t demo_done=0;
  unsigned long t;
  char my_name[20];

  uint32_t start[] = { 0, pic_sub4_1, pic_sub4_2, pic_sub4_3 };
  
  // random :-)
  pic_nr = random( 1, 4 );

  TFT_FULLPIC( start[ pic_nr ] );
  fade_in();

  exit_loop = 0;
  t = millis() + time_out;

  while ( (millis() < t) && (exit_loop < 5) )
  {
    if (millis()>t)demo_done=1;
    
    CTP_READ( GOODIX_READ_COOR_ADDR, 6, &buf[0] );
    if ( buf[0] == 0x81 )
    {
      t = millis() + time_out;
      finger.x = (uint16_t)((buf[3] << 8) + buf[2]);
      finger.y = (uint16_t)((buf[5] << 8) + buf[4]);
      if ( (finger.x < 40) && (finger.y < 40) )
      {
        exit_loop++;
      }
      else
      {
        exit_loop = 0;
      }
    }
    else
    {
      exit_loop = 0;
    }
    CTP_restart();
    delay( 20 );
  }
}

// -----------------------------------------------------HOMESCREEN

uint8_t HOMESCREEN(void)
{
  uint8_t sub_nr = 0;
  uint16_t x, y;

  TFT_FULLPIC( pic_home );
  fade_in();
  pinMode( KEY,INPUT_PULLUP );
  
  while ( sub_nr == 0 )
  { 
    WAIT_INPUT();

    if ( finger.valid == 2 )
    {
      sub_nr = 5;
    }
    else
    {
      x = finger.x;
      y = finger.y;

      if ( (x >   6) & (x < 148) & (y >   6) & (y < 117) ) sub_nr = 1;
      if ( (x > 166) & (x < 308) & (y >   6) & (y < 117) ) sub_nr = 2;
      if ( (x >   6) & (x < 148) & (y > 123) & (y < 234) ) sub_nr = 3;
      if ( (x > 166) & (x < 308) & (y > 123) & (y < 234) ) sub_nr = 4;
    }
  }

  fade_out();
  return ( sub_nr );
}

// ----------------------------------------------------------setup

void setup()
{
  unsigned int magic1, magic2;
  
  LED_KEY_init();

  #if ( MY_DEBUG )
    Serial.begin( 115200, SERIAL_8N1 );
    delay( 1000 );
    while ( !Serial ) {};
    delay( 500 );
    Serial.println( "Starting demo" );
  #endif

  // init SPI-library
  SPI.begin();
  SPI.beginTransaction( SPISettings( SPEED_SPI, MSBFIRST, SPI_MODE0 ) );

  // init I2C-library
  Wire.begin();
  Wire.setClock( SPEED_I2C );

  TFT_INIT();
  CTP_INIT();
  #if ( MY_DEBUG )
    CTP_INFO();
  #endif
  
  SST25VF_INIT();

  for ( uint8_t i = 0; i < 10; i++ ) randomSeed( analogRead(0) );

  // highscore
  // EEPROM.write( 0, 0 );
  
  if ( (EEPROM.read(1) != 'H' ) || (EEPROM.read(2) != 'P' ) )
  {
    #if ( MY_DEBUG )
      Serial.println( "Resetting HighScore" );
    #endif    
    EEPROM.write( 0,   0 );
    EEPROM.write( 1, 'H' );
    EEPROM.write( 2, 'P' );    
  }
}

// -----------------------------------------------------------loop

void loop( void )
{
  uint8_t sub_nr;
  
  #if ( MY_DEBUG )
    Serial.println( "loop started" );
  #endif

  sub_nr=0;   
  while ( 1 )
  {
    sub_nr = HOMESCREEN();   

    switch ( sub_nr )
    {
      case 1  : sub1(  5000 ); break;
      case 2  : sub2(  5000 ); break;
      case 3  : sub3( 10000 ); break;
      case 4  : sub4(  5000 ); break;
      default :                break;
    }
    fade_out();
  }
}
