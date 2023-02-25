#include "AuthDataConstruct.h"

String AuthDataConstruct::constructRegister(String typeDevice) {
  return (*dataConstruct).constructRegister(typeDevice);
}

String AuthDataConstruct::constructAuth(int idDevice, String typeDevice) {
  return (*dataConstruct).constructAuth(idDevice, typeDevice);
}