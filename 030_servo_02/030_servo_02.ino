#include <Servo.h>

/**
 * Servo
 * 
 * Read the value of a potentiometer and use it to move a servo
 */

// pin setup
#define POT_PIN A1
#define SERVO_PIN 3

// constants
const float servoPosMin = 1.;
const float servoPosMax = 179.;
const int potValMin = 0;
const int potValMax = 1023;

// I/O
int potVal;
float servoPos = servoPosMin;

// objects
Servo servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
  servo.attach(SERVO_PIN); // servo is attached to servoPin
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(POT_PIN);
  servoPos = map(potVal, potValMin, potValMax, servoPosMin, servoPosMax);
  servo.write(servoPos);
  Serial.println(String(potVal) + " => " + String(servoPos));
}
