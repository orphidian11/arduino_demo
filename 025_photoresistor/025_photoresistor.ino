// https://www.youtube.com/watch?v=WMkN-uHd-Xo&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=25

/**
 * Photoresistors
 * If room is dark, red LED ON
 * If room is bright, green LED ON
 * 
 * Value ranges:
 * Lights off : < 150
 * Lights on : >= 150
 */

int inputPin = A0;
int redPin = 10;
int greenPin = 9;

int lightLimit = 150;
float resistorVal = 10000;
int photoResistVal;
int delayMs = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(inputPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  photoResistVal = analogRead(inputPin);
  
  Serial.println(photoResistVal); 

  if (photoResistVal >= 150) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  } else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  
  delay(delayMs);
}
