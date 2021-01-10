/**
 * HC-12 + Hardware Serial
 * 
 * Transmitter
 * Capture potentiometer readings, convert to angle value between 0 to 180, 
 * and transmit via hardware serial ports connected to HC-12
 */

#define POT_PIN A1

const int potValMin = 0;
const int potValMax = 1023;
const float angleValMin = 1;
const float angleValMax = 179;
const int txDelayMs = 50;

int potVal;
float angleVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(POT_PIN);
  angleVal = map(potVal, potValMin, potValMax, angleValMin, angleValMax);
  
//  char helloWorld[11] = "Hello World";
//  Serial.write(helloWorld, sizeof(helloWorld));

//  Serial.print(String(potVal) + ">" + String(angleVal));
  Serial.print("[" + String(angleVal) + "]");
  delay(txDelayMs);
}
