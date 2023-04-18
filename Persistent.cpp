#include "Persistent.h"
#include "Arduino.h"

#define SIZE_EEPROM 512

void Persistent::setup() {
  EEPROM.begin(SIZE_EEPROM);
  EEPROM.get(0, idDevice);
  EEPROM.commit();
  EEPROM.end();
  updateRegisteredState();
  Serial.println("ID");
  Serial.println(idDevice);
}

void Persistent::updateRegisteredState() {
  registered = idDevice != -1;
}

void Persistent::saveId(int newId) {
  idDevice = newId;

  EEPROM.begin(SIZE_EEPROM);
  EEPROM.put(0, idDevice);
  EEPROM.commit();
  EEPROM.end();

  updateRegisteredState();
}

bool Persistent::getRegistered() {
  this->setup();
  return registered;
}

int Persistent::getSavedId() {
  this->setup();
  return idDevice;
}

int Persistent::getAddressForSavingSideData() {
  int sizeIdDevice = sizeof(idDevice);
  sizeIdDevice++;
  return sizeIdDevice;
}

void Persistent::savePowerControlState(bool newState) {
  EEPROM.begin(SIZE_EEPROM);
  EEPROM.put(getAddressForSavingSideData(), newState ? 1 : 0);
  EEPROM.commit();
  EEPROM.end();
}

bool Persistent::getSavedPowerControlState() {
  int data = 0;

  EEPROM.begin(SIZE_EEPROM);
  EEPROM.get(getAddressForSavingSideData(), data);
  EEPROM.end();

  // Serial.println("getSavedPowerControlState");
  // Serial.println(data);
  // Serial.println(!(data == -1 || data == 0));

  return !(data == -1 || data == 0);
}

void Persistent::saveLedConfigData(LedConfigData ledConfigData) {
  int startAddress = getAddressForSavingSideData();

  int sizeH = sizeof(ledConfigData.h);
  sizeH++;
  int sizeS = sizeof(ledConfigData.s);
  sizeS++;
  int sizeV = sizeof(ledConfigData.v);
  sizeV++;
  int sizeMode = sizeof(ledConfigData.mode);
  sizeMode++;

  EEPROM.begin(SIZE_EEPROM);
  EEPROM.put(startAddress, ledConfigData.h);
  EEPROM.put(startAddress + sizeH, ledConfigData.s);
  EEPROM.put(startAddress + sizeH + sizeS, ledConfigData.v);
  EEPROM.put(startAddress + sizeH + sizeS + sizeV, ledConfigData.mode);
  EEPROM.put(startAddress + sizeH + sizeS + sizeV + sizeMode, ledConfigData.powerOn ? 1 : 0);
  EEPROM.commit();
  EEPROM.end();


  // Serial.println("saveLedConfigData");
  // Serial.println("ledConfigData.h");
  // Serial.println(ledConfigData.h);
  // Serial.println("ledConfigData.s");
  // Serial.println(ledConfigData.s);
  // Serial.println("ledConfigData.v");
  // Serial.println(ledConfigData.v);
  // Serial.println("ledConfigData.mode");
  // Serial.println(ledConfigData.mode);
  // Serial.println("ledConfigData.powerOn");
  // Serial.println(ledConfigData.powerOn);
}

LedConfigData Persistent::getSavedLedConfigData() {
  LedConfigData ledConfigData;
  int powerOn = 0;

  int startAddress = getAddressForSavingSideData();

  int sizeH = sizeof(ledConfigData.h);
  sizeH++;
  int sizeS = sizeof(ledConfigData.s);
  sizeS++;
  int sizeV = sizeof(ledConfigData.v);
  sizeV++;
  int sizeMode = sizeof(ledConfigData.mode);
  sizeMode++;

  EEPROM.begin(SIZE_EEPROM);
  EEPROM.get(startAddress, ledConfigData.h);
  EEPROM.get(startAddress + sizeH, ledConfigData.s);
  EEPROM.get(startAddress + sizeH + sizeS, ledConfigData.v);
  EEPROM.get(startAddress + sizeH + sizeS + sizeV, ledConfigData.mode);
  EEPROM.get(startAddress + sizeH + sizeS + sizeV + sizeMode, powerOn);
  EEPROM.end();

  ledConfigData.powerOn = powerOn == 1;

  // Serial.println("getSavedLedConfigData");
  // Serial.println("ledConfigData.h");
  // Serial.println(ledConfigData.h);
  // Serial.println("ledConfigData.s");
  // Serial.println(ledConfigData.s);
  // Serial.println("ledConfigData.v");
  // Serial.println(ledConfigData.v);
  // Serial.println("ledConfigData.mode");
  // Serial.println(ledConfigData.mode);
  // Serial.println("ledConfigData.powerOn");
  // Serial.println(ledConfigData.powerOn);

  return ledConfigData;
}