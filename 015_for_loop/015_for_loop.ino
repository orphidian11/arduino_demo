// https://www.youtube.com/watch?v=OdHzRbR0xHQ&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=15
/**
 * Blink yellow LED 3 times, then the red LED 5 times
 */

// pins
int yellowPin = 8;
int redPin = 9;

int blinkYellowCount = 3;
int blinkRedCount = 5;

int delayMs = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int x = 0; x < blinkYellowCount; x++){
    digitalWrite(yellowPin, HIGH);
    delay(delayMs);
    digitalWrite(yellowPin, LOW);
    delay(delayMs);
  }

  for (int y = 0; y < blinkRedCount; y++){
    digitalWrite(redPin, HIGH);
    delay(delayMs);
    digitalWrite(redPin, LOW);
    delay(delayMs);
  }
}
