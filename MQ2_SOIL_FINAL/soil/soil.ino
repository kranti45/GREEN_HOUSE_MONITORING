#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include<ESP8266WebServer.h>
#include<ESP8266HTTPClient.h>
#define LED1PIN D1 // GPIO pin for LED
#define LED2PIN D2 // GPIO pin for Buzzer

// Replace with your network credentials
const char* ssid = "KRANTI";
const char* password = "12345678";

// Replace with your ThingSpeak credentials
const unsigned long channelID = 2594057;
const char* writeAPIKey = "HY8I1Y3R6B2A01SB";

// Create an instance of the WiFiClient
WiFiClient client;

void setup() {
  //pinMode(LED_PIN, OUTPUT);
  //pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(115200);
   pinMode(LED1PIN, OUTPUT);
  pinMode(LED2PIN, OUTPUT);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read soil moisture sensor value (analog)
  int soilMoistureValue = analogRead(A0);
  
  // Read MQ2 gas sensor value (digital)
  int mq2Value = digitalRead(D3);

  // Print values to Serial Monitor
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);
  Serial.print("MQ2 Digital Value: ");
  Serial.println(mq2Value);
  if (soilMoistureValue <400 ) {
    digitalWrite(LED1PIN, LOW); // Turn LED ON
  } 
  else {
    digitalWrite(LED1PIN, HIGH); // Turn LED OFF
  }
  if (mq2Value == 1) {
    digitalWrite(LED2PIN, HIGH); // Turn Buzzer ON
  } 
  else {
    digitalWrite(LED2PIN, LOW); // Turn Buzzer OFF
  }

  // Write values to ThingSpeak
  ThingSpeak.setField(1, soilMoistureValue);
  ThingSpeak.setField(2, mq2Value);

  // Update ThingSpeak
  int responseCode = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (responseCode == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(responseCode));
  }
   String body = "{\"soil_moisture\": "+String(soilMoistureValue)+",\"MQ2\": "+String(mq2Value)+"}";
  Serial.println("JSON object" + body);
  WiFiClient client;
  HTTPClient httpclient;

  httpclient.begin(client,"http://192.168.176.82:3000/readingdata");
  httpclient.addHeader("Content-type","application/JSON");

  int status=httpclient.POST(body);

  Serial.println("Status:" +String(status));
  
  // Wait 20 seconds to avoid exceeding ThingSpeak rate limits
  delay(1000);
}
