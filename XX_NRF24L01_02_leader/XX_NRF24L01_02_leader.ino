/**
 * NRF24L01 Leader
 * Sends instructions to follower and recieves response
 * 
 * Pin Out
 * VCC - +5V
 * GND - GND
 * CE - 8
 * CSN - 10
 * SCK - 13
 * MOSI - 11
 * MISO - 12
 */

#include <RHReliableDatagram.h>
#include <SPI.h>
#include <RH_NRF24.h>

#define LEADER_ADDRESS 1
#define FOLLOWER_ADDRESS 2

const int RESPONSE_TIMEOUT = 100;
unsigned long prevMs = 0;

RH_NRF24 driver;
RHReliableDatagram nrf24(driver, LEADER_ADDRESS);

void setup() {
  Serial.begin(9600);
  
  if (!nrf24.init()) Serial.println("init failed");

  Serial.println("BEGIN NRF24L01 LEADER");
}

void loop() {
  // command to be sent
  uint8_t cmd[3]; 
  cmd[0] = 1; // direction
  cmd[1] = 255; // speed 
  cmd[2] = 100; // duration

  // send the command
  if (nrf24.sendtoWait(cmd, sizeof(cmd), FOLLOWER_ADDRESS)) {
//    Serial.println("Command sent");
  } else {
//    Serial.println("Failed sending command");
  }

  // variable for holding response
  // expected structure: 0: speed, 1: distance, 2: voltage, 3: current
  uint8_t resp[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t respLen = sizeof(resp);
  uint8_t from;

  if (nrf24.recvfromAckTimeout(resp, &respLen, RESPONSE_TIMEOUT, &from)){
    Serial.print("spd: " + String(resp[0])); // Serial.print("spd: "); // 
    Serial.print(" / dis: " + String(resp[1])); // Serial.print(" / dis: "); // 
    Serial.print(" / volt: " + String(resp[2])); // Serial.print(" / volt: "); // 
    Serial.print(" / amps: " + String(resp[3])); // Serial.println(" / amps: "); // 
    Serial.println(" (" + String(millis() - prevMs) + "ms)");

    prevMs = millis();
  } else {
//    Serial.println("No response received");
  }
}
