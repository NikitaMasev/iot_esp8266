#pragma once

#include "WString.h"
#include "DataStruct.h"

class ModelDataConstruct {
public:
  virtual String constructUpsData(
    float tempUps,
    float tempAcc,
    int pwmCooler,
    float currentDC,
    float voltageDC) = 0;
  virtual String constructLedConfigData(LedConfigData ledConfigData) = 0;
  virtual String constructSwitchData(bool powerState) = 0;
  virtual String constructTempsData(float temps[], int length) = 0;
};