#pragma once

#define FASTLED_INTERRUPT_RETRY_COUNT 0  // fix flickering first led
//#define FASTLED_ALLOW_INTERRUPTS 0
//#define INTERRUPT_THRESHOLD 1
//#define FASTLED_ESP8266_RAW_PIN_ORDER

#define START_EFFECT_LED_ADDR 1
#define END_EFFECT_LED_ADDR 33

#include <FastLED.h>
#include "Config.h"