#include "LedCctControl.h"

LedCctConfigData LedCctControl::getLedConfig() {
  return ledConfigData;
}

void LedCctControl::updatePower(bool powerOn) {
  ledControl.setPower(powerOn);
  ledConfigData.powerOn = powerOn;
}

LedCctControl::LedCctControl() {
  ledControl.setCRT(true);
}

void LedCctControl::ledConfigApplyControl() {
  ledControl.setPower(ledConfigData.powerOn);
  ledControl.setBrightness(ledConfigData.brightness);

  uint8_t coldValue = 0;
  uint8_t warmValue = 0;

  if (ledConfigData.colorTemperature == 128) {
    coldValue = 255;
    warmValue = 255;
  } else if (ledConfigData.colorTemperature < 128) {
    coldValue = 255;
    warmValue = ledConfigData.colorTemperature * 2;
  } else if (ledConfigData.colorTemperature > 128) {
    warmValue = 255;
    coldValue = (255 - ledConfigData.colorTemperature) * 2;
  }

  ledControl.setRGB(coldValue, 0, warmValue);
}

void LedCctControl::updateLedConfig(LedCctConfigData newConfigData) {
  if (newConfigData.brightness == -1 || newConfigData.colorTemperature == -1) {
    return;
  }

  ledConfigData = newConfigData;
  ledConfigApplyControl();
}