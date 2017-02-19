#include <ESP8266WiFi.h>

const char* ssid     = "ssid"; // wifi SSID
const char* password = "password"; // wifi password

void setup() {

  Serial.begin(115200);  //Set Serial to 115200

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

}

