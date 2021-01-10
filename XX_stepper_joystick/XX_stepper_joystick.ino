/**
 * Stepper motor with Joystick control
 */

#include <Stepper.h>

// joystick
#define JX A5
#define JY A4
#define JB 2

// stepper motor
#define IN1 7
#define IN2 6
#define IN3 5 
#define IN4 4

const int stepsPerRevo = 2048; // for ROHS 28BYJ-48 5V DC stepper motor
const int stepperSpeed = 10; // RPM
const int stepsMax = 30;
const int stepsMin = 1;
const int cw = 1;
const int ccw = -1;
const int jXNeutMin = 499;
const int jXNeutMax = 501;

int xVal;
int yVal;
int bVal;
int bValPrev = 1;
int steps = stepsMin;

// Stepper class constructor format
// Note that 3rd parameter is switched, which is not that intuitive
Stepper stepper(stepsPerRevo, IN1, IN3, IN2, IN4);

void setup() {
  // put your setup code here, to run once:
  pinMode(JX, INPUT);
  pinMode(JY, INPUT);
  pinMode(JB, INPUT_PULLUP);

  stepper.setSpeed(stepperSpeed);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // INPUTS
  xVal = analogRead(JX);
  yVal = analogRead(JY);
  bVal = digitalRead(JB);

  if (xVal < jXNeutMin) {
//    Serial.println(String(xVal) + " LEFT");

    steps = map(xVal, jXNeutMin, 0, stepsMin, stepsMax);
    stepper.step(steps * ccw);
  } else if (xVal > jXNeutMax) {
//    Serial.println(String(xVal) + " RIGHT");
    
    steps = map(xVal, jXNeutMax, 1023, stepsMin, stepsMax);
    stepper.step(steps * cw);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    steps = 0;
  }
  
  if (bVal != bValPrev) {
    if (bValPrev == 0){
      stepper.step(cw * stepsPerRevo);
      delay(2000);
      stepper.step(ccw * stepsPerRevo);
      delay(2000);
    }
    
    bValPrev = bVal;
  }
  
//  stepper.step(cw * stepsPerRevo);
//  delay(2000);
//  stepper.step(ccw * stepsPerRevo);
//  delay(2000);
  
//  Serial.println(String(xVal) + "," + String(yVal) + "," + String(bVal));
  Serial.println(String(xVal) + "," + steps);
  
}
