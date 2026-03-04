#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for Serial Monitor

  Serial.println("BME280 Test");

  bool status = bme.begin(0x76); // try 0x76 first
  if (!status) {
    Serial.println("Could not find BME280 sensor!");
    Serial.println("Try address 0x77 or check wiring.");
    while (1);
  }

  Serial.println("BME280 found!");
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.println("-----------------------");
  delay(2000);
}
