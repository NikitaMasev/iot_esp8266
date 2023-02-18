#include "CryptoAesUtil.h"
#include "Network.h"

class CryptoNetwork {
private:
  Network network;
  CryptoAesUtil cryptoAesUtil;

  String (*onConnected)();
  String (*onMessage)(String data);

  String onMessageProxy(String data);
  String onConnectedProxy();

public:
  CryptoNetwork(Network network, CryptoAesUtil cryptoAesUtil);
  long getTimeRetryConnection();
  bool getConnectedState();
  void setup(String (*onConnected)(), String (*onMessage)(String data));
  void tick();
  void reconnect();
  void send(String data);
};