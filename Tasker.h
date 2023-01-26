#pragma once

#include "Config.h"
#include <GyverOS.h>
#include "Network.h"
#include "DataPusher.h"

#if defined(TYPE_DEVICE_UPS)
#include "CoolerControl.h"
#include "VoltCur.h"
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
#include "RgbaAddressControl.h"
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
#include "TempDetector.h"
#endif

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

void setupTasker() {
#if defined(TYPE_DEVICE_UPS)
  tasker.attach(0, networkLoop, 100);  //50 OK 100??? 250 OK
  tasker.attach(1, loopDataPusher, 150);
  tasker.attach(2, loopCooler, 5000);
  tasker.attach(3, loopTempDetector, 400);
  tasker.attach(4, loopVoltCur, 200);
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  tasker.attach(0, networkLoop, 250);  //50 OK 100??? 250 OK
  tasker.attach(1, loopDataPusher, 350);
  tasker.attach(2, loopLedAddress, 10);  //10 OK 20??
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  tasker.attach(0, networkLoop, 100);  //50 OK 100??? 250 OK
  tasker.attach(1, loopDataPusher, 150);
  tasker.attach(2, loopTempDetector, 400);
#endif
}

void loopTasker() {
  tasker.tick();
}