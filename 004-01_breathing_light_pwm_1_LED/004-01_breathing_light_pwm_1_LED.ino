/**********************************************************************
* Filename    : 004-01_breathing_light_pwm_1_LED
* Description : Make 1 LED light fade in and out
* using PWM (Pulse Width Modulation) a different way
* Auther      : Alternative Solutions
* Modification: 2026/02/06
**********************************************************************/

#define LED_BUILTIN  2    //define the led pin 1
#define PWM_CHN_1    7    //define PWM Channel 1
#define PWM_FRQ      1000 //define PWM Frequency
#define PWM_BIT      9    //define PWM Precision
#define DELAY_TIME   1000

//define LED pin Array
const byte ledPinArray[] = {LED_BUILTIN};
//define the PWM channels
const byte chnArray[] = {PWM_CHN_1};
//define the PWM duties
const int dutyArray[] = {
  0, 512, 256, 128, 64, 32, 16, 8, 4, 2, 0
};

int ledPinArraySize = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  ledPinArraySize = sizeof(ledPinArray);
  // Attach the LEDs to PWM Channel.
  for (int i = 0; i < ledPinArraySize; i++) {
    ledcAttachChannel(ledPinArray[i], PWM_FRQ, PWM_BIT, chnArray[i]);
  }
  Serial.begin(112500);
}

// the loop function runs over and over again forever
void loop() {
  
  for (int i = 0; i < 11; i++) {        //flowing based on value
    for (int j = 0; j < ledPinArraySize; j++) {
      ledcWrite(ledPinArray[j], dutyArray[i + j]);
//      delay(2000);
      Serial.print("j= ");
      Serial.print(j);
      Serial.print("duty= ");
      Serial.print(dutyArray[i + j]);
      Serial.println();
    }
    delay(DELAY_TIME);
    Serial.println("Next...");
  }

}
