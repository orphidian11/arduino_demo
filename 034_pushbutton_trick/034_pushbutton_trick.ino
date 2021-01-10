/**
 * https://www.youtube.com/watch?v=ChHNI8yt69g&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=34
 * 
 * 2 ways to use a push Button without a separate resistor:
 * 
 * #1 - simulate a pull-up resistor
 * pinMode(inputPin, INPUT);
 * digitalWrite(inputPin, HIGH);
 * 
 * #2 - shortened version of #1
 * pinMode(inputPin, INPUT_PULLUP);
 */

// pin setup
int inputPin = 2;
int inputV;

void setup() {
  // put your setup code here, to run once:
  pinMode(inputPin, INPUT_PULLUP);
//  digitalWrite(inputPin, HIGH);
  // simulates a pull-up resistor

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputV = digitalRead(inputPin);
  Serial.println(inputV);
}
