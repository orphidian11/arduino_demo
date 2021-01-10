/**
 * https://www.youtube.com/watch?v=vqRqtgvltOI&t=490s
 * HC-12 Demo
 * Transmit/Receive
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // if data is received, send to serial monitor
  byte incomingByte;
  String readBuffer = "";
  while (Serial.available()){
    incomingByte = Serial.read();
    readBuffer += char(incomingByte);
  }

  if (readBuffer != ""){
    Serial.println(readBuffer);
  }
}
