#include "IotNetwork.h"
#include "Arduino.h"

bool IotNetwork::getConnectedState() {
  return iotServerConnected;
}

long IotNetwork::getTimeRetryConnection() {
  return lastTimeRetryConnection;
}

void IotNetwork::setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage) {
  lastTimeRetryConnection = millis();
  WiFiMulti.addAP(ssid.c_str(), pass.c_str());

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("Try connecting to WIFI");
    delay(1000);
  }

  Serial.println("WIFI CONNECTED");

  client.onMessage([callbackMessage, this](WebsocketsMessage message) {
    Serial.println("IotNetwork onMessage BEFORE callbackMessage");
    String dataForService = callbackMessage(message.data());
    Serial.println("IotNetwork onMessage AFTER callbackMessage");

    if (!dataForService.isEmpty()) {
      client.send(dataForService);
    }
  });

  client.onEvent([callbackConnected, this](WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
      Serial.println("IotNetwork AFTER WebsocketsEvent::ConnectionOpened");
      iotServerConnected = true;
      String dataForService = callbackConnected();
      Serial.println("IotNetwork AFTER callbackConnected");
      Serial.println(dataForService);

      if (!dataForService.isEmpty()) {
        Serial.println("IotNetwork BEFORE client.send");
        client.send(dataForService);
        Serial.println("IotNetwork AFTER client.send");
      }
    } else if (event == WebsocketsEvent::ConnectionClosed) {
      Serial.println("IotNetwork WebsocketsEvent::ConnectionClosed");
      iotServerConnected = false;
    } else if (event == WebsocketsEvent::GotPing) {
      Serial.println("IotNetwork WebsocketsEvent::GotPing");
      client.pong();
    } else if (event == WebsocketsEvent::GotPong) {
      Serial.println("IotNetwork WebsocketsEvent::GotPong");
      client.ping();
    }
  });

  client.connect(serverAddress);
  lastTimeRetryConnection = millis();
}

void IotNetwork::tick() {
  if (iotServerConnected) {
    client.poll();
  } else if (millis() - lastTimeRetryConnection > TIME_RETRY_CONNECTION) {
    client.connect(serverAddress);
    lastTimeRetryConnection = millis();
  }
}

void IotNetwork::reconnect() {
  client.connect(serverAddress);
}

void IotNetwork::send(String data) {
  client.send(data);
}