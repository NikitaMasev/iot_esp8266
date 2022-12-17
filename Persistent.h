#include "WString.h"
#include <EEPROM.h>

enum LocalStateAuth {
  notRegistered,
  registering,
  registered,
};

LocalStateAuth localStateAuth = notRegistered;
int idDevice;

void updateLocalStateById() {
  localStateAuth = idDevice == 0 ? notRegistered : registered;
}

void savePersistentData() {
  EEPROM.begin(sizeof(idDevice));
  EEPROM.write(0, idDevice);
  EEPROM.commit();
  EEPROM.end();
  updateLocalStateById();
}

void updateIdDevice(int newId) {
  idDevice = newId;
  savePersistentData();
  updateLocalStateById();
}

void pullPersistentData() {
  EEPROM.begin(sizeof(idDevice));
  idDevice = EEPROM.read(0);
  EEPROM.end();
  updateLocalStateById();
  Serial.println("ID");
  Serial.println(idDevice);
}