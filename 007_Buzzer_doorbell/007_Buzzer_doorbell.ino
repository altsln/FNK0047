/**********************************************************************
* Filename    : 007_Buzzer_doorbell
* Description : Using a button to make an active buzzer to ring.   
* Auther      : Alternatives Solutions
* Modification: 2026/02/12
**********************************************************************/

#define PIN_BUZZER    13
#define PIN_BUTTON    4

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (LOW == digitalRead(PIN_BUTTON)) {
    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    digitalWrite(PIN_BUZZER, LOW);
  }
  
}

