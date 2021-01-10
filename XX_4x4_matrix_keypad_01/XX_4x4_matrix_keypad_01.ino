/**
 * https://www.youtube.com/watch?v=vl1-R6NsejM
 * 
 * 4x4 matrix keypad
 */
 
#include <Keypad.h>

#define C4 2
#define C3 3
#define C2 4
#define C1 5
#define R1 6
#define R2 7
#define R3 8
#define R4 9

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','x'},
  {'1','2','3','-'},
  {'=','0','.','+'}
};

byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3, C4};

Keypad kPad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char keyIn = kPad.getKey();

  if (keyIn){
    Serial.println(keyIn);
  }
}
