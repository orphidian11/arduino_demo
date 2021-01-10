/**
 * https://www.youtube.com/watch?v=0zOTvB0T5fY
 * HC-12 Demo
 * Receiver
 */

#define RED_PIN 7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  while(!Serial);
  Serial.println("begin");
  digitalWrite(RED_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()){
    String input = Serial.readString();
    Serial.println(input);
    
    if (input == "Hello World"){
      digitalWrite(RED_PIN, HIGH);
      delay(500);
      digitalWrite(RED_PIN, LOW);
    }
  }
}
