#pragma once

#include "CryptoAesUtil.h"
#include "Network.h"
#include "WString.h"
#include "DataTypes.h"

class CryptoNetwork {
private:
  Network network;
  CryptoAesUtil cryptoAesUtil;
public:
  CryptoNetwork(Network network, CryptoAesUtil cryptoAesUtil) : network(network), cryptoAesUtil(cryptoAesUtil) {};
  long getTimeRetryConnection();
  bool getConnectedState();
  void setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage);
  void tick();
  void reconnect();
  void send(String data);
};