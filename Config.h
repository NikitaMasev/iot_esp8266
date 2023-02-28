#pragma once

#include <stdint.h>

#define TYPE_DEVICE_UPS
//#define TYPE_DEVICE_LAMP
//#define TYPE_DEVICE_RGBA
//#define TYPE_DEVICE_RGBA_ADDRESS
//#define TYPE_DEVICE_TEMP_SENSOR

#define PKG_CMD_SYMB "^"
#define PKG_CMD_DELIMITER_SYMB ":"
#define START_PKG_DATA_SYMB "#"
#define DELIMITER_IOT_DATA_SYMB "/"
#define END_PKG_DATA_SYMB ";"

#define SERIAL_COMMUNICATION_SPEED 9600

const constexpr char *ssid = "CrynetSystem";
const constexpr char *password = "****";
const constexpr char *iotServer = "ws://192.168.50.213:5080";

const constexpr uint8_t cipher_key[] = { };
const constexpr uint8_t cipher_iv[] = {  };

///UPS START
////For Cooler
#define PIN_PWM_COOLER 14
#define TEMP_HIGH_UPS 58.0f    //C
#define TEMP_HIGH_ACC 35.0f    //C
#define TEMP_HYSTERESIS_ACC 5  //C
#define LOW_PWM_COOLER 65
#define HIGH_PWM_COOLER 255
///For VoltageCurrent Sensor
#define SAMPLES_VOLT_CUR 10
///For Temp Sensor
#define PIM_TEMP_DC 2
#define PIM_TEMP_ACC 13
#define TEMP_SENSOR_COUNT 2
#define TEMP_NOT_UPDATED -8000L
#define TIME_UPDATE_TEMP 750
///UPS END
///LAMP START
#define PIN_POWER_CONTROL 14
///LAMP END
///LED RGB START
#define PIN_R 9
#define PIN_G 10
#define PIN_B 11
///LED RGB END
///LED RGB ADDRESS START
#define LED_DT 14      // пин, куда подключен DIN ленты
#define LED_COUNT 100  // число светодиодов в кольце/ленте
///LED RGB ADDRESS END