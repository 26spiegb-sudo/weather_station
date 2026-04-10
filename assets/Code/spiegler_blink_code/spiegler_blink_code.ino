#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

void setup() {
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
}

void loop() {
    tft.fillScreen(0xF800);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(4);
    tft.setCursor(90, 110);
    tft.print("RED");
    delay(2000);

    tft.fillScreen(0x001F);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(4);
    tft.setCursor(75, 110);
    tft.print("BLUE");
    delay(2000);
}