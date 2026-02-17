/**********************************************************************
* Filename    : 011-01_potentiometer_led_RGB
* Description : Using three potentiometers to control the color RGB LED.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/17
**********************************************************************/

#define PWM_CHN             3
#define PWM_FRQ             1000

#define DELAY_TIME          10

const byte ledPins[] = {19, 18, 5};    //define RGB LED PINs
const byte pwmChns[] = {5, 6, 7};     //define PWM Channels
const byte adcChns[] = {36, 32, 35};  //define the adc channels
int colors[] = {0, 0, 0};             // red, green, blue, values of color. 

// the setup function runs once when you press reset or power the board
void setup() {
  for (int i = 0; i < 3; i++) {
    //setup the pwm channels
    ledcAttachChannel(ledPins[i], PWM_FRQ, 8, pwmChns[i]);
  }
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 0; i < 3; i++) {
    int adc_val = analogRead(adcChns[i]);
    //calculate color value
    colors[i] = map(adc_val, 0, 4096, 0, 255);
    Serial.printf("color[%d]: %d \n", i, colors[i]);
    //set color
    ledcWrite(ledPins[i], 256 - colors[i]);
  }
  delay(DELAY_TIME);
}
