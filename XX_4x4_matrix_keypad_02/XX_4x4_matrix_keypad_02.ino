/**
 * https://www.youtube.com/watch?v=vl1-R6NsejM
 * 
 * Digital calculator using
 * 4x4 matrix keypad plus
 * LCD with I2C
 */
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define C4 2
#define C3 3
#define C2 4
#define C1 5
#define R1 6
#define R2 7
#define R3 8
#define R4 9

// i2c to lcd pinout
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
// i2c adapter address
const int i2c_addr = 0x27;
const byte ROWS = 4;
const byte COLS = 4;

const char S1 = '7';
const char S2 = '8';
const char S3 = '9';
const char S4 = '/';

const char S5 = '4';
const char S6 = '5';
const char S7 = '6';
const char S8 = 'x';

const char S9 = '1';
const char S10 = '2';
const char S11 = '3';
const char S12 = '-';

const char S13 = '=';
const char S14 = '0';
const char S15 = 'C';
const char S16 = '+';

char keys[ROWS][COLS] = {
  { S1, S2, S3, S4},
  { S5, S6, S7, S8},
  { S9,S10,S11,S12},
  {S13,S14,S15,S16}
};

byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3, C4};

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
Keypad kPad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

float prevVal = 0.;
float inputVal = 0.;
float resVal = 0.;
int valLen = 0;
char eqEmpty = ' ';
char eqChar = eqEmpty;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  char keyIn = kPad.getKey();

  if (keyIn){
//    Serial.println(keyIn);
    lcd.clear();
  }

  switch(keyIn){
    case S1: case S2: case S3:
    case S5: case S6: case S7:
    case S9: case S10: case S11:
    case S14:
//      inputVal += charToNum(keyIn) * pow(10, valLen);
//      Serial.println(String(inputVal) + " = " + String(charToNum(keyIn)) + " * " + String(pow(10, valLen)) + " | valLen:" + String(valLen));
      
      inputVal = (inputVal * pow(10, valLen)) + charToNum(keyIn);
      valLen++;
      Serial.println("prevVal:" + String(prevVal) + " | inputVal:" + String(inputVal)); 
      break;
    case S4: case S8: case S12: case S16: // / x - +
      if (eqChar != eqEmpty){
        prevVal = computeVal(prevVal, inputVal, eqChar); 
      } else {
        if (inputVal != 0){
          prevVal = inputVal;  
        }
      }
      
      eqChar = keyIn;
      inputVal = 0;
      valLen = 0;
      Serial.println("prevVal:" + String(prevVal) + " | inputVal:" + String(inputVal)); 
      break;
    case S13: // =
      prevVal = computeVal(prevVal, inputVal, eqChar);
//      displayEquation();
      inputVal = 0;
      valLen = 0;
      eqChar = eqEmpty;
      Serial.println("prevVal:" + String(prevVal) + " | inputVal:" + String(inputVal)); 
      break;
    case S15: // C
      inputVal = prevVal = valLen = 0; // reset all
      eqChar = eqEmpty;
      break;
  }

  if (keyIn){
    lcd.clear();
    displayAll();
  }
  
  if (keyIn){
//    Serial.println("inputVal:" + String(inputVal) + " | prevVal:" + String(prevVal));
  }
}

float charToNum(char c){
  switch(c){
    case '1':
      return 1;
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case '4':
      return 4;
      break;
    case '5':
      return 5;
      break;
    case '6':
      return 6;
      break;
    case '7':
      return 7;
      break;
    case '8':
      return 8;
      break;
    case '9':
      return 9;
      break;
    case '0':
    default:
      return 0;
      break;
  }
}

void displayAll(){
//  lcd.clear();
  displayEquation();
  displayInput(inputVal);
}

void displayEquation(){
  lcd.setCursor(0,0);
  
  Serial.println(String(prevVal) + " " + eqChar + " " + String(inputVal));
  
  if (prevVal != 0. && eqChar != ' ' && inputVal != 0.){
    lcd.print(String(prevVal) + " " + eqChar + " " + String(inputVal));  
  } else if (prevVal != 0. && eqChar != ' ' && inputVal == 0.) {
    lcd.print(String(prevVal) + " " + eqChar);  
  } else if (prevVal != 0. && eqChar == ' ' && inputVal == 0.) {
    lcd.print(String(prevVal));  
//  } else if (prevVal == 0. && eqChar == ' ' && inputVal != 0.) {
//    lcd.print(String(inputVal));  
  }
  
}

void displayInput(float inputVal){
    lcd.setCursor(0,1);
    if (inputVal != 0.){
      lcd.print(inputVal); 
    }
}

float computeVal(float val1, float val2, char oper){
  switch(oper){
    case S4: 
      Serial.println(String(val1) + " / " + String(val2));
      return val1 / val2;
      break;
    case S8:
      Serial.println(String(val1) + " * " + String(val2));
      return val1 * val2;
      break;
    case S12:
      Serial.println(String(val1) + " - " + String(val2));
      return val1 - val2;
      break;
    case S16:
      Serial.println(String(val1) + " + " + String(val2));
      return val1 + val2;
      break;
  }
}
