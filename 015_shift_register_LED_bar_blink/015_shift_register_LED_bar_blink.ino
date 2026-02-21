/**********************************************************************
* Filename    : 015_shift_register_LED_bar_blink
* Description : Use shift register 74HC595 to drive the
* LEDbar to blink 8 LEDs instead of 10.
* Auther      : Alternatives Solutions
* Modification: 2026/02/21
**********************************************************************/

#define LATCH_PIN       12    //pin connected to ST_CP of 74HC595(pin12)
#define CLOCK_PIN       13    //pin connected to SH_CP of 74HC595(pin13)
#define DATA_PIN        14    //pin connected to DS of 74HC595(pin14)
#define DELAY_TIME      500

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {

  byte d = 0xFF;  //d = data = (b) 0000 0001
  static bool state = true;
  state = !state;
  if (state) {
    d = 0xFF;
  } else {
    d = 0x00;
  }

  digitalWrite(LATCH_PIN, LOW);
  //send serial data to 74HC595
  Serial.print("Sending Binary: ");
  Serial.print(d);
  Serial.print("\n");
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, d);
  //Output high level to latch pin and the component
  // 74HC595 will update the data to the parallel output port
  digitalWrite(LATCH_PIN, HIGH);

  delay(2 * DELAY_TIME);
  delay(2 * DELAY_TIME);
}
