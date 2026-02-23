/**********************************************************************
* Filename    : 016-01_7_segment_display_number7
* Description : Use 7-segment component to display
* number, (number 7).  
* Auther      : Alternatives Solutions
* Modification: 2026/02/22
**********************************************************************/

#define PIN_SEGMENT_A   15    //ESP32 pin 15 connected to SegmentA(pin7)
#define PIN_SEGMENT_B    2    //ESP32 pin  2 connected to SegmentB(pin6)
#define PIN_SEGMENT_C    4    //ESP32 pin  4 connected to SegmentC(pin4)
#define DELAY_TIME      500

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_SEGMENT_A, OUTPUT);
  pinMode(PIN_SEGMENT_B, OUTPUT);
  pinMode(PIN_SEGMENT_C, OUTPUT);
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PIN_SEGMENT_A, LOW);
  digitalWrite(PIN_SEGMENT_B, LOW);
  digitalWrite(PIN_SEGMENT_C, LOW);
  delay(2 * DELAY_TIME);
  digitalWrite(PIN_SEGMENT_A, HIGH);
  digitalWrite(PIN_SEGMENT_B, HIGH);
  digitalWrite(PIN_SEGMENT_C, HIGH);
  delay(2 * DELAY_TIME);
}
