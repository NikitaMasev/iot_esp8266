#include "Network.h"

Network::Network(String ssid, String pass, String serverAddress) {
  this->ssid = ssid;
  this->pass = pass;
  this->serverAddress = serverAddress;
  init();
}

Network::setup(const MessageCallback onMessageCallback, const EventCallback onEventsCallback) {
  WiFiMulti.addAP(ssid, password);

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("Try connecting to WIFI");
    delay(1000);
  }

  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);
  client.connect(serverAddress);
}

Network::tick() {
  client.poll();
}

Network::reconnect() {
  client.connect(serverAddress);
}

Network::send(String data) {
  client.send(data);
}