#include "EIoTCloudRestApi.h"
#include "EIoTCloudRestApiConfig.h"

#define INPUT_PIN D0
EIoTCloudRestApi eiotcloud;

bool oldInputState;

void setup() {
 Serial.begin(9600);
 eiotcloud.begin();

 pinMode(INPUT_PIN, INPUT_PULLUP);
 oldInputState = !digitalRead(INPUT_PIN);
   
}

void loop() {

  int inputState = digitalRead(INPUT_PIN); 
 
 if (inputState != oldInputState)
 {
   eiotcloud.sendParameter("57050077c943a0661cf314bc/uHIQBZexNqt7gyIq", (inputState == 1));
   oldInputState = inputState;
 }
}
