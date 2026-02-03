/**********************************************************************
* Filename    : 001_xternal_led
* Description : Make builtin and external leds to blink.
* Auther      : Alternative Solutions
* Modification: 2026/02/02
**********************************************************************/
#define LED_EXT_4  4
//#define LED_BUILTIN  2
#define LED_2  2
#define DELAY_TIME   1000

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_2, OUTPUT);
  pinMode(LED_EXT_4, OUTPUT);
  
  digitalWrite(LED_2, LOW);    // turn the LED on by making the voltage LOW
  digitalWrite(LED_EXT_4, LOW);   // turn the LED off (HIGH is the voltage level)
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_2, HIGH);   // turn the LED off (HIGH is the voltage level)
  digitalWrite(LED_EXT_4, LOW);   // turn the LED off (HIGH is the voltage level)
  delay(DELAY_TIME);                       // wait for a Defined delay time
  digitalWrite(LED_2, LOW);    // turn the LED on by making the voltage LOW
  digitalWrite(LED_EXT_4, HIGH);   // turn the LED off (HIGH is the voltage level)
  delay(DELAY_TIME);                       // wait for a Defined delay time
}

/*
The loop code above is actually the one from alternating between the 2 LEDs. 
But for now it the work around for making it working by blinking at the same time 

*/



