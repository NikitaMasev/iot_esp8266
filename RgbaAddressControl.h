#define FASTLED_INTERRUPT_RETRY_COUNT 0  // fix flickering first led
//#define FASTLED_ALLOW_INTERRUPTS 0
//#define INTERRUPT_THRESHOLD 1
//#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>
#include "RgbaAddressEffectsUtil.h"

void applyLedInternalConfig() {
  switch (ledConfigData.mode) {
    case 2: thisdelay = 60; break;  //---STRIP RAINBOW FADE
    case 3:
      thisdelay = 20;
      thisstep = 10;
      break;                        //---RAINBOW LOOP
    case 4: thisdelay = 20; break;  //---RANDOM BURST
    case 5:
      thisdelay = 20;
      //ledConfigData.h = 0;
      break;  //---CYLON v1
    case 6:
      thisdelay = 80;
      //ledConfigData.h = 30;
      break;  //---CYLON v2
    case 7:
      thisdelay = 40;
      ledConfigData.h = 0;
      break;  //---POLICE LIGHTS SINGLE
    case 8:
      thisdelay = 40;
      ledConfigData.h = 0;
      break;  //---POLICE LIGHTS SOLID
    case 9:
      ledConfigData.h = 160;
      ledConfigData.s = 50;
      thisdelay = 35;
      break;  //---STRIP FLICKER
    case 10:
      thisdelay = 15;
      //ledConfigData.h = 0;
      break;  //---PULSE COLOR BRIGHTNESS
    case 11:
      thisdelay = 30;
      ledConfigData.h = 0;
      break;  //---PULSE COLOR SATURATION
    case 12:
      thisdelay = 60;
      ledConfigData.h = 180;
      break;                          //---VERTICAL SOMETHING
    case 13: thisdelay = 100; break;  //---CELL AUTO - RULE 30 (RED)
    case 14: thisdelay = 80; break;   //---MARCH RANDOM COLORS
    case 15: thisdelay = 80; break;   //---MARCH RWB COLORS
    case 16:
      thisdelay = 60;
      ledConfigData.h = 95;
      break;  //---RADIATION SYMBOL
    case 18:
      thisdelay = 100;
      break;
    case 20:
      thisdelay = 100;
      ledConfigData.h = 0;
      break;  //---POP LEFT/RIGHT
    case 21:
      thisdelay = 100;
      ledConfigData.h = 180;
      break;  //---QUADRATIC BRIGHTNESS CURVE
    case 22:
      thisdelay = 0;
      break;
    case 23:
      thisdelay = 50;
      thisstep = 15;
      break;                         //---VERITCAL RAINBOW
    case 25: thisdelay = 35; break;  //---RANDOM COLOR POP
    case 26:
      thisdelay = 25;
      break;  //---EMERGECNY STROBE
    case 27:
      thisdelay = 100;
      ledConfigData.h = 0;
      break;  //---RGB PROPELLER
    case 28:
      thisdelay = 100;
      ledConfigData.h = 0;
      break;  //---KITT
    case 29:
      thisdelay = 10;
      ledConfigData.h = 95;
      break;                         //---MATRIX RAIN
    case 30: thisdelay = 15; break;  //---NEW RAINBOW LOOP
    case 33: thisdelay = 50; break;  // colorWipe
    case 35: thisdelay = 15; break;  // Fire
    case 37: thisdelay = 20; break;  // rainbowCycle
    case 38: thisdelay = 10; break;  // rainbowTwinkle
    case 39: thisdelay = 50; break;  // RunningLights
    case 42: thisdelay = 50; break;  // theaterChase
    case 43: thisdelay = 50; break;  // theaterChaseRainbow
    case 44: thisdelay = 0; break;   // Strobe
    case 45:
      one_color_allHSV();
      LEDS.show();
      break;
  }
  bouncedirection = 0;
  one_color_all(0, 0, 0);
}

void updateLedAddressConfig(LedConfigData newConfigData) {
  ledConfigData = newConfigData;
  saveLedConfigData(newConfigData);
  applyLedInternalConfig();
}

