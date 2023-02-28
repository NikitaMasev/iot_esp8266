#pragma once

#include "Persistent.h"

class AuthPersistent {
private:
  Persistent persistent;
public:
  AuthPersistent(Persistent persistent) : persistent(persistent) {};
  void setup();
  void saveId(int newId);
  int getSavedId();
  bool getRegistered();
};