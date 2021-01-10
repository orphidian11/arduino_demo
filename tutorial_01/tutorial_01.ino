// https://www.youtube.com/watch?v=r0sUNrqFrM0&list=PL1KVSZBJtW0rek6O1XLvheD6tY5YTg0Rt&index=1

int led = 13; // goes to pin 13

void setup () {
  pinMode(led, OUTPUT); // initialize as OUTPUT
}

void loop(){
  digitalWrite(led, HIGH); // (ON) set pin to high voltage level
  delay(500); // milliseconds
  digitalWrite(led, LOW); // (OFF) set to low voltage level
  delay(500); 
  digitalWrite(led, HIGH); 
  delay(500); 
  digitalWrite(led, LOW); 
  delay(2000); 
}
