/**
 * Joystick
 * https://www.youtube.com/watch?v=B6YEQj4d5WU&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=32
 * 
 * Left = 0, Center = 499-500, Right = 1023
 * Up = 0, Middle = 499-500, Down = 1023
 * Press Down = 0, Press Up = 1
 */

 // pin setup
 int xPin = A0;
 int yPin = A1;
 int swPin = 7;

 int xV;
 int yV;
 int swV;

 int delayMs = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(swPin, INPUT);
  
  digitalWrite(swPin, HIGH); 
  // trick to read from sPin without needing additional pull-up resistor
}

void loop() {
  // put your main code here, to run repeatedly:
  xV = analogRead(xPin);
  yV = analogRead(yPin);
  swV = digitalRead(swPin);

  Serial.print("[x,y]:");
  Serial.print(xV);
  Serial.print(",");
  Serial.print(yV);
  Serial.print(" / sw:");
  Serial.println(swV); 

//  delay(delayMs);
}
