#include "Network.h"
#include "IotController.h"
#include "CryptoAesUtil.h"

#define SERIAL_COMMUNICATION_SPEED 9600

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  setupIotController();
  delay(1000);
  setupNetwork();

  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);
  client.connect(iotServer);
}

void onMessageCallback(WebsocketsMessage message) {
  String decryptedData = decrypt(message.data());
  String dataForService = controlIncomingText(decryptedData);

  if (!dataForService.isEmpty()) {
    String encrypted = encrypt(dataForService);
    client.send(encrypted);
  }
}

void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    iotServerConnected = true;
    String dataForService = controlConnected();
    String encrypted = encrypt(dataForService);
    client.send(encrypted);
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    iotServerConnected = false;
  } else if (event == WebsocketsEvent::GotPing) {
    client.pong();
  } else if (event == WebsocketsEvent::GotPong) {
  }
}

void loop() {
  loopController();
}
