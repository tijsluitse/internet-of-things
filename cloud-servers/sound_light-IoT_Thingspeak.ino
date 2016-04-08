#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

// Declarations
int sound = digitalRead(D0);
int light = analogRead(A0);

// IoT
EIoTCloudRestApi eiotcloud;

// Thingspeak
const ssid[] = "iPhone van Tijs Luitse";
const pass[] = "johannes";

int status = WL_IDLE_STATUS;
WiFiClient  client;

long myChannelNumber = 106593; 
const char * myWriteAPIKey = "4DAJFLIJIKI58W59"; 

void setup() {
  
  WiFi.begin(ssid, pass);  
  ThingSpeak.begin(client);
  Serial.begin(9600);
  eiotcloud.begin();
  
}

void loop() {
 
  ThingSpeak.setField(1,sound);
  ThingSpeak.setField(2,light);

  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  eiotcloud.sendParameter("5704fefec943a0661cf314bb/3Djm9UlaIeiRtqQn", sound);
  eiotcloud.sendParameter("5704fefec943a0661cf314bb/YH1hPBkdnwuiNJzh", light);

  Serial.println(sound);
  Serial.println(light);
  delay(20);
  
}

