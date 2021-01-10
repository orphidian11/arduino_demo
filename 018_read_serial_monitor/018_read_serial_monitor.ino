// https://www.youtube.com/watch?v=7aP5KL5clWA&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=18

/**
 * Input number of times red LED will blink
 */

// pin setup
int redPin = 12;

int numBlink;
String msg = "Enter number: ";
int delayMs = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(msg);  // ask
  
  while (Serial.available() == 0) { // wait
    // do nothing
  }

  numBlink = Serial.parseInt(); // read

  for (int i = 0; i < numBlink; i++){
    digitalWrite(redPin, HIGH);
    delay(delayMs);
    digitalWrite(redPin, LOW);
    delay(delayMs);
  }
}
