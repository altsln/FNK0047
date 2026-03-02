/**********************************************************************
* Filename    : 016-25a_shift_register__LED_matrix__smiling_face
* Description : Using shift register component (74HC595) and a
* LED matrix component to display smiling face.   
* Auther      : Alternatives Solutions
* Modification: 2026/03/01
**********************************************************************/

#define PIN_LATCH       13    //ESP32 pin 13 connected to 595 Latch(pin12)
#define PIN_DATA        12    //ESP32 pin 12 connected to 595 DS(pin14)
#define PIN_CLOCK       14    //ESP32 pin 14 connected to 595 Clock(pin11)

#define DELAY_TIME      2
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
  //displayAllLEDsOnRow1AndColumn1();

  //displayXshape();
  //displaySmilingFaceUpsideDown();
  //displaySmilingFace();
  //writeTo74HC595s(MSBFIRST, ~0b10100101, 0x04);

  displayFace();
}

// il y a encore beaucoup de chose a explorer avec LED Matrix
//mais la je dois avancer. Pour rappel memore consulte 
//ton echange avec Gemini sur ton hotmail compte que tu as googlelise

void displayFace() {
  byte face[] = {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};
  byte rowValue = 0x01;

  for (int i = 0; i < 8; i++) {
    // 1. Send Data
    writeTo74HC595s(MSBFIRST, ~face[i], rowValue);
    
    // 2. Hold it for a tiny moment (Persistence of Vision)
    delay(2); 
    
    // 3. CLEAR (This prevents the "mess" on the next row)
    writeTo74HC595s(MSBFIRST, 0xFF, 0x00); 
    
    // 4. Move to next row
    rowValue <<= 1; 
  }
}

void displaySmilingFace() {

/*  // Define the pattern data for a smiling face
  const int smilingFace[] = {                       //"^ⅴ^"
    0x1C, 0x22, 0x51, 0x45, 0x45, 0x51, 0x22, 0x1C
  };
*/
  // Symmetrical Smiley Face - Top to Bottom
  byte mySmile[] = {
    0b00111100, // Row 1 (Top) - Forehead
    0b01000010, // Row 2        - Sides
    0b10100101, // Row 3        - Eyes
    0b10000001, // Row 4        - Middle
    0b10100101, // Row 5        - Smile starts
    0b10011001, // Row 6        - Mouth curve
    0b01000010, // Row 7        - Chin sides
    0b00111100  // Row 8        - Bottom
  };

  for (int j = 0; j < 500; j++ ) { 
    int cols = 0x01;
    for (int i = 0; i < 8; i++) {
      // We send (~cols) because 0 is ON for your columns
      // We send smilingFace[i] for the rows
      writeTo74HC595s(MSBFIRST, ~cols, mySmile[i]);
      //writeTo74HC595s(MSBFIRST, 0x00, 0x01); //line on the top
      delay(1); 
      writeTo74HC595s(MSBFIRST, 0xFF, 0x00); // Clear (All columns HIGH, All rows LOW)
      cols <<= 1; 
    }
  }
}



void displaySmilingFaceUpsideDown() {

  // Define the pattern data for a smiling face
  const int smilingFace[] = {                       //"^ⅴ^"
    0x1C, 0x22, 0x51, 0x45, 0x45, 0x51, 0x22, 0x14
  };
  
  for (int j = 0; j < 500; j++ ) { 
    int cols = 0x01;
    for (int i = 0; i < 8; i++) {
      // We send (~cols) because 0 is ON for your columns
      // We send smilingFace[i] for the rows
      writeTo74HC595s(MSBFIRST, ~cols, smilingFace[i]); 
      delay(1); 
      writeTo74HC595s(MSBFIRST, 0xFF, 0x00); // Clear (All columns HIGH, All rows LOW)
      cols <<= 1; 
    }
  }
}

