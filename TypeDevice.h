#include "WString.h"

enum TypeDevice {
  ups,
  lamp,
  rgba,
  rgbaEffects,
  tempSensor,
  unknown,
};

enum TypeControl {
  powerOn_c,
  powerOff_c,
  rgba_c,
  rgbaEffects_c,
  changeName_c,
  register_c,
};

const static struct {
  TypeDevice val;
  const char *str;
} typeDeviceToStr[] = {
  { ups, "ups" },
  { lamp, "lamp" },
  { rgba, "rgba" },
  { rgbaEffects, "rgbaAddress" },
  { tempSensor, "tempSensor" },
  { unknown, "unknown" },
};

TypeDevice stringToTypeDevice(const char *str) {
  for (int j = 0; j < sizeof(typeDeviceToStr) / sizeof(typeDeviceToStr[0]); ++j) {
    if (strcmp(str, typeDeviceToStr[j].str)) {
      return typeDeviceToStr[j].val;
    }
  }
  return unknown;
}

String typeDeviceToString(TypeDevice typeDevice) {
  for (int j = 0; j < sizeof(typeDeviceToStr) / sizeof(typeDeviceToStr[0]); ++j) {
    if (typeDevice == typeDeviceToStr[j].val) {
      return typeDeviceToStr[j].str;
    }
  }
  return typeDeviceToStr[unknown].str;
}
