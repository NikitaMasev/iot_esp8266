#pragma once

#include "CryptoNetwork.h"
#include "Tasker.h"
#include "DataStruct.h"
#include "Config.h"
#include "DataTypes.h"
#include "ModelPersistent.h"
#include "ModelDataConstruct.h"

#if defined(TYPE_DEVICE_UPS)
#include "VoltCurControl.h"
#include "CoolerControl.h"
#include "TempDetector.h"
#elif defined(TYPE_DEVICE_LAMP)
#include "PowerControl.h"
#elif defined(TYPE_DEVICE_RGBA)
#include "RgbaControl.h"
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
#include "RgbaAddressControl.h"
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
#include "TempDetector.h"
#endif

class IotModel {
private:
  CryptoNetwork cryptoNetwork;
  Tasker tasker;
  ModelDataConstruct *dataConstruct;
  ModelPersistent *persistent;

  void tickDataPusher();

#if defined(TYPE_DEVICE_UPS)
  TempDetector tempDetector = {};
  CoolerControl coolerControl = {};
  VoltCurController voltCurController = {};
#elif defined(TYPE_DEVICE_LAMP)
  PowerControl powerControl = {};
#elif defined(TYPE_DEVICE_RGBA)
  RgbaControl rgbaControl = {};
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  RgbaAddressControl rgbaAddressControl = {};
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  TempDetector tempDetector = {};
#endif
public:
  IotModel(CryptoNetwork cryptoNetwork, ModelPersistent *persistent, Tasker tasker, ModelDataConstruct *dataConstruct)
    : cryptoNetwork(cryptoNetwork), persistent(persistent), tasker(tasker), dataConstruct(dataConstruct){};
  void setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage);
  void tick();
  void updatePower(bool controlOn);
  void updateLedConfig(LedConfigData parsedLedConfig);
};