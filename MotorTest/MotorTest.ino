/**
 * MotorTest
 * Author: Neil Balaskandarajah
 * Created on: 07/25/2020
 * Testing motor control with PWM
 */

//Array for motor pins (A and B)
byte leftMotor[] = {6,9};
byte rightMotor[] = {10,11};

/**
 * Don't need to set up motor pins for analog write
 */
void setup() {
}

/**
 * Test controlling the motors with PWM
 */
void loop() {
    fwdRevTest();
    delay(500);
    speedRampTest();
    
    //Stops the motors
    driveLeft(0);
    driveRight(0);
    exit(0);
}

/**
 * Test driving each motor forward and reverse
 */
void fwdRevTest() {
    driveLeft(-255);
    delay(1000);
    driveLeft(0);
    driveRight(-255);
    delay(1000);
    driveRight(0);

    driveLeft(255);
    delay(1000);
    driveLeft(0);
    driveRight(255);
    delay(1000);
    driveRight(0);
}

/**
 * Test ramping the speed with PWM
 */
void speedRampTest() {
  int spd = 0;
  int pause = 20;
  for (; spd < 255; spd += 10) {
    driveLeft(spd);
    delay(pause);
  }
  driveLeft(spd);
  delay(500);
  for (; spd > 0; spd -= 10) {
    driveLeft(spd);
    delay(pause);
  }
  
  for (; spd < 255; spd += 10) {
    driveRight(spd);
    delay(pause);
  }
  driveRight(spd);
  delay(500);
  for (; spd > 0; spd -= 10) {
    driveRight(spd);
    delay(pause);
  }
}

/**
 * Drive a motor given its ports and the speed
 * byte pinA - Pin controlling MxA
 * byte pinB - Pin controlling MxB
 * int val - Value from 0-255 representing 0-100% duty cycle
 */
void driveMotor(byte pinA, byte pinB, int val) {
  val = min(255, max(-255, val));  //Clamp to allowable range
  //flip direction if going in reverse
  if (val <= 0) {
    analogWrite(pinB, -val);
    analogWrite(pinA, 0);
  } else {
    analogWrite(pinA, val);
    analogWrite(pinB, 0);
  }
}

/**
 * Drive the left motor
 * int val - Value from 0-255 representing 0-100% duty cycle
 */
void driveLeft(int val) {
  driveMotor(leftMotor[0], leftMotor[1], val);
}

/**
 * Drive the right motor
 * int val - Value from 0-255 representing 0-100% duty cycle
 */
void driveRight(int val) {
  driveMotor(rightMotor[0], rightMotor[1], val);
}
