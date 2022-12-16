#include "WString.h"
#include <EEPROM.h>

#define API_PKG_SYMB "^"
#define API_DELIMITER ":"

struct ParsedHeaderPayload {
  String header;
  String payload;
};

String constructRegister(String typeDevice) {
  uint8_t lengthApiChar = String(API_PKG_SYMB).length() * 2
                          + String(API_DELIMITER).length();

  char api[lengthApiChar + String(typeDevice).length()];

  strcat(api, API_PKG_SYMB);
  strcat(api, typeDevice.c_str());
  strcat(api, API_PKG_SYMB);

  return api;
}

String constructAuth(int idDevice, String typeDevice) {
  uint8_t lengthApiChar = String(API_PKG_SYMB).length() * 2
                          + String(API_DELIMITER).length();

  String idStr = String(idDevice);
  char api[lengthApiChar + idStr.length()];
  const char *idChar = idStr.c_str();

  strcat(api, API_PKG_SYMB);
  strcat(api, idChar);
  strcat(api, API_DELIMITER);
  strcat(api, typeDevice.c_str());
  strcat(api, API_PKG_SYMB);

  return api;
}

// void removeSignP(String data) {
//   uint8_t indexStart = data.indexOf(API_PKG_SYMB) + 1;
//   uint8_t indexEnd = data.lastIndexOf(API_PKG_SYMB);

//   String cmd = data.substring(indexStart, indexEnd);
//   id = cmd.toInt();

//   saveId();
// }

ParsedHeaderPayload parseTextData(String data) {
  ParsedHeaderPayload headerPayload;

  uint8_t indexStart = data.indexOf(API_PKG_SYMB) + 1;
  uint8_t indexEnd = data.lastIndexOf(API_PKG_SYMB);

  String parsed = data.substring(indexStart, indexEnd);
  uint8_t indexFirstDelimiter = data.indexOf(API_DELIMITER);

  headerPayload.header = parsed.substring(0, indexFirstDelimiter);
  headerPayload.payload = parsed.substring(indexFirstDelimiter + 1);

  return headerPayload;
}
