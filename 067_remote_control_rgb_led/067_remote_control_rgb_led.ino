/**
 * https://www.youtube.com/watch?v=ZgGGJDsoeKE&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=67
 * 
 * Homework
 * Remote control RGB LED
 * 
 * ch+ - LED on (full brightness, white)
 * ch- - LED off
 * 1, 2, 3 - R, G, B
 * 4, 5, 6 - Cyan, Magenta, Yellow
 * 0 - White
 * - Dim
 * + Brighten
 * When switching between colors, retain the level of brightness
 * 
 * Codes:
 * ch-  FFA25D
 * ch   FF629D
 * ch+  FFE21D
 * |<<  FF22DD
 * >>|  FF02FD
 * >||  FFC23D
 *  -   FFE01F
 *  +   FFA857
 *  EQ  FF906F
 *   0  FF6897
 * 100+ FF9867
 * 200+ FFB04F
 *   1  FF30CF
 *   2  FF18E7
 *   3  FF7A85
 *   4  FF10EF
 *   5  FF38C7
 *   6  FF5AA5
 *   7  FF42BD
 *   8  FF4AB5
 *   9  FF52AD
 */
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#define IR_PIN 10
#define RED_PIN 6
#define GRN_PIN 5
#define BLU_PIN 9

const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3; // i2c to lcd pinout
const int i2c_addr = 0x27; // i2c adapter address
const int maxLedV = 255;
const int minLedV = 0;
const int delayMs = 100;

int redV = minLedV;
int grnV = minLedV;
int bluV = minLedV;
int redFinV;
int grnFinV;
int bluFinV;
int dimV = maxLedV; // dimness value. use this to subtract
int dimIntervalV = 5;

String irInput;
IRrecv ir(IR_PIN);
decode_results cmd;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup() {
  // put your setup code here, to run once:
  ir.enableIRIn();
  lcd.begin(16,2); // 16 cols, 2 rows
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GRN_PIN, OUTPUT);
  pinMode(BLU_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ir.decode(&cmd)){
    ir.resume();
    lcd.clear();

//    Serial.println(cmd.value, HEX);
    
    switch(cmd.value){
      case 0xFFA25D: // ch- - LED off
        redV = bluV = grnV = minLedV;
        dimV = maxLedV;
        break;
      case 0xFF629D: // ch
        break;
      case 0xFFE21D: // ch+ - LED on (full brightness, white)
        redV = bluV = grnV = maxLedV;
        dimV = minLedV;
        break;
      case 0xFF22DD: //|<<
        break;
      case 0xFF02FD: // >>|
        break;
      case 0xFFC23D: // >||
        break;
      case 0xFFE01F: // - Dim
        dimV = dimV + dimIntervalV;
  
        if (dimV > maxLedV){
          dimV = maxLedV;
        }
        break;
      case 0xFFA857: // + Brighten
        dimV = dimV - dimIntervalV;
  
        if (dimV < minLedV){
          dimV = minLedV;
        }
        break;
      case 0xFF906F: // E
        break;
      case 0xFF6897: // 0 White
        redV = maxLedV;
        bluV = maxLedV;
        grnV = maxLedV;      
        break;
      case 0xFF9867:
        irInput = "100+";
        break;
      case 0xFFB04F:
        irInput = "200+";
        break;
      case 0xFF30CF: // 1 Red
        redV = maxLedV;
        grnV = minLedV;
        bluV = minLedV;      
        break;
      case 0xFF18E7: // 2 Green
        redV = minLedV;
        grnV = maxLedV;
        bluV = minLedV;
        break;
      case 0xFF7A85: // 3 Blue
        redV = minLedV;
        grnV = minLedV;
        bluV = maxLedV;
        break;
      case 0xFF10EF: // 4 Cyan #00FFFF
        redV = minLedV;
        grnV = maxLedV;
        bluV = maxLedV;
        break;
      case 0xFF38C7: // 5 Magenta #FF00FF
        redV = maxLedV;
        grnV = minLedV;
        bluV = maxLedV;
        break;
      case 0xFF5AA5: // 6 Yellow #FFFF00
        redV = maxLedV;
        grnV = maxLedV;
        bluV = minLedV;
        break;
      case 0xFF42BD: // 7
        break;
      case 0xFF4AB5: // 8
        break;
      case 0xFF52AD: // 9
        break;
    }
  }

  redFinV = (redV - dimV) < minLedV ? minLedV : (redV - dimV);
  grnFinV = (grnV - dimV) < minLedV ? minLedV : (grnV - dimV);
  bluFinV = (bluV - dimV) < minLedV ? minLedV : (bluV - dimV);
  
  analogWrite(RED_PIN, redFinV);
  analogWrite(GRN_PIN, grnFinV);
  analogWrite(BLU_PIN, bluFinV);

  lcd.setCursor(0,0);
  lcd.print("RGB(" + String(redFinV) + "," + String(grnFinV) + "," + String(bluFinV) + ")");

  lcd.setCursor(0,1);
  lcd.print("Brightness: " + String(dimV));

  Serial.print("RGB(");
  Serial.print(redFinV);
  Serial.print(",");
  Serial.print(grnFinV);
  Serial.print(",");
  Serial.print(bluFinV);
  Serial.print(") / Dim:");
  Serial.print(dimV);
  Serial.println();

  delay(delayMs);
  
}
