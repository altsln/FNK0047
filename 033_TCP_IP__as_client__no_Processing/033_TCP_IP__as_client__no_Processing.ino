/**********************************************************************
* Filename    : 033_TCP_IP__as_client__no_Processing
* Description : using Packet Sender (portable wiondows version)
* to demonstrate that ESP32 can connect to a server as a client.
* Auther      : Alternatives Solutions.
* Modification: 2026/04/08
**********************************************************************/
//ESP32 for now does not support 5G connection

#include <WiFi.h>

//This code will not work unless you update the below const and 
// server port number 
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* serverIP = "192.168.10.XX"; // Your Computer's Local IP
uint16_t serverPort = 8080; // 64122; //for current version of packet Sender
//using for the test Packet Sender V8.10.4
//Please update the above const and server port number before
// building this code

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); }
    Serial.println("Connected to WiFi");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    WiFiClient client;
    if (client.connect(serverIP, serverPort)) {
        Serial.println("Connected to TCP Server!");
        client.println("Hello from ESP32-S3 Karl!");
        client.stop();
    }
    delay(10000);
}