/**
 * https://www.youtube.com/watch?v=vqRqtgvltOI&t=490s
 * HC-12 Demo
 * Transmit/Receive
 */

#include <SoftwareSerial.h>

SoftwareSerial hc12(10,11); // 10: TX, 11: RX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hc12.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // if data is received, send to serial monitor
  while (hc12.available()){
    Serial.write(hc12.read());
  }
}
