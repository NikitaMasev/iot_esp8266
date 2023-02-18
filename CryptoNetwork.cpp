#include "CryptoNetwork.h"

CryptoNetwork::CryptoNetwork(Network network, CryptoAesUtil cryptoAesUtil) {
  this->network = network;
  this->cryptoAesUtil = cryptoAesUtil;
}

CryptoNetwork::getConnectedState() {
  return network.getConnectedState();
}

CryptoNetwork::getTimeRetryConnection() {
  return network.getTimeRetryConnection();
}

CryptoNetwork::setup(String (*onConnected)(), String (*onMessage)(String)) {
  this->onConnected = onConnected;
  this->onMessage = onMessage;
  network.setup(onConnectedProxy, onMessageProxy);
}

CryptoNetwork::onMessageProxy(String data) {
  if (data.isEmpty()) return;

  String dataForService = (*onMessage)(cryptoAesUtil.decrypt(data));

  if (!dataForService.isEmpty()) {
    String encr = cryptoAesUtil.encrypt(dataForService);
    network.send(encr);
  }
}

CryptoNetwork::onConnectedProxy() {
  String dataForService = (*onConnected)();

  if (!dataForService.isEmpty()) {
    String encr = cryptoAesUtil.encrypt(dataForService);
    network.send(encr);
  }
}

CryptoNetwork::tick() {
  network.tick();
}

CryptoNetwork::reconnect() {
  network.reconnect();
}

CryptoNetwork::send(String data) {
  network.send(data);
}