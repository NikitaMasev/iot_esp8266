#pragma once

#include "WString.h"
#include "DataConstruct.h"

class AuthDataConstruct {
private:
  DataConstruct dataConstruct;
public:
  AuthDataConstruct(DataConstruct dataConstruct)
    : dataConstruct(dataConstruct){};
  String constructRegister(String typeDevice);
  String constructAuth(int idDevice, String typeDevice);
};