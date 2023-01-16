#include "WString.h"
#include <GyverOS.h>
#include "TypeDevice.h"
#include "Config.h"
#if defined(TYPE_DEVICE_LAMP)
#include "PowerControl.h"
#endif
#if defined(TYPE_DEVICE_UPS)
#include "Persistent.h"
#include "CoolerControl.h"
#include "VoltCur.h"
#endif
#if defined(TYPE_DEVICE_RGBA)
#include "RgbaControl.h"
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
#include "RgbaAddressControl.h"
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
#include "Persistent.h"
#include "TempDetector.h"
#endif

const char* empty = "";

#if defined(TYPE_DEVICE_UPS)
GyverOS<3> tasker;
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
GyverOS<1> tasker;
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
GyverOS<1> tasker;
#endif

void setupIotController() {
  setupPersistent();
#if defined(TYPE_DEVICE_UPS)
  setupCoolerControl();
  setupVoltageCurrentSensor();
  setupTempDetector();

  tasker.attach(0, loopCooler, 5000);
  tasker.attach(1, loopTempDetector, 750);
  tasker.attach(2, loopVoltCur, 200);

  currentTypeDevice = ups;
#elif defined(TYPE_DEVICE_LAMP)
  setupPowerControl();
  currentTypeDevice = lamp;
#elif defined(TYPE_DEVICE_RGBA)
  setupLedControl();
  currentTypeDevice = rgba;
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  setupLedAddressControl();
  tasker.attach(0, loopLedAddress, 50);
  currentTypeDevice = rgbaAddress;
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  setupTempDetector();
  tasker.attach(0, loopTempDetector, 750);
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

String controlIncomingText(String data) {
  ParsedHeaderPayload headerPayload = parseTextData(data);

  Serial.println("headerPayload.header");
  Serial.println(headerPayload.header);
  Serial.println("headerPayload.payload");
  Serial.println(headerPayload.payload);

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

void loopController() {
// #if defined(TYPE_DEVICE_RGBA_ADDRESS)
//   loopLedAddress();
// #endif
#if defined(TYPE_DEVICE_UPS) || defined(TYPE_DEVICE_RGBA_ADDRESS) || defined(TYPE_DEVICE_TEMP_SENSOR)
  tasker.tick();
#endif
}