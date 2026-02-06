/**********************************************************************
* Filename    : 004_breathing_light_pwm
* Description : Make led light fade in and out
* using PWM (Pulse Width Modulation)
* Auther      : Alternative Solutions
* Modification: 2026/02/06
**********************************************************************/

#define LED_BUILTIN  2    //define the led pin
#define PWM_CHN      0    //define PWM Channel
#define PWM_FRQ      1000 //define PWM Frequency
#define PWM_BIT      8    //define PWM Precision
#define MAX_VALUE    256  //based on 8bits the max value is 256
#define DELAY_TIME   20

// the setup function runs once when you press reset or power the board
void setup() {
  // Attach the Builtin led to PWM Channel.
  ledcAttachChannel(LED_BUILTIN, PWM_FRQ, PWM_BIT, PWM_CHN);
}

// the loop function runs over and over again forever
void loop() {
  //make light fade in
  for (int i = MAX_VALUE - 1; i >= 0; i--) {
    ledcWrite(LED_BUILTIN, i);
    delay(DELAY_TIME);
  }
  delay(12 * DELAY_TIME);
  //make light fade out
  for (int i = 0; i < MAX_VALUE; i++) {
    ledcWrite(LED_BUILTIN, i);
    delay(DELAY_TIME);
  }
  delay(12 * DELAY_TIME);
  delay(12 * DELAY_TIME);
  delay(12 * DELAY_TIME);
}
