// https://www.youtube.com/watch?v=fJWR7dBuc18&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP

int pin = 13; 

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT); // send signal to pin as output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin, HIGH); // send signal
  delay(250);
  digitalWrite(pin, LOW);
  delay(250);
  
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
  
  delay(2000);
}
