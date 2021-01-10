// https://www.youtube.com/watch?v=7wKdxsvXAFo&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=14
/**
 * If no voltage, all LEDs off
 * If voltage <= 3, green ON
 * If voltage between 3 and 4, yellow ON
 * If voltage >= 4, red ON
 */

// pin setup
int readPin = A1;
int greenPin = 6;

// constants
float binMultiplier = (255./1023.);
int delayMs = 125;

// I/O
float vOut;
int pVal;
float ledVal;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  pinMode(greenPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  pVal = analogRead(readPin);
  ledVal = binMultiplier * pVal;

  analogWrite(greenPin, ledVal);
  
  Serial.println(ledVal);
  
  delay(delayMs);
}
