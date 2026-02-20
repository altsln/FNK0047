/**********************************************************************
* Filename    : 013_thermistor
* Description : Read value from Joystick.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/20
**********************************************************************/
#define INPUT_PIN_X       36//13
#define INPUT_PIN_Y       35//12
#define INPUT_PIN_Z       33//14
#define DELAY_TIME        500

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(INPUT_PIN_Z, INPUT_PULLUP);   //z axis is a button.
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  int x_value = analogRead(INPUT_PIN_X);
  int y_value = analogRead(INPUT_PIN_Y);
  int z_value = digitalRead(INPUT_PIN_Z);

  Serial.printf("X val: %d, - Y val: %d, - Z val: %d\n",
    x_value, y_value, z_value);
  delay(DELAY_TIME);
}
