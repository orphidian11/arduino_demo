#include <Servo.h>

/**
 * Joystick
 * https://www.youtube.com/watch?v=KCdoRDDLWgo&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=33
 * 
 * Using a joystick, control the position of the servo arm
 * 
 * (X-axis) Left = 0, Center = 499-500, Right = 1023
 * (Y-axis) Up = 0, Middle = 499-500, Down = 1023
 * Press Down = 0, Press Up = 1
 * 
 * Servo: 0 - 180 degrees
 */

// pin setup
int xPin = A0;
int yPin = A1;
int swPin = 9;
int buzzPin = 10;
int servoPin = 8;

// I/O
int xV;
int yV;
int swV;
Servo servo;
float servoDeg;
float m;

// constants
float xValMin = 0;
float xValMax = 1023;
float servoDegMin = 170;
float servoDegMax = 10;
int delayMs = 100;
int buzzDelay = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(swPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
  
  digitalWrite(swPin, HIGH); 
  // trick to read from sPin without needing additional pull-up resistor
}

void loop() {
  // put your main code here, to run repeatedly:
  xV = analogRead(xPin);
  yV = analogRead(yPin);
  swV = digitalRead(swPin);

  m = (servoDegMax - servoDegMin) / (xValMax - xValMin);
  servoDeg = (m * (xV - xValMin)) + servoDegMin;

  servo.write(servoDeg);

  if (swV == 0){
    digitalWrite(buzzPin, HIGH);
  } else {
    digitalWrite(buzzPin, LOW);
  }

  Serial.print("[x,y]:");
  Serial.print(xV);
  Serial.print(",");
  Serial.print(yV);
  Serial.print(" / sw:");
  Serial.print(swV); 
  Serial.print(" / m:");
  Serial.print(m); 
  Serial.print(" / servoDeg:");
  Serial.print(servoDeg);
  Serial.println();

  delay(delayMs);
}
