/**
 * https://www.youtube.com/watch?v=OXieoH5IsAI
 * Voltage Sensor
 */

#define VSENSOR A3

const float vinMin = 0.;
const float vinMax = 1023.;
const float voutMin = 0.;
const float voutMax = 25.;

void setup() {
  // put your setup code here, to run once:
  pinMode(VSENSOR, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float vin = analogRead(VSENSOR);
  float vout = map(vin, vinMin, vinMax, voutMin, voutMax);
  Serial.println(vout,4);
}
