/**********************************************************************
* Filename    : 016-00_7-segment_blink_LED_A
* Description : Use 7-segment component to display
* number. But now just blink one LED (LED A) of
* the component.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/22
**********************************************************************/

#define PIN_SEGMENT_A   15    //ESP32 pin 15 connected to SegmentA(pin7)
#define DELAY_TIME      500

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_SEGMENT_A, OUTPUT);
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PIN_SEGMENT_A, LOW);
  delay(2 * DELAY_TIME);
  digitalWrite(PIN_SEGMENT_A, HIGH);
  delay(2 * DELAY_TIME);
}
