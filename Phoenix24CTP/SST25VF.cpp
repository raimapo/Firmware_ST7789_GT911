#include "config.h"
#include "SST25VF.h"

 
void SST25VF_INIT( void )
{		

  pinMode( FLASH_WP, OUTPUT ); 
  digitalWrite( FLASH_WP, HIGH ); //write protect off

  pinMode( FLASH_HOLD, OUTPUT );
  digitalWrite( FLASH_HOLD, HIGH ); //mem hold off
	
  pinMode( FLASH_CS, OUTPUT ); //chip select 
  digitalWrite( FLASH_CS, HIGH );

  digitalWrite(FLASH_CS,LOW);
  SPI.transfer(0x50); //enable write status register instruction
  digitalWrite(FLASH_CS,HIGH);
  delay(50);
  digitalWrite(FLASH_CS,LOW);
  SPI.transfer(0x01); //write the status register instruction
  SPI.transfer(0x00);//value to write to register - xx0000xx will remove all block protection
  digitalWrite(FLASH_CS,HIGH);
  delay(50);

  #if ( MY_DEBUG )
    SST25VF_readID();
  #endif 
}
 

// ======================================================================================= //

void SST25VF_waitUntilDone( void )
{
  uint8_t data = 0;
  while (1)
  {
    digitalWrite(FLASH_CS,LOW);
    (void) SPI.transfer(0x05);
    data = SPI.transfer(0);
    digitalWrite(FLASH_CS,HIGH);
    if (!bitRead(data,0)) break;
    nop();
  }
}

// ======================================================================================= //

//void SST25VF_init()
//{

//  digitalWrite(FLASH_CS,LOW);
//  SPI.transfer(0x50); //enable write status register instruction
//  digitalWrite(FLASH_CS,HIGH);
//  delay(50);
//  digitalWrite(FLASH_CS,LOW);
//  SPI.transfer(0x01); //write the status register instruction
//  SPI.transfer(0x00);//value to write to register - xx0000xx will remove all block protection
//  digitalWrite(FLASH_CS,HIGH);
//  delay(50);

//}

// ======================================================================================= //

void SST25VF_readID( void )
{
  uint8_t id, mtype, dev;

  digitalWrite(FLASH_CS,LOW);
  SPI.transfer(0x9F); // Read ID command
  id = SPI.transfer(0);
  mtype = SPI.transfer(0);
  dev = SPI.transfer(0);
  char buf[16] = {0};
  sprintf(buf, "%02X %02X %02X", id, mtype, dev);
  Serial.print("SPI ID ");
  Serial.println(buf);
  digitalWrite(FLASH_CS,HIGH);
}

// ======================================================================================= //

//void SST25VF_totalErase()
//{
//  digitalWrite(FLASH_CS,LOW);
//  SPI.transfer(0x06);//write enable instruction
//  digitalWrite(FLASH_CS,HIGH);
//  nop();
//  digitalWrite(FLASH_CS, LOW); 
//  (void) SPI.transfer(0x60); // Erase Chip //
//  digitalWrite(FLASH_CS, HIGH);
//  SST25VF_waitUntilDone();
//}

// ======================================================================================= //

void SST25VF_setAddress( uint32_t addr )
{
  SPI.transfer(addr >> 16);
  SPI.transfer(addr >> 8);  
  SPI.transfer(addr);
}

// ======================================================================================= //

void SST25VF_readInit( uint32_t address )
{
  digitalWrite( FLASH_CS, LOW );
  SPI.transfer( 0x03 ); // Read Memory - 25/33 Mhz //
  SST25VF_setAddress( address );
}

// ======================================================================================= //

uint8_t SST25VF_readNext( void )
{ 
	return SPI.transfer( 0 ); 	
}

// ======================================================================================= //

void SST25VF_readFinish( void )
{
  digitalWrite( FLASH_CS, HIGH );
}

// ======================================================================================= //

void SST25VF_writeByte(uint32_t address, uint8_t data)
{
  digitalWrite(FLASH_CS,LOW);
  SPI.transfer(0x06);//write enable instruction
  digitalWrite(FLASH_CS,HIGH);
  nop();
  digitalWrite(FLASH_CS,LOW);
  (void) SPI.transfer(0x02); // Write Byte //
  SST25VF_setAddress(address);
  (void) SPI.transfer(data);
  digitalWrite(FLASH_CS,HIGH);
  SST25VF_waitUntilDone();
}

//uint32_t SST25VF_writeArray(uint32_t address,const uint8_t dataBuffer[],uint16_t dataLength)
//{
//	for( uint16_t i=0; i<dataLength; i++ )
//  {
//    writeByte((uint32_t)address+i, dataBuffer[i]);
//  }
//	return address + dataLength;
//}

void SST25VF_readArray( uint32_t address, uint8_t *dataBuffer, uint16_t dataLength )
{
  SST25VF_readInit( address );
  for ( uint16_t i=0; i<dataLength; ++i )
  {
    *dataBuffer++ = SST25VF_readNext();
  }
  SST25VF_readFinish();
}

// ======================================================================================= //

//void SST25VF_sectorErase(uint8_t sectorAddress)
//{
//  digitalWrite(FLASH_CS,LOW);
//  SPI.transfer(0x06);//write enable instruction
//  digitalWrite(FLASH_CS,HIGH);
//  nop();
//  digitalWrite(FLASH_CS,LOW);
//  (void) SPI.transfer(0x20); // Erase 4KB Sector //
//  SST25VF_setAddress(4096UL*long(sectorAddress));
//  digitalWrite(FLASH_CS,HIGH);
//  SST25VF_waitUntilDone();
//}
