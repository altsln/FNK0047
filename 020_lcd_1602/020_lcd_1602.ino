/**********************************************************************
* Filename    : 020_lcd_1602
* Description : Using I2C protocol to control the display
* characters of LCD 1602.
* Auther      : Alternatives Solutions
* Modification: 2026/03/10
**********************************************************************/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// I2C Pin
const int SDA_PIN = 15;
const int SCL_PIN = 13;

const int DELAY_TIME = 1000;
const bool IS_DEBUG = false;

// LCD param - Start with 0x27, we will change it if needed
int lcdAddr = 0x27;
const int LCD_COL = 16;
const int LCD_ROW = 2;

// We create the object once
LiquidCrystal_I2C lcd(lcdAddr, LCD_COL, LCD_ROW);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN); //attach I2C pins
  
  // Check if 0x27 responds. If not, we assume 0x3F.
  // Note: Since we can't easily "re-map" the object address here,
  // it's best to verify your 0x27 address manually first.
  if (!i2CAddrTest(lcdAddr)) {
    Serial.println("LCD not found at 0x27, trying 0x3F logic...");
    // If you REALLY want auto-addressing, you'd need a pointer,
    // but for now, let's stick to the address we know works (0x27).
    
    //ldc = LiquidCrystal_I2C(0x3F, LDC_COL, LDC_ROW);
  }
  lcd.init();       //LCD driver initialisation
  lcd.backlight();  //Open the backlight
  lcd.setCursor(0,0);   //set the cursor et Row 0 and Column 0
  lcd.print("Hello, World!"); //print specified message on the LCD


  Serial.println("\nESP32 Wrover initialization completed!");
}

// the loop function runs over and over again forever
void loop() {
  //
  lcd.setCursor(9, 1); // Move cursor right after "Counter: "
  lcd.print(millis() / 1000);
  
  // Note: We don't need to re-print "Counter: " every loop
  // unless we clear the screen. 
  if(millis() % 5000 < 1000) { // Just a little trick to show it's alive
     lcd.setCursor(0,1);
     lcd.print("Counter: ");
  }
  delay(DELAY_TIME);

}


bool i2CAddrTest(uint8_t addr) {
  Wire.beginTransmission(addr);
  return (0 == Wire.endTransmission());
}


/*
#include <Wire.h>

void setup() {
  Wire.begin(15, 13);
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  if (nDevices == 0) Serial.println("No I2C devices found\n");
  delay(5000);
}

*/

/*
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 based on your scanner result
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // IMPORTANT: Tell the ESP32 to use your specific pins for I2C
  Wire.begin(15, 13); 
  
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight
  lcd.backlight();
  
  // Print your success message!
  lcd.setCursor(0, 0); 
  lcd.print("I2C Found: 0x27");
  
  lcd.setCursor(0, 1);
  lcd.print("Pins: 15 & 13");
}

void loop() {
  // The screen stays static
}
*/

/*
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int counter = 0;

void setup() {
  Wire.begin(15, 13); 
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("System Active!");
}

void loop() {
  lcd.setCursor(0, 1); // Move to the second line
  lcd.print("Count: ");
  lcd.print(counter);
  
  // Important: Add spaces at the end to "clear" old digits
  // Otherwise, when 10 becomes 9, you might see "90"
  lcd.print("     "); 

  counter++;
  delay(500); 
}
*/
