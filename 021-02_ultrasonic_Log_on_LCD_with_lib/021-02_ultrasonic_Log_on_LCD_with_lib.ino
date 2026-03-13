/**********************************************************************
* Filename    : 021-02_ultrasonic_Log_on_LCD_with_lib
* Description : Using HC-SRO4 to control the ranging and display log
* on LCD 1602 component. "HC-SR04 is an Utrasonic component".
* Auther      : Alternatives Solutions
* Modification: 2026/03/13
**********************************************************************/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <UltrasonicSensor.h>

// I2C Pin
const int SDA_PIN = 15;
const int SCL_PIN = 13;
//HC-SR04 PIN
const int TRIG_PIN = 4;
const int ECHO_PIN = 5;

// LCD param - Start with 0x27, we will change it if needed
int lcdAddr = 0x27;
const int LCD_COL = 16;
const int LCD_ROW = 2;

const int DELAY_TIME = 300;
const bool IS_DEBUG = false;

// We create pointer to LCD
LiquidCrystal_I2C* lcdPtr = nullptr;

UltrasonicSensor ulSensor(TRIG_PIN, ECHO_PIN);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN); //attach I2C pins
  // Check if 0x27 responds. If not, we assume 0x3F.
  // Note: Since we can't easily "re-map" the object address here,
  // it's best to verify your 0x27 address manually first.
  if (i2CAddrTest(lcdAddr)) {
    Serial.println("LCD found at 0x27");
    lcdPtr = new LiquidCrystal_I2C(lcdAddr, LCD_COL, LCD_ROW);
  } else {
    Serial.println("LCD not found at 0x27, trying 0x3F logic...");
    // If you REALLY want auto-addressing, you'd need a pointer,
    // but for now, let's stick to the address we know works (0x27).
    
    lcdPtr = new LiquidCrystal_I2C(0x3F, LCD_COL, LCD_ROW);
  }

  lcdPtr->init();       //LCD driver initialisation
  lcdPtr->backlight();  //Open the backlight
  lcdPtr->setCursor(0,0);   //set the cursor et Row 0 and Column 0
  lcdPtr->print("Hello, World!"); //print specified message on the LCD

  Serial.println("\nESP32 Wrover initialization completed!");

  ulSensor.setTemperature(22);
  // Clean the TRIG_PIN
//  digitalWrite(TRIG_PIN, LOW);
}

// the loop function runs over and over again forever
void loop() {
  int distanceCm = ulSensor.distanceInCentimeters();

  delay(DELAY_TIME);

  // Monitor the values
  if (0 == distanceCm) {
    Serial.println("No pulse received. Check if VCC is in the 5V pin!");
  } else {
    if (IS_DEBUG) {
      Serial.print("Distance: ");
      Serial.print(distanceCm);
      Serial.println(" cm");
  //    delay(DELAY_TIME);
    }  
    //
    lcdPtr->setCursor(10, 1); // Move cursor right after "Counter: "
    lcdPtr->print(distanceCm);
    lcdPtr->print("    ");    // The "Eraser" spaces

    // Note: We don't need to re-print "Counter: " every loop
    // unless we clear the screen. 
    if(millis() % 1000 < 1000) { // Just a little trick to show it's alive
      lcdPtr->setCursor(0,1);
      lcdPtr->print("Distance: ");
    }
  }
  // 
  delay(DELAY_TIME);
}

bool i2CAddrTest(uint8_t addr) {
  Wire.beginTransmission(addr);
  return (0 == Wire.endTransmission());
}
