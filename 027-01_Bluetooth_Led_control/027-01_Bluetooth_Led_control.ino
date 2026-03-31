/**********************************************************************
* Filename    : 027-01_Bluetooth_Led_control
* Description : Controlling an LED over BT between ESP32 and
* the mobile phone.
* Auther      : Alternatives Solutions
* Modification: 2026/03/30
**********************************************************************/
#include <BluetoothSerial.h>

const int BUILTIN_LED = 2;
BluetoothSerial serialBT;

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);  //to force the LED OFF
  serialBT.begin("ESP32_BT_LED_Control");
  Serial.println("System Ready! Send '1' to ON, '0' to OFF.");
}

void loop() {
/* is this really needed?

  //From Computer to phone
  if (Serial.available()) {
    serialBT.write(Serial.read());
  }*/

  //From phone to ESP32
  if (serialBT.available()) {
    char cmd = serialBT.read(); //read the incoming character
    Serial.print("Received: ");
    Serial.println(cmd);

    if ('1' == cmd) {
      digitalWrite(BUILTIN_LED, LOW);
      serialBT.println("LED is ON");
    } else if ('0' == cmd) {
      digitalWrite(BUILTIN_LED, HIGH);
      serialBT.println("LED is OFF");
    } else {
      if (('\n' == cmd) || ('\r' == cmd)) {
        //ignore it
      } else {
        serialBT.println("Wrong Command \nPlease Send '1' to ON, '0' to OFF.");
      }
    }
  }
  delay(20);
}
/*
Is the "Computer to Phone" block needed?
// is this really needed? 

Mechanically? No. 
  The ESP32 doesn't need it to control the LED.
For Debugging? Yes. 
  As an embedded developer, keeping that block allows you to 
  "talk back" to your phone from your PC.
  For example, if you wanted to manually type a secret message 
  in the Arduino Serial Monitor and have it pop up on your phone, 
  you'd need that code. 
  
  If you only care about the phone controlling the ESP32, 
  you can leave it commented out.
*/
