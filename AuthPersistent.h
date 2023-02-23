#pragma once

class AuthPersistent {
protected:
  bool registered = false;
  int idDevice;
public:
  virtual void setup() = 0;
  virtual void saveId(int newId) = 0;
  virtual int getSavedId() = 0;
  virtual bool getRegistered() = 0;
};