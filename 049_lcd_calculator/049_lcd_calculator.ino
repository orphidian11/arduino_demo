/**
 * https://www.youtube.com/watch?v=4BaDaGTUgIY&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=48
 * 
 * LCD Display with I2C bus
 * Calculator
 * 
 * Prompt user to input two values, then select an operation.
 * Display the equation and the result afterwards.
 * 
 * Note:
 * - I2C addres: 39 (0x27)
 * - There are two possible i2c pin configurations:
 *   #1 - const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3
 *   #2 - const int en = 4, rw = 5, rs = 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3, bl = 7
 *   For your setup, use #1
 * - Troubleshooting for no display. Adjust potentiometer (blue dial at back of i2c) 
 *   https://forum.arduino.cc/index.php?topic=453497.msg3120006#msg3120006
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RED_BTN 8
#define YEL_BTN 9
#define BLU_BTN 10

const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3; // i2c to lcd pinout
const int i2c_addr = 0x27; // i2c adapter address
const int delayMs = 250;
const int resetVal = 0;
const int maxVal = 9;
const int operMinVal = 0;
const int operMaxVal = 3;

int opPhase = 0; // 0: ask 1st val, 1: ask 2nd val, 2: ask oper, 3: show result
int redVal;
int yelVal;
int bluVal;
int prevBluVal = 1;

int val1 = 0; // 0 - 9
int val2 = 0; // 0 - 9
int opVal = 0; // 0: add , 1: subtract , 2: multiply , 3: divide
float result = 0; // final result
String opChar = "";

String q1 = "1st val (^|v|x)";
String q2 = "2nd val (^|v|x)";
String q3 = "Oper (^|v|x)";

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
//LiquidCrystal_I2C lcd(i2c_addr);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2); // 16 cols, 2 rows

  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(YEL_BTN, INPUT_PULLUP);
  pinMode(BLU_BTN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
//  Serial.print("opPhase: ");
//  Serial.print(opPhase);
//  Serial.print(" val1: ");
//  Serial.print(val1);
//  Serial.print(" val2: ");
//  Serial.print(val2);
//  Serial.print(" opVal: ");
//  Serial.print(opVal);
//  Serial.println();

  Serial.print("redVal:");
  Serial.print(redVal);
  Serial.print(" yelVal:");
  Serial.print(yelVal);
  Serial.print(" bluVal:");
  Serial.print(bluVal);
  Serial.print(" prevBluVal:");
  Serial.print(prevBluVal);
  Serial.println();
  
  // get user input
  redVal = digitalRead(RED_BTN); // up
  yelVal = digitalRead(YEL_BTN); // down
  bluVal = digitalRead(BLU_BTN); // select
  
  lcd.clear();
  
  switch(opPhase){
    case 0: // ask for the 1st value
      lcd.setCursor(0,0);
      lcd.print(q1);

      val1 = getInputVal(val1, redVal, yelVal);

      // show values
      lcd.setCursor(0,1);
      lcd.print(val1);
      break;
    case 2: // ask for the 2nd value
      lcd.setCursor(0,0);
      lcd.print(q2);

      val2 = getInputVal(val2, redVal, yelVal);

      // show values
      lcd.setCursor(0,1);
      lcd.print(val2);
      break;
    case 1: // ask for the operation
      lcd.setCursor(0,0);
      lcd.print(q3);

      opVal = getOperVal(opVal, redVal, yelVal);
      opChar = getOperChar(opVal);

      // show values
      lcd.setCursor(0,1);
      lcd.print(opChar);
      break;
    case 3:// compute the result
      result = computeResult(val1, val2, opVal);
      opChar = getOperChar(opVal);
      
      lcd.setCursor(0,0);
      lcd.print(val1);

      lcd.setCursor(2,0);
      lcd.print(opChar);

      lcd.setCursor(4,0);
      lcd.print(val2);

      lcd.setCursor(6,0);
      lcd.print("=");

      lcd.setCursor(8,0);
      lcd.print(result);
      
      break;
    default:
      val1 = val2 = opVal = result = opPhase = resetVal; 
      break;
  }

  if (bluVal == 1 && prevBluVal == 0){ // blue button press up
    // move to next phase
    Serial.println("move to next phase");
    opPhase++;
  }
  
  prevBluVal = bluVal;

  delay(delayMs);
}

int getInputVal(int val, int upBtn, int downBtn){
  if (upBtn == 0 && downBtn == 1) {
    val--; // decrement
    
    if (val < resetVal){
      val = resetVal;
    }
  } else if (upBtn == 1 && downBtn == 0) {
    val++; // increment

    if (val > maxVal){
      val = maxVal;
    }
  }

  return val;
}

int getOperVal(int val, int upBtn, int downBtn){
  if (upBtn == 0 && downBtn == 1) {
    val--; // decrement
    
    if (val < operMinVal){
      val = operMinVal;
    }
  } else if (upBtn == 1 && downBtn == 0) {
    val++; // increment

    if (val > operMaxVal){
      val = operMaxVal;
    }
  }

  return val;
}

String getOperChar(int val){
  String opChar = "";

  switch(val){
    case 0: // addition
      opChar = "+";
      break;
    case 1: // subtraction
      opChar = "-";
      break;
    case 2: // multiplication
      opChar = "*";
//      opChar = "×";
      break;
    case 3: // division
      opChar = "/";
//      opChar = "÷";
      break;
    default:
      opChar = "!";
  }

  return opChar;
}

float computeResult (int v1, int v2, int op){
  float res = 0;
  
  switch(op){
    case 0: // addition
      res = v1 + v2;
      break;
    case 1: // subtraction
      res = v1 - v2;
      break;
    case 2: // multiplication
      res = v1 * v2;
      break;
    case 3: // division
      res = v1 / v2;
      break;
  }

  return res;
}
