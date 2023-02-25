#pragma once

#include "WString.h"
#include "DataStruct.h"

class DataConstruct {
public:
  String constructRegister(String typeDevice);
  String constructAuth(int idDevice, String typeDevice);

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