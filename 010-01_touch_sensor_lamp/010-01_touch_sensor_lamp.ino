/**********************************************************************
* Filename    : 010-01_touch_sensor_lamp
* Description : Read touch sensor value to control a LED.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/16
**********************************************************************/
#define PIN_LED             25
#define PRESS_VAL__T8       700   // a threshold to judge touch for T8
#define RELEASE_VAL__T8     1000   // a threshold to judge release for T8
//#define PRESS_VAL__T0     300   // a threshold to judge touch for T0
//#define RELEASE_VAL__T0   500   // a threshold to judge release for T0
#define DELAY_TIME          1000

bool isProcessed = false;
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {

  if (touchRead(T8) < PRESS_VAL__T8) {
    if (!isProcessed) {
      isProcessed = true;
      Serial.println("Touch detected! ");
      reverseGPIO(PIN_LED);
    }
  } else if (touchRead(T8) > RELEASE_VAL__T8) {
    if (isProcessed) {
      isProcessed = false;
      Serial.println("Touch released! ");
    }
  }
  //Serial.printf("Touch value: %d \n", touchRead(T8));
  //delay(DELAY_TIME);

}

void reverseGPIO(int pin) {
  static bool state = false;
  state = !state;
  digitalWrite(pin, state);
}