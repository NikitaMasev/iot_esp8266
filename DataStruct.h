#pragma once

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