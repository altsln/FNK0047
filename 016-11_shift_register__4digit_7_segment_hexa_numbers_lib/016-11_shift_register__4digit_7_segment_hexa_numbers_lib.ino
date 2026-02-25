/**********************************************************************
* Filename    : 016-11_shift_register__4digit_7_segment_hexa_numbers_lib
* Description : Using shift register component (74HC595) and a
* 4 Digit 7-segment component to display numbers.(improved version)  
* Auther      : Alternatives Solutions
* Modification: 2026/02/25
**********************************************************************/

#define PIN_LATCH       13    //ESP32 pin 13 connected to 595 Latch(pin12)
#define PIN_DATA        12    //ESP32 pin 12 connected to 595 DS(pin14)
#define PIN_CLOCK       14    //ESP32 pin 14 connected to 595 Clock(pin11)

#define DIGIT_1_PIN     23    //ESP32 Pin 23 connected to 4D_7-S(pin12)
#define DIGIT_2_PIN     22    //ESP32 Pin 22 connected to 4D_7-S(pin9)
#define DIGIT_3_PIN     21    //ESP32 Pin 21 connected to 4D_7-S(pin8)
#define DIGIT_4_PIN     19    //ESP32 Pin 19 connected to 4D_7-S(pin6)

#define DELAY_TIME      5

// Define the encoding of characters 0-F for the common-anode 7-Segment Display
byte numbers[] = {
  0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
  0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};

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
  //Display All numbers
  static unsigned long lastUpdate = 0; 
  static int hexaOffset = 0;
//The display must ALWAYS be refreshed
//display 4 consecutive array rows starting from hexaOffset
  for (int i = 0; i < 4; i++) {
    selectDigitalDisplay(i);  //select display
    int pos = (hexaOffset + i) % 16;
    writeTo74HC595(LSBFIRST, numbers[pos]);
    delay(DELAY_TIME); //check that DELAY_TIME is 5ms

    // Since you are Common Anode, digitalWrite(pin, LOW) turns it off.
    turnDigitalDisplayOFF(i); 
  
    // (Optional) Send 0xFF to the Shift Register to turn all segments off too
    // writeTo74HC595(LSBFIRST, 0xFF);
  }

//Implement now the logic to change the offset after 500ms
  if ((millis() - lastUpdate) >= 500) {
    hexaOffset += 4; // Jump to the next set: 0123 -> 4567 -> 89AB...
    if (hexaOffset >= 16) {
      hexaOffset = 0;
    }
    lastUpdate = millis(); 
  }
}

void turnDigitalDisplayOFF(int pos) {
  //select display
  switch (pos) {
    case 0:digitalWrite(DIGIT_1_PIN, LOW); break;
    case 1:digitalWrite(DIGIT_2_PIN, LOW); break;
    case 2:digitalWrite(DIGIT_3_PIN, LOW); break;
    case 3:digitalWrite(DIGIT_4_PIN, LOW); break;
    default: break;
  }  
}

void selectDigitalDisplay(int pos){
  //turn off all 4 display
  digitalWrite(DIGIT_1_PIN, LOW);
  digitalWrite(DIGIT_2_PIN, LOW);
  digitalWrite(DIGIT_3_PIN, LOW);
  digitalWrite(DIGIT_4_PIN, LOW);

  //select display
  switch (pos) {
    case 0:digitalWrite(DIGIT_1_PIN, HIGH); break;
    case 1:digitalWrite(DIGIT_2_PIN, HIGH); break;
    case 2:digitalWrite(DIGIT_3_PIN, HIGH); break;
    case 3:digitalWrite(DIGIT_4_PIN, HIGH); break;
    default: break;
  }  
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
