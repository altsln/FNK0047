/**********************************************************************
* Filename    : 005-02_RGB_gradient_p1
* Description : Use RGB LED to show the first range
* of gradient color. We are going from Red to Green
* Auther      : Alternatives Solutions
* Modification: 2026/02/09
**********************************************************************/

#define PWM_FRQ      1000 //define PWM Frequency
#define PWM_BIT      8   //define PWM Precision

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
  Serial.begin(112500);
}

// the loop function runs over and over again forever
void loop() { 

  //all LEDs ON
  Serial.println("Send all LEDs a 0 >> ON and wait 2 seconds.");
  ledcWrite(ledPinArray[0], 0);
  ledcWrite(ledPinArray[1], 0);
  ledcWrite(ledPinArray[2], 0);
  delay(2000);

  //All LEDs OFF
  Serial.println("Send all LEDs a 255 >> OFF and wait 2 seconds.");
  ledcWrite(ledPinArray[0], 255);
  ledcWrite(ledPinArray[1], 255);
  ledcWrite(ledPinArray[2], 255);
  delay(2000);


  //set the colors
  Serial.println("Moving from RED to GREEN");
  for(int duty = 0; duty <= 255; duty++) {
    //from Red to Green
    ledcWrite(ledPinArray[0], duty);
    ledcWrite(ledPinArray[1], 255 - duty);
    ledcWrite(ledPinArray[2], 255);
    delay(10);
  }
  /*
  for(int duty = 0; duty <= 255; duty++){
    ledcWrite(ledPinArray[0], 255);
    ledcWrite(ledPinArray[1], duty);
    ledcWrite(ledPinArray[2], 255 - duty);
    delay(10);
  }
  for(int duty = 0; duty <= 255; duty++){
    ledcWrite(ledPinArray[2], duty);
    ledcWrite(ledPinArray[0], 255 - duty);
    ledcWrite(ledPinArray[1], 255);
    delay(10);
  }
*/
  delay(DELAY_TIME);
}

