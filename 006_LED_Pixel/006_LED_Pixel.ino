/**********************************************************************
* Filename    : 006_LED_Pixel
* Description : Basic usage of LEDPixel,
* Make the strip light up in different colors gradually.   
* Auther      : Alternatives Solutions
* Modification: 2026/02/11
**********************************************************************/
//find the libraraie file here:
// repo/FNK0047/lib/Freenove_WS2812_Lib_for_ESP32-2.0.0.zip
#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT    8   // The number of led
#define LEDS_PIN      22  // define the pin connected to the Freenove 8 led strip
#define CHANNEL       3   // RMT module channel

#define DELAY_TIME   100

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(
  LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB
);

int m_color[5][3] = {
  {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0}
};

// the setup function runs once when you press reset or power the board
void setup() {
  strip.begin();
  strip.setBrightness(10);
}

// the loop function runs over and over again forever
void loop() {
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, 
        m_color[j][0], m_color[j][1], m_color[j][2]); //set color data.
      strip.show();
      delay(DELAY_TIME);
    }
    delay(5 * DELAY_TIME);
  }
}

