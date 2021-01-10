/**
 * https://www.youtube.com/watch?v=4BaDaGTUgIY&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=48
 * 
 * LCD Display with I2C bus
 * 
 * Note:
 * - I2C addres: 39 (0x27)
 * - SDA: A4, SCL: A5
 * - There are two possible i2c pin configurations:
 *   #1 - const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3
 *   #2 - const int en = 4, rw = 5, rs = 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3, bl = 7
 *   For your setup, use #1
 * - Troubleshooting for no display. Adjust potentiometer (blue dial at back of i2c) 
 *   https://forum.arduino.cc/index.php?topic=453497.msg3120006#msg3120006
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// i2c to lcd pinout
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// i2c adapter address
const int i2c_addr = 0x27;

int delayMs = 2000;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
//LiquidCrystal_I2C lcd(i2c_addr);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2); // 16 cols, 2 rows
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("hello world!");

  delay(delayMs);

  lcd.setCursor(0,1);
  lcd.clear();
  lcd.print("lorem ipsum");

  delay(delayMs);
}
