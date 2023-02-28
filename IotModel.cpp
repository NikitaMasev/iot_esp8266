#include "DataTypes.h"
#include "HardwareSerial.h"
#include "IotModel.h"
#include "TypeDevice.h"
#include "Arduino.h"

void IotModel::setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage) {
  Serial.println("IotModel::setup");
  
  CryptoNetwork *cryptoNetworkVar = &this->cryptoNetwork;

  tasker.runMainTasks(
    [cryptoNetworkVar]() {
      Serial.println("IotModel::setup inside tasker.runMainTasks cryptoNetwork.tick()");
      //this->cryptoNetwork.tick();
      cryptoNetworkVar->tick();
    },
    [this]() {
      this->tickDataPusher();
    });
  Serial.println("IotModel::setup AFTER tasker.runMainTasks");
#if defined(TYPE_DEVICE_UPS)
  Serial.println("IotModel::setup TYPE_DEVICE_UPS BEFORE  tasker.runUpsTasks");
  tasker.runUpsTasks(
    [this]() {
      Serial.println("IotModel::setup inside tasker.runUpsTasks coolerControl.tick");
      this->coolerControl.tick(this->tempDetector.temps[0]);
    },
    [this]() {
      Serial.println("IotModel::setup inside tasker.runUpsTasks tempDetector.tick");
      this->tempDetector.tick();
    },
    [this]() {
      Serial.println("IotModel::setup inside tasker.runUpsTasks voltCurController.tick");
      this->voltCurController.tick();
    });
  Serial.println("IotModel::setup TYPE_DEVICE_UPS AFTER  tasker.runUpsTasks");
#elif defined(TYPE_DEVICE_LAMP)
  updatePower(persistent.getSavedPowerControlState());
#elif defined(TYPE_DEVICE_RGBA)
  updateLedConfig(persistent.getSavedLedConfigData());
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  updateLedConfig(persistent, getSavedLedConfigData());
  tasker.runRgbaAddressTask(
    [this]() {
      this->rgbaAddressControl.tick();
    });
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  tasker.runTempTask(
    [this]() {
      this->tempDetector.tick();
    });
#endif
  Serial.println("IotModel::setup BEFORE cryptoNetwork.setup");
  cryptoNetwork.setup(callbackConnected, callbackMessage);
  Serial.println("IotModel::setup AFTER cryptoNetwork.setup");
}

void IotModel::updatePower(bool controlOn) {
#if defined(TYPE_DEVICE_LAMP)
  powerControl.updatePower(controlOn);
#endif
}

void IotModel::updateLedConfig(LedConfigData parsedLedConfig) {
#if defined(TYPE_DEVICE_RGBA)
  rgbaControl.updateLedConfig(parsedLedConfig);
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
  rgbaAddressControl.updateLedAddressConfig(parsedLedConfig);
#endif
}

void IotModel::tickDataPusher() {
    Serial.println("IotModel::tickDataPusher");
    if (!cryptoNetwork.getConnectedState()) return;

    String dataForService = "";

  #if defined(TYPE_DEVICE_LAMP)
    dataForService = dataConstruct.constructSwitchData(powerControl.getPowerState());
  #endif
  #if defined(TYPE_DEVICE_UPS)
    dataForService = dataConstruct.constructUpsData(tempDetector.temps[0], tempDetector.temps[1], coolerControl.pwmCooler, voltCurController.currentDC, voltCurController.voltageDC);
  #endif
  #if defined(TYPE_DEVICE_RGBA)
    dataForService = dataConstruct.constructLedConfigData(rgbaControl.getLedConfig());
  #endif
  #if defined(TYPE_DEVICE_RGBA_ADDRESS)
    dataForService = dataConstruct.constructLedConfigData(rgbaAddressControl.getLedAddressConfig());
  #endif
  #if defined(TYPE_DEVICE_TEMP_SENSOR)
    dataForService = dataConstruct.constructTempsData(tempDetector.temps, TEMP_SENSOR_COUNT);
  #endif

    if (!dataForService.isEmpty()) {
      Serial.println("IotModel::tickDataPusher");
      cryptoNetwork.send(dataForService);
    }
}

void IotModel::tick() {
  tasker.tick();
}