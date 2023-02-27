#include "IotController.h"
#include "DataStruct.h"
#include "TypeDevice.h"
#include "Arduino.h"

void IotController::setup() {
  Serial.println("IotController::setup");
  persistent.setup();
  Serial.println("IotController::setup AFTER persistent.setup()");
  iotModel.setup(
    []() {
      Serial.println("IotController::setup ONCONNECTED BEFORE (*persistent).getRegistered()");
      //persistent.getRegistered();
      return String("^ups^");
      // if (persistent.getRegistered()) {
      //   return dataConstruct.constructAuth(persistent.getSavedId(), typeDeviceToString(currentTypeDevice));
      // } else {
      //   return dataConstruct.constructRegister(typeDeviceToString(currentTypeDevice));
      // }
    },
    [](String data) {
      Serial.println("IotController::setup ONMESSAGE BEFORE dataParser.parseTextData(data)");
      // ParsedHeaderPayload headerPayload = dataParser.parseTextData(data);
      // Serial.println("IotController::setup ONMESSAGE AFTER dataParser.parseTextData(data)");

      // if (headerPayload.header.isEmpty()) {
      //   return String("");
      // }

      // TypeControl typeControl = stringToTypeControl(headerPayload.header.c_str());

      // if (typeControl == unknown_c || !allowedTypeControl(typeControl)) {
      //   return String("");
      // }
      // Serial.println("IotController::setup ONMESSAGE typeControl");
      // Serial.println(typeControl);

      // switch (typeControl) {
      //   case register_c:
      //     return handleRegister(headerPayload.payload);
      //   case reset_c:
      //     return handleReset();
      //   case powerOff_c:
      //     return handlePower(false);
      //   case powerOn_c:
      //     return handlePower(true);
      //   case rgba_c:
      //   case rgbaEffects_c:
      //     return handleRgba(headerPayload.payload);
      // }

      return String("");
    });
  Serial.println("IotController::setup AFTER iotModel.setup");
}

String IotController::handleRegister(String payload) {
  int newId = payload.toInt();
  persistent.saveId(newId);
  return String("");
}

String IotController::handleReset() {
  persistent.saveId(-1);
  return dataConstruct.constructRegister(typeDeviceToString(currentTypeDevice));
}

String IotController::handlePower(bool controlOn) {
  iotModel.updatePower(controlOn);
  return String("");
}

String IotController::handleRgba(String payload) {
  LedConfigData parsedLedConfig = dataParser.parseLedConfig(payload);
  iotModel.updateLedConfig(parsedLedConfig);
  return String("");
}

void IotController::tick() {
  iotModel.tick();
}