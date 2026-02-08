/**********************************************************************
* Filename    : 004-02_breathing_light_pwm_2_LEDs
* Description : Make 2 LEDs light fade in and out
* using PWM (Pulse Width Modulation)
* Auther      : Alternative Solutions
* Modification: 2026/02/06
**********************************************************************/

#define LED_BUILTIN  2    //define the led pin 1
#define LED_XTERNAL  4    //define the led pin 2
#define PWM_CHN_1    7    //define PWM Channel 1
#define PWM_CHN_2    5    //define PWM Channel 2
#define PWM_FRQ      1000 //define PWM Frequency
#define PWM_BIT      8    //define PWM Precision
#define MAX_VALUE_1  256  //based on 8bits the max value is 256
#define MAX_VALUE_2  128  //based on 8bits the max value is 256
#define DELAY_TIME   1500 //for better understanding (use different values
// 2000, 1500, 1000, 50 etc ...) At 50 brightness variation is not visible to 
// the naked eyes. At least you can see something at 500. 

//define LED pin Array
const byte ledPinArray[] = {LED_BUILTIN, LED_XTERNAL};
//define the PWM channels
const byte chnArray[] = {PWM_CHN_1, PWM_CHN_2};
//define the PWM duties
const int dutyArray[] = {
  0, 0,
  MAX_VALUE_1, MAX_VALUE_2,
  0, 0
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
  
  for (int i = 0; i < 4; i++) {        //flowing one side to other side
    for (int j = 0; j < ledPinArraySize; j++) {
      ledcWrite(ledPinArray[j], dutyArray[i + j]);
      //delay(2000);
      Serial.print("j= ");
      Serial.print(j);
      Serial.print(" duty= ");
      Serial.print(dutyArray[i + j]);
      Serial.println();
    }
    delay(DELAY_TIME);
    Serial.println("Next...");
  }
  
  for (int i = 0; i < 4; i++) {      //flowing one side to other side
    for (int j = ledPinArraySize - 1; j > -1; j--) {
      ledcWrite(ledPinArray[j], dutyArray[i + (ledPinArraySize - 1 - j)]);
    }
    delay(DELAY_TIME);
  }


}
