#pragma once

#include <OneWire.h>

#define TEMP_SENSOR_COUNT 2

class TempDetector {
private:
  // 2 pin - dc-dc temp, 15 pin - battery temp.
  OneWire wireTemps[TEMP_SENSOR_COUNT] = { OneWire(2), OneWire(13) };
  long lastTimesUpdateTemps[TEMP_SENSOR_COUNT];
  bool cmdWireTemps[TEMP_SENSOR_COUNT] = { false, false };
  float detectTemperature(OneWire *wireTemp, long *lastTimeUpdateTemp, bool *cmdWireTemp);
public:
  float temps[TEMP_SENSOR_COUNT];
  void tick();
};
