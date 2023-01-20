#include "RgbaAddressConfig.h"
#include "RgbaAddressUtil.h"

int idex = 0;             //-LED INDEX (0 to LED_COUNT-1
int ihue = 0;             //-HUE (0-255)
int ibright = 0;          //-BRIGHTNESS (0-255)
int isat = 0;             //-SATURATION (0-255)
int bouncedirection = 0;  //-SWITCH FOR COLOR BOUNCE (0-1)
float tcount = 0.0;       //-INC VAR FOR SIN LOOPS
int lcount = 0;           //-ANOTHER COUNTING VAR

//------------------------LED EFFECT FUNCTIONS------------------------
void one_color_all(int cred, int cgrn, int cblu) {  //-SET ALL LEDS TO ONE COLOR
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i].setRGB(cred, cgrn, cblu);
  }
}

void one_color_allHSV() {  //-SET ALL LEDS TO ONE COLOR (HSV)
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(ledConfigData.h, ledConfigData.s, ledConfigData.v);
  }
}

void rainbow_fade() {  //-m2-FADE ALL LEDS THROUGH HSV RAINBOW
  ihue++;
  if (ihue > 255) {
    ihue = 0;
  }
  for (int idex = 0; idex < LED_COUNT; idex++) {
    leds[idex] = CHSV(ihue, ledConfigData.s, 255);
  }
  LEDS.show();
  //delay(thisdelay);
}

void rainbow_loop() {  //-m3-LOOP HSV RAINBOW
  idex++;
  ihue = ihue + thisstep;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  if (ihue > 255) {
    ihue = 0;
  }
  leds[idex] = CHSV(ihue, ledConfigData.s, 255);
  LEDS.show();
  //delay(thisdelay);
}

void random_burst() {  //-m4-RANDOM INDEX/COLOR
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  leds[idex] = CHSV(ihue, ledConfigData.s, 255);
  LEDS.show();
  //delay(thisdelay);
}

void color_bounce() {  //-m5-BOUNCE COLOR (SINGLE LED)
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == LED_COUNT) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idex) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 255);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  //delay(thisdelay);
}

void color_bounceFADE() {  //-m6-BOUNCE COLOR (SIMPLE MULTI-LED FADE)
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == LED_COUNT) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  int iL1 = adjacent_cw(idex);
  int iL2 = adjacent_cw(iL1);
  int iL3 = adjacent_cw(iL2);
  int iR1 = adjacent_ccw(idex);
  int iR2 = adjacent_ccw(iR1);
  int iR3 = adjacent_ccw(iR2);
  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idex) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 255);
    } else if (i == iL1) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 150);
    } else if (i == iL2) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 80);
    } else if (i == iL3) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 20);
    } else if (i == iR1) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 150);
    } else if (i == iR2) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 80);
    } else if (i == iR3) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 20);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  //delay(thisdelay);
}

void ems_lightsONE() {  //-m7-EMERGENCY LIGHTS (TWO COLOR SINGLE LED)
  idex++;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue = (ledConfigData.h + 160) % 255;
  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idexR) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 255);
    } else if (i == idexB) {
      leds[i] = CHSV(thathue, ledConfigData.s, 255);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  //delay(thisdelay);
}

void ems_lightsALL() {  //-m8-EMERGENCY LIGHTS (TWO COLOR SOLID)
  idex++;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue = (ledConfigData.h + 160) % 255;
  leds[idexR] = CHSV(ledConfigData.h, ledConfigData.s, 255);
  leds[idexB] = CHSV(thathue, ledConfigData.s, 255);
  LEDS.show();
  //delay(thisdelay);
}

void flicker() {  //-m9-FLICKER EFFECT
  int random_bright = random(0, 255);
  int random_delay = random(10, 100);
  int random_bool = random(0, random_bright);
  if (random_bool < 10) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, random_bright);
    }
    LEDS.show();
    thisdelay = random_delay;
  }
}

void pulse_one_color_all() {  //-m10-PULSE BRIGHTNESS ON ALL LEDS TO ONE COLOR
  if (bouncedirection == 0) {
    ibright++;
    if (ibright >= 255) {
      bouncedirection = 1;
    }
  }
  if (bouncedirection == 1) {
    ibright = ibright - 1;
    if (ibright <= 1) {
      bouncedirection = 0;
    }
  }
  for (int idex = 0; idex < LED_COUNT; idex++) {
    leds[idex] = CHSV(ledConfigData.h, ledConfigData.s, ibright);
  }
  LEDS.show();
  //delay(thisdelay);
}

