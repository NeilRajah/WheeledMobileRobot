/**
   EncoderTest
   Author: Neil Balaskandarajah
   Created on: 24/07/2020
   Testing the Encoders out
*/

//Constants
#define TICKS_PER_REV 297.0   //Encoder ticks per revolution
#define DIA 30                //Wheel diameter in mm
#define INTERVAL 20           //Loop period in ms

//Encoder pins
#define leftEncA 2
#define leftEncB 5
#define rightEncA 3
#define rightEncB 4

//Encoder values
int leftTicks;
int rightTicks;

//Timing values
int curr;
int prev;

/**
 * Set up the pins and the code
 */
void setup() {
  //Initialize Serial and set pin modes
  Serial.begin(9600);
  pinMode(leftEncA, INPUT_PULLUP);
  pinMode(leftEncB, INPUT_PULLUP);
  pinMode(rightEncA, INPUT_PULLUP);
  pinMode(rightEncB, INPUT_PULLUP);

  //Side threads to track encoders
  attachInterrupt(digitalPinToInterrupt(leftEncA), updateLeftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncA), updateRightEncoder, RISING);

  //Initialize variables
  leftTicks = 0;
  rightTicks  = 0;
  prev = millis();
}

/**
 * Display encoders
 */
void loop() {
  curr = millis();
  float delta = curr - prev;
  if (delta >= INTERVAL) {
    prev = millis();
    
    displayEncoders();
  }
}

/**
 * Print the encoder positions (mm) to the screen
 */
void displayEncoders() {
  Serial.print(ticksToInches(leftTicks));
  Serial.print(' ');
  Serial.print(ticksToInches(rightTicks));
  Serial.println();
}

/**
 * Convert encoder ticks to inches
 */
float ticksToInches(int ticks) {
  return (ticks / TICKS_PER_REV) * PI * DIA;
}

/**
 * Update the left encoder
 */
void updateLeftEncoder() {
  if (digitalRead(leftEncA) == digitalRead(leftEncB)) {
    leftTicks++;
  } else {
    leftTicks--;
  }
}

/**
 * Update the right encoder (mirror of left)
 */
void updateRightEncoder() {
  if (digitalRead(rightEncA) == digitalRead(rightEncB)) {
    rightTicks--;
  } else {
    rightTicks++;
  }
}
