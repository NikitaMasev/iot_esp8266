#include "core_esp8266_features.h"
#include "WString.h"
#include "IotController.h"

#define TIME_DATA_PUSH 200

long lastTimeUpdateDataPusher;

String loopDataPusher() {
  if (millis() - lastTimeUpdateDataPusher > TIME_DATA_PUSH) {
    lastTimeUpdateDataPusher = millis();

#if defined(TYPE_DEVICE_LAMP)
    return constructSwitchData(powerState);
#endif
#if defined(TYPE_DEVICE_UPS)
    return constructUpsData(temps[0], temps[1], pwmCooler, currentDC, voltageDC);
#endif
#if defined(TYPE_DEVICE_RGBA)
    return constructLedConfigData(ledConfigData);
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
    return constructLedConfigData(ledConfigData);
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
    return constructTempsData(temps, TEMP_SENSOR_COUNT);
#endif
  }

  return empty;
}