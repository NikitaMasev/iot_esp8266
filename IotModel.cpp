#include "DataTypes.h"
#include "HardwareSerial.h"
#include "IotModel.h"
#include "TypeDevice.h"
#include "Arduino.h"

void IotModel::setup(CallbackConnected callbackConnected, CallbackMessage callbackMessage) {
  CryptoNetwork *cryptoNetworkVar = &this->cryptoNetwork;

  tasker.runMainTasks(
    [cryptoNetworkVar]() {
      cryptoNetworkVar->tick();
    },
    [this]() {
      this->tickDataPusher();
    });
#if defined(TYPE_DEVICE_UPS)
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
  updatePower(persistent.getSavedPowerControlState());
#elif defined(TYPE_DEVICE_RGBA)
  rgbaControl.updateLedConfig(persistent.getSavedLedConfigData());
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  rgbaAddressControl.updateLedAddressConfig(persistent.getSavedLedConfigData());
  RgbaAddressControl *rgbaTick = &this->rgbaAddressControl;
  tasker.runRgbaAddressTask(
    [rgbaTick]() {
      rgbaTick->tick();
    });
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  tasker.runTempTask(
    [this]() {
      this->tempDetector.tick();
    });
#endif
  cryptoNetwork.setup(callbackConnected, callbackMessage);

#if defined(CONTROL_LED_PAJ7620_SENSOR)
  RgbaAddressControl *rgbaAddrEffectSwitching = &this->rgbaAddressControl;
  ModelPersistent *persistentEffectSave = &this->persistent;

  gestureDetector.attachLeft([rgbaAddrEffectSwitching, persistentEffectSave]() {
    rgbaAddrEffectSwitching->previousEffect();
    LedConfigData newConfigLed = rgbaAddrEffectSwitching->getLedAddressConfig();
    persistentEffectSave->saveLedConfigData(newConfigLed);
  });
  gestureDetector.attachRight([rgbaAddrEffectSwitching, persistentEffectSave]() {
    rgbaAddrEffectSwitching->nextEffect();
    LedConfigData newConfigLed = rgbaAddrEffectSwitching->getLedAddressConfig();
    persistentEffectSave->saveLedConfigData(newConfigLed);
  });
  gestureDetector.attachUp([rgbaAddrEffectSwitching, persistentEffectSave]() {
    LedConfigData newConfigLed = rgbaAddrEffectSwitching->getLedAddressConfig();
    newConfigLed.powerOn = true;
    rgbaAddrEffectSwitching->updateLedAddressConfig(newConfigLed);
    persistentEffectSave->saveLedConfigData(newConfigLed);
  });
  gestureDetector.attachDown([rgbaAddrEffectSwitching, persistentEffectSave]() {
    LedConfigData newConfigLed = rgbaAddrEffectSwitching->getLedAddressConfig();
    newConfigLed.powerOn = false;
    rgbaAddrEffectSwitching->updateLedAddressConfig(newConfigLed);
    persistentEffectSave->saveLedConfigData(newConfigLed);
  });

  GestureDetector *gestureTick = &this->gestureDetector;

  tasker.runGestureDetector([gestureTick]() {
    gestureTick->tick();
  });
#endif
}

void IotModel::updatePower(bool controlOn) {
#if defined(TYPE_DEVICE_LAMP)
  powerControl.updatePower(controlOn);
#endif
}

void IotModel::updateLedConfig(LedConfigData parsedLedConfig) {
  persistent.saveLedConfigData(parsedLedConfig);
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
    cryptoNetwork.send(dataForService);
  }
}

void IotModel::tick() {
  tasker.tick();
}