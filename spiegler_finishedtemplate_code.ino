#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

/* ================= COLORS ================= */
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

/* ================= CONSTANTS ================= */
#define ALTITUDE 229.0                 // Altitude in Sparta, Greece
const unsigned long DAY_MS = 86400000UL; // 24 hours in milliseconds

/* ================= OBJECTS ================= */
MCUFRIEND_kbv tft;
Adafruit_BME280 bme;

/* ================= VARIABLES ================= */
float temperature;
float humidity;
float pressure;

float minTemp;
float maxTemp;

bool firstRead = true;
unsigned long minMaxStartTime = 0;

int screenState = 0;   // 0=Temp, 1=Humidity, 2=Pressure

/* ================= SETUP ================= */
void setup() {
  Serial.begin(9600);

  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);   // Landscape
  tft.fillScreen(BLACK);

  if (!bme.begin(0x76)) {
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(20, 100);
    tft.print("BME280 ERROR");
    while (1);
  }
}

/* ================= LOOP ================= */
void loop() {
  readSensors();

  switch (screenState) {
    case 0:
      showTemperature();
      break;
    case 1:
      showHumidity();
      break;
    case 2:
      showPressure();
      break;
  }

  screenState++;
  if (screenState > 2) screenState = 0;

  delay(3000);   // 3 seconds per screen
}

/* ================= SENSOR LOGIC ================= */
void readSensors() {
  temperature = Celsius2Fahrenheit(bme.readTemperature());
  humidity = bme.readHumidity();

  pressure = bme.readPressure();
  pressure = bme.seaLevelForAltitude(ALTITUDE, pressure);
  pressure /= 100.0F;

  // Initialize or reset min/max every 24 hours
  if (firstRead || (millis() - minMaxStartTime >= DAY_MS)) {
    minTemp = temperature;
    maxTemp = temperature;
    minMaxStartTime = millis();
    firstRead = false;
  } else {
    if (temperature < minTemp) minTemp = temperature;
    if (temperature > maxTemp) maxTemp = temperature;
  }
}

/* ================= DISPLAY SCREENS ================= */

void showTemperature() {
  tft.fillScreen(BLACK);

  tft.setTextColor(RED);
  tft.setTextSize(4);
  tft.setCursor(20, 40);
  tft.print("TEMP");

  tft.setTextSize(5);
  tft.setCursor(20, 100);
  tft.print(temperature, 1);
  tft.print(" F");

  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(20, 180);
  tft.print("MIN (24h): ");
  tft.print(minTemp, 1);
  tft.print(" F");

  tft.setCursor(20, 210);
  tft.print("MAX (24h): ");
  tft.print(maxTemp, 1);
  tft.print(" F");
}

void showHumidity() {
  tft.fillScreen(BLACK);

  tft.setTextColor(CYAN);
  tft.setTextSize(4);
  tft.setCursor(20, 40);
  tft.print("HUMIDITY");

  tft.setTextSize(5);
  tft.setCursor(20, 110);
  tft.print(humidity, 0);
  tft.print(" %");
}

void showPressure() {
  tft.fillScreen(BLACK);

  tft.setTextColor(YELLOW);
  tft.setTextSize(4);
  tft.setCursor(20, 40);
  tft.print("PRESSURE");

  tft.setTextSize(4);
  tft.setCursor(20, 120);
  tft.print(pressure, 2);
  tft.print(" hPa");
}

/* ================= UTILITIES ================= */

float Celsius2Fahrenheit(float celsius) {
  return celsius * 9.0 / 5.0 + 32.0;
}
