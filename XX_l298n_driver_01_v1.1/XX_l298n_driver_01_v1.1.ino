/**
 * https://www.youtube.com/watch?v=dyjo_ggEtVU
 * 
 * L298N Motor Driver
 * v1.1 - changed pin numbers
 */

#define EN_A 9
#define IN_A_1 8 
#define IN_A_2 7
#define EN_B 11
#define IN_B_1 12
#define IN_B_2 13

const float minSpd = 0;
const float maxSpd = 255;
float spd = minSpd;
int phaseInterval = 2000;
int rampUpInterval = 20;

void setup() {
  // put your setup code here, to run once:
  pinMode(EN_A, OUTPUT);
  pinMode(IN_A_1, OUTPUT);
  pinMode(IN_A_2, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN_B_1, OUTPUT);
  pinMode(IN_B_2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  motorForward();
  delay(phaseInterval);
  
  motorStop();
  delay(phaseInterval);
  
  motorReverse();
  delay(phaseInterval);
  
  motorStop();
  delay(phaseInterval);

  turnLeft();
  delay(phaseInterval);
  
  motorStop();
  delay(phaseInterval);

  turnRight();
  delay(phaseInterval);
  
  motorStop();
  delay(phaseInterval);

//  motorAccelForward();
//  delay(phaseInterval);
//  motorDecelForward();
//  delay(phaseInterval);
  
  motorStop();
  delay(phaseInterval);
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
void motorForward(){
  Serial.println("FORWARD MAX");
  
  // wheel A to forward
  digitalWrite(IN_A_1, HIGH);
  digitalWrite(IN_A_2, LOW);
  analogWrite(EN_A, maxSpd);

  // wheel B to forward
  digitalWrite(IN_B_1, HIGH);
  digitalWrite(IN_B_2, LOW);
  analogWrite(EN_B, maxSpd);

}

/**
 * Both wheels reverse at max speed
 */
void motorReverse(){
  Serial.println("REVERSE MAX");
  
  // wheel A to reverse
  digitalWrite(IN_A_1, LOW);
  digitalWrite(IN_A_2, HIGH);
  analogWrite(EN_A, maxSpd);

  // wheel B to reverse
  digitalWrite(IN_B_1, LOW);
  digitalWrite(IN_B_2, HIGH);
  analogWrite(EN_B, maxSpd);

}

void turnLeft(){
  Serial.println("LEFT MAX");
  
  // wheel A to forward
  digitalWrite(IN_A_1, HIGH);
  digitalWrite(IN_A_2, LOW);
  analogWrite(EN_A, maxSpd);

  // wheel B to reverse
  digitalWrite(IN_B_1, LOW);
  digitalWrite(IN_B_2, HIGH);
  analogWrite(EN_B, maxSpd);
  
}

void turnRight(){
  Serial.println("LEFT MAX");
  
  // wheel A to forward
  digitalWrite(IN_A_1, LOW);
  digitalWrite(IN_A_2, HIGH);
  analogWrite(EN_A, maxSpd);

  // wheel B to reverse
  digitalWrite(IN_B_1, HIGH);
  digitalWrite(IN_B_2, LOW);
  analogWrite(EN_B, maxSpd);
  
}

/**
 * Both wheelse forward accelerating
 */
void motorAccelForward(){
  Serial.println("FORWARD ACCELERATE");
  
  // wheel A to forward
  digitalWrite(IN_A_1, HIGH);
  digitalWrite(IN_A_2, LOW);
  
  // wheel B to forward
  digitalWrite(IN_B_1, HIGH);
  digitalWrite(IN_B_2, LOW);

  // accelerate
  for (int i = minSpd; i < maxSpd; i++){
    Serial.println(i);
    analogWrite(EN_A, i);
    analogWrite(EN_B, i);
    delay(rampUpInterval);
  }
}

/**
 * Both wheelse forward decelerating
 */
void motorDecelForward(){
  Serial.println("FORWARD DECELERATE");
  
  // wheel A to forward
  digitalWrite(IN_A_1, HIGH);
  digitalWrite(IN_A_2, LOW);
  
  // wheel B to forward
  digitalWrite(IN_B_1, HIGH);
  digitalWrite(IN_B_2, LOW);

  // accelerate
  for (int i = maxSpd; i > minSpd; i--){
    Serial.println(i);
    analogWrite(EN_A, i);
    analogWrite(EN_B, i);
    delay(rampUpInterval);
  }
}
