#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;
Adafruit_BME280 bme;

void setup() {
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);

    if (!bme.begin(0x76)) {
        tft.fillScreen(0x0000);
        tft.setTextColor(0xF800);
        tft.setTextSize(3);
        tft.setCursor(50, 150);
        tft.print("BME280 ERROR");
        while (1);
    }

    tft.fillScreen(0x0000);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(3);
    tft.setCursor(50, 150);
    tft.print("good");
    delay(2000);
}

void loop() {
    float tempC = bme.readTemperature();
    float tempF = tempC * 9.0 / 5.0 + 32.0;
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0F;

    tft.fillScreen(0x0000);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(2);

    tft.setCursor(20, 60);
    tft.print("Temp: ");
    tft.print(tempF, 1);
    tft.print(" F");

    tft.setCursor(20, 120);
    tft.print("Humidity: ");
    tft.print(humidity, 0);
    tft.print(" %");

    tft.setCursor(20, 180);
    tft.print("Pressure: ");
    tft.print(pressure, 0);
    tft.print(" hPa");

    delay(1000);
}