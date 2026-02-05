/**********************************************************************
* Filename    : 002_03_button_leds_mini_lamp
* Description : Make builtin and external leds to work as, 
* a mini lamp (default builtin and external Leds are OFF,
* and button is working as ON and OFF) toogle button
* Auther      : Alternative Solutions
* Modification: 2026/02/04
**********************************************************************/
#define LED_BUILTIN  2
#define LED_XTERNAL  4
#define PIN_BUTTON   13
#define DELAY_TIME   20

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

  //same logic bu using if statement
  if (HIGH == digitalRead(PIN_BUTTON)) {  //K (The button) is not pressed
    // (No operation)
  } else {                                //K is pressed, ==>> short circuit
    // first bounce
    delay(DELAY_TIME);
    if (LOW == digitalRead(PIN_BUTTON)) {
      reverseGPIO(LED_BUILTIN);
      reverseGPIO(LED_XTERNAL);
    }

    //block here until the button is release
    while(LOW == digitalRead(PIN_BUTTON));
    delay(DELAY_TIME);
  }
}

void reverseGPIO(uint8_t pin) {
  digitalWrite(pin, !digitalRead(pin));
}