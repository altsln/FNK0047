/**********************************************************************
* Filename    : 002-01_button_leds
* Description : Make builtin and external leds to be OFF, 
* when pressing on the button (default LEDs are ON)
* Auther      : Alternative Solutions
* Modification: 2026/02/02
**********************************************************************/
#define LED_BUILTIN  2
#define PIN_BUTTON   13
//#define DELAY_TIME   1000

int val = 0;  

/******** BEFORE DOING THIS EXCERCISE FIRST DO 002_button_led ********/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize digital pin PIN_BUTTON as an input.
  pinMode(PIN_BUTTON, INPUT);

  //Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
/*
  //logic without if statement
  val = digitalRead(PIN_BUTTON);
  val = (val + 1) % 2;
  digitalWrite(LED_BUILTIN, val);
*/

  /*delay(200);
  Serial.println("val");
  Serial.println(val);*/

  //same logic bu using if statement
  if (HIGH == digitalRead(PIN_BUTTON)) {  //K (The button) is not pressed
    digitalWrite(LED_BUILTIN, LOW);       //Led is turned ON on LOW signal
  } else {                                //K is pressed, ==>> short circuit
    digitalWrite(LED_BUILTIN, HIGH);      //Led is turned OFF on HIGH signal
  }

}