void setupLedAddressControl() {
  LedConfigData savedLedConfigData = getSavedLedConfigData();
  if (savedLedConfigData.h != -1) {
    ledConfigData = savedLedConfigData;
  }

  LEDS.setBrightness(ledConfigData.v);  // ограничить максимальную яркость

  LEDS.addLeds<WS2811, LED_DT, BRG>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0);                              // погасить все светодиоды
  LEDS.show();                                         // отослать команду

  randomSeed(analogRead(0));
  applyLedInternalConfig();
}

void updateLedAddressPower(bool controlOn) {
  LEDS.setBrightness(controlOn ? ledConfigData.v : 0);
  LEDS.show();
}

volatile long lastTimeLoopLedAddress = 0;

void loopLedAddress() {
  //if (millis() - lastTimeLoopLedAddress > thisdelay) {
    switch (ledConfigData.mode) {
      case 1: break;                              // пазуа
      case 2: rainbow_fade(); break;              // плавная смена цветов всей ленты OK
      case 3: rainbow_loop(); break;              // крутящаяся радуга               OK
      case 4: random_burst(); break;              // случайная смена цветов          OK
      case 5: color_bounce(); break;              // бегающий светодиод              OK
      case 6: color_bounceFADE(); break;          // бегающий паровозик светодиодов  OK
      case 7: ems_lightsONE(); break;             // вращаются красный и синий       OK
      case 8: ems_lightsALL(); break;             // вращается половина красных и половина синих  OK
      case 9: flicker(); break;                   // случайный стробоскоп             OK
      case 10: pulse_one_color_all(); break;      // пульсация одним цветом           OK
      case 11: pulse_one_color_all_rev(); break;  // пульсация со сменой цветов       OK
      case 12: fade_vertical(); break;            // плавная смена яркости по вертикали (для кольца) OK, НО НУЖЕН ЛИ ДЛЯ ЛИНЕЙНОЙ ЛЕНТЫ ???
      case 13: rule30(); break;                   // безумие красных светодиодов      OK
      case 14: random_march(); break;             // безумие случайных цветов         OK
      case 15: rwb_march(); break;                // белый синий красный бегут по кругу OK(?)
      case 18: white_temps(); break;              // бело синий градиент              OK
      case 20: pop_horizontal(); break;           // красные вспышки спускаются вниз  OK
      case 21: quad_bright_curve(); break;        // полумесяц                        OK
      case 22: flame(); break;                    // эффект пламени                   OK
      case 23: rainbow_vertical(); break;         // радуга в вертикаьной плоскости (кольцо)  OK
      case 25: random_color_pop(); break;         // безумие случайных вспышек        OK
      case 26: ems_lightsSTROBE(); break;         // полицейская мигалка              OK
      case 27: rgb_propeller(); break;            // RGB пропеллер                    OK
      case 28: kitt(); break;                     // случайные вспышки красного в вертикаьной плоскости OK
      case 29: matrix(); break;                   // зелёненькие бегают по кругу случайно OK
      case 30: new_rainbow_loop(); break;         // крутая плавная вращающаяся радуга  OK
      case 33:
        colorWipe(0x00, 0xff, 0x00, 0x00, 0x00, 0x00);  // OK
        break;
      case 35: Fire(55, 120); break;                    // линейный огонь          OK
      case 37: rainbowCycle(); break;                   // очень плавная вращающаяся радуга OK
      case 38: TwinkleRandom(); break;                  // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод) OK
      case 39: RunningLights(0xff, 0xff, 0x00); break;  // бегущие огни        OK
      case 42: theaterChase(0xff, 0, 0); break;         // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3) OK, НО НЕ РАБОТАЕТ АДЕКВАТНО
      case 43: theaterChaseRainbow(thisdelay); break;   // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3) НЕ РАБОТАЕТ АДЕКВАТНО
      case 44: Strobe(0xff, 0xff, 0xff); break;         // стробоскоп OK
    }
    //lastTimeLoopLedAddress = millis() + 12;
  //}
}