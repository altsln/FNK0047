/**********************************************************************
* Filename    : 032-03_Wifi_AP_mode_and_station_mode
* Description : Setting ESP32 to open an access point and also
* work as a staion mode. Ex: AP with phone and station
* mode with the router.
* Auther      : Alternatives Solutions.
* Modification: 2026/04/07
**********************************************************************/
//ESP32 for now does not support 5G connection

#include <WiFi.h>
#include <esp_wifi.h> 

// 1. Station Credentials (to connect to your router)
const char* sta_ssid = "YOUR_ROUTER_NAME";
const char* sta_password = "YOUR_ROUTER_PASSWORD";

// 2. Access Point Credentials (the network the ESP32 creates)
const char* ap_ssid = "ESP32-Wrover__KOK";
const char* ap_password = "pwd@123ESP"; // Must be at least 8 characters


void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("Configuring Access Point ...");
  // CRITICAL: Set the mode to Dual (AP and Station)
  WiFi.mode(WIFI_AP_STA);
  // --- Start Access Point ---
  setupAP();
  //--- 
  setupStationMode();

}

void loop() {
  // Both networks are now running simultaneously!
  // We can monitor how many devices are connected
  int num = WiFi.softAPgetStationNum();
  Serial.printf("Stations connected: %d\n", num);
  delay (5000);
}


void setupAP() {
  // --- Start Access Point ---
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("\n--- ACCESS POINT READY ---");
  Serial.print("Connect to: ");
  Serial.println(ap_ssid);
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP()); // Usually 192.168.4.1
}

void setupStationMode() {
  // --- Start Station Connection ---
  Serial.println("\n--- CONNECTING TO ROUTER ---");
  WiFi.begin(sta_ssid, sta_password);

  // Non-blocking wait (allows the AP to still function while connecting)
  int attempts = 0;
  while ((WiFi.status() != WL_CONNECTED) && (attempts < 10)) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n--- STATION CONNECTED ---");
    Serial.print("Router IP Address: ");
    Serial.println(WiFi.localIP()); 
  } else {
    Serial.println("\nRouter Connection Failed.");
  }
}
