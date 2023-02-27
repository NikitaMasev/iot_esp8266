#pragma once

#include "IotModel.h"
#include "AuthPersistent.h"
#include "AuthDataConstruct.h"
#include "DataParser.h"
#include "WString.h"

class IotController {
private:
  IotModel *iotModel;
  AuthPersistent *persistent;
  DataParser *dataParser;
  AuthDataConstruct *dataConstruct;

  const String empty = "";

  String handleRegister(String payload);
  String handleReset();
  String handlePower(bool controlOn);
  String handleRgba(String payload);
public:
  IotController(IotModel *iotModel, AuthPersistent *persistent, DataParser *dataParser, AuthDataConstruct *dataConstruct)
    : iotModel(iotModel), persistent(persistent), dataParser(dataParser), dataConstruct(dataConstruct){};
  void setup();
  void tick();
};