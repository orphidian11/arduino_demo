// https://www.youtube.com/watch?v=dHYKRrlPNzM&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=24

/**
 * Read signal from potentiometer.
 * For max potentiometer value (1023), buzz delay time is 10,000 microseconds
 * For low, 60 microsecond delay
 */

// pin setup
int buzzPin = 9;
int potPin = A0;

int potVal;
float minBuzzTime = 60;
float slope = 9940./1023.;
float buzzTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzPin, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potPin);
  
  buzzTime = (slope * potVal) + minBuzzTime;

  //Serial.print("potVal: ");
  //Serial.print(potVal);
  //Serial.print(" / buzzTime: ");
  //Serial.println(buzzTime);
  
  digitalWrite(buzzPin, HIGH);
  delayMicroseconds(buzzTime);
  digitalWrite(buzzPin, LOW);
  delayMicroseconds(buzzTime);
}
