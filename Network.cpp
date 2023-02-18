#include "Network.h"

Network::Network(String ssid, String pass, String serverAddress) {
  this->ssid = ssid;
  this->pass = pass;
  this->serverAddress = serverAddress;
  init();
}

Network::getConnectedState() {
  return iotServerConnected;
}

Network::getTimeRetryConnection() {
  return lastTimeRetryConnection;
}

Network::setup(String (*onConnected)(), String (*onMessage)(String data)) {
  this->onConnected = onConnected;
  this->onMessage = onMessage;

  WiFiMulti.addAP(ssid, password);

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("Try connecting to WIFI");
    delay(1000);
  }

  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);
  client.connect(serverAddress);
}

Network::onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    iotServerConnected = true;
    String dataForService = (*onConnected)();
    
    if (!dataForService.isEmpty()) {
      client.send(dataForService);
    }
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    iotServerConnected = false;
  } else if (event == WebsocketsEvent::GotPing) {
    client.pong();
  } else if (event == WebsocketsEvent::GotPong) {
    client.ping();
  }
}

Network::onMessageCallback(WebsocketsMessage message) {
  String dataForService = (*onMessage)(message.data());

  if (!dataForService.isEmpty()) {
    client.send(dataForService);
  }
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