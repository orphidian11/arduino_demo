// https://www.youtube.com/watch?v=CfdaJ4z4u4w&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=3
// homework: blink 3 LEDs (red, yellow, green)
int redPin = 13;
int yellowPin = 12;
int greenPin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // turn on red, yellow, green LED one by one
  digitalWrite(redPin, HIGH);
  delay(500);
  digitalWrite(yellowPin, HIGH);
  delay(500);
  digitalWrite(greenPin, HIGH);
  delay(3000);

  // blink all 3 LEDs 3 times then wait 2 seconds
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(250);
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, HIGH);
  delay(250);
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(250);
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, HIGH);
  delay(250);
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(250);
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, HIGH);
  delay(2000);

  // turn off LEDs one by one and wait 2 seconds
  digitalWrite(redPin, LOW);
  delay(500);
  digitalWrite(yellowPin, LOW);
  delay(500);
  digitalWrite(greenPin, LOW);
  delay(2000);
}
