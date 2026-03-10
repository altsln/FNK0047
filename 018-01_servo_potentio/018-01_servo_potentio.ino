/**********************************************************************
* Filename    : 018-01_servo_potentio
* Description : Control servo motor with a potentiometer knob. 
* Auther      : Alternatives Solutions
* Modification: 2026/03/08
**********************************************************************/

#include <ESP32Servo.h>

Servo servObj;   //create servo object to control a servo

// ADC Max Value read from the potentiometer
const int ADC_MAX_VALUE = 4095;

// Servo Pin
const int PIN_SERVO = 15;
// Potentio Pin
const int PIN_POT = 13;

// Servo stansard  frequence
const int SERV_FREQ = 50;

const int DELAY_TIME = 15;
const bool IS_DEBUG = false;


// the setup function runs once when you press reset or power the board
void setup() {
  servObj.setPeriodHertz(SERV_FREQ);     // standard 50 hz servo
  servObj.attach(PIN_SERVO, 500, 2500);  // attaches the servo on servoPin to the servo object

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  //read potentiometer value 
  int inValue = analogRead(PIN_POT);

  //Scale it to me used in the correct value for servo Motor
  int servoValue = map(inValue, 0, ADC_MAX_VALUE, 0, 180);

  //set the servo motor according to the scaled value
  servObj.write(servoValue);
  delay(DELAY_TIME);  // waits 15ms for the servo to reach the position

  // Monitor the values
  if (IS_DEBUG) {
    Serial.print("Pot: ");
    Serial.print(inValue);
    Serial.print(" | Servo: ");
    Serial.println(servoValue);

    delay(DELAY_TIME);
  }
}
