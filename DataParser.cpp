#include "DataParser.h"
#include "Config.h"

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

ParsedHeaderPayload DataParser::parseTextData(String data) {
  ParsedHeaderPayload headerPayload;

  uint8_t indexStart = data.indexOf(PKG_CMD_SYMB) + 1;
  uint8_t indexEnd = data.lastIndexOf(PKG_CMD_SYMB);

  String parsed = data.substring(indexStart, indexEnd);
  uint8_t indexFirstDelimiter = data.indexOf(PKG_CMD_DELIMITER_SYMB);

  headerPayload.header = parsed.substring(0, indexFirstDelimiter - 1);
  headerPayload.payload = parsed.substring(indexFirstDelimiter);

  return headerPayload;
}

LedConfigData DataParser::parseLedConfig(String data) {
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
      case 4:
        ledConfigData.powerOn = pars.str.toInt() == 1;
        break;
    }
    index++;
  }

  return ledConfigData;
}

LedCctConfigData DataParser::parseLedCctConfig(String data) {
  LedCctConfigData ledCctConfigData;
  StringParser pars;
  uint8_t index = 0;

  while (pars.update(data)) {
    switch (index) {
      case 0:
        ledCctConfigData.brightness = pars.str.toInt();
        break;
      case 1:
        ledCctConfigData.colorTemperature = pars.str.toInt();
        break;
      case 2:
        ledCctConfigData.powerOn = pars.str.toInt() == 1;
        break;
    }
    index++;
  }

  return ledCctConfigData;
}