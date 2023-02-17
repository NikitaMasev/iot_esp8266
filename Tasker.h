#pragma once

#include "Config.h"
#include <GyverOS.h>

class Tasker {
private:
#if defined(TYPE_DEVICE_UPS)
  GyverOS<5> tasker;
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
  GyverOS<3> tasker;
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
  GyverOS<3> tasker;
#endif
#if defined(TYPE_DEVICE_LAMP)
  GyverOS<2> tasker;
#endif
#if defined(TYPE_DEVICE_RGBA)
  GyverOS<2> tasker;
#endif
public:
  void run(void (*networkLoop)(), void (*loopDataPusher)(), void (*loopCooler)(), void (*loopTempDetector)(), void (*loopVoltCur)(), void (*loopLedAddress)());
  void tick();
};