/**********************************************************************
* Filename    : 004-03_breathing_light_pwm_Ledbar
* Description : Make Ledbar lights to fade in and out
* using PWM (Pulse Width Modulation) according to 
* a specific pattern
* Auther      : Alternative Solutions
* Modification: 2026/02/07
**********************************************************************/

#define PWM_FRQ      1000 //define PWM Frequency
#define PWM_BIT      10   //define PWM Precision

#define DELAY_TIME   50

//define LED pin Array
const byte ledPinArray[] = {15, 2, 0, 4, 5, 18, 19, 21, 22, 23};
//define the PWM channels
const byte chnArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//define the PWM duties
const int dutyArray[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1024, 512, 256, 128, 64, 32, 16, 8, 4, 2,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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
  
  for (int i = 0; i < 20; i++) {        //flowing one side to other side
    Serial.print("i= ");
    Serial.println(i);
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
  
  for (int i = 0; i < 20; i++) {      //flowing one side to other side
    for (int j = ledPinArraySize - 1; j >= 0; j--) {
      ledcWrite(ledPinArray[j], dutyArray[i + (ledPinArraySize - 1 - j)]);
    }
    delay(DELAY_TIME);
  }
}
