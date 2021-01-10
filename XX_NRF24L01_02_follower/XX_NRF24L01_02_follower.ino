/**
 * NRF24L01 Follower
 * Receives instructions from leader and sends response
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
#define BUZZ_PIN 7

const int BUZZ_US = 900; // microsecond interval
const int BUZZ_DURATION = 500;// buzz duration

RH_NRF24 driver;
RHReliableDatagram nrf24(driver, FOLLOWER_ADDRESS);

void setup() {
  Serial.begin(9600);
  
  if (!nrf24.init()) Serial.println("init failed");

  Serial.println("BEGIN NRF24L01 FOLLOWER");
}

void loop() {
  if (nrf24.available()){
    // varriable for holding command
    // expected structure: 0: direction, 1: speed, 2: duration
    uint8_t cmd[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t cmdLen = sizeof(cmd);
    uint8_t from;

    if (nrf24.recvfromAck(cmd, &cmdLen, &from)){
      Serial.print("dir: " + String(cmd[0])); // Serial.print("dir: "); // 
      Serial.print(" / spd: " + String(cmd[1])); // Serial.print(" / spd: "); // 
      Serial.println(" / dur: " + String(cmd[2])); // Serial.println(" / dur: "); // 
//      emitBuzzer();
    }

    // note: check if a response can be sent even if no command was received
    // response to be sent
    uint8_t resp[4];
    resp[0] = 255; // speed [0-255]
    resp[1] = 100; // distance [0-*]
    resp[2] = 255; // voltage [0-255]
    resp[3] = 125; // current [0-255]

    if (!nrf24.sendtoWait(resp, sizeof(resp), from)){
      Serial.println("Failed sending response");
    } else {
//      Serial.println("Response sent");
    }
  }

}

void emitBuzzer(){
  int currMs;
  int startMs = millis();
  do {
    digitalWrite(BUZZ_PIN, HIGH);
    delayMicroseconds(BUZZ_US);
    digitalWrite(BUZZ_PIN, LOW);
    delayMicroseconds(BUZZ_US);
    currMs = millis();
    Serial.println("emitBuzzer " + String(currMs - startMs) + " / " + String(BUZZ_DURATION));
  } while ((currMs - startMs) < BUZZ_DURATION);
}
