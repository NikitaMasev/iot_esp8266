#pragma once

#include <functional>
#include "WString.h"

using CallbackConnected = std::function<String()>;
using CallbackMessage = std::function<String(String)>;
using CallbackTaskerLoop = std::function<void()>;