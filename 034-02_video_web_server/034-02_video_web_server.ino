/**********************************************************************
* Filename    : 034-02_video_web_server
* Description : Building video webserver
* Step 1: Connect the ESP32 Wrover board to the local network,
* and prints a url through a serial port.
* Step 2: Users visit the site to view the video data from ESP32 camera.
* Auther      : Alternatives Solutions.
* Modification: 2026/04/13
**********************************************************************/
//ESP32 for now does not support 5G connection

#define BOARD_HAS_PSRAM
#include <WiFi.h>
#include "esp_camera.h"

// Select the camera model for Freenove (the WROVER model)
#define CAMERA_MODEL_WROVER_KIT 
#include "camera_pins.h"

//This code will not work unless you update the below const
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
//Please update the above const before building this code

camera_config_t config;

void startCameraServer();
void camera_init();

void setup() {
  Serial.begin(115200);
  // Verify PSRAM is actually working hardware-side
  if(psramInit()){
    Serial.println(" PSRAM detected! Memory is ready for video.");
  } else {
    Serial.println(" PSRAM NOT FOUND. This is causing the 500 error.");
  }
  Serial.setDebugOutput(true);
  Serial.println();

  camera_init();
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (ESP_OK != err) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  
  sensor_t * s = esp_camera_sensor_get();
  // drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_VGA);

  // Initialize WiFi (Using your Dual Mode logic if you like)
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

  Serial.println("");
  Serial.println("WiFi connected");
  // Start the Camera Server (This function is provided by the library)
  startCameraServer();

  Serial.print("\nCamera Ready! Go to: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  // The camera server runs in the background on a separate Core!
  delay(10000); 
}

void camera_init() {
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
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition

  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if (psramFound()) {
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  } 
}
