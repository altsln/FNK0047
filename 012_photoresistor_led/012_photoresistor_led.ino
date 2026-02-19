/**********************************************************************
* Filename    : 012_photoresistor_led
* Description : Using a photoresistor to control the brigthness
* of a LED via pwm.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/17
**********************************************************************/

#define INPUT_PIN         15       //define input analog Pin
#define PIN_LED           23  
#define PWM_CHN           0       //PWM module channel
#define PWM_FRQ           1000    //
#define PWM_BIT           12      //
#define LIGHT_MIN         372     // 
#define LIGHT_MAX         2048    // 

#define DELAY_TIME        100

// the setup function runs once when you press reset or power the board
void setup() {
  ledcAttachChannel(PIN_LED, PWM_FRQ, PWM_BIT, PWM_CHN);

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  int adc_val = analogRead(INPUT_PIN);
  int c_val = constrain(adc_val, LIGHT_MIN, LIGHT_MAX);
  int pwm_val = map(c_val, LIGHT_MIN, LIGHT_MAX, 0, 4095);
  Serial.printf("adc val: %d - pwm val: %d \n", adc_val, pwm_val);
  ledcWrite(PIN_LED, pwm_val);
  delay(DELAY_TIME);
}

