  #include <DHT.h>
#include <ESP8266WiFi.h>

#define DHTPIN D4       // DHT11 data pin connected to D4 (GPIO2)
#define DHTTYPE DHT11   // DHT 11
#define LEDPIN D2       // LED pin connected to D2 (GPIO4)
#define LDRPIN A0       // LDR pin connected to A0 (analog pin)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW); // Ensure LED is off initially
}

void loop() {
  // Read temperature and humidity from DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // Read light intensity from LDR
  int ldrValue = analogRead(LDRPIN);
  
  // Print sensor readings to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  
  // Control LED based on LDR value (adjust threshold as needed)
  if (ldrValue >1000) { // Example threshold for darkness
    digitalWrite(LEDPIN, HIGH); // Turn on LED
  } else {
    digitalWrite(LEDPIN, LOW); // Turn off LED
  }

  // Add a delay to avoid flooding the Serial Monitor
  delay(2000);
}
