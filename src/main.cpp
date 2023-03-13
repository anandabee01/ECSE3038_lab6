#include <Arduino.h>
#include <Wifi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//#include "env.h" 

#define fanPin 22
#define lightPin 23

#define endpoint // put render api link here""

float getTemp(){

  return random(21.1, 33.1);
}

void setup() {
  
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("");

  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("");
    Serial.println("");
    HTTPClient http;
  
    String http = "https://" + String(endpoint) + "/api/state";
    http.begin(http);
    http.addHeader("Content-type", "application/json");
    http.addHeader("Content-length", "23");

    StaticJsonDocument<1024> docput;
    String httpRequestData;

    doc["temperature"] = getTemp(); 
    
    serializeJson(docput, httpRequestData);

    int httpResponseCode = http.PUT(httpRequestData);
    String http_response;

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      Serial.print("HTTP Response from server: ");
      http_response = http.getString();
      Serial.println(http_response);
    }

    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();    
    http.begin(url);
    httpResponseCode = http.GET();

    Serial.println("");
    Serial.println("");

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      Serial.print("HTTP Response from server: ");
      http_response = http.getString();
      Serial.println(http_response);
    }
    
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
 
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, http_response);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());

      return;
    }
    
    bool fan = doc["fan"]; 
    bool light = doc["light"]; 

    digitalWrite(fanPin, temp);

    digitalWrite(lightPin, temp);
 
    http.end();

    delay(2000);
  }

  else {
    Serial.println("WiFi Disconnected");
  }
}