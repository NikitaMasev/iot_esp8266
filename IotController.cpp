#include "IotController.h"
#include "DataStruct.h"
#include "TypeDevice.h"
#include "Arduino.h"

void IotController::setup() {
  (*persistent).setup();
  iotModel.setup(
    [this]() {
      Serial.println("IotController::setup ONCONNECTED BEFORE (*persistent).getRegistered()");
      if ((*persistent).getRegistered()) {
        return (*dataConstruct).constructAuth((*persistent).getSavedId(), typeDeviceToString(currentTypeDevice));
      } else {
        return (*dataConstruct).constructRegister(typeDeviceToString(currentTypeDevice));
      }
    },
    [this](String data) {
      Serial.println("IotController::setup ONMESSAGE BEFORE dataParser.parseTextData(data)");
      ParsedHeaderPayload headerPayload = dataParser.parseTextData(data);
      Serial.println("IotController::setup ONMESSAGE AFTER dataParser.parseTextData(data)");

      if (headerPayload.header.isEmpty()) {
        return empty;
      }

      TypeControl typeControl = stringToTypeControl(headerPayload.header.c_str());

      if (typeControl == unknown_c || !allowedTypeControl(typeControl)) {
        return empty;
      }
      Serial.println("IotController::setup ONMESSAGE typeControl");
      Serial.println(typeControl);
      switch (typeControl) {
        case register_c:
          return handleRegister(headerPayload.payload);
        case reset_c:
          return handleReset();
        case powerOff_c:
          return handlePower(false);
        case powerOn_c:
          return handlePower(true);
        case rgba_c:
        case rgbaEffects_c:
          return handleRgba(headerPayload.payload);
      }

      return empty;
    });
}

String IotController::handleRegister(String payload) {
  int newId = payload.toInt();
  (*persistent).saveId(newId);
  return empty;
}

String IotController::handleReset() {
  (*persistent).saveId(-1);
  return (*dataConstruct).constructRegister(typeDeviceToString(currentTypeDevice));
}

String IotController::handlePower(bool controlOn) {
  iotModel.updatePower(controlOn);
  return empty;
}

String IotController::handleRgba(String payload) {
  LedConfigData parsedLedConfig = dataParser.parseLedConfig(payload);
  iotModel.updateLedConfig(parsedLedConfig);
  return empty;
}

void IotController::tick() {
  iotModel.tick();
}