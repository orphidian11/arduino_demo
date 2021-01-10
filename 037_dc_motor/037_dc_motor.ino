/**
 * https://www.youtube.com/watch?v=fPLEncYrl4Q&list=PLQJqki0RCuBsA2Gk_KRSY8kKNXzXGadHy&index=2
 * 
 * DC Motor with L293D driver
 */

#define SPD_PIN 5 
#define DIR_PIN1 4
#define DIR_PIN2 3

int mSpd = 100; // PWM: 0-100 (stop); 101-255 (speed variation)

void setup() {
  // put your setup code here, to run once:
  pinMode(SPD_PIN, OUTPUT);
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(DIR_PIN2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(DIR_PIN1, LOW);
  digitalWrite(DIR_PIN2, HIGH);
  analogWrite(SPD_PIN, 255);
  delay(100);
  analogWrite(SPD_PIN, 90);
  delay(5000);
}
