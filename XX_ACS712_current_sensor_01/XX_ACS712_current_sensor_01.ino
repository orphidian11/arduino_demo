/**
 * https://www.youtube.com/watch?v=t5C49Ma8g1s
 * ACS712 Current Sensor
 * with Voltage Sensor
 */

#define VSENSOR A3 // voltage sensor
#define CSENSOR A1 // ACS712 current sensor

const float vinMin = 0.;
const float vinMax = 1023.;
const float voutMin = 0.; // 0 volts
const float voutMax = 25.; // 25 volts

// reading for 0 amperes is 512
const float coutMin = -30.; // -30 amperes
const float coutMax = 30.; // 30 amperes
const float calibrateC = 2.;

void setup() {
  // put your setup code here, to run once:
  pinMode(VSENSOR, INPUT);
  pinMode(CSENSOR, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int vin = analogRead(VSENSOR);
  float vout = map(vin, vinMin, vinMax, voutMin, voutMax);

  int cin = analogRead(CSENSOR); // + calibrateC;
  float cout = map(cin, vinMin, vinMax, coutMin, coutMax); // use vinMin and vinMax since they are the same range

//  Serial.print(vin,2);
//  Serial.print("=>");
//  Serial.print(vout,2);
//  Serial.print(" V - ");
//  Serial.print(cin,2);
//  Serial.print("=>");
//  Serial.print(cout,2);
//  Serial.print(" A");
//  Serial.println();

//  Serial.println(String(vin) + "=>" + String(vout) + " V / " + String(cin) + "=>" + String(cout) + " A");
  
  char vinStr[10];
  char voutStr[10];
  char cinStr[10];
  char coutStr[10];
  
//  dtostrf(vin,10,2,vinStr); 
  dtostrf(vout,10,2,voutStr);
//  dtostrf(cin,10,2,cinStr); 
  dtostrf(cout,10,2,coutStr);
  
//  Serial.println(String(vinStr) + "=>" + String(voutStr) + " V / " + String(cinStr) + "=>" + String(coutStr) + " A");
  Serial.print(vin);
  Serial.print("=>");
  Serial.print(vout);
  Serial.print(" V - ");
  Serial.print(cin);
  Serial.print("=>");
  Serial.print(coutStr);
  Serial.print(" A");
  Serial.println();

  delay(50);
}
