/**********************************************************************
* Filename    : 016-02_7_segment_display_number8dot
* Description : Use 7-segment component to display
* number, (number 8.).  
* Auther      : Alternatives Solutions
* Modification: 2026/02/23
**********************************************************************/

#define PIN_SEGMENT_A   15    //ESP32 pin 15 connected to SegmentA(pin7)
#define PIN_SEGMENT_B    2    //ESP32 pin  2 connected to SegmentB(pin6)
#define PIN_SEGMENT_C    4    //ESP32 pin  4 connected to SegmentC(pin4)
#define PIN_SEGMENT_D    5    //ESP32 pin  5 connected to SegmentD(pin2)
#define PIN_SEGMENT_E   18    //ESP32 pin 18 connected to SegmentE(pin1)
#define PIN_SEGMENT_F   19    //ESP32 pin 19 connected to SegmentE(pin9)
#define PIN_SEGMENT_G   21    //ESP32 pin 21 connected to SegmentE(pin10)
#define PIN_SEGMENT_DP  22    //ESP32 pin 22 connected to SegmentE(pin5)
#define DELAY_TIME      500

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_SEGMENT_A, OUTPUT);
  pinMode(PIN_SEGMENT_B, OUTPUT);
  pinMode(PIN_SEGMENT_C, OUTPUT);
  pinMode(PIN_SEGMENT_D, OUTPUT);
  pinMode(PIN_SEGMENT_E, OUTPUT);
  pinMode(PIN_SEGMENT_F, OUTPUT);
  pinMode(PIN_SEGMENT_G, OUTPUT);
  pinMode(PIN_SEGMENT_DP, OUTPUT);
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  lightOnAllLEDs(true);
  delay(2 * DELAY_TIME);

  lightOnAllLEDs(false);
  delay(2 * DELAY_TIME);

  /*digitalWrite(PIN_SEGMENT_A, LOW);
  digitalWrite(PIN_SEGMENT_B, LOW);
  digitalWrite(PIN_SEGMENT_C, LOW);
  digitalWrite(PIN_SEGMENT_D, LOW);
  digitalWrite(PIN_SEGMENT_E, LOW);
  digitalWrite(PIN_SEGMENT_F, LOW);
  digitalWrite(PIN_SEGMENT_G, LOW);
  digitalWrite(PIN_SEGMENT_DP, LOW);
  delay(2 * DELAY_TIME);
  digitalWrite(PIN_SEGMENT_A, HIGH);
  digitalWrite(PIN_SEGMENT_B, HIGH);
  digitalWrite(PIN_SEGMENT_C, HIGH);
  digitalWrite(PIN_SEGMENT_D, HIGH);
  digitalWrite(PIN_SEGMENT_E, HIGH);
  digitalWrite(PIN_SEGMENT_F, HIGH);
  digitalWrite(PIN_SEGMENT_G, HIGH);
  digitalWrite(PIN_SEGMENT_DP, HIGH);
  delay(2 * DELAY_TIME);
*/
}


void lightOnAllLEDs(bool isON) {
  byte state = LOW;
  if (!isON) {
    state = HIGH;
  }
  
  //update LED state based on state
  digitalWrite(PIN_SEGMENT_A, state);
  digitalWrite(PIN_SEGMENT_B, state);
  digitalWrite(PIN_SEGMENT_C, state);
  digitalWrite(PIN_SEGMENT_D, state);
  digitalWrite(PIN_SEGMENT_E, state);
  digitalWrite(PIN_SEGMENT_F, state);
  digitalWrite(PIN_SEGMENT_G, state);
  digitalWrite(PIN_SEGMENT_DP, state);
} 