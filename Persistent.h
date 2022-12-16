#include "WString.h"
#include <EEPROM.h>

enum LocalStateAuth {
  notRegistered,
  registering,
  registered,
};

LocalStateAuth localStateAuth = notRegistered;
int idDevice;

void updateRegistered() {
  localStateAuth = idDevice == 0 ? notRegistered : registered;
}

void pullPersistentData() {
  EEPROM.begin(sizeof(idDevice));
  idDevice = EEPROM.read(0);
  EEPROM.end();
  updateRegistered();
  Serial.println("ID");
  Serial.println(idDevice);
}

void savePersistentData() {
  EEPROM.begin(sizeof(idDevice));
  EEPROM.write(0, idDevice);
  EEPROM.commit();
  EEPROM.end();
  updateRegistered();
}