void displayXshape() {
  //Set DELAY_TIME 2
  // Row 1: Pins 1 and 8 (Col 1 & 8)
  writeTo74HC595s(MSBFIRST, 0x7E, 0x01); 
  // Row 2: Pins 2 and 7 (Col 2 & 7)
  writeTo74HC595s(MSBFIRST, 0xBD, 0x02); 
  // Row 3: Pins 3 and 6 (Col 3 & 6)
  writeTo74HC595s(MSBFIRST, 0xDB, 0x04); 
  // Row 4: Pins 4 and 5 (Col 4 & 5)
  writeTo74HC595s(MSBFIRST, 0xE7, 0x08); 
  // Row 5: Pins 4 and 5 (Col 4 & 5)
  writeTo74HC595s(MSBFIRST, 0xE7, 0x10); 
  // Row 6: Pins 3 and 6 (Col 3 & 6)
  writeTo74HC595s(MSBFIRST, 0xDB, 0x20); 
  // Row 7: Pins 2 and 7 (Col 2 & 7)
  writeTo74HC595s(MSBFIRST, 0xBD, 0x40); 
  // Row 8: Pins 1 and 8 (Col 1 & 8)
  writeTo74HC595s(MSBFIRST, 0x7E, 0x80); 
}


void displayAllLEDsOnRow1AndColumn1() {
  //Manage ROWs HERE
  // --- [TURN ON] COL 1, ROW 1---
  digitalWrite(PIN_LATCH, LOW);
  // First 8 bits go to IC2 (Columns)
  // 0xFE is 11111110 in binary (Only Q0 is LOW/Ground)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0xFE); 
  // Next 8 bits stay in IC1 (Rows)
  // 0x01 is 00000001 in binary (Only Q0 is HIGH/Power)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0x01); 
  digitalWrite(PIN_LATCH, HIGH);
  delay(DELAY_TIME); 
  
  // --- [TURN ON] COL 1, ROW 2---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x02);
  
  // --- [TURN ON] COL 1, ROW 3---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x04);

  // --- [TURN ON] COL 1, ROW 4---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x08);

  // --- [TURN ON] COL 1, ROW 5---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x10);

  // --- [TURN ON] COL 1, ROW 6---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x20);

  // --- [TURN ON] COL 1, ROW 7---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x40);

  // --- [TURN ON] COL 1, ROW 8---
  writeTo74HC595s(MSBFIRST, 0xFE, 0x80);

  // --- TURN OFF ---
  // All Columns inactive (HIGH) 0xFF
  // All Rows inactive (LOW)     0x00
  writeTo74HC595s(MSBFIRST, 0xFF, 0x00);

  //manage COLUMNs HERE
  // --- [TURN ON] COL 1, ROW 1---
  digitalWrite(PIN_LATCH, LOW);
  // First 8 bits go to IC2 (Columns)
  // 0xFE is 11111110 in binary (Only Q0 is LOW/Ground)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0xFE); 
  // Next 8 bits stay in IC1 (Rows)
  // 0x01 is 00000001 in binary (Only Q0 is HIGH/Power)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0x01); 
  digitalWrite(PIN_LATCH, HIGH);
  delay(DELAY_TIME); 

  // --- [TURN ON] COL 2, ROW 1---
  // First 8 bits go to IC2 (Columns)
  // 0xFD is 11111101 in binary (Only Q1 is LOW/Ground)
  // Next 8 bits stay in IC1 (Rows)
  // 0x01 is 00000001 in binary (Only Q0 is HIGH/Power)
  writeTo74HC595s(MSBFIRST, 0xFD, 0x01);

  // --- [TURN ON] COL 3, ROW 1---
  writeTo74HC595s(MSBFIRST, 0xFB, 0x01);

  // --- [TURN ON] COL 4, ROW 1---
  writeTo74HC595s(MSBFIRST, 0xF7, 0x01);

  // --- [TURN ON] COL 5, ROW 1---
  writeTo74HC595s(MSBFIRST, 0xEF, 0x01);

  // --- [TURN ON] COL 6, ROW 1---
  writeTo74HC595s(MSBFIRST, 0xDF, 0x01);

  // --- [TURN ON] COL 7, ROW 1---
  writeTo74HC595s(MSBFIRST, 0xBF, 0x01);

  // --- [TURN ON] COL 8, ROW 1---
  writeTo74HC595s(MSBFIRST, 0x7F, 0x01);

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
