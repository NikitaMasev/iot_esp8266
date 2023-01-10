#include "Persistent.h"

#define PIN_POWER_CONTROL 2

bool powerState = false;

void applyPowerState() {
  digitalWrite(PIN_POWER_CONTROL, powerState);
}

void updatePower(bool controlOn) {
  if (powerState != controlOn) {
    savePowerControlState(controlOn);
  }

  powerState = controlOn;
  applyPowerState();
}

void setupPowerControl() {
  pinMode(PIN_POWER_CONTROL, OUTPUT);
  powerState = getSavedPowerControlState();
  applyPowerState();
}
