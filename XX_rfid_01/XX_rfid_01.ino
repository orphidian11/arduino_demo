/**
 * https://www.youtube.com/watch?v=gTQmLkwnUxk
 * 
 * RFID
 */

#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN);
const long timeout = 30000;

char* tagIds[100] = {}; // ideally, this list of IDs should come from a database!
int tagCtr = 0; // initally 0 because tagIds is empty
String tagId = ""; // global variable for tagId

bool readTag(long _timeout = timeout, bool useTimeout = false){
  bool successRead = false;
  
  unsigned long startTime = millis();
  unsigned long currTime = startTime;

//  Serial.println("scanning...");
  while (
      (!successRead && !useTimeout) || // unable to read
      (!successRead && ((currTime - startTime) < _timeout)) // unable to read but did not yet exceed timeout
    ){
    if (isTagPresent()) {
      successRead = getTagId();
    }
//    Serial.println("...");
  }

  return successRead;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  while(!Serial); // do not start until serial port is ready

  Serial.println(F("Please scan master tag..."));

  if (readTag()){
    tagIds[tagCtr] = strdup(tagId.c_str());
    Serial.println(F("Master tag set!"));
    Serial.println(tagIds[tagCtr]);
    tagCtr++;
  }

  promptToScan();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (isTagPresent()){
    getTagId();
    checkTagId();
  } else {
    delay(50);
  }
}

void promptToScan() {
    delay(1500);
    Serial.println();
    Serial.println(F("Please scan your tag..."));
}

bool isTagPresent() {
  bool isPresent = true;

//  Serial.print(rfid.PICC_IsNewCardPresent());
//  Serial.print(" / ");
//  Serial.println(rfid.PICC_ReadCardSerial());
  
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
//    Serial.println("XXX");
    isPresent = false;
  }

  return isPresent;
}

bool getTagId(){
  tagId = ""; // empty first the tagId

  Serial.print(F("UID: "));
  for (int i = 0; i < rfid.uid.size; i++){
    String _tmpTagId = (rfid.uid.uidByte[i] < 0x10 ? " 0" : " ") + rfid.uid.uidByte[i];
//    _tmpTagId.concat(rfid.uid.uidByte[i], HEX);

    Serial.print(_tmpTagId);

    tagId.concat(_tmpTagId);
  }

  tagId.toUpperCase();
  rfid.PICC_HaltA(); // stop reading

  return true;
}

void checkTagId(){
  byte tagIndex;
  
  if (tagId == tagIds[0]){ // this is the master tag
    Serial.println(F("==== ADMIN MODE ===="));
    Serial.println(F(" Add/Remove Tag"));

    if (readTag(timeout, true)){ // scan the next tag
      tagIndex = findTag(tagId);

      if (tagIndex != 0){ // an existing tag, but not the master tag
        tagIds[tagIndex] = '\0'; // remove the tagId
        Serial.println(F(" Tag removed"));
      } else { // tagId is not yet existing
        tagIds[tagCtr] = strdup(tagId.c_str());
        tagCtr++;
        Serial.println(F(" Tag enrolled"));
      }
    } else { // timeout
      Serial.println(F(" timeout"));
    }
  } else { // regular tag
      tagIndex = findTag(tagId);

      if (tagIndex != 0){
        Serial.println(F(" Access granted!"));
      } else {
        Serial.println(F(" Access denied!"));
      }
  }

  promptToScan();
}

byte findTag(String tagId){
  byte tagIndex = 0;

  for (int i = 1; i < 100; i++){
    if (tagId == tagIds[i]){
      tagIndex = i;
    }
  }

  return tagIndex;
}
