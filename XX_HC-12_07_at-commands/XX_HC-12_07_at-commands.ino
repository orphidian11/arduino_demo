/**
 * https://www.youtube.com/watch?v=0PyHYLAKfnQ
 * 
 * HC-12 
 * AT Commands
 * 
 * NOTE:
 * Changes made to one HC-12 module should be applied to the other HC-12 
 * module to ensure that they still communicate
 * 
 * AT 
 * - HC-12 will respond OK. Means that you can transmit commands
 * 
 * AT+RX
 * - shows all current settings
 * Example:
 * OK+B9600 => baud rate
 * OK+RC001 => channel
 * OK+RP:+20dBm => power
 * OK+FU3 => mode
 * 
 * AT+DEFAULT
 * - reset HC-12 to default settings
 * 
 * AT+B{/\d+/}
 * - change baud rate (default is 9600). make sure that arduino code 
 * is also set to the same baud rate
 * Example:
 * AT+B115200 => baud rate set to 115200
 * 
 * AT+C{/\d{3}/}
 * - change channel. it is recommended to stay below channel 100
 * Example:
 * AT+C100
 * 
 * AT+FU{/[1-4]/}
 * - change transmission mode (1 to 4). 
 * 1 - low power
 * 2 - low power
 * 3 - default mode. can in theory reach 1 km range
 * 4 - can in theory reach 1.8 km range (will change baud rate to 1200)
 * 
 * AT+P{/[1-8]/}
 * - change transmission power (1 to 8)
 * Level           1   2   3   4   5   6   7   8
 * Transmit (dBm) -1   2   5   8  11  14  17  20
 * 
 * AT+R{/(B|C|F|P)/}
 * - check an individual value
 * B => baud rate
 * C => channel
 * F => mode
 * P => power
 * 
 * AT+U{/\d\w\d/}
 * - setting data bits, parity bits, and stop bits of UART communication
 * 
 * AT+V
 * - check firmware version
 * 
 * AT+SLEEP
 * - module enters sleep mode. this can be used when no wireless 
 * transmission, in order to save energy
 */

#include <SoftwareSerial.h>

#define RX 11 //Connect to the TX pin of the HC-12
#define TX 10 //Connect to the RX pin of the HC-12
// NOTE: Make sure thtat SET pin of HC-12 is set to GND

SoftwareSerial mySerial(RX, TX);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  while(!Serial);

  Serial.println("Input AT commands");
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
