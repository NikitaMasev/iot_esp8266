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
  EEPROM.put(getAddressForSavingSideData(), newState ? 1 : 0);
  EEPROM.commit();
  EEPROM.end();
}

bool getSavedPowerControlState() {
  int data = 0;

  EEPROM.begin(SIZE_EEPROM);
  EEPROM.get(getAddressForSavingSideData(), data);
  EEPROM.end();

  Serial.println("getSavedPowerControlState");
  Serial.println(data);
  Serial.println(!(data == -1 || data == 0));

  return !(data == -1 || data == 0);
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

  
  Serial.println("saveLedConfigData");
  Serial.println("ledConfigData.h");
  Serial.println(ledConfigData.h);
  Serial.println("ledConfigData.s");
  Serial.println(ledConfigData.s);
  Serial.println("ledConfigData.v");
  Serial.println(ledConfigData.v);
  Serial.println("ledConfigData.mode");
  Serial.println(ledConfigData.mode);
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

  Serial.println("getSavedLedConfigData");
  Serial.println("ledConfigData.h");
  Serial.println(ledConfigData.h);
  Serial.println("ledConfigData.s");
  Serial.println(ledConfigData.s);
  Serial.println("ledConfigData.v");
  Serial.println(ledConfigData.v);
  Serial.println("ledConfigData.mode");
  Serial.println(ledConfigData.mode);

  return ledConfigData;
}
