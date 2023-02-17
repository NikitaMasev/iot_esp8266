#include "PowerControl.h"

#define PIN_POWER_CONTROL 14

PowerControl::PowerControl() {
  pinMode(PIN_POWER_CONTROL, OUTPUT);
  powerState = getSavedPowerControlState();
  applyPowerState();
}

PowerControl::applyPowerState() {
  digitalWrite(PIN_POWER_CONTROL, powerState);
}

PowerControl::updatePower(bool controlOn) {
  if (powerState != controlOn) {
    savePowerControlState(controlOn);
  }

  powerState = controlOn;
  applyPowerState();  
}