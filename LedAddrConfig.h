#pragma once

#define FASTLED_INTERRUPT_RETRY_COUNT 0  // fix flickering first led
//#define FASTLED_ALLOW_INTERRUPTS 0
//#define INTERRUPT_THRESHOLD 1
//#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>

#define LED_DT 14      // пин, куда подключен DIN ленты
#define LED_COUNT 100  // число светодиодов в кольце/ленте