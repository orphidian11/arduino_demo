/**
 * HC-12 Demo
 * Range Testing
 * Receiver
 * Produce a beep when a transmission is received
 * L = low sound
 * H = high sound
 */

#define BUZZ_PIN 9
 
const int H_US = 1000; // high microsecond delay
const int L_US = 100; // low microsecond delay
const unsigned long BUZZ_DURATION_MS = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUZZ_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // if data is received, send to serial monitor
  byte incomingByte;
  char txChar = 'X'; // default value
  while (Serial.available()){
    incomingByte = Serial.read();
    txChar = char(incomingByte);
    Serial.println(txChar);
  }

  switch(txChar){
    case 'H':
      buzz(H_US);
      break;
    case 'L':
      buzz(L_US);
      break;
    default:
      // do nothing
      break;
  }
}

void buzz(int buzzMs){
  if (buzzMs != 0){
    Serial.println(buzzMs);
    
    unsigned long beginMs = millis();
    while ((millis() - beginMs) < BUZZ_DURATION_MS){
      digitalWrite(BUZZ_PIN, HIGH);
      delayMicroseconds(buzzMs);
      digitalWrite(BUZZ_PIN, LOW);
      delayMicroseconds(buzzMs);
    }
  }
}
