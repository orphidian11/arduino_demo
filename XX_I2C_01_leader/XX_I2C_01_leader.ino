/**
 * https://www.youtube.com/watch?v=PnG4fO5_vU4
 * I2C
 * Leader
 */

#include<Wire.h>

#define FOLLOWER_ADDR 9 // address of i2c follower
#define ANSWER_SIZE 5 // follower answer size

void setup() {
  // no parameters passed to indicate this is running
  // in leader mode
  Wire.begin();

  Serial.begin(9600);
  Serial.println("I2C Leader Demonstration");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  Serial.println("writing data to follower...");

  // write character to follower
  Wire.beginTransmission(FOLLOWER_ADDR);
  Wire.write(0);
  Wire.endTransmission();

  Serial.println("receiving data from follower...");

  // read response from follower
  // read back 5 characters
  Wire.requestFrom(FOLLOWER_ADDR, ANSWER_SIZE);
  String resp = "";
  while (Wire.available()){
    char b = Wire.read();
    resp += b;
  }

  Serial.print(resp);
}
