/**********************************************************************
* Filename    : 035-03_ESP32__send_captured_image_tcp
* Description : Building arduino Task project
* In this project we are going to run 2 loops in parallel,
* Loop 1 (Standard): TCP Client that connects to your PC and
* sends an image.
* Task 2 (The New Worker): Blinks the built-in LED every 0.5 seconds.
* Auther      : Alternatives Solutions.
* Modification: 2026/04/16
**********************************************************************/
//ESP32 for now does not support 5G connection

//PLease check the C++ VS code in img/035-03 folder
#include <WiFi.h>
#include "esp_camera.h"


// Select the camera model for Freenove (the WROVER model)
#define CAMERA_MODEL_WROVER_KIT 
#include "camera_pins.h" 

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverIP = "192.168.10.XX"; // YOUR PC'S IP ADDRESS

const uint16_t serverPort = 8080;

const int LED_BUILT_IN = 2;

//extern TaskHandle_t loopTaskHandle;
// 1. We create a "Handle" (an ID card for our task)
TaskHandle_t MyTaskHandle;

bool initCamera();

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILT_IN, OUTPUT); // Built-in LED on most ESP32s
  //digitalWrite(LED_BUILTIN, HIGH); // turn the LED OFF (Active LOW)

  if (initCamera()) {
    Serial.println("Camera configuration complete!");
  }

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

bool initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  //freenove seeting here is   config.xclk_freq_hz = 10000000;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; // We want JPEGs
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition

  // Set resolution (QVGA is good for testing TCP)

  //psramFound();  //freenove uses this here.
  config.frame_size = FRAMESIZE_QVGA;
  //freenove seeting here is   config.jpeg_quality = 10;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (ESP_OK != err) {
    Serial.printf("Camera init failed with error 0x%x", err);
  }

  return (err == ESP_OK);
}


void BlinkTask(void * pvParameters) {
  for(;;) {
    digitalWrite(LED_BUILT_IN, !digitalRead(2));
    vTaskDelay(500 / portTICK_PERIOD_MS); 
  }
}


void TcpTask(void * pvParameters) {
  for(;;) {
      WiFiClient client;
      if (client.connect(serverIP, serverPort)) {
        // 1. Capture a frame
        camera_fb_t* fb = esp_camera_fb_get();
        if (!fb) {
          Serial.println("Camera capture failed");
          continue;
        }

        // 2. Send the SIZE of the image first (The Header)
        uint32_t size = fb->len;
        client.write((const uint8_t*)&size, sizeof(size));

        // 3. Send the actual IMAGE data (The Payload)
        client.write(fb->buf, fb->len);

        Serial.printf("Sent Image: %d bytes\n", fb->len);

        // 4. Return the frame buffer to the system
        esp_camera_fb_return(fb);
        client.stop();
      }
      //vTaskDelay(100 / portTICK_PERIOD_MS); // Stream at ~10 FPS
      vTaskDelay(10000 / portTICK_PERIOD_MS); // 10000ms = 10 seconds
  }
}

