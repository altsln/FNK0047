/**********************************************************************
* Filename    : 002_button_led
* Description : Make builtin and external leds to turn ON,
* based on the action on a button
* Auther      : Alternative Solutions
* Modification: 2026/02/03-04
**********************************************************************/
#define LED_BUILTIN  2
#define PIN_BUTTON   13
//#define DELAY_TIME   1000

int val = 0;  
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
  digitalWrite(LED_BUILTIN, val);
*/

  /*delay(200);
  Serial.println("val");
  Serial.println(val);*/

  //same logic bu using if statement
  if (HIGH == digitalRead(PIN_BUTTON)) {  //K (The button) is not pressed
    digitalWrite(LED_BUILTIN, HIGH);      //Led is turned OFF on HIGH signal
  } else {                                //K is pressed, ==>> short circuit
    digitalWrite(LED_BUILTIN, LOW);       //Led is turned ON on LOW signal
  }


}

/*
circuit to understand
 |------K--------+--10K Resistor------|
 |               |                    |
 |           10K Resistor             V
 |               |                    |
 GND           IO 13

Lets break it down
Step one (make things simple)


      +--10K Resistor------|
      |                    |
      |                    V
      |                    |
     GND                  GND

from this we can write Ohm law U = RI

Step 2 (add one more component)

      +--10K Resistor------|
      |                    |
  10K Resistor             V
      |                    |
    IO 13                 GND

Up to here things look ok. The intensity of 
the current flowing from V the source has 
decreased.
i13 is very small

Step 3 (short circuit ?) 
 |---------------+--10K Resistor------|
 |               |                    |
 |           10K Resistor             V
 |               |                    |
 GND           IO 13                 GND

At this step there is no current flowing to IO 13,
because of the 10K resistor.
One of the basic law of electricity is that the current
will avoid the path with reisistor like we guys avoid 
path with traffic when on the road 
Here i13 = 0;

Step 4 (add the last component the button)

 |------K--------+--10K Resistor------|
 |               |                    |
 |           10K Resistor             V
 |               |                    |
 GND           IO 13                 GND

K here is a button.
When K is not pressed the current is not flowing
there. The whole circuit is like the one in the step 2
there is a current which is very small and this is
what we want and we would like to protect the board.
so i13 is not null but it is very small. so because 
there is a current the read state will return HIGH.

But when K is pressed the current will avoid the 
resistor like human avoiding traffic on the road.
Because of the resistor, all the current will flow 
through K and i13 = 0, then, the read state will LOW. 

This explain the value we can read in the serial monitor 

The value read on IO13 (PIN_BUTTON) will be store in val
it value will be either 0 or 1. 
  val = digitalRead(PIN_BUTTON);

Then the value will be written to the LED so that it 
will light up the LED or not. 
  digitalWrite(LED_BUILTIN, val);

This can also be done using if statement for more 
clarity

*/

