#include "core_esp8266_features.h"
#include "RgbaAddressControl.h"

LedConfigData RgbaAddressControl::getLedAddressConfig() {
  return ledConfigData;
}

void RgbaAddressControl::updateLedAddressConfig(LedConfigData newConfigData) {
  if (newConfigData.h == -1 || newConfigData.s == -1 || newConfigData.v == -1) {
    return;
  }

  ledConfigData = newConfigData;
  rgbaAddressEffectsUtil.updateConfig(ledConfigData);
  updatePower(ledConfigData.powerOn);
  applyLedInternalConfig();
}

void RgbaAddressControl::updatePower(bool powerOn) {
  ledConfigData.powerOn = powerOn;

  if (powerOn) {
    LEDS.setBrightness(ledConfigData.v);  // ограничить максимальную яркость
  } else {
    LEDS.setBrightness(0);
  }
}

void RgbaAddressControl::nextEffect() {
  if (ledConfigData.mode != END_EFFECT_LED_ADDR) {
    ledConfigData.mode++;
    updateLedAddressConfig(ledConfigData);
  }
}

void RgbaAddressControl::previousEffect() {
  if (ledConfigData.mode != START_EFFECT_LED_ADDR) {
    ledConfigData.mode--;
    updateLedAddressConfig(ledConfigData);
  }
}

void RgbaAddressControl::applyLedInternalConfig() {
  switch (ledConfigData.mode) {
    case 2: rgbaAddressEffectsUtil.thisdelay = 60; break;  //---STRIP RAINBOW FADE
    case 3:
      rgbaAddressEffectsUtil.thisdelay = 20;
      rgbaAddressEffectsUtil.thisstep = 10;
      break;                                               //---RAINBOW LOOP
    case 4: rgbaAddressEffectsUtil.thisdelay = 20; break;  //---RANDOM BURST
    case 5:
      rgbaAddressEffectsUtil.thisdelay = 20;
      //ledConfigData.h = 0;
      break;  //---CYLON v1
    case 6:
      rgbaAddressEffectsUtil.thisdelay = 80;
      //ledConfigData.h = 30;
      break;  //---CYLON v2
    case 7:
      rgbaAddressEffectsUtil.thisdelay = 40;
      break;  //---POLICE LIGHTS SINGLE
    case 8:
      rgbaAddressEffectsUtil.thisdelay = 40;
      break;  //---POLICE LIGHTS SOLID
    case 9:
      ledConfigData.s = 50;
      rgbaAddressEffectsUtil.thisdelay = 35;
      break;  //---STRIP FLICKER
    case 10:
      rgbaAddressEffectsUtil.thisdelay = 15;
      //ledConfigData.h = 0;
      break;  //---PULSE COLOR BRIGHTNESS
    case 11:
      rgbaAddressEffectsUtil.thisdelay = 30;
      break;  //---PULSE COLOR SATURATION
    case 12:
      rgbaAddressEffectsUtil.thisdelay = 60;
      break;                                                 //---VERTICAL SOMETHING
    case 13: rgbaAddressEffectsUtil.thisdelay = 100; break;  //---CELL AUTO - RULE 30 (RED)
    case 14: rgbaAddressEffectsUtil.thisdelay = 80; break;   //---MARCH RANDOM COLORS
    case 15: rgbaAddressEffectsUtil.thisdelay = 80; break;   //---MARCH RWB COLORS
    case 16:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;
    case 17:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;  //---POP LEFT/RIGHT
    case 18:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;  //---QUADRATIC BRIGHTNESS CURVE
    case 19:
      rgbaAddressEffectsUtil.thisdelay = 0;
      break;
    case 20:
      rgbaAddressEffectsUtil.thisdelay = 50;
      rgbaAddressEffectsUtil.thisstep = 15;
      break;                                                //---VERITCAL RAINBOW
    case 21: rgbaAddressEffectsUtil.thisdelay = 35; break;  //---RANDOM COLOR POP
    case 22:
      rgbaAddressEffectsUtil.thisdelay = 25;
      break;  //---EMERGECNY STROBE
    case 23:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;  //---RGB PROPELLER
    case 24:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;  //---KITT
    case 25:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;                                                //---MATRIX RAIN
    case 26: rgbaAddressEffectsUtil.thisdelay = 15; break;  //---NEW RAINBOW LOOP
    case 27: rgbaAddressEffectsUtil.thisdelay = 50; break;  // colorWipe
    case 28: rgbaAddressEffectsUtil.thisdelay = 15; break;  // Fire
    case 29: rgbaAddressEffectsUtil.thisdelay = 20; break;  // rainbowCycle
    case 30: rgbaAddressEffectsUtil.thisdelay = 10; break;  // rainbowTwinkle
    case 31:
      rgbaAddressEffectsUtil.thisdelay = 50;
      break;                                                 // RunningLights
    case 32: rgbaAddressEffectsUtil.thisdelay = 100; break;  // Strobe
    case 33:
      rgbaAddressEffectsUtil.one_color_allHSV();
      LEDS.show();
      break;
    case 34: rgbaAddressEffectsUtil.thisdelay = 50; break;  // theaterChase
    case 35: rgbaAddressEffectsUtil.thisdelay = 50; break;  // theaterChaseRainbow
  }

  rgbaAddressEffectsUtil.bouncedirection = 0;
  rgbaAddressEffectsUtil.one_color_all(0, 0, 0);
}

