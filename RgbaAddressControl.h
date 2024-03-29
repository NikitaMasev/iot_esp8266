#pragma once

#include "DataStruct.h"
#include "RgbaAddressEffectsUtil.h"
#include "LedAddrConfig.h"

class RgbaAddressControl {
private:
  struct CRGB leds[LED_COUNT] = {};
  RgbaAddressEffectsUtil rgbaAddressEffectsUtil;

  LedConfigData ledConfigData = {
    h: 100,
    s: 255,
    v: 180,
    mode: 3,
    powerOn: true,
  };

  long lastTimeUpdateLed = 0;

  void applyLedInternalConfig();
public:
  RgbaAddressControl()
    : rgbaAddressEffectsUtil(leds) {
    LEDS.addLeds<WS2811, LED_DT, BRG>(leds, LED_COUNT);
    rgbaAddressEffectsUtil.one_color_all(0, 0, 0);
    LEDS.show();

    applyLedInternalConfig();
    rgbaAddressEffectsUtil.updateConfig(ledConfigData);
    LEDS.show();

    randomSeed(analogRead(0));
  };

  void nextEffect();
  void previousEffect();
  void updateLedAddressConfig(LedConfigData newConfigData);
  void updatePower(bool powerOn);
  LedConfigData getLedAddressConfig();
  void tick();
};
