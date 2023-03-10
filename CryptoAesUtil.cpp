#include "CryptoAesUtil.h"
#include "Base64.h"
#include <BearSSLHelpers.h>

String CryptoAesUtil::encrypt(String src) {
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

String CryptoAesUtil::decrypt(String src) {
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