/**********************************************************************
* Filename    : 011-02_single_potentiometer_RGB
* Description : Using one potentiometer to control the color RGB LED.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/17
**********************************************************************/

#define PWM_FRQ      1000  //define PWM Frequency
#define PWM_BIT      8     //define PWM Precision
#define DELAY_TIME   100

//define LED pin Array Red(IO 23), Green(IO 5), Blue(IO 15)
const byte ledPinArray[] = {19, 18, 5}; 
//define the PWM channels
const byte chnArray[] = {4, 5, 7};
const byte adcChn = 36;                 //define the adc channels
int ledPinArraySize = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  ledPinArraySize = sizeof(ledPinArray);
  // Attach the LEDs to PWM Channel.
  for (int i = 0; i < ledPinArraySize; i++) {
    //setup the pwm channels
    ledcAttachChannel(ledPinArray[i], PWM_FRQ, PWM_BIT, chnArray[i]);
  }
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {

    int adc_val = analogRead(adcChn);
    int wheelPos = map(adc_val, 0, 4096, 0, 255);
    
    Serial.printf("adc val: %d - wheel pos: %d \n", adc_val, wheelPos);
    setColor(wheel(wheelPos));
    delay(DELAY_TIME);
}

/*
Summary of a single line: 
ledcWrite(ledPins[0], 255 - (rgb >> 16) & 0xFF);

"Hey ESP32, considering the Red pin.
Take our big color number (24-bit 0xRRGGBB), 
slide it 16 spots over (0x0000RR), 
then make sure only 8 bits are kept (0x0000RR & 0xFF = 0xRR), 
flip the value for our LED type, and set the brightness. (255 - value)"
*/
void setColor(long rgb) {
  ledcWrite(ledPinArray[0], 255 - (rgb >> 16) & 0xFF);
  ledcWrite(ledPinArray[1], 255 - (rgb >> 8) & 0xFF);
  ledcWrite(ledPinArray[2], 255 - (rgb >> 0) & 0xFF);
}

//this function return actually a 24-bit Integer (0xRRGGBB)
long wheel(int pos) {
  long wheelPos = pos % 0xff;
  if (wheelPos < 85) {
    return manageRed2Green(wheelPos);
  } else if (wheelPos < 170) {
    wheelPos -= 85;
    return manageGreen2Blue(wheelPos);
  } else {
    wheelPos -= 170;
    return manageBlue2Red(wheelPos);
  }
}

//this function return actually a 24-bit Integer (0xRRGG--)
long manageRed2Green(long wheelPosition) {
  long redComponent = 255 - wheelPosition * 3;       //0x0000RR
  long redSlot = redComponent << 16;                 //0xRR----

  long greenComponent = wheelPosition * 3;           //0x0000GG
  long greenSlot = greenComponent << 8;              //0x--GG--

  return redSlot | greenSlot;
}

//this function return actually a 24-bit Integer (0x--GGBB)
long manageGreen2Blue(long wheelPosition) {
  long greenComponent = 255 - wheelPosition * 3;      //0x0000GG
  long greenSlot = greenComponent << 8;               //0x--GG--

  long blueComponent = wheelPosition * 3;             //0x0000BB
  long blueSlot = blueComponent;                      //0x----BB

  return greenSlot | blueSlot;
}

//this function return actually a 24-bit Integer (0xRR--BB)
long manageBlue2Red(long wheelPosition) {
  long redComponent = wheelPosition * 3;              //0x0000RR
  long redSlot = redComponent << 16;                  //0xRR----

  long blueComponent = 255 - wheelPosition * 3;       //0x0000BB
  long blueSlot = blueComponent;                      //0x----BB

  return redSlot | blueSlot;
}
