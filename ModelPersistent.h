#pragma once

#include "DataStruct.h"
#include "Persistent.h"

class ModelPersistent {
private:
  Persistent persistent;
public:
  ModelPersistent(Persistent persistent)
    : persistent(persistent){};

  void savePowerControlState(bool newState);
  bool getSavedPowerControlState();

  void saveLedConfigData(LedConfigData ledConfigData);
  LedConfigData getSavedLedConfigData();

  void saveLedCctConfigData(LedCctConfigData ledConfigData);
  LedCctConfigData getSavedLedCctConfigData();
};
