/**********************************************************************
* Filename    : 025_SR501_sensor
* Description : Using HC-SR501 sensor component to turn ON/OFF a LED.
* This time we are using interruption to read the data
* Auther      : Alternatives Solutions
* Modification: 2026/03/25
**********************************************************************/

// --- Configuration ---
const int SENSOR_PIN = 25;
const int LED_PIN = 4;

const int DELAY_TIME = 1000;

// 'volatile' is critical for variables shared with an ISR
volatile bool isMotionDetected = false;

// The Interrupt Service Routine (ISR)
// Needs to be stored in IRAM for speed on ESP32
void IRAM_ATTR handleMotion() {
  isMotionDetected = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("PIR Sensor Warming Up...");
  // Give the sensor 30 seconds to "learn" the room's heat signature
  for(int i = 30; i > 0; i--) {
    Serial.print(i);
    Serial.print("... ");
    delay(DELAY_TIME);
  }

  // Attach interrupt: Trigger on the RISING edge (LOW to HIGH)
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), handleMotion, RISING);

  Serial.println("\nSystem Armed. Interrupts Active!!");
}

void loop() {
  if (isMotionDetected) {
    Serial.println("--- INTERRUPT: MOTION DETECTED ---");
    digitalWrite(LED_PIN, HIGH);
    
    delay(DELAY_TIME * 2); // Keep LED on for 2 seconds
    
    digitalWrite(LED_PIN, LOW);
    isMotionDetected = false; // Reset the flag
  }
}
