#pragma once

#include <Adafruit_INA219.h>

class VoltCurController {
private:
  Adafruit_INA219 ina219;
  void updateVoltageAndCurrent();
public:
  VoltCurController();
  float currentDC;
  float voltageDC;
  void tick();
};