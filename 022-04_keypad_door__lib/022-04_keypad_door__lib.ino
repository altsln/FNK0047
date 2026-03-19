/**********************************************************************
* Filename    : 022-04_keypad_door__lib
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
#include <Keypad.h>
#include <ESP32Servo.h>

// --- Configuration ---
const int SERVO_PIN = 22;
const int BUZZER_PIN = 23;
const int SDA_PIN = 15;
const int SCL_PIN = 13;

const int PWD_LEN = 5;  // Length of "*1A0#"
const int SERVO_LOCKED = 0;
const int SERVO_UNLOCKED = 90; // Changed to 90 for a full quarter turn
const int BUZZ_SHORT = 100;
const int BUZZ_LONG = 800;

// --- Keypad Setup ---
const byte ROWS = 4;
const byte COLS = 4;
byte rowsPins[ROWS] = {21, 19, 18, 5}; 
byte colsPins[COLS] = {26, 27, 14, 12}; 

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad pad = Keypad(makeKeymap(keys), rowsPins, colsPins, ROWS, COLS);
LiquidCrystal_I2C* lcdPtr = nullptr;
Servo servObj;

const char MASTER_PWD[] = "*1A0#";

void setup() {
  Serial.begin(115200);
  
  pinMode(BUZZER_PIN, OUTPUT);
  setupServo();
  setupLCD();

  Serial.println("System Ready.");
}

void loop() {
  char usrPwd[PWD_LEN + 1]; // +1 for the null terminator \0
  memset(usrPwd, 0, sizeof(usrPwd));

  promptPassword();
  captureInput(usrPwd, PWD_LEN);
  
  if (checkAccess(usrPwd)) {
    handleSuccess();
  } else {
    handleFailure();
  }
}

// --- Logic Functions ---

void captureInput(char* buffer, int length) {
  for (int i = 0; i < length; i++) {
    char key = pad.waitForKey();
    buffer[i] = key;
    
    // UI Feedback
    lcdPtr->setCursor(i, 1);
    lcdPtr->print('*');
    triggerBuzzer(BUZZ_SHORT);
  }
  buffer[length] = '\0'; // Manually ensure null termination
}

bool checkAccess(char* input) {
  return (strncmp(input, MASTER_PWD, PWD_LEN) == 0);
}

void handleSuccess() {
  lcdPtr->setCursor(0, 1);
  lcdPtr->print("ACCESS GRANTED  ");
  servObj.write(SERVO_UNLOCKED);
  triggerBuzzer(BUZZ_SHORT);
  delay(200);
  triggerBuzzer(BUZZ_SHORT); // Double beep for success
  
  delay(3000); // Keep door open
  servObj.write(SERVO_LOCKED);
}

void handleFailure() {
  lcdPtr->setCursor(0, 1);
  lcdPtr->print("ACCESS DENIED   ");
  triggerBuzzer(BUZZ_LONG); // One long "error" beep
  delay(1000);
}

// --- Hardware Helpers ---

void triggerBuzzer(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}

void promptPassword() {
  if (lcdPtr) {
    lcdPtr->clear();
    lcdPtr->setCursor(0, 0);
    lcdPtr->print("ENTER PASSWORD:");
  }
}

void setupServo() {
  servObj.setPeriodHertz(50);
  servObj.attach(SERVO_PIN, 500, 2500);
  servObj.write(SERVO_LOCKED);
}

void setupLCD() {
  Wire.begin(SDA_PIN, SCL_PIN);
  lcdPtr = new LiquidCrystal_I2C(0x27, 16, 2);
  lcdPtr->init();
  lcdPtr->backlight();
}