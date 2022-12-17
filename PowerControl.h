#define PIN_POWER_CONTROL 2

bool powerState = false;

void setupPowerControl() {
  pinMode(PIN_POWER_CONTROL, OUTPUT);
}

void powerOn() {
  digitalWrite(PIN_POWER_CONTROL, HIGH);
  powerState = true;
}

void powerOff() {
  digitalWrite(PIN_POWER_CONTROL, LOW);
  powerState = false;
}
