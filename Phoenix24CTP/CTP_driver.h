#ifndef _CTP_H
  #define _CTP_H

  // GOODIX definitions
  #define GOODIX_I2C_ADDR_28  (0x28 >> 1)
  #define GOODIX_I2C_ADDR_BA  (0xBA >> 1)

  #define ConfigLen 186

  #define GOODIX_REG_CONFIG_DATA  0x8047
  #define GOODIX_REG_ID           0x8140 
  #define GOODIX_READ_COOR_ADDR   0x814E

  #define GOODIX_RESET         0x01
  #define GOODIX_DEVICE_ID     0x02
  #define GOODIX_TOUCH_STATUS  0x79
  #define GOODIX_FINGER_0      0x7C
  #define GOODIX_large_detect  0x40

  #define touch_max_x 320
  #define touch_max_y 240

  union my_fingers
  {
    uint8_t data[80];
    struct 
    {
      uint8_t track_id;
      uint8_t x_L;
      uint8_t x_H;
      uint8_t y_L;
      uint8_t y_H; 
      uint8_t touch_size_L;     
      uint8_t touch_size_H;
      uint8_t reserved;
    } touch_point[10];
  };
  
  
  void RESET_CTP( void );
  uint8_t CTP_touch_alive( void );
  uint8_t CTP_INIT( void );

  uint8_t CTP_WRITE( uint16_t reg_addr, uint8_t len, uint8_t *data );
  uint8_t CTP_READ( uint16_t reg_addr, uint8_t len, uint8_t *buf );

  //bool CTP_getTouchData( void );
    
  void CTP_INFO( void );
  void CTP_restart( void );
  void CTP_ClearBuffer(void);

#endif  // _CTP_H 
