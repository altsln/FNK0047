/**********************************************************************
* Filename    : 017-04_driver_motor_potentiometer_lib
* Description : Using Motor Driver "L293D" component and
* motor and potentiometer to make the motor spin at different speed
* and in different direction. 
* Auther      : Alternatives Solutions
* Modification: 2026/03/04
**********************************************************************/
// Pins for L293D
const int PIN_ENABLE1 = 13; // Speed (PWM) (Enable 1 pin)
const int PIN_IN1 = 12;     // Direction 1 (Channel 1 pin)
const int PIN_IN2 = 14;     // Direction 2 (Channel 2 pin)

// Potentiometer Pin
const int PIN_POT = 15;

// PWM Settings
const int PWM_FREQ = 5000;
const int PWM_BIT = 8;  // Precision/Resolution
const int PWM_CHANNEL = 0;

const int DELAY_TIME = 1000;
const bool DEBUG = false;


// the setup function runs once when you press reset or power the board
void setup() {
  // Set direction pins as outputs
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);

  // Correct order: Pin, Frequency, Resolution, Channel  
  ledcAttachChannel(PIN_ENABLE1, PWM_FREQ, PWM_BIT, PWM_CHANNEL);

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  int potValue = analogRead(PIN_POT);
  int speed = 0;

  // Center is roughly 2048. Let's create a "Neutral" zone.
  if (potValue > 2200) {
    // Forward
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);
    speed = map(potValue, 2200, 4095, 0, 255);
  } else if (potValue < 1900) {
    // Backward
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);
    speed = map(potValue, 1900, 0, 0, 255);
  } else {
    // Neutral/Stop
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, LOW);
    speed = 0;
  }

  ledcWrite(PIN_ENABLE1, speed);

  // Monitor the values
  if (DEBUG) {
    Serial.print("Pot: ");
    Serial.print(potValue);
    Serial.print(" | Speed: ");
    Serial.println(speed);

    delay(DELAY_TIME);
  }
}

/*
Why this works better:
  >> The "Dead Zone" (1900 to 2200):
    This stops the motor from "jittering" or humming 
    when the knob is in the middle.
  >> The map function:
    This translates your large sensor numbers (0-4095)
    into the smaller motor numbers (0-255) automatically.
  >> Hardware PWM:
    By using 5000Hz, the motor will be much quieter 
    and smoother than if you used a lower frequency.

*/