/**
 * https://www.youtube.com/watch?v=PnG4fO5_vU4
 * I2C
 * Follower
 */

#include<Wire.h>

#define FOLLOWER_ADDR 9 // address of i2c follower
#define ANSWER_SIZE 5 // follower answer size

String answer = "hello";

void setup() {
  // provide the FOLLOWER_ADDR to indicate that this will
  // run in follower mode
  Wire.begin(FOLLOWER_ADDR);

  // event handler function for onRequest event
  Wire.onRequest(requestEvent);

  // event handler function for onReceive event
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  Serial.println("I2C Follower Demonstration");
}

/**
 * Callback function for onReceive event
 */
void receiveEvent(){
  while (Wire.available()){
    byte x = Wire.read();
  }

  Serial.println("received!");
}

/**
 * Callback function for onRequest event
 */
void requestEvent(){
  byte response[ANSWER_SIZE];

  // convert the answer into an array
  for (byte i = 0; i < ANSWER_SIZE; i++){
    response[i] = (byte) answer.charAt(i);
  }

  // send response to master
  Wire.write(response, sizeof(response));

  Serial.println("responded!");
}

void loop() {
  delay(500);
}
