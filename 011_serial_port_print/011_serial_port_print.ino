//https://www.youtube.com/watch?v=b5kndEtAKl8&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=11

int j = 1;
int delayMs = 500;
String strOutput = "j = ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // baud rate
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.print(strOutput);
  Serial.println(strOutput + j);
  j = j + 1;
  delay(delayMs);
}
