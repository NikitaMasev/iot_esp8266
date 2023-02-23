#include "PowerControl.h"

void PowerControl::applyPowerState() {
  digitalWrite(PIN_POWER_CONTROL, powerState);
}

void PowerControl::updatePower(bool controlOn) {
  powerState = controlOn;
  applyPowerState();  
}

bool PowerControl::getPowerState() {
  return powerState;
}