#include <WiFi.h>
#include "time.h"


#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "kellywifi2";
const char* password = "nodetest001";
const char* serverUrl = "http://192.168.0.19:5000/airCon/setAirValues";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);

    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(1024);
    doc["deviceId"] = "mydev001";
    doc["temp"] = 22;
    doc["mois"] = 53;
    doc["illu"] = 1243;
    doc["tvoc"] = 2;
    doc["dust1"] = 4;
    doc["dust5"] = 5;
    doc["dust10"] = 6;

    String jsonString;
    serializeJson(doc, jsonString);
    Serial.println(jsonString);

    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    delay(5000);
  }
}
