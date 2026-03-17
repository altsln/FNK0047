/**********************************************************************
* Filename    : 022-01_matrix_keypad_LCD_buzzer_servo
* Description : Using Matrix Keypad to display message on LCD, and
* activate a servo motor and then an active buzzer for a couple
* of milliseconds.
* Auther      : Alternatives Solutions
* Modification: 2026/03/16
**********************************************************************/

//Open Arduino IDE -> Library Manager.
//Search for "Keypad".
//Install the one by Mark Stanley & Alexander Brevig.

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>    // The New Library

//Buzzer Pin
const int BUZZER_PIN = 23;

//KeyPad Pins and config
const byte ROWS = 4;  //four Rows
const byte COLS = 4;  //four Columns
//pins
byte rowsPins[ROWS] = {21, 19, 18, 5}; // Row 4, 3, 2, 1
byte colsPins[COLS] = {26, 27, 14, 12};  // Col 4, 3, 2, 1 
//symbols on the button of the keypad
const char Keys[ROWS][COLS] {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// I2C Pin
const int SDA_PIN = 15;
const int SCL_PIN = 13;

// LCD param - Start with 0x27, we will change it if needed
int lcdAddr = 0x27;
const int LCD_COL = 16;
const int LCD_ROW = 2;

const int DELAY_TIME = 300;
const bool IS_DEBUG = true;

// We create pointer to LCD
LiquidCrystal_I2C* lcdPtr = nullptr;

// initialize keypad
Keypad pad = Keypad(makeKeymap(Keys), rowsPins, colsPins, ROWS, COLS);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin(SDA_PIN, SCL_PIN); //attach I2C pins
  // Check if 0x27 responds. If not, we assume 0x3F.
  // Note: Since we can't easily "re-map" the object address here,
  // it's best to verify your 0x27 address manually first.
  Wire.beginTransmission(lcdAddr);
  if (0 == Wire.endTransmission()) {
    Serial.println("LCD found at 0x27");
    lcdPtr = new LiquidCrystal_I2C(lcdAddr, LCD_COL, LCD_ROW);
  } else {
    Serial.println("LCD not found at 0x27, trying 0x3F logic...");
    lcdPtr = new LiquidCrystal_I2C(0x3F, LCD_COL, LCD_ROW);
  }
  lcdPtr->init();       //LCD driver initialisation
  lcdPtr->backlight();  //Open the backlight
  lcdPtr->setCursor(0,0);   //set the cursor et Row 0 and Column 0
  lcdPtr->print("MATRIX KEYPAD"); //print specified message on the LCD

  Serial.println("\nESP32 Wrover initialization completed!");
}

// the loop function runs over and over again forever
void loop() {
  char key = pad.getKey();

  //delay(DELAY_TIME);

  // Monitor the values
  if (key) {
    if (IS_DEBUG) {
      Serial.print("Key: ");
      Serial.println(key);
      //Serial.println("    ");
    }  
    
    // LCD Update
    if (lcdPtr != nullptr) {
      lcdPtr->setCursor(0, 1);
      lcdPtr->print("KEY: ");
      lcdPtr->print(key);
      lcdPtr->print("      "); // Still using that "Eraser Space"!
    }

    digitalWrite(BUZZER_PIN, HIGH);
    delay(DELAY_TIME);
    digitalWrite(BUZZER_PIN, LOW);
    

  }
  
}
