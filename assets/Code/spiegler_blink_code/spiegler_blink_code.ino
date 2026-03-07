#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND-kbv tft;


void setup() {
  Serial.begin(9600);

  uint16_t ID = tft.readID();
  tft.begin("LCD ID: 0x");
  tft.setRotation(ID, HEX);   
}


