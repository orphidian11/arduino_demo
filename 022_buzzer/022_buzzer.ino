// https://www.youtube.com/watch?v=tuRAvlVBEl0&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=22

/**
 * Read signal from potentiometer.
 * If value 1000 > sound buzzer
 */
 
// pin setup
int actBuzzPin = 9;
int potPin = A0;

int potInput;
int numMaxVal = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(actBuzzPin, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potInput = analogRead(potPin);
  Serial.println(potInput);
  
  if (potInput > numMaxVal) {
    digitalWrite(actBuzzPin, HIGH);
  } else {
    digitalWrite(actBuzzPin, LOW);
  }
}
