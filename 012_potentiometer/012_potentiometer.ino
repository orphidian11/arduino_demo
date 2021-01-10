// https://www.youtube.com/watch?v=PUte1cmJ44A&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=12

int readPin = A2;
float vOut;
float binMultiplier = (5./1023.);
int delayMs = 125;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  vOut = analogRead(readPin) * binMultiplier;
  Serial.print("vOut = ");
  Serial.println(vOut);
  delay(delayMs);
}
