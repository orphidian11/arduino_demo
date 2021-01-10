// https://www.youtube.com/watch?v=6CRhpUV92ww&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=7

int pin = 9;
int maxBrightness = 255;
int minBrightness = 0;
int brightness = minBrightness; // 0 to 255
int delayMs = 50;
int increment = 1;

void setup() {
  pinMode(pin,OUTPUT);
}

void loop() {
  analogWrite(pin,brightness); 
  
  brightness = brightness + increment;

  if (brightness > maxBrightness){
    brightness = minBrightness;
  }

  delay(delayMs);
}
