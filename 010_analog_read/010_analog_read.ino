// https://www.youtube.com/watch?v=5TitZmA66bI&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=10

int readPin = A3;
int readVal;
float v2 = 0;
int delayMs = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readVal = analogRead(readPin);
  v2 = (5./1023.) * readVal;
  Serial.println(v2);
  delay(delayMs);
}
