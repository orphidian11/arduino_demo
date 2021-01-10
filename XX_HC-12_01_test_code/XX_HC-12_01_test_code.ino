/**
 * http://www.electronicsfreak.net/hc-12-module-testing-code/
 * HC-12 Test Code
 */

// By Roee Bloch
// Just stamping every 10 seconds after 's' is pressed
/*Arduino Nano connection to Module:
 * Connect Power from Arduino Nano From 5V to Module VCC (use Diode 1N4148 to lower the voltage and protect Module)
 * Connect GND from Arduino Nano to Module GND
 * Connect Arduino Nano D10 to Module TXD will use MySerial for data-in to Module
 * Connect Arduino Nano D11 to Module RXD again we will use the MySerial command (Software Serial)
 * Connect in Module Between VCC to GND 100uF capacitor close as possible to Module Power Pins - This will improve performance of the Module
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int i=0;
char s;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  Serial.println("Hello starting in 5 seconds");
  mySerial.println("Hello starting in 5 seconds");
  
  delay(5000);
  
  Serial.println("Waiting for Pressing s ");
  mySerial.println("Waiting for Pressing s ");
}

void loop() {
  
  while(s!='s')
  {
  if (mySerial.available())
    {
       s=mySerial.read();
       if (s=='s')
       {
        Serial.println("Starting now ......");
        mySerial.println("Starting now ......");
       }     
    }
  }
  
   Serial.print("Passed: ");
   Serial.print(i);
   Serial.println(" Seconds ..");
   mySerial.print("Passed: ");
   mySerial.print(i);
   mySerial.println(" Seconds ..");
   i=i+1;
   delay(1000);
}
