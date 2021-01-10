/**
 * HC-12 + Hardware Serial
 * 
 * Receiver
 * Capture HC-12 serial transmissions, parse the value, and transmit to servo
 */

#include <Servo.h>

#define SERVO_PIN 3

const int rxDelayMs = 10;
const float angleValMin = 1;
const float angleValMax = 179;
const char delimiterStart = '[';
const char delimiterEnd = ']';

float angleVal = angleValMin;
byte incomingByte;

Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(angleValMin);
}

void loop() {
  // put your main code here, to run repeatedly:
//  char readStr[11];
//  Serial.readBytes(readStr, 11);
//  Serial.println(readStr);
//  delay(1000);

  String readBuffer = "";
  boolean start = false;
  
  while(Serial.available()){
    incomingByte = Serial.read();
    delay(5);
//    Serial.print(char(incomingByte));

    if (start == true){
      if (incomingByte == delimiterStart){
        start = true;
        readBuffer = "";
      } else if (incomingByte == delimiterEnd){
        start = false;
//        Serial.println(readBuffer);
      } else {
        readBuffer += char(incomingByte);
      }
    } else if (incomingByte == delimiterStart) {
      start = true;
      readBuffer = "";
    }
  }

  angleVal = readBuffer.toFloat();

  if (angleVal >= angleValMin && angleVal <= angleValMax){
    servo.write(angleVal);
  }
  
//  delay(rxDelayMs);
}
