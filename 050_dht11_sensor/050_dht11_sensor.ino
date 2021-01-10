/**
 * https://www.youtube.com/watch?v=-AvF2TsB2GI&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=50
 * 
 * DHT11 Temp and Humidity Sensor
 */

#include <DHT.h>
#define TYPE DHT11
#define SENSOR_PIN 2

const int delaySetup = 1000;

DHT sensor(SENSOR_PIN, TYPE);

float humidity;
float tempC;
float tempF;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensor.begin();
  delay(delaySetup); // wait for device to setup
}

void loop() {
  // put your main code here, to run repeatedly:
  
  humidity = sensor.readHumidity();
  tempC = sensor.readTemperature(); // celsius
  tempF = sensor.readTemperature(true); // farenheit

  Serial.print("h:");
  Serial.print(humidity);
  Serial.print(" / c:");
  Serial.print(tempC);
  Serial.print(" / f:");
  Serial.print(tempF);
  Serial.println();
}
