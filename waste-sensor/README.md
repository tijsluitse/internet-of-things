##Automatic waste meter:
In this manual I will explain how to build an automatic waste meter to measure the waste inside your bin. 

###Materials:
- Breadboard
- ESP8266 UMC
- Distance meter
- Buzzer
- 3 led's
- 3 resistors

###Setup
Connect the leds, distance sensor and buzzer to your ESP. I used the following setup. 

HC-SR04 Trig = D0
HC-SR04 Echo = D1
Buzzer = D2
Led 1 = D6
Led 2 = D7
Led 3 = D8

###Arduino
After connecting all the materials. We need to setup the arduino code. First of all you initialize all the wifi stuff and your materials. 

```
// INCLUDES
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WIFI
const char* ssid = "xxx";  
const char* pass = "xxx";
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
```

With the ESP8266 wifi drivers you are able to connect to the wifi. You need to replace these "xxx" with your own wifi network information. ```const char* ssid = "xxx"; const char* pass = "xxx";``` .

##Data file
To write data to the server you need to create a json file. ```[{time: "", waste: ""}]``` It will be an array with the time and the waste height. 

###Buzzer file
To check if the buzzer is on or off you need to create an output.txt file. The php code writes "on" or "off" to the text file, which the ESP reads. 

##Arduino loop
After initializing all the materials in the Arduino code you need to create the loop which will run after uploading the code to the ESP. 

```
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
	  http.begin("http://www.tijsluitse.com/iot/eindopdracht/output.txt"); 
	  int httpCode = http.GET();        
	  String payload = http.getString();

	  Serial.println("Server: " + payload);

	    if (distance > 70) {  
	     	waste = "0";     
	     	digitalWrite(led1, LOW); 
	     	digitalWrite(led2, LOW);
	     	digitalWrite(led3, LOW); 
	     	Serial.println("Out of range");
	     	sound = 0;
	     	tone(buzzer, sound);
	    }
	    if (distance > 50 && distance < 70) {
	     	waste = "1";
	     	digitalWrite(led1, HIGH); 
	     	digitalWrite(led2, LOW);
	     	digitalWrite(led3, LOW);
	     	Serial.println("Empty");
	     	sound = 50;
	     	tone(buzzer, sound);
	    }  
	    if (distance > 20 && distance < 50) {
	     	waste = "2";
	     	digitalWrite(led1, LOW); 
	     	digitalWrite(led2, HIGH);
	     	digitalWrite(led3, LOW); 
	     	Serial.println("Almost full");
	     	sound = 100;
	     	tone(buzzer, sound);
	    }  
	    if (distance > 0 && distance < 20) {  
	     	waste = "4";     
	     	digitalWrite(led1, LOW); 
	     	digitalWrite(led2, LOW);
	     	digitalWrite(led3, HIGH); 
	     	Serial.println("Full");
	     	sound = 250;
	     	tone(buzzer, sound);
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
```

You can see the GET and the POST parts after the comments. 









