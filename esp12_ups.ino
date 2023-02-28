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
//Persistent persistent;
//DataConstruct dataConstruct;
//DataParser dataParser;


void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  CryptoAesUtil cryptoAesUtil(cipher_key, cipher_iv);      //-
  IotNetwork iotNetwork(ssid, password, iotServer);        //-
  CryptoNetwork cryptoNetwork(iotNetwork, cryptoAesUtil);  //-

  DataConstruct dataConstruct;
  ModelDataConstruct modelDataConstruct(&dataConstruct);  //+
  AuthDataConstruct authDataConstruct(&dataConstruct);

  Persistent persistent;
  AuthPersistent authPersistent(&persistent);
  ModelPersistent modelPersistent(&persistent);

  DataParser dataParser;
  Tasker tasker;  //-

  // IotModel iotModel(cryptoNetwork, modelPersistent, tasker, &modelDataConstruct);
  // iotController = new IotController(iotModel, authPersistent, dataParser, authDataConstruct);
  // (*iotController).setup();
  iotModel = new IotModel(cryptoNetwork, modelPersistent, tasker, &modelDataConstruct);
  persistent.setup();
  (*iotModel).setup(
    [&authDataConstruct, &persistent]() {
      Serial.println("IotController::setup ONCONNECTED BEFORE (*persistent).getRegistered()");
      if (persistent.getRegistered()) {
        return authDataConstruct.constructAuth(persistent.getSavedId(), typeDeviceToString(currentTypeDevice));
      } else {
        return authDataConstruct.constructRegister(typeDeviceToString(currentTypeDevice));
      }
      return String("");
    },
    [&dataParser, &persistent, &authDataConstruct, iotModel](String data) {
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
            persistent.saveId(newId);
            Serial.println("AFTER SAVE ID");
            return String("");
          }
        case reset_c:
          {
            persistent.saveId(-1);
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
