#include "Tasker.h"

Tasker::run(void (*networkLoop)(), void (*loopDataPusher)(), void (*loopCooler)(), void (*loopTempDetector)(), void (*loopVoltCur)(), void (*loopLedAddress)()) {
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

Tasker::tick() {
  tasker.tick();
}