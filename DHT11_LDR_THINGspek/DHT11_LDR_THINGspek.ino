#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

#define DHTPIN D4     // DHT11 data pin
#define DHTTYPE DHT11 // DHT 11
#define LED_PIN D2   // LED pin

const char* ssid = "KRANTI";  // Replace with your network SSID
const char* password = "12345678";  // Replace with your network password

unsigned long myChannelNumber = 2578684;  // Replace with your ThingSpeak channel number
const char* myWriteAPIKey = "O4VI3R9SQQGVXJ6I";  // Replace with your ThingSpeak write API key

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);

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
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Ensure LED is off initially
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int ldrValue = analogRead(A0);
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: "); Serial.print(h);
  Serial.print(" %\tTemperature: "); Serial.print(t);
  Serial.print(" *C\tLDR Value: "); Serial.println(ldrValue);

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
    digitalWrite(LED_PIN, HIGH); // Turn LED on
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn LED off
  }

  delay(1000);  // Wait for 20 seconds to update ThingSpeak
}
