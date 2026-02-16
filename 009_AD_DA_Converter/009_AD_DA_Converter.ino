/**********************************************************************
* Filename    : 009_DA_AD_Converter
* Description : Basic usage of ADC and DAC for ESP32 Wrover  
* Auther      : Alternatives Solutions
* Modification: 2026/02/15
**********************************************************************/
#define PIN_ANALOG_IN 36

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("\nESP32 Wrover initialization completed!");
  Serial.println("Ready to handle data...\n");
}

// the loop function runs over and over again forever
void loop() {

  int adc_val = analogRead(PIN_ANALOG_IN);
  int dac_val = map(adc_val, 0, 4095, 0, 255);

  double volt_result = adc_val / 4095.0 * 3.3;
  dacWrite(DAC1, dac_val);
  
  Serial.printf("ADC Val= %d, \t DAC Val= %d, \t Voltage= %.2fV\n", 
                      adc_val, dac_val, volt_result);
}
