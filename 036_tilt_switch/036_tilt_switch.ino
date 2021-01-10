/**
 * https://www.youtube.com/watch?v=SYDuRyweeLA&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=36
 * 
 * Tilt Switch / Ball Switch
 * Right side up (closed switch) => 0
 * Up side down (open switch) => 1
 */

#define READ_PIN 4
#define RED_PIN 9
#define GREEN_PIN 8

int readV;

void setup() {
  // put your setup code here, to run once:
  pinMode(READ_PIN, INPUT_PULLUP);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readV = digitalRead(READ_PIN);

  Serial.println(readV);

  if (readV == 1) { 
    // upside down
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
  } else {
    // right side up
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  }
}
