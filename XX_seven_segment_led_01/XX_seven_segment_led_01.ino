/**
 * https://www.youtube.com/watch?v=ZUXR7PjCPKI
 * 
 * 7-segment LED
 * Basic setup connecting to 7 pins in arduino board
 */

#define pinA 9
#define pinB 8
#define pinC 7
#define pinD 6
#define pinE 5
#define pinF 4
#define pinG 3

const int ctrMin = 0;
const int ctrMax = 9;
const int delayMs = 1000;

int ctr = ctrMin;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  switch(ctr){
    case 0:
      displayPins(1,1,1,1,1,1,0);
      break;
    case 1:
      displayPins(0,1,1,0,0,0,0);
      break;
    case 2:
      displayPins(1,1,0,1,1,0,1);
      break;
    case 3:
      displayPins(1,1,1,1,0,0,1);
      break;
    case 4:
      displayPins(0,1,1,0,0,1,1);
      break;
    case 5:
      displayPins(1,0,1,1,0,1,1);
      break;
    case 6:
      displayPins(1,0,1,1,1,1,1);
      break;
    case 7:
      displayPins(1,1,1,0,0,0,0);
      break;
    case 8:
      displayPins(1,1,1,1,1,1,1);
      break;
    case 9:
      displayPins(1,1,1,0,0,1,1);
      break;
  }

  ctr++;

  if (ctr > ctrMax){
    ctr = ctrMin;
  }

  delay(delayMs);
}

void displayPins(int a, int b, int c, int d, int e, int f, int g){
  
  if (a == 1){
    digitalWrite(pinA, HIGH);
  } else {
    digitalWrite(pinA, LOW);
  }
  
  if (b == 1){
    digitalWrite(pinB, HIGH);
  } else {
    digitalWrite(pinB, LOW);
  }
  
  if (c == 1){
    digitalWrite(pinC, HIGH);
  } else {
    digitalWrite(pinC, LOW);
  }
  
  if (d == 1){
    digitalWrite(pinD, HIGH);
  } else {
    digitalWrite(pinD, LOW);
  }
  
  if (e == 1){
    digitalWrite(pinE, HIGH);
  } else {
    digitalWrite(pinE, LOW);
  }
  
  if (f == 1){
    digitalWrite(pinF, HIGH);
  } else {
    digitalWrite(pinF, LOW);
  }
  
  if (g == 1){
    digitalWrite(pinG, HIGH);
  } else {
    digitalWrite(pinG, LOW);
  }
  
}
