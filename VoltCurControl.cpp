#include "VoltCurControl.h"
#include "Config.h"

VoltCurController::VoltCurController() {
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
  }
}

void VoltCurController::updateVoltageAndCurrent() {
  float current_mA = 0.0;
  float loadvoltage = 0.0;

  for (int i = 0; i < SAMPLES_VOLT_CUR; i++) {
    float shuntvoltage = ina219.getShuntVoltage_mV();
    float busvoltage = ina219.getBusVoltage_V();
    current_mA += ina219.getCurrent_mA();
    loadvoltage += busvoltage + (shuntvoltage / 1000);
  }
  currentDC = current_mA / SAMPLES_VOLT_CUR;
  voltageDC = loadvoltage / SAMPLES_VOLT_CUR + VOLTAGE_DROP_CALIBRATE;
}

void VoltCurController::tick() {
  updateVoltageAndCurrent();
}