/**********************************************************************
  Filename    : 032_Wifi_scanner
  Description : Scanning the networks.
  Auther      : Alternatives Solutions.
  Modification: 2026/04/07
**********************************************************************/

#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);    // Set to Station Mode
  WiFi.disconnect();      // Clear any old connections
  delay(100);
  Serial.println("WiFi Scan Start ...");
}

void loop() {
  int n = WiFi.scanNetworks();
  if (0 == n) {
    Serial.println("No networks found.");
  } else {
    Serial.printf("%d network(s) found:\n", n);
    for (int i = 0; i < n; i++) {
      Serial.printf("%d: %s, (%d dBm)\n",
        i+1,
        WiFi.SSID(i).c_str(),
        WiFi.RSSI(i));
    }
  }
  delay(5000);
}
