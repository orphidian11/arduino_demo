#include <Servo.h>

/**
 * Servo
 * https://www.youtube.com/watch?v=aFHu65LiFok&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=30
 * 
 * Using a photoresistor, check the brightness of the room.
 * Use the servo to point an arrow to either Sunny, Cloudy, Night
 */

// pin setup
int prPin =A0;
int servoPin = 9;

// constants
float servoPos;
float servoPosMin = 0;
int cloudMin = 150;
int cloudMax = 400;
float m = 180./1024.;
int prValMin = 0;

// I/O
int prVal;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(prPin, INPUT);
  Serial.begin(9600);
  servo.attach(servoPin); // servo is attached to servoPin
}

void loop() {
  // put your main code here, to run repeatedly:
  prVal = analogRead(prPin);
  servoPos = (m * (prVal - prValMin)) + servoPosMin;
  servo.write(servoPos);

  Serial.print("prVal: ");
  Serial.print(prVal);
  Serial.print(" / servoPos: ");
  Serial.println(servoPos);
}
