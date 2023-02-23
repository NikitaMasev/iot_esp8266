#pragma once

#include "WString.h"

class CryptoAesUtil {
private:
  const uint8_t *cipher_key;
  const uint8_t *cipher_iv;
public:
  CryptoAesUtil(const uint8_t *cipher_key, const uint8_t *cipher_iv)
    : cipher_key(cipher_key), cipher_iv(cipher_iv){};
  String encrypt(String src);
  String decrypt(String src);
};
