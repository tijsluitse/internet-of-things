// INCLUDES
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WIFI
const char* ssid = "iPhone van Tijs Luitse";  
const char* pass = "johannes";
WiFiClient  client;

// HOST 
const char* host = "www.tijsluitse.com";
String path = "/iot/eindopdracht/waste.json";
const int httpPort = 80;

// LEDS
int led1 = D6;
int led2 = D7;
int led3 = D8;

// DISTANCE
int trigPin = D0;
int echoPin = D1;

// BUZZER
int buzzer = D2;
int sound = 250;

void setup() {

  // SETUP PINMODES
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  // CONNECTING TO WIFI
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
}

void loop() {

  // DISTANCE 
  int duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(200); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration) / 58.2;
  Serial.print ("distance ");
  Serial.println (distance);
  delay(500);

  // WASTE
  String waste;
  
  // GET
  HTTPClient http;

  http.begin("http://tijsluitse.com/iot/eindopdracht/output.txt"); 
  int httpCode = http.GET();        
  String payload = http.getString();

  Serial.println("Server: " + payload);

    if (distance > 70 && distance < 1100) {  
     waste = "0";     
     digitalWrite(led1, LOW); 
     digitalWrite(led2, LOW);
     digitalWrite(led3, LOW); 
     Serial.println("Out of range");
     sound = 1;
     tone(buzzer, sound);
    }
    if (distance > 50 && distance < 70) {
     waste = "1";
     digitalWrite(led1, HIGH); 
     digitalWrite(led2, LOW);
     digitalWrite(led3, LOW);
     Serial.println("Empty");
     if (payload == "on") {
      sound = 50;
      tone(buzzer, sound);
     } else {
      noTone(buzzer);
     }
    }  
    if (distance > 20 && distance < 50) {
     waste = "2";
     digitalWrite(led1, LOW); 
     digitalWrite(led2, HIGH);
     digitalWrite(led3, LOW); 
     Serial.println("Almost full");
     if (payload == "on") {
      sound = 100;
      tone(buzzer, sound);
     } else {
      noTone(buzzer);
     }
    }  
    if (distance > 0 && distance < 20) {  
     waste = "4";     
     digitalWrite(led1, LOW); 
     digitalWrite(led2, LOW);
     digitalWrite(led3, HIGH); 
     Serial.println("Full");
     if (payload == "on") {
      sound = 250;
      tone(buzzer, sound);
     } else {
      noTone(buzzer);
     }
    }

 // POST
 String data;

 data = "waste="+waste;
 if (client.connect("www.tijsluitse.com", 80)) {
   client.println("POST /iot/eindopdracht/index.php HTTP/1.1");
   client.println("Host: www.tijsluitse.com");
   client.println("Content-Type: application/x-www-form-urlencoded");
   client.println("Connection: close");
   client.print("Content-Length: ");
   client.println(data.length());
   client.println();
   client.print(data);
   client.println();
   Serial.println(data);
   Serial.println("Data send");
 } else {
   Serial.println("Something went wrong");
 }
     
  // wait .5s to reloop this loop
  delay(500);
}
