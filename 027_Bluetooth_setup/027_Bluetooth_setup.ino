/**********************************************************************
* Filename    : 027_Bluetooth_setup
* Description : Setting up the BT communication between ESP32 and
* the mobile phone.
* Auther      : Alternatives Solutions
* Modification: 2026/03/29
**********************************************************************/
#include <BluetoothSerial.h>

BluetoothSerial serialBT;
//String buffer;

void setup() {
  Serial.begin(115200);
  serialBT.begin("ESP32_BT_Test");
  Serial.println("System Ready!");
}

void loop() {
  if (Serial.available()) {
    serialBT.write(Serial.read());
  }
  if (serialBT.available()) {
    Serial.write(serialBT.read());
  }
  delay(20);
}
