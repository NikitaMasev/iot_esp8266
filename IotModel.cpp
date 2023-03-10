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
  updateLedConfig(persistent.getSavedLedConfigData());
  RgbaAddressControl *rgbaAddressControl = &this->rgbaAddressControl;
  tasker.runRgbaAddressTask(
    [rgbaAddressControl]() {
      rgbaAddressControl->tick();
    });
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  tasker.runTempTask(
    [this]() {
      this->tempDetector.tick();
    });
#endif
  cryptoNetwork.setup(callbackConnected, callbackMessage);
  Serial.println("IotModel::setup AFTER cryptoNetwork.setup");
#if defined(CONTROL_LED_PAJ7620_SENSOR)
  if (!sensorPajLed.begin()) {
    Serial.println("PAJ7620 I2C error - halting");
  }
#endif
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

#if defined(CONTROL_LED_PAJ7620_SENSOR) && defined(TYPE_DEVICE_RGBA_ADDRESS)
  Gesture gesture;                       // Gesture is an enum type from RevEng_PAJ7620.h
  gesture = sensorPajLed.readGesture();  // Read back current gesture (if any) of type Gesture

  switch (gesture) {
    case GES_FORWARD:
      {
        Serial.print("GES_FORWARD");
        break;
      }

    case GES_BACKWARD:
      {
        Serial.print("GES_BACKWARD");
        break;
      }

    case GES_LEFT:
      {
        Serial.print("GES_LEFT");
        rgbaAddressControl.nextEffect();
        break;
      }

    case GES_RIGHT:
      {
        Serial.print("GES_RIGHT");
        rgbaAddressControl.previousEffect();
        break;
      }

    case GES_UP:
      {
        Serial.print("GES_UP");
        break;
      }

    case GES_DOWN:
      {
        Serial.print("GES_DOWN");
        break;
      }

    case GES_CLOCKWISE:
      {
        Serial.print("GES_CLOCKWISE");
        break;
      }

    case GES_ANTICLOCKWISE:
      {
        Serial.print("GES_ANTICLOCKWISE");
        break;
      }

    case GES_WAVE:
      {
        Serial.print("GES_WAVE");
        break;
      }

    case GES_NONE:
      {
        break;
      }
  }
#endif
}

void IotModel::tick() {
  tasker.tick();
}