void pulse_one_color_all_rev() {  //-m11-PULSE SATURATION ON ALL LEDS TO ONE COLOR
  if (bouncedirection == 0) {
    isat++;
    if (isat >= 255) {
      bouncedirection = 1;
    }
  }
  if (bouncedirection == 1) {
    isat = isat - 1;
    if (isat <= 1) {
      bouncedirection = 0;
    }
  }
  for (int idex = 0; idex < LED_COUNT; idex++) {
    leds[idex] = CHSV(ledConfigData.h, isat, 255);
  }
  LEDS.show();
  //delay(thisdelay);
}

void fade_vertical() {  //-m12-FADE 'UP' THE LOOP
  idex++;
  if (idex > TOP_INDEX) {
    idex = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  ibright = ibright + 10;
  if (ibright > 255) {
    ibright = 0;
  }
  leds[idexA] = CHSV(ledConfigData.h, ledConfigData.s, ibright);
  leds[idexB] = CHSV(ledConfigData.h, ledConfigData.s, ibright);
  LEDS.show();
  //delay(thisdelay);
}

void random_red() {  //QUICK 'N DIRTY RANDOMIZE TO GET CELL AUTOMATA STARTED
  int temprand;
  for (int i = 0; i < LED_COUNT; i++) {
    temprand = random(0, 100);
    if (temprand > 50) {
      leds[i].r = 255;
    }
    if (temprand <= 50) {
      leds[i].r = 0;
    }
    leds[i].b = 0;
    leds[i].g = 0;
  }
  LEDS.show();
}

void rule30() {  //-m13-1D CELLULAR AUTOMATA - RULE 30 (RED FOR NOW)
  if (bouncedirection == 0) {
    random_red();
    bouncedirection = 1;
  }
  copy_led_array();
  int iCW;
  int iCCW;
  int y = 100;
  for (int i = 0; i < LED_COUNT; i++) {
    iCW = adjacent_cw(i);
    iCCW = adjacent_ccw(i);
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
  }
  LEDS.show();
  //delay(thisdelay);
}

void random_march() {  //-m14-RANDOM MARCH CCW
  copy_led_array();
  int iCCW;
  leds[0] = CHSV(random(0, 255), 255, 255);
  for (int idex = 1; idex < LED_COUNT; idex++) {
    iCCW = adjacent_ccw(idex);
    leds[idex].r = ledsX[iCCW][0];
    leds[idex].g = ledsX[iCCW][1];
    leds[idex].b = ledsX[iCCW][2];
  }
  LEDS.show();
  //delay(thisdelay);
}

static long lastTimeRwb = 0;

void rwb_march() {  //-m15-R,W,B MARCH CCW
  if (millis() - lastTimeRwb > 80) {
    copy_led_array();
    int iCCW;
    idex++;
    if (idex > 2) {
      idex = 0;
    }
    switch (idex) {
      case 0:
        leds[0].r = 255;
        leds[0].g = 0;
        leds[0].b = 0;
        break;
      case 1:
        leds[0].r = 255;
        leds[0].g = 255;
        leds[0].b = 255;
        break;
      case 2:
        leds[0].r = 0;
        leds[0].g = 0;
        leds[0].b = 255;
        break;
    }
    for (int i = 1; i < LED_COUNT; i++) {
      iCCW = adjacent_ccw(i);
      leds[i].r = ledsX[iCCW][0];
      leds[i].g = ledsX[iCCW][1];
      leds[i].b = ledsX[iCCW][2];
    }
    LEDS.show();
    lastTimeRwb = millis();
  }
}

void radiation() {  //-m16-SORT OF RADIATION SYMBOLISH- ?
  int N3 = int(LED_COUNT / 3);
  int N6 = int(LED_COUNT / 6);
  int N12 = int(LED_COUNT / 12);
  for (int i = 0; i < N6; i++) {  //-HACKY, I KNOW...
    tcount = tcount + .02;
    if (tcount > 3.14) {
      tcount = 0.0;
    }
    ibright = int(sin(tcount) * 255);
    int j0 = (i + LED_COUNT - N12) % LED_COUNT;
    int j1 = (j0 + N3) % LED_COUNT;
    int j2 = (j1 + N3) % LED_COUNT;
    leds[j0] = CHSV(ledConfigData.h, ledConfigData.s, ibright);
    leds[j1] = CHSV(ledConfigData.h, ledConfigData.s, ibright);
    leds[j2] = CHSV(ledConfigData.h, ledConfigData.s, ibright);
  }
  LEDS.show();
  //delay(thisdelay);
}

void color_loop_vardelay() {  //-m17-COLOR LOOP (SINGLE LED) w/ VARIABLE DELAY ???
  idex++;
  if (idex > LED_COUNT) {
    idex = 0;
  }
  int di = abs(TOP_INDEX - idex);
  int t = constrain((10 / di) * 10, 10, 500);
  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idex) {
      leds[i] = CHSV(0, ledConfigData.s, 255);
    } else {
      leds[i].r = 0;
      leds[i].g = 0;
      leds[i].b = 0;
    }
  }
  LEDS.show();
  delay(t);
}

