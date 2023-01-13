#include "WString.h"
#include "DataStruct.h"
#include <EEPROM.h>

#define PKG_CMD_SYMB "^"
#define PKG_CMD_DELIMITER_SYMB ":"
#define START_PKG_DATA_SYMB "#"
#define DELIMITER_IOT_DATA_SYMB "/"
#define END_PKG_DATA_SYMB ";"

struct StringParser {
  void reset() {
    from = to = -1;
  }
  bool update(String& s, String div = PKG_CMD_DELIMITER_SYMB) {
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
  String apiStr;

  uint8_t lengthApiChar = String(PKG_CMD_SYMB).length() * 2;
  uint8_t fullLength = lengthApiChar + String(typeDevice).length();
  char api[fullLength];

  strcat(api, String(PKG_CMD_SYMB).c_str());
  strcat(api, typeDevice.c_str());
  strcat(api, String(PKG_CMD_SYMB).c_str());

  apiStr = api;

  return apiStr;
}

String constructAuth(int idDevice, String typeDevice) {
  String apiStr;

  uint8_t lengthApiChar = String(PKG_CMD_SYMB).length() * 2
                          + String(PKG_CMD_DELIMITER_SYMB).length();

  String idStr = String(idDevice);
  char api[lengthApiChar + idStr.length()];
  const char* idChar = idStr.c_str();

  strcat(api, PKG_CMD_SYMB);
  strcat(api, idChar);
  strcat(api, PKG_CMD_DELIMITER_SYMB);
  strcat(api, typeDevice.c_str());
  strcat(api, PKG_CMD_SYMB);

  apiStr = api;
  return apiStr;
}

ParsedHeaderPayload parseTextData(String data) {
  ParsedHeaderPayload headerPayload;

  uint8_t indexStart = data.indexOf(PKG_CMD_SYMB) + 1;
  uint8_t indexEnd = data.lastIndexOf(PKG_CMD_SYMB);

  String parsed = data.substring(indexStart, indexEnd);
  uint8_t indexFirstDelimiter = data.indexOf(PKG_CMD_DELIMITER_SYMB);

  headerPayload.header = parsed.substring(0, indexFirstDelimiter - 1);
  headerPayload.payload = parsed.substring(indexFirstDelimiter);

  return headerPayload;
}

LedConfigData parseLedConfig(String data) {
  LedConfigData ledConfigData;
  StringParser pars;
  uint8_t index = 0;

  while (pars.update(data)) {
    switch (index) {
      case 0:
        ledConfigData.h = pars.str.toInt();
        break;
      case 1:
        ledConfigData.s = pars.str.toInt();
        break;
      case 2:
        ledConfigData.v = pars.str.toInt();
        break;
      case 3:
        ledConfigData.mode = pars.str.toInt();
        break;
    }
    index++;
  }

  return ledConfigData;
}

String constructUpsData(
  float tempUps,
  float tempAcc,
  int pwmCooler,
  float currentDC,
  float voltageDC) {
  String dataStr;
  char data[32] = "";
  char tmp[8] = "";

  strcat(data, START_PKG_DATA_SYMB);
  dtostrf(tempUps, 4, 2, tmp);
  strcat(data, tmp);
  strcat(data, DELIMITER_IOT_DATA_SYMB);
  dtostrf(tempAcc, 4, 2, tmp);
  strcat(data, tmp);
  strcat(data, DELIMITER_IOT_DATA_SYMB);
  itoa(pwmCooler, tmp, DEC);
  strcat(data, tmp);
  strcat(data, DELIMITER_IOT_DATA_SYMB);
  //itoa(currentDC, tmp, DEC);
  dtostrf(currentDC, 4, 2, tmp);
  strcat(data, tmp);
  strcat(data, DELIMITER_IOT_DATA_SYMB);
  dtostrf(voltageDC, 4, 2, tmp);
  strcat(data, tmp);
  strcat(data, END_PKG_DATA_SYMB);

  dataStr = data;
  return dataStr;
}

String constructLedConfigData(LedConfigData ledConfigData) {
  String dataStr;
  char data[30] = "";
  char tmp[8] = "";

  strcat(data, START_PKG_DATA_SYMB);
  itoa(ledConfigData.h, tmp, DEC);
  strcat(data, tmp);
  strcat(data, DELIMITER_IOT_DATA_SYMB);
  itoa(ledConfigData.s, tmp, DEC);
  strcat(data, tmp);
  strcat(data, DELIMITER_IOT_DATA_SYMB);
  itoa(ledConfigData.v, tmp, DEC);
  strcat(data, tmp);
  strcat(data, DELIMITER_IOT_DATA_SYMB);
  itoa(ledConfigData.mode, tmp, DEC);
  strcat(data, tmp);
  strcat(data, END_PKG_DATA_SYMB);

  dataStr = data;
  return dataStr;
}

String constructSwitchData(bool powerState) {
  String dataStr;
  char data[8] = "";
  char tmp[8] = "";

  strcat(data, START_PKG_DATA_SYMB);
  itoa(powerState, tmp, DEC);
  strcat(data, tmp);
  strcat(data, END_PKG_DATA_SYMB);

  dataStr = data;
  return dataStr;
}

String constructTempsData(float temps[], int length) {
  String dataStr;
  char data[4 * length] = "";
  char tmp[8] = "";

  strcat(data, START_PKG_DATA_SYMB);

  for (int i = 0; i < length; i++) {
    dtostrf(temps[i], 4, 2, tmp);
    strcat(data, tmp);
    if (i + 1 != length) {
      strcat(data, DELIMITER_IOT_DATA_SYMB);
    }
  }

  strcat(data, END_PKG_DATA_SYMB);

  dataStr = data;
  return dataStr;
}
