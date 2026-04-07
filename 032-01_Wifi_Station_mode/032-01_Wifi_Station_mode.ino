/**********************************************************************
  Filename    : 032-01_Wifi_Station_mode
  Description : Scanning the networks.
  Auther      : Alternatives Solutions.
  Modification: 2026/04/07
**********************************************************************/
//ESP32 for now does not support 5G connection

#include <WiFi.h>

const char* ssid = "*****"; //replace with your ssid
const char* password = "******";  //replace with your pwd

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.printf("Connecting to %s ", ssid);

  //Start the connection process
  WiFi.begin(ssid, password);
  //Wait until we are connected (Wait for 10 seconds)
  int timeout_counter = 0;
  while ((WL_CONNECTED != WiFi.status()) && (timeout_counter < 40)) {
    delay(500);
    Serial.print(".");
    timeout_counter++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("(ESP32 Wrover) IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFAILED.");
    Serial.printf("Status Code: %d\n", WiFi.status());
    // Status 4 = WRONG_PASSWORD, Status 1 = NO_SSID_AVAIL
  }

}

void loop() {
  ;
}


/*
void setupDiganostic() {
    Serial.begin(115200);
    delay(2000);

    // 1. Force Station Mode and clear previous settings
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true); 
    delay(1000);

    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    // 2. Wait up to 20 seconds
    int timeout_counter = 0;
    while (WiFi.status() != WL_CONNECTED && timeout_counter < 40) {
        delay(500);
        Serial.print(".");
        timeout_counter++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nSUCCESS!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFAILED.");
        Serial.printf("Status Code: %d\n", WiFi.status());
        // Status 4 = WRONG_PASSWORD, Status 1 = NO_SSID_AVAIL
    }
}

void loopDiganostic() {}
*/
