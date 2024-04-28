#include <Arduino.h>
#include <GT911.h>


//  SDA 15 pin display - 21 ESP32 DOIT board
//  SCL 14 pin display - 22 ESP32 DOIT board
//  GND 2 pin display
//  VCC 11 pin display

GT911 ts = GT911();

void setup() {
  Serial.begin(115200);
  ts.begin();
}

void loop() {
  uint8_t touches = ts.touched(GT911_MODE_POLLING);

  if (touches) {
    GTPoint* tp = ts.getPoints();
    for (uint8_t  i = 0; i < touches; i++) {
      Serial.printf("#%d  %d,%d s:%d\n", tp[i].trackId, tp[i].x, tp[i].y, tp[i].area);
    }
  }
}