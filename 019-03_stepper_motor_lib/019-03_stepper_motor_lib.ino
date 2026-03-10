/**********************************************************************
* Filename    : 019-03_stepper_motor_lib
* Description : Using ULN2003 Driver Board to drive a stepper
* motor via ESP32 Wrover board.
* Auther      : Alternatives Solutions
* Modification: 2026/03/10
**********************************************************************/

// Servo Pin
const int STEPPER_PINS[] = {13, 12, 14, 27};

const int DELAY_TIME = 1000;
const bool IS_DEBUG = false;

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
//  rotateHalfWayThrough();
  rotateFullTurnBothWays();
}

void rotateFullTurnBothWays() {
  // Rotate a full turn 32 * 64
  moveSteps_hybridCode(true, 32 * 64, 3);
  delay(DELAY_TIME);
  // Rotate a half turn towards another direction
  moveSteps_hybridCode(false, 32 * 64, 3);
  delay(DELAY_TIME);
}


void rotateHalfWayThrough() {
  //Rotate a half turn [16 * 64]
  moveSteps(true, 16 * 64, 3);
  delay(DELAY_TIME);
  // Rotate a half turn towards another direction
  moveSteps(false, 16 * 64, 3);
  delay(DELAY_TIME);
}

void moveSteps(bool isForward, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep_simpleCode(isForward);  //Rotate a step
    delay(constrain(ms,3,20));          //Control the speed
  }
}


//Suggestion: the motor turns precisely when the ms range is between 3 and 20
void moveSteps_hybridCode(bool isForward, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep_hybridCode(isForward);  //Rotate a step
    delay(constrain(ms,3,20));          //Control the speed
  }
}


void moveOneStep_hybridCode(bool isForward) {
  // 'out' holds our "binary position" (0001, 0010, 0100, or 1000)
  static byte out = 0x01; 

  // 1. Logic: Decide where the "1" moves next
  if (isForward) { 
    // Forward: Shift the '1' to the left
    if (out == 0x08) { 
      out = 0x01;    // If at the end (1000), jump back to start (0001)
    } else {
      out = out << 1; // Move the '1' one spot to the left
    }
  } else {
    // Backward: Shift the '1' to the right
    if (out == 0x01) { 
      out = 0x08;    // If at the start (0001), jump to the end (1000)
    } else {
      out = out >> 1; // Move the '1' one spot to the right
    }
  }

  // 2. Output: Apply that bit pattern to our 4 pins
  for (int i = 0; i < 4; i++) {
    // This "Masking" checks: Is the i-th bit of 'out' a 1?
    bool pinState = (out >> i) & 0x01; 
    digitalWrite(STEPPER_PINS[i], pinState);
  }
}


void moveOneStep_simpleCode(bool isForward) {
  //Keep track of which step (0, 1, 2, or 3) we are on
  static int stepNum = 0;

  // 1. Update the step number based on direction
  if (isForward) { 
    stepNum++;       // Go forward
  } else {
    stepNum--;       // Go backward
  }

  // 2. "Wrap around" logic (The Ring)
  if (stepNum > 3) { stepNum = 0; }
  if (stepNum < 0) { stepNum = 3; }

  // 3. Turn off all pins first to be safe
  for (int i = 0; i < 4; i++) {
    digitalWrite(STEPPER_PINS[i], LOW);
  }

  // 4. Turn on ONLY the pin for the current step
  digitalWrite(STEPPER_PINS[stepNum], HIGH);
}

