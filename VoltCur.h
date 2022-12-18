#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

int currentDC;
float voltageDC;

void updateVoltageAndCurrent() {
  float shuntvoltage = ina219.getShuntVoltage_mV();
  float busvoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float loadvoltage = busvoltage + (shuntvoltage / 1000);

  currentDC = (int)current_mA;
  voltageDC = loadvoltage;
}

void setupVoltageCurrentSensor() {
    if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
  }
}