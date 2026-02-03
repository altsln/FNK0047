/**********************************************************************
* Filename    : 001_01-xternal_led
* Description : Make builtin and external leds to blink, 
* sync and alternate using functions
* Auther      : Alternative Solutions
* Modification: 2026/02/02
**********************************************************************/
#define LED_EXT_4  4
#define LED_BUILTIN  2
//#define LED_2  2
#define DELAY_TIME   1000

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_EXT_4, OUTPUT);
  
  digitalWrite(LED_BUILTIN, HIGH);      // turn the LED off by making the voltage LOW
  digitalWrite(LED_EXT_4, LOW);         // turn the LED off (HIGH is the voltage level)
}

// the loop function runs over and over again forever
void loop() {
  syncBlinking();
  syncBlinking();
  syncBlinking();
  syncBlinking();
  syncBlinking();
  
  digitalWrite(LED_EXT_4, LOW);     // turn the LED off (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off by making the voltage HIGH
  delay(3 * DELAY_TIME);            // wait for a Defined delay time

  syncBlinkingWorkaround();
  syncBlinkingWorkaround();
  syncBlinkingWorkaround();
  syncBlinkingWorkaround();
  syncBlinkingWorkaround();
  
  digitalWrite(LED_EXT_4, LOW);     // turn the LED off (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off by making the voltage HIGH
  delay(3 * DELAY_TIME);            // wait for a Defined delay time
}

void syncBlinking() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off (HIGH is the voltage level)
  digitalWrite(LED_EXT_4, HIGH);    // turn the LED on (HIGH is the voltage level)
  delay(DELAY_TIME);                // wait for a Defined delay time
  digitalWrite(LED_EXT_4, LOW);     // turn the LED off (LOW is the voltage level)
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on by making the voltage LOW
  delay(DELAY_TIME);                // wait for a Defined delay time
}

void syncBlinkingWorkaround() {
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off (HIGH is the voltage level)
  digitalWrite(LED_EXT_4, LOW);       // turn the LED off (LOW is the voltage level)
  delay(DELAY_TIME);                  // wait for a Defined delay time
  digitalWrite(LED_BUILTIN, LOW);     // turn the LED on by making the voltage LOW
  digitalWrite(LED_EXT_4, HIGH);      // turn the LED off (HIGH is the voltage level)
  delay(DELAY_TIME);                  // wait for a Defined delay time
}
