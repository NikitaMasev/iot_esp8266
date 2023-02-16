#pragma once

#include "WString.h"
#include "CryptoAesUtil.h"
#include "Network.h"
#include "Config.h"
#include "DataConstruct.h"

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

CryptoAesUtil cryptoAes;

void loopDataPusher() {
  //if (!iotServerConnected) return;

  String dataForService = "";

#if defined(TYPE_DEVICE_LAMP)
  dataForService = constructSwitchData(powerState);
#endif
#if defined(TYPE_DEVICE_UPS)
  dataForService = constructUpsData(temps[0], temps[1], pwmCooler, currentDC, voltageDC);
#endif
#if defined(TYPE_DEVICE_RGBA)
  dataForService = constructLedConfigData(ledConfigData);
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
  dataForService = constructLedConfigData(ledConfigData);
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
  dataForService = constructTempsData(temps, TEMP_SENSOR_COUNT);
#endif

  if (!dataForService.isEmpty()) {
    // String encrypted = cryptoAes.encrypt(dataForService);
    // client.send(encrypted);
  }
}