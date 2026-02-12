/**********************************************************************
* Filename    : 006-01_LED_Pixel_rainbow_light
* Description : Make the strip light up in rainbow colors.   
* Auther      : Alternatives Solutions
* Modification: 2026/02/11
**********************************************************************/
//find the libraraie file here:
// repo/FNK0047/lib/Freenove_WS2812_Lib_for_ESP32-2.0.0.zip
#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT    8   // The number of led
#define LEDS_PIN      22  // define the pin connected to the Freenove 8 led strip
#define CHANNEL       3   // RMT module channel

#define DELAY_TIME   10

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(
  LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB
);

// the setup function runs once when you press reset or power the board
void setup() {
  strip.begin();
}

// the loop function runs over and over again forever
void loop() {
  for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, 
        strip.Wheel((i * 256 / LEDS_COUNT + j) & 255)); //set color data.
    }
    strip.show();
    delay(DELAY_TIME);
  }
}

