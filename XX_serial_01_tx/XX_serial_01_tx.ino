/**
 * https://iot-guider.com/arduino/serial-communication-between-two-arduino-boards/
 * Serial communications
 * Transmitter
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char helloWorld[11] = "Hello World";
  Serial.write(helloWorld, sizeof(helloWorld));
  delay(1000);
}
