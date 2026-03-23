/**********************************************************************
* Filename    : 023-01_infrared_remote_LED_control
* Description : Using infrared remote control to decode and
* control the brightness of an LED.
* Auther      : Alternatives Solutions
* Modification: 2026/03/22
**********************************************************************/

#include "Freenove_IR_Lib_for_ESP32.h"

// --- Configuration ---
const int IR_PIN = 4;   //IR receiving pin
const int LED_PIN = 5;
const int BUZ_PIN = 27;

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
  //make a sound when receiving a command
  digitalWrite(BUZ_PIN, HIGH);
  delay(100);
  digitalWrite(BUZ_PIN, LOW);
  
  switch(val) {
    case 0xFF6897:    //0 is pressed
      ledcWrite(LED_PIN, 0);  //Turn OFF LED
      break;
    case 0xFF30CF:    //1 is pressed
      ledcWrite(LED_PIN, 7);  //Turn ON LED to dimmest brightness
      break;
    case 0xFF18E7:    //2 is pressed
      ledcWrite(LED_PIN, 63);  //Turn ON LED to medium brightness
      break;
    case 0xFF7a85:    //3 is pressed
      ledcWrite(LED_PIN, 255);  //Turn ON LED to full brightness
      break;
    default:          //any other character is pressed
      //no operation just log
      break;
  }
}
