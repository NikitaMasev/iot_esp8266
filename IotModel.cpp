#include "IotModel.h"
#include "TypeDevice.h"

void IotModel::setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage) {
  tasker.runMainTasks(
    [this]() {
      this->cryptoNetwork.tick();
    },
    [this]() {
      this->tickDataPusher();
    });
#if defined(TYPE_DEVICE_UPS)
  updatePower((*persistent).getSavedPowerControlState());
  tasker.runUpsTasks(
    [this]() {
      this->coolerControl.tick(this->tempDetector.temps[0]);
    },
    [this]() {
      this->tempDetector.tick();
    },
    [this]() {
      this->voltCurController.tick();
    });
#elif defined(TYPE_DEVICE_LAMP)
#elif defined(TYPE_DEVICE_RGBA)
  updateLedConfig((*persistent).getSavedLedConfigData());
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  updateLedConfig((*persistent).getSavedLedConfigData());
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
  cryptoNetwork.setup(callbackConnected, callbackMessage);
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
  if (!cryptoNetwork.getConnectedState()) return;

  String dataForService = "";

#if defined(TYPE_DEVICE_LAMP)
  dataForService = (*dataConstruct).constructSwitchData(powerControl.getPowerState());
#endif
#if defined(TYPE_DEVICE_UPS)
  dataForService = (*dataConstruct).constructUpsData(tempDetector.temps[0], tempDetector.temps[1], coolerControl.pwmCooler, voltCurController.currentDC, voltCurController.voltageDC);
#endif
#if defined(TYPE_DEVICE_RGBA)
  dataForService = (*dataConstruct).constructLedConfigData(rgbaControl.getLedConfig());
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
  dataForService = (*dataConstruct).constructLedConfigData(rgbaAddressControl.getLedAddressConfig());
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
  dataForService = (*dataConstruct).constructTempsData(tempDetector.temps, TEMP_SENSOR_COUNT);
#endif

  if (!dataForService.isEmpty()) {
    cryptoNetwork.send(dataForService);
  }
}

void IotModel::tick() {
  tasker.tick();
}