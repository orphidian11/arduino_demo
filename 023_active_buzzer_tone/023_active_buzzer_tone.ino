// https://www.youtube.com/watch?v=W5AApP9P-b0&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=23

// pin setup
int actBuzzPin = 9;

int delayMs = 1000;
int delayMs1 = 1;
int delayMs2 = 2;
int i;
int maxVal = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(actBuzzPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(actBuzzPin, HIGH);
  
  for (i = 1; i <= maxVal; i++){
    digitalWrite(actBuzzPin, HIGH);
    delay(delayMs1);
    digitalWrite(actBuzzPin, LOW);
    delay(delayMs1);
  }

  delay(delayMs);
  
  for (i = 1; i <= maxVal; i++){
    digitalWrite(actBuzzPin, HIGH);
    delay(delayMs2);
    digitalWrite(actBuzzPin, LOW);
    delay(delayMs2);
  }

  delay(delayMs);
}
