// https://www.youtube.com/watch?v=42ahyWUkTiU&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=26

/**
 * Photoresistor Homework
 * Change the tone of the passive buzzer based on the intensity of light
 * Higher tone for dark
 * Lower tone for light
 */

// pin setup
int prReadPin = A0; // read voltage from photoresistor
int buzzPin = 9;

int prReading;
float slope = 9940./1023.;
float maxDelayVal = 60;
float delayMs;

void setup() {
  // put your setup code here, to run once:
  pinMode(prReadPin, INPUT);
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  prReading = analogRead(prReadPin);

  delayMs = (slope * prReading) + maxDelayVal;

  digitalWrite(buzzPin, HIGH);
  delayMicroseconds(delayMs);
  digitalWrite(buzzPin, LOW);
  delayMicroseconds(delayMs);
}
