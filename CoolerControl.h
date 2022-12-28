#include "TempDetector.h"

#define PIN_PWM_COOLER 9

#define TIME_UPDATE_COOLER 5500
#define TEMP_HIGH_UPS 58.0f    //C
#define TEMP_HIGH_ACC 35.0f    //C
#define TEMP_HYSTERESIS_ACC 5  //C
#define LOW_PWM_COOLER 65
#define HIGH_PWM_COOLER 255

long lastTimesUpdateCooler;

int pwmCooler;

void setupCoolerControl() {
  pinMode(PIN_PWM_COOLER, OUTPUT);
}

void controlCooler(float tempAcc) {
  if (millis() - lastTimesUpdateCooler > TIME_UPDATE_COOLER) {
    lastTimesUpdateCooler = millis();

    if (tempAcc >= (TEMP_HIGH_ACC + TEMP_HYSTERESIS_ACC)) {
      pwmCooler = HIGH_PWM_COOLER * 0.75;
    } else if (tempAcc >= TEMP_HIGH_ACC) {
      pwmCooler = HIGH_PWM_COOLER * 0.5;
    } else if (tempAcc >= (TEMP_HIGH_ACC - TEMP_HYSTERESIS_ACC)) {
      pwmCooler = HIGH_PWM_COOLER * 0.3;
    } else {
      pwmCooler = 0;
    }
  }

  if (pwmCooler == LOW_PWM_COOLER) {
    pwmCooler = 0;
  }
  analogWrite(PIN_PWM_COOLER, pwmCooler);
}

void loopCooler() {
  controlCooler(temps[TEMP_SENSOR_COUNT - 1]);
}