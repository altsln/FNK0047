/**********************************************************************
* Filename    : 002-01_button_leds
* Description : Make builtin and external leds to alternate, 
* when pressing on the button (default builtin is ON, and 
* external is OFF)
* Auther      : Alternative Solutions
* Modification: 2026/02/04
**********************************************************************/
#define LED_BUILTIN  2
#define LED_XTERNAL  4
#define PIN_BUTTON   13
//#define DELAY_TIME   1000

int val = 0;  

/******** BEFORE DOING THIS EXCERCISE FIRST DO 002_button_led ********/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN and LED_XTERNAL as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_XTERNAL, OUTPUT);
  // initialize digital pin PIN_BUTTON as an input.
  pinMode(PIN_BUTTON, INPUT);

  //Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {

  //logic without if statement
  val = digitalRead(PIN_BUTTON);
  digitalWrite(LED_XTERNAL, val);
  val = (val + 1) % 2;
  digitalWrite(LED_BUILTIN, val);


  /*delay(200);
  Serial.println("val");
  Serial.println(val);*/

/*
  //same logic bu using if statement
  if (HIGH == digitalRead(PIN_BUTTON)) {  //K (The button) is not pressed
    digitalWrite(LED_BUILTIN, LOW);       //Led is turned ON on LOW signal
    digitalWrite(LED_XTERNAL, HIGH);
  } else {                                //K is pressed, ==>> short circuit
    digitalWrite(LED_BUILTIN, HIGH);      //Led is turned OFF on HIGH signal
    digitalWrite(LED_XTERNAL, LOW);
  }
*/
}

