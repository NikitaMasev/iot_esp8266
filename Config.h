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
const constexpr char *password = "*****";
const constexpr char *iotServer = "ws://192.168.50.213:5080";

const constexpr uint8_t cipher_key[] = {};
const constexpr uint8_t cipher_iv[] = {};
