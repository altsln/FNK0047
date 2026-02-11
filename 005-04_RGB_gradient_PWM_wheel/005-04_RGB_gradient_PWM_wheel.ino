/**********************************************************************
* Filename    : 005-04_RGB_gradient_PWM_wheel
* Description : Use RGB LED to show the full range of gradient
* color. We are going from Red to Green and from Green
* Blue and finally from Blue to red. This is another  
* Auther      : Alternatives Solutions
* Modification: 2026/02/10
**********************************************************************/

#define PWM_FRQ      1000 //define PWM Frequency
#define PWM_BIT      8    //define PWM Precision

#define DELAY_TIME   10

//define LED pin Array Red(IO 23), Green(IO 5), Blue(IO 15)
const byte ledPinArray[] = {23, 5, 15}; 
//define the PWM channels
const byte chnArray[] = {4, 5, 7};
int ledPinArraySize = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  ledPinArraySize = sizeof(ledPinArray);
  // Attach the LEDs to PWM Channel.
  for (int i = 0; i < ledPinArraySize; i++) {
    ledcAttachChannel(ledPinArray[i], PWM_FRQ, PWM_BIT, chnArray[i]);
  }
}

// the loop function runs over and over again forever
void loop() { 

  for (int ind = 0; ind < 256; ind++) {
    setColor(wheel(ind));
    delay(DELAY_TIME);
  }
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

