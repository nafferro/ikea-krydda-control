#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid     = "ssid"; // wifi SSID
const char* password = "password"; // wifi password

const char* host = "data.sparkfun.com";
const char* publicKey = "sparkfunpublicKey";
const char* privateKey = "sparkfunprivateKey";

DHT dht(D6, DHT22); // digital pin we're connected and DHTYPE - DHT22

float humidity = 0.;
float temp = 0.;

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
  delay(5000);
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  humidity = dht.readHumidity();
  temp = dht.readTemperature();

 String url = "/input/";
  url += publicKey;
  url += "?private_key=";
  url += privateKey;
  url += "&humidity=";
  url += humidity;
  url += "&temp=";
  url += temp;

  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");

}








