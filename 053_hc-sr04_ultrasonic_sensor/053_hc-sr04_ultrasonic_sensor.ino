/**
 * https://www.youtube.com/watch?v=M-UKXCUI0rE&list=PLQJqki0RCuBsA2Gk_KRSY8kKNXzXGadHy&index=8&t=1210s
 * 
 * HC-SR04 Ultrasonic Sensor
 */

#define TRIG_PIN 8
#define ECHO_PIN 9

int pingMs = 0; // travel time of ping

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // create a wave ping
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  pingMs = pulseIn(ECHO_PIN, HIGH);

  delay(25);

  Serial.println(pingMs);
}
