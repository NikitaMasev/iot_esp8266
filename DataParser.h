#pragma once

#include "DataStruct.h"
#include "WString.h"

class DataParser {
public:
  ParsedHeaderPayload parseTextData(String data);
  LedConfigData parseLedConfig(String data);
};