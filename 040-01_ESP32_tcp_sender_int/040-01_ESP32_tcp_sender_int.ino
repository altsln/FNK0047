/**********************************************************************
* Filename    : 040-01_ESP32_tcp_sender_int
* Description : Building simple arduino Task project
* In this project we are going to run 2 loops in parallel,
* Loop 1 (Standard): TCP Client that connects to aphone and
* sends the doubling numbers.
* Task 2 (The New Worker): Blinks the built-in LED every 0.5 seconds.
* Auther      : Alternatives Solutions.
* Modification: 2026/04/20
**********************************************************************/
//ESP32 for now does not support 5G connection

//PLease check the C++ VS code in img/035-01 folder
#include <WiFi.h>

//update the ssid and password with your own for this code to run
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";


// Instead of a client connecting to an IP, we start a Server on port 8080
const uint16_t serverPort = 8080;
WiFiServer server(serverPort); 

const int LED_BUILT_IN = 2;

//extern TaskHandle_t loopTaskHandle;
// 1. We create a "Handle" (an ID card for our task)
TaskHandle_t MyTaskHandle;


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILT_IN, OUTPUT); // Built-in LED on most ESP32s
  //digitalWrite(LED_BUILTIN, HIGH); // turn the LED OFF (Active LOW)

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nWiFi Connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP()); // YOU WILL NEED THIS FOR THE ANDROID APP

  server.begin(); // Start listening for the phone

  // Task 1: The Blinker (Core 0)
  xTaskCreatePinnedToCore(BlinkTask, "Blink", 1000, NULL, 1, NULL, 0);
  
  // Task 2: The Counter/Sender (Core 1)
  xTaskCreatePinnedToCore(TcpTask, "TCP", 4096, NULL, 1, NULL, 1);

  /*
  xTaskCreatePinnedToCore(
    MyWorkerFunction,   // The name of the function to run
    "BlinkTask",        // A name for us to read
    1000,               // Stack size (Memory for this worker)
    NULL,               // Parameters to pass (none)
    1,                  // Priority (1 is low, higher is more important)
    &MyTaskHandle,      // The ID card we created
    0                   // THE CORE: Run this on Core 0 (Loop runs on Core 1)
  );
  */
}


//task loop uses core 1.
void loop() { vTaskDelete(NULL); } // We use tasks, so loop is empty


void BlinkTask(void * pvParameters) {
  for(;;) {
    digitalWrite(LED_BUILT_IN, !digitalRead(LED_BUILT_IN));
    vTaskDelay(500 / portTICK_PERIOD_MS); 
  }
}

/*
void TcpTask(void * pvParameters) {
  for(;;) {
    WiFiClient client;
    if (client.connect(serverIP, serverPort)) {
      int count = 1;
      while(count <= 128) { // Doubling logic
        client.print("Number: ");
        client.println(count);
        Serial.printf("Sent: %d\n", count);
        count *= 2;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      client.stop();
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Wait 5s before restart
  }
}
*/
////////////////////////////////////////////////////////////////////

void TcpTask(void * pvParameters) {
  for(;;) {
    WiFiClient client = server.available(); // Wait for phone to connect
    if (client) {
      Serial.println("Phone Connected!");
      int count = 1;
      while (client.connected()) {
        // CASE 1: Sending as Raw Bytes (Little Endian) for your Java Receiver
        client.write((uint8_t*)&count, 4); 
        Serial.printf("Sent Counter: %d\n", count);
        if(count >= 128) count = 1; else count *= 2; // Reset loop for testing
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      client.stop();
      Serial.println("Phone Disconnected");
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to prevent watchdog issues
  }
}
