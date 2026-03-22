/**********************************************************************
* Filename    : 023_infrared_remote_setup
* Description : Setup infrared remote control to decode and
* print out the value through the serial port.
* Auther      : Alternatives Solutions
* Modification: 2026/03/22
**********************************************************************/

#include "Freenove_IR_Lib_for_ESP32.h"

// --- Configuration ---
const int IR_PIN = 4;   //IR receiving pin

Freenove_ESP32_IR_Recv ir_recv(IR_PIN);

void setup() {
  Serial.begin(115200);  
  Serial.print("System Ready and waiting for IR message on PIN: ");
  Serial.println(IR_PIN);
}

void loop() {
  ir_recv.task();
  if (ir_recv.nec_available()) {
    Serial.printf("IR Code %#x\r\n", ir_recv.data());
  }
}
