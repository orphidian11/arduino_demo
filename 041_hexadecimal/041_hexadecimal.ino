/**
 * https://www.youtube.com/watch?v=-RSI0z5zbqI&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=41
 * 
 * Hexadecimal
 */

byte myByte = 0xAB;
int delayMs = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myByte = myByte + 1;
  Serial.println(myByte,BIN);
  delay(delayMs);
}
