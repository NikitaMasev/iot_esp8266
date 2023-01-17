#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

const char *ssid = "CrynetSystem";
const char *password = "gish4264";
const char *ipServer = "192.168.50.143";
const uint16_t port = 5080;

uint8_t cipher_key[16] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 53, 54, 49, 48, 49, 49 };
uint8_t cipher_iv[16] = { 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48 };

long lastTimeUpdateWebsocket;

void startWifi() {
  WiFiMulti.addAP(ssid, password);

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("Try connecting to WIFI");
    delay(1000);
  }
  Serial.println("WIFI CONNECTED");
  webSocket.begin(ipServer, port);
  lastTimeUpdateWebsocket = millis();
}

void networkLoop() {
  if (millis() - lastTimeUpdateWebsocket > 100) {
    webSocket.loop();
    lastTimeUpdateWebsocket = millis();
  }
}