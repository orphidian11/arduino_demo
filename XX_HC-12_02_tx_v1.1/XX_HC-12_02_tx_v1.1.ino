/**
 * HC-12 Demo
 * Range Testing
 * Transmitter
 * Send a message to the receiver
 * L = low sound
 * H = high sound
 */

const int TX_DELAY = 500;
const int H = 0;
const int L = 0;
const char TX_ARR[] = "HHHLLLHHHLLL";
const int TX_ARR_LEN = 12;
const unsigned long buzzDurationMs = 500;

int i;
unsigned long currDurationMs = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  i = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  // transmit
  Serial.write("Hello World");
  delay(TX_DELAY);
}
