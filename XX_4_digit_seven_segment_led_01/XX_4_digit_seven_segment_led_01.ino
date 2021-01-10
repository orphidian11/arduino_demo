/**
 * https://www.youtube.com/watch?v=gesrM2J8VnY
 * 
 * 4-digit 7-segment LED using 74HC595 chip
 */

#define CLOCK_PIN 9 // SH_CP_PIN
#define LATCH_PIN 11 // ST_CP_PIN
#define DATA_PIN 12 // DS_PIN

const int ctrMin = 0;
const int ctrMax = 9;
const int delayMs = 1000;

int ctr = ctrMin;
byte ledSets[] = {
  0b1111110,
  0b0110000,
  0b1101101,
  0b1111001,
  0b0110011,
  0b1011011,
  0b1011111,
  0b1110000,
  0b1111111,
  0b1110011
};

void setup() {
  // put your setup code here, to run once:
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

//  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print(ctr);
//  Serial.print(":");
//  Serial.println(ledSets[ctr],BIN);

  displayDigit(ledSets[ctr]);

  ctr++;

  if (ctr > ctrMax){
    ctr = ctrMin;
  }

  delay(delayMs);
  
}

void displayDigit(byte ledByte){
  digitalWrite(LATCH_PIN, LOW); // latch down
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, ledByte);
  digitalWrite(LATCH_PIN, HIGH); // latch up
}
