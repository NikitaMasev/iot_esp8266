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

uint8_t cipher_key[16] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 53, 54, 49, 48, 49, 49 };
uint8_t cipher_iv[16] = { 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48 };

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