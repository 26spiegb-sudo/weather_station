#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold24pt7b.h>

MCUFRIEND_kbv tft;
Adafruit_BME280 bme;

float tempMax = -1000;
float tempMin = 1000;
unsigned long startTime;

#define BG_COLOR 0x0008

void centerText(String text, int y, uint16_t color) {
    tft.setFont(&FreeSansBold24pt7b);
    tft.setTextColor(color);

    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
    int x = (tft.width() - w) / 2;

    tft.setCursor(x, y);
    tft.print(text);
}

void setup() {
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);

    if (!bme.begin(0x76)) {
        tft.fillScreen(0x0000);
        centerText("BME280 ERROR", 150, 0xF800);
        while (1);
    }

    startTime = millis();
}

void loop() {
    float tempC = bme.readTemperature();
    float tempF = tempC * 9.0 / 5.0 + 32.0;
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0F;

    if (tempF > tempMax) tempMax = tempF;
    if (tempF < tempMin) tempMin = tempF;

    if (millis() - startTime >= 86400000UL) {
        tempMax = tempF;
        tempMin = tempF;
        startTime = millis();
    }

    tft.fillScreen(BG_COLOR);
    centerText("TEMPERATURE", 60, 0xFFFF);
    centerText(String(tempF, 1) + " F", 200, 0xF800);
    delay(3000);

    tft.fillScreen(BG_COLOR);
    centerText("HUMIDITY", 60, 0xFFFF);
    centerText(String(humidity, 0) + " %", 200, 0x07FF);
    delay(3000);

    tft.fillScreen(BG_COLOR);
    centerText("PRESSURE", 60, 0xFFFF);
    centerText(String(pressure, 0) + " hPa", 200, 0xFFE0);
    delay(3000);

    tft.fillScreen(BG_COLOR);
    centerText("24 HR HIGH / LOW", 50, 0xFFFF);
    centerText("HIGH: " + String(tempMax, 1) + " F", 160, 0x07E0);
    centerText("LOW: " + String(tempMin, 1) + " F", 240, 0x801F);
    delay(3000);
}