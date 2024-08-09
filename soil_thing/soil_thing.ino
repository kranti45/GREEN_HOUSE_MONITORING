#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Define the analog pin for the sensor
const int sensorPin = A0;

// WiFi credentials
const char* ssid = "KRANTI";
const char* password = "12345678";

// ThingSpeak settings
const char* server = "api.thingspeak.com";
const char* apiKey = "HY8I1Y3R6B2A01SB"; // Replace with your ThingSpeak Write API Key

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read the sensor value
  int sensorValue = analogRead(sensorPin);
  Serial.print("Soil Moisture Value: ");
  Serial.println(sensorValue);

  // Map the sensor value to percentage (0-100%)
  int moisturePercentage = map(sensorValue, 1023, 0, 0, 100);
  Serial.print("Soil Moisture Percentage: ");
  Serial.println(moisturePercentage);

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    if (client.connect(server, 80)) {
      String postStr = "api_key=";
      postStr += apiKey;
      postStr += "&field1=";
     postStr += String(moisturePercentage);
     //postStr += String(sensorValue);
      postStr += "\r\n\r\n";

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);

      Serial.print("Sent to ThingSpeak: ");
      Serial.println(postStr);
    }
    client.stop();
  }

  // Wait for a while before next reading
  delay(2000); // e.g., 20 sec
}
