#define PIN_POWER_CONTROL 2

bool powerState = false;

void setupPowerControl() {
  pinMode(PIN_POWER_CONTROL, OUTPUT);
}

void updatePower(bool controlOn) {
  powerState = controlOn;
  digitalWrite(PIN_POWER_CONTROL, powerState);
}
