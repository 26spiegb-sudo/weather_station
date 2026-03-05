#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

/* Simple color definitions */
#define BLACK   0x0000
#define RED     0xF800
#define BLUE    0x001F
#define WHITE   0xFFFF

MCUFRIEND_kbv tft;

bool state = false;

void setup() {
  Serial.begin(9600);

  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);   // Landscape
}

void loop() {
  state = !state;

  if (state) {
    tft.fillScreen(RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(6);
    tft.setCursor(80, 100);
    tft.print("ON");
  } else {
    tft.fillScreen(BLUE);
    tft.setTextColor(WHITE);
    tft.setTextSize(6);
    tft.setCursor(60, 100);
    tft.print("OFF");
  }

  delay(1000);  // 1 second = blink speed
}
