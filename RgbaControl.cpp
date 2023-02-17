#include "RgbaControl"

RgbaControl::RgbaControl() {
  LedConfigData savedLedConfigData = getSavedLedConfigData();
  if (savedLedConfigData.h != -1) {
    ledConfigData = savedLedConfigData;
  }
  ledControl.setCRT(true);
  ledConfigApplyControl();
}

RgbaControl::ledConfigApplyControl() {
  ledControl.setPower(ledConfigData.powerOn);
  ledControl.setBrightness(ledConfigData.v);
  ledControl.setHSV(ledConfigData.h, ledConfigData.s, ledConfigData.v);
}

RgbaControl::updateLedConfig(LedConfigData newConfigData) {
  ledConfigData = newConfigData;
  saveLedConfigData(ledConfigData);
  ledConfigApplyControl();
}