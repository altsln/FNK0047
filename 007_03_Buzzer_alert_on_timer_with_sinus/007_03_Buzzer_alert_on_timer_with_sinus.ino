/**********************************************************************
* Filename    : 007-03_Buzzer_alert_on_timer_with_sinus
* Description : Using a button to make a passive buzzer to ring,
* due to some bugs with the code of ledcWriteTone, this time
* we are going to use a timer and with a sinus function  
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
  static float wave_index = 0;  //The siren "position" - saved across every loop!
  if (LOW == digitalRead(PIN_BUTTON)) {
    //When button is pressed
    if (!isAlerting) {
      //Set alerting
      isAlerting = true;
      Serial.println("Button is pressed start alerting once");
      //perform next task that needs to be done once
      //Now there is a difference between timer and timerAlarm
      
      //start the alarm
      timerStart(timerId);
    }
    // --- SIREN MATGH SECTION ---
    // 1. Convert degrees to radians
    float radian = wave_index * PI / 180.0;
    // 2. Calculate a frequency that slides up and down
    float freq = 2000 + sin(radian) * 500;
    // 3. Convert frequency to a timer interval (microseconds)
    int interval = 1000000 / (freq * 2);
    // Update the timer interval immediately
    timerAlarm(timerId, interval, true, 0);
    
    wave_index++; // Move to the next "step" of the wave
    if (wave_index >= 360) wave_index = 0; // Reset after a full circle
    
    delay(2); // Small delay to control how fast the siren "wails"


  } else {
    //when button is not pressed
    if (isAlerting) {
      //stop the alarm once and change the state of the flag
      Serial.println("Button is released stop alerting once");
      isAlerting = false;
      //stop the alarm
      timerStop(timerId);
      digitalWrite(PIN_BUZZER, LOW); // Ensure silence
      wave_index = 0; // Reset the song for next time
    }
    
  }  
}
/*
The math
We use the formula: $freq = 2000 + \sin(i \cdot \frac{\pi}{180}) \cdot 500$.
This slides the frequency between 1500Hz and 2500Hz.
Since our timer is 1MHz, the "interval" we give the timer is $\frac{1,000,000}{freq \cdot 2}$ 
(the "2" is because the timer only represents half a wave—one flip).

for more info 
1. The "Base" Frequency (2000)
The value 2000 represents the "Center Pitch" in Hertz (Hz).
  > Resonant Frequency: Most small passive buzzers have a "sweet spot" (resonant frequency)
   where they are loudest, usually between 2000Hz and 2500Hz.
  > The Starting Point: By setting this to 2000, the alarm starts right in the middle
   of the buzzer's most effective range.
  > Effect: If you changed this to 500, the alarm would sound very deep and "growly."
   If you changed it to 4000, it would be a very piercing, high-pitched whistle.

2. The "Swing" Amount (500)The value 500 is the Amplitude of the wave. 
It determines how far "up" and "down" the pitch travels from the center.
  > The Range: Because you are adding and subtracting this from the base (2000),
   your alarm slides between 1500Hz ($2000 - 500$) and 2500Hz ($2000 + 500$).
  > Effect: If you increased this to 1000, the siren would sound much more dramatic
   (like a "Deep-High" cartoon siren). If you decreased it to 50, the pitch change
    would be so subtle you might barely hear it sliding.
    
3. The "Smoothness" ($\sin$ and $i$)
The sin() function is used because it doesn't move in a straight line.
  > The Curve: A sine wave spends more time at the very top and very bottom of the curve
   and moves quickly through the middle. This mimics the way mechanical sirens 
   (like on old fire trucks) sound as they spin up and down.
  > The Converter ($PI / 180.0$): The sin() function in C++ expects "Radians,"
   but as humans, we think in "Degrees" (0 to 360). This little bit of math converts
    your degree counter ($i$) into the format the computer understands.

4. The "Final Conversion" ($1,000,000 / (freq \cdot 2)$)
This is the bridge between Music (Frequency) and Time (the Timer).
  > The 1,000,000: Since your timer runs at 1MHz, there are 1,000,000 "ticks" in a second.
  > The $\cdot 2$: A full sound wave has a "High" part and a "Low" part.
   To make a 2000Hz sound, you need to flip the pin 4000 times per second.
  > The Result: This calculation tells the ESP32 exactly how many microseconds to wait
   before flipping the pin again to achieve the desired pitch.

Summary Table
--------------
Component,       Role,              Effect of Increasing
2000,            Center Pitch,      Higher overall sound
500,             Pitch Range,       "More ""dramatic"" slide"
i increment,     Speed,             "Faster ""wailing"""
delay(2),        Tempo,             "Slower ""wailing"""


*/






/*
//No Sinus function used

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
*/

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