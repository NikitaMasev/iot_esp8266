#include "CryptoNetwork.h"
#include "Arduino.h"

bool CryptoNetwork::getConnectedState() {
  return iotNetwork.getConnectedState();
}

long CryptoNetwork::getTimeRetryConnection() {
  return iotNetwork.getTimeRetryConnection();
}

void CryptoNetwork::setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage) {
  iotNetwork.setup(
    [callbackConnected, this] {
      Serial.println("CryptoNetwork BEFORE callbackConnected");
      String dataForService = callbackConnected();
      Serial.println("CryptoNetwork AFTER callbackConnected");
      Serial.println(dataForService);
      
      if (!dataForService.isEmpty()) {
        Serial.println("CryptoNetwork !dataForService.isEmpty()");
        String encr = cryptoAesUtil.encrypt(dataForService);
        Serial.println("CryptoNetwork AFTER cryptoAesUtil.encrypt(dataForService)");
        return encr;
      } else {
        return empty;
      }
    },
    [callbackMessage, this](String data) {
      if (data.isEmpty()) return empty;

      String decrData = cryptoAesUtil.decrypt(data);
      String dataForService = callbackMessage(decrData);

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