#include "CryptoNetwork.h"

const String empty = "";

bool CryptoNetwork::getConnectedState() {
  return network.getConnectedState();
}

long CryptoNetwork::getTimeRetryConnection() {
  return network.getTimeRetryConnection();
}

void CryptoNetwork::setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage) {
  network.setup([callbackConnected, this] {
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
  network.tick();
}

void CryptoNetwork::reconnect() {
  network.reconnect();
}

void CryptoNetwork::send(String data) {
  String encr = cryptoAesUtil.encrypt(data);
  network.send(encr);
}