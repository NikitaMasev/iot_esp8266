// #include "CryptoAesUtil.h"
#include "IotNetwork.h"
// #include "CryptoNetwork.h"
// #include "DataConstruct.h"
// #include "Persistent.h"
// #include "DataParser.h"
// #include "Tasker.h"
// #include "IotModel.h"
// #include "IotController.h"
#include "Config.h"

// IotController *iotController;
// CryptoNetwork *cryptoNetwork2;
IotNetwork *iotNetwork;

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  //CryptoAesUtil cryptoAesUtil(cipher_key, cipher_iv);
  iotNetwork = new IotNetwork(ssid, password, iotServer);
  //CryptoNetwork cryptoNetwork(network, cryptoAesUtil);

  // DataConstruct dataConstruct;
  // DataParser dataParser;
  // Persistent persistent;
  //persistent.setup();
  (*iotNetwork).setup(
    []() {
      Serial.println("CALLBACK ON CONNECTED");
      return String("");
    },
    [](String data) {
      Serial.println("CALLBACK ON MESSAGE");
      return String("");
    });
  //   (*cryptoNetwork2).setup(
  //     []() {
  // Serial.println("CONNECTED");
  //       return String("");
  //     },
  //     [](String data) {
  //       Serial.println("DATA");
  //       return String("");
  //     });

  //Tasker tasker;
  //IotModel iotModel(cryptoNetwork, &dataConstruct, &persistent, tasker);

  //iotController = new IotController(iotModel, &persistent, dataParser, &dataConstruct);
  //IotController iotController(iotModel, &persistent, dataParser, &dataConstruct);
  //(*iotController).setup();
  //setupIotController();
  //delay(1000);
  //setupNetwork();
}

void loop() {
  //(*cryptoNetwork2).tick();
  (*iotNetwork).tick();
  //(*iotController).tick();
  //loopController();
}
