/**********************************************************************
* Filename    : 024_DHT11
* Description : Using DHT11 component to read the value of
* Humidity and Temperature.
* Auther      : Alternatives Solutions
* Modification: 2026/03/23
**********************************************************************/

#include "DHTesp.h"
// --- Configuration ---
const int DHT_PIN = 23;
const int DELAY_TIME = 2000;
//
DHTesp dht;

void setup() {
  dht.setup(DHT_PIN, DHTesp::DHT11);
  Serial.begin(115200);
  Serial.print("System Ready and waiting for DHT message on PIN: ");
  Serial.println(DHT_PIN);
}

void loop() {
  delay(DELAY_TIME);

  //read data
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  logData(dht.getStatusString(), humidity, temperature);
}

void logData(const char* statusStr, const float hum, const float temp) {
  Serial.print("Status: ");
  Serial.print(statusStr); // Very helpful for debugging!
  Serial.print(" | Humidity: ");
  Serial.print(hum);
  Serial.print("% | Temperature: ");
  Serial.print(temp);
  Serial.println("°C");
}
