#include "CoolerControl.h"
#include "Arduino.h"

#define PIN_PWM_COOLER 14

#define TEMP_HIGH_UPS 58.0f    //C
#define TEMP_HIGH_ACC 35.0f    //C
#define TEMP_HYSTERESIS_ACC 5  //C
#define LOW_PWM_COOLER 65
#define HIGH_PWM_COOLER 255

CoolerControl::CoolerControl() {
  pinMode(PIN_PWM_COOLER, OUTPUT);
}

void CoolerControl::controlCooler(float tempAcc) {
  if (tempAcc >= (TEMP_HIGH_ACC + TEMP_HYSTERESIS_ACC)) {
    pwmCooler = HIGH_PWM_COOLER * 0.75;
  } else if (tempAcc >= TEMP_HIGH_ACC) {
    pwmCooler = HIGH_PWM_COOLER * 0.5;
  } else if (tempAcc >= (TEMP_HIGH_ACC - TEMP_HYSTERESIS_ACC)) {
    pwmCooler = HIGH_PWM_COOLER * 0.3;
  } else {
    pwmCooler = 0;
  }

  if (pwmCooler == LOW_PWM_COOLER) {
    pwmCooler = 0;
  }
  analogWrite(PIN_PWM_COOLER, pwmCooler);
}

void CoolerControl::tick(float tempControl) {
  controlCooler(tempControl);
}