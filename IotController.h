#pragma once

#include "WString.h"
#include "TypeDevice.h"
#include "Config.h"
#include "Tasker.h"
#include "DataConstruct.h"
#include "Persistent.h"

#if defined(TYPE_DEVICE_LAMP)
#include "PowerControl.h"
#endif
#if defined(TYPE_DEVICE_UPS)
#include "CoolerControl.h"
#include "VoltCur.h"
#include "TempDetector.h"
#endif
#if defined(TYPE_DEVICE_RGBA)
#include "RgbaControl.h"
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
#include "RgbaAddressControl.h"
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
#include "TempDetector.h"
#endif

const char *empty = "";

void setupIotController() {
  setupPersistent();
  setupTasker();
#if defined(TYPE_DEVICE_UPS)
  setupCoolerControl();
  setupVoltageCurrentSensor();
  setupTempDetector();
  currentTypeDevice = ups;
#elif defined(TYPE_DEVICE_LAMP)
  setupPowerControl();
  currentTypeDevice = lamp;
#elif defined(TYPE_DEVICE_RGBA)
  setupLedControl();
  currentTypeDevice = rgba;
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  setupLedAddressControl();
  currentTypeDevice = rgbaAddress;
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  setupTempDetector();
  currentTypeDevice = tempSensor;
#endif
}

String controlConnected() {
  if (registered) {
    return constructAuth(idDevice, typeDeviceToString(currentTypeDevice));
  } else {
    return constructRegister(typeDeviceToString(currentTypeDevice));
  }
}

String handleRegister(String payload) {
  int newId = payload.toInt();
  saveIdDevice(newId);
  return empty;
}

String handleReset() {
  saveIdDevice(-1);
  return constructRegister(typeDeviceToString(currentTypeDevice));
}

String handlePower(bool controlOn) {
#if defined(TYPE_DEVICE_LAMP)
  updatePower(controlOn);
#endif
  return empty;
}

String handleRgba(String payload) {
  LedConfigData parsedLedConfig = parseLedConfig(payload);

#if defined(TYPE_DEVICE_RGBA)
  updateLedConfig(parsedLedConfig);
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
  updateLedAddressConfig(parsedLedConfig);
#endif
  return empty;
}

String controlIncomingText(String data) {
  ParsedHeaderPayload headerPayload = parseTextData(data);

  if (headerPayload.header.isEmpty()) {
    return empty;
  }

  TypeControl typeControl = stringToTypeControl(headerPayload.header.c_str());

  if (typeControl == unknown_c || !allowedTypeControl(typeControl)) {
    return empty;
  }

  switch (typeControl) {
    case register_c:
      return handleRegister(headerPayload.payload);
    case reset_c:
      return handleReset();
    case powerOff_c:
      return handlePower(false);
    case powerOn_c:
      return handlePower(true);
    case rgba_c:
    case rgbaEffects_c:
      return handleRgba(headerPayload.payload);
  }

  return empty;
}

void loopController() {
  loopTasker();
}
