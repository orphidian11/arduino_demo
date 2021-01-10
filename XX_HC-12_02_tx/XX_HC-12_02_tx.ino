/**
 * https://www.youtube.com/watch?v=vqRqtgvltOI&t=490s
 * HC-12 Demo #2
 * Transmitter
 */

#include <SoftwareSerial.h>

#define RED_PIN 3
#define YEL_PIN 4
#define GRN_PIN 5

SoftwareSerial hc12(10,11); // 10: TX, 11: RX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hc12.begin(9600);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(YEL_PIN, OUTPUT);
  pinMode(GRN_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // LED is always ON to maintain power draw 
  // and prevent power bank from auto-shutoff
  digitalWrite(RED_PIN, HIGH); 
  digitalWrite(YEL_PIN, HIGH); 
  digitalWrite(GRN_PIN, HIGH); 

  // transmit
  hc12.write("Hello World");
  delay(2000);
}
