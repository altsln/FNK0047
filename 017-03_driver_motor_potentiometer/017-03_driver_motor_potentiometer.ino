/**********************************************************************
* Filename    : 017-03_driver_motor_potentiometer
* Description : Using Motor Driver "L293D" component and
* motor and potentiometer to make the motor spin at different speed. 
* Auther      : Alternatives Solutions
* Modification: 2026/03/04
**********************************************************************/

#define PIN_IN1       12  //for L293D Channel 1 pin
#define PIN_IN2       14  //for L293D Channel 2 pin

#define PIN_ENABLE1   13  //for L293D Enable 1 pin
#define PWM_CHANNEL   0
#define PWM_FRQ       1000
#define PWM_BIT       11  //precision

#define DELAY_TIME      10
#define DEBUG           false

boolean rotationDir;
int rotationSpeed;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_IN1, OUTPUT);     // Set channel 1 pin into output mode
  pinMode(PIN_IN2, OUTPUT);     // Set channel 2 pin into output mode
  ledcAttachChannel(PIN_ENABLE1, PWM_FRQ, PWM_BIT, PWM_CHANNEL);

  rotationDir = false;
  rotationSpeed = 0;

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  // Read and convert the voltage of the poyentiometer into digital
  int potenValue = analogRead(A0);

  if (DEBUG) {
    Serial.print("pot value= ");
    Serial.println(potenValue);
  }

  //delay(DELAY_TIME);


  //compare the value with 2048
  rotationSpeed = potenValue - 2048; 
  if (potenValue > 2048) {
    rotationDir = true;   //clockwise rotation
    if (DEBUG) Serial.println("clockwise rotation");
  } else {
    rotationDir = false;  //counter clockwise rotation
    if (DEBUG) Serial.println("counter clockwise rotation");
  }

  if (DEBUG) {
    Serial.print("rotation speed = ");
    Serial.println(rotationSpeed);
  }
  rotationSpeed = abs(rotationSpeed);
  //control the steering and speed of the motor
  driveMotor(rotationDir, constrain(rotationSpeed, 0, 2048));
}

void driveMotor(bool isClkwise, int speed) {
  //control motor direction of rotation
  if (isClkwise) {
    if (DEBUG) Serial.println("[driveMotor] clockwise rotation");
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);
  } else {
    if (DEBUG) Serial.println("[driveMotor] counter clockwise rotation");
    digitalWrite(PIN_IN2, HIGH);
    digitalWrite(PIN_IN1, LOW);
  }
  //control motor rotation speed
  ledcWrite(PIN_ENABLE1, speed);
}
