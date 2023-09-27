#pragma once

#include <GRGB.h>
#include "DataStruct.h"
#include "Config.h"

class RgbaControl {
private:
  // указать тип драйвера COMMON_CATHODE/COMMON_ANODE
  // и пины в порядке R,G,B
  GRGB ledControl={COMMON_CATHODE, PIN_R, PIN_G, PIN_B};
  LedConfigData ledConfigData = {
    h: 59,
    s: 255,
    v: 180,
    mode: 10,
    powerOn: true,
  };
  void ledConfigApplyControl();
public:
  RgbaControl();
  void updateLedConfig(LedConfigData newConfigData);
  void updatePower(bool powerOn);
  LedConfigData getLedConfig();
};