/**
 * HC-12 Demo
 * Range Testing
 * Transmitter
 * Send a message to the receiver
 * L = low sound
 * H = high sound
 */

const int TX_DELAY = 500;
const char TX_ARR[] = "HHHLLL";
const int TX_ARR_LEN = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // transmit
  for (int i = 0; i < TX_ARR_LEN; i++){
    Serial.write(TX_ARR[i]);
    delay(TX_DELAY);
  }
}
