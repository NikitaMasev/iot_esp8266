#pragma once

#include <stdint.h>

//#define TYPE_DEVICE_UPS
//#define TYPE_DEVICE_LAMP
//#define TYPE_DEVICE_RGBA ///TODO NEED FIX
//#define TYPE_DEVICE_RGBA_ADDRESS
#define TYPE_DEVICE_LED_CCT
//#define TYPE_DEVICE_TEMP_SENSOR

//#define CONTROL_LED_PAJ7620_SENSOR ///

#define PKG_CMD_SYMB "^"
#define PKG_CMD_DELIMITER_SYMB ":"
#define START_PKG_DATA_SYMB "#"
#define DELIMITER_IOT_DATA_SYMB "/"
#define END_PKG_DATA_SYMB ";"

#define SERIAL_COMMUNICATION_SPEED 9600

const constexpr char *ssid = "";
const constexpr char *password = "";

const constexpr char *iotServer = "ws://192.168.50.143:5080";



const constexpr uint8_t cipher_key[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 53, 54, 49, 48, 49, 49};
const constexpr uint8_t cipher_iv[] = {48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48};

///UPS START
//IO5/D1 - SCL, IO4/D2 - SDA
////For Cooler
#define PIN_PWM_COOLER 14
#define TEMP_HIGH_UPS 58.0f    //C
#define TEMP_HIGH_ACC 35.0f    //C
#define TEMP_HYSTERESIS_ACC 5  //C
#define LOW_PWM_COOLER 65
#define HIGH_PWM_COOLER 255
///For VoltageCurrent Sensor
#define SAMPLES_VOLT_CUR 10
#define VOLTAGE_DROP_CALIBRATE 0.215f
///For Temp Sensor
#define PIM_TEMP_DC 2 //D4
#define PIM_TEMP_ACC 13 //D7
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
///14/D5
#define LED_DT 14 //14      // пин, куда подключен DIN ленты
#define LED_COUNT 140  // число светодиодов в кольце/ленте
///LED RGB ADDRESS END
///LED CCT START
#define PIN_COLD D5
#define PIN_NULL D2
#define PIN_WARM D1
///LED CCT END