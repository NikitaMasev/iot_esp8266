#include <FastLED.h>
#include "RgbaAddressEffectsUtil.h"

void updateLedAddressConfig(LedConfigData newConfigData) {
  ledConfigData = newConfigData;
  saveLedConfigData(newConfigData);
  //ledConfigData.s = 255;
  switch (ledConfigData.mode) {
    case 2: thisdelay = 60; break;  //---STRIP RAINBOW FADE
    case 3:
      thisdelay = 20;
      thisstep = 10;
      break;                        //---RAINBOW LOOP
    case 4: thisdelay = 20; break;  //---RANDOM BURST
    case 5:
      thisdelay = 20;
      ledConfigData.h = 0;
      break;  //---CYLON v1
    case 6:
      thisdelay = 80;
      ledConfigData.h = 30;
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
    case 19:
      thisdelay = 35;
      ledConfigData.h = 180;
      break;  //---SIN WAVE BRIGHTNESS
    case 20:
      thisdelay = 100;
      ledConfigData.h = 0;
      break;  //---POP LEFT/RIGHT
    case 21:
      thisdelay = 100;
      ledConfigData.h = 180;
      break;  //---QUADRATIC BRIGHTNESS CURVE
    case 23:
      thisdelay = 50;
      thisstep = 15;
      break;                         //---VERITCAL RAINBOW
    case 25: thisdelay = 35; break;  //---RANDOM COLOR POP
    case 26:
      thisdelay = 25;
      ledConfigData.h = 0;
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
      thisdelay = 100;
      ledConfigData.h = 95;
      break;                          //---MATRIX RAIN
    case 30: thisdelay = 15; break;   //---NEW RAINBOW LOOP
    case 33: thisdelay = 50; break;   // colorWipe
    case 35: thisdelay = 15; break;   // Fire
    case 37: thisdelay = 20; break;   // rainbowCycle
    case 38: thisdelay = 10; break;   // rainbowTwinkle
    case 39: thisdelay = 50; break;   // RunningLights
    case 42: thisdelay = 50; break;   // theaterChase
    case 43: thisdelay = 50; break;   // theaterChaseRainbow
    case 44: thisdelay = 100; break;  // Strobe
    case 45:
      one_color_allHSV();
      LEDS.show();
      break;
  }
  bouncedirection = 0;
  one_color_all(0, 0, 0);
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
  updateLedAddressConfig(ledConfigData);
}

void updateLedAddressPower(bool controlOn) {
  LEDS.setBrightness(controlOn ? ledConfigData.v : 0);
  LEDS.show();
}

void loopLedAddress() {
  switch (ledConfigData.mode) {
    case 1: break;                              // пазуа
    case 2: rainbow_fade(); break;              // плавная смена цветов всей ленты OK
    case 3: rainbow_loop(); break;              // крутящаяся радуга               OK
    case 4: random_burst(); break;              // случайная смена цветов          OK
    case 5: color_bounce(); break;              // бегающий светодиод              OK
    case 6: color_bounceFADE(); break;          // бегающий паровозик светодиодов  OK
    case 7: ems_lightsONE(); break;             // вращаются красный и синий
    case 8: ems_lightsALL(); break;             // вращается половина красных и половина синих
    case 9: flicker(); break;                   // случайный стробоскоп
    case 10: pulse_one_color_all(); break;      // пульсация одним цветом
    case 11: pulse_one_color_all_rev(); break;  // пульсация со сменой цветов
    case 12: fade_vertical(); break;            // плавная смена яркости по вертикали (для кольца)
    case 13: rule30(); break;                   // безумие красных светодиодов
    case 14: random_march(); break;             // безумие случайных цветов
    case 15: rwb_march(); break;                // белый синий красный бегут по кругу (ПАТРИОТИЗМ!)
    case 18: white_temps(); break;              // бело синий градиент
    case 19: sin_bright_wave(); break;          // тоже хрень какая то
    case 20: pop_horizontal(); break;           // красные вспышки спускаются вниз
    case 21: quad_bright_curve(); break;        // полумесяц НУЖНО МОДИФИЦИРОВАТЬ
    case 22: flame(); break;                    // эффект пламени !!!!!
    case 23: rainbow_vertical(); break;         // радуга в вертикаьной плоскости (кольцо)
    case 25: random_color_pop(); break;         // безумие случайных вспышек
    case 26: ems_lightsSTROBE(); break;         // полицейская мигалка
    case 27: rgb_propeller(); break;            // RGB пропеллер
    case 28: kitt(); break;                     // случайные вспышки красного в вертикаьной плоскости
    case 29: matrix(); break;                   // зелёненькие бегают по кругу случайно
    case 30: new_rainbow_loop(); break;         // крутая плавная вращающаяся радуга
    case 33:
      colorWipe(0x00, 0xff, 0x00, thisdelay);
      colorWipe(0x00, 0x00, 0x00, thisdelay);
      break;                                                        // плавное заполнение цветом
    case 35: Fire(55, 120, thisdelay); break;                       // линейный огонь
    case 37: rainbowCycle(thisdelay); break;                        // очень плавная вращающаяся радуга
    case 38: TwinkleRandom(20, thisdelay, 1); break;                // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод) ???
    case 39: RunningLights(0xff, 0xff, 0x00, thisdelay); break;     // бегущие огни
    case 42: theaterChase(0xff, 0, 0, thisdelay); break;            // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
    case 43: theaterChaseRainbow(thisdelay); break;                 // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
    case 44: Strobe(0xff, 0xff, 0xff, 10, thisdelay, 1000); break;  // стробоскоп

    case 888: demo_modeA(); break;  // длинное демо
    case 889: demo_modeB(); break;  // короткое демо
  }
}