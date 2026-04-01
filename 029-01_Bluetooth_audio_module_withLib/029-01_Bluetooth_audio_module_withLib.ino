/**********************************************************************
* Filename    : 029-01_Bluetooth_audio_module_withLib
* Description : Streaming music over BT from the phone to the
* ESP32 using an audio module and external libraries.
* Auther      : Alternatives Solutions
* Modification: 2026/04/01
**********************************************************************/

#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

void setup() {
  // 1. Configure the I2S to use the Internal DAC
  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = 26;
  cfg.pin_ws = 25;
  cfg.pin_data = 22;
  i2s.begin(cfg);

  // 2. Start the A2DP Sink
  a2dp_sink.start("Karl_Speaker");
}

void loop() {
}

