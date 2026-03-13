/**********************************************************************
* Filename    : 021_ultrasonic_ranging_no_lib_imported
* Description : Using HC-SRO4 to control the ranging
* "HC-SR04 is an Utrasonic component".
* Auther      : Alternatives Solutions
* Modification: 2026/03/11
**********************************************************************/

//HC-SR04 PIN
const int TRIG_PIN = 4;
const int ECHO_PIN = 5;

const int DELAY_TIME = 1000;
const bool IS_DEBUG = false;


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");

  // Clean the TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
}

// the loop function runs over and over again forever
void loop() {
  //trigger the sensor by sending a 10us pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //read the echo Pin (returns the travel time in microsceconds)
  long duration = pulseIn(ECHO_PIN, HIGH, 50000);

  //calculate the distance
  //Distance = (Time * Speed of Sound) / 2 (there and back)
  //speed of sound is 0.034 cm/us
  float distanceCm = duration * 0.034 / 2;

  // Monitor the values
  if (duration == 0) {
    Serial.println("No pulse received. Check if VCC is in the 5V pin!");
  } else {
    if (IS_DEBUG) {
      Serial.print("Raw Duration: ");
      Serial.print(duration);
      Serial.print(" | ");
      Serial.print("Distance: ");
      Serial.print(distanceCm);
      Serial.println(" cm");
  //    delay(DELAY_TIME);
    }
  }
  
  // 
  delay(500);
}
