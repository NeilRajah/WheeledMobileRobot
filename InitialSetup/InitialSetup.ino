/*
 * InitialSetup
 * Author: Neil Balaskandarajah
 * Created on: 07/20/2020
 * Initial set up tests for the Uno
 */

//Constants
byte INTERVAL = 20;   //Loop interval time in ms
byte PIN = 13;        //LED pin

//Variables
unsigned long current_time;   //Current time in milliseconds
unsigned long prev_time;      //Previous time in milliseconds
int LED_state;                //State of the LED

/**
 * Set the program up
 */
void setup() {
  Serial.begin(9600);     //Open communications port
  prev_time = millis();   //Start with previous delta time
  pinMode(13, OUTPUT);    //Set the pin to output mode
  LED_state = LOW;        //Start with the LED off
}

/**
 * Toggle the LED
 */
void blink() {
  if (LED_state == LOW) {
    LED_state = HIGH;
  } else {
    LED_state = LOW;
  }
  digitalWrite(PIN, LED_state);
}

/**
 * Run the program
 */
void loop() {
  //Run at specific intervals
  current_time = millis();
  
  int delta = current_time - prev_time;   //don't need this variable in future iterations
  if (delta >= INTERVAL) {
    prev_time = current_time;
    blink();    
  }
}
