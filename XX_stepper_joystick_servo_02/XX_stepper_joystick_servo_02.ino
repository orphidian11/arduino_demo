/**
 * 2 Stepper motors and Servo with Joystick control
 */

#include <Stepper.h>
#include <Servo.h>

// joystick
#define JX A5
#define JY A4
#define JB 2

// servo
#define SERVO 9

// stepper motor
#define A_IN1 7
#define A_IN2 6
#define A_IN3 5 
#define A_IN4 4

#define B_IN1 10
#define B_IN2 11
#define B_IN3 12 
#define B_IN4 13

const int stepsPerRevo = 2048; // for ROHS 28BYJ-48 5V DC stepper motor
const int stepperSpeed = 10; // RPM
const int stepsMax = 10;
const int stepsMin = 1;
const int cw = 1;
const int ccw = -1;
const int jXNeutMin = 499;
const int jXNeutMax = 501;
const int jYNeutMin = 499;
const int jYNeutMax = 501;

int xVal;
int yVal;
int bVal;
int bValPrev = 1;
int stepsA = stepsMin;
int stepsB = stepsMin;
float servoPos;

// Stepper class constructor format
// Note that 3rd parameter is switched, which is not that intuitive
Stepper stepperA(stepsPerRevo, A_IN1, A_IN3, A_IN2, A_IN4);
Stepper stepperB(stepsPerRevo, B_IN1, B_IN3, B_IN2, B_IN4);

Servo servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(JX, INPUT);
  pinMode(JY, INPUT);
  pinMode(JB, INPUT_PULLUP);

  stepperA.setSpeed(stepperSpeed);
  stepperB.setSpeed(stepperSpeed);
  
  servo.attach(SERVO); 

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // INPUTS
  xVal = analogRead(JX);
  yVal = analogRead(JY);
  bVal = digitalRead(JB);

  // X-axis controls stepper motor A
  if (xVal < jXNeutMin) {
//    Serial.println(String(xVal) + " LEFT");
    stepsA = map(xVal, jXNeutMin, 0, stepsMin, stepsMax);
    stepperA.step(stepsA * ccw);
  } else if (xVal > jXNeutMax) {
//    Serial.println(String(xVal) + " RIGHT");
    stepsA = map(xVal, jXNeutMax, 1023, stepsMin, stepsMax);
    stepperA.step(stepsA * cw);
  } else {
    digitalWrite(A_IN1, LOW);
    digitalWrite(A_IN2, LOW);
    digitalWrite(A_IN3, LOW);
    digitalWrite(A_IN4, LOW);

    stepsA = 0;
  }

  // Y-axis controls stepper motor B
  if (yVal < jYNeutMin) {
    stepsB = map(yVal, jYNeutMin, 0, stepsMin, stepsMax);
    stepperB.step(stepsB * ccw);
  } else if (yVal > jYNeutMax) {
    stepsB = map(yVal, jYNeutMax, 1023, stepsMin, stepsMax);
    stepperB.step(stepsB * cw);
  } else {
    digitalWrite(B_IN1, LOW);
    digitalWrite(B_IN2, LOW);
    digitalWrite(B_IN3, LOW);
    digitalWrite(B_IN4, LOW);

    stepsB = 0;
  }

//  servoPos = map(yVal, 0, 1023, 0, 180);
//  servo.write(servoPos);

  // Joystick button press triggers servo to close
  if (bVal != bValPrev) {
    if (bValPrev == 0){
      servo.write(180); // close
      delay(10);
    } else {
      servo.write(0); // open
      delay(10);
    }
    
    bValPrev = bVal;
  }
  
//  Serial.println(String(xVal) + "," + String(yVal) + "," + String(bVal));
  Serial.println(String(xVal) + ":" + String(stepsA) + "|" + String(yVal) + ":" + String(stepsB));
  
}
