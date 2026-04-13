/**********************************************************************
* Filename    : 034_web_server
* Description : Building standard "Hello world" webserver
* Step 1: Connect the ESP32 Wrover board to the local network
* Step 2: Turn the ESP32 to server and wait for a client.
* Step 3: Connect with a client and play with build-in led 
* Auther      : Alternatives Solutions.
* Modification: 2026/04/12
**********************************************************************/
//ESP32 for now does not support 5G connection

#include <WiFi.h>

//This code will not work unless you update the below const
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
//Please update the above const before building this code

const int LED_BUILTIN = 2;

// Create a server on port 80, Web server always use that port
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED OFF (Active LOW)

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
  Serial.println("Server started on port 80.");
  Serial.println("Waiting for Connection...");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n--- New Web Client Connected ---");
    String currentLine = "";
    while(client.connected()) {
      if (client.available()) {
        char c = client.read();
        if ('\n' == c) {
          if (0 == currentLine.length()) {
            buildPage(client);
            break;
          } else {
            currentLine = "";
          }
        } else if ('\r' != c) {
          currentLine += c;
        }

        // Check the request for our commands
        runCommand(currentLine);
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

void buildHTTPHeaders(WiFiClient& client) {
  // HTTP headers always start with a response code
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();// Extra newline is mandatory
}

void buildPageContent(WiFiClient& client) {
  client.println("<h1>Karl's ESP32-S3 Server</h1>");
  client.println("<p>Click <a href=\"/H\">here</a> to turn LED ON.</p>");
  client.println("<p>Click <a href=\"/L\">here</a> to turn LED OFF.</p>");
  client.println(); // End the response
}

void buildPage (WiFiClient& client) {
  // build HTTP headers
  buildHTTPHeaders(client);
  // build the actual webpage content
  buildPageContent(client);
}

void runCommand(String cmd) {
//  Serial.print("command:");
//  Serial.println(cmd);
  if (cmd.endsWith("GET /H")) {
    digitalWrite(LED_BUILTIN, LOW); //active LOW
    Serial.println("LED ON");
  }
  if (cmd.endsWith("GET /L")) {
    digitalWrite(LED_BUILTIN, HIGH);  //active LOW
    Serial.println("LED OFF");
  }
}

