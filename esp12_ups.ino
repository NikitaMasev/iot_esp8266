#include "CryptoAesUtil.h"
#include "Network.h"
#include "CryptoNetwork.h"
#include "DataConstruct.h"
#include "Persistent.h"
#include "DataParser.h"
#include "Tasker.h"
#include "IotModel.h"
#include "IotController.h"
#include "Config.h"

IotController *iotController;

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  CryptoAesUtil cryptoAesUtil(cipher_key, cipher_iv);
  Network network(ssid, password, iotServer);
  CryptoNetwork cryptoNetwork(network, cryptoAesUtil);

  DataConstruct dataConstruct;
  DataParser dataParser;
  Persistent persistent;

  Tasker tasker;
  IotModel iotModel(cryptoNetwork, &dataConstruct, &persistent, tasker);

  iotController = new IotController(iotModel, &persistent, dataParser, &dataConstruct);
  //IotController iotController(iotModel, &persistent, dataParser, &dataConstruct);
  (*iotController).setup();
  //setupIotController();
  //delay(1000);
  //setupNetwork();
}

void loop() {
  (*iotController).tick();
  //loopController();
}
