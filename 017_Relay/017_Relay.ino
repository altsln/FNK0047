/**********************************************************************
* Filename    : 017_Relay
* Description : Setup relay "HK4100F-DC 5V-SHG" component and
* make the LED blink. 
* Auther      : Alternatives Solutions
* Modification: 2026/03/02
**********************************************************************/

#define PIN_RELAY       13

#define DELAY_TIME      1000
#define DEBUG           false

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_RELAY, OUTPUT);

  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PIN_RELAY, HIGH); // Transistor "Opens" the gate
  delay(DELAY_TIME); 
  digitalWrite(PIN_RELAY, LOW);  // Transistor "Closes" the gate
  delay(DELAY_TIME);
}
