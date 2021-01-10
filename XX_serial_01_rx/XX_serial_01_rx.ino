/**
 * https://iot-guider.com/arduino/serial-communication-between-two-arduino-boards/
 * Serial communications
 * Receiver
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char readStr[11];
  Serial.readBytes(readStr, 11);
  Serial.println(readStr);
  delay(1000);
}