void white_temps() {  //-m18-SHOW A SAMPLE OF BLACK BODY RADIATION COLOR TEMPERATURES
  int N9 = int(LED_COUNT / 9);
  for (int i = 0; i < LED_COUNT; i++) {
    if (i >= 0 && i < N9) {
      leds[i].r = 255;  //-CANDLE - 1900
      leds[i].g = 147;
      leds[i].b = 41;
    }
    if (i >= N9 && i < N9 * 2) {
      leds[i].r = 255;  //-40W TUNG - 2600
      leds[i].g = 197;
      leds[i].b = 143;
    }
    if (i >= N9 * 2 && i < N9 * 3) {
      leds[i].r = 255;  //-100W TUNG - 2850
      leds[i].g = 214;
      leds[i].b = 170;
    }
    if (i >= N9 * 3 && i < N9 * 4) {
      leds[i].r = 255;  //-HALOGEN - 3200
      leds[i].g = 241;
      leds[i].b = 224;
    }
    if (i >= N9 * 4 && i < N9 * 5) {
      leds[i].r = 255;  //-CARBON ARC - 5200
      leds[i].g = 250;
      leds[i].b = 244;
    }
    if (i >= N9 * 5 && i < N9 * 6) {
      leds[i].r = 255;  //-HIGH NOON SUN - 5400
      leds[i].g = 255;
      leds[i].b = 251;
    }
    if (i >= N9 * 6 && i < N9 * 7) {
      leds[i].r = 255;  //-DIRECT SUN - 6000
      leds[i].g = 255;
      leds[i].b = 255;
    }
    if (i >= N9 * 7 && i < N9 * 8) {
      leds[i].r = 201;  //-OVERCAST SKY - 7000
      leds[i].g = 226;
      leds[i].b = 255;
    }
    if (i >= N9 * 8 && i < LED_COUNT) {
      leds[i].r = 64;  //-CLEAR BLUE SKY - 20000
      leds[i].g = 156;
      leds[i].b = 255;
    }
  }
  LEDS.show();
}

void pop_horizontal() {  //-m20-POP FROM LEFT TO RIGHT UP THE RING
  int ix;
  if (bouncedirection == 0) {
    bouncedirection = 1;
    ix = idex;
  } else if (bouncedirection == 1) {
    bouncedirection = 0;
    ix = horizontal_index(idex);
    idex++;
    if (idex > TOP_INDEX) {
      idex = 0;
    }
  }
  for (int i = 0; i < LED_COUNT; i++) {
    if (i == ix) {
      leds[i] = CHSV(ledConfigData.h, ledConfigData.s, 255);
    } else {
      leds[i].r = 0;
      leds[i].g = 0;
      leds[i].b = 0;
    }
  }
  LEDS.show();
  //delay(thisdelay);
}

