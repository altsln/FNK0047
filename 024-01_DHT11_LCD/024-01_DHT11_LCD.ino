/**********************************************************************
* Filename    : 024-01_DHT11_LCD
* Description : Using DHT11 component to read the value of
* Humidity and Temperature and display them on LCD screen.
* Auther      : Alternatives Solutions
* Modification: 2026/03/24
**********************************************************************/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHTesp.h"

// --- Configuration ---
const int SDA_PIN = 15;
const int SCL_PIN = 13;
const int DHT_PIN = 23;

const int DELAY_TIME = 2000;
//
DHTesp dht;
LiquidCrystal_I2C* lcdPtr = nullptr;


void setup() {
  Serial.begin(115200);
  
  setupLCD();
  setupDHT();

  Serial.println("System Ready.");
}

void loop() {
  // DHT11 needs at least 2 seconds between reads
  delay(DELAY_TIME);

  //read data
  captureData();
}

// --- Logic Functions ---

void captureData() {
  if (dht.getStatus() == DHTesp::ERROR_NONE) {
    handleSuccess();
  } else {
    handleFailure();
  }
}

void handleSuccess() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  updateLCD(humidity, temperature);
  // Keep your Serial log for debugging
  //Serial.printf("Temp: %.1fC | Hum: %.1f%%\n", temperature, humidity);
  logData(dht.getStatusString(), humidity, temperature);
}

void handleFailure() {
  if (nullptr == lcdPtr) return;
  
  lcdPtr->setCursor(0, 1);
  lcdPtr->print("Sensor Error!   ");
  logData(dht.getStatusString());
}

void updateLCD(float hum, float temp) {
  if (lcdPtr == nullptr) return;

  // Line 1: Temperature
  lcdPtr->setCursor(0, 0);
  lcdPtr->print("Temp: ");
  lcdPtr->print(temp, 1); // 1 decimal place
  lcdPtr->write(223);     // Character code for degree symbol
  lcdPtr->print("C      ");

  // Line 2: Humidity
  lcdPtr->setCursor(0, 1);
  lcdPtr->print("Humid: ");
  lcdPtr->print(hum, 1);
  lcdPtr->print("%       ");
}

void logData(const char* statusStr) {
  Serial.print("Status: ");
  Serial.println(statusStr); // Very helpful for debugging!
}

void logData(const char* statusStr, const float hum, const float temp) {
  Serial.print("Status: ");
  Serial.print(statusStr);
  Serial.print(" | Humidity: ");
  Serial.print(hum);
  Serial.print("% | Temperature: ");
  Serial.print(temp);
  Serial.println("°C");
}

// --- Hardware Helpers ---
void setupLCD() {
  Wire.begin(SDA_PIN, SCL_PIN);
  lcdPtr = new LiquidCrystal_I2C(0x27, 16, 2);
  lcdPtr->init();
  lcdPtr->backlight();
  lcdPtr->clear();
  lcdPtr->setCursor(0, 0);
  lcdPtr->print("System Booting...");
  delay(1500);
  lcdPtr->clear();
}

void setupDHT() {
  dht.setup(DHT_PIN, DHTesp::DHT11);
  Serial.print("System Ready and waiting for DHT message on PIN: ");
  Serial.println(DHT_PIN);
}
