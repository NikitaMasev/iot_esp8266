#include "ModelPersistent.h"

void ModelPersistent::savePowerControlState(bool newState) {
  (*persistent).savePowerControlState(newState);
}

bool ModelPersistent::getSavedPowerControlState() {
  return (*persistent).getSavedPowerControlState();
}

void ModelPersistent::saveLedConfigData(LedConfigData ledConfigData) {
  (*persistent).saveLedConfigData(ledConfigData);
}

LedConfigData ModelPersistent::getSavedLedConfigData() {
  return (*persistent).getSavedLedConfigData();
}