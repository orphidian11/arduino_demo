/**
 * https://www.youtube.com/watch?v=PXRcdyHIT_g&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=46
 * 
 * Serial to Parallel Shift Register (74HC595)
 * Bit Flipper
 * Reverse position of bits by subtracting the value from 0xFF
 */

#define CLOCK_PIN 9 // SH_CP_PIN
#define LATCH_PIN 11 // ST_CP_PIN
#define DATA_PIN 12 // DS_PIN

byte ledValMin = 0x00;
byte ledValMax = 0xFF;
byte ledValInit = 0xA3;
byte ledVal = ledValInit;
int delayMs = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LATCH_PIN, LOW); // latch down
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, ledVal);
  digitalWrite(LATCH_PIN, HIGH); // latch up

  ledVal = ledValMax - ledVal;

  Serial.println(ledVal, BIN);
  delay(delayMs);
}
