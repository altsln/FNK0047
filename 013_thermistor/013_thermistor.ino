/**********************************************************************
* Filename    : 013_thermistor
* Description : Using a thermistor to read temperature.  
* Auther      : Alternatives Solutions
* Modification: 2026/02/19
**********************************************************************/

#define INPUT_PIN         4 //15       //define input analog Pin
//B is for thermal index
#define B_VALUE           3950.0
// Kelvin temperature (absolute temperature).
#define T1_VALUE          25
#define TEMP_CONST        273.15
//R is the nominal resistance of thermistor under T1 temperature;
#define R_VALUE           10000

#define DELAY_TIME        1000

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
//  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {
  int adc_val = analogRead(INPUT_PIN);    //read adc input pin
  double voltage = (float)adc_val / 4095.0 * 3.3;
  double Rt = R_VALUE * voltage / (3.3 - voltage);
  //Calculate Temperature Kelvin 
  double tempKel = 1 / ((1 / (TEMP_CONST + T1_VALUE)) + log(Rt / R_VALUE) / B_VALUE);
  //Calculate Temperature Celcius 
  double tempCel = tempKel - TEMP_CONST;

  Serial.printf("ADC val: %d, - Voltage: %.2fv, - Temperature: %.2fC\n",
    adc_val, voltage, tempCel);
  delay(DELAY_TIME);
}

//Also tested with tip of soldering iron to see if the temperature will increase.
//See picture for both cases normal and also the one when the temperature increases. 