/**********************************************************************
* Filename    : 022-03_keypad_door__keypad_LCD_buzzer_servo
* Description : Using Matrix Keypad, LCD, Buzzer and servo
* to build a keypad door.
* Auther      : Alternatives Solutions
* Modification: 2026/03/18
**********************************************************************/

//Open Arduino IDE -> Library Manager.
//Search for "Keypad".
//Install the one by Mark Stanley & Alexander Brevig.
//Search for "ESP32Servo".
//Install the one by Kevin Harrington, John K. Bennett.


#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>    // The New Library
#include <ESP32Servo.h>   // The New Library

//Servo Motor Pin
const int SERVO_PIN = 22;

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

//Servo object to control a servo
Servo servObj; 

const char padLock[] = {"*1A0#"}; //current pwd
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  setupServo();

  pinMode(BUZZER_PIN, OUTPUT);
  setupLCD();

  Serial.println("\nESP32 Wrover initialization completed!");
}

void setupServo() {
  servObj.setPeriodHertz(50); // standard 50 hz servo
  // set the high level time range of the servo motor for an accurate 0 to 180 sweep
  servObj.attach(SERVO_PIN, 500, 2500); // attaches the servoPin to the servo object
  servObj.write(0);   // Set the starting position of the servo motor
}

void setupLCD() {
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
  lcdPtr->print("PASSWORD PLEASE:"); //print specified message on the LCD
}

// the loop function runs over and over again forever
void loop() {
  static char usrPwd[6];
  memset(usrPwd, 0, 6);
  //Get password
  getPassword(usrPwd, 5);
  
  if (IS_DEBUG) {
    Serial.print("pwd: ");
    Serial.println(usrPwd);
    //Serial.println("    ");
  }

  if (checkPassword(usrPwd)) {
    grantAccess();

    //return the servo to position 0
    delay(4 * DELAY_TIME);
    servObj.write(0);
    clearLCD2ndLine();
  } else {
    denyAccess();
  }
}

void getPassword(char* pwdWord, int pwdSize) {
  //
  if ((nullptr == pwdWord) || (nullptr == lcdPtr)) {
    return;
  }
  
  for (int i = 0; i < pwdSize; i++) {
    char key = pad.waitForKey();
    lcdPtr->setCursor(i, 1);
//    lcdPtr->print(key);
    lcdPtr->print("*"); //hide the password
    lcdPtr->print("           "); // Still using that "Eraser Space"!
    //save input character
    pwdWord[i] = key;
    //set buzzer tone 
    digitalWrite(BUZZER_PIN, HIGH);
    delay(DELAY_TIME);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

bool checkPassword(char* pwd) {
  //compare 2 strings 
  if (0 == strncmp(pwd, padLock, 5)) {
    return true;
  }
  return false;
}

void grantAccess() {
  // LCD Update
  if (lcdPtr != nullptr) {
    lcdPtr->setCursor(0, 1);
    lcdPtr->print("ACCESS GRANTED");
    lcdPtr->print("      "); // Still using that "Eraser Space"!
  }
  //set buzzer tone 
  digitalWrite(BUZZER_PIN, HIGH);
  delay(DELAY_TIME);
  digitalWrite(BUZZER_PIN, LOW);

  servObj.write(45);
  delay(DELAY_TIME);

}

void denyAccess() {
  // LCD Update
  if (lcdPtr != nullptr) {
    lcdPtr->setCursor(0, 1);
    lcdPtr->print("ACCESS DENIED");
    lcdPtr->print("      "); // Still using that "Eraser Space"!
  }
  //set buzzer tone 
  digitalWrite(BUZZER_PIN, HIGH);
  delay(4 * DELAY_TIME);
  digitalWrite(BUZZER_PIN, LOW);

  clearLCD2ndLine();
}

void clearLCD2ndLine() {
  if (lcdPtr != nullptr) {
    lcdPtr->clear();
    lcdPtr->setCursor(0,0);
    lcdPtr->print("PASSWORD PLEASE:");
  }
}