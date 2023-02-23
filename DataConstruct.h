#pragma once

#include "WString.h"
#include "DataStruct.h"
#include "AuthDataConstruct.h"
#include "ModelDataConstruct.h"

class DataConstruct: public AuthDataConstruct, public ModelDataConstruct {
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