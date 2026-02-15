/**********************************************************************
* Filename    : 008-01_serial_read_write
* Description : Using serial communication (UART) to send 
* some data to PC, and show them on Serial Monitor  
* Auther      : Alternatives Solutions
* Modification: 2026/02/14
**********************************************************************/

String inputString = "";    // a string to hold incoming data
bool isCompleted = false;   // whether the string is complete



// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
  Serial.println("Please input some characters,");
  Serial.println("select \"newLine\" below and ctrl + Enter to send message to ESP32.");
  Serial.println("Ready to receive data...\n");
}

// the loop function runs over and over again forever
void loop() {
  if(Serial.available()) {
    inputString = Serial.readStringUntil('\n');

    // trim() removes leading and trailing whitespace characters, 
    // including \r, \n, tabs, etc.
    inputString.trim();

    if (!inputString.isEmpty()) {
      isCompleted = true;
    }

    if (isCompleted) {
      Serial.printf("InputString: %s, \r\n", inputString.c_str());
      inputString = "";
      isCompleted = false;
    }

  }

}
