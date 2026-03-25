/**********************************************************************
* Filename    : 025_SR501_sensor
* Description : Using HC-SR501 sensor component to turn ON/OFF a LED.
* Auther      : Alternatives Solutions
* Modification: 2026/03/25
**********************************************************************/

// --- Configuration ---
const int SENSOR_PIN = 25;
const int LED_PIN = 4;

const int DELAY_TIME = 1000;

void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("PIR Sensor Warming Up...");
  // Give the sensor 30 seconds to "learn" the room's heat signature
  for(int i = 30; i > 0; i--) {
    Serial.print(i);
    Serial.print("... ");
    delay(DELAY_TIME);
  }
  Serial.println("\nSystem Ready.");
}

void loop() {
  //read data
  int sensorState = digitalRead(SENSOR_PIN);

  if (sensorState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("--- MOTION DETECTED ---");
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(DELAY_TIME / 10); // Small delay for stability

}

/*
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(DELAY_TIME);
    digitalWrite(LED_PIN, LOW);
    delay(DELAY_TIME);
  }*/