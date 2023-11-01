#pragma once

#include <GRGB.h>
#include "DataStruct.h"
#include "Config.h"

class LedCctControl {
private:
  GRGB ledControl = { COMMON_CATHODE, PIN_COLD, PIN_NULL, PIN_WARM };
  LedCctConfigData ledConfigData = {
    brightness: 128,
    colorTemperature: 255,
    powerOn: true,
  };
  void ledConfigApplyControl();
public:
  LedCctControl();
  void updateLedConfig(LedCctConfigData newConfigData);
  void updatePower(bool powerOn);
  LedCctConfigData getLedConfig();
};