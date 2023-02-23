#pragma once

#include "WString.h"
#include "DataStruct.h" 
#include <EEPROM.h>
#include "AuthPersistent.h"
#include "ModelPersistent.h"

class Persistent: public AuthPersistent, public ModelPersistent {
private:
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
};