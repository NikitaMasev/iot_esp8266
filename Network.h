#pragma once

#include <ESP8266WiFiMulti.h>
#include <ArduinoWebsockets.h>

#define TIME_RETRY_CONNECTION 10000

using namespace websockets;

ESP8266WiFiMulti WiFiMulti;
WebsocketsClient client;

const char *ssid = "CrynetSystem";
const char *password = "gish4264";
const char *iotServer = "ws://192.168.50.143:5080";

bool iotServerConnected = false;
long lastTimeRetryConnection = 0;

void setupNetwork() {
  WiFiMulti.addAP(ssid, password);

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("Try connecting to WIFI");
    delay(1000);
  }
}

void networkLoop() {
  if (iotServerConnected) {
    client.poll();
  } else if (millis() - lastTimeRetryConnection > TIME_RETRY_CONNECTION) {
    client.connect(iotServer);
    lastTimeRetryConnection = millis();    
  }
}