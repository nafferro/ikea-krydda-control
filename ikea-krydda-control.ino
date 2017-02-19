#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid     = "ssid"; // wifi SSID
const char* password = "password"; // wifi password

DHT dht(D6, DHT22); // digital pin we're connected and DHTYPE - DHT22

float humidity = 0.;
float temperature = 0.;

void setup() {

  Serial.begin(115200);  //Set Serial to 115200
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wifi connected");
}

void loop() {

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  Serial.println("humidity");
  Serial.println(humidity);
  Serial.println("temperature");
  Serial.println(temperature);

  delay(1000);
}





