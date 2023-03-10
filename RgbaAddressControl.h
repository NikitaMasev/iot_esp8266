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
    mode: 10,
    powerOn: true,
  };

  long lastTimeUpdateLed = 0;

  void updatePowerState();
  void applyLedInternalConfig();
public:
  RgbaAddressControl()
    : rgbaAddressEffectsUtil(leds) {
    rgbaAddressEffectsUtil.updateConfig(ledConfigData);
    LEDS.addLeds<WS2811, LED_DT, BRG>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
    rgbaAddressEffectsUtil.one_color_all(0, 0, 0);       // погасить все светодиоды
    LEDS.show();                                         // отослать команду

    randomSeed(analogRead(0));
  };
  
  void nextEffect();
  void previousEffect();
  void updateLedAddressConfig(LedConfigData newConfigData);
  LedConfigData getLedAddressConfig();
  void tick();
};
