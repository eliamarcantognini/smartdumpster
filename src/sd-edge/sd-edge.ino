#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "Light.h"
#include "Led.h"
#include "Potentiometer.h"
#include "config.h"

Light* L_avail; // Available status led.
Light* L_notAvail; // Not available status led.
Potentiometer* pot; // Potentiometer.

int code; // HTTP request code.
HTTPClient client; // Client for HTTP request.
const String server = ""; // Local IP address for connection to server.

float quantity; // Quantity of trash in dumpster.
boolean available; // Status of the dumpster.
DynamicJsonDocument doc(2048); // JSON document for parsing datas.

String line; // Saves datas of GET request.
String data = ""; // Loads datas for PUT request.

const float Wmax = W_MAX; // Limit of the dumpster capacity.

void setup() {
  L_avail = new Led(AV_PIN);
  L_notAvail = new Led(NAV_PIN);
  pot = new Potentiometer(POT_PIN);
  
  quantity = pot->getValue();
  available = true;

  Serial.begin(BAUD_RATE);
  
  connectWifi();
}

void loop() {
  delay(1000);
  if(WiFi.status() == WL_CONNECTED){
    if(pot->updateValue()){
      quantity = pot->getValue();
      available = quantity >= Wmax ? false : true;
      sendData();
    } else {
      getData();
      available = quantity >= Wmax ? false : doc["available"];
      sendData();
    }
  }
  switchLed();
}

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PWD);
  
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void sendData(){
  doc["available"] = available;
  doc["quantity"] = quantity;
  serializeJson(doc, data);
  client.begin("http://" + server + ":" + PORT + "/api/v1/status");
  client.addHeader("Content-Type", "application/json");
  // HTTP PUT request.
  code = client.PUT(data);
  if(code <= 0){
    Serial.print(code);
    Serial.println("PUT request error");
  }
  data = "";
  client.end();
}

void getData(){
  client.begin("http://" + server + ":" + PORT + "/api/v1/status");
  code = client.GET();
  // HTTP GET request.
  if(code != 200){
    Serial.println("GET request error");
  }
  line = client.getString();
  client.end();
  deserializeJson(doc, line);
  available = doc["available"];
  quantity = doc["quantity"];
}

void switchLed(){
  if (available){
    L_avail->switchOn();
    L_notAvail->switchOff();
  } else {
    L_avail->switchOff();
    L_notAvail->switchOn();
  }
}
