#include "Persistent.h"

#define LED_COUNT 100  // число светодиодов в кольце/ленте
#define LED_DT 14      // пин, куда подключен DIN ленты

#define BOTTOM_INDEX 0  // светодиод начала отсчёта
#define TOP_INDEX (int(LED_COUNT / 2))
#define EVENODD (LED_COUNT % 2)

LedConfigData ledConfigData = {
  h: 100,
  s: 255,
  v: 180,
  mode: 10,
};

struct CRGB leds[LED_COUNT];
int ledsX[LED_COUNT][3];  //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

int thisdelay = 20;  //-FX LOOPS DELAY VAR
int thisstep = 10;   //-FX LOOPS DELAY VAR