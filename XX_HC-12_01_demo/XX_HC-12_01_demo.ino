/**
 * https://www.youtube.com/watch?v=0zOTvB0T5fY
 * HC-12 Demo 
 * Sender
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello from the other side");
  delay(2000);
}
