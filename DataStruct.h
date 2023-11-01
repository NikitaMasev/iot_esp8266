#pragma once

#include "WString.h"

struct ParsedHeaderPayload {
  String header;
  String payload;
};

struct LedConfigData {
  int h;
  int s;
  int v;
  int mode;
  bool powerOn;
};

struct LedCctConfigData {
  int brightness;
  int colorTemperature;
  bool powerOn;
};