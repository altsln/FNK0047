/**********************************************************************
* Filename    : 017-01_Relay_motor_button
* Description : Using relay "HK4100F-DC 5V-SHG" component and
* motor and motor to make the motor spin. 
* Auther      : Alternatives Solutions
* Modification: 2026/03/03
**********************************************************************/

#define PIN_RELAY       13
#define PIN_BTN         15

#define DELAY_TIME      1000
#define DEBUG           false

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_RELAY, OUTPUT);     // Set relay pin into output mode
  pinMode(PIN_BTN, INPUT);        // Set push button pin into input mode
  digitalWrite(PIN_RELAY, LOW);   // Set the initial state of relay into "off"

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  // Read the state of the button
  int btnState = digitalRead(PIN_BTN);

  // If the button is pressed (HIGH)
  if (btnState == LOW) {
    digitalWrite(PIN_RELAY, HIGH); // Turn motor ON
    if (DEBUG) Serial.println("Turn motor ON");
  } else {
    digitalWrite(PIN_RELAY, LOW);  // Turn motor OFF
    if (DEBUG) Serial.println("Turn motor OFF");
  }
}
