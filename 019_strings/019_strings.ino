// https://www.youtube.com/watch?v=MAnAc_t0OrM&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=19

/**
 * Ask user what color LED to light up:
 * RED, YELLOW, GREEN
 */

// pin setup
int redPin = 8;
int yellowPin = 9;
int greenPin = 10;

String strInput;
String msgInput = "Select a color to light up [red,yellow,green]: ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(msgInput);

  while(Serial.available() == 0){
    // do nothing. wait
  }

  strInput = Serial.readString();

  if (strInput == "red") {
      digitalWrite(redPin, HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, LOW);
  } else if (strInput == "yellow") {
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, HIGH);
      digitalWrite(greenPin, LOW);
  } else if (strInput == "green") {
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, HIGH);
  } else {
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, LOW);
  }
}
