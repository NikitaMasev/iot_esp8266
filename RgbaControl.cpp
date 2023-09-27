#include "RgbaControl.h"

LedConfigData RgbaControl::getLedConfig() {
  return ledConfigData;
}

void RgbaControl::updatePower(bool powerOn) {
  ledControl.setPower(powerOn);
  ledConfigData.powerOn = powerOn;
}

RgbaControl::RgbaControl() {
  ledControl.setCRT(true);
}

void RgbaControl::ledConfigApplyControl() {
  ledControl.setPower(ledConfigData.powerOn);
  ledControl.setBrightness(ledConfigData.v);
  ledControl.setHSV(ledConfigData.h, ledConfigData.s, ledConfigData.v);
}

void RgbaControl::updateLedConfig(LedConfigData newConfigData) {
  ledConfigData = newConfigData;
  ledConfigApplyControl();
}