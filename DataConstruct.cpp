#include "DataConstruct.h"
#include "Config.h"
#include "Arduino.h"

String DataConstruct::constructRegister(String typeDevice) {
  String apiStr;
  uint8_t lengthApiChar = String(PKG_CMD_SYMB).length() * 2;
  uint8_t fullLength = lengthApiChar + String(typeDevice).length();
  char api[fullLength] = "";

  strcat(api, String(PKG_CMD_SYMB).c_str());
  strcat(api, typeDevice.c_str());
  strcat(api, String(PKG_CMD_SYMB).c_str());

  apiStr = api;
  return apiStr;
}

String DataConstruct::constructAuth(int idDevice, String typeDevice) {
  String apiStr;
  uint8_t lengthApiChar = String(PKG_CMD_SYMB).length() * 2
                          + String(PKG_CMD_DELIMITER_SYMB).length();
  String idStr = String(idDevice);
  char api[lengthApiChar + idStr.length()] = "";

  strcat(api, PKG_CMD_SYMB);
  strcat(api, idStr.c_str());
  strcat(api, PKG_CMD_DELIMITER_SYMB);
  strcat(api, typeDevice.c_str());
  strcat(api, PKG_CMD_SYMB);

  apiStr = api;
  return apiStr;
}

String DataConstruct::constructUpsData(
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

String DataConstruct::constructLedConfigData(LedConfigData ledConfigData) {
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
  strcat(data, DELIMITER_IOT_DATA_SYMB);
  itoa(ledConfigData.powerOn ? 1 : 0, tmp, DEC);
  strcat(data, tmp);
  strcat(data, END_PKG_DATA_SYMB);

  dataStr = data;
  return dataStr;
}

String DataConstruct::constructSwitchData(bool powerState) {
  String dataStr;
  char data[8] = "";
  char tmp[8] = "";

  strcat(data, START_PKG_DATA_SYMB);
  itoa(powerState ? 1 : 0, tmp, DEC);
  strcat(data, tmp);
  strcat(data, END_PKG_DATA_SYMB);
  dataStr = data;

  return dataStr;
}

String DataConstruct::constructTempsData(float temps[], int length) {
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