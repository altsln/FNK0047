/**********************************************************************
* Filename    : 019_stepper_motor
* Description : Using ULN2003 Driver Board to drive a stepper
* motor via ESP32 Wrover board.
* Auther      : Alternatives Solutions
* Modification: 2026/03/09
**********************************************************************/

// Servo Pin
const int STEPPER_PINS[] = {13, 12, 14, 27};

const int DELAY_TIME = 15;
const bool IS_DEBUG = false;

// The 4-step sequence (Half-step or Full-step)
// This is the "Full Step" sequence
bool fullSteps[4][4] = {
  {HIGH, LOW, LOW, LOW},
  {LOW, HIGH, LOW, LOW},
  {LOW, LOW, HIGH, LOW},
  {LOW, LOW, LOW, HIGH}
};


// the setup function runs once when you press reset or power the board
void setup() {
  for (int ind = 0; ind < 4; ind++) {
    pinMode(STEPPER_PINS[ind], OUTPUT);
  }

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  // A waitTime of 2ms is very fast, 10ms is slower and stronger
  moveForward(10);

/*  // Monitor the values
  if (IS_DEBUG) {
    Serial.print("Pot: ");
    Serial.print(inValue);
    Serial.print(" | Servo: ");
    Serial.println(servoValue);

    delay(DELAY_TIME);
  }
*/
}

void moveForward(int waitTime) {
  // Loop through the 4 steps
  for (int i = 0; i < 4; i++) {
    // Set each of the 4 pins
    for (int j = 0; j < 4; j++) {
      digitalWrite(STEPPER_PINS[j], fullSteps[i][j]);
    }
    delay(waitTime); // Controlling speed
  }
}