#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";

void wifi_Setup(){
   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}

void fetchTimeData() {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, "http://10.0.0.16:5000/api/times");
  int httpResponseCode = http.GET();

  if (httpResponseCode == HTTP_CODE_OK) {
    response = http.getString();
    Serial.println("API Response:");
    Serial.println(response);

    DynamicJsonDocument jsonDoc(1024);
    deserializeJson(jsonDoc, response);

    int lastIndex = jsonDoc.size() - 1;
    JsonObject jsonObj = jsonDoc[lastIndex];
    heatingTime = jsonObj["Heating"].as<int>();
    lightLevelTime = jsonObj["Light_Level"].as<int>();
    activationTime = jsonObj["Activation"].as<int>();
    pauseTime = jsonObj["Pause"].as<int>();

  } else {
    Serial.println("Error fetching time data.");
  }

  http.end();
}