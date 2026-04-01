/**********************************************************************
* Filename    : 028_Bluetooth_media_DAC
* Description : Streaming music over BT from the phone to the
* ESP32 using external libraries.
* Auther      : Alternatives Solutions
* Modification: 2026/03/31
**********************************************************************/

#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

void setup() {
  // 1. Configure the I2S to use the Internal DAC
  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = 14;
  cfg.pin_ws = 15;
  cfg.pin_data = 25;
  i2s.begin(cfg);

  // 2. Start the A2DP Sink
  a2dp_sink.start("Karl_Speaker");
}

void loop() {
}

