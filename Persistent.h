#include "WString.h"
#include "DataConstruct.h"
#include <EEPROM.h>

#define SIZE_EEPROM 512

bool registered = false;
int idDevice;

void updateRegisteredState() {
  registered = idDevice != -1;
  Serial.println("registered");
  Serial.println(registered);
}

void saveIdDevice(int newId) {
  idDevice = newId;

  EEPROM.begin(sizeof(idDevice));
  EEPROM.put(0, idDevice);
  EEPROM.commit();
  EEPROM.end();

  updateRegisteredState();
}

void setupPersistent() {
  EEPROM.begin(SIZE_EEPROM);
  EEPROM.get(0, idDevice);
  EEPROM.end();
  updateRegisteredState();
  Serial.println("ID");
  Serial.println(idDevice);
}

int getAddressForSavingSideData() {
  int sizeIdDevice = sizeof(idDevice);
  sizeIdDevice++;
  return sizeIdDevice;
}

void savePowerControlState(bool newState) {
  EEPROM.begin(SIZE_EEPROM);
  EEPROM.put(getAddressForSavingSideData(), newState);
  EEPROM.commit();
  EEPROM.end();
}

bool getSavedPowerControlState() {
  bool state = false;

  EEPROM.begin(SIZE_EEPROM);
  EEPROM.get(getAddressForSavingSideData(), state);
  EEPROM.end();

  return state;
}

void saveLedConfigData(LedConfigData ledConfigData) {
  int startAddress = getAddressForSavingSideData();

  int sizeH = sizeof(ledConfigData.h);
  sizeH++;
  int sizeS = sizeof(ledConfigData.s);
  sizeS++;
  int sizeV = sizeof(ledConfigData.v);
  sizeV++;

  EEPROM.begin(SIZE_EEPROM);
  EEPROM.put(startAddress, ledConfigData.h);
  EEPROM.put(startAddress + sizeH, ledConfigData.s);
  EEPROM.put(startAddress + sizeH + sizeS, ledConfigData.v);
  EEPROM.put(startAddress + sizeH + sizeS + sizeV, ledConfigData.mode);
  EEPROM.commit();
  EEPROM.end();
}

LedConfigData getSavedLedConfigData() {
  LedConfigData ledConfigData;

  int startAddress = getAddressForSavingSideData();

  int sizeH = sizeof(ledConfigData.h);
  sizeH++;
  int sizeS = sizeof(ledConfigData.s);
  sizeS++;
  int sizeV = sizeof(ledConfigData.v);
  sizeV++;

  EEPROM.begin(SIZE_EEPROM);
  EEPROM.get(startAddress, ledConfigData.h);
  EEPROM.get(startAddress + sizeH, ledConfigData.s);
  EEPROM.get(startAddress + sizeH + sizeS, ledConfigData.v);
  EEPROM.get(startAddress + sizeH + sizeS + sizeV, ledConfigData.mode);
  EEPROM.end();

  return ledConfigData;
}
