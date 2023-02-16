#pragma once

#include <ESP8266WiFiMulti.h>
#include <ArduinoWebsockets.h>
#include "WString.h"

#define TIME_RETRY_CONNECTION 10000

using namespace websockets;

class Network {
private:
  ESP8266WiFiMulti WiFiMulti;
  long lastTimeRetryConnection = 0;
  String serverAddress;
public:
  WebsocketsClient client;
  bool iotServerConnected = false;
  Network(String serverAddress);  
  void setup(const MessageCallback onMessageCallback, const EventCallback onEventsCallback);
  void tick();
  void reconnect();
};


void onMessageCallback(WebsocketsMessage message) {
  String decryptedData = cryptoAesUtil.decrypt(message.data());
  String dataForService = controlIncomingText(decryptedData);

  if (!dataForService.isEmpty()) {
    String encrypted = cryptoAesUtil.encrypt(dataForService);
    client.send(encrypted);
  }
}

void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    iotServerConnected = true;
    String dataForService = controlConnected();
    String encrypted = cryptoAesUtil.encrypt(dataForService);
    client.send(encrypted);
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    iotServerConnected = false;
  } else if (event == WebsocketsEvent::GotPing) {
    client.pong();
  } else if (event == WebsocketsEvent::GotPong) {
  }
}

void setupNetwork() {
  WiFiMulti.addAP(ssid, password);

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("Try connecting to WIFI");
    delay(1000);
  }

  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);
  client.connect(iotServer);
}

void networkLoop() {
  if (iotServerConnected) {
    client.poll();
  } else if (millis() - lastTimeRetryConnection > TIME_RETRY_CONNECTION) {
    client.connect(iotServer);
    lastTimeRetryConnection = millis();
  }
}
