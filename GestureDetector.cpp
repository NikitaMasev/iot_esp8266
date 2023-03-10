#include "GestureDetector.h"

void GestureDetector::attachLeft(CallbackTaskerLoop callback) {
  callbacksLeft[indexLeft] = callback;
  indexLeft++;
}

void GestureDetector::attachRight(CallbackTaskerLoop callback) {
  callbacksRight[indexRight] = callback;
  indexRight++;
}

void GestureDetector::tick() {
  Gesture gesture;                       // Gesture is an enum type from RevEng_PAJ7620.h
  gesture = sensorPajLed.readGesture();  // Read back current gesture (if any) of type Gesture

  switch (gesture) {
    case GES_FORWARD:
      {
        Serial.print("GES_FORWARD");
        break;
      }

    case GES_BACKWARD:
      {
        Serial.print("GES_BACKWARD");
        break;
      }

    case GES_LEFT:
      {
        Serial.print("GES_LEFT");
        for (int i = 0; i < COUNT_CALLBACKS; i++) {
          if (callbacksLeft[i] != nullptr) {
            callbacksLeft[i]();
          }
        }
        break;
      }

    case GES_RIGHT:
      {
        Serial.print("GES_RIGHT");
        for (int i = 0; i < COUNT_CALLBACKS; i++) {
          if (callbacksRight[i] != nullptr) {
            callbacksRight[i]();
          }
        }
        break;
      }

    case GES_UP:
      {
        Serial.print("GES_UP");
        break;
      }

    case GES_DOWN:
      {
        Serial.print("GES_DOWN");
        break;
      }

    case GES_CLOCKWISE:
      {
        Serial.print("GES_CLOCKWISE");
        break;
      }

    case GES_ANTICLOCKWISE:
      {
        Serial.print("GES_ANTICLOCKWISE");
        break;
      }

    case GES_WAVE:
      {
        Serial.print("GES_WAVE");
        break;
      }

    case GES_NONE:
      {
        break;
      }
  }
}