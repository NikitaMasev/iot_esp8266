#pragma once

#include "WString.h"
#include "DataStruct.h"
#include "DataConstruct.h"

class ModelDataConstruct {
private:
  DataConstruct *dataConstruct;
public:
  ModelDataConstruct(DataConstruct *dataConstruct)
    : dataConstruct(dataConstruct){};
  String constructUpsData(
    float tempUps,
    float tempAcc,
    int pwmCooler,
    float currentDC,
    float voltageDC);
  String constructLedConfigData(LedConfigData ledConfigData);
  String constructSwitchData(bool powerState);
  String constructTempsData(float temps[], int length);
};