#include "WString.h"
#include <EEPROM.h>

#define API_PKG_SYMB "^"
#define API_DELIMITER ":"

struct ParsedHeaderPayload {
  String header;
  String payload;
};

struct ParsedRgba {
  int r;
  int g;
  int b;
  int a;
};

struct StringParser {
  void reset() {
    from = to = -1;
  }
  bool update(String& s, String div = API_DELIMITER) {
    if (to == s.length()) return 0;
    from = to + 1;
    to = s.indexOf(div, from);
    if (to < 0) to = s.length();
    str = s.substring(from, to);
    return 1;
  }
  String str;
  int from = -1;
  int to = -1;
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
  const char* idChar = idStr.c_str();

  strcat(api, API_PKG_SYMB);
  strcat(api, idChar);
  strcat(api, API_DELIMITER);
  strcat(api, typeDevice.c_str());
  strcat(api, API_PKG_SYMB);

  return api;
}

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

ParsedRgba parseRgba(String data) {
  ParsedRgba parsedRgba;
  StringParser pars;
  uint8_t index = 0;

  while (pars.update(data)) {
    switch (index) {
      case 0:
        parsedRgba.r = pars.str.toInt();
        break;
      case 1:
        parsedRgba.g = pars.str.toInt();
        break;
      case 2:
        parsedRgba.b = pars.str.toInt();
        break;
      case 3:
        parsedRgba.a = pars.str.toInt();
        break;
    }
    index++;
  }

  return parsedRgba;
}
