#include "AuthPersistent.h"

void AuthPersistent::setup() {
  persistent.setup();
}

void AuthPersistent::saveId(int newId) {
   persistent.saveId(newId);
}

int AuthPersistent::getSavedId() {
  return persistent.getSavedId();
}

bool AuthPersistent::getRegistered() {
  return persistent.getRegistered();
}