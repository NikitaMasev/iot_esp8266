#include "RgbaControl.h"

LedConfigData RgbaControl::getLedConfig() {
  return ledConfigData;
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