#pragma once

class CoolerControl {
private:
  void controlCooler(float tempAcc);
public:
  CoolerControl();
  int pwmCooler;
  void tick(float tempControl);
};