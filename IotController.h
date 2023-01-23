#include "WString.h"
#include <GyverOS.h>
#include "TypeDevice.h"
#include "Config.h"
#if defined(TYPE_DEVICE_LAMP)
#include "PowerControl.h"
#endif
#if defined(TYPE_DEVICE_UPS)
#include "Persistent.h"
#include "CoolerControl.h"
#include "VoltCur.h"
#endif
#if defined(TYPE_DEVICE_RGBA)
#include "RgbaControl.h"
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
#include "RgbaAddressControl.h"
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
#include "Persistent.h"
#include "TempDetector.h"
#endif

const char *empty = "";

#if defined(TYPE_DEVICE_UPS)
GyverOS<3> tasker;
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
GyverOS<2> tasker;
#endif
#if defined(TYPE_DEVICE_TEMP_SENSOR)
GyverOS<1> tasker;
#endif

#include <ESP8266WiFiMulti.h>
#include <ArduinoWebsockets.h>

#define TIME_RETRY_CONNECTION 10000
long lastTimeRetryConnection = 0;

using namespace websockets;
// #include <WebSocketsClient.h>

ESP8266WiFiMulti WiFiMulti;
WebsocketsClient client;
// WebSocketsClient webSocket;

const char *ssid = "CrynetSystem";
const char *password = "gish4264";
//const char *ipServer = "192.168.50.143";
const char *iotServer = "ws://192.168.50.143:5080";

uint8_t cipher_key[16] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 53, 54, 49, 48, 49, 49 };
uint8_t cipher_iv[16] = { 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48 };

bool iotServerConnected = false;

void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Got Message: ");
  Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    iotServerConnected = true;
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    iotServerConnected = false;
  } else if (event == WebsocketsEvent::GotPing) {
    client.pong();
    client.send("Hi Server!");
  } else if (event == WebsocketsEvent::GotPong) {
  }
}

void startWifi() {
  WiFiMulti.addAP(ssid, password);

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("Try connecting to WIFI");
    delay(1000);
  }

  // Setup Callbacks
  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);

  client.connect(iotServer);

  // WiFiMulti.addAP(ssid, password);

  // while (WiFiMulti.run() != WL_CONNECTED) {
  //   Serial.println("Try connecting to WIFI");
  //   delay(1000);
  // }
  // Serial.println("WIFI CONNECTED");
  //webSocket.begin(ipServer, port);
  //lastTimeUpdateWebsocket = millis();
}

void networkLoop() {
  if (iotServerConnected) {
    client.poll();
  } else if (millis() - lastTimeRetryConnection > TIME_RETRY_CONNECTION) {
    client.connect(iotServer);
    lastTimeRetryConnection = millis();    
  }
}

void setupIotController() {
  setupPersistent();
#if defined(TYPE_DEVICE_UPS)
  setupCoolerControl();
  setupVoltageCurrentSensor();
  setupTempDetector();

  tasker.attach(0, loopCooler, 5000);
  tasker.attach(1, loopTempDetector, 750);
  tasker.attach(2, loopVoltCur, 200);

  currentTypeDevice = ups;
#elif defined(TYPE_DEVICE_LAMP)
  setupPowerControl();
  currentTypeDevice = lamp;
#elif defined(TYPE_DEVICE_RGBA)
  setupLedControl();
  currentTypeDevice = rgba;
#elif defined(TYPE_DEVICE_RGBA_ADDRESS)
  setupLedAddressControl();
  tasker.attach(0, loopLedAddress, 80);
  tasker.attach(1, networkLoop, 100);  //250 OK
  currentTypeDevice = rgbaAddress;
#elif defined(TYPE_DEVICE_TEMP_SENSOR)
  setupTempDetector();
  tasker.attach(0, loopTempDetector, 750);
  currentTypeDevice = tempSensor;
#endif
}

String controlConnected() {
  if (registered) {
    return constructAuth(idDevice, typeDeviceToString(currentTypeDevice));
  } else {
    return constructRegister(typeDeviceToString(currentTypeDevice));
  }
}

String handleRegister(String payload) {
  int newId = payload.toInt();
  saveIdDevice(newId);
  return empty;
}

String handlePower(bool controlOn) {
#if defined(TYPE_DEVICE_LAMP)
  updatePower(controlOn);
#endif
#if defined(TYPE_DEVICE_RGBA)
  updateLedPower(controlOn);
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
  updateLedAddressPower(controlOn);
#endif
  return empty;
}

String handleRgba(String payload) {
  LedConfigData parsedLedConfig = parseLedConfig(payload);

#if defined(TYPE_DEVICE_RGBA)
  updateLedConfig(parsedLedConfig);
#endif
#if defined(TYPE_DEVICE_RGBA_ADDRESS)
  updateLedAddressConfig(parsedLedConfig);
#endif
  return empty;
}

String controlIncomingText(String data) {
  ParsedHeaderPayload headerPayload = parseTextData(data);

  Serial.println("headerPayload.header");
  Serial.println(headerPayload.header);
  Serial.println("headerPayload.payload");
  Serial.println(headerPayload.payload);

  if (headerPayload.header.isEmpty()) {
    return empty;
  }

  TypeControl typeControl = stringToTypeControl(headerPayload.header.c_str());

  if (typeControl == unknown_c || !allowedTypeControl(typeControl)) {
    return empty;
  }

  switch (typeControl) {
    case register_c:
      return handleRegister(headerPayload.payload);
    case powerOff_c:
      return handlePower(false);
    case powerOn_c:
      return handlePower(true);
    case rgba_c:
    case rgbaEffects_c:
      return handleRgba(headerPayload.payload);
  }

  return empty;
}

void loopController() {
#if defined(TYPE_DEVICE_UPS) || defined(TYPE_DEVICE_RGBA_ADDRESS) || defined(TYPE_DEVICE_TEMP_SENSOR)
  tasker.tick();
#endif
}