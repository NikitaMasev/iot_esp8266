#pragma once

#include "CryptoAesUtil.h"
#include "IotNetwork.h"
#include "WString.h"
#include "DataTypes.h"

class CryptoNetwork {
private:
  IotNetwork iotNetwork;
  CryptoAesUtil cryptoAesUtil;
public:
  CryptoNetwork(IotNetwork iotNetwork, CryptoAesUtil cryptoAesUtil) : iotNetwork(iotNetwork), cryptoAesUtil(cryptoAesUtil) {};
  long getTimeRetryConnection();
  bool getConnectedState();
  void setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage);
  void tick();
  void reconnect();
  void send(String data);
};