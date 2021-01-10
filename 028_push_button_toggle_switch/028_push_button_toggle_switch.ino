// https://www.youtube.com/watch?v=aMato4olzi8&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=28

// pin setup
int ledPin = 8;
int inputPin = 12;
int inputVal;
int currVal = 1; // button up
int ledFlag = 0;
int delayMs = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
   
//  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputVal = digitalRead(inputPin);

  if (inputVal == 1 && currVal == 0){ 
//    Serial.println("switch!");
    if (ledFlag == 0) {
        digitalWrite(ledPin, HIGH);
        ledFlag = 1;
    } else {
        digitalWrite(ledPin, LOW);
        ledFlag = 0;
    }
  }
  
  currVal = inputVal;

//  Serial.print("inputVal : ");
//  Serial.print(inputVal);
//  Serial.print(" / currVal : ");
//  Serial.print(currVal);
//  Serial.print(" / ledFlag : ");
//  Serial.print(ledFlag);
//  Serial.println();
//  delay(delayMs);
}
