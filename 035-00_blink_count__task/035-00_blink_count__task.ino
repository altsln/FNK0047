/**********************************************************************
* Filename    : 035_blink_count__task
* Description : Building the simpliest arduino Task project
* In this project we are going to run 2 loops in parallel,
* Loop 1 (Standard): Prints a "Hello" message every 1 second.
* Task 2 (The New Worker): Blinks the built-in LED every 0.5 seconds.
* Auther      : Alternatives Solutions.
* Modification: 2026/04/15
**********************************************************************/
//ESP32 for now does not support 5G connection

const int LED_BUILT_IN = 2;

//extern TaskHandle_t loopTaskHandle;
// 1. We create a "Handle" (an ID card for our task)
TaskHandle_t MyTaskHandle;


void setup() {

  Serial.begin(115200);
  pinMode(LED_BUILT_IN, OUTPUT); // Built-in LED on most ESP32s
  //digitalWrite(LED_BUILTIN, HIGH); // turn the LED OFF (Active LOW)


  // 2. We "Hire" the worker.
  xTaskCreatePinnedToCore(
    MyWorkerFunction,   // The name of the function to run
    "BlinkTask",        // A name for us to read
    1000,               // Stack size (Memory for this worker)
    NULL,               // Parameters to pass (none)
    1,                  // Priority (1 is low, higher is more important)
    &MyTaskHandle,      // The ID card we created
    0                   // THE CORE: Run this on Core 0 (Loop runs on Core 1)
  );
  
}

//task loop uses core 1.
void loop() {
  // This runs on Core 1, completely independent of the LED blink!
  Serial.println("I am the main loop, and I am not blocked!");
  delay(1000);
}

// 3. This is the worker's own private loop
void MyWorkerFunction(void * pvParameters) {
  for(;;) { // Workers need their own infinite loop
    digitalWrite(LED_BUILT_IN, HIGH);
    delay(500); 
    digitalWrite(LED_BUILT_IN, LOW);
    delay(500);
  }
}