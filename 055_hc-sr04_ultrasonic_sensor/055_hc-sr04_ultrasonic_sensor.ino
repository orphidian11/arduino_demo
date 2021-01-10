/**
 * https://www.youtube.com/watch?v=2hwrDSVHQ-E&list=PLQJqki0RCuBsA2Gk_KRSY8kKNXzXGadHy&index=9
 * 
 * HC-SR04 Ultrasonic Sensor
 * Distance Measurement
 */

#define TRIG_PIN 8
#define ECHO_PIN 9

const int mps = 343; // speed of sound (m/s)
//float cmpus = (mps * 100) / 1000000; // cm/us

float pingUs; // travel time of ping (microseconds)
float distance; 

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

  pingUs = pulseIn(ECHO_PIN, HIGH);

  delay(25);

  distance = (mps * (pingUs / 1000000)) / 2; // distance = rate * time
//  Serial.println(String(mps) + "/" + String(pingUs) + "=" + String(distance) + " m");
  Serial.println(distance,4);
}
