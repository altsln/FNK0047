/**********************************************************************
* Filename    : 023-03_infrared_remote_LED_control__step-wise
* Description : Using infrared remote control to decode and
* control the brightness of an LED, by using only '+' and '-'
* to update the brightness of the LED.
* Auther      : Alternatives Solutions
* Modification: 2026/03/23
**********************************************************************/

#include "Freenove_IR_Lib_for_ESP32.h"

// --- Configuration ---
const int IR_PIN = 4;   //IR receiving pin
const int LED_PIN = 5;
const int BUZ_PIN = 27;

const int B_STEP = 25;  //Brightness step to change per click

// --- Code of Command to handle ---
const unsigned long IR_CODE_PLUS = 0xFF02FD;
const unsigned long IR_CODE_MINUS = 0xFF9867;
const unsigned long IR_CODE_OFF = 0xFFA25D;
const unsigned long IR_REPEAT = 0xFFFFFFFF;

Freenove_ESP32_IR_Recv ir_recv(IR_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(BUZ_PIN, OUTPUT);
  //pin(LED_PIN), Freq(1000), Resolution(8bits), channel(2)
  ledcAttachChannel(LED_PIN, 1000, 8, 2);  
  Serial.print("System Ready and waiting for IR message on PIN: ");
  Serial.println(IR_PIN);
}

void loop() {
  static int currentBrightness = 0;   
  ir_recv.task();
  if (ir_recv.nec_available()) {
    handleControl(ir_recv.data(), currentBrightness);
  }
}

void triggerBuzzer(int delayTime) {
  digitalWrite(BUZ_PIN, HIGH);
  delay(delayTime); // Shorter beep feels more responsive like 50
  digitalWrite(BUZ_PIN, LOW);
}

void handleControl(unsigned long val, int& currentBright) {
  // Ignore the repeat code so the buzzer doesn't go crazy
  if (val == IR_REPEAT) return;

  // Make a sound only when a NEW valid command is received
  triggerBuzzer(50);
  
  switch(val) {
    case IR_CODE_PLUS:    //'+' is pressed
      currentBright += B_STEP;
      if (currentBright > 255) {
        currentBright = 255;
      }
      break;
    case IR_CODE_MINUS:    //'-' is pressed
      currentBright -= B_STEP;
      if (currentBright < 0) {
        currentBright = 0;
      }
      break;
    case IR_CODE_OFF:    //OFF is pressed (emergency OFF)
      currentBright = 0;
      break;
    default:          //any other character is pressed
      //no operation just log
      Serial.print("Unknown Code: ");
      Serial.println(val, HEX);
      break;
  }

  ledcWrite(LED_PIN, currentBright);
  Serial.print("New Brightness: ");
  Serial.println(currentBright);
}
