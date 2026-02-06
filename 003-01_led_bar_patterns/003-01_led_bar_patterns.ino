/**********************************************************************
* Filename    : 003-01_led_bar_patterns
* Description : Make leds on a led bar to light up according
* to a specific pattern like K2000 (Flowing light)
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

  flowingOneWayWithPause3x();
  clearLedBar();
  flowingOneWayNoPause3x();
  clearLedBar();
  flowingBothWaysWithPause3x();
  clearLedBar();
  flowingBothWaysNoPause3x();
  clearLedBar();

}

  void flowingOneWayWithPause3x() {
    flowingOneWayWithPause();
    flowingOneWayWithPause();
    flowingOneWayWithPause();
  } 
  
  void flowingOneWayNoPause3x() {
    flowingOneWayNoPause();
    flowingOneWayNoPause();
    flowingOneWayNoPause();
  } 
  
  void flowingBothWaysWithPause3x() {
    flowingBothWaysWithPause();
    flowingBothWaysWithPause();
    flowingBothWaysWithPause();
  }
  
  void flowingBothWaysNoPause3x() {
    flowingBothWaysNoPause();
    flowingBothWaysNoPause();
    flowingBothWaysNoPause();
  }
  
  
void clearLedBar() {
  for (int i = ledBarSize-1; i >= 0; i--) {
    digitalWrite(ledBar[i], HIGH);
  }
  delay(12 * DELAY_TIME);
}


void flowingOneWayWithPause() {
  flowingFromLeftToRight();
  delay(10 * DELAY_TIME);
}

void flowingOneWayNoPause() {
  flowingFromLeftToRight();
  delay(DELAY_TIME);
}

void flowingBothWaysWithPause() {
  flowingFromLeftToRight();
  delay(10 * DELAY_TIME);
  flowingFromRightToLeft();
  delay(6 * DELAY_TIME);
}

void flowingBothWaysNoPause() {
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