void RgbaAddressControl::tick() {
  if (millis() - lastTimeUpdateLed >= rgbaAddressEffectsUtil.thisdelay) {
    switch (ledConfigData.mode) {
      case 1: break;                                                     // пазуа
      case 2: rgbaAddressEffectsUtil.rainbow_fade(); break;              // плавная смена цветов всей ленты OK
      case 3: rgbaAddressEffectsUtil.rainbow_loop(); break;              // крутящаяся радуга               OK
      case 4: rgbaAddressEffectsUtil.random_burst(); break;              // случайная смена цветов          OK
      case 5: rgbaAddressEffectsUtil.color_bounce(); break;              // бегающий светодиод              OK
      case 6: rgbaAddressEffectsUtil.color_bounceFADE(); break;          // бегающий паровозик светодиодов  OK
      case 7: rgbaAddressEffectsUtil.ems_lightsONE(); break;             // вращаются красный и синий       OK
      case 8: rgbaAddressEffectsUtil.ems_lightsALL(); break;             // вращается половина красных и половина синих  OK
      case 9: rgbaAddressEffectsUtil.flicker(); break;                   // случайный стробоскоп             OK
      case 10: rgbaAddressEffectsUtil.pulse_one_color_all(); break;      // пульсация одним цветом           OK
      case 11: rgbaAddressEffectsUtil.pulse_one_color_all_rev(); break;  // пульсация со сменой цветов       OK
      case 12: rgbaAddressEffectsUtil.fade_vertical(); break;            // плавная смена яркости по вертикали (для кольца) OK, НО НУЖЕН ЛИ ДЛЯ ЛИНЕЙНОЙ ЛЕНТЫ ?
      case 13: rgbaAddressEffectsUtil.rule30(); break;                   // безумие красных светодиодов      OK
      case 14: rgbaAddressEffectsUtil.random_march(); break;             // безумие случайных цветов         OK
      case 15: rgbaAddressEffectsUtil.rwb_march(); break;                // белый синий красный бегут по кругу OK ?
      case 16: rgbaAddressEffectsUtil.white_temps(); break;              // бело синий градиент              OK
      case 17: rgbaAddressEffectsUtil.pop_horizontal(); break;           // красные вспышки спускаются вниз  OK
      case 18: rgbaAddressEffectsUtil.quad_bright_curve(); break;        // полумесяц                        OK
      case 19: rgbaAddressEffectsUtil.flame(); break;                    // эффект пламени                   OK
      case 20: rgbaAddressEffectsUtil.rainbow_vertical(); break;         // радуга в вертикаьной плоскости (кольцо)  OK
      case 21: rgbaAddressEffectsUtil.random_color_pop(); break;         // безумие случайных вспышек        OK
      case 22: rgbaAddressEffectsUtil.ems_lightsSTROBE(); break;         // полицейская мигалка              OK
      case 23: rgbaAddressEffectsUtil.rgb_propeller(); break;            // RGB пропеллер                    OK
      case 24: rgbaAddressEffectsUtil.kitt(); break;                     // случайные вспышки красного в вертикаьной плоскости OK
      case 25: rgbaAddressEffectsUtil.matrix(); break;                   // зелёненькие бегают по кругу случайно OK ?
      case 26: rgbaAddressEffectsUtil.new_rainbow_loop(); break;         // крутая плавная вращающаяся радуга  OK
      case 27:
        rgbaAddressEffectsUtil.colorWipe(0x00, 0x00, 0x00);  // OK
        break;
      case 28: rgbaAddressEffectsUtil.Fire(55, 120); break;    // линейный огонь          OK
      case 29: rgbaAddressEffectsUtil.rainbowCycle(); break;   // очень плавная вращающаяся радуга OK
      case 30: rgbaAddressEffectsUtil.TwinkleRandom(); break;  // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод) OK
      case 31:
        rgbaAddressEffectsUtil.RunningLights();
        break;  // бегущие огни        OK ?
      case 32:
        rgbaAddressEffectsUtil.Strobe();
        break;  // стробоскоп OK
      case 33:
        rgbaAddressEffectsUtil.one_color_allHSV();
        LEDS.show();
        break;
      case 34: rgbaAddressEffectsUtil.theaterChase(); break;         // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3) OK, НО НЕ РАБОТАЕТ АДЕКВАТНО
      case 35: rgbaAddressEffectsUtil.theaterChaseRainbow(); break;  // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3) НЕ РАБОТАЕТ АДЕКВАТНО
    }
    lastTimeUpdateLed = millis();
  } else {
    LEDS.show();
  }
}