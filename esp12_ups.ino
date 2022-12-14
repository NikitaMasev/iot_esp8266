#include "Base64.h"
#include "DataConstruct.h"
#include "TempDetector.h"
#include "VoltCur.h"
#include "CoolerControl.h"
#include "Network.h"
#include "TypeDevice.h"

///was 285 code lines, 319
#define SERIAL_COMMUNICATION_SPEED 9600

static String data = "";

long lastUpdate;

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);
  getAndCheckId();
  //id = 0;
  //saveId();

  startWifi();

  webSocket.onEvent(webSocketEvent);

  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
  }
}

void continueRegisteringIfNot(String decrCmd) {
  if (registering) {
    uint8_t indexStart = decrCmd.indexOf(API_PKG_SYMB) + 1;
    uint8_t indexEnd = decrCmd.lastIndexOf(API_PKG_SYMB);

    String cmd = decrCmd.substring(indexStart, indexEnd);
    id = cmd.toInt();

    saveId();
    //registerOrAuth();
  }
}

String decryptCmd(uint8_t *payload, size_t length) {
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

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      connected = false;
      break;
    case WStype_CONNECTED:
      {
        connected = true;
        //registerOrAuth();
      }
      break;
    case WStype_TEXT:
      {
        String decrCmd = decryptCmd(payload, length);
        continueRegisteringIfNot(decrCmd);
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
