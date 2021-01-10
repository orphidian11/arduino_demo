/**
 * https://www.youtube.com/watch?v=tXs3Bzf7s9g&list=PLQJqki0RCuBsA2Gk_KRSY8kKNXzXGadHy&index=3
 * 
 * DC Motor with L293D driver + Tilt Switch
 */

#define SPD_PIN 5 
#define DIR_PIN1 4
#define DIR_PIN2 3
#define BALL_PIN 2

int noSpd = 0;
int minSpd = 100;
int maxSpd = 255; // PWM: 0-100 (stop); 101-255 (speed variation)
int ballIn;

void setup() {
  // put your setup code here, to run once:
  pinMode(SPD_PIN, OUTPUT);
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(DIR_PIN2, OUTPUT);
  pinMode(BALL_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  ballIn = digitalRead(BALL_PIN);
  Serial.println(ballIn);
  
  digitalWrite(DIR_PIN1, LOW);
  digitalWrite(DIR_PIN2, HIGH);

  if (ballIn == 0){
//    analogWrite(SPD_PIN, minSpd);
    analogWrite(SPD_PIN, maxSpd);
  } else {
    analogWrite(SPD_PIN, noSpd);
  }
}
