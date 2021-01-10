/**
 * https://www.youtube.com/watch?v=ep7uBz43fCI&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=51
 * 
 * DHT11 Temp and Humidity Sensor with LCD 
 */

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TYPE DHT11
#define SENSOR_PIN 2

const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3; // i2c to lcd pinout
const int i2c_addr = 0x27; // i2c adapter address
const int delaySetup = 250;

DHT sensor(SENSOR_PIN, TYPE);
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

float humidity;
float tempC;
float tempF;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2); // 16 cols, 2 rows
  sensor.begin();
  
  delay(delaySetup); // wait for device to setup
}

void loop() {
  // put your main code here, to run repeatedly:
  
  humidity = sensor.readHumidity();
  tempC = sensor.readTemperature(); // celsius
  tempF = sensor.readTemperature(true); // farenheit

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(humidity);

  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print((char) 223);
  lcd.print("C / ");
  lcd.print(tempF);
  lcd.print((char) 223);
  lcd.print("F");
}
