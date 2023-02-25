#include "CryptoNetwork.h"

bool CryptoNetwork::getConnectedState() {
  return iotNetwork.getConnectedState();
}

long CryptoNetwork::getTimeRetryConnection() {
  return iotNetwork.getTimeRetryConnection();
}

void CryptoNetwork::setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage) {
  iotNetwork.setup(
    [callbackConnected, this] {
      String dataForService = callbackConnected();

      if (!dataForService.isEmpty()) {
        String encr = cryptoAesUtil.encrypt(dataForService);
        return encr;
      } else {
        return empty;
      }
    },
    [callbackMessage, this](String data) {
      if (data.isEmpty()) return empty;

      String dataForService = callbackMessage(cryptoAesUtil.decrypt(data));

      if (!dataForService.isEmpty()) {
        String encr = cryptoAesUtil.encrypt(dataForService);
        return encr;
      } else {
        return empty;
      }
    });
}

void CryptoNetwork::tick() {
  iotNetwork.tick();
}

void CryptoNetwork::reconnect() {
  iotNetwork.reconnect();
}

void CryptoNetwork::send(String data) {
  String encr = cryptoAesUtil.encrypt(data);
  iotNetwork.send(encr);
}