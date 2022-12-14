#include "WString.h"
#include <EEPROM.h>

#define API_PKG_SYMB "^"
#define API_DELIMITER ":"
#define TYPE_DEVICE "wifi_ups_helper"

int id;
bool connected = false;
bool registered = false;
bool registering = false;

String getRegisterOrAuthData() {
  uint8_t lengthApiChar = String(API_PKG_SYMB).length() * 2
                          + String(API_DELIMITER).length();
  String apiStr;

  if (registered) {
    String idStr = String(id);
    char api[lengthApiChar + idStr.length()];
    const char *idChar = idStr.c_str();

    strcat(api, API_PKG_SYMB);
    strcat(api, idChar);
    strcat(api, API_DELIMITER);
    strcat(api, TYPE_DEVICE);
    strcat(api, API_PKG_SYMB);

    apiStr = api;
  } else {
    char api[lengthApiChar + String(TYPE_DEVICE).length()];

    strcat(api, API_PKG_SYMB);
    strcat(api, TYPE_DEVICE);
    strcat(api, API_PKG_SYMB);

    registering = true;
    apiStr = api;
  }
  return apiStr;
  // String encryptedApi = encrypt(apiStr);
  // webSocket.sendTXT(encryptedApi);
}

void updateRegistered() {
  registered = id != 0;
  registering = false;
}

void getAndCheckId() {
  EEPROM.begin(sizeof(id));
  id = EEPROM.read(0);
  EEPROM.end();
  updateRegistered();
  Serial.println("ID");
  Serial.println(id);
}

void saveId() {
  EEPROM.begin(sizeof(id));
  EEPROM.write(0, id);
  EEPROM.commit();
  EEPROM.end();
  updateRegistered();
}