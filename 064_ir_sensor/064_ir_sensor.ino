/**
 * https://www.youtube.com/watch?v=Y2HC3bdFoPw&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=64
 * 
 * Infrared Sensor
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
 
#include <IRremote.h>
#define IR_PIN 10

const int delayMs = 250;

String irInput;
IRrecv ir(IR_PIN);
decode_results cmd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  ir.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  while(ir.decode(&cmd) == 0){
    // do nothing
  }
  
//  Serial.print(cmd.value,HEX);
//  Serial.print(":");
//  Serial.println(cmd.value);
//  delay(delayMs);
  
  ir.resume();

  switch(cmd.value){
    case 0xFFA25D:
      irInput = "ch-";
      break;
    case 0xFF629D:
      irInput = "ch";
      break;
    case 0xFFE21D:
      irInput = "ch+";
      break;
    case 0xFF22DD:
      irInput = "|<<";
      break;
    case 0xFF02FD:
      irInput = ">>|";
      break;
    case 0xFFC23D:
      irInput = ">||";
      break;
    case 0xFFE01F:
      irInput = "-";
      break;
    case 0xFFA857:
      irInput = "+";
      break;
    case 0xFF906F:
      irInput = "EQ";
      break;
    case 0xFF6897:
      irInput = "0";
      break;
    case 0xFF9867:
      irInput = "100+";
      break;
    case 0xFFB04F:
      irInput = "200+";
      break;
    case 0xFF30CF:
      irInput = "1";
      break;
    case 0xFF18E7:
      irInput = "2";
      break;
    case 0xFF7A85:
      irInput = "3";
      break;
    case 0xFF10EF:
      irInput = "4";
      break;
    case 0xFF38C7:
      irInput = "5";
      break;
    case 0xFF5AA5:
      irInput = "6";
      break;
    case 0xFF42BD:
      irInput = "7";
      break;
    case 0xFF4AB5:
      irInput = "8";
      break;
    case 0xFF52AD:
      irInput = "9";
      break;
  }
 
  Serial.print(cmd.value,HEX);
  Serial.print(":"); 
  Serial.println(irInput);
}
