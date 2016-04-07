#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

char ssid[] = "xxxxxxx";
char pass[] = "xxxxxxx";

int status = WL_IDLE_STATUS;
WiFiClient  client;

long myChannelNumber = 106593; 
const char * myWriteAPIKey = "4DAJFLIJIKI58W59"; 

void setup() {
  WiFi.begin(ssid, pass);  
  ThingSpeak.begin(client);
  Serial.begin(9600);
}

void loop() {
  int sound = digitalRead(D0);
  int light = analogRead(A0);

  ThingSpeak.setField(1,sound);
  ThingSpeak.setField(2,light);

  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  

  Serial.println(sound);
  Serial.println(light);
  delay(1000);
}


