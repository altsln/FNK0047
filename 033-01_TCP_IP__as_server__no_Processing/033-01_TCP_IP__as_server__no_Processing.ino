/**********************************************************************
* Filename    : 033-01_TCP_IP__as_server__no_Processing
* Description : using Packet Sender (portable wiondows version)
* to demonstrate how it can connect as a client to ESP32(server).
* Auther      : Alternatives Solutions.
* Modification: 2026/04/10
**********************************************************************/
//ESP32 for now does not support 5G connection

#include <WiFi.h>

//This code will not work unless you update the below const
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
//using for the test Packet Sender V8.10.4
//Please update the above const before building this code

// Create a server on port 8081
WiFiServer server(8081);


void setup() {
  Serial.begin(115200);

  //connect first to the network
  WiFi.begin(ssid, password);
  while (WL_CONNECTED != WiFi.status()) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("ESP32 IP Address (Server IP): ");
  Serial.println(WiFi.localIP()); 
  //Use the server IP in Packet Sender 

  server.begin();
  Serial.println("Server started on port 8081.");
  Serial.println("Waiting for Connection...");
}

void loop() {
  // Check if a client (Packet Sender) has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n--- New Client Connected ---");

    while(client.connected()) {
      if (client.available()) {
        // Read the incoming message
        String line = client.readStringUntil('\r');
        Serial.printf("Received from PC: %s", line);

        // Optional: Send a reply back to the PC
        client.println("Thank you! Message received");
        client.flush(); // Wait for the transmission buffer to clear
        delay(10);      // Give the hardware a millisecond to breathe
        //With Packet Sender also check the "Persistent TCP" checkbox
        break; 
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

