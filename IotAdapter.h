#include "WString.h"
#include "DataConstruct.h"
#include "Persistent.h"
#include "TypeDevice.h"
#include "Config.h"
#if defined(TYPE_DEVICE_LAMP)
#include "PowerControl.h"
#endif
#if defined(TYPE_DEVICE_UPS)
#include "CoolerControl.h"
#include "VoltCur.h"
#endif
#if defined(TYPE_DEVICE_RGBA)
#include "RgbaControl.h"
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
#include "RgbaAddressControl.h"
#endif

const char* empty = "";

void setupAdapter() {
#if defined(TYPE_DEVICE_UPS)
  setupCoolerControl();
  setupVoltageCurrentSensor();
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
  currentTypeDevice = tempSensor;
#endif
}

String adaptConnected() {
  switch (localStateAuth) {
    case notRegistered:
      return constructRegister(typeDeviceToString(currentTypeDevice));
    case registering:
      ///registering after adaptConnected function
      return empty;
    case registered:
      return constructAuth(idDevice, typeDeviceToString(currentTypeDevice));
  }
  return empty;
}

String handleRegister(String payload) {
  int newId = payload.toInt();
  updateIdDevice(newId);
  return empty;
}

String handlePower(bool controlOn) {
#if defined(TYPE_DEVICE_LAMP)
  updatePower(controlOn);
#endif
#if defined(TYPE_DEVICE_RGBA)
  updateLedPower(controlOn);
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
  updateLedAddressPower(controlOn);
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

String adaptText(String data) {
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