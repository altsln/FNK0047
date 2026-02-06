/**********************************************************************
* Filename    : 003_led_bar
* Description : Make leds on a led bar to light up according
* to a specific pattern.
* Auther      : Alternative Solutions
* Modification: 2026/02/05
**********************************************************************/

#define DELAY_TIME   100

//leds array
byte ledBar[] = {15, 2, 0, 4, 5, 18, 19, 21, 22, 23};
int ledBarSize = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin in the LedBar as an output.
  ledBarSize = sizeof(ledBar);
  for (int i = 0; i < ledBarSize; i++) {
    pinMode(ledBar[i], OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {
  flowingFromLeftToRight();
  flowingFromRightToLeft();  
}


void flowingFromLeftToRight() {
  for (int i = 0; i < ledBarSize; i++) {
    digitalWrite(ledBar[i], HIGH);
    delay(DELAY_TIME);
    digitalWrite(ledBar[i], LOW);
  }
}

void flowingFromRightToLeft() {
  for (int i = ledBarSize-1; i >= 0; i--) {
    digitalWrite(ledBar[i], HIGH);
    delay(DELAY_TIME);
    digitalWrite(ledBar[i], LOW);
  }
}
