#include "RgbaAddressControl.h"
#include "RgbaAddressEffectsUtil.h"

LedConfigData RgbaAddressControl::getLedAddressConfig() {
  return ledConfigData;
}

void RgbaAddressControl::updateLedAddressConfig(LedConfigData newConfigData) {
  ledConfigData = newConfigData;
  rgbaAddressEffectsUtil.updateConfig(ledConfigData);
  updatePowerState();
  applyLedInternalConfig();
}

void RgbaAddressControl::updatePowerState() {
  if (ledConfigData.powerOn) {
    LEDS.setBrightness(ledConfigData.v);  // ограничить максимальную яркость
  } else {
    LEDS.setBrightness(0);
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
    case 18:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;
    case 20:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;  //---POP LEFT/RIGHT
    case 21:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;  //---QUADRATIC BRIGHTNESS CURVE
    case 22:
      rgbaAddressEffectsUtil.thisdelay = 0;
      break;
    case 23:
      rgbaAddressEffectsUtil.thisdelay = 50;
      rgbaAddressEffectsUtil.thisstep = 15;
      break;                                                //---VERITCAL RAINBOW
    case 25: rgbaAddressEffectsUtil.thisdelay = 35; break;  //---RANDOM COLOR POP
    case 26:
      rgbaAddressEffectsUtil.thisdelay = 25;
      break;  //---EMERGECNY STROBE
    case 27:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;  //---RGB PROPELLER
    case 28:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;  //---KITT
    case 29:
      rgbaAddressEffectsUtil.thisdelay = 100;
      break;                                                //---MATRIX RAIN
    case 30: rgbaAddressEffectsUtil.thisdelay = 15; break;  //---NEW RAINBOW LOOP
    case 33: rgbaAddressEffectsUtil.thisdelay = 50; break;  // colorWipe
    case 35: rgbaAddressEffectsUtil.thisdelay = 15; break;  // Fire
    case 37: rgbaAddressEffectsUtil.thisdelay = 20; break;  // rainbowCycle
    case 38: rgbaAddressEffectsUtil.thisdelay = 10; break;  // rainbowTwinkle
    case 39:
      rgbaAddressEffectsUtil.thisdelay = 50;
      break;  // RunningLights
    //case 42: thisdelay = 50; break;  // theaterChase
    //case 43: thisdelay = 50; break;  // theaterChaseRainbow
    case 44: rgbaAddressEffectsUtil.thisdelay = 0; break;  // Strobe
    case 45:
      rgbaAddressEffectsUtil.one_color_allHSV();
      LEDS.show();
      break;
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
      case 18: rgbaAddressEffectsUtil.white_temps(); break;              // бело синий градиент              OK
      case 20: rgbaAddressEffectsUtil.pop_horizontal(); break;           // красные вспышки спускаются вниз  OK
      case 21: rgbaAddressEffectsUtil.quad_bright_curve(); break;        // полумесяц                        OK
      case 22: rgbaAddressEffectsUtil.flame(); break;                    // эффект пламени                   OK
      case 23: rgbaAddressEffectsUtil.rainbow_vertical(); break;         // радуга в вертикаьной плоскости (кольцо)  OK
      case 25: rgbaAddressEffectsUtil.random_color_pop(); break;         // безумие случайных вспышек        OK
      case 26: rgbaAddressEffectsUtil.ems_lightsSTROBE(); break;         // полицейская мигалка              OK
      case 27: rgbaAddressEffectsUtil.rgb_propeller(); break;            // RGB пропеллер                    OK
      case 28: rgbaAddressEffectsUtil.kitt(); break;                     // случайные вспышки красного в вертикаьной плоскости OK
      case 29: rgbaAddressEffectsUtil.matrix(); break;                   // зелёненькие бегают по кругу случайно OK ?
      case 30: rgbaAddressEffectsUtil.new_rainbow_loop(); break;         // крутая плавная вращающаяся радуга  OK
      case 33:
        rgbaAddressEffectsUtil.colorWipe(0x00, 0xff, 0x00, 0x00, 0x00, 0x00);  // OK
        break;
      case 35: rgbaAddressEffectsUtil.Fire(55, 120); break;    // линейный огонь          OK
      case 37: rgbaAddressEffectsUtil.rainbowCycle(); break;   // очень плавная вращающаяся радуга OK
      case 38: rgbaAddressEffectsUtil.TwinkleRandom(); break;  // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод) OK
      case 39:
        rgbaAddressEffectsUtil.RunningLights(0xff, 0xff, 0x00);
        break;  // бегущие огни        OK ?
      //case 42: theaterChase(0xff, 0, 0); break;         // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3) OK, НО НЕ РАБОТАЕТ АДЕКВАТНО
      //case 43: theaterChaseRainbow(thisdelay); break;   // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3) НЕ РАБОТАЕТ АДЕКВАТНО
      case 44:
        rgbaAddressEffectsUtil.Strobe(0xff, 0xff, 0xff);
        break;  // стробоскоп OK
      case 45:
        rgbaAddressEffectsUtil.one_color_allHSV();
        LEDS.show();
        break;
    }
    lastTimeUpdateLed = millis() + 12;
  }
}