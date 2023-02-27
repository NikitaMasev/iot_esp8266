#pragma once

#include "Arduino.h"
#include "Config.h"

class PowerControl {
private:
  void applyPowerState();
  bool powerState = false;
public:
  PowerControl() {
    pinMode(PIN_POWER_CONTROL, OUTPUT);
  };
  void updatePower(bool controlOn);
  bool getPowerState();
};
