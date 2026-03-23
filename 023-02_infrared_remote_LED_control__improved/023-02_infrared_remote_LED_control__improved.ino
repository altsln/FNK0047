/**********************************************************************
* Filename    : 023-02_infrared_remote_LED_control__improved
* Description : Using infrared remote control to decode and
* control the brightness of an LED, avoiding along the way
* the long press from the remote when sending a command.
* Auther      : Alternatives Solutions
* Modification: 2026/03/23
**********************************************************************/

#include "Freenove_IR_Lib_for_ESP32.h"

// --- Configuration ---
const int IR_PIN = 4;   //IR receiving pin
const int LED_PIN = 5;
const int BUZ_PIN = 27;

// --- Code of Command to handle ---
const unsigned long IR_CODE_0 = 0xFF6897;
const unsigned long IR_CODE_1 = 0xFF30CF;
const unsigned long IR_CODE_2 = 0xFF18E7;
const unsigned long IR_CODE_3 = 0xFF7A85;
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
  ir_recv.task();
  if (ir_recv.nec_available()) {
    handleControl(ir_recv.data());
  }
}

void handleControl(unsigned long val) {
  // Ignore the repeat code so the buzzer doesn't go crazy
  if (val == IR_REPEAT) return;

  // Make a sound only when a NEW valid command is received
  digitalWrite(BUZ_PIN, HIGH);
  delay(50); // Shorter beep feels more responsive
  digitalWrite(BUZ_PIN, LOW);
  
  switch(val) {
    case IR_CODE_0:    //0 is pressed
      ledcWrite(LED_PIN, 0);  //Turn OFF LED
      Serial.println("LED: OFF");
      break;
    case IR_CODE_1:    //1 is pressed
      ledcWrite(LED_PIN, 7);  //Turn ON LED to dimmest brightness
      Serial.println("LED: 3%");
      break;
    case IR_CODE_2:    //2 is pressed
      ledcWrite(LED_PIN, 63);  //Turn ON LED to medium brightness
      Serial.println("LED: 25%");
      break;
    case IR_CODE_3:    //3 is pressed
      ledcWrite(LED_PIN, 255);  //Turn ON LED to full brightness
      Serial.println("LED: 100%");
      break;
    default:          //any other character is pressed
      //no operation just log
      Serial.print("Unknown Code: ");
      Serial.println(val, HEX);
      break;
  }
}
