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
//#include "IotController.h"
#include "Config.h"
#include "TypeDevice.h"

//IotController *iotController;
IotModel *iotModel;

const CryptoAesUtil cryptoAesUtil(cipher_key, cipher_iv);      //-
const IotNetwork iotNetwork(ssid, password, iotServer);        //-
const CryptoNetwork cryptoNetwork(iotNetwork, cryptoAesUtil);  //-

const DataConstruct dataConstruct = {};
const Persistent persistent = {};

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  Persistent persistent = {};

  ModelDataConstruct modelDataConstruct(dataConstruct);  //+
  AuthDataConstruct authDataConstruct(dataConstruct);

  AuthPersistent authPersistent(persistent);
  ModelPersistent modelPersistent(persistent);

  DataParser dataParser;
  Tasker tasker;  //-

  //IotModel iotModel(cryptoNetwork, modelPersistent, tasker, &modelDataConstruct);
  // iotController = new IotController(iotModel, authPersistent, dataParser, authDataConstruct);
  // (*iotController).setup();
  iotModel = new IotModel(cryptoNetwork, modelPersistent, tasker, modelDataConstruct);

  persistent.setup();

  (*iotModel).setup(
    [&authDataConstruct, &authPersistent]() {
      Serial.println("IotController::setup ONCONNECTED BEFORE (*persistent).getRegistered()");
      if (authPersistent.getRegistered()) {
        return authDataConstruct.constructAuth(authPersistent.getSavedId(), typeDeviceToString(currentTypeDevice));
      } else {
        return authDataConstruct.constructRegister(typeDeviceToString(currentTypeDevice));
      }
      return String("");
    },
    [&dataParser, &authPersistent, &authDataConstruct, iotModel](String data) {
      Serial.println("IotController::setup ONMESSAGE BEFORE dataParser.parseTextData(data)");
      ParsedHeaderPayload headerPayload = dataParser.parseTextData(data);
      Serial.println("IotController::setup ONMESSAGE AFTER dataParser.parseTextData(data)");

      if (headerPayload.header.isEmpty()) {
        return String("");
      }

      TypeControl typeControl = stringToTypeControl(headerPayload.header.c_str());

      if (typeControl == unknown_c || !allowedTypeControl(typeControl)) {
        return String("");
      }
      Serial.println("IotController::setup ONMESSAGE typeControl");
      Serial.println(typeControl);
      switch (typeControl) {
        case register_c:
          {
            int newId = headerPayload.payload.toInt();
            Serial.println("newId");
            Serial.println(newId);
            authPersistent.saveId(newId);
            return String("");
          }
        case reset_c:
          {
            authPersistent.saveId(-1);
            return authDataConstruct.constructRegister(typeDeviceToString(currentTypeDevice));
          }
        case powerOff_c:
          {
            iotModel->updatePower(false);
            return String("");
          }
        case powerOn_c:
          {
            iotModel->updatePower(false);
            return String("");
          }
        case rgba_c:
        case rgbaEffects_c:
          {
            LedConfigData parsedLedConfig = dataParser.parseLedConfig(headerPayload.payload);
            iotModel->updateLedConfig(parsedLedConfig);
            return String("");
          }
      }

      return String("");
    });
}

void loop() {
  (*iotModel).tick();
  //(*iotController).tick();
}
