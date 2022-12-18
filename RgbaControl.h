#include <GRGB.h>

// указать тип драйвера COMMON_CATHODE/COMMON_ANODE
// и пины в порядке R,G,B
GRGB rgbaControl(COMMON_CATHODE, 9, 10, 11);

int ledR = 128;
int ledG = 128;
int ledB = 100;
int ledA = 128;

void setupRgbaControl() {
  rgbaControl.setBrightness(ledA);
  led.setRGB(ledR, ledG, ledB);
  rgbaControl.setCRT(true);
}

void updateRgba(int r, int g, int b, int a) {
  ledR = r;
  ledG = g;
  ledB = b;
  ledA = a;

  setupRgbaControl();
}