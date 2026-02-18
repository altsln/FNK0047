/**********************************************************************
* Filename    : 011-03_potentiometer_stripled
* Description : Using one potentiometer to control the color
* of Freenove Strip LED.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/17
**********************************************************************/
#include <Freenove_WS2812_Lib_for_ESP32.h>

#define STRIP_LED_S_PIN   15  //S input of StripLed is connected to IO2
#define STRIP_LED_COUNT   8   //number of LEDs on the StripLed
#define RMT_CHN           3   //RMT module channel
#define BRIGHTNESS        100 // brightness range value (0 ... 255)

#define INPUT_PIN         36  //define input analog Pin
#define DELAY_TIME        10

Freenove_ESP32_WS2812 strip = 
  Freenove_ESP32_WS2812(STRIP_LED_COUNT, STRIP_LED_S_PIN, RMT_CHN, TYPE_GRB);

// the setup function runs once when you press reset or power the board
void setup() {
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {

  int adc_val = analogRead(INPUT_PIN);
  int colorPos = map(adc_val, 0, 4096, 0, 255);
  //Serial.printf("adc val: %d - color pos: %d \n", adc_val, colorPos);
  for (int i = 0; i < STRIP_LED_COUNT; i++) {
    int rgb = strip.Wheel(colorPos + i * 255 / 8);
    strip.setLedColorData(i, rgb);
  }
  strip.show();
  delay(DELAY_TIME);
}

