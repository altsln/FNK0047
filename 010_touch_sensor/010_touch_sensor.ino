/**********************************************************************
* Filename    : 010_touch_sensor
* Description : Read touch sensor value.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/15
**********************************************************************/

#define DELAY_TIME    1000

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  //get value using T2 (GPIO2) //not working...Trying T8
//  Serial.printf("Touch value: %d \n", touchRead(T2));
  Serial.printf("Touch value: %d \n", touchRead(T8));
  delay(DELAY_TIME);
}
