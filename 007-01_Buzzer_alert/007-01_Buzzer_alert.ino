/**********************************************************************
* Filename    : 007-01_Buzzer_alert
* Description : Using a button to make a passive buzzer to ring.   
* Auther      : Alternatives Solutions
* Modification: 2026/02/12
**********************************************************************/

#define PIN_BUZZER    13
#define PIN_BUTTON    4
#define PWM_CHN       1

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_BUTTON, INPUT);
  ledcAttachChannel(PIN_BUZZER, 1, 10, PWM_CHN);
  ledcWriteTone(PIN_BUZZER, 2000);    //Sound at 2KHz for 0.3 seconds
  delay(300);
}

// the loop function runs over and over again forever
void loop() {
  if (LOW == digitalRead(PIN_BUTTON)) {
    alert();
  } else {
    ledcWriteTone(PIN_BUZZER, 0);
  }  
}

void alert() {
  float sinVal;       //Define a variable to save the sine value
  int toneVal;        //Define a variable to save sound frequency
  for (int x = 0; x < 360; x += 10) {   //x moves from 0 to 360
    sinVal = sin(x * (PI / 180));          //calculate the sin of x
    toneVal = 2000 + sinVal * 500;      //calculate sound frequency 
    ledcWriteTone(PIN_BUZZER, toneVal);
    delay(10);
  }
}
