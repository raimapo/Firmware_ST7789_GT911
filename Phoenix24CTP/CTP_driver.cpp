/*****************************************************************************
* | File      	:	CTP_Driver.c
* | Author      : admatec team
* | Function    : ctp driver
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
#include <Wire.h>
#include "config.h"
#include "CTP_driver.h"


uint8_t _i2cadr = GOODIX_I2C_ADDR_BA;
uint8_t num_sensor=0, num_driver=0;

 
// ===============================================================
// Functions
// ===============================================================

void RESET_CTP( void )
{
  pinMode( CTP_RESET, OUTPUT );
  digitalWrite( CTP_RESET, LOW );

  pinMode( CTP_IRQ, OUTPUT );
  digitalWrite( CTP_IRQ, LOW );

  delay( 50 );
  
    /* HIGH: 0x28/0x29 (0x14 7bit), LOW: 0xBA/0xBB (0x5D 7bit) */
  digitalWrite( CTP_IRQ, _i2cadr==GOODIX_I2C_ADDR_28 );
  delay( 50 );

  digitalWrite( CTP_RESET, HIGH );
  delay( 100 );

  // change CTP_INT to input
  pinMode( CTP_IRQ, INPUT );
  delay( 200 );
}




uint8_t CTP_touch_alive( void )
{
  Wire.beginTransmission( _i2cadr );
  uint8_t value = Wire.endTransmission();
  return ( value );
}




uint8_t CTP_INIT()
{
  #ifdef MY_DEBUG
    Serial.println( F("GOODIX: init") );
  #endif
 
  RESET_CTP();

  uint8_t value = CTP_touch_alive();

  #ifdef MY_DEBUG
    Serial.println( F(value == 0 ? "GOODIX: OK" : "CTP init error") );
  #endif
  
  return ( value );
}




uint8_t CTP_WRITE( uint16_t reg_addr, uint8_t len, uint8_t *data )
{ 
  Wire.beginTransmission( _i2cadr );
  Wire.write( highByte( reg_addr ) );
  Wire.write( lowByte( reg_addr ) );
  Wire.write( &data[0], len );
  return( Wire.endTransmission() );
}





uint8_t CTP_READ( uint16_t reg_addr, uint8_t len, uint8_t *buf )
{
  uint8_t result;
  
  Wire.beginTransmission( _i2cadr );
  Wire.write( highByte( reg_addr ) );
  Wire.write(  lowByte( reg_addr ) );
  result = Wire.endTransmission();

  if (result != 0)
    return ( result );

  Wire.requestFrom( _i2cadr, len );
  delay( 1 );

  while( Wire.available() && (len-->0) )
  {
    *buf++ = Wire.read();
  }

  return( Wire.endTransmission() );
}





uint8_t CTP_check_ic_config()
{
   uint8_t i, i2c_buf, raw_cfg_len, CheckSum=0;

   raw_cfg_len = ConfigLen-2;
   for( i=0; i<raw_cfg_len; i++ )
   {
      CTP_READ( GOODIX_REG_CONFIG_DATA+i, 1, &i2c_buf );
      CheckSum += i2c_buf;
   }
   
   CheckSum = (~CheckSum) + 1;   
   CTP_READ( GOODIX_REG_CONFIG_DATA+raw_cfg_len, 1, &i2c_buf );

   if( CheckSum == i2c_buf )
      return 0;
   else
      return -1;
}




void CTP_getTouchData( void )
{
//  uint8_t buf[6];  
//  
//  finger.x = 0xFFFF;
//  finger.y = 0xFFFF;
//  
//  CTP_READ( GOODIX_READ_COOR_ADDR, 6, &buf[0] );
//  if( buf[0] == 0x81 )
//  {
//    digitalWrite( LED_BUILTIN, LED_ON );
//    while( buf[0] == 0x81 )
//    {
//      finger.x = (uint16_t)((buf[3]<<8) + buf[2]);
//      finger.y = (uint16_t)((buf[5]<<8) + buf[4]);
//      buf[0] = 0;
//      CTP_WRITE( GOODIX_READ_COOR_ADDR, 1, &buf[0] );
//      delay( 10 );
//      CTP_READ( GOODIX_READ_COOR_ADDR, 6, &buf[0] );
//    }
//    while( buf[0] != 0 )
//    {
//      buf[0] = 0;
//      CTP_WRITE( GOODIX_READ_COOR_ADDR, 1, &buf[0] );
//      delay( 20 );
//      CTP_READ( GOODIX_READ_COOR_ADDR, 1, &buf[0] );
//    }
//    
//  }
//  else
//  {
//    digitalWrite( LED_BUILTIN, LED_OFF );
//  }
//  buf[0] = 0;
//  CTP_WRITE( GOODIX_READ_COOR_ADDR, 1, &buf[0] );
}










