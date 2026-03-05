#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

/* Colors */
#define BLACK  0x0000
#define RED    0xF800
#define BLUE   0x001F
#define WHITE  0xFFFF

MCUFRIEND_kbv tft;
Adafruit_BME280 bme;

bool state = false;

void setup() {
  Serial.begin(9600);
  delay(1000);

  // TFT init
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);

  // BME280 init
  if (!bme.begin(0x76)) {   // try 0x77 if needed
    tft.fillScreen(RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(20, 120);
    tft.print("BME280 FAIL");
    while (1);
  }

  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(20, 120);
  tft.print("SYSTEM OK");
  delay(1500);
}

void loop() {
  state = !state;

  float tempC = bme.readTemperature();
  float tempF = tempC * 9.0 / 5.0 + 32.0;

  if (state) {
    tft.fillScreen(BLUE);
  } else {
    tft.fillScreen(RED);
  }

  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(20, 100);
  tft.print("Temp:");
  tft.setCursor(20, 150);
  tft.print(tempF, 1);
  tft.print(" F");

  Serial.print("Temp: ");
  Serial.print(tempF, 1);
  Serial.println(" F");

  delay(1000);   // Blink speed
}
