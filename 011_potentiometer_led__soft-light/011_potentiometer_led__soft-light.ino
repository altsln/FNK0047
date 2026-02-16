/**********************************************************************
* Filename    : 011_potentiometer_led_soft-light
* Description : Using potentiometer to control LED brightness.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/16
**********************************************************************/
#define PIN_ANALOG_IN       36
#define PIN_LED             25
#define PWM_CHN             3
#define PWM_FRQ             1000

#define DELAY_TIME          10

// the setup function runs once when you press reset or power the board
void setup() {
  ledcAttachChannel(PIN_LED, PWM_FRQ, 12, PWM_CHN);
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  int adc_val = analogRead(PIN_ANALOG_IN);
  ledcWrite(PIN_LED, adc_val);
  Serial.printf("Touch value: %d \n", adc_val);
  delay(DELAY_TIME);
}
