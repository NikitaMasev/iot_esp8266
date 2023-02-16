#include "Network.h"
#include "IotController.h"

#define SERIAL_COMMUNICATION_SPEED 9600

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  setupIotController();
  delay(1000);
  setupNetwork();
}

void loop() {
  loopController();
}
