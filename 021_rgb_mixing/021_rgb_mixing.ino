// https://www.youtube.com/watch?v=kj2br03bOuk&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=21

// pin setup
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

String msg = "Select color [red,green,blue]: ";
String strInput;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(msg);

  while(Serial.available() == 0){
    // do nothing. wait
  }

  strInput = Serial.readString();

  if (strInput == "red") {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  } else if (strInput == "green") {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  } else if (strInput == "blue") {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  } else if (strInput == "orange") { /***/
    analogWrite(redPin, 255);
    analogWrite(greenPin, 165);
    analogWrite(bluePin, 0);
  } else if (strInput == "yellow") {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 100);
    analogWrite(bluePin, 0);
  } else if (strInput == "indigo") {
    analogWrite(redPin, 75);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 130);
  } else if (strInput == "violet") {
    analogWrite(redPin, 238);
    analogWrite(greenPin, 130);
    analogWrite(bluePin, 238);
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
}
