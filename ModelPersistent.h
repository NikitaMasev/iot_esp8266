#pragma once

#include "DataStruct.h"

class ModelPersistent {
public:
  virtual void savePowerControlState(bool newState) = 0;
  virtual bool getSavedPowerControlState() = 0;
  virtual void saveLedConfigData(LedConfigData ledConfigData) = 0;
  virtual LedConfigData getSavedLedConfigData() = 0;
};
