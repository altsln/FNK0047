/**********************************************************************
* Filename    : 005_RGB_random_color
* Description : Use RGB LED to show random color
* Auther      : Alternatives Solutions
* Modification: 2026/02/09
**********************************************************************/

#define PWM_FRQ      1000 //define PWM Frequency
#define PWM_BIT      10   //define PWM Precision

#define DELAY_TIME   200

//define LED pin Array Red(IO 23), Green(IO 5), Blue(IO 15)
const byte ledPinArray[] = {23, 5, 15}; 
//define the PWM channels
const byte chnArray[] = {4, 5, 7};
int ledPinArraySize = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  ledPinArraySize = sizeof(ledPinArray);
  // Attach the LEDs to PWM Channel.
  for (int i = 0; i < ledPinArraySize; i++) {
    ledcAttachChannel(ledPinArray[i], PWM_FRQ, PWM_BIT, chnArray[i]);
  }
  Serial.begin(112500);
}

// the loop function runs over and over again forever
void loop() { 
  redColor = random(0, 256);
  greenColor = random(0, 256);
  blueColor = random(0, 256);
  
  //
  Serial.print("r= ");
  Serial.print(redColor);
  Serial.print(", [256-r= ");
  Serial.print(256-redColor);
  Serial.print("] - g= ");
  Serial.print(greenColor);
  Serial.print(", [256-g= ");
  Serial.print(256-greenColor);
  Serial.print("] - b= ");
  Serial.print(blueColor);
  Serial.print(", [256-b= ");
  Serial.print(256-blueColor);
  Serial.print("]");
  Serial.println("");

  //set the colors
  setColor(redColor, greenColor, blueColor);

  delay(DELAY_TIME);
}

void setColor(byte r, byte g, byte b) {
  ledcWrite(ledPinArray[0], redColor);
  ledcWrite(ledPinArray[1], greenColor);
  ledcWrite(ledPinArray[2], blueColor);
}

void setColor2(byte r, byte g, byte b) {
  ledcWrite(ledPinArray[0], 256 - redColor);
  ledcWrite(ledPinArray[1], 256 - greenColor);
  ledcWrite(ledPinArray[2], 256 - blueColor);
}