void quad_bright_curve() {  //-m21-QUADRATIC BRIGHTNESS CURVER
  int ax;
  for (int x = 0; x < LED_COUNT; x++) {
    if (x <= TOP_INDEX) {
      ax = x;
    } else if (x > TOP_INDEX) {
      ax = LED_COUNT - x;
    }
    int a = 1;
    int b = 1;
    int c = 0;
    int iquad = -(ax * ax * a) + (ax * b) + c;  //-ax2+bx+c
    int hquad = -(TOP_INDEX * TOP_INDEX * a) + (TOP_INDEX * b) + c;
    ibright = int((float(iquad) / float(hquad)) * 255);
    leds[x] = CHSV(ledConfigData.h, ledConfigData.s, ibright);
  }
  LEDS.show();
  //delay(thisdelay);
}

const float hmin = 0.1;
const float hmax = 45.0;
const float hdif = hmax - hmin;
int indexFlame = 0;
int idelay = 0;
int randtemp = 0;
float hinc = 0;
int ihueFlame = 0;

void flame() {  //-m22-FLAMEISH EFFECT
  if (indexFlame == 0) {
    thisdelay = random(0, 35);
    randtemp = random(0, 3);
    hinc = (hdif / float(TOP_INDEX)) + randtemp;
    ihueFlame = hmin;
    Serial.println(thisdelay);
  }

  if (indexFlame <= TOP_INDEX) {
    ihueFlame += hinc;
    leds[indexFlame] = CHSV(ihueFlame, ledConfigData.s, 255);
    int ih = horizontal_index(indexFlame);
    leds[ih] = CHSV(ihueFlame, ledConfigData.s, 255);
    leds[TOP_INDEX].r = 255;
    leds[TOP_INDEX].g = 255;
    leds[TOP_INDEX].b = 255;
    LEDS.show();
    indexFlame++;
  } else {
    indexFlame = 0;
  }
}

