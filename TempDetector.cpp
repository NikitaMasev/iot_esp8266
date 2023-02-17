#include "TempDetector.h"

#define TEMP_NOT_UPDATED -8000L
#define TIME_UPDATE_TEMP 750

TempDetector::detectTemperature(OneWire *wireTemp, long *lastTimeUpdateTemp, bool *cmdWireTemp) {
  float temp = TEMP_NOT_UPDATED;
  byte data[2];

  if (*cmdWireTemp) {
    *cmdWireTemp = false;

    (*wireTemp).reset();
    (*wireTemp).write(0xCC);
    (*wireTemp).write(0x44);

    *lastTimeUpdateTemp = millis();
  }

  if (millis() - *lastTimeUpdateTemp > TIME_UPDATE_TEMP) {
    (*wireTemp).reset();
    (*wireTemp).write(0xCC);
    (*wireTemp).write(0xBE);
    data[0] = (*wireTemp).read();
    data[1] = (*wireTemp).read();

    temp = ((data[1] << 8) | data[0]) * 0.06;  //default 0.0625

    *cmdWireTemp = true;
  }
  return temp;  
}

TempDetector::tick() {
  for (int i = 0; i < TEMP_SENSOR_COUNT; i++) {
    float temp = detectTemperature(&wireTemps[i], &lastTimesUpdateTemps[i], &cmdWireTemps[i]);
    if (temp != TEMP_NOT_UPDATED) {
      temps[i] = temp;
    }
  }
}