// https://www.youtube.com/watch?v=rTuKKVcYeMg&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=5
// homework: iterate from 0 to 15 and display them as binary in 4 LEDs

// pins
int pin0 = 2;
int pin1 = 3;
int pin2 = 4;
int pin3 = 5;

int pin0Flag = 0;
int pin1Flag = 0;
int pin2Flag = 0;
int pin3Flag = 0;

int i = 0;
int maxNum = 16;

int delaySec = 1000;
int delaySecBlink = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (i < maxNum) {
    switch(i){
      case 0:
        displayBinary(0,0,0,0);
        break;
      case 1:
        displayBinary(0,0,0,1);
        break;
      case 2:
        displayBinary(0,0,1,0);
        break;
      case 3:
        displayBinary(0,0,1,1);
        break;
      case 4:
        displayBinary(0,1,0,0);
        break;
      case 5:
        displayBinary(0,1,0,1);
        break;
      case 6:
        displayBinary(0,1,1,0);
        break;
      case 7:
        displayBinary(0,1,1,1);
        break;
      case 8:
        displayBinary(1,0,0,0);
        break;
      case 9:
        displayBinary(1,0,0,1);
        break;
      case 10:
        displayBinary(1,0,1,0);
        break;
      case 11:
        displayBinary(1,0,1,1);
        break;
      case 12:
        displayBinary(1,1,0,0);
        break;
      case 13:
        displayBinary(1,1,0,1);
        break;
      case 14:
        displayBinary(1,1,1,0);
        break;
      case 15:
        displayBinary(1,1,1,1);
        break;
    }
  }

  i++;

  delay(1000);

  if (i >= maxNum) {
    i = 0;
    displayBlink(3);
    displayReset();
  }
}

void displayReset(){
  displayClear();
}

void displayBlink(int x){
  for (int y = 0; y < x; y++){
    displayClear();
    delay(delaySecBlink);
    displayAll();
    delay(delaySecBlink);
    displayClear();
  }
}

void displayAll(){
    digitalWrite(pin0, HIGH);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
}

void displayClear(){
    digitalWrite(pin0, LOW);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
}

void displayBinary(int p0, int p1, int p2, int p3){
  if (p0 == 0) {
    digitalWrite(pin0, LOW);
  } else {
    digitalWrite(pin0, HIGH);
  }
  
  if (p1 == 0) {
    digitalWrite(pin1, LOW);
  } else {
    digitalWrite(pin1, HIGH);
  }
  
  if (p2 == 0) {
    digitalWrite(pin2, LOW);
  } else {
    digitalWrite(pin2, HIGH);
  }
  
  if (p3 == 0) {
    digitalWrite(pin3, LOW);
  } else {
    digitalWrite(pin3, HIGH);
  }
}
