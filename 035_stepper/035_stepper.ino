#include <Stepper.h>

/**
 * https://www.youtube.com/watch?v=CEz1EeDlpbs&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=35
 */

// constants
#define pinIN1 7
#define pinIN2 6
#define pinIN3 5
#define pinIN4 4
#define pinBTN 2

const int steps = 2;
const int stepsPerRevo = 2048; // for ROHS 28BYJ-48 5V DC stepper motor
const int stepperSpeed = 10; // RPM
const int delayMs = 500; // ms

int btnPrevVal = 1;
int btnVal;
int rotationCW = 1;
int rotationCCW = -1;
int rotationDir = rotationCW;

// Stepper class constructor format
// Note that 3rd parameter is switched, which is not that intuitive
Stepper myStepper(stepsPerRevo, pinIN1, pinIN3, pinIN2, pinIN4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myStepper.setSpeed(stepperSpeed);
  pinMode(pinBTN, INPUT_PULLUP);
}

void loop() {
  btnVal = digitalRead(pinBTN);
  
//  Serial.print(btnVal);
//  Serial.print("-");
//  Serial.print(btnPrevVal);
//  Serial.print("-");
//  Serial.print(rotationDir);
//  Serial.println();
  
  if (btnVal != btnPrevVal){
    if (btnVal == 1){
      rotationDir = rotationDir * -1;
      Serial.print("rotationDir: ");
      Serial.println(rotationDir);
    }
    
    btnPrevVal = btnVal;
  }
  
  myStepper.step(steps * rotationDir);
}
