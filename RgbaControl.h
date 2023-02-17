#pragma once

#include <GRGB.h>
#include "DataStruct.h"

class RgbaControl {
private:
  // указать тип драйвера COMMON_CATHODE/COMMON_ANODE
  // и пины в порядке R,G,B
  GRGB ledControl(COMMON_CATHODE, 9, 10, 11);
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
};