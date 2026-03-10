/**********************************************************************
* Filename    : 019-02_stepper_motor_counter_clkwise
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
// This is the "Half Step" sequence
bool halfSteps[8][4] = {
  {HIGH, LOW, LOW, LOW},
  {HIGH, HIGH, LOW, LOW},
  {LOW, HIGH, LOW, LOW},
  {LOW, HIGH, HIGH, LOW},
  {LOW, LOW, HIGH, LOW},
  {LOW, LOW, HIGH, HIGH},
  {LOW, LOW, LOW, HIGH},
  {HIGH, LOW, LOW, HIGH}
};


// the setup function runs once when you press reset or power the board
void setup() {
  for (int ind = 0; ind < 4; ind++) {
    // Ensure all start OFF
    pinMode(STEPPER_PINS[ind], OUTPUT);
  }

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  // A waitTime of 2ms is very fast, 10ms is slower and stronger
  moveBackward(10);
}

void moveBackward(int waitTime) {
  // Loop through the 8 steps
  for (int i = 0; i < 8; i++) {
    // Set each of the 4 pins
    for (int j = 3; j >= 0; j--) {
      digitalWrite(STEPPER_PINS[j], halfSteps[i][j]);
    }
    // Controlling speed
    delay(waitTime);  // Start with 3ms. Too fast and it will hum!
  }
}

void moveForward(int waitTime) {
  // Loop through the 8 steps
  for (int i = 0; i < 8; i++) {
    // Set each of the 4 pins
    for (int j = 0; j < 4; j++) {
      digitalWrite(STEPPER_PINS[j], halfSteps[i][j]);
    }
    // Controlling speed
    delay(waitTime);  // Start with 3ms. Too fast and it will hum!
  }
}

