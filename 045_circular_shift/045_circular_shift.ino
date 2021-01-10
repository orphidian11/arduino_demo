/**
 * https://www.youtube.com/watch?v=-WDO4mi2I68&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=45
 * 
 * Serial to Parallel Shift Register (74HC595)
 * Circular Shift Left and Right
 * CS Left = (byte / 128) + (byte * 2)
 * CS Right = (byte * 128) + (byte / 2)
 */

#define CLOCK_PIN 9 // SH_CP_PIN
#define LATCH_PIN 11 // ST_CP_PIN
#define DATA_PIN 12 // DS_PIN

byte ledValMin = 0x00;
byte ledValMax = 0xFF;
byte ledValInit = 0b10111111;
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

//  ledVal = (ledVal * 128) + (ledVal / 2); // CS Right = (byte * 128) + (byte / 2)
  ledVal = (ledVal / 128) + (ledVal * 2); // CS Left = (byte / 128) + (byte * 2)

  Serial.println(ledVal, BIN);
  delay(delayMs);
}
