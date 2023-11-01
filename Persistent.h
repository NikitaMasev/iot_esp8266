#pragma once

#include "WString.h"
#include "DataStruct.h"
#include <EEPROM.h>

class Persistent {
private:
  bool registered = false;
  int idDevice = -1;

  int getAddressForSavingSideData();
  void updateRegisteredState();
public:
  void setup();
  void saveId(int newId);
  int getSavedId();
  bool getRegistered();

  void savePowerControlState(bool newState);
  bool getSavedPowerControlState();

  void saveLedConfigData(LedConfigData ledConfigData);
  LedConfigData getSavedLedConfigData();

  void saveLedCctConfigData(LedCctConfigData ledConfigData);
  LedCctConfigData getSavedLedCctConfigData();
};