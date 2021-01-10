// https://www.youtube.com/watch?v=XWL6Ydsmi0s&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=29

/**
 * Dimmable LED
 * When red button is down, reduce LED brightness
 * When yellow button is down, increase LED brightness
 * Buzzer sound when minimum or maximum brightness is reached
 */

// pin setup
int redBtnPin = 3;
int yellowBtnPin = 4;
int redLedPin = 10;
int buzzPin = 9;

int redBtnRead;
int yellowBtnRead;
int redLedVInterval = 1;
int redLedV = 0;
int redLedMaxV = 255;
int redLedMinV = 0;
float buzzDelayMin = 60;
int buzzDelay = 100;
float factor = 9940./255.;

void setup() {
  // put your setup code here, to run once:
  pinMode(redBtnPin, INPUT);
  pinMode(yellowBtnPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  redBtnRead = digitalRead(redBtnPin);
  yellowBtnRead = digitalRead(yellowBtnPin);
      
  if (redBtnRead == 0) { // red button down
    if (redLedV <= redLedMinV) {
      Serial.println("BUZZ!!!");
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(buzzDelay);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(buzzDelay);
    } else {
      redLedV = redLedV - redLedVInterval;
    }
  } else if (yellowBtnRead == 0) { // yellow button down
    if (redLedV >= redLedMaxV) {
      Serial.println("BUZZ!!!");
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(buzzDelay);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(buzzDelay);
    } else {
      redLedV = redLedV + redLedVInterval;
    }
  }

  analogWrite(redLedPin, redLedV);

//  Serial.print("redBtnRead: ");
//  Serial.print(redBtnRead);
//  Serial.print(" / yellowBtnRead: ");
//  Serial.print(yellowBtnRead);
//  Serial.print(" / redLedV: ");
//  Serial.print(redLedV);
//  Serial.print(" / buzzDelay: ");
//  Serial.print(buzzDelay);
//  Serial.println();

   delay(1);
}

float computeBuzzDelay(int redLedV){
  return (factor * (redLedV - redLedMinV)) + buzzDelayMin;
}
