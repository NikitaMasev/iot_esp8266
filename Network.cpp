#include "Network.h"

Network::Network(String serverAddress) {
  this->serverAddress = serverAddress;
  init();
}