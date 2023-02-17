#pragma once

#define FASTLED_INTERRUPT_RETRY_COUNT 0  // fix flickering first led
//#define FASTLED_ALLOW_INTERRUPTS 0
//#define INTERRUPT_THRESHOLD 1
//#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>
#include "DataStruct.h"

class RgbaAddressControl {
private:
  LedConfigData ledConfigData = {
    h: 100,
    s: 255,
    v: 180,
    mode: 10,
    powerOn: true,
  };
  struct CRGB leds[LED_COUNT];
  int ledsX[LED_COUNT][3];  //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

  int thisdelay = 20;  //-FX LOOPS DELAY VAR
  int thisstep = 10;   //-FX LOOPS DELAY VAR
  long lastTimeUpdateLed = 0;

  void updatePowerState();
  void applyLedInternalConfig();
public:
  RgbaAddressControl();
  void updateLedAddressConfig(LedConfigData newConfigData);
  void tick();
};
