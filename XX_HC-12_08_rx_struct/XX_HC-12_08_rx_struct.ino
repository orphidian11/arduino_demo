
#include <SoftwareSerial.h>

#define TX 10
#define RX 11

byte incomingByte;

// drive command structure
struct DriveCommand {
  int dir; // 0 - stop; 1 - forward; 2 - reverse; 3 - left; 4 - right
  int spd; // 0 to 255
  int durationMs; // in milliseconds
};

// telemetry structure 
struct Telemetry {
  DriveData drive;
  SensorData sensor;
};

SoftwareSerial hc12(TX,RX);

void setup() {
  hc12.begin(9600);
  Serial.begin(9600);
  Serial.println("RECEIVE STRUCT BEGIN!");
}

void loop() {
  while (hc12.available()){
    incomingByte = hc12.read();
  }

}
