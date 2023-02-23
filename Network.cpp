#include "Network.h"

bool Network::getConnectedState() {
  return iotServerConnected;
}

long Network::getTimeRetryConnection() {
  return lastTimeRetryConnection;
}

void Network::setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage) {
  // client.onMessage([callbackMessage, this](WebsocketsMessage message) {
  //   String dataForService = callbackMessage(message.data());

  //   if (!dataForService.isEmpty()) {
  //     client.send(dataForService);
  //   }
  // });

  // client.onEvent([callbackConnected, this](WebsocketsEvent event, String data) {
  //   if (event == WebsocketsEvent::ConnectionOpened) {
  //     iotServerConnected = true;
  //     String dataForService = callbackConnected();

  //     if (!dataForService.isEmpty()) {
  //       client.send(dataForService);
  //     }
  //   } else if (event == WebsocketsEvent::ConnectionClosed) {
  //     iotServerConnected = false;
  //   } else if (event == WebsocketsEvent::GotPing) {
  //     client.pong();
  //   } else if (event == WebsocketsEvent::GotPong) {
  //     client.ping();
  //   }
  // });

  // WiFiMulti.addAP(ssid.c_str(), pass.c_str());

  // while (WiFiMulti.run() != WL_CONNECTED) {
  //   Serial.println("Try connecting to WIFI");
  //   delay(1000);
  // }

  // client.connect(serverAddress);
}

void Network::tick() {
  // if (iotServerConnected) {
  //   client.poll();
  // } else if (millis() - lastTimeRetryConnection > TIME_RETRY_CONNECTION) {
  //   client.connect(serverAddress);
  //   lastTimeRetryConnection = millis();
  // }
}

void Network::reconnect() {
  //client.connect(serverAddress);
}

void Network::send(String data) {
  //client.send(data);
}