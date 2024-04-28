#ifndef _SST25VF_H
  #define _SST25VF_H
  
  #include <SPI.h>

  #define FLASH_MAX_BYTES 2097152 //this chip contains this much storage
  #define FLASH_MAX_SECTOR 512 //each sector is 4096 bytes
  
  void SST25VF_INIT( void );
  void SST25VF_readID( void );

  void SST25VF_readInit( uint32_t address );
  uint8_t SST25VF_readNext( void );
  void SST25VF_readFinish( void );
  void SST25VF_readArray( uint32_t address, uint8_t *dataBuffer, uint16_t dataLength );

  void SST25VF_waitUntilDone( void );
  void SST25VF_setAddress( uint32_t addr );
  //void SST25VF_enable() {};  //  { SPI.setBitOrder(MSBFIRST); nop(); }
  //void SST25VF_disable() {}; //  { SPI.setBitOrder(LSBFIRST); nop(); }
  inline void volatile nop(void) { asm __volatile__ ("nop"); }
  
//	void SST25VF_totalErase( void );
//	void SST25VF_sectorErase(uint8_t sectorAddress);
//	
  void SST25VF_writeByte(uint32_t address, uint8_t data);
//	uint32_t SST25VF_writeArray(uint32_t address,const uint8_t dataBuffer[],uint16_t dataLength);

#endif // _SST25VF_H
