#pragma once

#include "Config.h"
#include "Arduino.h"
#include "GyverOS.h"
#include "DataTypes.h"

class Tasker {
private:
GyverOS<2> os = {};
// #if defined(TYPE_DEVICE_UPS)
//   GyverOS<5> os = {};
// #elif defined(TYPE_DEVICE_RGBA_ADDRESS)
//   GyverOS<3> os = {};
// #elif defined(TYPE_DEVICE_TEMP_SENSOR)
//   GyverOS<3> os = {};
// #elif defined(TYPE_DEVICE_LAMP)
//   GyverOS<2> os = {};
// #elif defined(TYPE_DEVICE_RGBA)
//   GyverOS<2> os = {};
// #endif
public:
  void runMainTasks(CallbackTaskerLoop taskNetwork, CallbackTaskerLoop taskDataPusher);
  void runUpsTasks(CallbackTaskerLoop taskCooler, CallbackTaskerLoop taskTemp, CallbackTaskerLoop taskVoltCurSensor);
  void runRgbaAddressTask(CallbackTaskerLoop taskRgba);
  void runTempTask(CallbackTaskerLoop taskTemp);
  void tick();
};