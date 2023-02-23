#pragma once

#include "WString.h"

#define SIZE_TYPE_CONTROL_MAP 6

enum TypeDevice {
  ups,
  lamp,
  rgba,
  rgbaAddress,
  tempSensor,
  unknown,
};

enum TypeControl {
  powerOn_c,
  powerOff_c,
  rgba_c,
  rgbaEffects_c,
  register_c,
  reset_c,
  unknown_c,
};

#if defined(TYPE_DEVICE_UPS)
const TypeDevice currentTypeDevice = ups;
#elif defined(TYPE_DEVICE_LAMP)
const TypeDevice currentTypeDevice = lamp;
#elif defined(TYPE_DEVICE_RGBA)
const TypeDevice currentTypeDevice = rgba;
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
const TypeDevice currentTypeDevice = rgbaAddress;
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
const TypeDevice currentTypeDevice = tempSensor;
#elif
const TypeDevice currentTypeDevice = unknown;
#endif

const static struct {
  TypeDevice val;
  const char *str;
} typeDeviceToStr[] = {
  { ups, "ups" },
  { lamp, "lamp" },
  { rgba, "rgba" },
  { rgbaAddress, "rgbaAddress" },
  { tempSensor, "tempSensor" },
  { unknown, "unknown" },
};

const static struct {
  TypeControl val;
  const char *str;
} typeControlToStr[] = {
  { powerOn_c, "powerOn" },
  { powerOff_c, "powerOff" },
  { rgba_c, "rgba" },
  { rgbaEffects_c, "rgbaEffects" },
  { register_c, "register" },
  { reset_c, "reset" },
  { unknown_c, "unknown" },
};

const static struct {
  TypeDevice typeDevice;
  TypeControl typeControl[SIZE_TYPE_CONTROL_MAP];
} typeDeviceToTypeControl[] = {
  { ups, { register_c, reset_c } },
  { lamp, { powerOn_c, powerOff_c, register_c, reset_c } },
  { rgba, { register_c, rgba_c, reset_c } },
  { rgbaAddress, { register_c, rgbaEffects_c, reset_c } },
  { tempSensor, { register_c, reset_c } },
  { unknown, {} },
};

inline TypeDevice stringToTypeDevice(const char *str) {
  for (int j = 0; j < sizeof(typeDeviceToStr) / sizeof(typeDeviceToStr[0]); ++j) {
    if (!strcmp(typeDeviceToStr[j].str, str)) {
      return typeDeviceToStr[j].val;
    }
  }
  return unknown;
}

inline String typeDeviceToString(TypeDevice typeDevice) {
  for (int j = 0; j < sizeof(typeDeviceToStr) / sizeof(typeDeviceToStr[0]); ++j) {
    if (typeDevice == typeDeviceToStr[j].val) {
      return typeDeviceToStr[j].str;
    }
  }
  return typeDeviceToStr[unknown].str;
}

inline TypeControl stringToTypeControl(const char *str) {
  for (int j = 0; j < sizeof(typeControlToStr) / sizeof(typeControlToStr[0]); ++j) {
    if (!strcmp(typeControlToStr[j].str, str)) {
      return typeControlToStr[j].val;
    }
  }
  return unknown_c;
}

inline String typeControlToString(TypeControl typeControl) {
  for (int j = 0; j < sizeof(typeControlToStr) / sizeof(typeControlToStr[0]); ++j) {
    if (typeControl == typeControlToStr[j].val) {
      return typeControlToStr[j].str;
    }
  }
  return typeControlToStr[unknown_c].str;
}

inline bool allowedTypeControl(TypeControl typeControl) {
  for (int i = 0; i < sizeof(typeDeviceToTypeControl) / sizeof(typeDeviceToTypeControl[0]); i++) {
    if (typeDeviceToTypeControl[i].typeDevice == currentTypeDevice) {
      for (int j = 0; j < sizeof(typeDeviceToTypeControl[i].typeControl) / sizeof(typeDeviceToTypeControl[i].typeControl[0]); j++) {
        if (typeDeviceToTypeControl[i].typeControl[j] == typeControl) {
          return true;
        }
      }
      return false;
    }
  }
  return false;
}
