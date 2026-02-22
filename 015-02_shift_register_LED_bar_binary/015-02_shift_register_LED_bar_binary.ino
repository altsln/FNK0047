/**********************************************************************
* Filename    : 015-02_shift_register_LED_bar_binary
* Description : Use shift register 74HC595 to drive the
* LEDbar to display the flowing light on 8 LEDs instead
* of 10, in binary conversion.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/21
**********************************************************************/

#define LATCH_PIN       15//12    //pin connected to ST_CP of 74HC595(pin12)
#define CLOCK_PIN       4//13    //pin connected to SH_CP of 74HC595(pin13)
#define DATA_PIN        23//14    //pin connected to DS of 74HC595(pin14)
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
  //Define one byte variable to use to represent the sate or the 
  // value of the LED bar or le state of each of 8 of the selected
  // 8 LEDs of the LEDbar.
  //The variable is set to 0x01to show that at the begining only 
  // one LED is on.
  displayBinary ();
  delay(2 * DELAY_TIME);

}

void displayBinary () {
  for (int i = 0; i < 256; i++) {
    writeTo74HC595(LSBFIRST, i);
    delay(DELAY_TIME);
  }
}

void writeTo74HC595(int order, byte dataElt) {
  //Output LOW level to latch pin
  digitalWrite(LATCH_PIN, LOW);

  Serial.print("Sending Binary: ");
  Serial.print(dataElt);
  Serial.print("\n");

  //send serial data to 74HC595
  shiftOut(DATA_PIN, CLOCK_PIN, order, dataElt);
  //Output high level to latch pin and the component
  // 74HC595 will update the data to the parallel output port
  digitalWrite(LATCH_PIN, HIGH);
}