void rainbow_vertical() {  //-m23-RAINBOW 'UP' THE LOOP
  idex++;
  if (idex > TOP_INDEX) {
    idex = 0;
  }
  ihue = ihue + thisstep;
  if (ihue > 255) {
    ihue = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  leds[idexA] = CHSV(ihue, ledConfigData.s, 255);
  leds[idexB] = CHSV(ihue, ledConfigData.s, 255);
  LEDS.show();
  //delay(thisdelay);
}

void random_color_pop() {  //-m25-RANDOM COLOR POP
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  one_color_all(0, 0, 0);
  leds[idex] = CHSV(ihue, ledConfigData.s, 255);
  LEDS.show();
  //delay(thisdelay);
}

void ems_lightsSTROBE() {  //-m26-EMERGENCY LIGHTS (STROBE LEFT/RIGHT)
  int newHue = 0;
  int thathue = (newHue + 160) % 255;
  for (int x = 0; x < 5; x++) {
    for (int i = 0; i < TOP_INDEX; i++) {
      leds[i] = CHSV(newHue, ledConfigData.s, 255);
    }
    LEDS.show();
    delay(thisdelay);
    one_color_all(0, 0, 0);
    LEDS.show();
    delay(thisdelay);
  }
  for (int x = 0; x < 5; x++) {
    for (int i = TOP_INDEX; i < LED_COUNT; i++) {
      leds[i] = CHSV(thathue, ledConfigData.s, 255);
    }
    LEDS.show();
    delay(thisdelay);
    one_color_all(0, 0, 0);
    LEDS.show();
    delay(thisdelay);
  }
}

void rgb_propeller() {  //-m27-RGB PROPELLER
  idex++;
  int ghue = (ledConfigData.h + 80) % 255;
  int bhue = (ledConfigData.h + 160) % 255;
  int N3 = int(LED_COUNT / 3);
  int N6 = int(LED_COUNT / 6);
  int N12 = int(LED_COUNT / 12);
  for (int i = 0; i < N3; i++) {
    int j0 = (idex + i + LED_COUNT - N12) % LED_COUNT;
    int j1 = (j0 + N3) % LED_COUNT;
    int j2 = (j1 + N3) % LED_COUNT;
    leds[j0] = CHSV(ledConfigData.h, ledConfigData.s, 255);
    leds[j1] = CHSV(ghue, ledConfigData.s, 255);
    leds[j2] = CHSV(bhue, ledConfigData.s, 255);
  }
  LEDS.show();
  //delay(thisdelay);
}

void kitt() {  //-m28-KNIGHT INDUSTIES 2000
  int rand = random(0, TOP_INDEX);
  for (int i = 0; i < rand; i++) {
    leds[TOP_INDEX + i] = CHSV(ledConfigData.h, ledConfigData.s, 255);
    leds[TOP_INDEX - i] = CHSV(ledConfigData.h, ledConfigData.s, 255);
    LEDS.show();
    delay(thisdelay / rand);
  }
  for (int i = rand; i > 0; i--) {
    leds[TOP_INDEX + i] = CHSV(ledConfigData.h, ledConfigData.s, 0);
    leds[TOP_INDEX - i] = CHSV(ledConfigData.h, ledConfigData.s, 0);
    LEDS.show();
    delay(thisdelay / rand);
  }
}

void matrix() {  //-m29-ONE LINE MATRIX
  int rand = random(0, 100);
  if (rand > 90) {
    leds[0] = CHSV(ledConfigData.h, ledConfigData.s, 255);
  } else {
    leds[0] = CHSV(ledConfigData.h, ledConfigData.s, 0);
  }
  copy_led_array();
  for (int i = 1; i < LED_COUNT; i++) {
    leds[i].r = ledsX[i - 1][0];
    leds[i].g = ledsX[i - 1][1];
    leds[i].b = ledsX[i - 1][2];
  }
  LEDS.show();
}

void strip_march_cw() {  //-m50-MARCH STRIP CW ???
  copy_led_array();
  int iCW;
  for (int i = 0; i < LED_COUNT; i++) {
    iCW = adjacent_cw(i);
    leds[i].r = ledsX[iCW][0];
    leds[i].g = ledsX[iCW][1];
    leds[i].b = ledsX[iCW][2];
  }
  LEDS.show();
  //delay(thisdelay);
}

void strip_march_ccw() {  //-m51-MARCH STRIP CCW ???
  copy_led_array();
  int iCCW;
  for (int i = 0; i < LED_COUNT; i++) {
    iCCW = adjacent_ccw(i);
    leds[i].r = ledsX[iCCW][0];
    leds[i].g = ledsX[iCCW][1];
    leds[i].b = ledsX[iCCW][2];
  }
  LEDS.show();
  //delay(thisdelay);
}

void new_rainbow_loop() {  //-m88-RAINBOW FADE FROM FAST_SPI2
  ihue -= 1;
  fill_rainbow(leds, LED_COUNT, ihue);
  LEDS.show();
  //delay(thisdelay);
}

//-----------------------------плавное заполнение цветом-----------------------------------------
bool colorWipeFirst = true;
int indexColorWipe = 0;

void colorWipe(byte red, byte green, byte blue, byte redWipe, byte greenWipe, byte blueWipe) {
  if (indexColorWipe < LED_COUNT) {
    if (colorWipeFirst) {
      setPixel(indexColorWipe, red, green, blue);
    } else {
      setPixel(indexColorWipe, redWipe, greenWipe, blueWipe);
    }
    FastLED.show();
    indexColorWipe++;
  } else {
    indexColorWipe = 0;
    colorWipeFirst = !colorWipeFirst;
  }
}

//---------------------------------линейный огонь-------------------------------------
void setPixelHeatColor(int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F;  // 0..63
  heatramp <<= 2;               // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if (t192 > 0x80) {  // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if (t192 > 0x40) {  // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {  // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void Fire(int Cooling, int Sparking) {
  static byte heat[LED_COUNT];
  int cooldown;

  // Step 1.  Cool down every cell a little
  for (int i = 0; i < LED_COUNT; i++) {
    cooldown = random(0, ((Cooling * 10) / LED_COUNT) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (int k = LED_COUNT - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if (random(255) < Sparking) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for (int j = 0; j < LED_COUNT; j++) {
    setPixelHeatColor(j, heat[j]);
  }

  FastLED.show();
  //delay(SpeedDelay);
}

//-------------------------------newKITT---------------------------------------
byte *Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

const int rainbowCycles = 256 * 5;
int indexRainbowCycle = 0;

void rainbowCycle() {
  byte *c;

  if (indexRainbowCycle < rainbowCycles) {
    for (int i = 0; i < LED_COUNT; i++) {
      c = Wheel(((i * 256 / LED_COUNT) + indexRainbowCycle) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    FastLED.show();
    indexRainbowCycle++;
  } else {
    indexRainbowCycle = 0;
  }
}

//-------------------------------TwinkleRandom---------------------------------------
const int twinkleRandomCount = 20;
int indexTwinkleRandom = 0;
bool twinkleRandomDelay = false;

void TwinkleRandom() {
  if (indexTwinkleRandom == 0) {
    setAll(0, 0, 0);
  }

  if (indexTwinkleRandom < twinkleRandomCount && !twinkleRandomDelay) {
    setPixel(random(LED_COUNT), random(0, 255), random(0, 255), random(0, 255));
    FastLED.show();
    twinkleRandomDelay = true;
  } else if (indexTwinkleRandom < twinkleRandomCount && twinkleRandomDelay) {
    setAll(0, 0, 0);
    indexTwinkleRandom++;
    twinkleRandomDelay = false;
  } else {
    indexTwinkleRandom = 0;
  }
}

//-------------------------------RunningLights---------------------------------------
const int runningLightsCount = LED_COUNT * 2;
int indexRunningLights = 0;

void RunningLights(byte red, byte green, byte blue) {
  if (indexRunningLights < runningLightsCount) {
    for (int i = 0; i < LED_COUNT; i++) {
      setPixel(i, ((sin(i + indexRunningLights + 1) * 127 + 128) / 255) * red,
               ((sin(i + indexRunningLights + 1) * 127 + 128) / 255) * green,
               ((sin(i + indexRunningLights + 1) * 127 + 128) / 255) * blue);
    }
    FastLED.show();
    indexRunningLights++;
  } else {
    indexRunningLights = 0;
  }
}

//-------------------------------theaterChase---------------------------------------
const int theaterChaseCycles = 10;
const int theaterChaseQ = 3;
int indexCycleTheaterChase = 0;
int indexQTheaterChase = 0;
bool theaterChaseTurnMode = true;

void theaterChase(byte red, byte green, byte blue) {
  if (indexQTheaterChase < theaterChaseQ && theaterChaseTurnMode) {
    for (int i = 0; i < LED_COUNT; i = i + 3) {
      setPixel(i + indexQTheaterChase, red, green, blue);  //turn every third pixel on
    }
    FastLED.show();
    theaterChaseTurnMode = false;
  } else if (indexQTheaterChase < theaterChaseQ && !theaterChaseTurnMode) {
    for (int i = 0; i < LED_COUNT; i = i + 3) {
      setPixel(i + indexQTheaterChase, 0, 0, 0);  //turn every third pixel off
    }
    theaterChaseTurnMode = true;
    indexQTheaterChase++;
  } else if (indexQTheaterChase == theaterChaseQ && indexCycleTheaterChase < theaterChaseCycles) {
    indexQTheaterChase = 0;
    indexCycleTheaterChase++;
    theaterChaseTurnMode = true;
  } else if (indexCycleTheaterChase == theaterChaseCycles) {
    indexCycleTheaterChase = 0;
    theaterChaseTurnMode = true;
  }
}

//-------------------------------theaterChaseRainbow---------------------------------------
void theaterChaseRainbow(int SpeedDelay) {
  byte *c;

  for (int j = 0; j < 256; j++) {  // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < LED_COUNT; i = i + 3) {
        c = Wheel((i + j) % 255);
        setPixel(i + q, *c, *(c + 1), *(c + 2));  //turn every third pixel on
      }
      FastLED.show();
      delay(SpeedDelay);
      for (int i = 0; i < LED_COUNT; i = i + 3) {
        setPixel(i + q, 0, 0, 0);  //turn every third pixel off
      }
    }
  }
}

//-------------------------------Strobe---------------------------------------
const int delayPause = 1000;
const int delayFlash = 100;
const int strobeCount = 10;

static int strobeCounter = 0;
bool previousOn = false;
long lastTimeStrobe;
int strobeAnim = delayFlash;

void Strobe(byte red, byte green, byte blue) {
  if (millis() - lastTimeStrobe > strobeAnim) {
    if (strobeCounter == strobeCount) {
      strobeAnim = delayPause;
      strobeCounter = 0;
      setAll(0, 0, 0);
      FastLED.show();
    } else {
      if (previousOn) {
        setAll(0, 0, 0);
      } else {
        setAll(red, green, blue);
      }
      FastLED.show();
      strobeAnim = delayFlash;
      strobeCounter++;
      previousOn = !previousOn;
    }

    lastTimeStrobe = millis();
  }
}
