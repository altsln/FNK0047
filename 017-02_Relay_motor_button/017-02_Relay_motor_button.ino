/**********************************************************************
* Filename    : 017-02_Relay_motor_button
* Description : Using relay "HK4100F-DC 5V-SHG" component and
* motor and button to make the motor spin. 
* Auther      : Alternatives Solutions
* Modification: 2026/03/03
**********************************************************************/

#define PIN_RELAY       13
#define PIN_BTN         15

#define DELAY_TIME      1000
#define DEBUG           false

int btnState = HIGH;          // Record button state, and initial the state to high level
int previousBtnState = HIGH;  // Record the button state of last detection
long lastChangeTime = 0;      // Record the time point for button state change
int relayState = LOW;         // Record relay state, and initial the state to low level

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
  // Read the current state of the button
  int currentBtnState = digitalRead(PIN_BTN);

  // If button pin state has changed, record the time point
  if (currentBtnState != previousBtnState) {
    lastChangeTime = millis();
  }

  // If button state changes, and stays stable for a while, then it should have skipped the bounce area
  if (millis() - lastChangeTime > 10) {
    if (btnState != currentBtnState) {      // Confirm button state has changed
      btnState = currentBtnState;
      if (btnState == LOW) {                // Low level indicates the button is pressed
        relayState = !relayState;           // Reverse relay state
        digitalWrite(PIN_RELAY, relayState); // Update relay state
      }
    }
  }
  previousBtnState = currentBtnState; // Save the state of last button
}
