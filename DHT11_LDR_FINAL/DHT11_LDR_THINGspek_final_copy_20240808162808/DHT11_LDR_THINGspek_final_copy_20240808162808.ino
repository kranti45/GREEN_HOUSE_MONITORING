#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>
#include<ESP8266WebServer.h>
#include<ESP8266HTTPClient.h>
#define DHTPIN D4     // DHT11 data pin
#define DHTTYPE DHT11 // DHT 11
//#define LED_PIN D2   // LED pin
//#define LED1_PIN D3   // LED pin
#define LED1PIN D1  // Pin where LED 1 is connected
#define LED2PIN D2  // Pin where LED 2 is connected


const char* ssid = "KRANTI";  // Replace with your network SSID
const char* password = "12345678";  // Replace with your network password

unsigned long myChannelNumber = 2578684;  // Replace with your ThingSpeak channel number
const char* myWriteAPIKey = "O4VI3R9SQQGVXJ6I";  // Replace with your ThingSpeak write API key

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);

float ldrValue,t,h;
String myStatus = "";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);

  dht.begin();
  
  pinMode(LED1PIN, OUTPUT);
  digitalWrite(LED1PIN, LOW); 
  pinMode(LED2PIN, OUTPUT);
  digitalWrite(LED2PIN, LOW);  // Ensure LED is off initially
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int ldrValue = analogRead(A0);
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }



 // Serial.println("ldrrd =" + String(ldrrd));
  Serial.print("humidity: "); Serial.print(h);
  Serial.print(" %\ttemperature: "); Serial.print(t);
  Serial.print(" *C\tldrrd: "); Serial.println(ldrValue);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.setField(3, ldrValue);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  if(x == 200){
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  // Control LED based on LDR value
  if (ldrValue >500) {  // Adjust the threshold value as needed
    digitalWrite(LED1PIN, HIGH); // Turn LED on
  } else {
    digitalWrite(LED1PIN, LOW);  
    }// Turn LED off
    // Control LED based on LDR value
  if (t>20.5) {  // Adjust the threshold value as needed
    digitalWrite(LED2PIN, HIGH); // Turn LED on
  } else {
    digitalWrite(LED2PIN, LOW);  // Turn LED off
  }
    
  String body = "{\"temperature\": "+String(t)+",\"humidity\": "+String(h)+",\"ldrrd\": "+String(ldrValue)+"}";
  Serial.println("JSON object" + body);
  WiFiClient client;
  HTTPClient httpclient;

  httpclient.begin(client,"http://192.168.176.82:3000/readingdata");
  httpclient.addHeader("Content-type","application/JSON");

  int status=httpclient.POST(body);

  Serial.println("Status:" +String(status));
  
  
  delay(1000);  // Wait for 20 seconds to update ThingSpeak
}
