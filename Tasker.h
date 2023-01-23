#pragma once

#include "Config.h"
#include <GyverOS.h>
#include "Network.h"

#if defined(TYPE_DEVICE_UPS)
#include "Persistent.h"
#include "CoolerControl.h"
#include "VoltCur.h"
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
#include "RgbaAddressControl.h"
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
#include "Persistent.h"
#include "TempDetector.h"
#endif

#if defined(TYPE_DEVICE_UPS)
GyverOS<4> tasker;
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
GyverOS<2> tasker;
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
GyverOS<2> tasker;
#endif

void setupTasker() {
  tasker.attach(0, networkLoop, 50); //50 OK 100??? 250???
#if defined(TYPE_DEVICE_UPS)
  tasker.attach(1, loopCooler, 5000);
  tasker.attach(2, loopTempDetector, 750);
  tasker.attach(3, loopVoltCur, 200);
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  tasker.attach(1, loopLedAddress, 80);
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  tasker.attach(1, loopTempDetector, 750);
#endif
}

void loopTasker() {
#if defined(TYPE_DEVICE_UPS) || defined(TYPE_DEVICE_RGBA_ADDRESS) || defined(TYPE_DEVICE_TEMP_SENSOR)
  tasker.tick();
#endif
}