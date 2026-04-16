/**********************************************************************
* Filename    : 035-01_ESP32_tcp_sender
* Description : Building simple arduino Task project
* In this project we are going to run 2 loops in parallel,
* Loop 1 (Standard): TCP Client that connects to your PC and
* sends string messages.
* Task 2 (The New Worker): Blinks the built-in LED every 0.5 seconds.
* Auther      : Alternatives Solutions.
* Modification: 2026/04/15
**********************************************************************/
//ESP32 for now does not support 5G connection

//PLease check the C++ VS code in img/035-02 folder
#include <WiFi.h>


const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverIP = "192.168.10.XX"; // YOUR PC'S IP ADDRESS

const uint16_t serverPort = 8080;

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
    digitalWrite(LED_BUILT_IN, !digitalRead(2));
    vTaskDelay(500 / portTICK_PERIOD_MS); 
  }
}


void TcpTask(void * pvParameters) {
  int count = 1;
  for(;;) {
    WiFiClient client;
    if (client.connect(serverIP, serverPort)) {
      // Create a status string
      String status = "ALERT: Motion detected! Count is: " + String(count) + "\n";
      
      // Send the string
      client.print(status);
      Serial.print("Sent string: " + status);
      
      count *= 2;
      if(count > 2048) count = 1; // Reset so it doesn't overflow
      
      client.stop(); // Close connection after sending
    }
    vTaskDelay(3000 / portTICK_PERIOD_MS); // Wait 3 seconds
  }
}
