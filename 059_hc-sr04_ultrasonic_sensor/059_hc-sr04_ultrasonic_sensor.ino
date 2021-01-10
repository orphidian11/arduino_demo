/**
 * https://www.youtube.com/watch?v=cEuzEPJnb5s&list=PLQJqki0RCuBsA2Gk_KRSY8kKNXzXGadHy&index=13
 * 
 * HC-SR04 Ultrasonic Sensor / LCD Display with I2C bus
 * Portable Distance Measurement
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 8
#define ECHO_PIN 9

// i2c to lcd pinout
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// i2c adapter address
const int i2c_addr = 0x27;

const int mps = 343; // speed of sound (m/s)

float pingUs; // travel time of ping (microseconds)
float distance; 

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  lcd.begin(16,2); // 16 cols, 2 rows

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // create a wave ping
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  pingUs = pulseIn(ECHO_PIN, HIGH);

  delay(25);

  distance = (mps * (pingUs / 1000000)) / 2; // distance = rate * time
  Serial.println(distance);
  
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(String(distance) + "m");
}
