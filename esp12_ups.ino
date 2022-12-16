#include "Base64.h"
//#include "DataConstruct.h"
#include "TempDetector.h"
#include "VoltCur.h"
#include "CoolerControl.h"
#include "Network.h"
//#include "TypeDevice.h"
//#include "Persistent.h"
#include "IotAdapter.h"

///was 285 code lines, 319
#define SERIAL_COMMUNICATION_SPEED 9600

static String data = "";

long lastUpdate;

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  setupIna219();
  pullPersistentData();
  startWifi();

  webSocket.onEvent(webSocketEvent);
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      {
        String dataForService = adaptConnected();
        String encrypted = encrypt(dataForService);
        webSocket.sendTXT(encrypted);
      }
      break;
    case WStype_TEXT:
      {
        String normalizedData = decryptAndFormatToString(payload, length);
        String dataForService = adaptText(normalizedData);
        
        if (!dataForService.isEmpty()) {
          String encrypted = encrypt(dataForService);
          webSocket.sendTXT(encrypted);
        }
      }
      break;
    case WStype_BIN:
      break;
    case WStype_PING:
      break;
    case WStype_PONG:
      break;
  }
}

String decryptAndFormatToString(uint8_t *payload, size_t length) {
  char encrCmd[length + 1];

  memcpy(encrCmd, payload, length);
  encrCmd[length] = '\0';

  String decrCmd = decrypt(String(encrCmd));
  Serial.println(decrCmd);
  return decrCmd;
}

void loop() {
  webSocket.loop();
  updateTemperatures();
  updateVoltageAndCurrent();
  controlCooler();
}

///CBC
String encrypt(String src) {
  int i;
  // PKCS#7 Padding (Encryption), Block Size : 16
  int len = src.length();
  int n_blocks = len / 16 + 1;
  uint8_t n_padding = n_blocks * 16 - len;
  uint8_t data[n_blocks * 16];
  memcpy(data, src.c_str(), len);
  for (i = len; i < n_blocks * 16; i++) {
    data[i] = n_padding;
  }

  uint8_t key[16], iv[16];
  memcpy(key, cipher_key, 16);
  memcpy(iv, cipher_iv, 16);

  // encryption context
  br_aes_big_cbcenc_keys encCtx;

  // reset the encryption context and encrypt the data
  br_aes_big_cbcenc_init(&encCtx, key, 16);
  br_aes_big_cbcenc_run(&encCtx, iv, data, n_blocks * 16);

  // Base64 encode
  len = n_blocks * 16;
  char encoded_data[base64_enc_len(len)];
  base64_encode(encoded_data, (char *)data, len);

  return String(encoded_data);
}

String decrypt(String src) {
  int input_len = src.length();
  char *encoded_data = const_cast<char *>(src.c_str());
  int len = base64_dec_len(encoded_data, input_len);
  uint8_t data[len];
  base64_decode((char *)data, encoded_data, input_len);

  uint8_t key[16], iv[16];
  memcpy(key, cipher_key, 16);
  memcpy(iv, cipher_iv, 16);

  int n_blocks = len / 16;

  br_aes_big_cbcdec_keys decCtx;

  br_aes_big_cbcdec_init(&decCtx, key, 16);
  br_aes_big_cbcdec_run(&decCtx, iv, data, n_blocks * 16);

  // PKCS#7 Padding (Decryption)
  uint8_t n_padding = data[n_blocks * 16 - 1];
  len = n_blocks * 16 - n_padding;
  char plain_data[len + 1];
  memcpy(plain_data, data, len);
  plain_data[len] = '\0';

  return String(plain_data);
}
