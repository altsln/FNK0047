/**********************************************************************
* Filename    : 016-03_shift_register__7_segment_setup_one_LED_on
* Description : Setup a shift register component (74HC595) and a
* 7-segment component. Before displaying number first turn one LED on.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/23
**********************************************************************/

#define PIN_LATCH       13    //ESP32 pin 13 connected to 595 Latch(pin12)
#define PIN_DATA        12    //ESP32 pin 12 connected to 595 DS(pin14)
#define PIN_CLOCK       14    //ESP32 pin 14 connected to 595 Latch(pin11)
#define DELAY_TIME      500

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  writeTo74HC595(LSBFIRST, 0x80);
  delay(2 * DELAY_TIME);
  writeTo74HC595(LSBFIRST, 0x00);
  delay(2 * DELAY_TIME);
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
