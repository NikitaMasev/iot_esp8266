#pragma once

#include "WString.h"
#include "DataStruct.h"
#include <EEPROM.h>

class Persistent {
private:
  int getAddressForSavingSideData();
  void updateRegisteredState();
public:
  Persistent();
  bool registered = false;
  int idDevice;
  void saveIdDevice(int newId);
  void savePowerControlState(bool newState);
  bool getSavedPowerControlState();
  void saveLedConfigData(LedConfigData ledConfigData);
  LedConfigData getSavedLedConfigData();
};