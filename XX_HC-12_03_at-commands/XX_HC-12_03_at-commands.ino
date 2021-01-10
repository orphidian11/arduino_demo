/**
 * https://www.youtube.com/watch?v=0PyHYLAKfnQ
 * HC-12 
 * AT Commands
 */

#include <SoftwareSerial.h>

#define RX 11 //Connect to the TX pin of the HC-12
#define TX 10 //Connect to the RX pin of the HC-12
#define SET_PIN 12

SoftwareSerial mySerial(RX, TX);

void setup() {
  pinMode(SET_PIN, OUTPUT);
  digitalWrite(SET_PIN, LOW); // config mode

  Serial.begin(9600);
  mySerial.begin(9600);

  while(!Serial);

  Serial.println("Input AT commands");
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
