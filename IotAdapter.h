#include "WString.h"
#include "DataConstruct.h"
#include "Persistent.h"
#include "TypeDevice.h"

String adaptConnected() {
  switch (localStateAuth) {
    case notRegistered:
      localStateAuth = registering;
      return constructRegister(typeDeviceToString(currentTypeDevice));
    case registering:
      ///registering after adaptConnected function
      return "";
    case registered:
      return constructAuth(idDevice, typeDeviceToString(currentTypeDevice));
  }
  return "";
}

String adaptText(String data) {
  ParsedHeaderPayload headerPayload = parseTextData(data);

  if (headerPayload.header.isEmpty()) {
    return "";
  }


  return "";
}