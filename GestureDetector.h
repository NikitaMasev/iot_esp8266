#pragma once

#include "RevEng_PAJ7620.h"
#include "DataTypes.h"
#include "Arduino.h"

#define COUNT_CALLBACKS 1

class GestureDetector {
private:
  RevEng_PAJ7620 sensorPajLed = RevEng_PAJ7620();
  CallbackTaskerLoop callbacksLeft[COUNT_CALLBACKS] = {nullptr};
  CallbackTaskerLoop callbacksRight[COUNT_CALLBACKS] = {nullptr};
  uint8_t indexLeft = 0;
  uint8_t indexRight = 0;
public:
  GestureDetector() {
    if (!sensorPajLed.begin()) {
      Serial.println("PAJ7620 I2C error - halting");
    }
  };
  void attachLeft(CallbackTaskerLoop callback);
  void attachRight(CallbackTaskerLoop callback);
  void tick();
};