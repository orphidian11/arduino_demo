/**
 * https://www.youtube.com/watch?v=dyjo_ggEtVU
 * 
 * L298N Motor Driver
 * With joystick navigation (code was based on 039_dc_motor_joystic.ino)
 */

#define EN_A 3
#define IN_A_1 4 
#define IN_A_2 5
#define EN_B 9
#define IN_B_1 8
#define IN_B_2 7
#define JX A0
#define JY A1

/** CONSTANTS **/
// wheels
const int L = 0;
const int R = 1;

// speed range
const float minSpd = 0;
const float maxSpd = 255;
const float startSpd = 80;

// joystick range
const float jMin = 0;
const float jMax = 1023;

// joystick neutral range tolerance 
const float jNeutMin = 498;
const float jNeutMax = 501;

int xVal;
int yVal;
float rSpd = minSpd;
float lSpd = minSpd;
float lSpdRedux = minSpd;
float rSpdRedux = minSpd;
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

  pinMode(JX, INPUT);
  pinMode(JY, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  /** INPUT **/
  int xVal = analogRead(JX);
  int yVal = analogRead(JY);

  /** PROCESS **/
  // forward/reverse/stop
  if (yVal <= jNeutMin){
    // forward
    lSpd = rSpd = map(yVal, jNeutMin, jMin, minSpd, maxSpd);
    setForward(0);
    setForward(1);
  } else if (yVal >= jNeutMax) {
    // reverse
    lSpd = rSpd = map(yVal, jNeutMax, jMax, minSpd, maxSpd);
    setReverse(0);
    setReverse(1);
  } else {
    motorStop();
  }

  // left/right turn
  if (xVal <= jNeutMin){
    // left turn
    lSpdRedux = map(xVal, jNeutMin, jMin, minSpd, lSpd);
    rSpdRedux = minSpd;
  } else if (xVal >= jNeutMax) {
    // right turn
    lSpdRedux = minSpd;
    rSpdRedux = map(xVal, jNeutMax, jMax, minSpd, rSpd);
  } else {
    lSpdRedux = rSpdRedux = 0.;
  }

  // to prevent negative speed reduction, set reduction to 0 when speed is 0
  if (lSpd == minSpd){
    lSpdRedux = 0.;
  } 
  if (rSpd == minSpd){
    rSpdRedux = 0.;
  }

  /** OUTPUT **/
  analogWrite(EN_A, lSpd - lSpdRedux);
  analogWrite(EN_B, rSpd - rSpdRedux);

//  Serial.print("x,y = [" + String(xVal) + "," + String(yVal) + "] => ");
  Serial.print("L,R = [" + String(lSpd) + "," + String(rSpd) + "] ");
  Serial.print("Lr,Rr = [" + String(lSpdRedux) + "," + String(rSpdRedux) + "] ");
  Serial.print("Lf,Rf = [" + String(lSpd - lSpdRedux) + "," + String(rSpd - rSpdRedux) + "] ");
  Serial.println();
}

/**
 * Both wheels stop
 */
void motorStop(){
//  Serial.println("STOP");
  
  digitalWrite(IN_A_1, LOW);
  digitalWrite(IN_A_2, LOW);
  
  digitalWrite(IN_B_1, LOW);
  digitalWrite(IN_B_2, LOW);
}

void setForward(int wheel){
//  Serial.println("FORWARD");
  if (wheel == 0){ // left
    digitalWrite(IN_A_1, HIGH);
    digitalWrite(IN_A_2, LOW);
  } else { // right
    digitalWrite(IN_B_1, HIGH);
    digitalWrite(IN_B_2, LOW);
  }
}

void setReverse(int wheel){
//  Serial.println("REVERSE");
  if (wheel == 0){ // left
    digitalWrite(IN_A_1, LOW);
    digitalWrite(IN_A_2, HIGH);
  } else { // right
    digitalWrite(IN_B_1, LOW);
    digitalWrite(IN_B_2, HIGH);
  }
}
