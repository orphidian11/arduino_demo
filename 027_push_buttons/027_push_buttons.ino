// https://www.youtube.com/watch?v=AgQW81zzR18&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=27

// pin setup
int ledPin = 8;
int inputPin = 12;
int inputVal;
int delayMs = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
   
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputVal = digitalRead(inputPin);
  
  // Serial.println(inputVal);
  //delay(delayMs);

  if (inputVal == 0) { // button down
    digitalWrite(ledPin, HIGH);
  } else { // button up
    digitalWrite(ledPin, LOW);
  }
}
