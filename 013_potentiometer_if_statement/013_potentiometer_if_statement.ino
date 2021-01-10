// https://www.youtube.com/watch?v=ORNted-NgRM&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=13
/**
 * If no voltage, all LEDs off
 * If voltage <= 3, green ON
 * If voltage between 3 and 4, yellow ON
 * If voltage >= 4, red ON
 */

// pin setup
int readPin = A2;
int greenPin = 9;
int yellowPin = 10;
int redPin = 11;

// constants
float binMultiplier = (5./1023.);
int delayMs = 125;

// ranges
float greenMin = 0.;
float greenMax = 3.;
// yellow is in between greenMax and redMin
float redMin = 4.;

// I/O
float vOut;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  vOut = analogRead(readPin) * binMultiplier;
  
  Serial.print("vOut = ");
  Serial.println(vOut);

  if (vOut <= greenMin) { 
    // all are off
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
  } else if (vOut > greenMin && vOut <= greenMax) {
    // green on
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
  } else if (vOut > greenMax && vOut < redMin) {
    // yellow on
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, LOW);
  } else {
    // red on
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);
  }
  
  delay(delayMs);
}
