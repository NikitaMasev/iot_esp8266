#include <GRGB.h>

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
  ledControl.setPower(true);
}

void setupLedControl() {
  ledControl.setBrightness(ledConfigData.v);
  ledControl.setHSV(ledConfigData.h, ledConfigData.s, ledConfigData.v);
  ledControl.setCRT(true);
}

void updateLedConfig(LedConfigData newConfigData) {
  ledConfigData = newConfigData;
  setupLedControl();
}