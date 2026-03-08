/**********************************************************************
* Filename    : 018_servo
* Description : Control servo motor. 
* Auther      : Alternatives Solutions
* Modification: 2026/03/05
**********************************************************************/

#include <ESP32Servo.h>

Servo servObj;   //create servo object to control a servo

// Servo Pin
const int PIN_SERVO = 15;

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
  for (int pos = 0; pos <= 180; pos++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servObj.write(pos);     // tell servo to go to position in variable 'pos'
    delay(DELAY_TIME);      // waits 15ms for the servo to reach the position
  }
  for (int pos = 180; pos >= 0; pos--) { // goes from 180 degrees to 0 degrees
    servObj.write(pos);     // tell servo to go to position in variable 'pos'
    delay(DELAY_TIME);      // waits 15ms for the servo to reach the position
  }

/*  // Monitor the values
  if (DEBUG) {
    Serial.print("Pot: ");
    Serial.print(potValue);
    Serial.print(" | Speed: ");
    Serial.println(speed);

    delay(DELAY_TIME);
  }
*/
}
