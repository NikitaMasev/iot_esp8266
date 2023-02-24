#pragma once

#include <ESP8266WiFiMulti.h>
#include <ArduinoWebsockets.h>
#include "DataTypes.h"
#include "WString.h"

#define TIME_RETRY_CONNECTION 10000

using namespace websockets;

class IotNetwork {
private:
  ESP8266WiFiMulti WiFiMulti;
  WebsocketsClient client;

  String ssid;
  String pass;
  String serverAddress;

  bool iotServerConnected = false;
  long lastTimeRetryConnection = 0;

public:
  IotNetwork(String ssid, String pass, String serverAddress)
    : ssid(ssid), pass(pass), serverAddress(serverAddress){};

  long getTimeRetryConnection();
  bool getConnectedState();

  void setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage);
  void tick();
  void reconnect();
  void send(String data);
};