void CTP_INFO( void )
{
  uint8_t i2c_buf[50];

  Serial.println( "\nGOODIX-Info" );
  
  // check I2C status
  uint8_t value = CTP_touch_alive();

  Serial.print("I2Cadr=" );
  Serial.print( _i2cadr, HEX );
  Serial.print( ", I2C_stat=" );
  Serial.print( value );
  switch ( value )
  {
    case 0 :  Serial.println( "=OK");
              break;
    case 1 :  Serial.println( "=very strange");
              break;
    case 2 :  Serial.println( "=NACK on addr");
              break;
    case 3 :  Serial.println( "=NACK on data");
              break;
    default : Serial.println( "=very strange error");
              break;        
  }


  // get product ID
  CTP_READ( GOODIX_REG_ID, 11, &i2c_buf[0] );
  Serial.println( "product info" );
  Serial.print( "  ID: " );
  Serial.print( char( i2c_buf[0] ) );
  Serial.print( char( i2c_buf[1] ) );
  Serial.print( char( i2c_buf[2] ) );
  Serial.println( char( i2c_buf[3] ) );
  
  Serial.print( "  FW: " );
  Serial.println( word( i2c_buf[5], i2c_buf[4]), HEX );

  Serial.print( "  max_x: " );
  Serial.println( word( i2c_buf[7], i2c_buf[6]) );

  Serial.print( "  max_y: " );
  Serial.println( word( i2c_buf[9], i2c_buf[8]) );

  Serial.print( "  vendor ID: " );
  Serial.println( i2c_buf[10] );


  CTP_READ( 0x8062, 3, &i2c_buf[0] );
  Serial.print( "  Number of driver A: " );
  Serial.println( i2c_buf[0] & 0x1F, HEX );
  Serial.print( "  Number of driver B: " );
  Serial.println( i2c_buf[1] & 0x1F, HEX );
  num_driver = (i2c_buf[0] & 0x1F) + (i2c_buf[1] & 0x1F);

  Serial.print( "  Number of sensor A: " );
  Serial.println( i2c_buf[2] & 0x0F, HEX );
  Serial.print( "  Number of sensor B: " );
  Serial.println( i2c_buf[2]>>4, HEX );
  num_sensor = (i2c_buf[2] & 0x0F) + (i2c_buf[2]>>4);


//  // ITO sensor
//  CTP_READ( 0x80B7, 14, &i2c_buf[0] );
//  for (uint8_t i=0; i<14; i++)
//  {
//      Serial.println( i2c_buf[i] );
//  }
//
//  Serial.println( "  " );
//
//  // ITO driver
//  CTP_READ( 0x80D5, 26, &i2c_buf[0] );
//  for (uint8_t i=0; i<26; i++)
//  {
//      Serial.println( i2c_buf[i] );
//  }



  // check config status
  Serial.print( "config checksum ");
  if ( CTP_check_ic_config() ) 
    Serial.println( "error" );
  else
    Serial.println( "OK" );


  // check config information
  CTP_READ( 0x8047, 7, &i2c_buf[0] );
  
  Serial.println( "config data" );
  Serial.print( "  config number: " );
  Serial.print( i2c_buf[0] );
  Serial.print( "=0x" );
  Serial.println( i2c_buf[0], HEX );


  Serial.print( "  max_x: " );
  Serial.println( word( i2c_buf[2], i2c_buf[1]) );

  Serial.print( "  max_y: " );
  Serial.println( word( i2c_buf[4], i2c_buf[3]) );
  
  Serial.print( "  max_fingers: " );
  Serial.println( i2c_buf[5] & 0x0F );

  Serial.print( "  int_mode: " );
  switch( i2c_buf[6] & 0x03 )
  {
    case 0 :  Serial.println( "rising edge" );
              break;
    case 1 :  Serial.println( "falling edge" );
              break;
    case 2 :  Serial.println( "low level" );
              break;
    default:  Serial.println( "high level" );
              break;
  }

  Serial.println();
}

void CTP_restart()
{
  uint8_t restart=0;
  CTP_WRITE( GOODIX_READ_COOR_ADDR, 1, &restart );
}


void CTP_ClearBuffer() // dummy read to clean buffer
{
  uint8_t buf[6];
  for ( uint8_t i=0; i<5; i++ )
  {
    CTP_READ( GOODIX_READ_COOR_ADDR, 1, &buf[0] );      
    CTP_restart();
    delay( 20 );
  }  
}
