#pragma once

#include "DataStruct.h"
#include "LedAddrConfig.h"

class RgbaAddressEffectsUtil {
private:
  int idex = 0;        //-LED INDEX (0 to LED_COUNT-1
  int ihue = 0;        //-HUE (0-255)
  int ibright = 0;     //-BRIGHTNESS (0-255)
  int isat = 0;        //-SATURATION (0-255)
  float tcount = 0.0;  //-INC VAR FOR SIN LOOPS
  int lcount = 0;      //-ANOTHER COUNTING VAR
  struct CRGB *leds;
  int ledsX[LED_COUNT][3];  //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

  const float hmin = 0.1;
  const float hmax = 45.0;
  const float hdif = hmax - hmin;
  int indexFlame = 0;
  int idelay = 0;
  int randtemp = 0;
  float hinc = 0;
  int ihueFlame = 0;

  const int emsXCount = 5;
  int indexEmsX = 0;
  bool emsModeFirstHue = true;
  bool emsModeDelayBeforeOff = false;

  bool colorWipeFirst = true;
  int indexColorWipe = 0;

  const int rainbowCycles = 256 * 5;
  int indexRainbowCycle = 0;

  const int twinkleRandomCount = 20;
  int indexTwinkleRandom = 0;
  bool twinkleRandomDelay = false;

  const int runningLightsCount = LED_COUNT * 2;
  int indexRunningLights = 0;

  const int theaterChaseRainbowCycles = 255;
  const int theaterChaseCycles = 10;
  const int theaterChaseQ = 3;
  int indexCycleTheaterChase = 0;
  int indexQTheaterChase = 0;
  bool theaterChaseTurnMode = true;

  const int delayPause = 1000;
  const int delayFlash = 100;
  const int strobeCount = 10;

  int strobeCounter = 0;
  bool previousOn = false;
  int strobeAnim = delayFlash;

  LedConfigData ledConfigData = {
    h: 100,
    s: 255,
    v: 180,
    mode: 10,
    powerOn: true,
  };

  void set_color_led(int adex, int cred, int cgrn, int cblu);
  int horizontal_index(int i);
  int antipodal_index(int i);
  int adjacent_cw(int i);
  int adjacent_ccw(int i);
  void copy_led_array();
  void setPixel(int Pixel, byte red, byte green, byte blue);
  void setAll(byte red, byte green, byte blue);
public:
  RgbaAddressEffectsUtil(CRGB *leds) {
    this->leds = leds;
  };

  int thisdelay = 20;       //-FX LOOPS DELAY VAR
  int thisstep = 10;        //-FX LOOPS DELAY VAR
  int bouncedirection = 0;  //-SWITCH FOR COLOR BOUNCE (0-1)
  
  void updateConfig(LedConfigData newConfigData);

  void one_color_all(int cred, int cgrn, int cblu);
  void one_color_allHSV();
  void rainbow_fade();
  void rainbow_loop();
  void random_burst();
  void color_bounce();
  void color_bounceFADE();
  void ems_lightsONE();
  void ems_lightsALL();
  void flicker();
  void pulse_one_color_all();
  void pulse_one_color_all_rev();
  void fade_vertical();
  void random_red();
  void rule30();
  void random_march();
  void rwb_march();
  void radiation();
  void color_loop_vardelay();
  void white_temps();
  void pop_horizontal();
  void quad_bright_curve();
  void flame();
  void rainbow_vertical();
  void random_color_pop();
  void ems_lightsSTROBE();
  void rgb_propeller();
  void kitt();
  void matrix();
  void strip_march_cw();
  void strip_march_ccw();
  void new_rainbow_loop();
  void colorWipe(byte redWipe, byte greenWipe, byte blueWipe);
  void setPixelHeatColor(int Pixel, byte temperature);
  void Fire(int Cooling, int Sparking);
  byte *Wheel(byte WheelPos);
  void rainbowCycle();
  void TwinkleRandom();
  void RunningLights();
  void theaterChase();
  void theaterChaseRainbow();
  void Strobe();
};