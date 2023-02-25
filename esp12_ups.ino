#include "CryptoAesUtil.h"
#include "IotNetwork.h"
#include "CryptoNetwork.h"
#include "DataConstruct.h"
#include "ModelDataConstruct.h"
#include "AuthDataConstruct.h"
#include "Persistent.h"
#include "AuthPersistent.h"
#include "ModelPersistent.h"
#include "DataParser.h"
#include "Tasker.h"
#include "IotModel.h"
#include "IotController.h"
#include "Config.h"

IotController *iotController;

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  CryptoAesUtil cryptoAesUtil(cipher_key, cipher_iv);
  IotNetwork iotNetwork(ssid, password, iotServer);
  CryptoNetwork cryptoNetwork(iotNetwork, cryptoAesUtil);

  DataConstruct dataConstruct;
  ModelDataConstruct modelDataConstruct(&dataConstruct);
  AuthDataConstruct authDataConstruct(&dataConstruct);

  Persistent persistent;
  AuthPersistent authPersistent(&persistent);
  ModelPersistent modelPersistent(&persistent);

  DataParser dataParser;
  Tasker tasker;

  IotModel iotModel(cryptoNetwork, &modelPersistent, tasker, &modelDataConstruct);
  iotController = new IotController(iotModel, &authPersistent, dataParser, &authDataConstruct);
  (*iotController).setup();
}

void loop() {
  (*iotController).tick();
}
