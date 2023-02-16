#pragma once

#include "WString.h"

class CryptoAesUtil {
private:
  uint8_t cipher_key[16] = { };
  uint8_t cipher_iv[16] = { };
public:
  String encrypt(String src);
  String decrypt(String src);
};
