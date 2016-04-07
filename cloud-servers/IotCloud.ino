#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>

EIoTCloudRestApi eiotcloud;

void setup() {
  Serial.begin(9600);
  eiotcloud.begin();
}

void loop() {
  
  int sound = digitalRead(D0);
  int light = analogRead(A0);
  
  eiotcloud.sendParameter("5704fefec943a0661cf314bb/3Djm9UlaIeiRtqQn", sound);
  eiotcloud.sendParameter("5704fefec943a0661cf314bb/YH1hPBkdnwuiNJzh", light);
      
  Serial.println(sound);
  Serial.println(light);
  delay(20);
  }
