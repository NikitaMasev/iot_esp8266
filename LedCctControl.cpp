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
  } else {
    coldValue = 255 - ledConfigData.colorTemperature;
    warmValue = ledConfigData.colorTemperature;
  }

  ledControl.setRGB(coldValue, 0, warmValue);
}

void LedCctControl::updateLedConfig(LedCctConfigData newConfigData) {
  ledConfigData = newConfigData;
  ledConfigApplyControl();
}