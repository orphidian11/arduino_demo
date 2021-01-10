/**
 * HC-12 Demo #3
 * Receiver
 * Capture HC12 angle transmits and move servo
 */

//#include <SoftwareSerial.h>
#include <Servo.h>

#define HC12_TX 10
#define HC12_RX 11
#define SERVO_PIN 3

const float servoMin = 1.; // degrees
const float servoMax = 179.; // degrees
const char txBegin = '[';
const char txEnd = ']';

float servoValPrev = servoMin;
float servoVal = servoMin;
char incomingByte;
String strBuffer = "";
boolean start;

Servo servo;
//SoftwareSerial hc12(HC12_TX,HC12_RX); 

void setup() {
  Serial.begin(9600);
//  hc12.begin(9600);
  
  servo.attach(SERVO_PIN);
  servoVal = servoMin;
//  servo.write(servoVal);
  
  start = false;
}

void loop() {
  boolean isContinue = false;
  
  // capture potentiometer value
  while (Serial.available()){
    incomingByte = Serial.read(); // read the capture as byte
    delay(5);
    Serial.write(incomingByte);

    if (start == true){
      if (incomingByte != '[' && incomingByte != ']'){
        strBuffer += char(incomingByte); // parse the byte and add to string buffer
      } else if (incomingByte == ']'){
        start = false;
      } else {
        start = true;
      }
    } else if (incomingByte == '['){
      start = true;
      strBuffer = "";
    }
  }

  // parse the transmitted value
  servoVal = strBuffer.toFloat(); 

  // proceed to moving the servo only if there is a change in the values
  if (servoValPrev != servoVal){
    // acceptable angles should only be in the specified range
    if (servoVal >= servoMin && servoVal <= servoMax){
      Serial.println(strBuffer + " => " + String(servoVal));
      servo.write(servoVal);
      isContinue = false;
    }
    
    servoValPrev = servoVal;
  }

  strBuffer = "";
}
