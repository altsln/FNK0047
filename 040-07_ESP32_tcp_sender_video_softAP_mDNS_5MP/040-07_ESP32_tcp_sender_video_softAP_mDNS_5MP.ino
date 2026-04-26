/**********************************************************************
* Filename    : 040-07_ESP32_tcp_sender_video_softAP_mDNS_5MP
* Description : Building arduino Task project with mDNS broadcast
* In this project we are going to run 2 loops in parallel,
* Loop 1 (Standard): TCP Client that connects to a phone and
* sends video.
* Task 2 (The New Worker): Blinks the built-in LED every 5 seconds.
* Direct connection between ESP and the phone.
* Code updated to use a 5MP camera sensor
* Auther      : Alternatives Solutions.
* Modification: 2026/04/25
**********************************************************************/
//ESP32 for now does not support 5G connection

//PLease check the android phone code in img/040-06 folder
#include <ESPmDNS.h>
#include <WiFi.h>
#include "esp_camera.h"

#include "sensor.h"
//#include "ov5640.h" // This provides access to the driver-specific functions

// Select the camera model for Freenove (the WROVER model)
#define CAMERA_MODEL_WROVER_KIT 
#include "camera_pins.h" 

const char* ssid_ap = "ESP32-KDO-Cam";
const char* password_ap = "pwd123pwd456";
//"ESP32-KDO-Cam", "pwd123pwd456"

// Instead of a client connecting to an IP, we start a Server on port 8080
const uint16_t serverPort = 8080;
WiFiServer server(serverPort); 

const int LED_BUILT_IN = 2;

//extern TaskHandle_t loopTaskHandle;
// 1. We create a "Handle" (an ID card for our task)
TaskHandle_t MyTaskHandle;

bool initCamera();
void setup_mDNS();

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILT_IN, OUTPUT); // Built-in LED on most ESP32s
  //digitalWrite(LED_BUILTIN, HIGH); // turn the LED OFF (Active LOW)

  if (initCamera()) {
    Serial.println("Camera configuration complete!");
  }

  //WiFi.begin(ssid, password);
  //while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  //Serial.println("\nWiFi Connected!");
  WiFi.softAP(ssid_ap, password_ap);
  Serial.print("ESP32 AP IP Address: ");
//  Serial.println(WiFi.localIP()); // YOU WILL NEED THIS FOR THE ANDROID APP
  Serial.println(WiFi.softAPIP()); // YOU WILL NEED THIS FOR THE ANDROID APP

  setup_mDNS();

  server.begin(); // Start listening for the phone

  // Task 1: The Blinker (Core 0)
  xTaskCreatePinnedToCore(
    BlinkTask,    // The name of the function to run
    "Blink",      // A name for us to read
    1000,         // Stack size (Memory for this worker)
    NULL,         // Parameters to pass (none)
    1,            // Priority (1 is low, higher is more important)
    NULL,         // The ID card we created
    0             // THE CORE: Run this on Core 0 (Loop runs on Core 1)
  );
  
  // Task 2: The Counter/Sender (Core 1)
  xTaskCreatePinnedToCore(TcpTask, "TCP", 4096, NULL, 1, NULL, 1);
}


//task loop uses core 1.
void loop() { vTaskDelete(NULL); } // We use tasks, so loop is empty

void setup_mDNS() {
  if (!MDNS.begin("esp32-KDO")) {
    Serial.println("Error setting up MDNS responder!");
  } else {
    Serial.println("mDNS responder started at esp32-KDO.local");
    // Advertise the TCP service on port 8080
    MDNS.addService("arduino", "tcp", 8080);
  }
}

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
//old  config.xclk_freq_hz = 20000000;
  
  // OV5640 is much more stable at 12MHz or 16MHz than 20MHz.
  // This value works perfectly for both sensors.
  config.xclk_freq_hz = 12000000;

  config.pixel_format = PIXFORMAT_JPEG; // We want JPEGs
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition

  // Set resolution (QVGA is good for testing TCP)

  //psramFound();  //freenove uses this here.
  /* old
  config.frame_size = FRAMESIZE_QVGA;
  //freenove seeting here is   config.jpeg_quality = 10;
  config.jpeg_quality = 12;
  */
  // Use SVGA (800x600) for a "High Def" salon look. 
  // Both sensors support this easily.
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 12;

//old  config.fb_count = 1;

  // IMPORTANT: Increase to 2 buffers. 
  // This prevents the Android "skia" warnings because the ESP32 can
  // capture the next frame while the current one is still being sent.
  config.fb_count = 2;


  // Init camera
  esp_err_t err = esp_camera_init(&config);
  if (ESP_OK != err) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return false;
  }

  // SENSOR SPECIFIC TUNING
  sensor_t* s = esp_camera_sensor_get();
  if (s->id.PID == OV5640_PID) {
    Serial.println("OV5640 detected! Enabling Salon Pro features...");

    // Most recent library versions use these commands:
    s->set_vflip(s, 1);    // Match your salon mounting
    s->set_hmirror(s, 1);

    // TRIGGER AUTOFOCUS
    // On many ESP32-S3 and high-end boards, this is the standard call:
    esp_err_t af_err = s->set_reg(s, 0xFF, 0xFF, 0x01); // Standard trigger for many AF drivers
    
    // If your board supports the NEW official AF API (v2.1.6+):
    // s->set_res_raw(s, 0, 0, 0, 1); // This is sometimes used for AF trigger
    
    Serial.println("Autofocus triggered.");

/*
  // Use the driver-specific call
    ov5640_focus_set(s, 0); // 0 = Continuous Focus (often represented as 'auto' in drivers)

    // Anti-flicker for salon lights (60Hz)  
    s->set_aec_value(s, 1); 

    // High-Detail Mode
    s->set_sharpness(s, 2); 

    s->set_brightness(s, 1);
    // Auto-Focus Command (Continuous mode)

//    s->set_af_mode(s, 1); // 1 = Continuous
//    s->set_af_trigger(s, 1);*/
  } else if (s->id.PID == OV2640_PID) {
    Serial.println("OV2640 detected. Using standard settings.");
  }

  return true;
}


void BlinkTask(void * pvParameters) {
  for(;;) {
    digitalWrite(LED_BUILT_IN, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(LED_BUILT_IN, HIGH);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}


////////////////////////////////////////////////////////////////////

void TcpTask(void * pvParameters) {
  for(;;) {
    WiFiClient client = server.available(); // Wait for phone to connect
    if (client) {
      Serial.println("Phone Connected!");
      while (client.connected()) {
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
//        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000ms = 1 second
      }
      client.stop();
      Serial.println("Phone Disconnected");
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to prevent watchdog issues
  }
}


