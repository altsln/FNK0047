/**********************************************************************
* Filename    : 005-00_RGB_color_check
* Description : Use RGB LED to show one color at a time,
* just to check that it works
* Auther      : Alternative Solutions
* Modification: 2026/02/08
**********************************************************************/

#define DELAY_TIME   50

//define LED pin Array Red, Green, Blue
const byte ledPinArray[] = {23, 5, 15}; 
int ledPinArraySize = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  ledPinArraySize = sizeof(ledPinArray);
  // configure the LEDs pin as OUTPUT.
  for (int i = 0; i < ledPinArraySize; i++) {
    pinMode(ledPinArray[i], OUTPUT);
  }
  Serial.begin(112500);
}


// the loop function runs over and over again forever
void loop() {
  clearAllLeds();
  //turn red LED ON
  delay(11 * DELAY_TIME);
  digitalWrite(ledPinArray[0], LOW);
  delay(11 * DELAY_TIME);
  
  clearAllLeds();
  //turn green LED ON
  delay(11 * DELAY_TIME);
  digitalWrite(ledPinArray[1], LOW);
  delay(11 * DELAY_TIME);
  
  clearAllLeds();
  //turn Blue LED ON
  delay(11 * DELAY_TIME);
  digitalWrite(ledPinArray[2], LOW);
  delay(11 * DELAY_TIME);

  clearAllLeds();
  //turn red LED ON
  delay(11 * DELAY_TIME);
  digitalWrite(ledPinArray[0], LOW);
  delay(11 * DELAY_TIME);
  //turn green LED ON
  digitalWrite(ledPinArray[0], HIGH);
  digitalWrite(ledPinArray[1], LOW);
  delay(11 * DELAY_TIME);
  //turn Blue LED ON
  digitalWrite(ledPinArray[1], HIGH);
  digitalWrite(ledPinArray[2], LOW);
  delay(11 * DELAY_TIME);

}

void clearAllLeds() {
  for (int i = 0; i < ledPinArraySize; i++) {
    digitalWrite(ledPinArray[i], HIGH);
  }
  delay(DELAY_TIME);
}