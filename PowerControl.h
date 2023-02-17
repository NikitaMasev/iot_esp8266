#pragma once

class PowerControl {
private:
  void applyPowerState();
public:
  PowerControl();
  bool powerState = false;
  void updatePower(bool controlOn);
};
