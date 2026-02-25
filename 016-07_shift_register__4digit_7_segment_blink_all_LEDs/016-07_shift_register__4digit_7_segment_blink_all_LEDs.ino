/**********************************************************************
* Filename    : 016-07_shift_register__4digit_7_segment_blink_all_LEDs
* Description : Wire shift register component (74HC595) and a
* 4 Digit 7-segment component (blink all LEDs on each display).
* Auther      : Alternatives Solutions
* Modification: 2026/02/24
**********************************************************************/

#define PIN_LATCH       13    //ESP32 pin 13 connected to 595 Latch(pin12)
#define PIN_DATA        12    //ESP32 pin 12 connected to 595 DS(pin14)
#define PIN_CLOCK       14    //ESP32 pin 14 connected to 595 Clock(pin11)

#define DIGIT_1_PIN     23    //ESP32 Pin 23 connected to 4D_7-S(pin12)
#define DIGIT_2_PIN     22    //ESP32 Pin 22 connected to 4D_7-S(pin9)
#define DIGIT_3_PIN     21    //ESP32 Pin 21 connected to 4D_7-S(pin8)
#define DIGIT_4_PIN     19    //ESP32 Pin 19 connected to 4D_7-S(pin6)

#define DELAY_TIME      500
/*
// Define the encoding of characters 0-F for the common-anode 7-Segment Display
byte numbers[] = {
  0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
  0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};
*/
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);

  pinMode(DIGIT_1_PIN, OUTPUT);
  pinMode(DIGIT_2_PIN, OUTPUT);
  pinMode(DIGIT_3_PIN, OUTPUT);
  pinMode(DIGIT_4_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {

  for (int i = 0; i < 4; i++) {
    //select display
    switch (i) {
      case 0:selectDigitalDisplay(DIGIT_1_PIN); break;
      case 1:selectDigitalDisplay(DIGIT_2_PIN); break;
      case 2:selectDigitalDisplay(DIGIT_3_PIN); break;
      case 3:selectDigitalDisplay(DIGIT_4_PIN); break;
      default: break;
    }
    
    for (int j = 0; j < 3; j++) { 
      writeTo74HC595(LSBFIRST, 0xFF);
      delay(DELAY_TIME);
      writeTo74HC595(LSBFIRST, 0x00);
      delay(DELAY_TIME);
    } 
  } 
}

void selectDigitalDisplay(int display){
  //turn off all 4 display
  digitalWrite(DIGIT_1_PIN, LOW);
  digitalWrite(DIGIT_2_PIN, LOW);
  digitalWrite(DIGIT_3_PIN, LOW);
  digitalWrite(DIGIT_4_PIN, LOW);

  //now open the selected single display
  digitalWrite(display, HIGH);
}

void writeTo74HC595(int order, byte dataElt) {
  //Output LOW level to latch pin
  digitalWrite(PIN_LATCH, LOW);

  Serial.print("Sending Binary: ");
  Serial.print(dataElt, BIN);
  Serial.print("\n");

  //send serial data to 74HC595
  shiftOut(PIN_DATA, PIN_CLOCK, order, dataElt);
  //Output high level to latch pin and the component
  // 74HC595 will update the data to the parallel output port
  digitalWrite(PIN_LATCH, HIGH);
}
