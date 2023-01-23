#pragma once

#include <GRGB.h>
#include "Persistent.h"

// указать тип драйвера COMMON_CATHODE/COMMON_ANODE
// и пины в порядке R,G,B
GRGB ledControl(COMMON_CATHODE, 9, 10, 11);

LedConfigData ledConfigData = {
  h: 59,
  s: 255,
  v: 180,
  mode: 10,
};

void updateLedPower(bool controlOn) {
  ledControl.setPower(controlOn);
}

void ledConfigApplyControl() {
  ledControl.setBrightness(ledConfigData.v);
  ledControl.setHSV(ledConfigData.h, ledConfigData.s, ledConfigData.v);
}

void setupLedControl() {
  LedConfigData savedLedConfigData = getSavedLedConfigData();
  if (savedLedConfigData.h != -1) {
    ledConfigData = savedLedConfigData;
  }
  ledControl.setCRT(true);
  ledConfigApplyControl();
}

void updateLedConfig(LedConfigData newConfigData) {
  ledConfigData = newConfigData;
  saveLedConfigData(ledConfigData);
  ledConfigApplyControl();
}