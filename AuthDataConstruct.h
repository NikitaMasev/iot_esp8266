#pragma once

#include "WString.h"
#include "DataStruct.h"

class AuthDataConstruct {
public:
  virtual String constructRegister(String typeDevice) = 0;
  virtual String constructAuth(int idDevice, String typeDevice) = 0;
};