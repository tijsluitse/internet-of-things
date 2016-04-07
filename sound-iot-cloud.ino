#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>

EIoTCloudRestApi eiotcloud;

void setup() {
  Serial.begin(9600);
    eiotcloud.begin();
}

void loop() {
  int sound = analogRead(A0);
  eiotcloud.sendParameter("5704fefec943a0661cf314bb/YH1hPBkdnwuiNJzh", sound);
    delay(20);
    Serial.println(sound);
}
