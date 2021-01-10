// https://www.youtube.com/watch?v=YfV-vYT3yfQ&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=8
int pin = 9;
int brightness = 127; 

void setup() {
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(pin,brightness); 
}
