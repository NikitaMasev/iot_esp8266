#include "ModelDataConstruct.h"

String ModelDataConstruct::constructUpsData(
  float tempUps,
  float tempAcc,
  int pwmCooler,
  float currentDC,
  float voltageDC) {
  return (*dataConstruct).constructUpsData(tempUps, tempAcc, pwmCooler, currentDC, voltageDC);
}

String ModelDataConstruct::constructLedConfigData(LedConfigData ledConfigData) {
  return (*dataConstruct).constructLedConfigData(ledConfigData);
}

String ModelDataConstruct::constructSwitchData(bool powerState) {
  return (*dataConstruct).constructSwitchData(powerState);
}

String ModelDataConstruct::constructTempsData(float temps[], int length) {
  return (*dataConstruct).constructTempsData(temps, length);
}