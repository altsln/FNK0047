/**********************************************************************
* Filename    : 007-02_Buzzer_alert_on_timer_no_sinus
* Description : Using a button to make a passive buzzer to ring,
* due to some bugs with the code of ledcWriteTone, this time
* we are going to use a timer but no sinus function  
* Auther      : Alternatives Solutions
* Modification: 2026/02/13
**********************************************************************/

#define PIN_BUZZER    13
#define PIN_BUTTON    4

hw_timer_t* timerId = NULL;   //timer identity

//IRAM_ATTR tells the ESP32 to keep this function in its fastest memory 
// because it's going to be called very frequently.
// onTimer() is our callback function. will be called when needed.
void IRAM_ATTR onTimer() {
  static bool pinState = false;     //the magic of static
  pinState = !pinState;             //flip the state
  digitalWrite(PIN_BUZZER, pinState);
}

//we do not want to create multiple timer action
//or stop the timer multiple times
bool isAlerting = false;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  Serial.begin(115200);
  //initialize the timer (set the frequence and attach the callback function)
  timerId = timerBegin(1000000); //(This sets a 1MHz clock).
  //This links your "flip the pin" function to the timer)
  timerAttachInterrupt(timerId, &onTimer); 
}

// the loop function runs over and over again forever
void loop() {
  if (LOW == digitalRead(PIN_BUTTON)) {
    //When button is pressed
    if (!isAlerting) {
      //Set alerting
      isAlerting = true;
      Serial.println("Button is pressed start alerting once");
      //perform next task that need to be done once
      
      //Now there is a difference between timer and timerAlarm
      //Create a timerAlarm and set it to 250microsec and repeat
      timerAlarm(timerId, 250, true, 0);
      //start the alarm
      timerStart(timerId);
    }
//    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    //when button is not pressed
    if (isAlerting) {
      //stop the alarm once and change the state of the flag
      Serial.println("Button is released stop alerting once");
      isAlerting = false;
      //stop the alarm
      timerStop(timerId);
    }
    digitalWrite(PIN_BUZZER, LOW);
  }  
}


/*
//initialize the timer in the setup
//set the clock to 1Mhz and attach the callback function to it.

#define PIN_BUZZER    13
#define PIN_BUTTON    4

hw_timer_t* timerId = NULL;   //timer identity

//IRAM_ATTR tells the ESP32 to keep this function in its fastest memory 
// because it's going to be called very frequently.
// onTimer() is our callback function. will be called when needed.
void IRAM_ATTR onTimer() {
  static bool pinState = false;     //the magic of static
  pinState = !pinState;             //flip the state
  digitalWrite(PIN_BUZZER, pinState);
}

//we do not want to create multiple timer action
//or stop the timer multiple times
bool isAlerting = false;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  Serial.begin(115200);
  //initialize the timer (set the frequence and attach the callback function)
  timerId = timerBegin(1000000); //(This sets a 1MHz clock).
  //This links your "flip the pin" function to the timer)
  timerAttachInterrupt(timerId, &onTimer); 
}

// the loop function runs over and over again forever
void loop() {
  if (LOW == digitalRead(PIN_BUTTON)) {
    //When button is pressed
    if (!isAlerting) {
      //Set alerting
      isAlerting = true;
      Serial.println("Button is pressed start alerting once");
      //perform next task that need to be done once
    }
  } else {
    //when button is not pressed
    if (isAlerting) {
      //stop the alarm once and change the state of the flag

      Serial.println("Button is released stop alerting once");
      isAlerting = false;
    }
  }  
}

*/

/*
//create Timer identity or variable and the 
//callback function that the timer will use
#define PIN_BUZZER    13
#define PIN_BUTTON    4

hw_timer_t* timerId = NULL;   //timer identity

//IRAM_ATTR tells the ESP32 to keep this function in its fastest memory 
// because it's going to be called very frequently.
// onTimer() is our callback function. will be called when needed.
void IRAM_ATTR onTimer() {
  static bool pinState = false;     //the magic of static
  pinState = !pinState;             //flip the state
  digitalWrite(PIN_BUZZER, pinState);
}

//we do not want to create multiple timer action
//or stop the timer multiple times
bool isAlerting = false;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  if (LOW == digitalRead(PIN_BUTTON)) {
    //When button is pressed
    if (!isAlerting) {
      //Set alerting
      isAlerting = true;
      Serial.println("Button is pressed start alerting once");
      //perform next task that need to be done once
    }
  } else {
    //when button is not pressed
    if (isAlerting) {
      //stop the alarm once and change the state of the flag

      Serial.println("Button is released stop alerting once");
      isAlerting = false;
    }
  }  
}


The Magic of static
When you put static in front of a variable inside a function,
 it changes how the computer treats it:

1- Initialization happens only once: 
The line static bool pinState = false;
 only actually "runs" the very first time the function is called.

2- It has "Memory": When the function finishes, pinState is not destroyed.
It stays alive in the computer's memory, holding its value until the next time
 the timer calls the function.
*/


/*
#define PIN_BUZZER    13
#define PIN_BUTTON    4

//we do not want to create multiple timer action
//or stop the timer multiple times
bool isAlerting = false;
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  if (LOW == digitalRead(PIN_BUTTON)) {
    //When button is pressed
    if (!isAlerting) {
      //Set alerting
      isAlerting = true;
      Serial.println("Button is pressed start alerting once");
      //perform next task that need to be done once
    }
  } else {
    //when button is not pressed
    if (isAlerting) {
      //stop the alarm once and change the state of the flag

      Serial.println("Button is released stop alerting once");
      isAlerting = false;
    }
  }  
}

Why your suggestion is great:
Preventing "Machine Gun" Execution: 
By using if (!isAlerting), you ensure that the code inside only runs once 
at the moment the button is first pressed. 
Without this, the ESP32 would try to "start" the alarm thousands of times
 per second as long as your finger is on the button.

Clean Shutdown: Your else block correctly checks if (isAlerting) 
so it only runs the "stop" code once when you let go.

*/


/*
//here the goal is just to check if the button is pressed or released.
#define PIN_BUZZER    13
#define PIN_BUTTON    4

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  if (LOW == digitalRead(PIN_BUTTON)) {
    //When button is pressed

  } else {
    //when button is not pressed

  }  
}
*/