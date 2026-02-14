/**********************************************************************
* Filename    : 008_serial_print
* Description : Using serial communication to display log messages
* and show them on the Serial Monitor  
* Auther      : Alternatives Solutions
* Modification: 2026/02/14
**********************************************************************/

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Wrover initialization completed!");
}

// the loop function runs over and over again forever
void loop() {
  Serial.printf("Running time: %.1f s\n", millis() / 1000.0f);
  delay(1000);
}
