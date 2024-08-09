#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const int sensorPin = D7; // Define the analog pin for the sensor

// WiFi credentials
/*const char* ssid = "KRANTI";
const char* password = "12345678";
*/
/*// Server settings (optional, if you want to send data)
const char* serverName = "http://example.com/update"; // Replace with your server URL
*/
void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  /*// Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");*/
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
/*
  // Optionally send data to server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Create the payload
    String httpRequestData = "moisture=" + String(moisturePercentage);
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }*/

  // Wait for a while before next reading
  delay(2000); // e.g., 1 minute
}
