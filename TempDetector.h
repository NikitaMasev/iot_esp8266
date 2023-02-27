#pragma once

#include <OneWire.h>
#include "Config.h"

class TempDetector {
private:
  // 2 pin - dc-dc temp, 15 pin - battery temp.
  OneWire wireTemps[TEMP_SENSOR_COUNT] = { OneWire(PIM_TEMP_DC), OneWire(PIM_TEMP_ACC) };
  long lastTimesUpdateTemps[TEMP_SENSOR_COUNT];
  bool cmdWireTemps[TEMP_SENSOR_COUNT] = { false, false };
  float detectTemperature(OneWire *wireTemp, long *lastTimeUpdateTemp, bool *cmdWireTemp);
public:
  float temps[TEMP_SENSOR_COUNT];
  void tick();
};
