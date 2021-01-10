/**
 * HC-12 Demo #3
 * Transmitter
 * Capture potentiometer signals, convert to angles, and transmit
 */

#include <SoftwareSerial.h>

#define HC12_TX 10
#define HC12_RX 11
#define POT_PIN A3 // analog input

const int potCtrMax = 10;
const int potMin = 0;
const int potMax = 1023;
const float angleMin = 1.; // degrees
const float angleMax = 179.; // degrees
const int txDelayMs = 20; // delay between transmits

int potCtr = 0;
int potVal = 0;
float angleValPrev = angleMin;
float angleVal = angleMin;
String txtStr = "";

SoftwareSerial hc12(HC12_TX,HC12_RX); 

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);

  pinMode(POT_PIN, INPUT);
}

void loop() {
  // capture potentiometer value
  potVal += analogRead(POT_PIN);
  potCtr++;

  // compute the angle value only after 'potCtrMax' times to smooth out the value
  if (potCtr >= potCtrMax){
    potVal = potVal / potCtrMax; // get the average
    potCtr = 0;
    
    if (potVal >= potMin && potVal <= potMax){
      angleVal = map(potVal, potMin, potMax, angleMin, angleMax);
  
      // transmit only when there is a change in value
      // otherwise, the receiving will keep receiving a stream of values and 
      // will not exit the while loop
      if (angleVal != angleValPrev){
        txtStr = "[" + String(angleVal) + "]";
        
        Serial.println(txtStr);
        hc12.print(txtStr);
        delay(txDelayMs);
        
        angleValPrev = angleVal;
      }
      
    }
  }
}
