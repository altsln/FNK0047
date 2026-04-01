/**********************************************************************
* Filename    : 028_Bluetooth_media_DAC
* Description : NOT WORKING TO REVISIT.
* Auther      : Alternatives Solutions
* Modification: 2026/03/31
**********************************************************************/

#include "BluetoothSerial.h"
#include "driver/i2s.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "esp_bt.h"
#include "bt_app_core.h"
#include "bt_app_av.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"
#include "esp_avrc_api.h"

#define CONFIG_CLASSIC_BT_ENABLED
#define CONFIG_BT_ENABLED 
#define CONFIG_BLUEDROID_ENABLED

BluetoothSerial SerialBT;

static void bt_av_hdl_stack_evt(uint16_t event, void *p_param){
  if(event==0) {
    /* initialize A2DP sink */
    esp_a2d_register_callback(&bt_app_a2d_cb);
    esp_a2d_sink_register_data_callback(bt_app_a2d_data_cb);
    esp_a2d_sink_init();
    /* initialize AVRCP controller */
    esp_avrc_ct_init();
    esp_avrc_ct_register_callback(bt_app_rc_ct_cb);
    /* set discoverable and connectable mode, wait to be connected */
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
  }
}

void setup() {
  Serial.begin(115200);
  //SerialBT.begin("ESP32_DAC");
  Serial.println("Init seccess!");
  setupBT();
  Serial.println("System Ready! Waiting for a phone to connect...");
  //Serial.println("Please use your bluetooth device to connect the ESP32");

}


void loop() {
  // We can put the ESP32 to sleep or do other tasks here.
  // The Callbacks handle the Bluetooth communication!
//  delay(1000);
}


void setupBT() {
  //log info
  Serial.println("Setting up BLE in progress...");

  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }

  //Define an I2S interface variable and initialize it.
  i2s_config_t i2s_config;
  i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN);
  i2s_config.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
  i2s_config.sample_rate = 44100;
  i2s_config.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;  
  i2s_config.communication_format = I2S_COMM_FORMAT_STAND_I2S;
  i2s_config.intr_alloc_flags = 0;
  i2s_config.dma_buf_count = 8;
  i2s_config.dma_buf_len = 64;
  i2s_config.tx_desc_auto_clear = true;
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN);
  i2s_set_pin(I2S_NUM_0, NULL);

  //Initialize the Bluetooth hardware device, 
  //establish a Bluetooth thread task, and print out messages to prompt the user to take the next step.

  // 1. Initialize the Bluetooth Controller and Bluedroid
  esp_bluedroid_init();
  esp_bluedroid_enable();

  // 2.1. SET THE NAME HERE
  esp_bt_dev_set_device_name("ESP32_DAC"); // <--- Change your name here!
  //2.2 Set the Class of Device (This tells the phone "I am a Speaker")
  // 0x200414 = Service: Rendering, Major: Audio, Minor: Loudspeaker
  esp_bt_cod_t cod;
  cod.major = 0b00100;      // Audio
  cod.minor = 0b000101;    // Loudspeaker
  cod.service = 0b00101;   // Rendering
  esp_bt_gap_set_cod(cod, ESP_BT_SET_COD_ALL);

  // 2.3. Make sure it is actually Discoverable
  esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

  // 3. Start the Bluetooth tasks
  bt_app_task_start_up();
  bt_app_work_dispatch(bt_av_hdl_stack_evt, 0, NULL, 0, NULL);
}
