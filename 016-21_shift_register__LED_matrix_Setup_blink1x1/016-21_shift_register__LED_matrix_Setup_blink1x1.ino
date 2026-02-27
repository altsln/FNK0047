/**********************************************************************
* Filename    : 016-21_shift_register__LED_matrix_Setup_blink1x1
* Description : Setup shift register component (74HC595) and a
* LED matrix component to blink a LED.(r1 x c1)  
* Auther      : Alternatives Solutions
* Modification: 2026/02/26
**********************************************************************/

#define PIN_LATCH       13    //ESP32 pin 13 connected to 595 Latch(pin12)
#define PIN_DATA        12    //ESP32 pin 12 connected to 595 DS(pin14)
#define PIN_CLOCK       14    //ESP32 pin 14 connected to 595 Clock(pin11)

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
  // --- TURN ON ---
  digitalWrite(PIN_LATCH, LOW);
  // First 8 bits go to IC2 (Columns)
  // 0xFE is 11111110 in binary (Only Q0 is LOW/Ground)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0xFE); 
  // Next 8 bits stay in IC1 (Rows)
  // 0x01 is 00000001 in binary (Only Q0 is HIGH/Power)
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0x01); 
  digitalWrite(PIN_LATCH, HIGH);
  delay(DELAY_TIME); 

  // --- TURN OFF ---
  digitalWrite(PIN_LATCH, LOW);
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0xFF); // All Columns inactive (HIGH) 
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0x00); // All Rows inactive (LOW) 
  digitalWrite(PIN_LATCH, HIGH);
  delay(DELAY_TIME); 

}
