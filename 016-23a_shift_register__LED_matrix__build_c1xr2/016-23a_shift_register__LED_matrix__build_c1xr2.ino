/**********************************************************************
* Filename    : 016-23a_shift_register__LED_matrix__build_c1xr2
* Description : Setup shift register component (74HC595) and a
* LED matrix component to blink more LEDs.(ry x c1) y = 1..8  
* Auther      : Alternatives Solutions
* Modification: 2026/02/27
**********************************************************************/

#define PIN_LATCH       13    //ESP32 pin 13 connected to 595 Latch(pin12)
#define PIN_DATA        12    //ESP32 pin 12 connected to 595 DS(pin14)
#define PIN_CLOCK       14    //ESP32 pin 14 connected to 595 Clock(pin11)

#define DELAY_TIME      100
#define DEBUG           false

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
  // --- [TURN ON] ROW 1, COL 1---
  digitalWrite(PIN_LATCH, LOW);
  // First 8 bits go to IC2 (Columns)
  // 0xFE is 11111110 in binary (Only Q0 is LOW/Ground)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0xFE); 
  // Next 8 bits stay in IC1 (Rows)
  // 0x01 is 00000001 in binary (Only Q0 is HIGH/Power)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0x01); 
  digitalWrite(PIN_LATCH, HIGH);
  delay(DELAY_TIME); 

  
  // --- [TURN ON] ROW 1, COL 2---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x02);
  
  // --- [TURN ON] ROW 1, COL 3---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x04);

  // --- [TURN ON] ROW 1, COL 4---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x08);

  // --- [TURN ON] ROW 1, COL 5---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x10);

  // --- [TURN ON] ROW 1, COL 6---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x20);

  // --- [TURN ON] ROW 1, COL 7---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x40);

  // --- [TURN ON] ROW 1, COL 8---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x80);

  // --- TURN OFF ---
  // All Columns inactive (HIGH) 0xFF
  // All Rows inactive (LOW)     0x00
  writeTo74HC595s(MSBFIRST, 0xFF, 0x00);

  //manage column
  // --- [TURN ON] ROW 1, COL 1---
  digitalWrite(PIN_LATCH, LOW);
  // First 8 bits go to IC2 (Columns)
  // 0xFE is 11111110 in binary (Only Q0 is LOW/Ground)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0xFE); 
  // Next 8 bits stay in IC1 (Rows)
  // 0x01 is 00000001 in binary (Only Q0 is HIGH/Power)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0x01); 
  digitalWrite(PIN_LATCH, HIGH);
  delay(DELAY_TIME); 

  // --- [TURN ON] ROW 2, COL 1---
  digitalWrite(PIN_LATCH, LOW);
  // First 8 bits go to IC2 (Columns)
  // 0xFE is 11111101 in binary (Only Q1 is LOW/Ground)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0xFD); 
  // Next 8 bits stay in IC1 (Rows)
  // 0x01 is 00000001 in binary (Only Q0 is HIGH/Power)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0x01); 
  digitalWrite(PIN_LATCH, HIGH);
  delay(DELAY_TIME); 

  // --- TURN OFF ---
  writeTo74HC595s(MSBFIRST, 0xFF, 0x00);
}


void writeTo74HC595s(int order, byte dataElt1, byte dataElt2) {
  //Output LOW level to latch pin
  digitalWrite(PIN_LATCH, LOW);

  if (DEBUG) {
    Serial.print("Sending Binary1: ");
    Serial.print(dataElt1, BIN);
    Serial.print("\n");
  }
  //send serial data to 74HC595 IC1
  shiftOut(PIN_DATA, PIN_CLOCK, order, dataElt1);

  if (DEBUG) {
    Serial.print("Sending Binary2: ");
    Serial.print(dataElt2, BIN);
    Serial.print("\n");
  }  
  //send serial data to 74HC595 IC2
  shiftOut(PIN_DATA, PIN_CLOCK, order, dataElt2);
  //Output high level to latch pin and the component
  // 74HC595 will update the data to the parallel output port

  digitalWrite(PIN_LATCH, HIGH);
  delay(DELAY_TIME); 
}
