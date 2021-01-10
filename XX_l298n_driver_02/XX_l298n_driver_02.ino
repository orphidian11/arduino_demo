/**
 * https://www.youtube.com/watch?v=dyjo_ggEtVU
 * 
 * L298N Motor Driver
 * With potentiometer speed control
 */

#define EN_A 3
#define IN_A_1 4 
#define IN_A_2 5
#define EN_B 9
#define IN_B_1 8
#define IN_B_2 7
#define POT A0

const float minSpd = 0;
const float maxSpd = 255;
const float minPot = 0;
const float maxPot = 1023;
const float startSpd = 80;

float potVal;
float spd = minSpd;
int phaseInterval = 10000;
int rampUpInterval = 20;

void setup() {
  // put your setup code here, to run once:
  pinMode(EN_A, OUTPUT);
  pinMode(IN_A_1, OUTPUT);
  pinMode(IN_A_2, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN_B_1, OUTPUT);
  pinMode(IN_B_2, OUTPUT);

  pinMode(POT, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  motorForward(getSpd());
}

float getSpd(){
  int pVal = analogRead(POT);
  float spdVal = map(pVal, minPot, maxPot, minSpd, maxSpd);

  if (spdVal < startSpd){
    spdVal = 0;
  }

//  Serial.println(String(pVal) + "-" + String(spdVal));

  return spdVal;
}

/**
 * Both wheels stop
 */
void motorStop(){
  Serial.println("STOP");
  
  digitalWrite(IN_A_1, LOW);
  digitalWrite(IN_A_2, LOW);
  
  digitalWrite(IN_B_1, LOW);
  digitalWrite(IN_B_2, LOW);
}

/**
 * Both wheels forward at max speed
 */
void motorForward(float spd){
  Serial.println("FORWARD MAX " + String(spd));
  
  // wheel A to forward
  digitalWrite(IN_A_1, HIGH);
  digitalWrite(IN_A_2, LOW);
  analogWrite(EN_A, getSpd());

  // wheel B to forward
  digitalWrite(IN_B_1, HIGH);
  digitalWrite(IN_B_2, LOW);
  analogWrite(EN_B, spd);

}

/**
 * Both wheels reverse at max speed
 */
void motorReverse(float spd){
  Serial.println("REVERSE MAX " + String(spd));
  
  // wheel A to reverse
  digitalWrite(IN_A_1, LOW);
  digitalWrite(IN_A_2, HIGH);
  analogWrite(EN_A, spd);

  // wheel B to reverse
  digitalWrite(IN_B_1, LOW);
  digitalWrite(IN_B_2, HIGH);
  analogWrite(EN_B, spd);

}
